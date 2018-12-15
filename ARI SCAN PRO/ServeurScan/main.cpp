#include <QApplication>
#include "serveur.h"

int main (int argc, char* argv[])
{

    QApplication app(argc, argv);

    Serveur fen;
    fen.show();

    return app.exec();
}
