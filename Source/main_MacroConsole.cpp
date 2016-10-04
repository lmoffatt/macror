#include "Markov_Mol/QMarkovModel.h"
#include "Markov_Mol/GaussianNoise.h"

#include "Markov_LA/matrixRand.h"
#include "Markov_Console/Markov_CommandManager.h"
#include "Markov_Console/Markov_console.h"



int main(int argc, char *argv[])
{
  Markov_Console_New::Markov_Console co(new Markov_IO_New::Markov_CommandManagerVar());
  if (argc>1)
    {
     std::string line;
     std::size_t i=1;
     while (argc>i)
       {line+=argv[i];line+=" ";++i;}
     co.exec(line);
    return 0;
    }
  else
    {
      co.exec();
      return 0;

    }
 }
