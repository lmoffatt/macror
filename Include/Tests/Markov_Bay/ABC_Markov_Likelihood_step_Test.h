#ifndef ABC_MARKOV_LIKELIHOOD_STEP_TEST_H
#define ABC_MARKOV_LIKELIHOOD_STEP_TEST_H


#include "Markov_Bay/ABC_MarkovLikelihoodStep.h"

#include "Tests/MultipleTests.h"
#include "Tests/Markov_IO/ABC_Put_Test.h"
namespace Markov_Test
{
namespace Markov_Bay_Test
{

using namespace Markov_Bay;

class ABC_Markov_Likelihood_step_Test:public Markov_IO_Test::ABC_Put_Test
{
public:

    virtual MultipleTests AllTests();
    virtual MultipleTests classInvariant()const;

    virtual MultipleTests startInvariant(double x);
    virtual MultipleTests runInvariant(const Markov_IO::ABC_measure_step& Y,
                                       std::size_t numSamples,
                                       std::size_t numSteps,
                                       double pmin)const;


    ABC_Markov_Likelihood_step_Test(const ABC_Markov_Likelihood_step& sample);



    virtual ~ABC_Markov_Likelihood_step_Test();

private:
     ABC_Markov_Likelihood_step* S_;

    MultipleTests LogL_Test_()const;
    MultipleTests Model_Test_()const;

};

MultipleTests Probability_vector_Test(const Markov_LA::M_Matrix<double> P);

MultipleTests Probability_Covariance_Test(const Markov_LA::M_Matrix<double> Pcov);


}
}



#endif // ABC_MARKOV_LIKELIHOOD_STEP_TEST_H
