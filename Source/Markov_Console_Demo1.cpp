#include <fstream>

//#include "Markov_IO/filemanager.h"
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
#include "Markov_Console/Markov_console.h"



//using namespace std;

int Markov_Console_Demo1(int argc, char *argv[])
{
  Markov_Console::Markov_Console();
    return 0;
}
