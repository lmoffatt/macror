#include "Markov_Console/ExitCommand.h"
#include "Markov_Console/Markov_CommandManager.h"
#include "Markov_IO/auxiliarIO.h"

namespace Markov_Console
{
///  destructor
ExitCommand::~ExitCommand(){}



ExitCommand::ExitCommand(Markov_CommandManager* cm)
    {
    cm_=cm;
}


/// hint about of the class nature
std::string ExitCommand::Tip()const
{
    return "Displays help on subject";
}

/// a short description of the class
std::string ExitCommand::WhatThis()const
{
    return "Help command\n"
            " returns help on subject\n"
            " subject can be either a command";
}




std::string ExitCommand::commandName()const
{
    return "exit";
}
/// runs the command on the command manager and returns true if succeeds
bool ExitCommand::run(std::deque<Token> & tokenList)
{
    exit(0);
}



}

