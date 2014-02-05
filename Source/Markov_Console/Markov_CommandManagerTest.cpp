#include "Markov_Console/Markov_CommandManagerTest.h"
#include "Include/Markov_Console/TestCommand.h"
#include  "Include/Tests/Markov_Bay/Markov_Bay_Test.h"
#include  "Include/Tests/Markov_IO/ABC_Put_Test.h"
#include  "Include/Tests/Markov_LA/Markov_LA_Tests.h"
#include  "Include/Tests/Markov_LA/Matrix_Test.h"
#include  "Include/Tests/Markov_LA/ToleranceComparison_Test.h"
#include  "Include/Tests/Markov_Mol/Markov_Mol_Tests.h"
#include "Include/Tests/MersenneTwister_Test.h"
#include "Include/Markov_Console/Autocomplete.h"
#include "Include/Markov_Console/BayesianAutocomplete.h"

namespace Markov_Console
{

Markov_CommandManagerTest::Markov_CommandManagerTest():
    Markov_CommandManager()
{
  TestCommand* testcmd=new TestCommand(this);
  cmds[testcmd->commandName()]=testcmd;

  tests[Markov_Test::Markov_LA_Test::Markov_LATest<double>::TestName()]=
      new Markov_Test::Markov_LA_Test::Markov_LATest<double>;
  tests[Markov_Test::Markov_LA_Test::Matrix_Test<double>::TestName()]=
      new Markov_Test::Markov_LA_Test::Matrix_Test<double>;
  tests[Markov_Test::Markov_LA_Test::ToleranceComparison_Test::TestName()]=
      new Markov_Test::Markov_LA_Test::ToleranceComparison_Test;
  tests[Markov_Test::MersenneTwister_Test::MersenneTwister_Test::TestName()]=
      new Markov_Test::MersenneTwister_Test::MersenneTwister_Test;
  tests[Markov_Test::Markov_Mol_Test::ABC_Markov_Model_Test::TestName()]=
      new Markov_Test::Markov_Mol_Test::ABC_Markov_Model_Test;
  tests[Markov_Test::Markov_Mol_Test::Markov_Mol_Test::TestName()]=
      new Markov_Test::Markov_Mol_Test::Markov_Mol_Test;




  for (auto it=tests.begin(); it!=tests.end(); ++it)
  {
      autoCmptByKind[ABC_Command::testName()].push_back(it->first);

  }



  }

std::string Markov_CommandManagerTest::version() const
{
  return "MacroConsoleTest 0.1";

}

Markov_Test::All_Tests * Markov_CommandManagerTest::getTest(const std::string& testName)
{
  auto it=tests.find(testName);
  if (it==tests.end())
    return nullptr;
  else
    return it->second;
}


bool Markov_CommandManagerTest::next_instruction()
{
    // Else try with all other commands
    return Markov_CommandManager::next_instruction();
}

}


