#ifndef WHOCOMMAND_H
#define WHOCOMMAND_H
#include "Markov_Console/ABC_Command.h"

namespace Markov_Console
{

  class WhoCommandVar:public ABC_CommandVar
  {
  public:
    WhoCommandVar(Markov_CommandManagerVar* cm);

    /// virtual destructor
    virtual ~WhoCommandVar(){}


    static std::string ClassName(){return "who";}

  private:
    bool run() const;



    // ABC_CommandVar interface
  public:
    virtual bool run(ABC_CommandVar * ) const override;
    virtual WhoCommandVar* clone()const
    {
      return new WhoCommandVar(*this);
    }
  };

  class WhoCommand:public ABC_Command
  {
  public:
    WhoCommand(Markov_CommandManager* cm);

    /// virtual destructor
    virtual ~WhoCommand();

    /// hint about of the class nature
    virtual std::string Tip()const;

    /// a short description of the class
    virtual std::string WhatThis()const;

    virtual std::string commandName()const;

    /// runs the command on the command manager and returns true if succeeds
    virtual bool run(std::deque<Token>& tokenList);

    /// runs the command for a list of parameters
    virtual bool run(const std::string& className);

  };


}



#endif // WHOCOMMAND_H
