#ifndef TESTCOMMAND_H
#define TESTCOMMAND_H
#include "Include/Markov_Console/ABC_Command.h"
#include "Include/Markov_Console/Markov_CommandManagerTest.h"
#include <vector>

namespace Markov_Console
{

class TestCommand:public ABC_Command
{
public:
    TestCommand(Markov_CommandManagerTest* cm);

    /// virtual destructor
    virtual ~TestCommand();

        /// hint about of the class nature
    virtual std::string Tip()const;

    /// a short description of the class
    virtual std::string WhatThis()const;

    virtual std::string commandName()const;



    virtual std::vector<std::string> complete(const std::string &hint, const std::deque<Token>& tokenList);



    virtual std::string check(const std::deque<Token>& tokenList);


    virtual bool run( std::deque<Token>& tokenList);


    bool run(const std::vector<std::string>& InputValue,
                         const std::vector<std::string>& OutputValue);




    /// runs the command for a list of parameters
    virtual bool run(const std::string& testKind,
                     const std::string& testedvariable,
                         const std::string& mode,
                     const std::string& filenamOut);


private:
    void updateTestKind(const std::deque<Token> &tokenList);
    void updateTestKindrun(const std::deque<Token> &tokenList);
    Markov_CommandManagerTest* cmt_;
    std::string testedVariableKind_;
};


}




#endif // TESTCOMMAND_H
