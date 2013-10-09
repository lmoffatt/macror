
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
class Markov_Console :public Markov_IO::ABC_IO
{
protected:
    Markov_CommandManager* cm;

public:
    Markov_Console(Markov_CommandManager* c,const std::string& fileCommandName="");
    virtual bool getline(std::string& s);

    virtual char getchar();

    /// put a string to the output source
    virtual void put(const std::string& s);


};

}
#endif // MARKOV_CONSOLE_H_INCLUDED



