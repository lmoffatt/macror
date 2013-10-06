#include "Markov_Console/Markov_console.h"
#include "Markov_Console/Markov_CommandManagerTest.h"

int main(int argc, char *argv[])
{
  if (argc>1)
    {
      Markov_Console::Markov_Console(new Markov_Console::Markov_CommandManagerTest(),std::string(argv[1]));
    return 0;
    }
  else
    {
      Markov_Console::Markov_Console(new Markov_Console::Markov_CommandManagerTest());
    return 0;

    }

}

