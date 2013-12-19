#include "Markov_Console/ModelCommand.h"
#include "Markov_Console/Help_File.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_Console/Markov_CommandManager.h"
#include "Markov_Mol/QMarkovModel.h"
#include "Markov_Mol/PatchModel.h"
namespace Markov_Console
{
///  destructor
ModelCommand::~ModelCommand(){}



ModelCommand::ModelCommand(Markov_CommandManager* cm)
{
    cm_=cm;
}


/// hint about of the class nature
std::string ModelCommand::Tip()const
{
    return "Displays help on subject";
}

/// a short description of the class
std::string ModelCommand::WhatThis()const
{
    return "Help command\n"
            " returns help on subject\n"
            " subject can be either a command";
}




std::string ModelCommand::commandName()const
{
    return "model";
}
/// runs the command on the command manager and returns true if succeeds
bool ModelCommand::run(std::deque<Token> & tokenList)
{
    std::string  typeName;
    std::string  varName;
    if (tokenList.empty())
    {
        output_.clear();
        errorMessage_="missing parameter; expected model channel or model patch";
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
            varName="my";
            varName+=typeName;
            return run(typeName,varName);
        }
        else if (tokenList[0].get_token()!=Token::IDENTIFIER)
        {
            output_.clear();
            errorMessage_="unexpected Token; expected Name, found other";
            return false;
        }
        else
        {
            varName=tokenList.front().Name();
            tokenList.pop_front();
            return run(typeName,varName);

        }


    }
}


bool ModelCommand::run(const std::string &typeName, const std::string& varname)

{
    if (typeName=="channel")
    {
        std::string typestring=Markov_Mol::Q_Markov_Model::ClassName();
        std::string runline="create "+typestring +" "+varname;
        return cm_->runLine(runline);
    }
    else if (typeName=="patch")
    {
        std::string typestring=Markov_Mol::PatchModel::ClassName();
        std::string runline="create "+typestring +" "+varname;
        return cm_->runLine(runline);

    }
    else{
        output_.clear();
        errorMessage_="unrecognized type";
        return false;
    }
}
}

