#include "Tests/AssertPlain.h"
#include "Markov_IO/PulsesTrace.h"
#include "Markov_IO/Pulse.h"

#include "Markov_LA/matrixIO.h"
#include "Markov_LA/auxiliarMath.h"
#include "Markov_LA/matrixMaxMin.h"
#include "Markov_LA/matrixAssigmentOp.h"
#include "Markov_LA/matrixSum.h"
#include "Markov_LA/matrixRelational.h"

#include "Markov_IO/ClassDescription.h"
#include "Markov_IO/auxiliarIO.h"

namespace Markov_IO
{

Pulses_trace* Pulses_trace::clone() const
{
    return new Pulses_trace(*this);
};
/// default constructors

Pulses_trace* Pulses_trace::create() const
{
    return new Pulses_trace();
};

Pulses_trace::~Pulses_trace() {}

std::ostream& Pulses_trace::put(std::ostream& s) const
{
    s<<"\nPulses_trace \n";
    s<<" time of changes \n"<<t_on_M;
    s<<" \n Concentration of pulses \n"<<x_on_M;
    s<<"\n frequency of sampling\t"<<fs_d<<"\ttrace duration \t"<<tracedur_d;
    s<<"\t time to next trace\t"<<time_to_next_trace_d<<"\tsub step time\t"<<sub_step_time_d<<"\n";
    ABC_trace::put(s);
    return s;
}


std::size_t Pulses_trace::i_sample()const
{
    return isample_u;
};


const Pulses_trace& Pulses_trace::operator++()const
{
    ASSERT_LEQ(isample_u, num_measures());
    isample_u++;
    trun_d+=dt_d;
    std::size_t i=0;
    while ((t_on_M[i_min_pulse_u]<trun_d-dt_d*0.5-3*exchange_d)&&
	   (i_min_pulse_u<size(t_on_M)))
    {
	i_min_pulse_u++;
    };
    while ((t_on_M[i_max_pulse_u]<=trun_d+dt_d*0.5+3*exchange_d)&&
	   (i_max_pulse_u<size(t_on_M)))
    {
	i++;
    };
    if (i_min_pulse_u>0)
    {
	x_d=x_on_M[i_min_pulse_u-1];
    }
    else
    {
	x_d=0;
    }
    if (i_max_pulse_u>i_min_pulse_u)
    {
	n_sub_steps_u=max_n_sub_steps_u;
	xdt_r.dt(sub_step_time_d);
	xdt_r.x(x_d);

	for(i=i_min_pulse_u; i<i_max_pulse_u; i++)
	{
	    x_d+=pulse_profile((trun_d-t_on_M[i])/exchange_d)*(dx_on_M[i]);
	};
	xdt_r.x(x_d);
    }
    else
    {
	n_sub_steps_u=1;
	xdt_r.dt(dt_d);
	xdt_r.x(x_d);
    };
    if (isample_u==nmeasures_u)
    {
	xdt_r.dt(time_to_next_trace_d);
    };


    return *this;
}


const Pulses_trace& Pulses_trace::operator[](std::size_t i_samp)const
{
    ASSERT_LEQ(i_samp, num_measures());
    isample_u=i_samp;
    trun_d=dt_d*(0.5+isample_u);
    double eps=dt_d*1e-6;
    std::size_t i=0;
    while ((i<size(t_on_M))&&(t_on_M[i]<trun_d-dt_d*0.5-3.0*exchange_d-eps))
    {
	i++;
    };
    i_min_pulse_u=i;
    while ((i<size(t_on_M)&&(t_on_M[i]<=trun_d+dt_d*0.5+3.0*exchange_d+eps)))
    {
	i++;
    };
    i_max_pulse_u=i;
    if (i_min_pulse_u>0)
    {
	x_d=x_on_M[i_min_pulse_u-1];
    }
    else
    {
	x_d=x_on_M[0];
    }
    if (i_max_pulse_u>i_min_pulse_u)
    {
	n_sub_steps_u=max_n_sub_steps_u;
	xdt_r.dt(sub_step_time_d);
	xdt_r.x(x_d);

	for(i=i_min_pulse_u; i<i_max_pulse_u; i++)
	{
	    x_d+=pulse_profile((trun_d-t_on_M[i])/exchange_d)*(dx_on_M[i]);
	};
	xdt_r.x(x_d);
    }
    else
    {
	n_sub_steps_u=1;
	xdt_r.dt(dt_d);
	xdt_r.x(x_d);
    };
    if (isample_u==nmeasures_u)
    {
    trun_d=dt_d*(isample_u)+0.5*time_to_next_trace_d;

	xdt_r.dt(time_to_next_trace_d);
    };

    return *this;
}


const Pulses_trace& Pulses_trace::trace_interval()const
{
    return (*this)[num_measures()];
}


std::size_t Pulses_trace::num_measures()const
{
    return nmeasures_u;
}

 std::size_t Pulses_trace::num_replicates()const{
     return 0;
 }

 const Pulses_trace& Pulses_trace::replicate(std::size_t i)const
 {
   ASSERT_LESS(i, num_replicates());

   return *this;
 }




double Pulses_trace::t()const
{
    return trun_d;
}


double Pulses_trace::dt()const
{
    if (isample_u<nmeasures_u)
	return dt_d;
    else
	return time_to_next_trace_d;
}



double Pulses_trace::x()const
{
    return x_d;
}


double Pulses_trace::y() const
{
    return Markov_LA::NaN();
}


std::size_t Pulses_trace::num_steps()const
{
    return n_sub_steps_u;
}


const x_dt&  Pulses_trace::sub_step(std::size_t i_sub)const
{
  ASSERT_LESS(i_sub, num_steps());
  if (n_sub_steps_u>1)
    {
      double trun_s=1.*(isample_u+(1.0*i_sub)/n_sub_steps_u)/fs_d;
      double trun_e=1.*(isample_u+(1.0+i_sub)/n_sub_steps_u)/fs_d;

      double x_s;
      if (i_min_pulse_u>0)
        x_s=x_on_M[i_min_pulse_u-1];
      else
        x_s=x_on_M[0];
      double x_e=x_s;
      if (exchange_d>0)
        {
          for(std::size_t i=i_min_pulse_u; i<i_max_pulse_u; i++)
            {
              x_s+=pulse_profile((trun_s-t_on_M[i])/exchange_d)*(dx_on_M[i]);
              x_e+=pulse_profile((trun_e-t_on_M[i])/exchange_d)*(dx_on_M[i]);
            };
        }
      else
        {
          for(std::size_t i=i_min_pulse_u; i<i_max_pulse_u; i++)
            {
              if (trun_s>t_on_M[i])
                {
                  x_s+=(dx_on_M[i]);
                }
              if (trun_e>t_on_M[i])
                {
                  x_e+=dx_on_M[i];
                }
            }
        }
      xdt_r.x((x_s+x_e)/2.0);
      xdt_r.dt(trun_e-trun_s);
    };
  return xdt_r;
}


Pulses_trace& Pulses_trace::set_max_x_trace(double new_max)
{
    double f=new_max/max(x_on_M);
    x_on_M*=f;
    dx_on_M*=f;
    return *this;
}


Pulses_trace::Pulses_trace(const std::string& name,
    const Markov_LA::M_Matrix<double>& time_of_each_pulse,
			       const Markov_LA::M_Matrix<double>& concentration_of_each_pulse,
			       double trace_duration,
			       double frequency_of_sampling,
			       double time_to_exchange,
			       double sub_step_time,
			       double time_to_next_trace):
    name_(name),
    t_on_M(time_of_each_pulse),
    x_on_M (concentration_of_each_pulse),
    tracedur_d(trace_duration),
    fs_d(frequency_of_sampling),
    exchange_d(time_to_exchange),
    sub_step_time_d(sub_step_time),
    time_to_next_trace_d(time_to_next_trace),
    dx_on_M(diff(concentration_of_each_pulse)),
    dt_d(1.0/frequency_of_sampling),
    nmeasures_u(std::size_t(round(frequency_of_sampling*trace_duration))),
    max_n_sub_steps_u(std::size_t(round(1.0/sub_step_time/frequency_of_sampling)))
{
  tracedur_d=nmeasures_u*dt_d;
  sub_step_time_d=dt_d/max_n_sub_steps_u;
  ASSERT_GEQ(x_on_M,0.00);
  ASSERT_GEQ(t_on_M,0.0);
  ASSERT_LEQ(t_on_M,tracedur_d);
  ASSERT_LEQ(dt_d*2,tracedur_d);
  ASSERT_LEQ(0.00,exchange_d);
  ASSERT_LESS(exchange_d*5,tracedur_d);
  ASSERT_LEQ(sub_step_time_d,dt_d);
//  ASSERT_EQ(sub_step_time_d*max_n_sub_steps_u,dt_d);
    (*this)[0];
}

Pulses_trace::Pulses_trace(const std::string& name,
             std::size_t number_of_concentration_changes):
    name_(name),
    t_on_M(Markov_LA::M_Matrix<double>(1,number_of_concentration_changes)),
    x_on_M (Markov_LA::M_Matrix<double>(1,number_of_concentration_changes)),
    tracedur_d(0),
    fs_d(0),
    exchange_d(0),
    sub_step_time_d(0),
    time_to_next_trace_d(0),
    dx_on_M(),
    dt_d(0),
    nmeasures_u(0),
    max_n_sub_steps_u(0)
    {}



Pulses_trace::Pulses_trace() {}



Pulses_trace::Pulses_trace(const Pulses_trace& other):
    name_(other.name_),
    t_on_M(other.t_on_M),
    x_on_M (other.x_on_M),
    tracedur_d(other.tracedur_d ),
    fs_d(other.fs_d ),
    exchange_d(other.exchange_d),
    sub_step_time_d(other.sub_step_time_d ),
    time_to_next_trace_d(other.time_to_next_trace_d),

    dx_on_M(other.dx_on_M),
    dt_d(other.dt_d),
    nmeasures_u(other.nmeasures_u ),
    max_n_sub_steps_u(other.max_n_sub_steps_u),

    isample_u(other.isample_u ),
    trun_d(other.trun_d ),

    x_d(other.x_d ),
    xdt_r(other.xdt_r ),

    i_min_pulse_u(other.i_min_pulse_u),
    i_max_pulse_u(other.i_max_pulse_u),
    n_sub_steps_u(other.n_sub_steps_u ) {}





ClassDescription  Pulses_trace:: GetDescription()const
{
    ClassDescription desc(myClass(),mySuperClass());;
    desc.push_back("name",name_);

    desc.push_back("number_of_concentration_changes",
                   Markov_LA::size(t_on_M),
                   "number of concentration changes that occur during the trace",
                   "include the change at zero time ");

    desc.push_back("time_of_each_concentration_change",t_on_M,
                   "[s]",
                   "indicates the time where each concentration change occurs",
                   "the time is on the middle of the change");

    desc.push_back("concentration_of_each_change",
                   x_on_M,
                   "[uM]",
                   "concentration during the interval of time",
                   "the interval of time is defined by two succesive concentration "
                   "changes");

    desc.push_back("trace_duration",tracedur_d,
                   "[s]",
                   "time duration of the trace, that is time where data is recorded",
                   "");

    desc.push_back("frequency_of_sampling",fs_d,
                   "[Hz]",
                   "frquency of the recording",
                   "it tells the simulation the frequency that the recording is "
                   "supposed to have");

    desc.push_back("time_to_exchange",exchange_d,
                   "[s]",
                   "time constant of the solution exchange",
                   " it uses an error function to simulate the exchange") ;

    desc.push_back("sub_step_time",sub_step_time_d,
                   "[s]",
                   "time step used for the simulation",
                   "the simulation assumes that during this time steps there are no "
                   "changes of state");

    desc.push_back("time_to_next_trace",time_to_next_trace_d,
                   "[s]",
                   "time interval between traces",
                   "time lapse from the end of the last measurement of the trace and "
                   "the begining of the next one"
                   );


    return desc;
}

std::string Pulses_trace::ClassName()
{
    return "Pulses_trace";
}







std::string Pulses_trace::myName()const
{
   return name_;
};

 std::string Pulses_trace::myClass()const
{
   return ClassName();
}


bool Pulses_trace::LoadFromDescription(
    const ClassDescription& classDes)
{
    if (classDes.ClassName()!=myClass())
	return false;
    std::string name;
    if (!ToValue(classDes["name"],name))
	return false;

    Markov_LA::M_Matrix<double> time_of_each_pulse;
    if (!ToValue(classDes["time_of_each_concentration_change"],time_of_each_pulse))
	return false;


    Markov_LA::M_Matrix<double> concentration_of_each_pulse;
    if (!ToValue(classDes["concentration_of_each_change"],
		 concentration_of_each_pulse))
	return false;


    double trace_duration;
    if(!ToValue(classDes["trace_duration"],trace_duration))
	return false;
    double frequency_of_sampling;
    if(!ToValue(classDes["frequency_of_sampling"],frequency_of_sampling))
	return false;

    double time_to_exchange;
    if(!ToValue(classDes["time_to_exchange"],time_to_exchange))
	return false;
    double sub_step_time;
    if(!ToValue(classDes["sub_step_time"],sub_step_time))
	return false;
    double time_to_next_trace;
    if(!ToValue(classDes["time_to_next_trace"],time_to_next_trace))
	return false;


    *this=Pulses_trace(name,
		       time_of_each_pulse,
		       concentration_of_each_pulse,
		       trace_duration,
		       frequency_of_sampling,
		       time_to_exchange,
		       sub_step_time,
		       time_to_next_trace);


    return true;
}



}
