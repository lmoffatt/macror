#ifndef CLEARCOMMAND_H
#define CLEARCOMMAND_H
#include "Markov_Console/ABC_Command.h"
#include <vector>

namespace Markov_Console
{

  class ClearCommandVar: public ABC_CommandVar
  {
  public:
      ClearCommandVar(Markov_CommandManagerVar* cm);

      /// virtual destructor
      virtual ~ClearCommandVar(){}



     virtual bool processTokens(Markov_IO::Token_Stream &t);


    private:
      virtual bool run(const std::vector<std::string>& varnames);



      // ABC_CommandVar interface
  public:
      virtual bool run(ABC_CommandVar *) const override
      {
      }
      virtual ClearCommandVar* clone() const
      {
        return new ClearCommandVar(*this);
      }
  };



class ClearCommand:public ABC_Command
{
public:
    ClearCommand(Markov_CommandManager* cm);

    /// virtual destructor
    virtual ~ClearCommand();


    virtual std::string commandName()const;

    /// runs the command on the command manager and returns true if succeeds
    virtual bool run(std::deque<Token>& tokenList);

    /// runs the command for a list of parameters
    virtual bool run(const std::vector<std::string>& varnames);

};


}


#endif // CLEARCOMMAND_H
