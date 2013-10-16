#include "Tests/Markov_Mol/Markov_Mol_Tests.h"
#include "Markov_Console/Markov_CommandManagerTest.h"


namespace Markov_Test
{
namespace Markov_Mol_Test
{

   std::string Markov_Mol_Test::testedClass()const
  {
    return this->modelTest.testedClass();
  }

    std::string Markov_Mol_Test::TestName()
    {
      return "Markov_Mol_Test";
    }

    std::string Markov_Mol_Test::myTest()const
    {
      return TestName();
    }


    Markov_Mol_Test::Markov_Mol_Test(const ABC_Markov_Model& model):
        modelTest(model){}

    Markov_Mol_Test::Markov_Mol_Test(){}


    MultipleTests Markov_Mol_Test::AllTests(Markov_Console::Markov_CommandManager* cm, const std::string varNameTested)
    {
      ABC_Saveable* s;

      if (!cm->getVar(varNameTested,s))
        return MultipleTests();
      ABC_Markov_Model *m=dynamic_cast<ABC_Markov_Model*>(s);
      modelTest=ABC_Markov_Model_Test(*m);

      MultipleTests results("namespace Markov_Mol",
                              "all tests");



        results.push_back(modelTest.AllTests(cm,varNameTested));
        return results;
    }



}


}




