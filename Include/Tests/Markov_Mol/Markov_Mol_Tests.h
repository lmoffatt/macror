#ifndef MARKOV_MOL_TESTS_H
#define MARKOV_MOL_TESTS_H

#include "Tests/Markov_Mol/ABC_Markov_Model_Test.h"


namespace Markov_Test
{

namespace Markov_Mol_Test
{
//using namespace Markov_Mol;
class Markov_Mol_Test:public All_Tests
{

public:
  virtual std::string testedClass()const;

    Markov_Mol_Test(const ABC_Markov_Model& model);
    Markov_Mol_Test();

    virtual MultipleTests AllTests(Markov_Console::Markov_CommandManager* cm, const std::string varNameTested);
    static std::string TestName();
    virtual std::string myTest()const;
    ~Markov_Mol_Test(){}

private:
 ABC_Markov_Model_Test modelTest;



};
}
}



#endif // MARKOV_MOL_TESTS_H
