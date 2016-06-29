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





#include "Markov_IO/PulsesProgram.h"
#include "Markov_IO/auxiliarIO.h"
#include "Tests/AssertPlain.h"

namespace Markov_IO
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
    run_trace_T=traces_v[to_i_trace_v[itrace_u]];
    run_trace_T.set_max_x_trace(pulse_concentration_M[itrace_u]);
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
    return size(to_i_trace_v);
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

Pulses_program::Pulses_program(const std::string& name,
    const std::vector<Pulses_trace>&
    vector_of_traces,
    const Markov_LA::M_Matrix<std::size_t>&
    sequence_of_traces,
    const Markov_LA::M_Matrix<double>&
    concentration_of_each_trace
    ):
    name_(name),
    traces_v(vector_of_traces),
    to_i_trace_v(sequence_of_traces),
    pulse_concentration_M(concentration_of_each_trace),
total_samples_u(0),
itrace_u(0)
{
    for (std::size_t i=0; i<size(to_i_trace_v); i++)
        total_samples_u+=traces_v[to_i_trace_v[i] ].num_measures();
    this->trace(0);
}

Pulses_program::Pulses_program(const std::string& name,
       std::size_t numberTraces,
       std::size_t numberRepetitions):
    name_(name),
    traces_v(std::vector<Pulses_trace>(numberTraces)),
    to_i_trace_v(Markov_LA::M_Matrix<std::size_t>(1,numberRepetitions)),
    pulse_concentration_M(Markov_LA::M_Matrix<double>(1,numberRepetitions)),
    total_samples_u(0),
    itrace_u(0)
    {}


Pulses_program::Pulses_program():
    name_(),
    traces_v(std::vector<Pulses_trace>()),
    to_i_trace_v(Markov_LA::M_Matrix<std::size_t>()),
    pulse_concentration_M(Markov_LA::M_Matrix<double>()),
    total_samples_u(0),
    itrace_u(0)
    {}


Pulses_program::Pulses_program(const Pulses_program& other):
    name_(other.name_),
    traces_v(other.traces_v),
    to_i_trace_v(other.to_i_trace_v),
    pulse_concentration_M(other.pulse_concentration_M),
    total_samples_u(other.total_samples_u),
    itrace_u(other.itrace_u),
    run_trace_T(other.run_trace_T) {}




ClassDescription Pulses_program::GetDescription()const
 {
     ClassDescription desc(myClass(),mySuperClass());;

     desc.push_back("name",name_);

     desc.push_back("number_of_traces",traces_v.size());

     desc.push_back("number_of_repetitions",Markov_LA::size(to_i_trace_v));

     if (traces_v.empty())
         desc.push_back("traces_0",Pulses_trace());
     else  for (std::size_t i=0;i<traces_v.size();++i)
     {
         desc.push_back("traces_"+ToString(i),traces_v[i]);

     }
     desc.push_back("sequence_of_traces",to_i_trace_v);

     desc.push_back("concentration_of_each_trace",
                    pulse_concentration_M);
     return desc;
 }

 std::string Pulses_program::ClassName()
 {
     return "Pulses_program";
 }






 std::string Pulses_program::id()const
 {
     return name_;
 }

  std::string Pulses_program::myClass()const
 {
     return ClassName();
 }





 bool Pulses_program::LoadFromDescription(
     const ClassDescription& classDes)
 {
     if (classDes.ClassName()!=Pulses_program::ClassName())
         return false;

     std::string name;
     if (!ToValue(classDes["name"],name))
         return false;


     std::vector<Pulses_trace>     vector_of_traces;
     std::size_t number_of_traces;

     if (!ToValue(classDes["number_of_traces"],number_of_traces))
         return false;


     for (std::size_t i=0;i<number_of_traces;++i)
     {
         Pulses_trace* trace;
         if (!ToValue(classDes["traces_"+ToString(i)],trace))
             return false;
         vector_of_traces.push_back(*trace);
         delete trace;
     }
     Markov_LA::M_Matrix<std::size_t> sequence_of_traces;
     if (!ToValue(classDes["sequence_of_traces"],sequence_of_traces))
         return false;

     Markov_LA::M_Matrix<double> concentration_of_each_trace;
     if (!ToValue(classDes["concentration_of_each_trace"],
             concentration_of_each_trace))
         return false;
     *this=Pulses_program(name,
                          vector_of_traces,
                          sequence_of_traces,
                          concentration_of_each_trace);

     return true;
 }
}


