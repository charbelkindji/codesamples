#ifndef AIDE_H
#define AIDE_H


#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>

class Aide : public QDialog
{
public:
    Aide();

private:
    QVBoxLayout *layoutPrincipal;
    QHBoxLayout *hLayout;
    QPushButton *btn_ok;
    QLabel *lab_img;
    QLabel *lab_texte;

};
#endif // AIDE_H
