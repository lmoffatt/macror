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



int main(int argc, char *argv[])
{
  if (argc>1)
    {
      Markov_Console::Markov_Console(std::string(argv[1]));
    return 0;
    }
  else
    {
      Markov_Console::Markov_Console();
    return 0;

    }
 }
