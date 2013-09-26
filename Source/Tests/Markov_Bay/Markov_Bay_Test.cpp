#include "Tests/Markov_Bay/Markov_Bay_Test.h"

#include "Markov_Bay/MacroDRStep.h"
#include "Markov_Bay/MacroRStep.h"
#include "Markov_Bay/MacroNRStep.h"
#include "Markov_LA/matrixInverse.h"
#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixOperators.h"
#include "Markov_LA/matrixSum.h"
#include "Markov_LA/matrixAritmetic.h"

#include "Markov_IO/x_step.h"

#include "Tests/Markov_Bay/MultivariateGaussian_Test.h"

#include "Tests/MersenneTwister_Test.h"

namespace Markov_Test
{

namespace Markov_Bay_Test
{

using namespace Markov_LA;

    Markov_Bay_Test::Markov_Bay_Test(const Markov_Mol::ABC_PatchModel& patch):
        patch_(patch){}

     MultipleTests Markov_Bay_Test::All_Tests()
     {
         MultipleTests result("namespace Markov_Bay",
                       "all tests");


         result.push_back(MersenneTwister_Test::MersenneTwister_Test(0).AllTests());


         M_Matrix<double> Mean("2  3   4 7  4");

         Mean=Mean/totalsum(Mean);

         M_Matrix<double> SD("0.2  0.13   0.24 0.23  0.04");

        SD=SD/10.;


         M_Matrix<double> Corr(" 1   -0.2  0.02  0.07 0.02 \n"
                              "  -0.2   1   0.05  0.032  0.2 \n"
                              " 0.02   0.05   1  -0.1  0.01 \n"
                              "  0.07    0.032   -0.1  1  0.09 \n"
                              "  0.02   0.2     0.01  0.09  1 ");


         M_Matrix<double> Cov=diag(SD)*Corr*diag(SD);



         MultivariateGaussian g(Mean,inv(Cov),0);

         result.push_back(MultivariateGaussian_Test(g).AllTests());


          // we can test everything with Macro_DR_step
         result.push_back(ABC_Markov_Likelihood_step_Test(
                              Macro_DR_step(patch_,true)).AllTests());



         result.push_back(ABC_Markov_Likelihood_step_Test(
                              Macro_DR_step(patch_,false)).AllTests());


         std::cerr<<"llega ";
         // we have to be more carefull with Macro_R_step

         // first build xstep
         double agonist_concentration=1;


         double dt_short=1e-4;
         double dt_long=1e-2;
         std::size_t numSamples=10000;
         std::size_t numSteps=100;

         double NumChannels_few=100;
         double NumChannels_many=1000;

         double pmin=1e-3;
         Markov_IO::x_step xst_short_few,xst_short_few2;
         Markov_IO::x_step xst_long_many;

         std::size_t n=1;
         for (std::size_t i=0; i<n; i++)
         {
             xst_short_few.push_back(dt_short/n,agonist_concentration,0.0);
             xst_long_many.push_back(dt_long/n,agonist_concentration,0.0);
       //      xst.push_back(dt/n,agonist_concentration*0,0.0);
         }

        xst_short_few2=xst_short_few;
         // now simulate the outcome

         // set the Number of channels right

         Markov_IO::Parameters par_few=patch_.get_parameters();

         par_few[Markov_Mol::num_channels_label()]=NumChannels_few;
         Markov_Mol::ABC_PatchModel* patch_few=patch_.clone();
         patch_few->apply_parameters(par_few);

         Markov_IO::Parameters par_many=patch_.get_parameters();

         par_many[Markov_Mol::num_channels_label()]=NumChannels_many;
         Markov_Mol::ABC_PatchModel* patch_many=patch_.clone();
         patch_many->apply_parameters(par_many);



         Borrowed::MersenneTwister::MTRand sto(Borrowed::MersenneTwister::seedinit(0));

         Markov_Mol::Markov_state
                 S0_few=patch_few->Model().start(0,patch_few->AverageNumberOfChannels(),sto);

         Markov_Mol::Markov_state
                 S1_short_few=patch_few->Model().run(xst_short_few,S0_few,numSteps,sto);
         patch_few->Noise().set_random_generator(&sto);

         Markov_Mol::Markov_state
                 S2_short_few=patch_few->Model().run(xst_short_few2,S1_short_few,numSteps,sto);


         Markov_Mol::Markov_state
                 S0_many=patch_few->Model().start(0,patch_many->AverageNumberOfChannels(),sto);
         Markov_Mol::Markov_state
                 S1_long_many=patch_few->Model().run(xst_long_many,S0_many,numSteps,sto);
         patch_few->Noise().set_random_generator(&sto);
         patch_many->Noise().set_random_generator(&sto);


         double yrun_short_few=S1_short_few.ymean();
         double noise_short=patch_few->Noise().sample(xst_short_few.dt());
         xst_short_few.y(yrun_short_few+noise_short);

         double noise_short2=patch_few->Noise().sample(xst_short_few.dt());
         xst_short_few.y(yrun_short_few+noise_short);

         double yrun_short_few2=S2_short_few.ymean();
         xst_short_few2.y(yrun_short_few2+noise_short2);





         double yrun_long_many=S1_long_many.ymean();
         double noise_long=patch_many->Noise().sample(xst_long_many.dt());
         xst_long_many.y(yrun_long_many+noise_long);

         std::cerr<<"llega ";

         ABC_Markov_Likelihood_step_Test  macroRAvgTest(Macro_R_step(*patch_many,true,true));
         MultipleTests pMRA("class Macro_R_step with averaging",
                       "test against many channels on long step");
         pMRA.push_back(macroRAvgTest.startInvariant(0.0));
         std::cerr<<"llega ";
         pMRA.push_back(macroRAvgTest.runInvariant(xst_long_many,numSamples,numSteps,pmin));
         std::cerr<<"llega ";
         pMRA.push_back(macroRAvgTest.classInvariant());
         std::cerr<<"llega ";

         result.push_back(pMRA);
         MultipleTests pMRNA("class Macro_R_step without averaging",
                       "test against few channels on short step");


         Macro_R_step MRNA(*patch_few,false,true);
         MRNA.start(0);
         xst_short_few.y(Markov_LA::NaN());

         MRNA.run(xst_short_few);
         ABC_Markov_Likelihood_step_Test  macroRNotAvgTest(MRNA);
         pMRNA.push_back(macroRNotAvgTest.runInvariant(xst_short_few2,numSamples,numSteps,pmin));
         std::cerr<<"llega ";
         pMRNA.push_back(macroRNotAvgTest.classInvariant());
         std::cerr<<"llega ";
         pMRNA.push_back(macroRNotAvgTest.startInvariant(0.0));
         std::cerr<<"llega ";

         result.push_back(pMRNA);


         // now for non recursive the instrumental noise has to be
        // much bigger than the channel noise
         // information gained



         return result;

     }

     Markov_Bay_Test::~Markov_Bay_Test(){}



}
}
