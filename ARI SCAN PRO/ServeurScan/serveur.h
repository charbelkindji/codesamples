#ifndef SERVEUR_H
#define SERVEUR_H

#include <QWidget>
#include <QStringListModel>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QStringList>
#include <QHash>
#include <QNetworkInterface>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QHeaderView>

namespace Ui {
class Serveur;
}

class Serveur : public QWidget
{
    Q_OBJECT

public:
    explicit Serveur(QWidget *parent = 0); //constructeur
    ~Serveur(); //destructeur
    void openDialog(QString type, QString title, QString msg); //Ouvrir des boîtes de dialogue
    QString getlocalIP(); //Pour récupérer l'adresse IP du serveur

    bool scanPorts(QString IP, int port); //Méthode effectuant le scan des ports
    void majResultScan(QStandardItemModel *modele); // Mise à jour de la vue pour afficher les résultats du scan
    void setHeader(QStandardItemModel *modele); //Définir les entêtes de la liste des résultats du scan



private:
    Ui::Serveur *ui;

    QTcpServer *serveur; //Représente le serveur
    QList<QTcpSocket *> clients; //Liste des clients. Un client = un objet QTcpSocket
    QStringList clientsIP; //Liste des adresse IP des clients pour les afficher dans la zone prévue
    QStringListModel *modeleClientsIP; //Modèle de donnée pour l'affichage des Ip des clients
    int nbreClients; //Nombre de clients connectés

    //Tableau clé => valeur contenant en clé les adresses des clients en IPV6 et en valeur, les adresses en IPV4 reçues des clients
    //Ceci est utilisé pour entre autre mettre à jour la liste des IP des clients
    QHash<QHostAddress, QString> *IPV6Table;
    QString ipServeur; //stocke l'IP du serveur
    int portServeur; //stocke le port du serveur

private slots:
    void nouvelleConnexion();
    void majListClients();
    void deconnexionClient();
    void on_scanBtn_clicked(); //Déclancher le scan

};

#endif // SERVEUR_H
