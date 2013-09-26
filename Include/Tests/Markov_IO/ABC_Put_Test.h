#ifndef ABC_PUT_TEST_H
#define ABC_PUT_TEST_H
#include "Markov_IO/ABC_Put.h"

#include "Tests/MultipleTests.h"
namespace Markov_Test
{
namespace Markov_IO_Test
{

using namespace Markov_IO;

class ABC_Put_Test
{
public:

    virtual MultipleTests classInvariant()const;

    ABC_Put_Test(const ABC_Put& aPut);

    virtual~ABC_Put_Test();

protected:
    const ABC_Put* sample_;
};

}
}


#endif // ABC_PUT_TEST_H
