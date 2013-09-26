#include "Markov_IO/experiment2.h"
#include "Markov_LA/Matrix.h"
#include "Markov_LA/matrixRand.h"

#include "Markov_Mol/QMarkovModel.h"
#include "Markov_Mol/GaussianNoise.h"
#include "Markov_Mol/MarkovSimulator.h"
#include "Markov_Mol/PatchModel.h"

#include "Markov_Bay/MarkovLikelihood.h"
#include "Markov_Bay/MacroDRStep.h"
#include "Markov_Bay/MacroRStep.h"
#include "Markov_Bay/MacroNRStep.h"
#include "Markov_Bay/MarkovOptim.h"


#include "Markov_IO/SinglePulses.h"

using Markov_LA::M_Matrix;
using Markov_Mol::gaussian_noise;
using Markov_Mol::Markov_Simulator;
using Markov_Mol::Experiment_simulation;
using Markov_Mol::Q_Markov_Model;
using Markov_LA::Rand;


using Markov_Bay::Macro_DR_step;
using Markov_Bay::Macro_NR_step;
using Markov_Bay::Macro_R_step;
using Markov_Bay::Markov_Likelihood;
using Markov_Bay::Markov_Optim;


using Markov_IO::Single_Pulses;

void run_experiment2()
{
 M_Matrix<double> g("0 \n  1 \n  0 \n ");

     M_Matrix<double> Q(
        "0   500   0 \n \
          200  0  100 \n \
           0   50  0  \n ");

  M_Matrix<std::size_t> a("0   1   1  \n ");

     Q_Markov_Model M("Moffatt 2007",Q,g,a,1.0);

    std::cerr<<M;
 //   M_Matrix<double> con("100 1000 5000 10000\n");
     M_Matrix<double> con;

     double fs=5e3;

     Single_Pulses SP("200_us",
		 0.01,//time of pulse
                     0.02,//pulse_duration
                     con,// pulse_concentration
                     0.02,//control_duration
                     1,//control_concentration
                     0.04,//trace_duration
                     2.0,//trace_interval_
                     fs,//fs
                     0,//time_to_exchange
                     1.0/50e3);//sub_step_time


     Borrowed::MersenneTwister::MTRand sto(
	     Borrowed::MersenneTwister::seedinit(0));
    gaussian_noise noise("noi",1.0,50e3,&sto);

    std::size_t Nch=10000;
    Markov_Simulator Sim(Markov_Mol::PatchModel("pa", M,Nch,noise,sto),0.01/fs,0);
    Experiment_simulation E;
    E=Sim.run(SP,100);
   std::cout<<E;
   std::ofstream f;
   // f.open ("data.txt");
   // f<<E;
  //  f.close();
//  Macro_R_step  MacroRTA(M,Nch,noise,true,true);
   Markov_Bay::Macro_DR_step  MacroDRTAZ(M,Nch,noise,true,true);
    Macro_R_step  MacroRZ(M,Nch,noise,false,true);

    Macro_DR_step  MacroDRTANZ(M,Nch,noise,true,false);
    Macro_R_step  MacroRNZ(M,Nch,noise,false,false);


    //  Macro_NR_step  MacroNR(M,Nch,noise,false);
  //  Macro_NR_step  MacroNRTA(M,Nch,noise,true);
    Markov_Likelihood  MDRZTA(MacroDRTAZ,E);
    Markov_Likelihood  MRZ(MacroRZ,E);

    Markov_Likelihood  MDRNZTA(MacroDRTANZ,E);
    Markov_Likelihood  MRNZ(MacroRNZ,E);

    //Markov_Likelihood  MRTA(MacroRTA,E);
  //  Markov_Likelihood  MNR(MacroNR,E);
  //  Markov_Likelihood  MNRTA(MacroNRTA,E);

    M_Matrix<double> logbeta0=MDRZTA.logbeta();
//     std::cout<< "\nbeta \n"<<logbeta0;

    M_Matrix<double> b2=logbeta0+(Rand(logbeta0,0)-0.5)*2.;
   // std::cout<<"\n  MDRTA(logbeta0)\n"<<MDRTA(logbeta0);
    std::cout<<" \ndispersion in logbeta +- 0.5\n";

  // std::cout<<"\n  MDRTA(b2)\n"<<b2<<" "<<MDRTA(b2);
      Markov_Optim<Markov_Likelihood>  OMRZ(MRZ,logbeta0);
      Markov_Optim<Markov_Likelihood>  OMRZ_2(MRZ,b2);

      Markov_Optim<Markov_Likelihood>  OMDRZTA(MDRZTA,logbeta0);
     Markov_Optim<Markov_Likelihood>  OMDRZTA_2(MDRZTA,b2);

     Markov_Optim<Markov_Likelihood>  OMRNZ(MRNZ,logbeta0);
     Markov_Optim<Markov_Likelihood>  OMRNZ_2(MRNZ,b2);

     Markov_Optim<Markov_Likelihood>  OMDRNZTA(MDRNZTA,logbeta0);
    Markov_Optim<Markov_Likelihood>  OMDRNZTA_2(MDRNZTA,b2);





      std::cout<<"\nOMDRZTA_2.fmin(b2,Markov_Optim<Markov_Likelihood>::BFGS);\n";
      M_Matrix<double> betaDTAZ_BFGS_2=OMDRZTA_2.fmin(b2,Markov_Optim<Markov_Likelihood>::BFGS);
      //press_any_key_to_continue();
      M_Matrix<double> betaDTAZ_BFGS=OMDRZTA.fmin(logbeta0,Markov_Optim<Markov_Likelihood>::BFGS);
      //press_any_key_to_continue();
      M_Matrix<double> betaDTAZ_BFGS_3=OMDRZTA.fmin(b2,Markov_Optim<Markov_Likelihood>::BFGS);

       M_Matrix<double> betaMRZ_BFGS=OMRZ.fmin(logbeta0,Markov_Optim<Markov_Likelihood>::BFGS);
      //press_any_key_to_continue();
      M_Matrix<double> betaMRZ_BFGS_2=OMRZ_2.fmin(b2,Markov_Optim<Markov_Likelihood>::BFGS);

      M_Matrix<double> betaDTANZ_BFGS=OMDRNZTA.fmin(logbeta0,Markov_Optim<Markov_Likelihood>::BFGS);
      //press_any_key_to_continue();
      M_Matrix<double> betaDTANZ_BFGS_2=OMDRNZTA_2.fmin(b2,Markov_Optim<Markov_Likelihood>::BFGS);
      //press_any_key_to_continue();
      M_Matrix<double> betaMRNZ_BFGS=OMRNZ.fmin(logbeta0,Markov_Optim<Markov_Likelihood>::BFGS);
      //press_any_key_to_continue();
      M_Matrix<double> betaMRNZ_BFGS_2=OMRNZ_2.fmin(b2,Markov_Optim<Markov_Likelihood>::BFGS);
      //



    double LL_DRZTA=MDRZTA(betaDTAZ_BFGS);
    std::cout<< "\n MDRZTA \n"<<MDRZTA.logL()<<" expected  \t"<<MDRZTA.elogL()<<"diff \t"<<MDRZTA.logL()-MDRZTA.elogL()<<" sqrt(N)"<<sqrt(MDRZTA.nsamples());

    double LL_DRZTA_2=MDRZTA(betaDTAZ_BFGS_2);
    std::cout<< "\n MDRZTA 2 \n"<<MDRZTA.logL()<<" expected  \t"<<MDRZTA.elogL()<<"diff \t"<<MDRZTA.logL()-MDRZTA.elogL()<<" sqrt(N)"<<sqrt(MDRZTA.nsamples());


    double LL_MRZ=MRZ(betaMRZ_BFGS);
    std::cout<< "\n MRZ 2 \n"<<MRZ.logL()<<" expected  \t"<<MRZ.elogL()<<"diff \t"<<MRZ.logL()-MRZ.elogL()<<" sqrt(N)"<<sqrt(MRZ.nsamples());


    double LL_MRZ_2=MRZ(betaMRZ_BFGS_2);


    double LL_DRNZTA=MDRNZTA(betaDTANZ_BFGS);

    double LL_DRNZTA_2=MDRNZTA(betaDTANZ_BFGS_2);

    double LL_MRNZ=MRNZ(betaMRNZ_BFGS);

    double LL_MRNZ_2=MRNZ(betaMRNZ_BFGS_2);



     std::cout<<" \n\nbeta  "<<exp10(logbeta0);
     std::cout<<" \n\nb2  "<<exp10(b2);

     std::cout<<" \n\nbeta betaDTAZ_BFGS\n "<<exp10(betaDTAZ_BFGS)<<exp10(betaDTAZ_BFGS-logbeta0);
     std::cout<<"\n LL\t"<<LL_DRZTA<<OMDRZTA;

    std::cout<<" \n\nbeta betaDTANZ_BFGS\n "<<exp10(betaDTANZ_BFGS)<<exp10(betaDTANZ_BFGS-logbeta0);
    std::cout<<"\n LL"<<LL_DRNZTA<<"\t dif LL_DRNZTA-LL_DRZTA=\t"<<LL_DRNZTA-LL_DRZTA<<OMDRNZTA;;

    std::cout<<" \n\nbeta betaMRZ_BFGS\n "<<exp10(betaMRZ_BFGS)<<exp10(betaMRZ_BFGS-logbeta0);
    std::cout<<"\n LL"<<LL_MRZ<<"\tdif LL_MRZ-LL_DRZTA=\t"<<LL_MRZ-LL_DRZTA<<OMRZ;
    std::cout<<" \n\nbeta betaMRNZ_BFGS\n "<<exp10(betaMRNZ_BFGS)<<exp10(betaMRNZ_BFGS-logbeta0);
    std::cout<<"\n LL"<<LL_MRNZ<<"\tdif LL_MRNZ-LL_MRZ\t"<<LL_MRNZ-LL_MRZ<<OMRNZ;


    std::cout<<" \n\nbeta betaDTAZ_BFGS 2\n "<<exp10(betaDTAZ_BFGS_2)<<exp10(betaDTAZ_BFGS_2-betaDTAZ_BFGS);
    std::cout<<"\n LL"<<LL_DRZTA_2<<"\tdif LL_DRZTA_2-LL_DRZTA\t"<<LL_DRZTA_2-LL_DRZTA<<OMDRZTA_2;

    std::cout<<" \n\nbeta betaDTANZ_BFGS 2\n "<<exp10(betaDTANZ_BFGS_2);
    std::cout<<exp10(betaDTANZ_BFGS_2-betaDTANZ_BFGS);
    std::cout<<"\n LL"<<LL_DRNZTA_2<<"\tdif LL_DRZTA_2-LL_DRNZTA\t"<<LL_DRZTA_2-LL_DRNZTA<<OMDRNZTA_2;

    std::cout<<" \n\nbeta betaMRZ_BFGS 2\n "<<exp10(betaMRZ_BFGS_2)<<exp10(betaMRZ_BFGS_2-betaMRZ_BFGS);
    std::cout<<"\n LL"<<LL_MRZ_2<<"\tdif LL_MRZ_2-LL_MRZ\t"<<LL_MRZ_2-LL_MRZ<<OMRZ_2;

    std::cout<<" \n\nbeta betaMRNZ_BFGS 2\n "<<exp10(betaMRNZ_BFGS_2)<<exp10(betaMRNZ_BFGS_2-betaMRNZ_BFGS);
    std::cout<<"\n LL"<<LL_MRNZ_2<<"\tdif LL_MRZ_2-LL_MRZ\t"<<LL_MRNZ_2-LL_MRNZ<<OMRNZ_2;





};


