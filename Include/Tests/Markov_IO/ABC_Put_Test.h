#ifndef ABC_PUT_TEST_H
#define ABC_PUT_TEST_H
#include "Markov_IO/ABC_Put.h"

#include "Tests/MultipleTests.h"
#include "Tests/All_Tests.h"

namespace Markov_Test
{
namespace Markov_IO_Test
{

using namespace Markov_IO;

class ABC_Put_Test:public All_Tests
{
public:
  virtual MultipleTests AllTests(Markov_Console::Markov_CommandManager* cm, const std::string varNameTested);

  virtual std::string testedClass()const;
  static std::string TestName();

  virtual std::string myTest()const;


    virtual MultipleTests classInvariant()const;

    ABC_Put_Test(const ABC_Put& aPut);

    ABC_Put_Test(){}

    virtual~ABC_Put_Test();

protected:
    const ABC_Put* sample_;
};

}
}


#endif // ABC_PUT_TEST_H
