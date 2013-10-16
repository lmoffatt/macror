#ifndef MARKOVSTATE_TEST_H
#define MARKOVSTATE_TEST_H

#include "Markov_Mol/MarkovState.h"

#include "Tests/MultipleTests.h"
#include "Tests/Markov_IO/ABC_Put_Test.h"
namespace Markov_Test
{
namespace Markov_Mol_Test
{

using namespace Markov_Mol;

class Markov_state_Test:public Markov_IO_Test::ABC_Put_Test
{
public:

    virtual MultipleTests classInvariant()const;
  virtual std::string testedClass()const;

    Markov_state_Test(const Markov_state& sample);

    virtual ~Markov_state_Test();
    static std::string TestName();
    virtual std::string myTest()const;

private:
    const Markov_state* S_;
};

}
}


#endif // MARKOVSTATE_TEST_H
