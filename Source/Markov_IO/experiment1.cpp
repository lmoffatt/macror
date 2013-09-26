#include "Markov_IO/experiment1.h"
#include "Markov_IO/SinglePulses.h"



#include "Markov_LA/matrixRand.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/Matrix.h"
#include "Markov_LA/matrixRand.h"

#include "Markov_Mol/QMarkovModel.h"
#include "Markov_Mol/GaussianNoise.h"
#include "Markov_Mol/MarkovSimulator.h"

#include "Markov_Bay/MarkovLikelihood.h"
#include "Markov_Bay/MacroDRStep.h"
#include "Markov_Bay/MacroRStep.h"
#include "Markov_Bay/MacroNRStep.h"
#include "Markov_Bay/MarkovOptim.h"
using Markov_LA::M_Matrix;
using Markov_Mol::gaussian_noise;
using Markov_Mol::Markov_Simulator;
using Markov_Mol::Experiment_simulation;
using Markov_Mol::Q_Markov_Model;


using Markov_Bay::Macro_DR_step;
using Markov_Bay::Macro_NR_step;
using Markov_Bay::Macro_R_step;
using Markov_Bay::Markov_Likelihood;
using Markov_Bay::Markov_Optim;


using Markov_IO::Single_Pulses;




void run_experiment1()
{
    Markov_LA::M_Matrix<double> g("0 \n  1 \n  0 \n ");

    Markov_LA::M_Matrix<double> Q(
	    "0   500   0 \n  \
             200  0  100 \n  \
             0   50  0  \n   " );

    Markov_LA::M_Matrix<std::size_t> a("0   1   1  \n ");

    Q_Markov_Model M("moffatt 2007",Q,g,a,1.0);

    std::cerr<<M;
    //   Markov_LA::M_Matrix<double> con("100 1000 5000 10000\n");
    Markov_LA::M_Matrix<double> con;

    double fs=50e3;

    Single_Pulses SP("200_us",
		     1./fs,//time of pulse
                     0.04,//pulse_duration
                     con,// pulse_concentration
                     0.04,//control_duration
                     1,//control_concentration
                     0.04,//trace_duration
                     2.0,//trace_interval_
                     fs,//fs
                     0,//time_to_exchange
                     1.0/50e3);//sub_step_time


    Borrowed::MersenneTwister::MTRand sto(Borrowed::MersenneTwister::seedinit(0));
    gaussian_noise noise("noise",1.0,50e3,&sto);

    std::size_t Nch=100;
    Markov_Simulator Sim(Markov_Mol::PatchModel("Pa",M,Nch,noise,sto),0.01/fs,0);
    Experiment_simulation E;
    E=Sim.run(SP,1);
    // std::cout<<E;
    std::ofstream f;
    //f.open ("d3.txt");
    //f<<E;
    //f.close();
    Macro_R_step  MacroRTA(M,Nch,noise,true,true);
    Macro_DR_step  MacroDRTA(M,Nch,noise,true,true);

    Macro_R_step  MacroR(M,Nch,noise,false,true);
    Macro_NR_step  MacroNR(M,Nch,noise,false);
    Macro_NR_step  MacroNRTA(M,Nch,noise,true);
    Markov_Likelihood  MDRTA(MacroDRTA,E);
    Markov_Likelihood  MRTA(MacroRTA,E);

    Markov_Likelihood  MNR(MacroNR,E);
    Markov_Likelihood  MNRTA(MacroNRTA,E);
    Markov_Likelihood  MR(MacroR,E);

    Markov_LA::M_Matrix<double> logbeta0=MDRTA.logbeta();
    //     std::cout<< "\nbeta \n"<<logbeta0;

    Markov_LA::M_Matrix<double> b2=logbeta0+(Rand(logbeta0,0)-0.5)*1.;
    // std::cout<<"\n  MDRTA(logbeta0)\n"<<MDRTA(logbeta0);
    // std::cout<<"\n  MDRTA(b2)\n"<<b2<<" "<<MDRTA(b2);
    Markov_Optim<Markov_Likelihood>  OMR(MR,logbeta0);
    Markov_Optim<Markov_Likelihood>  OMR_2(MR,logbeta0);
    //  Markov_Optim<Markov_Likelihood>  OMNRTA(MNRTA,logbeta0);
    Markov_Optim<Markov_Likelihood>  OMDRTA(MDRTA,logbeta0);
    Markov_Optim<Markov_Likelihood>  OMDRTA_2(MDRTA,logbeta0);

    Markov_Optim<Markov_Likelihood>  OMRTA(MRTA,logbeta0);

    //  Markov_LA::M_Matrix<double> betaMR=OMR.fmin(logbeta0);
    //   Markov_LA::M_Matrix<double> betaMNRTA=OMNRTA.fmin(logbeta0);
    //  std::cout<<" beta MR  "<<exp10(betaMR);

    //  press_any_key_to_continue();

    //   Markov_LA::M_Matrix<double> betaDTA2=OMDRTA.fminBFGS(b2);



    //  OMDRTA.maxfeval=10;
    //  Markov_LA::M_Matrix<double> bmin;
    //  double LLmin=infinity();
    //  for (std::size_t i=0; i<0; i++)
    //  {
    //     Markov_LA::M_Matrix<double> bout=b2+(Rand(logbeta0)-0.5)*0.5;
    //     bout=OMDRTA.fmin(bout);
    //     double LLout=MDRTA(bout);
    //     if (LLout<LLmin)
    //     {
    //         LLmin=LLout;
    //         bmin=bout;
    //     }
    //   };
    //    OMDRTA.maxfeval=10;
    //  bmin=OMDRTA.fmin(bmin);
    //
    //
    Markov_LA::M_Matrix<double> betaDTA_BFGS=OMDRTA.fmin(logbeta0,Markov_Optim<Markov_Likelihood>::BFGS);
    //press_any_key_to_continue();
    Markov_LA::M_Matrix<double> betaDTA_BFGS_2=OMDRTA_2.fmin(b2,Markov_Optim<Markov_Likelihood>::BFGS);
    //press_any_key_to_continue();
    Markov_LA::M_Matrix<double> betaMR_BFGS=OMR.fmin(logbeta0,Markov_Optim<Markov_Likelihood>::BFGS);
    //press_any_key_to_continue();
    Markov_LA::M_Matrix<double> betaMR_BFGS_2=OMR_2.fmin(b2,Markov_Optim<Markov_Likelihood>::BFGS);

    //

    //     Markov_LA::M_Matrix<double> betaDTA_TaylorLL=OMDRTA.fmin(b2,Markov_Optim<Markov_Likelihood>::TaylorLL);
    // Markov_LA::M_Matrix<double> betaDTA_FIM=OMDRTA.fmin(b2,Markov_Optim<Markov_Likelihood>::FIM);
    //  std::cout<<" beta MR  "<<exp10(betaMR);
    //  std::cout<<" betaMNRTA "<< exp10(betaMNRTA );
    //   double LL_min=MDRTA(bmin);
    //   double LL_DTA_BFGS=MDRTA(betaDTA_BFGS);
    //   double LL_DTA_TaylorLL=MDRTA(betaDTA_TaylorLL);
    //    double LL_DTA_FIM=MDRTA(betaDTA_FIM);

    //   std::cout<<" \n\n beta bmin "<< LL_min<<" \n";
    //   std::cout<<" \n\n beta betaDTA_BFGS "<< LL_DTA_BFGS<<" \n";
    //std::cout<<" beta betaDTA_TaylorLL "<<LL_DTA_TaylorLL<<" \n";
    //   std::cout<<" beta betaDTA_FIM "<<LL_DTA_FIM<<" \n";

    std::cout<<" \n\nbeta  "<<exp10(logbeta0);
    std::cout<<" \n\nb2  "<<exp10(b2);
    //  std::cout<<" \n\nbeta betaDTA_BFGS 2 "<<exp10(bmin)<<exp10(bmin-betaDTA_BFGS);
    std::cout<<" \n\nbeta betaDTA_BFGS\n "<<exp10(betaDTA_BFGS)<<exp10(betaDTA_BFGS-logbeta0);;
    std::cout<<" \n\nbeta betaMR_BFGS\n "<<exp10(betaMR_BFGS)<<exp10(betaMR_BFGS-logbeta0);;
    std::cout<<" \n\nbeta betaDTA_BFGS 2\n "<<exp10(betaDTA_BFGS_2)<<exp10(betaDTA_BFGS_2-betaDTA_BFGS);;
    std::cout<<" \n\nbeta betaMR_BFGS 2\n "<<exp10(betaMR_BFGS_2)<<exp10(betaMR_BFGS_2-betaMR_BFGS);;
    //   std::cout<<" beta betaDTA_TaylorLL " <<exp10(betaDTA_TaylorLL);
    //     std::cout<<" beta betaDTA_FIM "<< exp10(betaDTA_FIM);

    std::cout<< "\nMacroNR \n"<<MNR.logL()<<" expected  \t"<<MNR.elogL()<<"diff \t"<<MNR.logL()-MNR.elogL()<<" sqrt(N)"<<sqrt(MNR.nsamples());
    std::cout<< "\nMacroNR-TA \n"<<MNRTA.logL()<<" expected \t "<<MNRTA.elogL()<<"diff \t"<<MNRTA.logL()-MNRTA.elogL();
    std::cout<< "\nMacroR \n"<<MR.logL()<<" expected  \t"<<MR.elogL()<<"diff \t"<<MR.logL()-MR.elogL();
    std::cout<< "\nMacroR-TA\n"<<MRTA.logL()<<" expected \t "<<MRTA.elogL()<<"diff \t"<<MRTA.logL()-MRTA.elogL();
    std::cout<< "\nMacroDR-TA\n"<<MDRTA.logL()<<" expected \t "<<MDRTA.elogL()<<"diff \t"<<MDRTA.logL()-MDRTA.elogL();

    //press_any_key_to_continue();
    //  std::cout<<"\n MDRTA\n"<<MDRTA;
    //  std::cout<<"\n MRTA\n"<<MRTA;
}



