#ifndef MODELCOMMAND_H
#define MODELCOMMAND_H
#include "Markov_Console/ABC_Command.h"
#include <vector>
#include "Markov_IO/ClassDescription.h"

namespace Markov_Console
{
class ModelCommand:public ABC_Command
{
public:
    ModelCommand(Markov_CommandManager* cm);

    /// virtual destructor
    virtual ~ModelCommand();

        /// hint about of the class nature
    virtual std::string Tip()const;

    /// a short description of the class
    virtual std::string WhatThis()const;

    virtual std::string commandName()const;

    /// runs the command on the command manager and returns true if succeeds
    virtual bool run(std::deque<Token>& tokenList);

    /// runs the command for a list of parameters
    virtual bool run(const std::string &typeName,const std::string &varname);


};


}




#endif // MODELCOMMAND_H
