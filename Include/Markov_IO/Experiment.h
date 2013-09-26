#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "Markov_IO/ABC_Experiment.h"
#include "Markov_IO/Trace.h"

namespace Markov_IO
{

class Experiment: public ABC_Experiment
{
public:
    virtual Experiment* clone() const;
    ///virtual default constructors
    virtual Experiment* create() const;
    virtual ~Experiment();

    static std::string ClassName();
    static std::vector<std::string> parentClasses();
    static std::vector<std::string> childClasses();
    virtual bool amIAbstract()const;
    virtual std::vector<std::string>  myParentClasses()const;
    virtual std::vector<std::string>  myChildClasses()const;

    virtual std::string myName()const;
    virtual std::string myClass()const;

    virtual std::size_t total_samples()const;

    virtual std::size_t num_replicates()const;

    virtual const Experiment& replicate(std::size_t i)const;

    virtual const Experiment& trace(std::size_t i)const;
    virtual std::size_t i_trace()const;


    virtual std::size_t num_traces() const;

    virtual const Experiment& operator[](std::size_t i)const;
    virtual const Experiment& operator++()const;

    virtual std::size_t i_sample()const;

    virtual std::size_t num_measures()const;

    virtual double t()const;
    virtual double dt()const;
    virtual double x()const;
    virtual std::size_t num_steps()const;
    virtual const ABC_measure_point&  sub_step(std::size_t i)const;

    /// gives NaN() if there are no measures
    virtual double y()const;
    virtual Experiment& y(double new_value);


    Experiment();

    Experiment(const Experiment& other);

    Experiment& operator=(const Experiment& other);

    friend void swap(Experiment& one, Experiment& other);


    Experiment(const ABC_Experiment& other);

    Experiment(const std::string& name,
	       const std::vector<Trace>& traces);


    virtual ClassDescription GetDescription()const;

    virtual bool LoadFromDescription(const ClassDescription& classDes);




  private:
    std::string name_;
    std::vector<Trace> traces_;

    std::size_t total_samples_;
    mutable std::size_t i_trace_;

};

}


#endif // EXPERIMENT_H
