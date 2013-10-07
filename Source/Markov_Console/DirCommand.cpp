#include "Markov_Console/DirCommand.h"
#include "Markov_Console/Markov_CommandManager.h"
#include "Markov_IO/auxiliarIO.h"

namespace Markov_Console
{
  ///  destructor
  DirCommand::~DirCommand(){}



  DirCommand::DirCommand(Markov_CommandManager* cm)
  {
    cm_=cm;
  }


  /// hint about of the class nature
  std::string DirCommand::Tip()const
  {
    return "Displays help on subject";
  }

  /// a short description of the class
  std::string DirCommand::WhatThis()const
  {
    return "Help command\n"
        " returns help on subject\n"
        " subject can be either a command";
  }




  std::string DirCommand::commandName()const
  {
    return "dir";
  }
  /// runs the command on the command manager and returns true if succeeds
  bool DirCommand::run(std::deque<Token> & tokenList)
  {
    std::string dirName;
    if (tokenList.empty())
      {
        return run(dirName);
      }
    else switch(tokenList.front().get_token())
      {
      case Token::IDENTIFIER:
        dirName=tokenList.front().Name();
        tokenList.pop_front();
        return run(dirName);
        break;
      case Token::STRING:
        dirName=tokenList.front().Path();
        tokenList.pop_front();
        return run(dirName);
        break;
      default:
        output_.clear();
        errorMessage_="unexpected Token; expected NAME or PATH, found "+
            tokenList.front().get_tokenString();
        return false;
      }
  }


  /// runs the command for a list of parameters
  bool DirCommand::run(const std::string& dirName)
  {
    std::stringstream ss;
    if (dirName.empty())
      {
        Markov_IO::FileDir d(getCommandManager()->getDir());
        d.begin();
        while(d.next())
          {
            ss<<d.FileName()<<"\t";
          }

        output_=ss.str();
        errorMessage_.clear();
        return true;
      }
    else
      {
        Markov_IO::FileDir tempDir(cm_->getDir());
        if (!tempDir.cd(dirName))
          {
            output_.clear();
            errorMessage_=dirName+" is not a directory";
            return false;
          }
        else
          {
            tempDir.begin();
            while(tempDir.next())
              {
                ss<<tempDir.FileName()<<"\t";
              }

            output_=ss.str();
            errorMessage_.clear();
            return true;
          }
      }

  }

}
