#include <QtWidgets/QApplication>
#include <QTextCodec>

#include "FenPrincipale.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    FenPrincipale fen;
    fen.setWindowTitle("CONVERTISSEUR INFIXE-PREFIXE");
    fen.show();
    return app.exec();
}

