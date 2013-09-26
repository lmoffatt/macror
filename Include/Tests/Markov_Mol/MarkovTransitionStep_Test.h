#ifndef MARKOVTRANSITIONSTEP_TEST_H
#define MARKOVTRANSITIONSTEP_TEST_H


#include "Markov_Mol/MarkovTransitionStep.h"

#include "Tests/MultipleTests.h"
#include "Tests/Markov_IO/ABC_Put_Test.h"
namespace Markov_Test
{
namespace Markov_Mol_Test
{

using namespace Markov_Mol;

class Markov_Transition_step_Test:public Markov_IO_Test::ABC_Put_Test
{
public:

    virtual MultipleTests classInvariant()const;

    Markov_Transition_step_Test(const Markov_Transition_step& sample);

    virtual~Markov_Transition_step_Test();

private:
    const Markov_Transition_step* Qstep_;
    std::size_t k_;
    bool is_averaging_;
    bool varying_;
    bool two_anchor_;

    MultipleTests RightSize()const;
    MultipleTests EmptyShellConstructor()const;


};

}
}


#endif // MARKOVTRANSITIONSTEP_TEST_H
