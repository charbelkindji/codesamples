#include "APropos.h"


    APropos::APropos()
    {
        //setFixedSize(500, 250);
        layoutPrincipal = new QVBoxLayout;
        layoutCentre = new QHBoxLayout;

        lab_img = new QLabel(this);
        lab_texte = new QLabel("<strong>Convertisseur d'expression"
                               "<br>de la forme infixe vers la<br>forme prefixe.</strong><br>"
                               "Auteur: Gaspard Charbel Novixi KINDJI<br>"
                               "<br>chabkind@gmail.com", this);
        btn_fermer = new QPushButton("Fermer", this);

        QPixmap pix("../Converter/icones/a_propos_.png");
        lab_img->setPixmap(pix);
        btn_fermer->setIcon(QIcon("../Converter/icones/quit.png"));



        layoutCentre->addWidget(lab_img);
        layoutCentre->addWidget(lab_texte);

        layoutPrincipal->addLayout(layoutCentre);

        layoutPrincipal->addWidget(btn_fermer, 0, Qt::AlignRight);

        setLayout(layoutPrincipal);

        connect(btn_fermer, SIGNAL(clicked()), this, SLOT(accept()));

        /****************************************************\
         ***********************STYLE************************
        \****************************************************/

        setStyleSheet("QLabel { font: 15px Footlight MT Light, sans-serif;"

                              "}"
                      "QPushButton { font: 13px Footlight MT Light, sans-serif;"

                              "}"
                      );


        setWindowTitle("A propos");

    }

