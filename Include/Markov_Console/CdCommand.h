#ifndef CDCOMMAND_H
#define CDCOMMAND_H
#include "Markov_Console/ABC_Command.h"

namespace Markov_Console
{

  class CdCommandVar:public ABC_CommandVar
{
public:
    CdCommandVar(Markov_CommandManagerVar* cm);


    /// virtual destructor
    virtual ~CdCommandVar(){}



    // ABC_Value interface
  public:
    virtual bool processTokens(Markov_IO::Token_Stream &t);

  private:
    virtual bool run(const std::string& dirName);


  };









  class CdCommand:public ABC_Command
{
public:
    CdCommand(Markov_CommandManager* cm);

    /// virtual destructor
    virtual ~CdCommand();

        /// hint about of the class nature
    virtual std::string Tip()const;

    /// a short description of the class
    virtual std::string WhatThis()const;

    virtual std::string commandName()const;

    /// runs the command on the command manager and returns true if succeeds
    virtual bool run(std::deque<Token>& tokenList);

    /// runs the command for a list of parameters
    virtual bool run(const std::string& dirName);

};






}
#endif // CDCOMMAND_H
