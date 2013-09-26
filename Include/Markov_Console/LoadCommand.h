#ifndef LOADCOMMAND_H
#define LOADCOMMAND_H
#include "Markov_Console/ABC_Command.h"
#include <vector>

namespace Markov_Console
{
class LoadCommand:public ABC_Command
{
public:
    LoadCommand(Markov_CommandManager* cm);

    /// virtual destructor
    virtual ~LoadCommand();

        /// hint about of the class nature
    virtual std::string Tip()const;

    /// a short description of the class
    virtual std::string WhatThis()const;

    virtual std::string commandName()const;

    /// runs the command on the command manager and returns true if succeeds
    virtual bool run(std::deque<Token>& tokenList);

    /// runs the command for a list of parameters
    virtual bool run(const std::string& fname,
                     const std::vector<std::string>& varnames);

private:
    size_t MacroVersion_;

};


}



#endif // LOADCOMMAND_H
