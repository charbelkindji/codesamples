#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    //Initialisations
    socket = new QTcpSocket(this);

    //Le signal stateChanged(QAbstractSocket::SocketState) est émis à chaque changement d'état de l'objet QTcpSocket
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(displayMsgConnected()));

    //Affichages des msg pour avertir l'utilisateur de ce qui se passe. En cas d'erreur notamment
    //Le signal error(QAbstractSocket::SocketError) est émis en cas d'erreur
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));

    //signal disconnected() émis par l'objet QTcpSocket à la déconnexion
    connect(socket, SIGNAL(disconnected()), this, SLOT(deconnecte()));
}


Client::~Client()
{
    delete ui;
}


/*
 * SLOTS
 */

void Client::on_connecterBtn_clicked()
{
    //Désactiver le boutton
    ui->connecterBtn->setEnabled(false);

    //Si le client était connecté on le déconnecte, sinon on le connecte au serveur
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
       socket->disconnectFromHost();

    }else if (socket->state() == QAbstractSocket::UnconnectedState)
    {
        // On désactive les connexions précédentes s'il y en a
        socket->abort();

        //Connexion au serveur suivant IP et port renseignés
        socket->connectToHost(ui->serveurIP->text(), ui->serveurPort->value());

        //Envoyer l'IP du client au serveur
        socket->write(getlocalIP().toUtf8());

        //Désactiver les champs
        ui->serveurIP->setEnabled(false);
        ui->serveurPort->setEnabled(false);
    }
}

void Client::displayMsgConnected()
{
    //On intercepte l'état QAbstractSocket::ConnectedState qui correspond à l'état du QTcpSocket une fois connecté
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        openDialog("Info", "Connexion", "Connexion au serveur effectuée avec succès !");

        ui->labelEtatConnexion->setText("Vous êtes connecté au serveur.");

        //Rétablir boutton
        ui->connecterBtn->setEnabled(true);

        //Modifier texte boutton
        ui->connecterBtn->setText("Déconnecter");
    }
}

void Client::deconnecte()
{
    ui->labelEtatConnexion->setText("Entrer les paramètres de connexion.");
    openDialog("Info", "Déconnexion", "Déconnexion effectuée avec succès !");

    ui->connecterBtn->setText("Connecter");
    ui->connecterBtn->setEnabled(true);

    //Activer les champs
    ui->serveurIP->setEnabled(true);
    ui->serveurPort->setEnabled(true);

}

/*
 *
 * AUTRES METHODES
 */

void Client::openDialog(QString type, QString title, QString msg)
{
    if(type == "Info")
    {
       QMessageBox::information(this, title, msg);
    }else if(type == "Warning")
    {
        QMessageBox::warning(this, title, msg);
    }else
    {
        QMessageBox::information(this, title, msg);
    }
}

QString Client::getlocalIP()
{
    QTcpSocket dnsTestSocket;
    QString localIP="127.0.0.1";    
    QString googleDns = "8.8.8.83";  
    dnsTestSocket.connectToHost(googleDns, 53);
    if (dnsTestSocket.waitForConnected(3000))
    {
        localIP = dnsTestSocket.localAddress().toString();
    }
    else
    {
        foreach (const QHostAddress &address, QNetworkInterface::allAddresses())
        {
            QString guessedGatewayAddress = address.toString().section( ".",0,2 ) + ".1";

            if (address.protocol() == QAbstractSocket::IPv4Protocol
                && address != QHostAddress(QHostAddress::LocalHost)
                )
            {
                dnsTestSocket.connectToHost(guessedGatewayAddress, 53);
                if (dnsTestSocket.waitForConnected(3000))
                {
                    localIP = dnsTestSocket.localAddress().toString();
                    break;
                }
            }
        }
    }
    return localIP;
}


void Client::erreurSocket(QAbstractSocket::SocketError erreur)
{
    switch(erreur) // On affiche un message différent selon l'erreur qu'on nous indique
    {
        case QAbstractSocket::HostNotFoundError:
            openDialog("Warning", "Erreur", "Le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port.");
            break;
        case QAbstractSocket::ConnectionRefusedError:
            openDialog("Warning", "Erreur", "Le serveur a refusé la connexion. Vérifiez si le programme \"Serveur scan\" a bien été lancé. Vérifiez aussi l'IP et le port.");
            break;
        case QAbstractSocket::RemoteHostClosedError:
            openDialog("Warning", "Erreur", "Le serveur a coupé la connexion.");
            break;
        default:
            openDialog("Warning", "Erreur", socket->errorString());
    }

    //Rétablir boutton et champs
    ui->serveurIP->setEnabled(true);
    ui->serveurPort->setEnabled(true);

    ui->connecterBtn->setEnabled(true);
}
