#include "Markov_LA/matrixOperators.h"
#include "Markov_LA/matrixRelational.h"
#include "Markov_LA/matrixSum.h"
#include "Markov_LA/matrixInit.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_IO/x_dt.h"
#include "Markov_IO/x_step.h"

#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixExp.h"
#include "Markov_LA/matrixMaxMin.h"
#include "Markov_IO/auxiliarIO.h"

#include "Markov_Bay/MacroAproxStep.h"

#include "Tests/Markov_Bay/ABC_Markov_Likelihood_step_Test.h"


#include "Tests/ElementaryTest.h"


namespace Markov_Test
{
namespace Markov_Bay_Test
{
using namespace Markov_LA;
using namespace Markov_IO;
  std::string ABC_Markov_Likelihood_step_Test::TestName()
  {
    return "Markov_Likelihood_step_Test";
  }

   std::string ABC_Markov_Likelihood_step_Test::myTest()const
  {
    return TestName();
  }


  MultipleTests ABC_Markov_Likelihood_step_Test::classInvariant()const
{
    MultipleTests results("ClassDescription ",
                          "Class Invariant");
    results.push_back(ABC_Put_Test::classInvariant());

    if (!(S_->P_mean()==0.0))
    {

        results.push_back(Probability_vector_Test(S_->P_mean()));

        results.push_back(Probability_Covariance_Test(S_->P_cov()));

        results.push_back(LogL_Test_());
    }

    results.push_back(Model_Test_());


    return results;


}

MultipleTests ABC_Markov_Likelihood_step_Test::LogL_Test_()const
{
    MultipleTests results("LogLikelihood",
                          "Invariants");

    if (!(Markov_LA::isNaN(S_->plogL())))
    {

        ToleranceComparison<double> T;
        double pLogL=-0.5*log(2*PI*S_->y_var())-
                0.5*(S_->y()-S_->y_mean())*(S_->y()-S_->y_mean())/S_->y_var();
        results.push_back(
                    ElementaryTest(
                        "logL",
                        "calculation using y ymean yvar\n"
                        "given \t"+ToString(S_->plogL())+
                        "\ncalculated \t"+ToString(pLogL)+"\n",
                        T.isEqual(S_->plogL(),pLogL)));


        results.push_back(ElementaryTest(
                              "ystd",
                              "Equals sqrt yvar"
                              "nvar\t"+ ToString(S_->y_var())+
                              "nstd*std\t"+ToString(S_->y_std()*S_->y_std()),
                              T.isEqual(S_->y_var(),S_->y_std()*S_->y_std())));

        double	eplogL=-0.5*(1+log(2*PI*S_->y_var()));
        results.push_back(ElementaryTest("expected LogLikelihood",
                                         "Check calculation",
                                         T.isEqual(S_->eplogL(),eplogL)));
    }

    return results;
}


MultipleTests ABC_Markov_Likelihood_step_Test::Model_Test_()const
{
    MultipleTests results("Patch model",
                          "Invariants");
    results.push_back(ElementaryTest("Has the right channel model",
                      "both path are the same",
                      &S_->model()==&S_->patch().Model()));

    results.push_back(ElementaryTest("Has the right noise",
                      "both path are the same",
                      S_->noise()==S_->patch().Noise()));

    results.push_back(ElementaryTest("Has the number of channels",
                      "both path are the same",
                      S_->N_channels()==S_->patch().AverageNumberOfChannels()));

    return results;


}



ABC_Markov_Likelihood_step_Test::
ABC_Markov_Likelihood_step_Test(const ABC_Markov_Likelihood_step& sample):
    ABC_Put_Test(sample),
    S_(sample.clone())
{}

ABC_Markov_Likelihood_step_Test::~ABC_Markov_Likelihood_step_Test()
{}


 MultipleTests ABC_Markov_Likelihood_step_Test::
 startInvariant(double x){
     MultipleTests results("start("+Markov_IO::ToString(x)+")",
                           "method invariants");

     S_->start(x);

     results.push_back(ElementaryTest(
                           "Pmean",
                           "Equal to Peq",
                           S_->P_mean()==S_->model().Peq(x)));

     M_Matrix<double> P_cov=diag(S_->P_mean())-
             TranspMult(S_->P_mean(),S_->P_mean());

     results.push_back(ElementaryTest(
                           "Pcov",
                           "Equal to diag(P_mean())-"
                           "TranspMult(P_mean()),P_mean())",
                           S_->P_cov()==P_cov));

     return results;


 }

 /**
   @post the "framed"  Likelihood_step is advanced and compared to a the
   approximation buildt by an Macro_Aprox_step object
   */

 MultipleTests ABC_Markov_Likelihood_step_Test::
 runInvariant(const Markov_IO::ABC_measure_step& Y,
              std::size_t numSamples,
              std::size_t numSteps,
              double pmin)const
 {

     MultipleTests results("ABC_Markov_Likelihood_step::run(step)",
                           "method invariants"
                           "\n Number of trials="+ToString(numSamples)+
                           "\n Number of steps="+ToString(numSteps));


     Macro_Aprox_step L(S_->parentVar(),"Macro_Aprox",*S_,numSamples,numSteps,0);

     L.run(Y);


     ElementaryTest tmpE(
                 "pLogL()",
                 " p>"+Markov_IO::ToString(pmin)+
                 "\npLogL calculated  \t"+ToString(L.TestedStep().plogL())+
                 "\npLogL approximate \t"+ToString(L.plogL())+
                 "\nchi2 value        \t"+ToString(L.Chi2_pLogL())+
                 "\n considering the square root of "+
                 ToString(numSamples)+"  trials"
                 " \n df=1 \n p="+ToString(L.Pr_pLogL())+"\n",
                 pmin<L.Pr_pLogL());

     results.push_back(tmpE);


     tmpE=ElementaryTest(
                 "y_mean()",
                 " p>"+Markov_IO::ToString(pmin)+
                 "\ny_mean() calculated \t"+ToString(L.TestedStep().y_mean())+
                 "\ny_mean() approximate \t"+ToString(L.y_mean())+"\n"
                 "\nchi2 value        \t"+ToString(L.Chi2_y_mean())+
                 " \n df=1 \n p="+ToString(L.Pr_y_mean())+"\n",
                 pmin<L.Pr_y_mean());


     results.push_back(tmpE);


     tmpE=ElementaryTest(
                 "y_var()",
                 " p>"+Markov_IO::ToString(pmin)+
                 "\ny_var calculated \t"+ToString(L.TestedStep().y_var())+
                 "\ny_var approximate \t"+ToString(L.y_var())+"\n"
                 "\nchi2 value        \t"+ToString(L.Chi2_y_var())+
                 "\n df="+ToString(numSamples)+", the number of trials"
                 "\np="+ToString(L.Pr_y_var())+"\n",
                 pmin/2<L.Pr_y_var()&&(1-pmin/2)>L.Pr_y_var());

     results.push_back(tmpE);


     double noise=L.patch().Noise().std(Y.dt());


     tmpE=ElementaryTest (
                 "P_mean()",
                 " p>"+Markov_IO::ToString(pmin)+
                 "\n P_mean calculated \n"+ToString(L.TestedStep().P_mean())+
                 "\n P_mean approximate \n"+ToString(L.P_mean())+"\n"
                 "\nchi2 value        \t"+ToString(L.Chi2_P_mean())+
                 "\n considering a number of trial hits of "+ToString(L.df())+
                 "\n ratio between instrumental noise("+ToString(noise)+
                 ") and channel noise="+
                 ToString(noise/L.TestedStep().y_std())+
                 "\n df="+ToString(L.NumVaryingStates()-1)+
                 ", the number of independent states \n"
                 "\n p="+ToString(L.Pr_P_mean())+"\n",
                 pmin<L.Pr_P_mean());

     results.push_back(tmpE);



     MultipleTests pP_cov("P_cov()",
                          "for each i,j pair"
                          " p>"+Markov_IO::ToString(pmin)
                          );
     std::size_t k=L.model().k();
     for (std::size_t i=0; i<k; ++i)
         for (std::size_t j=i;j<k; j++)
         {
             ElementaryTest t(
                         "P_cov("+
                         Markov_IO::ToString(i)+","+
                         Markov_IO::ToString(j)+")",
                         " p>"+Markov_IO::ToString(pmin)+
                         "\n calculated \t"+ToString(L.TestedStep().P_cov()(i,j))+
                         "\n approximated \t"+ToString(L.P_cov()(i,j))+"\n"
                         "\nchi2 value        \t"+ToString(L.Chi2_P_cov(i,j))+
                         "\n considering a number of trial hits of "+ToString(L.df())+
                         "\n df="+ToString(L.df()-1)+
                         ", the number of trial hits\n"
                         "\n p="+ToString(L.Pr_P_cov(i,j))+"\n",
                         (L.Pr_P_cov(i,j)>pmin/2)&&(L.Pr_P_cov(i,j)<1-pmin/2));

             pP_cov.push_back(t);
         }
     results.push_back(pP_cov);
     return results;

 }
  std::string ABC_Markov_Likelihood_step_Test::testedClass()const
 {
    return "";
 }


  MultipleTests ABC_Markov_Likelihood_step_Test::AllTests(Markov_Console::Markov_CommandManager* , const std::string )
 {
     MultipleTests result("class ABC_Markov_Likelihood_step on "+
                          S_->myClass(),
                   "All tests");

     result.push_back(classInvariant());


     double agonist_concentration=1;


     double dt=1e-4;
     std::size_t numSamples=1000;
     std::size_t numSteps=100;
     double pmin=1e-3;
     Markov_IO::x_step xst;
     std::size_t n=2;
     for (std::size_t i=0; i<n; i++)
     {
         xst.push_back(dt/n,agonist_concentration*(i+1),0.0);
         xst.push_back(dt/n,agonist_concentration*0,0.0);
     }
     Borrowed::MersenneTwister::MTRand sto(Borrowed::MersenneTwister::seedinit(0));

     Markov_Mol::Markov_state
             S0=S_->patch().Model().start(0,
                                          S_->N_channels(),
                                          sto);
     Markov_IO::x_step xst1(xst);
     Markov_Mol::Markov_state
             S1=S_->patch().Model().run(xst1,S0,numSteps,sto);
     S_->patch().Noise().set_random_generator(&sto);

    // double yrunFit=S_->y();
  //   double yrun=S1.ymean();
     double noise=S_->patch().Noise().sample(xst.dt());
     xst1.y(S1.ymean()+noise);

     result.push_back(startInvariant(0.0));
     result.push_back(runInvariant(xst1,numSamples,numSteps,pmin));
     result.push_back(classInvariant());
     S_->run(xst1);
     Markov_IO::x_step xst2(xst);
     Markov_Mol::Markov_state
     S2=S_->patch().Model().run(xst2,S1,numSteps,sto);
     noise=S_->patch().Noise().sample(xst2.dt());
     xst2.y(S2.ymean()+noise);


     //yrunFit=S_->y();
     //yrun=S2.ymean();

     result.push_back(runInvariant(xst2,numSamples,numSteps,pmin));
     result.push_back(classInvariant());
     S_->run(xst2);

     Markov_IO::x_step xst3(xst);

     Markov_Mol::Markov_state
             S3=S_->patch().Model().run(xst3,S2,numSteps,sto);
     noise=S_->patch().Noise().sample(xst3.dt());
     xst3.y(S3.ymean()+noise);
     //yrunFit=S_->y();
     //yrun=S3.ymean();

     result.push_back(runInvariant(xst3,numSamples,numSteps,pmin));
     result.push_back(classInvariant());

     return result;

 }






 MultipleTests Probability_vector_Test(const Markov_LA::M_Matrix<double> P)
 {
     MultipleTests results("Probability_vector",
                           "invariant");

     ToleranceComparison<double> tol(1e-9,1e-9);

     results.push_back(ElementaryTest("sum up one",
                                      "sum(P)==1.0"
                                      "\n P \t="+ToString(P)+
                                      "\t sum(P)-1="+ToString(totalsum(P)-1.0)+"\n",
                                      tol.isEqual(totalsum(P),1.0)));
     results.push_back(ElementaryTest("each probability is more than zero",
                                      "P>=0.0",
                                      P>=0.0));
     results.push_back(ElementaryTest("each probability is less or equal to one",
                                      "P<=1.0",
                                      P<=1.0));

     return results;


 }

 MultipleTests
 Probability_Covariance_Test(const Markov_LA::M_Matrix<double> Pcov)
 {
     MultipleTests results("Probability_variance",
                           "invariant");

     results.push_back(ElementaryTest(
                           "square",
                           "nrows()=ncols()",
                           nrows(Pcov)==ncols(Pcov)));


     return results;


 }





}


}

