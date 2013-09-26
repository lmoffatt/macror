
#include "Markov_LA/matrixOperators.h"
#include "Markov_LA/matrixRelational.h"
#include "Markov_LA/matrixSum.h"
#include "Markov_LA/matrixInit.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_IO/x_dt.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixExp.h"
#include "Markov_LA/matrixMaxMin.h"
#include "Markov_IO/auxiliarIO.h"

#include "Markov_Bay/MacroAproxStep.h"

#include "Tests/Markov_Bay/SimpleOptimization_Test.h"


#include "Tests/ElementaryTest.h"


namespace Markov_Test
{
namespace Markov_Bay_Test
{
using namespace Markov_LA;
MultipleTests SimpleOptimization_Test::classInvariant()const
{
    MultipleTests results("ClassDescription ",
                          "Class Invariant");

    results.push_back(ABC_Put_Test::classInvariant());
    return results;


}



SimpleOptimization_Test::
SimpleOptimization_Test(const SimpleOptimization& sample):
    ABC_Put_Test(sample),
    O_(dynamic_cast<const SimpleOptimization*>(sample_))
{}

SimpleOptimization_Test::~SimpleOptimization_Test()
{}



 MultipleTests SimpleOptimization_Test::
 runInvariant(const Markov_IO::Parameters& beta)
 {
     MultipleTests results("SimpleOptimization::run(const Markov_IO::Parameters&)",
                   "method invariant");

     return results;

 }

}


}

