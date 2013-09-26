#ifndef SINGLEOPTIMIZATION_TEST_H
#define SINGLEOPTIMIZATION_TEST_H



#include "Markov_Bay/SimpleOptimization.h"

#include "Tests/MultipleTests.h"
#include "Tests/Markov_IO/ABC_Put_Test.h"
namespace Markov_Test
{
namespace Markov_Bay_Test
{

using namespace Markov_Bay;

class SimpleOptimization_Test:public Markov_IO_Test::ABC_Put_Test
{
public:

    virtual MultipleTests classInvariant()const;

    virtual MultipleTests runInvariant(const Markov_IO::Parameters& beta);


    SimpleOptimization_Test(const SimpleOptimization& sample);



    virtual ~SimpleOptimization_Test();






private:
    const SimpleOptimization* O_;


};


}
}






#endif // SINGLEOPTIMIZATION_TEST_H
