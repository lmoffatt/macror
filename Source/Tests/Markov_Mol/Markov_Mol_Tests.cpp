#include "Tests/Markov_Mol/Markov_Mol_Tests.h"


namespace Markov_Test
{
namespace Markov_Mol_Test
{

    Markov_Mol_Test::Markov_Mol_Test(const ABC_Markov_Model& model):
        modelTest(model){}
    MultipleTests Markov_Mol_Test::All_Tests()
    {
        MultipleTests results("namespace Markov_Mol",
                              "all tests");
        results.push_back(modelTest.AllTests());
        return results;
    }



}


}




