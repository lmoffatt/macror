#ifndef MARKOVTRANSITIONRATE_TEST_H
#define MARKOVTRANSITIONRATE_TEST_H
#include "Markov_Mol/MarkovTransitionRate.h"

#include "Tests/MultipleTests.h"
#include "Tests/Markov_IO/ABC_Put_Test.h"
namespace Markov_Test
{
namespace Markov_Mol_Test
{

using namespace Markov_Mol;

class Markov_Transition_rate_Test:public Markov_IO_Test::ABC_Put_Test
{
public:

    virtual MultipleTests classInvariant()const;

    Markov_Transition_rate_Test(const Markov_Transition_rate& sample);

    virtual~Markov_Transition_rate_Test();

private:
    const Markov_Transition_rate* Qx_;
};

}
}



#endif // MARKOVTRANSITIONRATE_TEST_H
