#include "Markov_Console/HelpCommand.h"
#include "Markov_Console/Help_File.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_Console/Markov_CommandManager.h"

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
    std::string helpath=cm_->getHelpDir()+"/"+helpFileName;
    helpFileContents=HelpFile(helpath);
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

  HelpCommandVar::HelpCommandVar(Markov_CommandManagerVar *cm):
    ABC_CommandVar(cm
                   ,ClassName()
                   ,"Displays help on subject"
                   ,""
                   ,"Help command\n"
                    " returns help on subject\n"
                    " subject can be either a command"
                   ,0)
  {
     pushChild(new Markov_IO::Implements_Simple_Value<std::string>(true,
                                                                   HelpSubjectName()
                                                                   ,HelpSubject::ClassName()
                                                                   ,"subject to be clarified"
                                                                   ,"an identifier for the subject"));
  }

  bool HelpCommandVar::run(std::string subject)const
  {
    std::string text;
    if (subject.empty())
      {
        return run();
     }
    else if (cm_->has_command(subject))
      {
        auto c=cm_->getCommand(subject);
         text=c->WhatThis();
      }
    else if (cm_->has_child(subject))
      {
        auto c=cm_->idToValue(subject);
        text=c->WhatThis();
      }
    cm_->putOut(text);
    return true;
  }
  
  bool HelpCommandVar::run() const
  {
    std::stringstream ss;
    const Markov_IO::Implements_Identifier_Class* i= cm_->getIdList(HelpSubject::ClassName());
    auto s=i->idSet();
    for (auto idstr:s)
      {
        auto o=cm_->idToValue(idstr);
        ss<<idstr<<"\t"<<o->myClass()<<"\t"<<o->myVar()<<"\n";
        ss<<o->Tip()<<"\n----\n";
        
      }
     cm_->putOut(ss.str());
     return true;
  }

  bool HelpCommandVar::run(ABC_CommandVar *var) const
  {
    std::string subject;
    var->getVal(HelpSubjectName(),subject);
    return run(subject);
  }

}
