#ifndef SIMULATECOMMAND_H
#define SIMULATECOMMAND_H
#include <Markov_Console/ABC_Command.h>


namespace Markov_Console
{
class SimulateCommand:public ABC_Command
{
public:
    /// virtual destructor
    virtual ~SimulateCommand();

    SimulateCommand(Markov_CommandManager* cm);

        /// hint about of the class nature
    virtual std::string Tip()const;

    /// a short description of the class
    virtual std::string WhatThis()const;

    virtual std::string commandName()const;

    /// runs the command on the command manager and returns true if succeeds
    virtual bool run(std::deque<Token>& tokenList);

    virtual bool run(const std::string& patch_in,
                     const std::string& experiment_in,
                     const std::string& experiment_out,
                     std::size_t num_replicates,
                     const std::string& options_in);

private:


};


}

#endif // SIMULATECOMMAND_H
