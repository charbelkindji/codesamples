#include "serveur.h"
#include "ui_serveur.h"

Serveur::Serveur(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Serveur)
{
    //Initalisation des variables
    ui->setupUi(this);

    serveur = new QTcpServer(this);
    modeleClientsIP = new QStringListModel(clientsIP);
    nbreClients = 0;
    IPV6Table =  new QHash<QHostAddress, QString>();

    //Empêcher que la liste soit éditable
    ui->listViewIP->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Application du modèle à la vue
    ui->listViewIP->setModel(modeleClientsIP);

    // Démarrage du serveur sur toutes les IP disponibles et sur un port libre
    if (!serveur->listen(QHostAddress::Any))
    {
        openDialog("Warning", "Erreur", tr("Le serveur n'a pas pu être démarré. Raison :<br />") + serveur->errorString());
    }
    else
    {
        //Serveur démarré. Afficher msg et maj interface
        openDialog("Info", "Serveur démarré", tr("Le serveur a été démarré sur le port <strong>") + QString::number(serveur->serverPort()));

        ipServeur = getlocalIP();
        portServeur = serveur->serverPort();

        ui->etatServeur->setText(tr("Le serveur est démarré. IP : <strong>") + ipServeur + tr("</strong> || Port : <strong>") + QString::number(portServeur) + tr("</strong>"));
        connect(serveur, SIGNAL(newConnection()), this, SLOT(nouvelleConnexion()));
    }
}

Serveur::~Serveur()
{
    delete ui;
}

/*
 * SLOTS
 */
void Serveur::nouvelleConnexion()
{
    QTcpSocket *nouveauClient = serveur->nextPendingConnection();
    clients << nouveauClient;

    //Connexion des signaux du client aux différents slots
    connect(nouveauClient, SIGNAL(readyRead()), this, SLOT(majListClients()));
    connect(nouveauClient, SIGNAL(disconnected()), this, SLOT(deconnexionClient()));

    QString data = QString(nouveauClient->readLine());

    //Incrément nombre de clients
    nbreClients++;
}

void Serveur::deconnexionClient()
{
    // On détermine quel client se déconnecte
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) // Si on n'a pas trouvé le client à l'origine du signal, on arrête la méthode
        return;

    clients.removeOne(socket);

    socket->deleteLater();

    //Retirer Ip de la liste des IP
    clientsIP.removeOne(IPV6Table->value(socket->peerAddress()));

    //Maj QListView
    modeleClientsIP->setStringList(clientsIP); //maj liste du modèle
    ui->listViewIP->setModel(modeleClientsIP);

    //Décrémenter nbre clients
    nbreClients--;

    //Si pour une raison ou pour une autre cette variable passe à une valeur négative, on la remet à zéro
    if(nbreClients < 0)
        nbreClients = 0;

    //Maj label nombreclients connectés
    QString labelText = "";

    //Afficher "05" par exemple ...
    if(nbreClients < 10)
    {
        labelText ="Clients connectés (0" + QString::number(nbreClients) + ")";

    }else
    {
        labelText ="Clients connectés (" + QString::number(nbreClients) + ")";
    }

    ui->labelClientsCon->setText(labelText);

    openDialog("Info", "INFORMATION", "Un client s'est déconnecté !");
}


void Serveur::on_scanBtn_clicked()
{
    //Si aucun client connecté, erreur
    if(clients.isEmpty())
    {
        openDialog("Warning", "Erreur",  tr("Aucun client connecté ! Les clients peuvent se connecter en utilisant les paramètres suivants :<br />"
                                            "<strong>Adresse IP : </strong>") + ipServeur +
                                            "<br /><strong>Port : </strong>" + QString::number(portServeur));

    }else if(ui->startPortInPut->value() > ui->endtPortInPut->value())
    {
      //Erreur port début ne peut pas être supérieur à port fin
        openDialog("Warning", "Erreur",  "Veuillez entrer une plage de port valide. Le port de début ne peut pas être supérieur au port de fin.");

    }else
    {
        //Tout est OK. On peut lancer le scan
        ui->labelResultScan->setText("Résultats du scan (Scan en cours...)");
        ui->scanBtn->setEnabled(false);
        openDialog("Info", "INFORMATION", "Veuillez patienter. Scan des clients en cours...");

        //Récupérer informations renseignées
        int startPort = ui->startPortInPut->value();
        int endPort = ui->endtPortInPut->value();

        //Initialisation de variables pour le traitement
        int nbOpenPort = 0;
        int nbClosedPort = 0;
        int nbLinesPerClient = (endPort - startPort) + 1;
        int indexClientInfo = 0; //Garder l'index de la ligne contenant l'IP du client pour maj nb ports ouvers et fermés

        //Modèle de données pour l'affichage dans le QListView
        QStandardItemModel *modele = new QStandardItemModel(this);

        //On boucle sur l'ensemble des clients. Et pour chaque client, sur l'ensemble des ports spécifiés
        for(int i = 0; i<clientsIP.size(); i++)
        {
            if(i != 0)
            {
                //index nouvelle adr = précédent index + nbre lignes ajoutées
                indexClientInfo = (indexClientInfo + nbLinesPerClient) + 1;
            }

            //Première ligne du résultat
            QList<QStandardItem*> clientInfo;
            clientInfo.append(new QStandardItem(clientsIP[i])); //ip client
            clientInfo.append(new QStandardItem(""));
            clientInfo.append(new QStandardItem(""));

            modele->appendRow(clientInfo);

            //Scanner les ports spécifiés
            for(int j = startPort; j<= endPort; j++)
            {
                QList<QStandardItem*> items;
                items.append(new QStandardItem(""));
                items.append(new QStandardItem(QString::number(j))); //le port

                //Passer l'IP et le port sur lequel on est à la méthode
                if(scanPorts(clientsIP[i], j))
                {
                    nbOpenPort++;
                    items.append(new QStandardItem("OUVERT")); //son état
                }else
                {
                   nbClosedPort++;
                   items.append(new QStandardItem("FERME")); //son état
                }
                modele->appendRow(items); //ajout de la ligne au modèle
            }

//            openDialog("Info", "Nb ouverts", "Nb ouverts = " + QString::number(nbOpenPort));
//            openDialog("Info", "Nb fermés", "Nb fermés = " + QString::number(nbClosedPort));

            //Sauvegarder les résultats pour affichage
            /* La vue : exemple
             * ------------------------------------------------------
             * Client       |  Port             | Etat              |
             * ------------------------------------------------------
             * 198.168.8.45 (Ports ouverts : 5  | Ports fermés : 4) |
             * ------------------------------------------------------
             *              |        5          |      OUVERT       |
             * ------------------------------------------------------
             *              |        6          |       FERME       |
             * ------------------------------------------------------
             * 198.168.8.45 (Ports ouverts : 5  | Ports fermés : 4) |
             * ------------------------------------------------------
             *              |        5          |      OUVERT       |
             * ------------------------------------------------------
             *              |        6          |       FERME       |
             * ------------------------------------------------------
             * 198.168.8.45 (Ports ouverts : 5  | Ports fermés : 4) |
             * ------------------------------------------------------
             *              |        5          |      OUVERT       |
             * ------------------------------------------------------
             *              |        6          |       FERME       |
             * ------------------------------------------------------
             */

            //Maj de la première ligne où figure l'IP du client pour définir le nmbre de ports ouverts et fermés
            modele->setItem(indexClientInfo, 1, new QStandardItem("Ouverts : " + QString::number(nbOpenPort)));
            modele->setItem(indexClientInfo, 2, new QStandardItem("Fermés : " + QString::number(nbClosedPort)));

            //Remettre les valeurs à 0 pour client suivant
            nbOpenPort = 0;
            nbClosedPort = 0;

            //maj liste résultas au fur et à mesure
            majResultScan(modele);
        }

        //Scan achevé. Affichage des résultats
        ui->labelResultScan->setText("Résultats du scan");
        ui->scanBtn->setEnabled(true);
        openDialog("Info", "INFORMATION", "Scan achevé !");
        setHeader(modele);
    }
}


/*
 * AUTRES METHODES
 */

bool Serveur::scanPorts(QString IP, int port)
{
    bool isOpen = false;

    //Etablir la connexion TCP
    //Si ok, alors port ouvert ; sinon,port fermé
    QTcpSocket socket(0);
    socket.abort();
    socket.connectToHost(IP, port);

    if(socket.waitForConnected(1000)){
        isOpen = true;
    }

    return isOpen;
}

void Serveur::openDialog(QString type, QString title, QString msg)
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

void Serveur::majListClients()
{
     QTcpSocket* conn = qobject_cast<QTcpSocket*>(sender());
     QString data = QString(conn->readLine());

     //Ajouter l'IP du client à la liste des IP
     clientsIP << data;

     //Stocker les IP dans un tableau clé -> valeur pour pouvoir les supprimer en se basant sur l'index
     IPV6Table->insert(conn->peerAddress(), data);

     //Maj de la liste des clients
     if(modeleClientsIP->insertRow(modeleClientsIP->rowCount())) {
         QModelIndex index = modeleClientsIP->index(modeleClientsIP->rowCount() - 1, 0);
         modeleClientsIP->setData(index, data);
     }

     //Afficher "05" par exemple ...
     QString labelText = "";

     if(nbreClients < 10)
     {
         labelText ="Clients connectés (0" + QString::number(nbreClients) + ")";

     }else
     {
         labelText ="Clients connectés (" + QString::number(nbreClients) + ")";
     }

     ui->labelClientsCon->setText(labelText);

     openDialog("Info", "INFORMATION", "Un nouveau client s'est connecté !");
}


QString Serveur::getlocalIP()
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

void Serveur::majResultScan(QStandardItemModel *modele)
{
    ui->treeViewPort->setModel(modele);
}


void Serveur::setHeader(QStandardItemModel *modele)
{
    //Creation du header du tableau de résultats de scan des ports
    //Définir le header du tableau
    modele->setHeaderData(0, Qt::Horizontal, QObject::tr("CLIENT"));
    modele->setHeaderData(1, Qt::Horizontal, QObject::tr("PORT"));
    modele->setHeaderData(2, Qt::Horizontal, QObject::tr("ETAT"));
}
