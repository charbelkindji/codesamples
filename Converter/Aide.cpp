#include "Aide.h"

Aide::Aide()
{
//    setFixedSize(500, 250);
    hLayout = new QHBoxLayout;
    layoutPrincipal = new QVBoxLayout;
    btn_ok = new QPushButton("OK", this);
    lab_img = new QLabel;
    lab_texte = new QLabel("Saisissez une expression sous sa\n"
                           "forme infixée dans le champ du haut.\n"
                           "Cliquez ensuite sur le bouton 'Convertir'\n"
                           "pour convertir l'expression vers sa\nforme préfixée.\nMERCI !", this);

    /****************************************************\
     *************Propriétés des  widgets****************
    \****************************************************/

    btn_ok->setIcon(QIcon("../Converter/icones/quit.png"));

    QPixmap pix("../Converter/icones/aide_.png");
    lab_img->setPixmap(pix);

    hLayout->addWidget(lab_img);
    hLayout->addWidget(lab_texte);
    layoutPrincipal->addLayout(hLayout);
    layoutPrincipal->addWidget(btn_ok, 0, Qt::AlignCenter);

    setLayout(layoutPrincipal);

    connect(btn_ok, SIGNAL(clicked()), this, SLOT(accept()));


    /****************************************************\
     ***********************STYLE************************
    \****************************************************/

    setStyleSheet("QLabel { font: 15px Footlight MT Light, sans-serif;"

                          "}"
                  "QPushButton { font: 13px Footlight MT Light, sans-serif;"

                          "}"
                  );


    setWindowTitle("Aide");
}
