#include "Include/Markov_Console/TestCommand.h"
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



  TestCommand::TestCommand(Markov_CommandManager *cm)
  {
    cm_=cm;
  }

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

  /// runs the command on the command manager and returns true if succeeds
  bool TestCommand::run(std::deque<Token>& tokenList)
  {
    if (tokenList.size()<2)
      {
        output_.clear();
        errorMessage_="tested item is missing";
        return false;
      }
    else if (tokenList.size()<3)
      run(tokenList[1].Name(),"");
    else
      run(tokenList[1].Name(),tokenList[2].Name());
  }





  bool TestCommand::run(const std::string& testedEntity,
                        const std::string& mode)
  {
    Markov_Test::MultipleTests testResult;
    if (testedEntity=="MarkovLA")
      {
        Markov_Test::Markov_LA_Test::Markov_LA_Test<double> LAtest;
        testResult=LAtest.All_Tests();
      }
    else if (testedEntity=="MarkovMol")
      {
        auto varnames =cm_->getVarsList(Markov_Mol::ABC_PatchModel::ClassName());
        Markov_Mol::ABC_PatchModel* p=dynamic_cast<Markov_Mol::ABC_PatchModel*>(cm_->getVar(varnames.front()));
        if (p)
          {
            Markov_Test::Markov_Mol_Test::Markov_Mol_Test Moltest(p->Model());
            testResult=Moltest.All_Tests();
          }
      }
    else if (testedEntity=="MarkovBay")
      {
        auto varnames =cm_->getVarsList(Markov_Mol::ABC_PatchModel::ClassName());
        Markov_Mol::ABC_PatchModel* p=dynamic_cast<Markov_Mol::ABC_PatchModel*>(cm_->getVar(varnames.front()));
        if (p)
          {
            Markov_Test::Markov_Bay_Test::Markov_Bay_Test Baytest(*p);
            testResult=Baytest.All_Tests();
          }
      }
    else if (testedEntity=="Random")
      {
        Markov_Test::MersenneTwister_Test::MersenneTwister_Test MTT(0);
        testResult=MTT.AllTests();

      }
    else if (testedEntity=="Autocomplete")
      {
        Markov_Test::Markov_MacroConsele_Test::Autocomplete_Test test;
        testResult=test.classInvariant();

      }
    else if (testedEntity=="BayesAutocomplete")
      {
        Markov_Test::Markov_MacroConsele_Test::BayesAutocomplete_Test test;
        testResult=test.classInvariant();

      }
    if (mode=="verbose")
      testResult.VerboseLevel(true);
    else
      testResult.VerboseLevel(0);
    std::cerr<<testResult;

    std::ofstream f;
    f.open("test.txt");
    f<<testResult;
    f.close();

  }




}


