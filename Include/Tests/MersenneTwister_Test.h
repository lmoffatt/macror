#ifndef MERSENNETWISTER_TEST_H
#define MERSENNETWISTER_TEST_H
#include "Borrowed/MersenneTwister.h"
#include "Tests/MultipleTests.h"
#include "Markov_LA/Matrix.h"
#include  "Tests/All_Tests.h"

namespace Markov_Test
{
namespace MersenneTwister_Test
{
using namespace Borrowed::MersenneTwister;

class MersenneTwister_Test:public All_Tests
{
public:

  virtual MultipleTests AllTests(Markov_Console::Markov_CommandManager* cm,
                                 const std::string varNameTested);
 // virtual MultipleTests AllTests()=0;
  static std::string TestName();

  virtual std::string myTest()const;

  virtual std::string testedClass()const;



    MultipleTests AllTests()const;
    MultipleTests rand_Test(std::size_t n,
                            std::size_t NumBins,
                            std::size_t NumLags,
                            double p_min) const;
    MultipleTests Binomial_Test()const;
    MultipleTests Multinomial_Test(const Markov_LA::M_Matrix<double>& P,
                                   std::size_t N,
                                   std::size_t NumSamples,
                                   double p_min)const;
    MultipleTests Normal_Test(std::size_t n,
                              std::size_t NumBins,
                              std::size_t NumLags,
                              double p_min) const;

    MersenneTwister_Test(std::size_t seed=0);
   virtual ~MersenneTwister_Test();
private:
    mutable MTRand sto_;
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
