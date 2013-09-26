#ifndef MARKOV_SCRIPT_H
#define MARKOV_SCRIPT_H

#include <iostream>
#include <fstream>
#include <string>
#include "Markov_CommandManager.h"

namespace Markov_Console
{

class Markov_CommandManager;

/**
    @brief Display a console wich execute the commands entered
    in stdin

    @todo To run a script direct from the executable the main function
    will have to take account of args and argc chars.

  */
class Markov_Script
{
public:
    Markov_Script(Markov_CommandManager &cm, const std::string& file);
};

}

#endif // MARKOV_SCRIPT_H
