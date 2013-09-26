#ifndef MARKOV_CONSOLETEST_H
#define MARKOV_CONSOLETEST_H

#include "Markov_Console/Markov_console.h"
#include "Markov_Console/Markov_CommandManagerTest.h"
namespace Markov_Console
{

/**
    @brief Display a console wich execute the commands entered
    in stdin

  */
class Markov_ConsoleTest
{
    Markov_CommandManagerTest cm;

public:
    Markov_ConsoleTest(const std::string& fileCommandName="");
};

}

#endif // MARKOV_CONSOLETEST_H
