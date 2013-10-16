#ifndef ABC_PARAMETRIZABLE_TEST_H
#define ABC_PARAMETRIZABLE_TEST_H
#include "Markov_IO/ABC_Parametrizable.h"

#include "Tests/MultipleTests.h"
namespace Markov_Test
{

namespace Markov_IO_Test
{

using namespace Markov_IO;


class ABC_Parametrizable_Test: public ABC_Saveable_Test
{
public:

  virtual MultipleTests AllTests(Markov_Console::Markov_CommandManager* cm, const std::string varNameTested);

  virtual std::string testedClass()const;
  static std::string TestName();

  virtual std::string myTest()const;




    /**
      Test invariants of apply_parameters and get_parameters

      */
    virtual MultipleTests classInvariant()const;

    ABC_Parametrizable_Test(const ABC_Parametrizable& parametrizable);

    ABC_Parametrizable_Test();


    virtual ~ABC_Parametrizable_Test();

protected:
    const ABC_Parametrizable* param_;

    };
}

}




#endif // ABC_PARAMETRIZABLE_TEST_H
