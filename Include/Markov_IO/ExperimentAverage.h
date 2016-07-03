#ifndef EXPERIMENTAVERAGE_H
#define EXPERIMENTAVERAGE_H

#include <vector>


#include "Markov_IO/ABC_Experiment.h"
#include "Markov_IO/x_dt.h"
#include "Markov_IO/x_step.h"


namespace Markov_IO_New
{

class Experiment_Average: public ABC_Experiment

{

public:
    virtual Experiment_Average* clone() const;


    virtual Experiment_Average* create() const;

    virtual ~Experiment_Average();

    virtual std::size_t total_samples()const;

    virtual std::size_t num_replicates()const;

    virtual const Experiment_Average& replicate(std::size_t i)const;

    virtual const Experiment_Average& trace(std::size_t i)const;

    virtual std::size_t i_trace()const;

    virtual const Experiment_Average& trace_interval()const;

    virtual std::size_t num_traces() const;

    virtual const Experiment_Average& operator[](std::size_t i)const;

    virtual const Experiment_Average& operator++()const;

    virtual std::size_t i_sample()const;

    virtual std::size_t num_measures()const;

    virtual double t()const;

    virtual double dt()const;

    virtual double x()const;

    virtual std::size_t num_steps()const;

    virtual const x_dt&  sub_step(std::size_t i)const;


    virtual double y()const;
    //    virtual Experiment_Average& y(double new_value)=0;




    Experiment_Average();




    static std::string ClassName();
    virtual std::string myClass()const {return ClassName();}

    friend class AverageExperiment;

private:
    void update();
    std::string name_;
    const ABC_Experiment* E_;
    std::vector< std::vector< std::vector< x_step> > >   data_;
    std::vector< std::vector< std::vector< double> > >      t_;
    std::size_t total_samples_;

    mutable std::size_t i_replicate_;
    mutable std::size_t i_trace_;
    mutable std::size_t i_sample_;



};

}


#include <vector>


#include "Markov_IO/ABC_Experiment.h"
#include "Markov_IO/x_dt.h"
#include "Markov_IO/x_step.h"


#include "Markov_LA/ToleranceComparison.h"
namespace Markov_IO
{

class Experiment_Average: public ABC_Experiment

{

public:
    virtual Experiment_Average* clone() const;


    virtual Experiment_Average* create() const;

    virtual ~Experiment_Average();

    virtual std::size_t total_samples()const;

    virtual std::size_t num_replicates()const;

    virtual const Experiment_Average& replicate(std::size_t i)const;

    virtual const Experiment_Average& trace(std::size_t i)const;

    virtual std::size_t i_trace()const;

    virtual const Experiment_Average& trace_interval()const;

    virtual std::size_t num_traces() const;

    virtual const Experiment_Average& operator[](std::size_t i)const;

    virtual const Experiment_Average& operator++()const;

    virtual std::size_t i_sample()const;

    virtual std::size_t num_measures()const;

    virtual double t()const;

    virtual double dt()const;

    virtual double x()const;

    virtual std::size_t num_steps()const;

    virtual const x_dt&  sub_step(std::size_t i)const;


    virtual double y()const;
    //    virtual Experiment_Average& y(double new_value)=0;




    Experiment_Average();



    virtual ClassDescription GetDescription()const{return {};}

    virtual bool LoadFromDescription(const ClassDescription& ){return false;}

    static std::string ClassName();

    virtual std::string id()const;
    virtual std::string myClass()const;

    friend class AverageExperiment;

private:
    void update();
    std::string name_;
    const ABC_Experiment* E_;
    std::vector< std::vector< std::vector< x_step> > >   data_;
    std::vector< std::vector< std::vector< double> > >      t_;
    std::size_t total_samples_;

    mutable std::size_t i_replicate_;
    mutable std::size_t i_trace_;
    mutable std::size_t i_sample_;



};

}




#endif // EXPERIMENTAVERAGE_H
