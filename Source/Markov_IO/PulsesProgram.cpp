#include "Markov_IO/PulsesProgram.h"
#include "Markov_IO/auxiliarIO.h"
#include "Tests/AssertPlain.h"

namespace Markov_IO_New
{

Pulses_program* Pulses_program::clone() const
{
    return new Pulses_program(*this);
}
/// default constructors
Pulses_program* Pulses_program::create() const
{
    return new Pulses_program();
}
Pulses_program::~Pulses_program() {}

std::ostream& Pulses_program::put(std::ostream& s) const
{
    ABC_Experiment::put(s);
    return s;
}

std::size_t Pulses_program::total_samples() const
{
    return total_samples_u;
}


std::size_t Pulses_program::num_replicates()const
{
    return 0;
}

const Pulses_program& Pulses_program::replicate(std::size_t i)const
{
  ASSERT_LESS(i, num_replicates());
    return *this;
}



const Pulses_program& Pulses_program::trace(std::size_t i)const
{
  ASSERT_LESS(i, num_traces());
  itrace_u=i;
    run_trace_T=*traces_v[to_i_trace_v[itrace_u]];
    run_trace_T.set_max_x_trace(pulse_concentration_[itrace_u]);
    run_trace_T[0];
    return *this;
}

const Pulses_program& Pulses_program::trace_interval()const
{
    run_trace_T.trace_interval();
    return *this;
}

std::size_t Pulses_program::i_trace()const
{
    return itrace_u;
}


std::size_t Pulses_program::num_traces() const
{
    return to_i_trace_v.size();
}


std::size_t Pulses_program::i_sample()const
{
    return run_trace_T.i_sample();
}

//     Pulses_program& set_max_x_trace(double new_x)
//    {
//        run_trace_T.set_max_x_trace(new_x);
//        return *this;
//    }

const Pulses_program& Pulses_program::operator[](std::size_t i)const
{
    run_trace_T[i];
    return *this;
}

const Pulses_program& Pulses_program::operator++()const
{
    ++(run_trace_T);
    return (*this);
}

std::size_t Pulses_program::num_measures()const
{
    return (run_trace_T).num_measures();
}

double Pulses_program::t()const
{
    return (run_trace_T).t();
}

double Pulses_program::dt()const
{
    return (run_trace_T).dt();
}

double Pulses_program::x()const
{
    return (run_trace_T).x();
}


double Pulses_program::y() const
{
    return run_trace_T.y();
}

std::size_t Pulses_program::num_steps()const
{
    return (run_trace_T).num_steps();
}

const x_dt&  Pulses_program::sub_step(std::size_t i)const
{
    return (run_trace_T).sub_step(i);
}

Pulses_program::Pulses_program(const std::vector<Pulses_trace *> &vector_of_traces,
    const std::vector<std::size_t>&
    sequence_of_traces,
    const std::vector<double>&
    concentration_of_each_trace
    ):
    traces_v(vector_of_traces),
    to_i_trace_v(sequence_of_traces),
    pulse_concentration_(concentration_of_each_trace),
total_samples_u(0),
itrace_u(0)
{
    for (std::size_t i=0; i<to_i_trace_v.size(); i++)
        total_samples_u+=traces_v[to_i_trace_v[i] ]->num_measures();
    this->trace(0);
}

Pulses_program::Pulses_program(std::size_t numberTraces,
       std::size_t numberRepetitions):
   traces_v(std::vector<Pulses_trace*>(numberTraces)),
    to_i_trace_v(numberRepetitions),
    pulse_concentration_(numberRepetitions),
    total_samples_u(0),
    itrace_u(0)
    {}


Pulses_program::Pulses_program():
    name_(),
    traces_v(std::vector<Pulses_trace*>()),
    to_i_trace_v(),
    pulse_concentration_(),
    total_samples_u(0),
    itrace_u(0)
    {}


Pulses_program::Pulses_program(const Pulses_program& other):
    name_(other.name_),
    traces_v(other.traces_v),
    to_i_trace_v(other.to_i_trace_v),
    pulse_concentration_(other.pulse_concentration_),
    total_samples_u(other.total_samples_u),
    itrace_u(other.itrace_u),
    run_trace_T(other.run_trace_T) {}





 std::string Pulses_program::ClassName()
 {
     return "Pulses_program";
 }












 }




