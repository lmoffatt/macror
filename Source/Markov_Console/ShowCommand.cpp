#include "Markov_Console/ShowCommand.h"
#include "Markov_Console/Help_File.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_Console/Markov_CommandManager.h"
namespace Markov_Console
{
///  destructor
ShowCommand::~ShowCommand(){}



ShowCommand::ShowCommand(Markov_CommandManager* cm)
{
    cm_=cm;
}


/// hint about of the class nature
std::string ShowCommand::Tip()const
{
    return "Displays help on subject";
}

/// a short description of the class
std::string ShowCommand::WhatThis()const
{
    return "Help command\n"
            " returns help on subject\n"
            " subject can be either a command";
}




std::string ShowCommand::commandName()const
{
    return "show";
}
/// runs the command on the command manager and returns true if succeeds
bool ShowCommand::run(std::deque<Token> & tokenList)
{
    std::string  varname;
    if (tokenList.empty())
    {
        output_.clear();
        errorMessage_="missing parameter; expected variable to be shown";
        return false;
    }
    else if (tokenList[0].get_token()!=Token::IDENTIFIER)
    {
        output_.clear();
        errorMessage_="unexpected Token; expected Name, found other";
        return false;
    }
    else
    {
        varname=tokenList.front().Name();
        tokenList.pop_front();

    }
    return run(varname);

}


bool ShowCommand::run(const std::string& varname)

{
    errorMessage_.clear();
    output_.clear();
    if (cm_->has_var(varname))
    {
        std::stringstream ss;
        ss<< *cm_->getVar(varname);
        output_=ss.str();
        return true;

    }
    else
    {
        errorMessage_= "Variable does not exist";
        return false;

    }
}


}


