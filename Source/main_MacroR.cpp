#include "Markov_GUI/MacrorMainWindow.h"


#include <QApplication>
#include <qdebug.h>

int main(int argc, char **argv)
{

    QApplication app(argc, argv);
    MacrorMainWindow mainWin;
    mainWin.resize(800, 608);
    mainWin.show();
    return app.exec();
}
