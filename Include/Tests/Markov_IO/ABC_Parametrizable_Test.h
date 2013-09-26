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



    /**
      Test invariants of apply_parameters and get_parameters

      */
    virtual MultipleTests classInvariant()const;

    ABC_Parametrizable_Test(const ABC_Parametrizable& parametrizable);

    virtual ~ABC_Parametrizable_Test();

private:
    const ABC_Parametrizable* param_;

    };
}

}




#endif // ABC_PARAMETRIZABLE_TEST_H
