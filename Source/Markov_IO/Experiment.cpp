#include "Tests/AssertPlain.h"
#include "Markov_IO/Experiment.h"
#include "Markov_LA/auxiliarMath.h"
#include "Markov_IO/auxiliarIO.h"

namespace Markov_IO_New
{

    Experiment* Experiment::clone() const{
    return new Experiment(*this);
    }
    ///default constructors
    Experiment* Experiment::create() const{
    return new Experiment();
    }
    Experiment::~Experiment() {}

    std::string Experiment::ClassName()
    {
	return "Simple_Experiment";
    }





    std::size_t Experiment::total_samples()const{
    return total_samples_;
    }

    std::size_t Experiment::num_replicates()const{
	return traces_[i_trace()].num_replicates();
    }

    const Experiment& Experiment::replicate(std::size_t i)const{
      ASSERT_LESS(i, num_replicates());

      traces_[i_trace()].replicate(i);
       return *this;
    }

    const Experiment& Experiment::trace(std::size_t i)const{
      ASSERT_LESS(i, num_traces());
      i_trace_=i;
      return *this;
    }

    std::size_t Experiment::i_trace()const{
       return i_trace_;
    }

    std::size_t Experiment::num_traces() const{
      return this->traces_.size();
    }

    const Experiment& Experiment::operator[](std::size_t i)const{
    traces_[i_trace_][i];
    return *this;

    }
    const Experiment& Experiment::operator++()const{
    ++traces_[i_trace_];
    return *this;

    }

    std::size_t Experiment::i_sample()const{
    return traces_[i_trace_].i_sample();

    }

    std::size_t Experiment::num_measures()const{
    return traces_[i_trace_].num_measures();

    }

    double Experiment::t()const
    {
    return traces_[i_trace_].t();
    }
    double Experiment::dt()const
    {
	return traces_[i_trace_].dt();

    }
    double Experiment::x()const{
	return traces_[i_trace_].x();
    }
    std::size_t Experiment::num_steps()const{
	return traces_[i_trace_].num_steps();
    }
    const ABC_measure_point&  Experiment::sub_step(std::size_t i)const{
	return traces_[i_trace_].sub_step(i);

    }

    /// gives NaN() if there are no measures
    double Experiment::y()const
    {
	return traces_[i_trace()].y();
    }

    Experiment& Experiment::y(double new_value)
	    {
		traces_[i_trace()].y(new_value);
		return *this;
	    }



    Experiment::Experiment(const std::vector<Trace>& traces):
        traces_(traces),
	total_samples_(0),
	i_trace_(0)
	{
	    for (std::size_t i=0; i<num_traces(); i++)
	    {
		trace(i);
		total_samples_+=num_measures()*num_replicates();
	     }
	}


    Experiment::Experiment():
	name_(),
	traces_(),
	total_samples_(0),
	i_trace_(0){}


    Experiment::Experiment(const Experiment &other):
	name_(other.name_),
	traces_(other.traces_),
	total_samples_(other.total_samples_),
	i_trace_(other.i_trace_){}


    Experiment::Experiment(const ABC_Experiment &other):
    traces_(std::vector<Trace>(other.num_traces())),
	total_samples_(other.total_samples()),
    i_trace_(0)
    {
    for (std::size_t i=0; i<other.num_traces(); i++)
	{
        Trace tr=Trace(other.trace(i));
        traces_[i]=tr;
	}

    }


    Experiment& Experiment::operator =(const Experiment& other)
    {
	if (this!=&other)
	{
	    Experiment tmp(other);
	    swap(tmp,*this);
	}
	return *this;
    }


    void swap(Experiment& one, Experiment& other)
    {
	using std::swap;
	swap(one.name_,other.name_);
	swap (one.traces_,other.traces_);
	swap(one.total_samples_,other.total_samples_);
	swap(one.i_trace_,other.i_trace_);
    }




}






