#include "Markov_Mol/PatchModel.h"
#include "Markov_Mol/QMarkovModel.h"
#include "Markov_Mol/GaussianNoise.h"

namespace Markov_Mol_New
{

  PatchModel* PatchModel::clone() const
  {
    return new PatchModel(*this);
  }

  /// default constructors
  PatchModel* PatchModel::create() const
  {
    return new PatchModel();
  }





  PatchModel::~PatchModel()
  {
    delete model_;
    delete noise_;
  }



  const ABC_Markov_Model& PatchModel::Model()const{return *model_;}

  std::size_t PatchModel::ChannelsCount()const {return nChannels_;}

  double PatchModel::AverageNumberOfChannels()const {return nChannels_;}

  const ABC_noise& PatchModel::Noise()const {return *noise_;}

  ABC_noise& PatchModel::Noise() {return *noise_;}



  std::string PatchModel::ClassName()
  {
    return "Simple_Patch_Model";
  }







  PatchModel::PatchModel(const ABC_Markov_Model *model,
                         std::size_t nChannels,
                         const ABC_noise *noise):
    model_(model->clone()),
    nChannels_(nChannels),
    noise_(noise->clone())
  {
  }

  PatchModel::PatchModel():
    model_(new Q_Markov_Model()),
    nChannels_(0),
    noise_(new gaussian_noise())
  {
  }



  PatchModel::PatchModel(const PatchModel& other):
    model_(other.Model().clone()),
    nChannels_(other.nChannels_),
    noise_(other.Noise().clone())
  {
    }




  void swap(PatchModel& one, PatchModel& two)
  {
    std::swap(one.model_,two.model_);

    std::swap(one.nChannels_,two.nChannels_);
    std::swap(one.noise_,two.noise_);
    }

  Experiment_simulation PatchModel::run(const Markov_IO_New::ABC_Experiment& x,
                                        std::size_t n_replicates,
                                        double time_step, std::size_t num_steps,
                                        std::mt19937_64 &sto)const
  {
    Experiment_simulation ES(x,
                             *this,
                             n_replicates);


    //#pragma omp parallel for
    for (std::size_t i_r=0; i_r<n_replicates; i_r++)
      {
        ES.replicate(i_r);
        double x0=x.trace(0)[0].sub_step(0).x();

        Markov_state S=this->Model().start(x0,this->ChannelsCount(),sto);
        for (std::size_t itrace=0; itrace<x.num_traces(); itrace++)
          {
            x.trace(itrace);
            for (std::size_t i=0; i<x.num_measures(); i++)
              {
                //(x[i]).printSelf(std::cerr);
                std::size_t nSteps;
                if (x.dt()>time_step)
                  nSteps=std::ceil(x.dt()/time_step-0.5);
                else nSteps=1;
                nSteps=std::max(nSteps,num_steps);
                S=Model().run(x[i],S,nSteps,sto);
                double yval=S.ymean()+this->Noise().sample(x.dt(),sto);
                ES.y(yval);
                // std::cout<<"\r \t"<<i;
              };
            S=Model().run(x[x.num_measures()],S,x.dt(),sto);
          };
        std::cerr<<" "<<i_r;
      };
    return ES;
  }



}







