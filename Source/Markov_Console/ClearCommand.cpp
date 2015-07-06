#include "Markov_Console/ClearCommand.h"
#include "Markov_Console/Help_File.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_Console/Markov_CommandManager.h"
namespace Markov_Console
{
  ///  destructor
  ClearCommand::~ClearCommand(){}




  ClearCommand::ClearCommand(Markov_CommandManager* cm)
    :ABC_Command(cm,
                 "clear",{{
                 "variables",ABC_Command::varName(),true}},{}){}




  std::string ClearCommand::commandName()const
  {
    return "clear";
  }
  /// runs the command on the command manager and returns true if succeeds
  bool ClearCommand::run(std::deque<Token> & tokenList)
  {
    std::vector<std::string> varnames;
    while(!tokenList.empty())
      {
        if (tokenList[0].get_token()!=Token::IDENTIFIER)
          {
            output_.clear();
            errorMessage_="unexpected Token; expected Name, found other";
            return false;
          }
        else
          {
            varnames.push_back(tokenList.front().Name());
            tokenList.pop_front();
          }
      } ;
    return run(varnames);

  }


  //TODO add the possibility of clear mod*

  /// runs the command for a list of parameters
  bool ClearCommand::run(const std::vector<std::string>& varnames)
  {
    output_.clear();
    if (varnames.empty())
      {
        errorMessage_="missing parameter";
        return true;

      }
    else
      {
        for (std::size_t i=0; i< varnames.size();i++)
          {

            if (cm_->has_var(varnames[i])|| varnames[i]=="all")
              {
                cm_->delete_var(varnames[i]);
              }
            else
              {
                output_.clear();
                errorMessage_=varnames[i]+" unrecognized name ";
                return false;

              }
          }
        return true;
      }
  }

  ClearCommandVar::ClearCommandVar(Markov_CommandManagerVar *cm)
      : Markov_IO::Implements_ValueId("clear"
                                      , ""
                                      ,"erases variables"
                                      ,""
                                      )
      ,ABC_CommandVar(cm
                      ,"clear"
                      , ""
                      ,"erases variables"
                      ,""
                      ,{}
                      ,{{"","","",""}})
    {}

  bool ClearCommandVar::processTokens(Markov_IO::Token_Stream &t)

  {
    if ((t.currToken().tok()==Markov_IO::Token_New::IDENTIFIER)
        &&(t.currToken().str()==id()))
        ++t;
        else
      return false;
    std::vector<std::string> varnames;
    while((!t.empty()||t.currToken().tok()!=Markov_IO::Token_New::EOL))
      {
        if (t.currToken().tok()!=Markov_IO::Token_New::IDENTIFIER)
          {
            std::string errorMessage="unexpected Token; expected Name, found other";
            cm_->putErrorOut(errorMessage);
            return false;
          }
        else
          {
            varnames.push_back(t.currToken().str());
            ++t;
          }
      }
    return run(varnames);

  }


  bool ClearCommandVar::run(const std::vector<std::string> &varnames)

  {
    if (varnames.empty())
      {
        std::string errorMessage_="missing parameter";
        cm_->putErrorOut(errorMessage_);
        return false;

      }
    else
      {
        for (std::size_t i=0; i< varnames.size();i++)
          {

            if (cm_->has_var(varnames[i]))
              {
                cm_->removeChild(varnames[i]);
              }
            else
              {
                auto errorMessage_=varnames[i]+" unrecognized name ";
                cm_->putErrorOut(errorMessage_);
                return false;

              }
          }
        return true;
      }
  }



}
