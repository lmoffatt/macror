#ifndef EXITCOMMAND_H
#define EXITCOMMAND_H

#include "Markov_Console/ABC_Command.h"

namespace Markov_Console
{
class ExitCommand:public ABC_Command
{
public:
    ExitCommand(Markov_CommandManager* cm);

    /// virtual destructor
    virtual ~ExitCommand();

        /// hint about of the class nature
    virtual std::string Tip()const;

    /// a short description of the class
    virtual std::string WhatThis()const;

    virtual std::string commandName()const;

    /// runs the command on the command manager and returns true if succeeds
    virtual bool run(std::deque<Token>& tokenList);


};


}


#endif // EXITCOMMAND_H
