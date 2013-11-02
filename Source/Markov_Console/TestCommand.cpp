#include "Include/Markov_Console/TestCommand.h"
#include "Markov_IO/Object.h"

#include "Markov_IO/auxiliarIO.h"

#include "Tests/Markov_LA/Markov_LA_Tests.h"
#include "Tests/Markov_Mol/Markov_Mol_Tests.h"
#include "Tests/Markov_Bay/Markov_Bay_Test.h"
#include "Tests/MersenneTwister_Test.h"
#include "Include/Markov_Console/Autocomplete.h"
#include "Include/Markov_Console/BayesianAutocomplete.h"
#include "Include/Markov_Console/Markov_CommandManager.h"


namespace Markov_Console
{
  ///  destructor
  TestCommand::~TestCommand(){}



  TestCommand::TestCommand(Markov_CommandManagerTest *cm)
    :ABC_Command(cm,
                 "test",{{
                 "test_kind",ABC_Command::testName(),true},{
                 "tested_variable",ABC_Command::varName(),false},{
                 "verbose_mode",Markov_IO::Object<std::string>::ClassName(),false}},{{
                 "filename_out",Markov_IO::Object<std::string>::ClassName(),false}}),
      cmt_(cm)
  {}

  /// hint about of the class nature
  std::string TestCommand::Tip()const
  {
    return "Performs a test";
  }

  /// a short description of the class
  std::string TestCommand::WhatThis()const
  {
    return "";
  }



  std::string TestCommand::commandName()const
  {
    return "test";
  }



  void TestCommand::updateTestKind(const std::deque<Token>& tokenList)
  {
    if (tokenList.size()>1)
      {
        std::string testKind=tokenList[1].Name();
        Markov_Test::All_Tests *t=cmt_->getTest(testKind);
        if (t!=nullptr)
          {
            inputTypes_[1]=t->testedClass();
            inputNames_[1]=t->testedClass();
            inputMandatory_[1]=true;
          }
      }

  }


  void TestCommand::updateTestKindrun(const std::deque<Token>& tokenList)
  {
    if (tokenList.size()>0)
      {
        std::string testKind=tokenList[0].Name();
        Markov_Test::All_Tests *t=cmt_->getTest(testKind);
        if (t!=nullptr)
          {
            inputTypes_[1]=t->testedClass();
            inputNames_[1]=t->testedClass();
            inputMandatory_[1]=true;
          }
      }

  }

  std::vector<std::string> TestCommand::complete(const std::string &hint, const std::deque<Token>& tokenList)
  {
    updateTestKind(tokenList);
    return ABC_Command::complete(hint,tokenList);

  }



  std::string TestCommand::check(const std::deque<Token>& tokenList){
    updateTestKind(tokenList);
    return ABC_Command::check(tokenList);

  }

  bool TestCommand::run( std::deque<Token>& tokenList){
  //  updateTestKindrun(tokenList);
    return ABC_Command::run(tokenList);

  }



  bool TestCommand::run(const std::vector<std::string>& InputValue,
                        const std::vector<std::string>& OutputValue)
  {
    std::string testKind=InputValue[0];
    std::string testedvariable="";
    std::string mode="";
    std::string filenamOut=testKind+".txt";
    if (InputValue.size()>1)
      testedvariable=InputValue[1];
    if (InputValue.size()>2)
      mode=InputValue[2];
    if (OutputValue.size()>0)
      filenamOut=OutputValue[0];
    return run(testKind,
               testedvariable,
               mode,
               filenamOut);



  }


  bool TestCommand::run(const std::string& testKind,
                        const std::string& testedvariable,
                        const std::string& mode,
                        const std::string& filenamOut)

  {
    Markov_Test::All_Tests * testK=cmt_->getTest(testKind);
    Markov_Test::MultipleTests testResult=testK->AllTests(cmt_,testedvariable);
    bool verbose=mode=="verbose";
    testResult.VerboseLevel(verbose);

    std::stringstream ss;
    ss<<testResult;

    output_=ss.str();

    std::ofstream f;
    f.open(filenamOut);
    f<<testResult;
    return true;
  }




}


