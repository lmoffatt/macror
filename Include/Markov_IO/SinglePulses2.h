#ifndef SINGLEPULSES2_H
#define SINGLEPULSES2_H

#include <vector>

#include "Markov_IO/ABC_Experiment.h"
#include "Markov_IO/x_dt.h"
#include "Markov_IO/PulsesTrace.h"
#include "Markov_IO/PulsesProgram.h"

#include "Markov_LA/Matrix.h"

namespace Markov_IO
{

class Single_Pulses2: public ABC_Experiment
{
public:

    virtual Single_Pulses2* clone() const;

    virtual Single_Pulses2* create() const;
    virtual ~Single_Pulses2();

    virtual std::ostream& put(std::ostream& s) const;

    virtual std::size_t total_samples() const;

    virtual std::size_t num_replicates()const;
    virtual const Single_Pulses2& replicate(std::size_t i)const;


    virtual const Single_Pulses2& trace(std::size_t i)const;
    virtual const Single_Pulses2& trace_interval()const;
    virtual std::size_t i_trace()const;

    virtual std::size_t num_traces() const;

    virtual std::size_t i_sample()const;

    virtual const Single_Pulses2& operator[](std::size_t i)const;

    virtual const Single_Pulses2& operator++()const;

    virtual std::size_t num_measures()const;

    virtual double t()const;

    virtual double dt()const;

    virtual double x()const;

    virtual double y() const;

    virtual std::size_t num_steps()const;

    virtual const x_dt&  sub_step(std::size_t i)const;
    //    virtual Single_Pulses2& set_max_x_trace(double new_x)
    //    {
    //        PP_PP.set_max_x_trace(new_x);
    //        return *this;
    //    }


    Single_Pulses2(const std::string& name,
		   double time_of_pulse,
		   double pulse_duration,
		   const Markov_LA::M_Matrix<double> pulse_concentration,
		   double control_duration,
		   double control_concentration,
		   double trace_duration,
		   double trace_interval_,
		   double fs,
		   double time_to_exchange,
		   double sub_step_time);

    Single_Pulses2();


    Single_Pulses2(const Single_Pulses2& other);


    friend void swap(Single_Pulses2& one, Single_Pulses2& other);


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
    double ton_d;
    double durpul_d;
    Markov_LA::M_Matrix<double> con_M;
    double durcon_d;
    double concon_d;
    double tracedur_d;
    double trace_interval_d;
    double fs_d;
    double exchange_d;
    double sub_step_time_d;

    Pulses_program PP_PP;


};

void swap(Single_Pulses2& one, Single_Pulses2& other);
}
#endif // SINGLEPULSES2_H
