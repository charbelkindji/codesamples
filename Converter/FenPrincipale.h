#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include "APropos.h"
#include "Aide.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>
#include <QPixmap>
#include <QtWidgets/QMessageBox>

class FenPrincipale : public QWidget
{
    Q_OBJECT

public:
    FenPrincipale();
    QString inverseChaine(QString exp);
    bool estOperateur(QChar symbole);
    bool testPriorite(QChar operateur1, QChar operateur2);

public slots:
    void convertir();
    void effacer();
    void affiche_apropos();
    void affiche_aide();
    void viderChampResultat(QString);

private:
    //Layouts
    QVBoxLayout *layoutPrincipal;
    QHBoxLayout *layoutExpression;
    QHBoxLayout *layoutHaut;
    QHBoxLayout *layoutBas;
    QHBoxLayout *layoutBas1;
    QHBoxLayout *layoutBas2;
    QVBoxLayout *layoutCentre;

    QLabel *lab_titre;
    QLabel *lab_exp;
    QLineEdit *champ_exp;
    QPushButton *btn_effacer;
    QPushButton *btn_convertir;
    QLabel *lab_resultat;
    QLineEdit *champ_resultat;
    QPushButton *btn_apropos;
    QPushButton *btn_quitter;
    QPushButton *btn_aide;


    //Autres fenêtres
    APropos *fen_apropos;
    Aide *fen_aide;



};


#endif // FENPRINCIPALE_H
