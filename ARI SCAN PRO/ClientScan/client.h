#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QtNetwork>
#include <QMessageBox>

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0); //constructeur
    ~Client(); //destructeur
    QString getlocalIP(); //Pour récupérer l'adresse IP du client
    void openDialog(QString type, QString title, QString msg); //Ouvrir des boîtes de dialogue


private slots:
    void on_connecterBtn_clicked(); //connexion au serveur
    void displayMsgConnected(); //Affichage de msg
    void deconnecte(); //déconnexion
    void erreurSocket(QAbstractSocket::SocketError erreur); // msg d'erreur dans la connexion au serveur

private:
    Ui::Client *ui;
    QTcpSocket *socket;
};

#endif // CLIENT_H
