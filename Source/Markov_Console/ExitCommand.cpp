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
bool ExitCommand::run(std::deque<Token> & )
{
  exit(0);
}

ExitCommandVar::ExitCommandVar(Markov_CommandManagerVar *cm):
    ABC_CommandVar(cm
                  ,"exit"
                  , ""
                  ,"exit the program"
                  ,""
                  ,0)
{}

bool ExitCommandVar::processTokens(Markov_IO::Token_Stream &t)
{
  delete cm_;
  exit(0);

}

bool ExitCommandVar::run(ABC_CommandVar *) const
{
  delete cm_;
  exit(0);
}


}
