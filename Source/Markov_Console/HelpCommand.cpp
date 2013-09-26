#include "Markov_Console/HelpCommand.h"
#include "Markov_Console/Help_File.h"
#include "Markov_IO/auxiliarIO.h"

namespace Markov_Console
{
///  destructor
HelpCommand::~HelpCommand(){}



HelpCommand::HelpCommand(Markov_CommandManager* cm)
    {
    cm_=cm;
}


/// hint about of the class nature
std::string HelpCommand::Tip()const
{
    return "Displays help on subject";
}

/// a short description of the class
std::string HelpCommand::WhatThis()const
{
    return "Help command\n"
            " returns help on subject\n"
            " subject can be either a command";
}




std::string HelpCommand::commandName()const
{
    return "help";
}
/// runs the command on the command manager and returns true if succeeds
bool HelpCommand::run(std::deque<Token> & tokenList)
{
    std::string helpFileName;
    if (tokenList.empty())
    {
        helpFileName="help.txt";
    }
    else if (tokenList[0].get_token()!=Token::IDENTIFIER)
    {
        output_.clear();
        errorMessage_="unexpected Token; expected Name, found other";
        return false;
    }
    else
    {
        std::string commandHelped=tokenList[0].Name();
        if (tokenList.size()==1)
        {
            helpFileName=commandHelped+".txt";
        }
        else if (tokenList.size()==2)
        {
            if (tokenList[1].get_token()!=Token::IDENTIFIER)
            {
                output_.clear();
                errorMessage_="unexpected Token; expected Name, found other";
                return false;
            }
            else
            {
                std::string options=tokenList[1].Name();
                helpFileName=commandHelped+"_"+options+".txt";
            }
        }
        else
        {
            output_.clear();
            errorMessage_="too many parameters; expected 0-2, found "+
                    Markov_IO::ToString(tokenList.size());

            return false;
        }
    }

    return run(helpFileName);
}
/// runs the command for a list of parameters
 bool HelpCommand::run(const std::string& helpFileName)
{
        std::string helpFileContents;
        helpFileContents=HelpFile(helpFileName);
        if (helpFileContents.empty())
        {
            output_.clear();
            errorMessage_="file "+helpFileName+ " not found";
            return false;

        }
        else
        {
            output_=helpFileContents;
            errorMessage_.clear();
            return true;
        }


}

}
