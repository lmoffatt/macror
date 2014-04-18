#ifndef ABSTRACT_COMMAND_H
#define ABSTRACT_COMMAND_H

#include <deque>
#include <vector>
#include <string>
#include <tuple>

#include <Markov_Console/Token_old.h>

#include <Macror_Var/Implement_Named_Object.h>




namespace Macror_Console
{
  class Macror_CommandManager;

  struct argument
  {
    std::string name;
    std::string type;
    bool mandatory;
  };
  
  
  class Abstract_Command: public Macror_Var::Abstract_Named_Object
  {
  public:
    
    virtual void run(const std::vector<std::string> &InputValue,
                     const std::vector<std::string> &OutputValue);

    virtual  void  reRun();
    
    virtual std::string result()const;
    
    
    virtual ~Abstract_Command();
    /// virtual formated output


   
    
    
   // TODO: constructor based on vector of tuples

    Abstract_Command(Markov_CommandManager* cm,
                const std::string& commandName,
                const std::vector<std::string> &inputNames,
                const std::vector<std::string> &inputTypes,
                const std::vector<bool> &inputIsMandatory,
                const std::vector<std::string> &outputNames,
                const std::vector<std::string> &outputTypes,
                const std::vector<bool> &outputIsMandatory);


    Abstract_Command(Markov_CommandManager* cm,
                const std::string& commandName,
                const std::vector<argument > &inputs,
                const std::vector<argument > &outputs);




    ABC_Command(){}


    virtual void  run(std::deque<Token> &tokenList);


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


    virtual std::vector<std::string> complete(const std::string &hint,
                                              const std::deque<Token>& tokenList);

    virtual std::string check(const std::deque<Token>& tokenList);



    /// runs the command on the command manager and returns true if succeeds
    virtual bool run( std::deque<Token>& tokenList);

   // virtual bool run( std::deque<Token>& tokenList){}

    virtual bool run(const std::vector<std::string>& InputValue,
                     const std::vector<std::string>& OutputValue);



  protected:
    virtual void errorMessage(const std::string& errmsg);
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


#endif // ABSTRACT_COMMAND_H
