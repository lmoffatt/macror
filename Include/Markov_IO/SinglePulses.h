#ifndef SINGLEPULSES_H
#define SINGLEPULSES_H

#include "Markov_IO/ABC_Experiment.h"
#include "Markov_IO/x_dt.h"

#include "Markov_LA/Matrix.h"
#include "Markov_IO/ClassDescription.h"

namespace Markov_IO_New
{

class Single_Pulses: public ABC_Experiment
{
public:
    virtual Single_Pulses* clone() const;

    ///virtual default constructors
    virtual Single_Pulses* create() const;
    virtual ~Single_Pulses();

    virtual std::ostream& put(std::ostream& s) const;

    virtual std::size_t total_samples() const;

    virtual std::size_t num_replicates()const;

    virtual const Single_Pulses& replicate(std::size_t)const;

    //    virtual Single_Pulses& set_max_x_trace(double new_x)
    //    {

    //        return *this;

    //    };


    virtual const Single_Pulses& trace(std::size_t i)const;

    virtual const Single_Pulses& trace_interval()const;

    virtual std::size_t i_trace()const;

    virtual std::size_t num_traces() const;

    virtual std::size_t i_sample()const;

    virtual const Single_Pulses& raw_sample(std::size_t i)const;

    virtual const Single_Pulses& operator[](std::size_t i)const;

    virtual const Single_Pulses& operator++()const;

    virtual std::size_t num_measures()const;

    virtual double t()const;

    virtual double dt()const;

    virtual double x()const;

    virtual double y() const;

    virtual std::size_t num_steps()const;

    virtual const x_dt&  sub_step(std::size_t i)const;

    Single_Pulses(const std::string& name,
	double time_of_pulse,
		  double pulse_duration,
		  const Markov_LA::M_Matrix<double>& pulse_concentration,
		  double control_duration,
		  double control_concentration,
		  double trace_duration,
		  double trace_interval_,
		  double fs,
		  double time_to_exchange,
		  double sub_step_time);

    Single_Pulses();


    Single_Pulses(const Single_Pulses& other);
    friend void swap(Single_Pulses& one, Single_Pulses& other);



    static std::string ClassName();



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

    std::size_t n_traces_u;

    double dt_d;

    std::size_t nmeasures_u;
    std::size_t nsub_steps_u;
    double sub_step_time_d;

    mutable double x_d;

    mutable bool short_pulse_b;

    mutable std::size_t itrace_u;
    mutable std::size_t isample_u;
    mutable std::size_t n_sub_steps_u;
    mutable std::size_t i_sub_step_u;
    mutable double trun_d;
    mutable x_dt xdt_r;



};
void swap(Single_Pulses& one, Single_Pulses& other);
}



#include "Markov_IO/ABC_Experiment.h"
#include "Markov_IO/x_dt.h"

#include "Markov_LA/Matrix.h"
#include "Markov_IO/ClassDescription.h"

namespace Markov_IO
{

class Single_Pulses: public ABC_Experiment
{
public:
    virtual Single_Pulses* clone() const;

    ///virtual default constructors
    virtual Single_Pulses* create() const;
    virtual ~Single_Pulses();

    virtual std::ostream& put(std::ostream& s) const;

    virtual std::size_t total_samples() const;

    virtual std::size_t num_replicates()const;

    virtual const Single_Pulses& replicate(std::size_t)const;

    //    virtual Single_Pulses& set_max_x_trace(double new_x)
    //    {

    //        return *this;

    //    };


    virtual const Single_Pulses& trace(std::size_t i)const;

    virtual const Single_Pulses& trace_interval()const;

    virtual std::size_t i_trace()const;

    virtual std::size_t num_traces() const;

    virtual std::size_t i_sample()const;

    virtual const Single_Pulses& raw_sample(std::size_t i)const;

    virtual const Single_Pulses& operator[](std::size_t i)const;

    virtual const Single_Pulses& operator++()const;

    virtual std::size_t num_measures()const;

    virtual double t()const;

    virtual double dt()const;

    virtual double x()const;

    virtual double y() const;

    virtual std::size_t num_steps()const;

    virtual const x_dt&  sub_step(std::size_t i)const;

    Single_Pulses(const std::string& name,
        double time_of_pulse,
                  double pulse_duration,
                  const Markov_LA::M_Matrix<double>& pulse_concentration,
                  double control_duration,
                  double control_concentration,
                  double trace_duration,
                  double trace_interval_,
                  double fs,
                  double time_to_exchange,
                  double sub_step_time);

    Single_Pulses();


    Single_Pulses(const Single_Pulses& other);
    friend void swap(Single_Pulses& one, Single_Pulses& other);


    virtual ClassDescription GetDescription()const;

    virtual bool LoadFromDescription(const ClassDescription& classDes);

    static std::string ClassName();

    virtual std::string id()const;
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

    std::size_t n_traces_u;

    double dt_d;

    std::size_t nmeasures_u;
    std::size_t nsub_steps_u;
    double sub_step_time_d;

    mutable double x_d;

    mutable bool short_pulse_b;

    mutable std::size_t itrace_u;
    mutable std::size_t isample_u;
    mutable std::size_t n_sub_steps_u;
    mutable std::size_t i_sub_step_u;
    mutable double trun_d;
    mutable x_dt xdt_r;



};
void swap(Single_Pulses& one, Single_Pulses& other);
}
#

#endif // SINGLEPULSES_H
