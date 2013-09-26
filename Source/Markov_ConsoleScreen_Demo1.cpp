#include <fstream>

#include <QApplication>

#include "Markov_IO/filemanager.h"
#include "Markov_IO/RandomPulses.h"

#include "Markov_LA/Matrix.h"

#include "Markov_Mol/QMarkovModel.h"
#include "Markov_Mol/GaussianNoise.h"
#include "Markov_Mol/MarkovSimulator.h"

#include "Markov_Bay/MacroDRStep.h"
#include "Markov_Bay/MacroRStep.h"
#include "Markov_Bay/MacroNRStep.h"
#include "Markov_Bay/MarkovLikelihood.h"
#include "Markov_Bay/MarkovOptim.h"
#include "Markov_LA/matrixRand.h"
#include "Markov_Console/Markov_CommandManager.h"
#include "Markov_Console/Markov_Console.h"


int Markov_ConsoleScreen_Demo1(int argc, char *argv[])
{
    system("copy \"empty.png\" \"temp.png\"");
    // Redirect cout to file
    std::ofstream f;
    f.open("output.txt");
    std::cout.rdbuf(f.rdbuf());
    // Open window
    QApplication a(argc,argv);
    MacroR sc;
    sc.show();
    a.exec();

    // close file
    f.close();

}
