#ifndef APROPOS_H
#define APROPOS_H


#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QPixmap>

class APropos : public QDialog
{
public:
    APropos();

private:
    QVBoxLayout *layoutPrincipal;
    QHBoxLayout *layoutCentre;
    QPushButton *btn_fermer;
    QLabel *lab_img;
    QLabel *lab_texte;

};
#endif // APROPOS_H
