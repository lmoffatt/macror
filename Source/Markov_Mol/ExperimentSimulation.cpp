#include "Tests/AssertPlain.h"
#include "Markov_Mol/ExperimentSimulation.h"
#include "Markov_LA/auxiliarMath.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_Mol/PatchModel.h"



namespace Markov_Mol
{
  using Markov_IO::ToValue;




  Experiment_simulation*  Experiment_simulation::clone() const
  {
    return new Experiment_simulation(*this);
  }
  /// default constructors

  Experiment_simulation* Experiment_simulation::create() const
  {
    return new Experiment_simulation();
  }

  Experiment_simulation::~Experiment_simulation() {}


  std::size_t Experiment_simulation::total_samples()const
  {
    return E->total_samples()*num_replicates_u;
  };

  std::size_t Experiment_simulation::num_replicates()const
  {
    return num_replicates_u;
  };

  const Experiment_simulation& Experiment_simulation::replicate(std::size_t i)const
  {
    ASSERT_LESS(i, num_replicates());
    i_replicate_u=i;
    return *this;
  }

  const Experiment_simulation& Experiment_simulation::trace(std::size_t i)const
  {
    E->trace(i);
    return *this;
  };

  const Experiment_simulation& Experiment_simulation::trace_interval()const
  {
    E->trace_interval();
    return *this;
  };

  std::size_t Experiment_simulation::i_trace()const
  {
    return E->i_trace();
  };

  std::size_t Experiment_simulation::num_traces() const
  {
    return E->num_traces();
  };

  std::size_t Experiment_simulation::i_sample()const
  {
    return E->i_sample();
  };

  double Experiment_simulation::t()const
  {
    return E->t();
  }

  double Experiment_simulation::dt()const
  {
    return E->dt();
  };

  double Experiment_simulation::x()const
  {
    return E->x();
  };

  std::size_t Experiment_simulation::num_steps()const
  {
    return E->num_steps();
  };

  const ABC_measure_point&  Experiment_simulation::sub_step(std::size_t i)const
  {
    return E->sub_step(i);
  };

  const Experiment_simulation& Experiment_simulation::operator[](std::size_t i)const
  {
    (*E)[i];
    return *this;
  };

  const Experiment_simulation& Experiment_simulation::operator++()const
  {
    ++(*E);
    return *this;
  };

  //     const Experiment_simulation& raw_sample(std::size_t i)const
  //    {
  //        (*E).raw_sample(i);
  //        return *this;
  //    };

  std::size_t Experiment_simulation::num_measures()const
  {
    return E->num_measures();
  };

  double Experiment_simulation::y()const
  {
    if ((i_sample()<num_measures())||(num_replicates()==0))
      return y_v[E->i_trace()+E->num_traces()*i_replicate_u][E->i_sample()];
    else
      return NaN();
  };

  Experiment_simulation& Experiment_simulation::y(double new_value)
  {
    y_v[E->i_trace()+E->num_traces()*i_replicate_u][E->i_sample()]=new_value;
    return *this;
  }

  const ABC_Markov_Model& Experiment_simulation::model()const
  {
    return this->patch_->Model();
  }

  const ABC_noise& Experiment_simulation::noise()const
  {
    return this->patch_->Noise();
  }

  std::size_t Experiment_simulation::Nchannels()const
  {
    return this->patch_->ChannelsCount();
  }


  Experiment_simulation::Experiment_simulation():
    y_v(),
    E(0),
    patch_(),
    num_replicates_u(0),
    i_replicate_u(0) {}

  Experiment_simulation::Experiment_simulation(
      const std::string& name,
      const ABC_Experiment& experiment,
      const ABC_PatchModel& patch,
      std::size_t number_of_replicates):
    name_(name),
    y_v(),
    E(&experiment),
    patch_(&patch),
    num_replicates_u(number_of_replicates),
    i_replicate_u(0)

  {
    for (std::size_t j=0; j<num_replicates_u; j++)
      {
        for (std::size_t i=0; i<E->num_traces(); i++)
          {
            E->trace(i);
            std::vector<double> y_d(E->num_measures());
            y_v.push_back(y_d);
          }
      }
  }

  Experiment_simulation& Experiment_simulation::operator=(
      const Experiment_simulation& other)
  {
    if (this != &other)
      {
        Experiment_simulation tmp(other);
        swap(*this, tmp);
      }
    return *this;
  }

  void swap(Experiment_simulation& one, Experiment_simulation& other)
  {
    std::swap(one.name_,other.name_);
    std::swap(one.E,other.E);
    std::swap(one.i_replicate_u,other.i_replicate_u);
    std::swap(one.patch_,other.patch_);
    std::swap(one.y_v,other.y_v);
  }




  ClassDescription Experiment_simulation::GetDescription()const
  {
    ClassDescription desc(myClass(),mySuperClass());;
    desc.push_back("name",name_);

    desc.push_back("Experiment",*E);
    desc.push_back("Patch_Model",*patch_);
    desc.push_back("number_of_replicates",num_replicates_u);
    return desc;
  }

  std::string Experiment_simulation::ClassName()
  {
    return "Experiment_simulation";
  }



  std::string Experiment_simulation::id()const
  {
    return name_;
  };

  std::string Experiment_simulation::myClass()const
  {
    return ClassName();
  }




  bool Experiment_simulation::LoadFromDescription(const Markov_IO::ClassDescription& classDes)
  {
    if (classDes.ClassName()!=myClass())
      return false;
    std::string name;
    if (!ToValue(classDes["name"],name))
      return false;



    Markov_IO::ABC_Experiment* experiment;
    if (!ToValue(classDes["Experiment"],experiment))
      return false;

    ABC_PatchModel* patch;
    if (!ToValue(classDes["Patch_Model"],patch))
      return false;

    std::size_t number_of_replicates;
    if (!ToValue(classDes["number_of_replicates"],number_of_replicates))
      return false;

    *this=Experiment_simulation(name,
                                *experiment,
                                *patch,
                                number_of_replicates);
    return true;
  }

  const ABC_PatchModel& Experiment_simulation::Patch()const
  {
    return *patch_;
  }


}
