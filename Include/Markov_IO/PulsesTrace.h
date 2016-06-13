#ifndef PULSESTRACE_H
#define PULSESTRACE_H

#include "Markov_IO/ABC_Trace.h"
#include "Markov_IO/x_dt.h"

#include "Markov_LA/Matrix.h"


namespace Markov_IO_New
{

class Pulses_trace: public ABC_trace
{
public:
    virtual Pulses_trace* clone() const;

    virtual Pulses_trace* create() const;

     virtual ~Pulses_trace() ;

    virtual std::ostream& put(std::ostream& s) const;

    virtual std::size_t i_sample()const;

    virtual const Pulses_trace& operator++()const;

    virtual const Pulses_trace& operator[](std::size_t i_samp)const;

    virtual const Pulses_trace& trace_interval()const;

    virtual std::size_t num_measures()const;

    virtual std::size_t num_replicates()const;

    virtual const Pulses_trace& replicate(std::size_t i)const;


    virtual double t()const;

    virtual double dt()const;

    virtual double x()const;

    virtual double y() const;

    virtual std::size_t num_steps()const;

    virtual const x_dt&  sub_step(std::size_t i_sub)const;

    virtual Pulses_trace& set_max_x_trace(double new_max);

    Pulses_trace(const std::string& name,
		 const Markov_LA::M_Matrix<double>& time_of_each_concentration_change,
		 const Markov_LA::M_Matrix<double>& concentration_at_each_time,
		 double trace_duration,
		 double frequency_of_sampling,
		 double time_to_exchange,
		 double sub_step_time,
		 double time_to_next_trace);

    Pulses_trace(const std::string& name,
                 std::size_t number_of_concentration_changes);


    Pulses_trace();


    Pulses_trace(const Pulses_trace& other);

     static std::string ClassName();




private:
    std::string name_;
    /** this variables define the object */
    Markov_LA::M_Matrix<double> t_on_M;
    Markov_LA::M_Matrix<double> x_on_M;
    double tracedur_d;
    double fs_d;
    double exchange_d;
    double sub_step_time_d;
    double time_to_next_trace_d;


    /** this variables are derivations of the former*/
    Markov_LA::M_Matrix<double> dx_on_M;
    double dt_d;
    std::size_t nmeasures_u;
    std::size_t max_n_sub_steps_u;


    /** this variable defines the position on the trace */
    mutable std::size_t isample_u;

    /** these variables are defined by isample_u*/

    mutable double trun_d;
    mutable double x_d;
    mutable x_dt xdt_r;

    /** these variable determine the number of sub_steps at this position */

    mutable std::size_t i_min_pulse_u;
    mutable std::size_t i_max_pulse_u;
    mutable std::size_t n_sub_steps_u;

};


}


#include "Markov_IO/ABC_Trace.h"
#include "Markov_IO/x_dt.h"

#include "Markov_LA/Matrix.h"


namespace Markov_IO
{

class Pulses_trace: public ABC_trace
{
public:
    virtual Pulses_trace* clone() const;

    virtual Pulses_trace* create() const;

     virtual ~Pulses_trace() ;

    virtual std::ostream& put(std::ostream& s) const;

    virtual std::size_t i_sample()const;

    virtual const Pulses_trace& operator++()const;

    virtual const Pulses_trace& operator[](std::size_t i_samp)const;

    virtual const Pulses_trace& trace_interval()const;

    virtual std::size_t num_measures()const;

    virtual std::size_t num_replicates()const;

    virtual const Pulses_trace& replicate(std::size_t i)const;


    virtual double t()const;

    virtual double dt()const;

    virtual double x()const;

    virtual double y() const;

    virtual std::size_t num_steps()const;

    virtual const x_dt&  sub_step(std::size_t i_sub)const;

    virtual Pulses_trace& set_max_x_trace(double new_max);

    Pulses_trace(const std::string& name,
                 const Markov_LA::M_Matrix<double>& time_of_each_concentration_change,
                 const Markov_LA::M_Matrix<double>& concentration_at_each_time,
                 double trace_duration,
                 double frequency_of_sampling,
                 double time_to_exchange,
                 double sub_step_time,
                 double time_to_next_trace);

    Pulses_trace(const std::string& name,
                 std::size_t number_of_concentration_changes);


    Pulses_trace();


    Pulses_trace(const Pulses_trace& other);

    virtual ClassDescription GetDescription() const;

    virtual bool LoadFromDescription(
                                     const ClassDescription &classDes);
    static std::string ClassName();

    virtual std::string id()const;
    virtual std::string myClass()const;



private:
    std::string name_;
    /** this variables define the object */
    Markov_LA::M_Matrix<double> t_on_M;
    Markov_LA::M_Matrix<double> x_on_M;
    double tracedur_d;
    double fs_d;
    double exchange_d;
    double sub_step_time_d;
    double time_to_next_trace_d;


    /** this variables are derivations of the former*/
    Markov_LA::M_Matrix<double> dx_on_M;
    double dt_d;
    std::size_t nmeasures_u;
    std::size_t max_n_sub_steps_u;


    /** this variable defines the position on the trace */
    mutable std::size_t isample_u;

    /** these variables are defined by isample_u*/

    mutable double trun_d;
    mutable double x_d;
    mutable x_dt xdt_r;

    /** these variable determine the number of sub_steps at this position */

    mutable std::size_t i_min_pulse_u;
    mutable std::size_t i_max_pulse_u;
    mutable std::size_t n_sub_steps_u;

};


}


#endif // PULSESTRACE_H
