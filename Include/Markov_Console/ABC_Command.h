#ifndef ABC_COMMAND_H
#define ABC_COMMAND_H

#include <deque>
#include <vector>
#include <string>
#include <tuple>

#include <Markov_Console/Token.h>

#include "Markov_IO/ABC_Var.h"


namespace Markov_Console
{
  class Markov_CommandManager;
  class Markov_CommandManagerVar;

  // TODO: root ABC_Command in the hierarchy
  class ABC_CommandVar : public Markov_IO::Implements_Complex_Value
  {
  public:
     ~ABC_CommandVar();
    /// virtual formated output



    // TODO: constructor based on vector of tuples

    ABC_CommandVar(Markov_CommandManagerVar* cm,
                   const std::string& commandName,
                   const std::string &commandClass,
                   const std::string &tip,
                   const std::string &whatthis,
                   std::vector<Implements_ValueId> Inputs,
                   std::size_t numMandatory);


    ABC_CommandVar(){}


  protected:
     Markov_IO::ABC_Var *toSameVar(const Markov_IO::ABC_Value *) const
    {
      return nullptr;
    }
     Markov_IO::ABC_Measure *toMeasure(const Markov_IO::ABC_Value *) const
    {
      return nullptr;
    }

  public:
    static std::string ClassName()
    {
      return "ABC_Command";
    }

     std::string myClass() const
    {
      return ClassName();
    }

     std::set<std::string> mySuperClasses() const
    {
      return {ClassName()};
    }


    std::size_t numMandatoryInputs()const
    {
      return numMandatoryFields_;
    }






    // ABC_Value interface
  public:
    /// returns the Markov_CommandManager
     Markov_CommandManagerVar* getCommandManager(){return cm_;}


     const Markov_CommandManagerVar* getCommandManager()const {return cm_;}


  protected:
    Markov_CommandManagerVar *cm_;

   std::size_t numMandatoryFields_;



  };




  // TODO: root ABC_Command in the hierarchy
  class ABC_Command : public Markov_IO::Implements_ValueId
  {
  public:
    struct variable
    {
      std::string name;
      std::string type;
      bool mandatory;
    };

     ~ABC_Command();
    /// virtual formated output
     std::ostream& put(std::ostream& s) const;

    virtual bool operator==(const ABC_Command& other)const;

    /// hint about of the class nature
     std::string Tip()const;

    /// a short description of the class
     std::string WhatThis()const;



    // TODO: constructor based on vector of tuples

    ABC_Command(Markov_CommandManager* cm,
                const std::string& commandName,
                const std::vector<std::string> &inputNames,
                const std::vector<std::string> &inputTypes,
                const std::vector<bool> &inputIsMandatory,
                const std::vector<std::string> &outputNames,
                const std::vector<std::string> &outputTypes,
                const std::vector<bool> &outputIsMandatory);


    ABC_Command(Markov_CommandManager* cm,
                const std::string& commandName,
                const std::vector<variable > &inputs,
                const std::vector<variable > &outputs);




    ABC_Command(){}



    virtual std::string commandName()const;


    //
    /// returns the Markov_CommandManager
    virtual Markov_CommandManager* getCommandManager();


    virtual const Markov_CommandManager* getCommandManager()const ;


    /// printed output, empty string if command fails
    virtual std::string output()const;

    virtual std::size_t numInputs()const;

    virtual std::string InputType(std::size_t i)const;
    virtual std::string InputName(std::size_t i)const;
    virtual bool isMandatoryInput(std::size_t i)const;


    virtual std::size_t numOutputs()const;
    virtual std::string OutputType(std::size_t i)const;
    virtual std::string OutputName(std::size_t i)const;
    virtual bool isMandatoryOutput(std::size_t i)const;


    // TODO: handle error messages through commandmanager or return a composite class with boolean and error message
    /// error message, empty string if succeeded
    virtual std::string errorMessage()const;


    virtual std::vector<std::string> complete(const std::string &hint, const std::deque<Token>& tokenList);



    virtual std::string check(const std::deque<Token>& tokenList);



    /// runs the command on the command manager and returns true if succeeds
    virtual bool run( std::deque<Token>& tokenList);

    virtual bool run( ){}

    virtual bool run(const std::vector<std::string>& InputValue,
                     const std::vector<std::string>& OutputValue){return InputValue==OutputValue;}


    static std::string directory();

    static std::string varName();

    static std::string typeName();

    static std::string fileName();

    static std::string testName();



    bool run(Markov_IO::Token_Stream tokenList);
  protected:
    virtual void errorMessage(const std::string& errmsg);


    Markov_CommandManager* cm_;
    std::string commandName_;
    std::vector<std::string> inputNames_;
    std::vector<std::string> inputTypes_;
    std::vector<bool> inputMandatory_;

    std::string output_;
    std::string errorMessage_;


    std::vector<std::string> outputNames_;
    std::vector<std::string> outputTypes_;
    std::vector<bool> outputMandatory_;


  };


}


#endif // ABC_COMMAND_H
