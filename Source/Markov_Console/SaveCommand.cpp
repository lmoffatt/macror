#include "Markov_Console/SaveCommand.h"
#include "Markov_Console/Help_File.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_Console/Markov_CommandManager.h"


#include "Markov_IO/Object.h"
namespace Markov_Console
{
///  destructor
SaveCommand::~SaveCommand(){}



SaveCommand::SaveCommand(Markov_CommandManager* cm):
  ABC_Command(cm,
              "save",{{
              "fileName",Markov_IO::Object<std::string>::ClassName(),false},{
              "varname",ABC_Command::varName(),false}},{}){}


/// hint about of the class nature
std::string SaveCommand::Tip()const
{
    return "Displays help on subject";
}

/// a short description of the class
std::string SaveCommand::WhatThis()const
{
    return "Help command\n"
            " returns help on subject\n"
            " subject can be either a command";
}




std::string SaveCommand::commandName()const
{
    return "save";
}
/// runs the command on the command manager and returns true if succeeds
bool SaveCommand::run(std::deque<Token> & tokenList)
{
    std::string saveFileName;
    std::vector<std::string> varnames;
    if (tokenList.empty())
    {
        saveFileName="macror.txt";
    }
    else if (tokenList[0].get_token()==Token::STRING)
    {
        saveFileName=tokenList.front().Path();
        tokenList.pop_front();

    }
    else if(tokenList[0].get_token()==Token::IDENTIFIER)

    {
        saveFileName=tokenList.front().Name();
        tokenList.pop_front();

    }
        else
    {
        output_.clear();
        errorMessage_="unexpected Token; expected Name, found other";
        return false;
    }
    if (tokenList.empty())
    {
        return run(saveFileName,varnames);
    }
    else while (!tokenList.empty())
    {
        switch(tokenList.front().get_token())
        {
        case Token::IDENTIFIER:
            varnames.push_back(tokenList.front().Name());
            tokenList.pop_front();
            break;
        default:
            std::string tokenString=tokenList.front().get_tokenString();
            output_.clear();
            errorMessage_="wrong token; expected NAME or NUMBER one number, found : "+
                    tokenString;
            return false;
        }
    }
    return run(saveFileName,varnames);

}
/// runs the command for a list of parameters
bool SaveCommand::run(
         const std::string& filename,
         const std::vector<std::string>& varnames)
 {
  std::string path=filename;

  if (filename.find(".")==filename.npos)
      path=filename+".txt";

     std::ofstream ftest(path.c_str());


    if (!ftest)
    {
        path=cm_->getDir()+Markov_IO::FileDir::slash()+filename;
    }


    std::ofstream f(path.c_str());
     if(!f)
     {
         output_.clear();
         errorMessage_="invalid name "+path;
         return false;
     }
     if (varnames.empty())
     {
         f<<getCommandManager()->version()<<std::endl;
         std::size_t i=0;
         auto variablenames=cm_->getChildList();
         for (auto name : variablenames)
         {
             f<<cm_->getChild(name)->toString();
             i++;
         }
         f.close();
         output_=Markov_IO::ToString(i)+"  variables saved in file "+path;
         errorMessage_.clear();
         return true;

     }
     else
     {
         for (std::size_t i=0; i<varnames.size(); i++)
         {
             if (!cm_->has_var(varnames[i]))
             {
                output_.clear();
                errorMessage_="variable "+varnames[i]+" not found; no variable saved";
                return false;
             }
         }
         f<<getCommandManager()->version()<<std::endl;
         for (auto name: varnames)
         {
                f<<name<<std::endl;
                f<<cm_->getVar(name)->GetDescription();
          }
          f.close();
          output_=Markov_IO::ToString(varnames.size())+"  variables saved in file "+path;
          errorMessage_.clear();
          return true;
     }
 }

}
