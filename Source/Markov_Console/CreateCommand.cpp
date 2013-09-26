#include "Markov_Console/CreateCommand.h"
#include "Markov_Console/Help_File.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_Console/Markov_CommandManager.h"

#include <string>
namespace Markov_Console
{
///  destructor
CreateCommand::~CreateCommand(){}



CreateCommand::CreateCommand(Markov_CommandManager* cm)
{
    cm_=cm;
}


/// hint about of the class nature
std::string CreateCommand::Tip()const
{
    return "Displays help on subject";
}

/// a short description of the class
std::string CreateCommand::WhatThis()const
{
    return "Help command\n"
            " returns help on subject\n"
            " subject can be either a command";
}




std::string CreateCommand::commandName()const
{
    return "create";
}
/// runs the command on the command manager and returns true if succeeds
bool CreateCommand::run(std::deque<Token> & tokenList)
{
    std::string  typeName;
    std::string  variableName;

    if (tokenList.empty())
    {
        output_.clear();
        errorMessage_="missing parameter; expected variable type to be created";
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
        typeName=tokenList.front().Name();
        tokenList.pop_front();

        if (tokenList.empty())
        {
            variableName="my";
            variableName+=typeName;
            return run(typeName,variableName);
        }
        else if (tokenList[0].get_token()!=Token::IDENTIFIER)
        {
            output_.clear();
            errorMessage_="unexpected Token; expected Name, found other";
            return false;
        }
        else
        {

            variableName=tokenList.front().Name();
            std::string vna=variableName;
            tokenList.pop_front();
            bool ok=run(typeName,vna);
            return ok;
        }


    }
}


bool CreateCommand::run(const std::string &typeName, const std::string& varname)

{
    if (cm_->has_type(typeName))
    {
        Markov_IO::ABC_Saveable* v=cm_->getType(typeName)->create();
        cm_->add_var(varname,v);
        std::string runline="edit "+varname;
        return cm_->runLine(runline);
    }
    output_.clear();
    errorMessage_="unrecognized type";
    return false;
}
}



