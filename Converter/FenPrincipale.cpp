#include "FenPrincipale.h"
#include <QStack>

FenPrincipale::FenPrincipale()
{

    fen_apropos = new APropos;
    fen_aide = new Aide;

    //setFixedSize();

    /****************************************************\
     ***********************Layouts**********************
    \****************************************************/
    layoutPrincipal = new QVBoxLayout;
    layoutExpression = new QHBoxLayout;
    layoutCentre = new QVBoxLayout;
    layoutHaut = new QHBoxLayout;
    layoutBas = new QHBoxLayout;

    /****************************************************\
     ******************Autres widgets********************
    \****************************************************/
    lab_titre = new QLabel("CONVERTISSEUR INFIXE VERS PREFIXE");
    lab_exp = new QLabel("Expression infixe");
    champ_exp = new QLineEdit(this);
    btn_effacer = new QPushButton(this);
    btn_convertir = new QPushButton("Convertir", this);
    lab_resultat = new QLabel("Résultat");
    champ_resultat = new QLineEdit(this);
    btn_aide = new QPushButton("Aide", this);
    btn_apropos = new QPushButton("A propos", this);
    btn_quitter = new QPushButton("Quitter", this);

    /****************************************************\
     *************Propriétés des  widgets****************
    \****************************************************/
    btn_effacer->setIcon(QIcon("../Converter/icones/effacer.png"));
    btn_convertir->setIcon(QIcon("../Converter/icones/convert.png"));

    //lab_titre->setStyleSheet("background-image: url(\"../Converter/icones/titre.png\"");
    btn_effacer->setToolTip("Effacer");

    champ_resultat->setReadOnly(true);

    btn_aide->setToolTip("Aide");
    btn_aide->setIcon(QIcon("../Converter/icones/aide.png"));

    btn_apropos->setIcon(QIcon("../Converter/icones/a_propos.png"));
    btn_quitter->setIcon(QIcon("../Converter/icones/quit.png"));

    QPixmap pix("../Converter/icones/logo.png");
    //ui->label->setStyelSheet("border-image:url(:/2.png);");
    lab_titre->setPixmap(pix);

    /****************************************************\
     *************Ajout des widgets aux layouts**********
    \****************************************************/

    layoutHaut->addWidget(lab_titre);
    layoutBas->addWidget(btn_aide, 0, Qt::AlignRight);

    layoutExpression->addWidget(champ_exp);
    layoutExpression->addWidget(btn_effacer);


    layoutCentre->addWidget(btn_convertir, 0, Qt::AlignCenter);
    layoutCentre->addWidget(lab_resultat, 0, Qt::AlignCenter);

    layoutBas->addWidget(btn_apropos, 0, Qt::AlignRight);
    layoutBas->addWidget(btn_quitter, 0, Qt::AlignRight);

    layoutPrincipal->addLayout(layoutHaut);
    layoutPrincipal->addWidget(lab_exp, 0, Qt::AlignCenter);
    layoutPrincipal->addLayout(layoutExpression);
    layoutPrincipal->addLayout(layoutCentre);
    layoutPrincipal->addWidget(champ_resultat);
    layoutPrincipal->addLayout(layoutBas);

    setLayout(layoutPrincipal);

    /****************************************************\
     *******************Signaux et slots*****************
    \****************************************************/

    QObject::connect(btn_quitter, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(btn_convertir, SIGNAL(clicked()), this, SLOT(convertir()));
    QObject::connect(btn_effacer, SIGNAL(clicked()), this, SLOT(effacer()));
    QObject::connect(btn_apropos, SIGNAL(clicked()), this, SLOT(affiche_apropos()));
    QObject::connect(btn_aide, SIGNAL(clicked()), this, SLOT(affiche_aide()));
    QObject::connect(champ_exp, SIGNAL(returnPressed()), this, SLOT(convertir()));
    QObject::connect(champ_exp, SIGNAL(textChanged(QString)), this, SLOT(viderChampResultat(QString)));

    /****************************************************\
     ***********************STYLE************************
    \****************************************************/



    setStyleSheet("qApp {background-color: red;}"
                  "QLineEdit { border-radius: 5px;"
                               "border: 1px solid black;"
                               "padding: 3px;"
                               "font: 15px Century Gothic, sans-serif;"

                             "}"
                  "QLabel { font: 15px Footlight MT Light, sans-serif;"

                          "}"
                  "QPushButton { font: 13px Footlight MT Light, sans-serif;"

                          "}"
                  );



}

void FenPrincipale::viderChampResultat(QString)
{
    champ_resultat->setText("");
}

void FenPrincipale::effacer()
{
    champ_exp->setText("");
    champ_resultat->setText("");
    champ_exp->setFocus();
}

void FenPrincipale::affiche_apropos()
{
    fen_apropos->setModal(true);
    fen_apropos->exec();


}

void FenPrincipale::affiche_aide()
{
    fen_aide->setModal(true);
    fen_aide->exec();
}


QString FenPrincipale::inverseChaine(QString exp)
{
    QString chaineInverse = "";
    for(int i(exp.size()); i>0; i--)
    {
        /*Changer les '(' en ')' et les ')' en '('
           (A+B^C)*D+E^5 --> 5^E+D*)C^B+A( --> 5^E+D*(C^B+A)
        */

        if(exp.at(i-1) == '(')
        {
            chaineInverse += ")";
        }else if(exp.at(i-1) == ')')
        {
            chaineInverse += "(";
        }else if(exp.at(i-1) == ' ')
        {
            continue;

        }else
        {
            chaineInverse += exp.at(i-1);
        }

    }
    return chaineInverse;
}

bool FenPrincipale::estOperateur(QChar symbole)
{
    if(symbole == '^')
    {
        return true;
    }else if(symbole == '*')
    {
        return true;
    }else if(symbole == '/')
    {
        return true;
    }else if(symbole == '+')
    {
        return true;
    }else if(symbole == '-')
    {
        return true;
    }else if(symbole == '(')
    {
        return true;
    }else if(symbole == ')')
    {
        return true;
    }else
    {
        return false;
    }
}

bool FenPrincipale::testPriorite(QChar operateur1, QChar operateur2)
{
    //operateur1 celui qu'on veut ajouter, operateur2, celui qui était dans la pile

    /*
     *  ^       1
     *  *,/     2
     *  +,-     3
     */

     //return true --> dépiler et envoyer dans exp finale

     if(operateur1 == '^')
     {
         if(operateur2 == operateur1)
         {
             return true;
         }else
         {
             return false;
         }
     }else if(operateur1 == '*' || operateur1 == '/')
     {
         if(operateur2 == operateur1 || operateur2 == '^')
         {
             return true;
         }else
         {
             return false;
         }
     }else if(operateur1 == '+' || operateur1 == '-')
     {
         return true;
     }

}

void FenPrincipale::convertir()
{
    if(champ_exp->text().isEmpty())
    {
        QMessageBox::critical(this, "Erreur", "Veuillez renseigner l'expression à convertir !");
    }else
    {
        QStack <QChar> operateurs;
        QString expTraitement(""), expConvertie("");

        //Récupérer expression infixe saisie
        QString expInfix = champ_exp->text();

        //Inverser expression
        expTraitement = FenPrincipale::inverseChaine(expInfix);

        int i(0);
        do
        {
             //Tester si opérande ou opérateur
            if(FenPrincipale::estOperateur(expTraitement.at(i)))
            {
                //Les opérateurs dans la pile '(' et ')' aussi
                //Si pile vide, empiler
                if(operateurs.empty())
                {
                    operateurs.push(expTraitement.at(i));
                    expTraitement = expTraitement.mid(1, expTraitement.size()-1);
                    i--;
                }else
                {
                    if(expTraitement.at(i) == '(')
                    {
                        operateurs.push(expTraitement.at(i));
                        expTraitement = expTraitement.mid(1, expTraitement.size()-1);
                        i--;

                    }else if(expTraitement.at(i) == ')')
                    {
                        /*dépiler l'opérateur depuis pile puis l'ajouter à
                         *exp finale jusqu'à trouver le '('
                         */
                        while(operateurs.top() != '(')
                        {
                           expConvertie += operateurs.top();
                           operateurs.pop();
                        }
                        //... puis dépiler pile pour se débarrasser du '('
                        operateurs.pop();

                        //Suppression du caractère ')'
                       expTraitement = expTraitement.mid(1, expTraitement.size()-1);
                       i--;
                    }else
                    {
                        //Parcourir la pile des operateurs

                       /*tant que l'opérateur au sommet de la pile est moins
                       prioritaire ou égal à la priorité de l'opérateur en
                       cours dépiler et ajouter à EP. enfin empiler l'opérateur.
                       */


                       while(testPriorite(expTraitement.at(i), operateurs.top())) // J'usquà rencontrer '('
                       {

                            if(operateurs.top() == '(')
                                break;

                           expConvertie += operateurs.top();
                           //Vider la pile
                           //Quand il n'y a qu'un seul élément, le pop ne fonctionne pas. Donc vider la pie dans ce cas
                           if(operateurs.size() == 1)
                           {
                               operateurs = QStack <QChar>();
                                //~operateurs;
                               break;
                            }else
                            {
                                operateurs.pop();
                            }
                       }
                       //Empiler l'opérateur
                       operateurs.push(expTraitement.at(i));
                       expTraitement = expTraitement.mid(1, expTraitement.size()-1);

                       i--;
                    }
                }
            }else
            {
                //Opérande dans l'expression finale
                expConvertie += expTraitement.at(i);
                expTraitement = expTraitement.mid(1, expTraitement.size()-1);
                i--;
            }

            i++;

                    //A un moment donné, l'expression est vidée et il reste à vider les opérateurs restants et les ajouter au résultat
            if(expTraitement.size() == 0 && operateurs.size() != 0)
            {
                while(!operateurs.empty())
                {

                    expConvertie += operateurs.top();
                    operateurs.pop();
                }
                break;
                //Fin de conversion
            }

        }while(expTraitement.size() != 0);

        //Inverser expression à nouveau
        expConvertie = inverseChaine(expConvertie);

        //Afficher le résultat

        champ_resultat->setText(expConvertie);

           // champ_resultat->setText(champ_exp->text());
    }
}
