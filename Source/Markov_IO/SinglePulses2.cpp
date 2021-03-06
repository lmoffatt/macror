#include "Tests/AssertPlain.h"
#include "Markov_IO/SinglePulses2.h"
#include "Markov_LA/matrixIO.h"

#include "Markov_IO/auxiliarIO.h"
namespace Markov_IO_New
{

  using Markov_LA::M_Matrix;

  Single_Pulses2*  Single_Pulses2::clone() const
  {
    return new Single_Pulses2(*this);
  };
  /// default constructors
  Single_Pulses2* Single_Pulses2::create() const
  {
    return new Single_Pulses2();
  };
  Single_Pulses2::~Single_Pulses2() {};

  std::ostream& Single_Pulses2::put(std::ostream& s) const
  {
    s<<"\nSingle_Pulses \n";
    s<<" Pulse duration\n"<<this->durpul_d;
    s<<" \n Concentration of pulses \n"<<this->con_M;
    ABC_Experiment::put(s);
    return s;
  };

  std::size_t Single_Pulses2::total_samples() const
  {
    return PP_PP.total_samples();
  }


  std::size_t Single_Pulses2::num_replicates()const
  {
    return 0;
  }

  const Single_Pulses2& Single_Pulses2::replicate(std::size_t)const
  {
    return *this;
  }



  const Single_Pulses2& Single_Pulses2::trace(std::size_t i)const
  {
    PP_PP.trace(i);
    return *this;
  };

  const Single_Pulses2& Single_Pulses2::trace_interval()const
  {
    PP_PP.trace_interval();
    return *this;
  };

  std::size_t Single_Pulses2::i_trace()const
  {
    return PP_PP.i_trace();
  };


  std::size_t Single_Pulses2::num_traces() const
  {
    return PP_PP.num_traces();
  };


  std::size_t Single_Pulses2::i_sample()const
  {
    return PP_PP.i_sample();
  };


  const Single_Pulses2& Single_Pulses2::operator[](std::size_t i)const
  {
    PP_PP[i];
    return *this;
  }
  const Single_Pulses2& Single_Pulses2::operator++()const
  {
    ++PP_PP;
    return (*this);
  }

  std::size_t Single_Pulses2::num_measures()const
  {
    return PP_PP.num_measures();
  };

  double Single_Pulses2::t()const
  {
    return PP_PP.t();
  };
  double Single_Pulses2::dt()const
  {
    return PP_PP.dt();
  };
  double Single_Pulses2::x()const
  {
    return PP_PP.x();
  };


  double Single_Pulses2::y() const
  {
    return PP_PP.y();
  };
  std::size_t Single_Pulses2::num_steps()const
  {
    return PP_PP.num_steps();
  };

  const x_dt&  Single_Pulses2::sub_step(std::size_t i)const
  {
    return PP_PP.sub_step(i);
  };

  //     Single_Pulses2& set_max_x_trace(double new_x)
  //    {
  //        PP_PP.set_max_x_trace(new_x);
  //        return *this;
  //    }


  Single_Pulses2::Single_Pulses2(const std::string& name,
                                 double time_of_pulse,
                                 double pulse_duration,
                                 const Markov_LA::M_Matrix<double> pulse_concentration,
                                 double control_duration,
                                 double control_concentration,
                                 double trace_duration,
                                 double trace_interval_,
                                 double fs,
                                 double time_to_exchange,
                                 double sub_step_time):
    name_(name),
    ton_d(time_of_pulse),
    durpul_d(pulse_duration),
    con_M(pulse_concentration),
    durcon_d(control_duration),
    concon_d(control_concentration),
    tracedur_d(trace_duration),
    trace_interval_d(trace_interval_),
    fs_d(fs),
    exchange_d(time_to_exchange),
    sub_step_time_d(sub_step_time),
    PP_PP()
  {

    Markov_LA::M_Matrix<double> ton_pulse(1,2);
    ton_pulse(0,0)=ton_d;
    ton_pulse(0,1)=ton_d+durpul_d;

    Markov_LA::M_Matrix<double> ton_con(1,2);
    ton_con(0,0)=ton_d;
    ton_con(0,1)=ton_d+durcon_d;

    Markov_LA::M_Matrix<double> x_at_ton(1,2);
    x_at_ton(0,0)=1.0;
    x_at_ton(0,1)=0.0;

    std::vector<Pulses_trace*> traces;
    Pulses_trace* p0= new Pulses_trace(ton_pulse,
                    x_at_ton,
                    tracedur_d,
                    fs_d,
                    exchange_d,
                    sub_step_time_d,
                    trace_interval_d);
    traces.push_back(p0);

    Pulses_trace*  p1= new Pulses_trace(ton_con,
                     x_at_ton,
                     tracedur_d,
                     fs_d,
                     exchange_d,
                     sub_step_time_d,
                     trace_interval_d);
    traces.push_back(p1);
    std::vector<std::size_t> to_i_trace(1,2*size(con_M)+1);
    std::vector<double> trace_con(1,2*size(con_M)+1);
    for (std::size_t i=0; i<size(con_M); i++)
      {
        to_i_trace[i* 2]=1;
        trace_con[i*2]=concon_d;
        to_i_trace[i*2+1]=0;
        trace_con[i*2+1]=con_M[i];
      };
    to_i_trace[size(con_M)*2]=1;
    trace_con[size(con_M)*2]=concon_d;
    PP_PP=Pulses_program(traces,to_i_trace,trace_con);
  };

  Single_Pulses2::Single_Pulses2() {};


  Single_Pulses2::Single_Pulses2(const Single_Pulses2& other):
    name_(other.name_),
    ton_d(other.ton_d),
    durpul_d(other.durpul_d),
    con_M(other.con_M),
    durcon_d(other.durcon_d),
    concon_d(other.concon_d),
    tracedur_d(other.tracedur_d),
    trace_interval_d(other.trace_interval_d),
    fs_d(other.fs_d),
    exchange_d(other.exchange_d),
    PP_PP(other.PP_PP) {}


  void swap(Single_Pulses2& one, Single_Pulses2& other)
  {
    using std::swap;
    swap(one.name_,other.name_);
    swap(one.ton_d,other.ton_d);
    swap(one.durpul_d,other.durpul_d);
    swap(one.con_M,other.con_M);
    swap(one.durcon_d,other.durcon_d);
    swap(one.concon_d,other.concon_d);
    swap(one.tracedur_d,other.tracedur_d);
    swap(one.trace_interval_d,other.trace_interval_d);
    swap(one.fs_d,other.fs_d);
    swap(one.exchange_d,other.exchange_d);
    swap(one.PP_PP,other.PP_PP);

  }


  std::string Single_Pulses2::ClassName()
  {return "Single_Pulses2";}






}


