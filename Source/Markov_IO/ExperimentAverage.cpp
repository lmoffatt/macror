#include "Tests/AssertPlain.h"
#include "Markov_IO/ExperimentAverage.h"
#include "Markov_IO/auxiliarIO.h"

namespace Markov_IO_New
{

Experiment_Average* Experiment_Average::clone() const
{
    return new Experiment_Average(*this);
}

/// default constructors
Experiment_Average* Experiment_Average::create() const
{
    return new Experiment_Average();
}

Experiment_Average::~Experiment_Average() {}


std::size_t Experiment_Average::total_samples()const
{
    return total_samples_;
}


std::size_t Experiment_Average::num_replicates()const
{
    return data_.size();
}

const Experiment_Average& Experiment_Average::replicate(std::size_t i)const
{
  ASSERT_LESS(i, num_replicates());
    i_replicate_=i;
    return *this;
}

const Experiment_Average& Experiment_Average::trace(std::size_t i)const
{
  ASSERT_LESS(i, num_traces());
    i_trace_=i;
    return *this;
}
std::size_t Experiment_Average::i_trace()const
{return i_trace_;}

const Experiment_Average& Experiment_Average::trace_interval()const
{return (*this)[num_measures()];}


std::size_t Experiment_Average::num_traces() const
{return data_[i_replicate_].size();}

const Experiment_Average& Experiment_Average::operator[](std::size_t i)const
{
    i_sample_=i;
    return *this;
}
const Experiment_Average& Experiment_Average::operator++()const
{
    ++i_sample_;
    return *this;
}
std::size_t Experiment_Average::i_sample()const
{
    return i_sample_;
}

std::size_t Experiment_Average::num_measures()const
{
    return data_[i_replicate_][i_trace_].size()-1;
}

double Experiment_Average::t()const
{return t_[i_replicate_][i_trace_][i_sample_];}

double Experiment_Average::dt()const
{return data_[i_replicate_][i_trace_][i_sample_].dt();}

double Experiment_Average::x()const
{
    return data_[i_replicate_][i_trace_][i_sample_].x();}

std::size_t Experiment_Average::num_steps()const
{
    return data_[i_replicate_][i_trace_][i_sample_].num_steps();
}

const x_dt&  Experiment_Average::sub_step(std::size_t i)const{
    return data_[i_replicate_][i_trace_][i_sample_].sub_step(i);
}
/// gives NaN() if there are no measures
double Experiment_Average::y()const{
    return data_[i_replicate_][i_trace_][i_sample_].y();}

//     Experiment_Average& y(double new_value)=0;




Experiment_Average::Experiment_Average():
    name_(),
	data_(),
	t_(),
	total_samples_(),
	i_replicate_(0),
	i_trace_(0),
	i_sample_(0)
{
  }




std::string Experiment_Average::ClassName()
{
    return "Experiment_Average";
}









}




#include "Markov_IO/ExperimentAverage.h"
#include "Markov_IO/auxiliarIO.h"

namespace Markov_IO
{

Experiment_Average* Experiment_Average::clone() const
{
    return new Experiment_Average(*this);
}

/// default constructors
Experiment_Average* Experiment_Average::create() const
{
    return new Experiment_Average();
}

Experiment_Average::~Experiment_Average() {}


std::size_t Experiment_Average::total_samples()const
{
    return total_samples_;
}


std::size_t Experiment_Average::num_replicates()const
{
    return data_.size();
}

const Experiment_Average& Experiment_Average::replicate(std::size_t i)const
{
  ASSERT_LESS(i, num_replicates());
    i_replicate_=i;
    return *this;
}

const Experiment_Average& Experiment_Average::trace(std::size_t i)const
{
  ASSERT_LESS(i, num_traces());
    i_trace_=i;
    return *this;
}
std::size_t Experiment_Average::i_trace()const
{return i_trace_;}

const Experiment_Average& Experiment_Average::trace_interval()const
{return (*this)[num_measures()];}


std::size_t Experiment_Average::num_traces() const
{return data_[i_replicate_].size();}

const Experiment_Average& Experiment_Average::operator[](std::size_t i)const
{
    i_sample_=i;
    return *this;
}
const Experiment_Average& Experiment_Average::operator++()const
{
    ++i_sample_;
    return *this;
}
std::size_t Experiment_Average::i_sample()const
{
    return i_sample_;
}

std::size_t Experiment_Average::num_measures()const
{
    return data_[i_replicate_][i_trace_].size()-1;
}

double Experiment_Average::t()const
{return t_[i_replicate_][i_trace_][i_sample_];}

double Experiment_Average::dt()const
{return data_[i_replicate_][i_trace_][i_sample_].dt();}

double Experiment_Average::x()const
{
    return data_[i_replicate_][i_trace_][i_sample_].x();}

std::size_t Experiment_Average::num_steps()const
{
    return data_[i_replicate_][i_trace_][i_sample_].num_steps();
}

const x_dt&  Experiment_Average::sub_step(std::size_t i)const{
    return data_[i_replicate_][i_trace_][i_sample_].sub_step(i);
}
/// gives NaN() if there are no measures
double Experiment_Average::y()const{
    return data_[i_replicate_][i_trace_][i_sample_].y();}

//     Experiment_Average& y(double new_value)=0;




Experiment_Average::Experiment_Average():
    name_(),
        data_(),
        t_(),
        total_samples_(),
        i_replicate_(0),
        i_trace_(0),
        i_sample_(0)
{
  }




std::string Experiment_Average::ClassName()
{
    return "Experiment_Average";
}





std::string Experiment_Average::id()const
{
    return name_;
};

std::string Experiment_Average::myClass()const
{
    return ClassName();
}




}

