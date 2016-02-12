#ifndef AVERAGE_COMMAND_H
#define AVERAGE_COMMAND_H
#include <Markov_Console/ABC_Command.h>

namespace Markov_Console
{

  class AverageCommandVar:public ABC_CommandVar
{
public:
    AverageCommandVar(Markov_CommandManagerVar* cm);


    /// virtual destructor
    virtual ~AverageCommandVar(){}

    // ABC_Value interface
  public:
    virtual bool processTokens(Markov_IO::Token_Stream &t);

  private:

    void run(const std::string &experiment_in, const std::string &experiment_out, const std::string &options_in);

    // ABC_CommandVar interface
  public:
    virtual bool run(ABC_CommandVar *) const override
    {
    }

  };





class AverageCommand:public ABC_Command
{
public:
    /// virtual destructor
    virtual ~AverageCommand();

    AverageCommand(Markov_CommandManager* cm);

        /// hint about of the class nature
    virtual std::string Tip()const;

    /// a short description of the class
    virtual std::string WhatThis()const;

    virtual std::string commandName()const;

    /// runs the command on the command manager and returns true if succeeds
    virtual bool run(std::deque<Token>& tokenList);

    virtual bool run(const std::string& experiment_in,
                     const std::string& experiment_out,
                     const std::string& options_in);

private:


};


}



#endif // AVERAGE_COMMAND_H
