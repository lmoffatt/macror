
#ifndef MARKOV_CONSOLE_H_INCLUDED
#define MARKOV_CONSOLE_H_INCLUDED

#include "Markov_CommandManager.h"
#include <iostream>
#include <string>


namespace Markov_Console
{

/**
    @brief Display a console wich execute the commands entered
    in stdin

  */
class Markov_Console
{
protected:
    Markov_CommandManager* cm;

public:
    Markov_Console(Markov_CommandManager* c,const std::string& fileCommandName="");
};

}
#endif // MARKOV_CONSOLE_H_INCLUDED



