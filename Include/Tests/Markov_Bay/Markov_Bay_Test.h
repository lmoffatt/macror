#ifndef MARKOV_BAY_TEST_H
#define MARKOV_BAY_TEST_H

#include "Tests/Markov_Bay/ABC_Markov_Likelihood_step_Test.h"


namespace Markov_Test
{

namespace Markov_Bay_Test
{
//using namespace Markov_Mol;
class Markov_Bay_Test
{

public:

    Markov_Bay_Test(const Markov_Mol::ABC_PatchModel& patch);
    virtual MultipleTests All_Tests();

    virtual ~Markov_Bay_Test();

private:
 const Markov_Mol::ABC_PatchModel& patch_;



};
}
}





#endif // MARKOV_BAY_TEST_H
