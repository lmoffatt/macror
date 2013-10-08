#include "Markov_GUI/MacrorMainWindow.h"
#include "Markov_Console/Markov_CommandManagerTest.h"

#include <QApplication>
#include <qdebug.h>

#include "Markov_IO/ABFFile.h"
#include "Markov_IO/PulsesProgram.h"

int main(int argc, char **argv)
{
 QApplication app(argc, argv);
   Markov_Console::Markov_CommandManagerTest* cm=new Markov_Console::Markov_CommandManagerTest();
   MacrorMainWindow mainWin(0,cm);
   mainWin.resize(800, 608);
    mainWin.show();
    return app.exec();
}

