#include <sys/stat.h>

#include "Markov_Console/ExportCommand.h"
#include "Markov_Console/Help_File.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_Console/Markov_CommandManager.h"
#include "Markov_Console/MkdirCommand.h"
namespace Markov_Console
{
  ///  destructor
  ExportCommand::~ExportCommand(){}



  ExportCommand::ExportCommand(Markov_CommandManager* cm)
  {
    cm_=cm;
  }


  /// hint about of the class nature
  std::string ExportCommand::Tip()const
  {
    return "Displays help on subject";
  }

  /// a short description of the class
  std::string ExportCommand::WhatThis()const
  {
    return "Help command\n"
        " returns help on subject\n"
        " subject can be either a command";
  }




  std::string ExportCommand::commandName()const
  {
    return "export";
  }
  /// runs the command on the command manager and returns true if succeeds
  bool ExportCommand::run(std::deque<Token> & tokenList)
  {
    std::string dirName;
    std::vector<std::string> varnames;

    if (tokenList.empty())
      {
        dirName="";
      }
    else if (tokenList[0].get_token()==Token::STRING)
      {
        dirName=tokenList.front().Path();
        tokenList.pop_front();

      }
    else if(tokenList[0].get_token()==Token::IDENTIFIER)

      {
        dirName=tokenList.front().Name();
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
        return run(dirName,varnames);
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
    return run(dirName,varnames);

  }
  /// runs the command for a list of parameters
  bool ExportCommand::run(
      const std::string& dirname,
      const std::vector<std::string>& varnames)
  {

    errorMessage_.clear();
    output_.clear();
    if (!Markov_IO::IsDir(dirname))
      {
        MkdirCommand mk(cm_);
        if (!mk.run(dirname))
          {
            errorMessage_=mk.errorMessage();
            return false;

          }
      }
    if (varnames.empty())
      {

        std::vector<std::string> varNamesDeque=cm_->getVarsList();
        for (std::size_t i=0;i<varNamesDeque.size(); ++i)
          {
            std::string path=dirname+"/"+varNamesDeque[i]+".txt";
            std::ofstream f(path.c_str());

            f<<varNamesDeque[i]<<std::endl;
            f<<cm_->getVar(varNamesDeque[i])->GetDescription();
            f.close();

          }
        output_=Markov_IO::ToString(varNamesDeque.size())+" variables saved in directory"+dirname;
        return true;

      }
    else
      {
        for (std::size_t i=0; i<varnames.size(); i++)
          {
            if (cm_->has_var(varnames[i]))
              {
                std::string path=dirname+"/"+varnames[i]+".txt";
                std::ofstream f(path.c_str());


                f<<varnames[i]<<std::endl;
                f<<cm_->getVar(varnames[i])->GetDescription();
                f.close();
              }
            else
              {
                errorMessage_=varnames[i]+" not found";
                return false;
              }

          }
        output_=Markov_IO::ToString(varnames.size())+" variables saved in directory "+dirname;
        return true;

      }
  }

}

