#ifndef MARKOV_BAY_TEST_H
#define MARKOV_BAY_TEST_H

#include "Tests/Markov_Bay/ABC_Markov_Likelihood_step_Test.h"


namespace Markov_Test
{

namespace Markov_Bay_Test
{
//using namespace Markov_Mol;
class Markov_Bay_Test:public All_Tests
{

public:

    Markov_Bay_Test(const Markov_Mol::ABC_PatchModel& patch);
    virtual MultipleTests AllTests(Markov_Console::Markov_CommandManager* cm, const std::string varNameTested);
    virtual std::string testedClass()const;

    virtual ~Markov_Bay_Test();
    static std::string TestName();
    virtual std::string myTest()const;


private:
 const Markov_Mol::ABC_PatchModel& patch_;



};
}
}





#endif // MARKOV_BAY_TEST_H
