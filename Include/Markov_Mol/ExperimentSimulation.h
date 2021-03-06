#ifndef EXPERIMENTSIMULATION_H
#define EXPERIMENTSIMULATION_H

#include <cstddef>
#include <vector>

#include "Markov_IO/ABC_Experiment.h"

#include "Markov_Mol/ABC_MarkovModel.h"
#include "Markov_Mol/ABC_Noise.h"
#include "Markov_LA/auxiliarMath.h"
//#include "Markov_Mol/PatchModel.h"

namespace Markov_Mol_New
{

    using Markov_IO_New::ABC_measure_point;
    using Markov_LA::NaN;
    using namespace Markov_IO_New;


    class ABC_PatchModel;

    class Experiment_simulation:public Markov_IO_New::ABC_Experiment
{
public:

    virtual std::string myClass()const override {return ClassName();}
    virtual Experiment_simulation* clone() const override;

    virtual Experiment_simulation* create() const override;
    virtual ~Experiment_simulation();
    virtual std::size_t total_samples()const override;
    virtual std::size_t num_replicates()const override;
    virtual const Experiment_simulation& replicate(std::size_t i)const override;
    virtual const Experiment_simulation& trace(std::size_t i)const override;
    virtual const Experiment_simulation& trace_interval()const override;
    virtual std::size_t i_trace()const override;
    virtual std::size_t num_traces() const override;
    virtual std::size_t i_sample()const override;
    virtual double t()const override;
    virtual double dt()const override;
    virtual double x()const override;
    virtual std::size_t num_steps()const override;
    virtual const ABC_measure_point&  sub_step(std::size_t i)const override;
    virtual const Experiment_simulation& operator[](std::size_t i)const override;
    virtual const Experiment_simulation& operator++()const override;

    virtual std::size_t num_measures()const override;
    virtual double y()const override;
    virtual Experiment_simulation& y(double new_value);

    virtual const ABC_Markov_Model& model()const;
    virtual const ABC_noise& noise()const;
    virtual std::size_t Nchannels()const;
    virtual const ABC_PatchModel& Patch()const;


//    virtual std::ostream& put(std::ostream& s) const;
    Experiment_simulation();

    Experiment_simulation(const ABC_Experiment& E_,
			  const ABC_PatchModel& patch,
			  std::size_t num_replicate=1);

    Experiment_simulation& operator=(const Experiment_simulation& other);







    static std::string ClassName();


    friend void swap(Experiment_simulation& one, Experiment_simulation& other);




private:
    typedef std::vector< double>  trace_v;
    std::vector<trace_v> y_v;
    const ABC_Experiment* E;
    const ABC_PatchModel* patch_;
    std::size_t num_replicates_u;
    mutable std::size_t i_replicate_u;
};





}






#endif // EXPERIMENTSIMULATION_H
