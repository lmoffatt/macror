#ifndef MULTIVARIATEGAUSSIAN_TEST_H
#define MULTIVARIATEGAUSSIAN_TEST_H
#include "Tests/MultipleTests.h"
#include "Tests/Markov_IO/ABC_Parametrizable_Test.h"
#include "Markov_Bay/MultivariateGaussian.h"


namespace Markov_Test
{


namespace Markov_Bay_Test
{
using Markov_LA::M_Matrix;

using namespace Markov_Bay;


class MultivariateGaussian_Test
{
public:
    /**
      Test invariants of apply_parameters and get_parameters

      */
    virtual MultipleTests AllTests();

    virtual MultipleTests logP_Test(const Markov_LA::M_Matrix<double>& x)const;
    virtual MultipleTests  P_Test(const Markov_LA::M_Matrix<double>&)const;

    virtual MultipleTests  sample_Test(std::size_t NumSamples,
                                       double p_mean)const;




    MultivariateGaussian_Test(const MultivariateGaussian& multivariategaussian);

    virtual ~MultivariateGaussian_Test();

private:
    MultivariateGaussian MuGa_;

   };
}
}




#endif // MULTIVARIATEGAUSSIAN_TEST_H
