#include "Tests/AssertPlain.h"
#include "Markov_IO/SinglePulses.h"
#include "Markov_IO/Pulse.h"

#include "Markov_LA/matrixIO.h"

#include "Markov_LA/auxiliarMath.h"
#include "Markov_IO/auxiliarIO.h"
namespace Markov_IO_New
{

  using Markov_LA::M_Matrix;


  Single_Pulses*  Single_Pulses::clone() const
  {
    return new Single_Pulses(*this);
  };
  /// default constructors
  Single_Pulses* Single_Pulses::create() const
  {
    return new Single_Pulses();
  };
  Single_Pulses::~Single_Pulses() {}

  std::ostream& Single_Pulses::put(std::ostream& s) const
  {
    ABC_Experiment::put(s);
    return s;
  };

  std::size_t Single_Pulses::total_samples() const
  {
    return num_traces()*num_measures();
  }


  std::size_t Single_Pulses::num_replicates()const
  {
    return 0;
  }

  const Single_Pulses& Single_Pulses::replicate(std::size_t)const
  {

    return *this;
  }

  //     Single_Pulses& set_max_x_trace(double new_x)
  //    {

  //        return *this;

  //    };


  const Single_Pulses& Single_Pulses::trace(std::size_t i)const
  {
    ASSERT_LESS(i, num_traces());
    itrace_u=i;
    if (itrace_u%2==0)
      {
        short_pulse_b=concon_d<exchange_d*6;
      }
    else
      {
        short_pulse_b=durpul_d<exchange_d*6;

      }
    return *this;
  };

  const Single_Pulses& Single_Pulses::trace_interval()const
  {
    (*this)[num_measures()];

    return *this;
  };

  std::size_t Single_Pulses::i_trace()const
  {
    return itrace_u;
  };


  std::size_t Single_Pulses::num_traces() const
  {
    return 2*size(con_M)+1;
  };


  std::size_t Single_Pulses::i_sample()const
  {
    return isample_u;
  };


  const Single_Pulses& Single_Pulses::raw_sample(std::size_t i)const
  {
    trace(std::size_t(floor(i/num_measures())));
    (*this)[i-i_trace()*num_measures()];
    return *this;
  };

  const Single_Pulses& Single_Pulses::operator[](std::size_t i)const
  {
    isample_u=i;
    i_sub_step_u=0;
    trun_d=1.0*(isample_u+0.5)/fs_d;
    if ((itrace_u % 2)==0)
      {
        if (short_pulse_b)
          {
            if ((trun_d>ton_d-exchange_d*3)&&(trun_d<ton_d+durcon_d+3*exchange_d))
              {
                n_sub_steps_u=nsub_steps_u;
              }
            else
              {
                n_sub_steps_u=1;
              }
          }
        else
          {
            if ((std::abs(trun_d-ton_d)<exchange_d*3)|(std::abs(trun_d-ton_d-durcon_d)<exchange_d*3))
              {
                n_sub_steps_u=nsub_steps_u;
              }
            else
              {
                n_sub_steps_u=1;
              }
          };
        double trun_=1.0*(isample_u+0.5/n_sub_steps_u)/fs_d;
        xdt_r.x(Pulse(trun_-ton_d,durcon_d,exchange_d)*concon_d);
        if (n_sub_steps_u>1)
          {
            //  trun_d=1.0*(isample_u+0.5)/fs_d;
            x_d=Pulse(trun_d-ton_d,durcon_d,exchange_d)*concon_d;
          }
        else
          {
            x_d=xdt_r.x();
          }

      }
    else
      {
        if (short_pulse_b)
          {
            if ((trun_d>ton_d-exchange_d*3)&&(trun_d<ton_d+durpul_d+3*exchange_d))
              {
                n_sub_steps_u=nsub_steps_u;
              }
            else
              {
                n_sub_steps_u=1;
              }
          }
        else
          {
            if ((std::abs(trun_d-ton_d)<exchange_d*3)|(std::abs(trun_d-ton_d-durpul_d)<exchange_d*3))
              {
                n_sub_steps_u=nsub_steps_u;
              }
            else
              {
                n_sub_steps_u=1;
              }
          }
        double trun_=1.0*(isample_u+0.5/n_sub_steps_u)/fs_d;
        xdt_r.x(Pulse(trun_-ton_d,durpul_d,exchange_d)*con_M[itrace_u/2]);
        if (n_sub_steps_u>1)
          {
            // trun_d=1.0*(isample_u+0.5)/fs_d;
            x_d=Pulse(trun_d-ton_d,durpul_d,exchange_d)*con_M[itrace_u/2];
          }
        else
          {
            x_d=xdt_r.x();
          };

      };
    if (this->isample_u<this->nmeasures_u)
      {
        xdt_r.dt(dt_d/n_sub_steps_u);
      }
    else
      {
        xdt_r.dt(trace_interval_d);
      }
    return *this;
  };

  const Single_Pulses& Single_Pulses::operator++()const
  {
    return (*this)[i_sample()+1];
  }

  std::size_t Single_Pulses::num_measures()const
  {
    return nmeasures_u;
  };

  double Single_Pulses::t()const
  {
    return trun_d;
  };
  double Single_Pulses::dt()const
  {
    if (isample_u<nmeasures_u)
      return dt_d;
    else
      return trace_interval_d;
  };
  double Single_Pulses::x()const
  {
    return x_d;
  };


  double Single_Pulses::y() const
  {
    return Markov_LA::NaN();
  };
  std::size_t Single_Pulses::num_steps()const
  {
    return n_sub_steps_u;
  };

  const x_dt&  Single_Pulses::sub_step(std::size_t i)const
  {
    i_sub_step_u=i;
    double trun_=(isample_u+(0.5+i_sub_step_u)/n_sub_steps_u)/fs_d;
    if ((itrace_u % 2)==0)
      {
        xdt_r.x(Pulse(trun_-ton_d,durcon_d,exchange_d)*concon_d);
      }
    else
      {
        xdt_r.x(Pulse(trun_-ton_d,durpul_d,exchange_d)*con_M[itrace_u/2]);
      };

    return xdt_r;
  }

  Single_Pulses::Single_Pulses(const std::string& name,
                               double time_of_pulse,
                               double pulse_duration,
                               const Markov_LA::M_Matrix<double>& pulse_concentration,
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
    dt_d(1.0/fs),
    nmeasures_u(std::size_t(ceil(tracedur_d*fs_d))),
    nsub_steps_u(std::size_t(round(1.0/sub_step_time/fs_d))),
    sub_step_time_d(dt_d/nsub_steps_u),
    short_pulse_b(concon_d<exchange_d*6),
    itrace_u(0),
    isample_u(0),
    n_sub_steps_u(1),
    trun_d(0.),
    xdt_r(x_dt(dt_d,concon_d))     {}

  Single_Pulses::Single_Pulses():
    name_(),
    ton_d(),
    durpul_d(),
    con_M(),
    durcon_d(),
    concon_d(),
    tracedur_d(),
    trace_interval_d(),
    fs_d(),
    exchange_d(),
    dt_d(),
    nmeasures_u(),
    nsub_steps_u(),
    sub_step_time_d(),
    short_pulse_b(),
    itrace_u(),
    isample_u(),
    n_sub_steps_u(),
    trun_d(),
    xdt_r()     {}


  Single_Pulses::Single_Pulses(const Single_Pulses& other):
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
    dt_d(other.dt_d),
    nmeasures_u(other.nmeasures_u),
    nsub_steps_u(other.nsub_steps_u),
    sub_step_time_d(other.sub_step_time_d),
    short_pulse_b(other.short_pulse_b),
    itrace_u(0),
    isample_u(0),
    n_sub_steps_u(1),
    trun_d(0),
    xdt_r(other.xdt_r)         {}


  void swap(Single_Pulses& one, Single_Pulses& other)
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
    swap(one.dt_d,other.dt_d);
    swap(one.nmeasures_u,other.nmeasures_u);
    swap(one.nsub_steps_u,other.nsub_steps_u);
    swap(one.sub_step_time_d,other.sub_step_time_d);
    swap(one.short_pulse_b,other.short_pulse_b);
    swap(one.itrace_u,other.itrace_u);
    swap(one.isample_u,other.isample_u);
    swap(one.n_sub_steps_u,other.n_sub_steps_u);
    swap(one.trun_d,other.trun_d);
    swap(one.xdt_r,other.xdt_r);
  }



  std::string Single_Pulses::ClassName()
  {
    return "Single_Pulses";
  }











}




#include "Tests/AssertPlain.h"
#include "Markov_IO/SinglePulses.h"
#include "Markov_IO/Pulse.h"

#include "Markov_LA/matrixIO.h"

#include "Markov_LA/auxiliarMath.h"
#include "Markov_IO/auxiliarIO.h"
namespace Markov_IO
{

  using Markov_LA::M_Matrix;


  Single_Pulses*  Single_Pulses::clone() const
  {
    return new Single_Pulses(*this);
  };
  /// default constructors
  Single_Pulses* Single_Pulses::create() const
  {
    return new Single_Pulses();
  };
  Single_Pulses::~Single_Pulses() {}

  std::ostream& Single_Pulses::put(std::ostream& s) const
  {
    ABC_Experiment::put(s);
    return s;
  };

  std::size_t Single_Pulses::total_samples() const
  {
    return num_traces()*num_measures();
  }


  std::size_t Single_Pulses::num_replicates()const
  {
    return 0;
  }

  const Single_Pulses& Single_Pulses::replicate(std::size_t)const
  {

    return *this;
  }

  //     Single_Pulses& set_max_x_trace(double new_x)
  //    {

  //        return *this;

  //    };


  const Single_Pulses& Single_Pulses::trace(std::size_t i)const
  {
    ASSERT_LESS(i, num_traces());
    itrace_u=i;
    if (itrace_u%2==0)
      {
        short_pulse_b=concon_d<exchange_d*6;
      }
    else
      {
        short_pulse_b=durpul_d<exchange_d*6;

      }
    return *this;
  };

  const Single_Pulses& Single_Pulses::trace_interval()const
  {
    (*this)[num_measures()];

    return *this;
  };

  std::size_t Single_Pulses::i_trace()const
  {
    return itrace_u;
  };


  std::size_t Single_Pulses::num_traces() const
  {
    return 2*size(con_M)+1;
  };


  std::size_t Single_Pulses::i_sample()const
  {
    return isample_u;
  };


  const Single_Pulses& Single_Pulses::raw_sample(std::size_t i)const
  {
    trace(std::size_t(floor(i/num_measures())));
    (*this)[i-i_trace()*num_measures()];
    return *this;
  };

  const Single_Pulses& Single_Pulses::operator[](std::size_t i)const
  {
    isample_u=i;
    i_sub_step_u=0;
    trun_d=1.0*(isample_u+0.5)/fs_d;
    if ((itrace_u % 2)==0)
      {
        if (short_pulse_b)
          {
            if ((trun_d>ton_d-exchange_d*3)&&(trun_d<ton_d+durcon_d+3*exchange_d))
              {
                n_sub_steps_u=nsub_steps_u;
              }
            else
              {
                n_sub_steps_u=1;
              }
          }
        else
          {
            if ((std::abs(trun_d-ton_d)<exchange_d*3)|(std::abs(trun_d-ton_d-durcon_d)<exchange_d*3))
              {
                n_sub_steps_u=nsub_steps_u;
              }
            else
              {
                n_sub_steps_u=1;
              }
          };
        double trun_=1.0*(isample_u+0.5/n_sub_steps_u)/fs_d;
        xdt_r.x(Pulse(trun_-ton_d,durcon_d,exchange_d)*concon_d);
        if (n_sub_steps_u>1)
          {
            //  trun_d=1.0*(isample_u+0.5)/fs_d;
            x_d=Pulse(trun_d-ton_d,durcon_d,exchange_d)*concon_d;
          }
        else
          {
            x_d=xdt_r.x();
          }

      }
    else
      {
        if (short_pulse_b)
          {
            if ((trun_d>ton_d-exchange_d*3)&&(trun_d<ton_d+durpul_d+3*exchange_d))
              {
                n_sub_steps_u=nsub_steps_u;
              }
            else
              {
                n_sub_steps_u=1;
              }
          }
        else
          {
            if ((std::abs(trun_d-ton_d)<exchange_d*3)|(std::abs(trun_d-ton_d-durpul_d)<exchange_d*3))
              {
                n_sub_steps_u=nsub_steps_u;
              }
            else
              {
                n_sub_steps_u=1;
              }
          }
        double trun_=1.0*(isample_u+0.5/n_sub_steps_u)/fs_d;
        xdt_r.x(Pulse(trun_-ton_d,durpul_d,exchange_d)*con_M[itrace_u/2]);
        if (n_sub_steps_u>1)
          {
            // trun_d=1.0*(isample_u+0.5)/fs_d;
            x_d=Pulse(trun_d-ton_d,durpul_d,exchange_d)*con_M[itrace_u/2];
          }
        else
          {
            x_d=xdt_r.x();
          };

      };
    if (this->isample_u<this->nmeasures_u)
      {
        xdt_r.dt(dt_d/n_sub_steps_u);
      }
    else
      {
        xdt_r.dt(trace_interval_d);
      }
    return *this;
  };

  const Single_Pulses& Single_Pulses::operator++()const
  {
    return (*this)[i_sample()+1];
  }

  std::size_t Single_Pulses::num_measures()const
  {
    return nmeasures_u;
  };

  double Single_Pulses::t()const
  {
    return trun_d;
  };
  double Single_Pulses::dt()const
  {
    if (isample_u<nmeasures_u)
      return dt_d;
    else
      return trace_interval_d;
  };
  double Single_Pulses::x()const
  {
    return x_d;
  };


  double Single_Pulses::y() const
  {
    return Markov_LA::NaN();
  };
  std::size_t Single_Pulses::num_steps()const
  {
    return n_sub_steps_u;
  };

  const x_dt&  Single_Pulses::sub_step(std::size_t i)const
  {
    i_sub_step_u=i;
    double trun_=(isample_u+(0.5+i_sub_step_u)/n_sub_steps_u)/fs_d;
    if ((itrace_u % 2)==0)
      {
        xdt_r.x(Pulse(trun_-ton_d,durcon_d,exchange_d)*concon_d);
      }
    else
      {
        xdt_r.x(Pulse(trun_-ton_d,durpul_d,exchange_d)*con_M[itrace_u/2]);
      };

    return xdt_r;
  }

  Single_Pulses::Single_Pulses(const std::string& name,
                               double time_of_pulse,
                               double pulse_duration,
                               const Markov_LA::M_Matrix<double>& pulse_concentration,
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
    dt_d(1.0/fs),
    nmeasures_u(std::size_t(ceil(tracedur_d*fs_d))),
    nsub_steps_u(std::size_t(round(1.0/sub_step_time/fs_d))),
    sub_step_time_d(dt_d/nsub_steps_u),
    short_pulse_b(concon_d<exchange_d*6),
    itrace_u(0),
    isample_u(0),
    n_sub_steps_u(1),
    trun_d(0.),
    xdt_r(x_dt(dt_d,concon_d))     {}

  Single_Pulses::Single_Pulses():
    name_(),
    ton_d(),
    durpul_d(),
    con_M(),
    durcon_d(),
    concon_d(),
    tracedur_d(),
    trace_interval_d(),
    fs_d(),
    exchange_d(),
    dt_d(),
    nmeasures_u(),
    nsub_steps_u(),
    sub_step_time_d(),
    short_pulse_b(),
    itrace_u(),
    isample_u(),
    n_sub_steps_u(),
    trun_d(),
    xdt_r()     {}


  Single_Pulses::Single_Pulses(const Single_Pulses& other):
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
    dt_d(other.dt_d),
    nmeasures_u(other.nmeasures_u),
    nsub_steps_u(other.nsub_steps_u),
    sub_step_time_d(other.sub_step_time_d),
    short_pulse_b(other.short_pulse_b),
    itrace_u(0),
    isample_u(0),
    n_sub_steps_u(1),
    trun_d(0),
    xdt_r(other.xdt_r)         {}


  void swap(Single_Pulses& one, Single_Pulses& other)
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
    swap(one.dt_d,other.dt_d);
    swap(one.nmeasures_u,other.nmeasures_u);
    swap(one.nsub_steps_u,other.nsub_steps_u);
    swap(one.sub_step_time_d,other.sub_step_time_d);
    swap(one.short_pulse_b,other.short_pulse_b);
    swap(one.itrace_u,other.itrace_u);
    swap(one.isample_u,other.isample_u);
    swap(one.n_sub_steps_u,other.n_sub_steps_u);
    swap(one.trun_d,other.trun_d);
    swap(one.xdt_r,other.xdt_r);
  }



  ClassDescription Single_Pulses::GetDescription()const
  {
    ClassDescription desc(myClass(),mySuperClass());;
    desc.push_back("name",name_);
    desc.push_back("time_of_pulse",ton_d);
    desc.push_back("pulse_duration",durpul_d);
    desc.push_back("pulse_concentration",con_M);
    desc.push_back("control_duration",durcon_d);
    desc.push_back("control_concentration",concon_d);
    desc.push_back("trace_duration",tracedur_d);
    desc.push_back("frequency_of_sampling",fs_d);
    desc.push_back("time_to_exchange",exchange_d);
    desc.push_back("trace_interval",trace_interval_d);
    desc.push_back("sub_step_time",sub_step_time_d);
    return desc;
  }

  std::string Single_Pulses::ClassName()
  {
    return "Single_Pulses";
  }

  std::string Single_Pulses::id()const
  {
    return name_;
  };

  std::string Single_Pulses::myClass()const
  {
    return ClassName();
  }







  bool Single_Pulses::LoadFromDescription(const ClassDescription& classDes)
  {
    if (classDes.ClassName()!=myClass())
      return false;
    std::string name;
    if (!ToValue(classDes["name"],name))
      return false;

    double time_of_pulse;
    if (!ToValue(classDes["time_of_pulse"],time_of_pulse))
      return false;

    double pulse_duration;
    if (!ToValue(classDes["pulse_duration"],pulse_duration))
      return false;
    Markov_LA::M_Matrix<double> pulse_concentration;
    if (!ToValue(classDes["pulse_concentration"],pulse_concentration))
      return false;
    double control_duration;
    if (!ToValue(classDes["control_duration"],control_duration))
      return false;
    double control_concentration;
    if (!ToValue(classDes["control_concentration"],control_concentration))
      return false;
    double trace_duration;
    if (!ToValue(classDes["trace_duration"],trace_duration))
      return false;
    double trace_interval;
    if (!ToValue(classDes["trace_interval"],trace_interval))
      return false;
    double frequency_of_sampling;
    if (!ToValue(classDes["frequency_of_sampling"],frequency_of_sampling))
      return false;
    double time_to_exchange;
    if (!ToValue(classDes["time_to_exchange"],time_to_exchange))
      return false;
    double sub_step_time;
    if (!ToValue(classDes["sub_step_time"],sub_step_time))
      return false;


    *this=Single_Pulses(name,
                        time_of_pulse,
                        pulse_duration,
                        pulse_concentration,
                        control_duration,
                        control_concentration,
                        trace_duration,
                        trace_interval,
                        frequency_of_sampling,
                        time_to_exchange,
                        sub_step_time);

    return true;
  }




}
