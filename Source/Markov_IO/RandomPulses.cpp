#include "Markov_IO/RandomPulses.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_IO/ClassDescription.h"
#include "Tests/AssertPlain.h"
#include "Markov_LA/matrixRelational.h"

namespace Markov_IO
{

using Markov_LA::M_Matrix;

Random_Pulses* Random_Pulses::clone() const
{
    return new Random_Pulses(*this);
};
/// default constructors
 Random_Pulses* Random_Pulses::create() const
{
    return new Random_Pulses();
};
 Random_Pulses::~Random_Pulses() {}

// std::ostream& Random_Pulses::put(std::ostream& s) const
//{
//    for(std::size_t k=0; k<num_traces(); k++)
//    {
//	trace(k);
//	for (std::size_t j=0; j<num_measures(); j++)
//	{
//	    (*this)[j];
//	    s<<t()<<"  ";
//	    s<<dt()<<"  "<<x()<<"  "<<y()<<"    "<<k;
//	    s<<"\n";
//	    for (std::size_t i=0; i<num_steps(); i++)
//		s<<" \t "<<sub_step(i).dt()<<"  "<<sub_step(i).x()<<"\n";
//	};

//	//            s<<"--------------------------------------------------------------------------------------------\n";
//	//            s<<"                                      new trace";
//	//            s<<"--------------------------------------------------------------------------------------------\n";
//	//            s<<"\n";
//    };
//    return s;
//};

 std::size_t Random_Pulses::total_samples() const
{
    return PP_PP.total_samples();
};


 std::size_t Random_Pulses::num_replicates()const
{
    return 0;
};

 const Random_Pulses& Random_Pulses::replicate(std::size_t i)const
{
   ASSERT_LESS(i, num_replicates());

   return *this;
};



 const Random_Pulses& Random_Pulses::trace(std::size_t i)const
{
    PP_PP.trace(i);
    return *this;
};

 const Random_Pulses& Random_Pulses::trace_interval()const
{
    PP_PP.trace_interval();
    return *this;
};

 std::size_t Random_Pulses::i_trace()const
{
    return PP_PP.i_trace();
};


 std::size_t Random_Pulses::num_traces() const
{
    return PP_PP.num_traces();
};


 std::size_t Random_Pulses::i_sample()const
{
    return PP_PP.i_sample();
};


 const Random_Pulses& Random_Pulses::operator[](std::size_t i)const
{
    PP_PP[i];
    return *this;
}
 const Random_Pulses& Random_Pulses::operator++()const
{
    ++PP_PP;
    return (*this);
}

 std::size_t Random_Pulses::num_measures()const
{
    return PP_PP.num_measures();
};

 double Random_Pulses::t()const
{
    return PP_PP.t();
};
 double Random_Pulses::dt()const
{
    return PP_PP.dt();
};
 double Random_Pulses::x()const
{
    return PP_PP.x();
};


 double Random_Pulses::y() const
{
    return PP_PP.y();
};
 std::size_t Random_Pulses::num_steps()const
{
    return PP_PP.num_steps();
};

 const x_dt&  Random_Pulses::sub_step(std::size_t i)const
{
    return PP_PP.sub_step(i);
};

//     Random_Pulses& set_max_x_trace(double new_x)
//    {
//        PP_PP.set_max_x_trace(new_x);
//        return *this;
//    }


 Random_Pulses::Random_Pulses(const std::string& name,
			      double time_of_pulse,
			      double minimal_pulse_duration,
			      double maximal_pulse_duration,
			      double minimal_interval,
			      double maximal_interval,
			      bool is_log_scale,
			      Markov_LA::M_Matrix<double> concentrations,
			      double trace_duratrion,
			      double trace_interval,
			      double frequency_of_sampling,
			      double exchange_time,
			      double sub_step_time,
			      Borrowed::MersenneTwister::MTRand& sto):
     name_(name),
     ton_d(time_of_pulse),
     durpul_min_d(minimal_pulse_duration),
     durpul_max_d(maximal_pulse_duration),
     interval_min_d(minimal_interval),
     interval_max_d(maximal_interval),
     log_scale_b(is_log_scale),
     con_M(concentrations),
     tracedur_d(trace_duratrion),
     trace_interval_d(trace_interval),
     fs_d(frequency_of_sampling),
     exchange_d(exchange_time),
     sub_step_time_d(sub_step_time),
     PP_PP()
 {
   // not complete, just copied from other
   ASSERT_GEQ(con_M,0.00);
   ASSERT_GEQ(ton_d,0.0);
   ASSERT_LEQ(ton_d,tracedur_d);
   ASSERT_LEQ(0.00,exchange_d);
   ASSERT_LESS(exchange_d*5,tracedur_d);
   ASSERT_LEQ(sub_step_time_d,1.0/fs_d);


     std::vector<double> ton_v,xon_v;
     ton_v.push_back(0);
     xon_v.push_back(0);

     if (log_scale_b)
     {
	 double log_dur_diff=log(durpul_max_d/durpul_min_d);
	 double log_interval_diff=log(interval_max_d/interval_min_d);
	 double next_ton=ton_d;

	 double next_toff=next_ton+durpul_min_d*exp(sto.rand(log_dur_diff));
	 if (next_toff>=tracedur_d)
	 {
	     std::cout<<"pulse too long for the trace duration \n";
	 }

     while (next_toff<tracedur_d-ton_d)
	 {
	     ton_v.push_back(next_ton);
	     ton_v.push_back(next_toff);
	     xon_v.push_back(1);
	     xon_v.push_back(0);
	     next_ton=next_toff+interval_min_d*exp(sto.rand(log_interval_diff));
	     next_toff=next_ton+durpul_min_d*exp(sto.rand(log_dur_diff));
	 }
     }
     else
     {
	 double next_ton=ton_d;
	 double next_toff=next_ton+
		 1./(1./durpul_max_d+sto.rand(1./durpul_min_d-1./durpul_max_d));

     while (next_toff<tracedur_d-ton_d)
	 {
	     ton_v.push_back(next_ton);
	     ton_v.push_back(next_toff);
	     xon_v.push_back(1);
	     xon_v.push_back(0);
	     next_ton=next_toff+1./
		     (1./interval_max_d+
		      sto.rand(1./interval_min_d-1./interval_max_d)
		      );
	     next_toff=next_ton+
		     1./(1./durpul_max_d+sto.rand(1./durpul_min_d-1./durpul_max_d));
	 }
     }

     Markov_LA::M_Matrix<double> ton_pulse(1,ton_v.size(),ton_v);
     Markov_LA::M_Matrix<double> x_at_ton(1,xon_v.size(),xon_v);

     std::vector<Pulses_trace> traces;


     Pulses_trace p0("random_trace",
		     ton_pulse,
		     x_at_ton,
		     tracedur_d,
		     fs_d,
		     exchange_d,
		     sub_step_time_d,
		     trace_interval_d);
     traces.push_back(p0);

     Markov_LA::M_Matrix<std::size_t> to_i_trace(1,size(con_M));
     Markov_LA::M_Matrix<double> trace_con(1,size(con_M));
     for (std::size_t i=0; i<size(con_M); i++)
     {
	 to_i_trace(0,i)=0;
	 trace_con(0,i)=con_M[i];
     };

     PP_PP=Pulses_program("Random_Pulses_Program",traces,to_i_trace,trace_con);
 };

 Random_Pulses::Random_Pulses():
     name_(""),
     ton_d(0),
     durpul_min_d(1e-5),
     durpul_max_d(1e-5),
     interval_min_d(1e-5),
     interval_max_d(1e-5),
     log_scale_b(true),
     con_M(Markov_LA::M_Matrix<double>(1,1)),
     tracedur_d(1),
     trace_interval_d(10),
     fs_d(10e3),
     exchange_d(0),
     sub_step_time_d(2e-6),
     PP_PP() {}




 Random_Pulses::Random_Pulses(const Random_Pulses& other):
     name_(other.name_),
     ton_d(other.ton_d),
     durpul_min_d(other.durpul_min_d),
     durpul_max_d(other.durpul_max_d),
     interval_min_d(other.interval_min_d),
     interval_max_d(other.interval_max_d),
     log_scale_b(other.log_scale_b),
     con_M(other.con_M),
     tracedur_d(other.tracedur_d),
     trace_interval_d(other.trace_interval_d),
     fs_d(other.fs_d),
     exchange_d(other.exchange_d),
     sub_step_time_d(other.sub_step_time_d),
     PP_PP(other.PP_PP) {}




 void swap(Random_Pulses& one,Random_Pulses& other)
 {
     using std::swap;
     swap(one.name_,other.name_);
     swap(one.ton_d,other.ton_d);
     swap(one.durpul_min_d,other.durpul_min_d);
     swap(one.durpul_max_d,other.durpul_max_d);
     swap(one.interval_min_d,other.interval_min_d);
     swap(one.interval_max_d,other.interval_max_d);
     swap(one.log_scale_b,other.log_scale_b);
     swap(one.con_M,other.con_M);
     swap(one.tracedur_d,other.tracedur_d);
     swap(one.trace_interval_d,other.trace_interval_d);
     swap(one.fs_d,other.fs_d);
     swap(one.exchange_d,other.exchange_d);
     swap(one.sub_step_time_d,other.sub_step_time_d);
     swap(one.PP_PP,other.PP_PP);

 }





 ClassDescription Random_Pulses::GetDescription()const
 {
     ClassDescription desc(myClass(),mySuperClass());;
     desc.push_back("name",name_);
     desc.push_back("time_of_pulse",ton_d);
     desc.push_back("minimal_pulse_duration",durpul_min_d);
     desc.push_back("maximal_pulse_duration",durpul_max_d);
     desc.push_back("minimal_interval",interval_min_d);
     desc.push_back("maximal_interval",interval_max_d);
     desc.push_back("is_log_scale",log_scale_b);
     desc.push_back("concentrations",con_M);
     desc.push_back("trace_duratrion",tracedur_d);
     desc.push_back("trace_interval",trace_interval_d);
     desc.push_back("frequency_of_sampling",fs_d);
     desc.push_back("exchange_time",exchange_d);
     desc.push_back("sub_step_time",sub_step_time_d);
     return desc;
 }

 std::string Random_Pulses::ClassName()
 {
     return "Random_Pulses";
 }


 std::vector<std::string> Random_Pulses::parentClasses()
 {
     std::vector<std::string> v;
     v.push_back(Markov_IO::ABC_Experiment::ClassName());

    return v;

 }

 std::vector<std::string> Random_Pulses::childClasses()
 {
     std::vector<std::string> v;
     return v;
 }

  bool Random_Pulses::amIAbstract()const
 {
     return false;
 }

  std::vector<std::string>  Random_Pulses::myParentClasses()const
 {
     return parentClasses();
 }
  std::vector<std::string>  Random_Pulses::myChildClasses()const
 {
     return childClasses();
 }





 std::string Random_Pulses::myName()const
 {
     return name_;
 };

 std::string Random_Pulses::myClass()const
 {
     return ClassName();
 }

 bool Random_Pulses::LoadFromDescription(
     const Markov_IO::ClassDescription& classDes)
 {
     if (classDes.ClassName()!=myClass())
	 return false;

     std::string name;
     if (!ToValue(classDes["name"],name))
	 return false;


     double time_of_pulse;
     if (!ToValue(classDes["time_of_pulse"],time_of_pulse))
	 return false;

     double minimal_pulse_duration;
     if (!ToValue(classDes["minimal_pulse_duration"],minimal_pulse_duration))
	 return false;

     double maximal_pulse_duration;
     if (!ToValue(classDes["maximal_pulse_duration"],maximal_pulse_duration))
	 return false;

     double minimal_interval;
     if (!ToValue(classDes["minimal_interval"],minimal_interval))
	 return false;

     double maximal_interval;
     if (!ToValue(classDes["maximal_interval"],maximal_interval))
	 return false;

     bool is_log_scale;
     if (!ToValue(classDes["is_log_scale"],is_log_scale))
	 return false;

     Markov_LA::M_Matrix<double> concentrations;
     if (!ToValue(classDes["concentrations"],concentrations))
	 return false;

     double trace_duratrion;
     if (!ToValue(classDes["trace_duratrion"],trace_duratrion))
	 return false;

     double trace_interval;
     if (!ToValue(classDes["trace_interval"],trace_interval))
	 return false;

     double frequency_of_sampling;
     if (!ToValue(classDes["frequency_of_sampling"],frequency_of_sampling))
	 return false;

     double exchange_time;
     if (!ToValue(classDes["exchange_time"],exchange_time))
	 return false;

     double sub_step_time;
     if (!ToValue(classDes["sub_step_time"],sub_step_time))
	 return false;
     Borrowed::MersenneTwister::MTRand* sto;
     sto=new Borrowed::MersenneTwister::MTRand();

     Random_Pulses tmp(name,
			 time_of_pulse,
			 minimal_pulse_duration,
			 maximal_pulse_duration,
			 minimal_interval,
			 maximal_interval,
			 is_log_scale,
			 concentrations,
			 trace_duratrion,
			 trace_interval,
			 frequency_of_sampling,
			 exchange_time,
			 sub_step_time,
			 *sto);
     swap(*this, tmp);
     return true;
 }









}
