#include "Markov_Console/Markov_consoleTest.h"

int main(int argc, char *argv[])
{
  if (argc>1)
    {
      Markov_Console::Markov_ConsoleTest(std::string(argv[1]));
    return 0;
    }
  else
    {
      Markov_Console::Markov_ConsoleTest();
    return 0;

    }
 //  leandroDemo_1(argc,argv);
 //  lucianoTest_1(argc,argv);
  // lucianoTest_2(argc,argv);

}

