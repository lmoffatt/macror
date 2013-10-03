#ifndef ABC_COMMAND_H
#define ABC_COMMAND_H

#include <deque>
#include <vector>
#include <string>

#include <Markov_Console/Token.h>



namespace Markov_Console
{
  class Markov_CommandManager;

  class ABC_Command
  {
  public:
    virtual ~ABC_Command();
    /// virtual formated output
    virtual std::ostream& put(std::ostream& s) const;


    virtual bool operator==(const ABC_Command& other)const;

    /// hint about of the class nature
    virtual std::string Tip()const;

    /// a short description of the class
    virtual std::string WhatThis()const;

    /// checks if commandName ref   ers to the actual command
    virtual bool IsCommand(const std::string& ACommandName)const;


    virtual std::string commandName()const=0;


    /// runs the command for a vector of Tokens
    virtual bool run(std::deque<Token>& tokensList)=0;



    virtual std::vector<std::string> complete(const std::string& hint,const std::deque<Token>& token)const{}


    /// error message, empty string if succeeded
    virtual std::string errorMessage()const;

    /// printed output, empty string if command fails
    virtual std::string output()const;

    /// returns the Markov_CommandManager
    virtual Markov_CommandManager* getCommandManager();

  protected:
    std::string output_;
    std::string errorMessage_;
    Markov_CommandManager* cm_;
  };

}


#endif // ABC_COMMAND_H
