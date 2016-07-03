#ifndef RANDOMPULSES_H
#define RANDOMPULSES_H

#include <ostream>

#include "Markov_IO/ABC_Experiment.h"

#include "Markov_IO/x_dt.h"
#include "Markov_IO/x_step.h"
#include "Markov_IO/PulsesProgram.h"

#include "Markov_LA/Matrix.h"
#include "Markov_LA/auxiliarMath.h"

#include "Borrowed/MersenneTwister.h"


namespace Markov_IO_New
{


class Random_Pulses: public ABC_Experiment
{
public:
    virtual Random_Pulses* clone() const;

    ///virtual default constructors

    virtual Random_Pulses* create() const;

    virtual ~Random_Pulses();


    //virtual std::ostream& put(std::ostream& s) const;

    virtual std::size_t total_samples() const;

    virtual std::size_t num_replicates()const;

    virtual const Random_Pulses& replicate(std::size_t i)const;


    virtual const Random_Pulses& trace(std::size_t i)const;

    virtual const Random_Pulses& trace_interval()const;

    virtual std::size_t i_trace()const;

    virtual std::size_t num_traces() const;

    virtual std::size_t i_sample()const;

    virtual const Random_Pulses& operator[](std::size_t i)const;

    virtual const Random_Pulses& operator++()const;

    virtual std::size_t num_measures()const;

    virtual double t()const;


    virtual double dt()const;

    virtual double x()const;

    virtual double y() const;

    virtual std::size_t num_steps()const;

    virtual const x_dt&  sub_step(std::size_t i)const;
    //    virtual Random_Pulses& set_max_x_trace(double new_x)
    //    {
    //        PP_PP.set_max_x_trace(new_x);
    //        return *this;
    //    }


    Random_Pulses(const std::string& name,
	double time_of_pulse,
		  double durpul_min,
		  double durpul_max,
		  double interval_min,
		  double interval_max,
		  bool log_scale,
		  std::vector<double> con,
		  double tracedur,
		  double trace_interval,
		  double fs,
		  double exchange,
		  double sub_step_time,
		  Borrowed::MersenneTwister::MTRand& sto);


    Random_Pulses();



    Random_Pulses(const Random_Pulses& other);

    friend void swap(Random_Pulses& one,Random_Pulses& other);



    static std::string ClassName();
    virtual std::string myClass()const {return ClassName();}



private:
    std::string name_;
    double ton_d;
    double durpul_min_d;
    double durpul_max_d;
    double interval_min_d;
    double interval_max_d;
    bool log_scale_b;
    std::vector<double> con_M;
    double tracedur_d;
    double trace_interval_d;
    double fs_d;
    double exchange_d;
    double sub_step_time_d;
    Pulses_program PP_PP;

    };

void swap(Random_Pulses& one,Random_Pulses& other);
}



#include <ostream>

#include "Markov_IO/ABC_Experiment.h"

#include "Markov_IO/x_dt.h"
#include "Markov_IO/x_step.h"
#include "Markov_IO/PulsesProgram.h"

#include "Markov_LA/Matrix.h"
#include "Markov_LA/auxiliarMath.h"

#include "Borrowed/MersenneTwister.h"
#include "Markov_IO/ClassDescription.h"


namespace Markov_IO
{


class Random_Pulses: public ABC_Experiment
{
public:
    virtual Random_Pulses* clone() const;

    ///virtual default constructors

    virtual Random_Pulses* create() const;

    virtual ~Random_Pulses();


    //virtual std::ostream& put(std::ostream& s) const;

    virtual std::size_t total_samples() const;

    virtual std::size_t num_replicates()const;

    virtual const Random_Pulses& replicate(std::size_t i)const;


    virtual const Random_Pulses& trace(std::size_t i)const;

    virtual const Random_Pulses& trace_interval()const;

    virtual std::size_t i_trace()const;

    virtual std::size_t num_traces() const;

    virtual std::size_t i_sample()const;

    virtual const Random_Pulses& operator[](std::size_t i)const;

    virtual const Random_Pulses& operator++()const;

    virtual std::size_t num_measures()const;

    virtual double t()const;


    virtual double dt()const;

    virtual double x()const;

    virtual double y() const;

    virtual std::size_t num_steps()const;

    virtual const x_dt&  sub_step(std::size_t i)const;
    //    virtual Random_Pulses& set_max_x_trace(double new_x)
    //    {
    //        PP_PP.set_max_x_trace(new_x);
    //        return *this;
    //    }


    Random_Pulses(const std::string& name,
        double time_of_pulse,
                  double durpul_min,
                  double durpul_max,
                  double interval_min,
                  double interval_max,
                  bool log_scale,
                  Markov_LA::M_Matrix<double> con,
                  double tracedur,
                  double trace_interval,
                  double fs,
                  double exchange,
                  double sub_step_time,
                  Borrowed::MersenneTwister::MTRand& sto);


    Random_Pulses();



    Random_Pulses(const Random_Pulses& other);

    friend void swap(Random_Pulses& one,Random_Pulses& other);


    virtual ClassDescription GetDescription()const;

    virtual bool LoadFromDescription(const ClassDescription& classDes);

    static std::string ClassName();

    virtual std::string id()const;
    virtual std::string myClass()const;


private:
    std::string name_;
    double ton_d;
    double durpul_min_d;
    double durpul_max_d;
    double interval_min_d;
    double interval_max_d;
    bool log_scale_b;
    Markov_LA::M_Matrix<double> con_M;
    double tracedur_d;
    double trace_interval_d;
    double fs_d;
    double exchange_d;
    double sub_step_time_d;
    Pulses_program PP_PP;

    };

void swap(Random_Pulses& one,Random_Pulses& other);
}



#endif // RANDOMPULSES_H
