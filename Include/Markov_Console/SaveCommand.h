#ifndef SAVECOMMAND_H
#define SAVECOMMAND_H
#include "Markov_Console/ABC_Command.h"
#include <vector>

namespace Markov_Console
{
class SaveCommand:public ABC_Command
{
public:
    SaveCommand(Markov_CommandManager* cm);

    /// virtual destructor
    virtual ~SaveCommand();

        /// hint about of the class nature
    virtual std::string Tip()const;

    /// a short description of the class
    virtual std::string WhatThis()const;

    virtual std::string commandName()const;

    /// runs the command on the command manager and returns true if succeeds
    virtual bool run(std::deque<Token>& tokenList);

    /// runs the command for a list of parameters
    virtual bool run(const std::string& helpFileName,
                     const std::vector<std::string>& varnames);

};


}
#endif // SAVECOMMAND_H
