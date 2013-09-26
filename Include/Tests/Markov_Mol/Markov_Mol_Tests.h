#ifndef MARKOV_MOL_TESTS_H
#define MARKOV_MOL_TESTS_H

#include "Tests/Markov_Mol/ABC_Markov_Model_Test.h"


namespace Markov_Test
{

namespace Markov_Mol_Test
{
//using namespace Markov_Mol;
class Markov_Mol_Test
{

public:

    Markov_Mol_Test(const ABC_Markov_Model& model);
    MultipleTests All_Tests();

private:
 ABC_Markov_Model_Test modelTest;



};
}
}



#endif // MARKOV_MOL_TESTS_H
