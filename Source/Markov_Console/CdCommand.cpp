#include "Markov_Console/CdCommand.h"
#include "Markov_Console/Markov_CommandManager.h"
#include "Markov_IO/auxiliarIO.h"


namespace Markov_Console
{
  ///  destructor
  CdCommand::~CdCommand(){}



  CdCommand::CdCommand(Markov_CommandManager* cm)
    :ABC_Command(cm,
                 "cd",{{
                 "dir",ABC_Command::directory(),false}},{})
  {
  }


  /// hint about of the class nature
  std::string CdCommand::Tip()const
  {
    return "Displays help on subject";
  }

  /// a short description of the class
  std::string CdCommand::WhatThis()const
  {
    return "Help command\n"
           " returns help on subject\n"
           " subject can be either a command";
  }

  std::string CdCommand::commandName()const
  {
    return "cd";
  }
  /// runs the command on the command manager and returns true if succeeds
  bool CdCommand::run(std::deque<Token> & tokenList)
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

      case Token::PATH:
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
  bool CdCommand::run(const std::string& dirName)
  {
    Markov_IO::FileDir d(getCommandManager()->getDir());

    if (dirName.empty())
      {
        output_=d.DirName();
        errorMessage_.clear();
        return true;
      }
    else  if (!d.cd(dirName))
      {
        output_.clear();
        errorMessage_=dirName+" is not a directory";
        return false;
      }
    else
      {
        getCommandManager()->setDir(d.DirName());
        output_=d.DirName();
        errorMessage_.clear();
        return true;
      }

  }

  CdCommandVar::CdCommandVar(Markov_CommandManagerVar *cm)
    : Markov_IO::Implements_ValueId("cd"
                                    , ""
                                    ,"display or change directory"
                                    ,""
                                    )
    ,ABC_CommandVar(cm
                    ,"cd"
                    , ""
                    ,"display or change directory"
                    ,""
                    ,{}
                    ,{{"","","",""}})
  {}

  bool CdCommandVar::processTokens(Markov_IO::Token_Stream &t)
  {
    if ((t.currToken().tok()==Markov_IO::Token_New::IDENTIFIER)
        &&(t.currToken().str()==id()))
        ++t;
        else
      return false;

    std::string dirName;
    if (t.currToken().tok()==Markov_IO::Token_New::EOL)
      {
        return run(dirName);
      }
    else switch(t.currToken().tok())
      {
      case Markov_IO::Token_New::IDENTIFIER:
      case Markov_IO::Token_New::STRING:
        dirName=t.currToken().str();
        t.advance(1);
        return run(dirName);
        break;
      default:
        std::string errorMessage="unexpected Token; expected NAME or PATH, found "
            +t.currToken().str();
        cm_->putErrorOut(errorMessage);
        return false;
        break;
      }
  }

  bool CdCommandVar::run(const std::string &dirName)

  {
    Markov_IO::FileDir d(cm_->getDir());

    if (dirName.empty())
      {
        cm_->putOut(d.DirName());
        return true;
      }
    else  if (!d.cd(dirName))
      {
        std::string errorMessage=dirName+" is not a directory";
        cm_->putErrorOut(errorMessage);
        return false;
      }
    else
      {
        cm_->setDir(d.DirName());
        cm_->putOut(d.DirName());
        return true;
      }

  }


}


