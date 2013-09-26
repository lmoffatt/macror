#ifndef MERSENNETWISTER_TEST_H
#define MERSENNETWISTER_TEST_H
#include "Borrowed/MersenneTwister.h"
#include "Tests/MultipleTests.h"
#include "Markov_LA/Matrix.h"

namespace Markov_Test
{
namespace MersenneTwister_Test
{
using namespace Borrowed::MersenneTwister;

class MersenneTwister_Test
{
public:

    MultipleTests AllTests();
    MultipleTests rand_Test(std::size_t n,
                            std::size_t NumBins,
                            std::size_t NumLags,
                            double p_min);
    MultipleTests Binomial_Test();
    MultipleTests Multinomial_Test(const Markov_LA::M_Matrix<double>& P,
                                   std::size_t N,
                                   std::size_t NumSamples,
                                   double p_min);
    MultipleTests Normal_Test(std::size_t n,
                              std::size_t NumBins,
                              std::size_t NumLags,
                              double p_min);

    MersenneTwister_Test(std::size_t seed);
   ~MersenneTwister_Test();
private:
    MTRand sto_;
};

MultipleTests CheckMoments(const Markov_LA::M_Matrix<double>& sample,
                           double Mean,
                           double Variance,
                           double Skewness,
                           double ExcessKurtosis,
                           double p_min);

MultipleTests CheckDistribution(const Markov_LA::M_Matrix<double>& sample,
                                const std::map<double,double>& pdf,
                                double p_min);

MultipleTests CheckAutocorrelation(const Markov_LA::M_Matrix<double>& sample,
                                   std::size_t NumLags,
                                   double Mean,
                                   double Variance,
                                   double p_min);


} //end of MersenneTwister_Test

}



#endif // MERSENNETWISTER_TEST_H
