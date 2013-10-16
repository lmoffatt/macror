#include "Tests/MersenneTwister_Test.h"
#include "Tests/ElementaryTest.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_LA/auxiliarMath.h"
#include "Markov_Bay/G_Test.h"
#include "Markov_Bay/MacroscopicGaussianDistribution.h"
#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixOperators.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixSum.h"

namespace Markov_Test
{
namespace MersenneTwister_Test
{
using namespace Borrowed::MersenneTwister;
using namespace Markov_IO;
using namespace Markov_LA;
using namespace Markov_Bay;

   MultipleTests MersenneTwister_Test::AllTests(Markov_Console::Markov_CommandManager* cm,
                                                const std::string varNameTested)
   {
     return AllTests();
   }
 // virtual MultipleTests AllTests()=0;
   std::string MersenneTwister_Test::TestName()
   {
     return "MersenneTwister_Test";
   }

   std::string MersenneTwister_Test::myTest()const
   {
     return TestName();
   }

   std::string MersenneTwister_Test::testedClass()const
   {
     return "";
   }



  MultipleTests MersenneTwister_Test::AllTests()const
  {

    MultipleTests result("MersenneTwister header",
                         " check random generators");
    const std::size_t NumSamples=1e4;
    const std::size_t NumBins=NumSamples/1000;
    const std::size_t NumLags=1e3;
    const double p_min=0.01;

    result.push_back(rand_Test(NumSamples,NumBins,NumLags,p_min));

    result.push_back(Normal_Test(NumSamples,NumBins,NumLags,p_min));

    const std::size_t k=5;

    M_Matrix<double> P(1,k);
    P[0]=0.01;
    P[1]=0.1;
    P[2]=0.5;
    P[3]=0.001;
    P[4]=0;
    P[4]=1.-totalsum(P);

    const std::size_t N=27;

    result.push_back(Multinomial_Test(P,N,NumSamples,p_min));


    return result;


}

MultipleTests MersenneTwister_Test::rand_Test(std::size_t n,
                                              std::size_t NumBins,
                                              std::size_t NumLags,
                                              double p_min)const
{
    MultipleTests result("method rand()",
                         "check the randomness");


    Markov_LA::M_Matrix<double> r(1,n);
    for (std::size_t i=0; i<n; i++)
        r[i]=sto_.rand();

    double Mean=0.5;
    double Variance=1./12;
    double Skewness=0;
    double Kurtosis=-6./5;
    result.push_back(CheckMoments(r,Mean,Variance,Skewness,Kurtosis,p_min));

    std::map<double, double> pdf;
    for (std::size_t i=0; i<NumBins; ++i)
        pdf[1./NumBins*(i+1)]=1./NumBins;

    result.push_back(CheckDistribution(r,pdf,p_min));

    result.push_back(CheckAutocorrelation(r,NumLags,Mean,Variance,p_min));

    return result;

}

MersenneTwister_Test::MersenneTwister_Test(std::size_t seed):
    sto_(MTRand(seedinit(seed))){}


MersenneTwister_Test::~MersenneTwister_Test(){}

MultipleTests MersenneTwister_Test::Binomial_Test() const{}

MultipleTests MersenneTwister_Test::Multinomial_Test(const M_Matrix<double>& P,
                                                     std::size_t N,
                                                     std::size_t NumSamples,
                                                     double p_min)const
{
    std::size_t k=size(P);

    sto_.Multinomial(P,N);



    MultipleTests results("method Multinomial(P,n)"
                         "\n P= "+ToString(P)+
                         "\n n= "+ToString(N),
                         "check randomness");


    M_Matrix<double> sumN(1,k);
    M_Matrix<double> sumN2(k,k);

    M_Matrix<double> sample(1,k);
    double sumLogL=0;
    double sumLogL2=0;
    for (std::size_t i=0; i<NumSamples; ++i)
    {
        sample=sto_.Multinomial(P,N);
        sumN+=sample;
        sumN2+=TranspMult(sample,sample);
        double logL=LogMultinomialPdf(sample,P);
        sumLogL+=logL;
        sumLogL2+=logL*logL;
    }


    M_Matrix<double> meanEx=P*double(N);
    M_Matrix<double> PcovEx=(diag(P)-TranspMult(P,P));

    M_Matrix<double> mean=sumN/NumSamples;
    M_Matrix<double> Pmean=sumN/NumSamples/N;

    M_Matrix<double> Pcov=(diag(Pmean)-TranspMult(Pmean,Pmean));

    Markov_Bay::MacroscopicGaussianDistribution Ma(P,PcovEx,N,0);
    double chiPmean=Ma.Chi2_P_mean(Pmean)*NumSamples;
    double p_Pmean=Ma.Pr_P_mean(Pmean,NumSamples);
    ElementaryTest tmpE(
                "P_mean()",
                " p>"+Markov_IO::ToString(p_min)+
                "\n N expected \n"+ToString(meanEx)+
                "\n P recovered \n"+ToString(mean)+"\n"
                "\nchi2 value        \t"+ToString(chiPmean)+
                "\n NumSamples "+ToString(NumSamples)+
                "\n df="+ToString(Ma.NumVaryingStates())+
                "\n p="+ToString(p_Pmean)+"\n",
                p_min<p_Pmean);

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
                chi2_cov=Pcov(i,i)/PcovEx(i,i) *NumSamples;
            else
                chi2_cov=(Pcov(i,i)+Pcov(j,j)+2.0*Pcov(i,j))/
                        (PcovEx(i,i)+PcovEx(j,j)+2.0*PcovEx(i,j))*NumSamples;
            double p_cov=1.-ChiSqrCdf(chi2_cov,NumSamples);
            ElementaryTest t(
                        "P_cov("+
                        Markov_IO::ToString(i)+","+
                        Markov_IO::ToString(j)+")",
                        " p>"+Markov_IO::ToString(p_min)+
                        "\n calculated \t"+ToString(PcovEx(i,j))+
                        "\n approximated \t"+ToString(Pcov(i,j))+"\n"
                        "\nchi2 value        \t"+ToString(chi2_cov)+
                        "\n df="+ToString(NumSamples)+"\n"
                        "\n p="+ToString(p_cov)+"\n",
                        p_cov>p_min);

            pP_cov.push_back(t);
        }
    results.push_back(pP_cov);

    return results;


}
MultipleTests MersenneTwister_Test::Normal_Test(std::size_t n,
                                              std::size_t NumBins,
                                              std::size_t NumLags,
                                              double p_min)const
{
    MultipleTests result("method randNormal()",
                         "check the randomness");


    Markov_LA::M_Matrix<double> r(1,n);
    for (std::size_t i=0; i<n; i++)
        r[i]=sto_.randNorm();

    double Mean=0;
    double Variance=1;
    double Skewness=0;
    double Kurtosis=0;
    result.push_back(CheckMoments(r,Mean,Variance,Skewness,Kurtosis,p_min));

    std::map<double, double> pdf;
    for (std::size_t i=0; i<NumBins; ++i)
    {
        double cumP=1.*(i+1)/NumBins;
        double x=NormalCdfInv(cumP);
        pdf[x]=1./NumBins;
    }

    result.push_back(CheckDistribution(r,pdf,p_min));

    result.push_back(CheckAutocorrelation(r,NumLags,Mean,Variance,p_min));

    return result;

}



MultipleTests CheckMoments(const Markov_LA::M_Matrix<double>& sample,
                           double Mean,
                           double Variance,
                           double Skewness,
                           double ExcessKurtosis,
                           double p_min)
{
    MultipleTests pMoments("Moments",
                           "check against expected");
    //get the sample

//check momentsn
//const double Mean=0.5;
//const double Variance=1./12;
const double StdDev=std::sqrt(Variance);
//const double Skewness=0;
//const double ExcessKurtosis=-6./5.;
double firstMoment=0;
double secondMoment=0;
double thirdMoment=0;
double fourthMoment=0;
std::size_t n=size(sample);
for (std::size_t i=0; i<n; i++)
{
    double res=sample[i]-Mean;
    firstMoment+=res;
    secondMoment+=res*res;
    thirdMoment+=res*res*res;
    fourthMoment+=res*res*res*res;
}
double mean=firstMoment/n+Mean;
double SE=StdDev/std::sqrt(n);
double z=std::abs(mean-Mean)/SE;
double p_z=(1.-NormalCdf(z))*2;

double variance=secondMoment/n;

double chi2=secondMoment/Variance;

double p_chi2=1.-ChiSqrCdf(chi2,n);

double skewness=thirdMoment/Variance/StdDev/n;

double SD_Skewness=std::sqrt(6.*n/(n+1)/(n+3));
double z_skewness=std::abs(skewness-Skewness)/SD_Skewness;
double p_zSkw=(1.-NormalCdf(z_skewness))*2;
double excKurtosis=fourthMoment/n/Variance/Variance-3;
double SD_Kur=std::sqrt(24. * n*(n-2)*(n-3)/(1.*(n+1)*(n+1)*(n+3)*(n+5)));
double z_Kur=std::abs(excKurtosis-ExcessKurtosis)/SD_Kur;
double p_Kur=(1.-NormalCdf(z_Kur))*2;




pMoments.push_back(ElementaryTest(
                       "mean",
                       "\nexpected\t"+ToString(Mean)+
                       "\nfound   \t"+ToString(mean)+
                       "\nz=      \t"+ToString(z)+
                       "\np=      \t"+ToString(p_z)+"\n",
                       p_z>p_min));

pMoments.push_back(ElementaryTest(
                       "variance",
                       "\nexpected\t"+ToString(Variance)+
                       "\nfound   \t"+ToString(variance)+
                       "\nchi2=      \t"+ToString(chi2)+
                       "\ndf=      \t"+ToString(n)+
                       "\np=      \t"+ToString(p_chi2)+"\n",
                       (p_chi2>p_min/2)&&(p_chi2<1-p_min/2)));


pMoments.push_back(ElementaryTest(
                       "Skewness",
                       "\nexpected\t"+ToString(Skewness)+
                       "\nfound   \t"+ToString(skewness)+
                       "\nz=      \t"+ToString(z_skewness)+
                       "\np=      \t"+ToString(p_zSkw)+"\n",
                       p_zSkw>p_min));

pMoments.push_back(ElementaryTest(
                       "Kurtosis",
                       "\nexpected\t"+ToString(ExcessKurtosis)+
                       "\nfound   \t"+ToString(excKurtosis)+
                       "\nz=      \t"+ToString(z_Kur)+
                       "\np=      \t"+ToString(p_Kur)+"\n",
                       p_Kur>p_min));

return pMoments;
}





MultipleTests CheckDistribution(const Markov_LA::M_Matrix<double>& sample,
                                const std::map<double,double>& pdf,
                                double p_min)

{
    G_Test G(sample,pdf);
    std::size_t Nt=size(sample);
    MultipleTests result("G_Test",
                         "against pdf");

    std::string values;



    std::map<double,std::size_t>::const_iterator iCount= G.count().begin();
    for (std::map<double,double>::const_iterator iPdf= pdf.begin();
         iPdf!=pdf.end();
         ++iPdf, ++iCount         )
    {
        values=values+ToString(iPdf->first)+"\tE:"+ToString(iPdf->second*Nt);
        values=values+"\tF:"+ToString(iCount->second)+"\n";
    }
    values=values+"\n\nG= "+ToString(G.G());
    values=values+"\ndf= "+ToString(G.df());
    values=values+"\np= "+ToString(G.p());


    result.push_back(ElementaryTest("G_value",
                                    values,
                                    G.p()>p_min));
    return result;
}




MultipleTests CheckAutocorrelation(const Markov_LA::M_Matrix<double>& sample,
                                   std::size_t NumLags,
                                   double Mean,
                                   double Variance,
                                   double p_min){

    MultipleTests result("Autocorrelation",
                         "sum of r2");

    double chi2=0;
    std::size_t n=size(sample)-NumLags;
    Markov_LA::M_Matrix<double> r(1,NumLags);
    for (std::size_t i=0; i<NumLags; ++i)
    {
        double sumr=0;
        for (std::size_t ii=0; ii<n; ++ii)
            sumr+=(sample[ii]-Mean)*(sample[ii+i]-Mean)/Variance;
        r[i]=sumr/n;
        if (i>0)
        chi2+=r[i]*sumr;
    }
    double p=1.-ChiSqrCdf(chi2,NumLags);

    std::string values;
    for (std::size_t i=0; i<NumLags; ++i)
    {
        values=values+ToString(i)+"th r= "+ToString(r[i]);
        values=values+"\tchi2= "+ToString(r[i]*r[i]*n)+"\n";
    }
    values=values+"\n\nchi2= "+ToString(chi2);
    values=values+"\ndf= "+ToString(NumLags);
    values=values+"\np= "+ToString(p);


    result.push_back(ElementaryTest("Chi2 test",
                                    values,
                                    p>p_min));
    return result;


 }




} //end of MersenneTwister_Test

}



