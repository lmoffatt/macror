#ifndef PULSESPROGRAM_H
#define PULSESPROGRAM_H

#include <iostream>
#include <vector>
#include <cstddef>

#include "Markov_IO/ABC_Experiment.h"
#include "Markov_IO/x_dt.h"
#include "Markov_IO/x_step.h"
#include "Markov_IO/PulsesTrace.h"

#include "Markov_LA/Matrix.h"

namespace Markov_IO
{


class Pulses_program: public ABC_Experiment
{
public:
    virtual Pulses_program* clone() const;

    virtual Pulses_program* create() const;

    virtual ~Pulses_program();


    virtual std::ostream& put(std::ostream& s) const;


    virtual std::size_t total_samples() const;

    virtual std::size_t num_replicates()const;

    virtual const Pulses_program& replicate(std::size_t i)const;


    virtual const Pulses_program& trace(std::size_t i)const;

    virtual const Pulses_program& trace_interval()const;

    virtual std::size_t i_trace()const;


    virtual std::size_t num_traces() const;


    virtual std::size_t i_sample()const;


    virtual const Pulses_program& operator[](std::size_t i)const;

    virtual const Pulses_program& operator++()const;

    virtual std::size_t num_measures()const;

    virtual double t()const;

    virtual double dt()const;

    virtual double x()const;

    virtual double y() const;

    virtual std::size_t num_steps()const;

    virtual const x_dt&  sub_step(std::size_t i)const;

    Pulses_program(const std::string& name,
		   const std::vector<Pulses_trace>&
		   vector_of_traces,
		   const Markov_LA::M_Matrix<std::size_t>&
		   sequence_of_traces,
		   const Markov_LA::M_Matrix<double>&
		   concentration_of_each_trace);

    Pulses_program(const std::string& name,
           std::size_t numberTraces,
           std::size_t numberRepetitions);


    Pulses_program();


    Pulses_program(const Pulses_program& other);




    virtual ClassDescription GetDescription()const;

    virtual bool LoadFromDescription(const ClassDescription& classDes);

    static std::string ClassName();
    static std::vector<std::string> parentClasses();
    static std::vector<std::string> childClasses();
    virtual bool amIAbstract()const;
    virtual std::vector<std::string>  myParentClasses()const;
    virtual std::vector<std::string>  myChildClasses()const;

    virtual std::string myName()const;
    virtual std::string myClass()const;



private:
    std::string name_;
    std::vector<Pulses_trace> traces_v;
    Markov_LA::M_Matrix<std::size_t> to_i_trace_v;
    Markov_LA::M_Matrix<double> pulse_concentration_M;
    std::size_t total_samples_u;
    mutable std::size_t itrace_u;
    mutable Pulses_trace run_trace_T;

    std::string dirName_;
    std::string author_;
    std::string date_;
    std::string id_;
};

}
#endif // PULSESPROGRAM_H
