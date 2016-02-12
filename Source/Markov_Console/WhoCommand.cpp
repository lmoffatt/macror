#include "Markov_Console/WhoCommand.h"
#include "Markov_Console/Markov_CommandManager.h"
#include "Markov_IO/auxiliarIO.h"

namespace Markov_Console
{
///  destructor
WhoCommand::~WhoCommand(){}



WhoCommand::WhoCommand(Markov_CommandManager* cm)
  :ABC_Command(cm,
               "who",{{
               "variable",ABC_Command::varName(),false}},{}){}

/// hint about of the class nature
std::string WhoCommand::Tip()const
{
    return "Displays help on subject";
}

/// a short description of the class
std::string WhoCommand::WhatThis()const
{
    return "Help command\n"
            " returns help on subject\n"
            " subject can be either a command";
}




std::string WhoCommand::commandName()const
{
    return "who";
}
/// runs the command on the command manager and returns true if succeeds
bool WhoCommand::run(std::deque<Token> & tokenList)
{
    std::string className;
    if (tokenList.empty())
    {
        return run(className);
    }
    else switch(tokenList.front().get_token())
    {
    case Token::IDENTIFIER:
        className=tokenList.front().Name();
        tokenList.pop_front();
        return run(className);
        break;
    default:
        output_.clear();
        errorMessage_="unexpected Token; expected NAME or PATH, found "+
                tokenList.front().get_tokenString();
        return false;
    }
}


/// runs the command for a list of parameters
bool WhoCommand::run(const std::string& className)
{
    output_.clear();
    std::vector<std::string> list;
    if (className.empty())
        list=cm_->getChildList();
    else  if (cm_->has_child(className))
    {
        list.push_back(className);
    }
    else
    {
        list=cm_->getVarsList(className);
    }
    std::string ret;
    std::size_t widthName=0;
    std::size_t widthClass=0;
    for (std::size_t i=0;i<list.size();++i)
    {
        auto wN=list[i].size();
        auto wC=cm_->idToValue(list[i])->myVar().size();
        if (wN>widthName)
            widthName=wN;

        if (wC>widthClass)
            widthClass=wC;
    }
    for (std::size_t i=0;i<list.size();++i)
    {
        ret.append(list[i]);
        std::size_t n=widthName-list[i].size()+3;
        ret.append(n,' ');
        ret.append(cm_->idToValue(list[i])->myVar());
        n=widthClass-cm_->idToValue(list[i])->myVar().size()+3;
        ret.append(n,' ');
        ret += "\n";
    }
    output_=ret;
    return true;
}

WhoCommandVar::WhoCommandVar(Markov_CommandManagerVar *cm):
ABC_CommandVar(cm
               ,ClassName()
               , ""
               ,"working variables"
               ,"who command\n"
                " returns list of working variables"
               ,0)
{}
bool WhoCommandVar::run() const
{
  auto list=cm_->getChildList();
  for (auto& s:list)
  cm_->putOut(s+"\t");
  return true;

}

bool WhoCommandVar::run(ABC_CommandVar *) const
{
  return run();
}

}

