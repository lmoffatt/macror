#include "Tests/Markov_Bay/MultivariateGaussian_Test.h"
#include "Tests/ElementaryTest.h"
#include "Markov_LA/matrixProduct.h"
#include "Markov_Bay/MacroscopicGaussianDistribution.h"
#include "Markov_LA/auxiliarMath.h"
#include "Markov_LA/matrixAssigmentOp.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixInverse.h"

#include "Markov_IO/auxiliarIO.h"


namespace Markov_Test
{

namespace Markov_Bay_Test
{
using namespace Markov_LA;

using namespace Markov_Bay;

using namespace Markov_IO;

 MultipleTests MultivariateGaussian_Test::AllTests()
 {

     MultipleTests result("MultivariateGaussian",
                          "check sampling");
     const std::size_t NumSamples=1e5;
     const double p_min=1e-2;
     result.push_back(sample_Test(NumSamples,p_min));


     return result;



 }

 MultipleTests MultivariateGaussian_Test::logP_Test(const Markov_LA::M_Matrix<double>& )const
 {

 }
 MultipleTests  MultivariateGaussian_Test::P_Test(const Markov_LA::M_Matrix<double>& )const
 {

 }

 MultipleTests  MultivariateGaussian_Test::sample_Test(std::size_t NumSamples,
                                                       double p_min)const
 {
     MultipleTests results("method sample()",
                    "check invariants");

     std::size_t k=MuGa_.size();
     M_Matrix<double> Mean=zeros<double>(1,k);

     M_Matrix<double> Cov=zeros<double>(k,k);
     //double sumLogL=0;

     //double sumLogL2=0;

     for (std::size_t i=0; i< NumSamples; ++i)
     {
         M_Matrix<double> x=MuGa_.sample();
         Mean+=x;
         M_Matrix<double> dx=x-MuGa_.Mean();
         Cov+=TranspMult(dx,dx);

     }
     Mean/=double(NumSamples);
     Cov/=double(NumSamples);
    // Cov-=TranspMult(MuGa_.Mean(),MuGa_.Mean());
     M_Matrix<double> CovEx=MuGa_.Cov();
     M_Matrix<double> Pdiff=Mean-MuGa_.Mean();

     double chi2_Mean=ToDouble(Pdiff*multTransp(MuGa_.CovInv(),Pdiff))*NumSamples;


     double p_Mean=1.-ChiSqrCdf(chi2_Mean,k-1);
     ElementaryTest tmpE(
                 "P_mean()",
                 " p>"+Markov_IO::ToString(p_min)+
                 "\n N expected \n"+ToString(MuGa_.Mean())+
                 "\n P recovered \n"+ToString(Mean)+"\n"
                 "\nchi2 value        \t"+ToString(chi2_Mean)+
                 "\n NumSamples "+ToString(NumSamples)+
                 "\n df="+ToString(k-1)+
                 "\n p="+ToString(p_Mean)+"\n",
                 p_min<p_Mean);

     results.push_back(tmpE);


     MultipleTests pP_cov("P_cov()",
                          "for each i,j pair"
                          " p>"+Markov_IO::ToString(p_min)
                          );

     for (std::size_t i=0; i<k; ++i)
         for (std::size_t j=i;j<k; j++)
         {
             double chi2_cov;
             if (i==j)
                 chi2_cov=Cov(i,i)/CovEx(i,i) *NumSamples;
             else
                 chi2_cov=(Cov(i,i)+Cov(j,j)+2.0*Cov(i,j))/
                         (CovEx(i,i)+CovEx(j,j)+2.0*CovEx(i,j))*NumSamples;
             double p_cov=1.-ChiSqrCdf(chi2_cov,NumSamples);
             ElementaryTest t(
                         "P_cov("+
                         Markov_IO::ToString(i)+","+
                         Markov_IO::ToString(j)+")",
                         " p>"+Markov_IO::ToString(p_min)+
                         "\n expected \t"+ToString(MuGa_.Cov()(i,j))+
                         "\n approximated \t"+ToString(Cov(i,j))+"\n"
                         "\nchi2 value        \t"+ToString(chi2_cov)+
                         "\n df="+ToString(NumSamples)+"\n"
                         "\n p="+ToString(p_cov)+"\n",
                         p_cov>p_min);

             pP_cov.push_back(t);
         }
     results.push_back(pP_cov);




   return results;

 }



MultivariateGaussian_Test::MultivariateGaussian_Test(const MultivariateGaussian& multivariategaussian):
      MuGa_(multivariategaussian){}

MultivariateGaussian_Test::~MultivariateGaussian_Test(){}

}
}




