#ifndef OPTIMIZECOMMAND_H
#define OPTIMIZECOMMAND_H
#include "Markov_IO/ABC_IO.h"
#include "Markov_Console/ABC_Command.h"

namespace Markov_Console
{
class OptimizeCommand:public ABC_Command
{
public:
    /// virtual destructor
    virtual ~OptimizeCommand();

    OptimizeCommand(Markov_CommandManager* cm);

        /// hint about of the class nature
    virtual std::string Tip()const;

    /// a short description of the class
    virtual std::string WhatThis()const;

    virtual std::string commandName()const;

    /// runs the command on the command manager and returns true if succeeds
    virtual bool run(std::deque<Token>& tokenList);

    virtual bool run(const std::string& parameters_in,
                     const std::string& patch_in,
                     const std::string& experiment_in,
                     const std::string& options_in,
                     const std::string& results_out,
                     bool zeroIter,
                     double randomRadius,
                     std::size_t numStarts);


};


}

#endif // OPTIMIZECOMMAND_H
