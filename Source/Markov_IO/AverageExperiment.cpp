#include "Markov_IO/AverageExperiment.h"
#include "Markov_IO/Experiment.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_LA/auxiliarMath.h"

namespace Markov_IO
{

std::string AverageExperiment::ClassName()
{
    return "AverageExperiment";
}


AverageExperiment* AverageExperiment::clone() const
{
    return new AverageExperiment(*this);
}

/// default constructors
AverageExperiment* AverageExperiment::create() const
{
    return new AverageExperiment();
}

AverageExperiment::~AverageExperiment()
{}

 std::string AverageExperiment::myName()const
{
    return name_;
}
 std::string AverageExperiment::myClass()const
{
    return ClassName();
}



bool AverageExperiment::amIAbstract() const
{
    return true;
}



 Experiment AverageExperiment::run(const Markov_IO::ABC_Experiment& x)
{
     std::vector<Trace> tr;
     for (std::size_t i_trace=0; i_trace<x.num_traces();i_trace++)
    {
         x.trace(i_trace);
          std::vector<double> ts;
         std::vector<double>  ys;
         double t=0;
         x_step xs=x[0];
         x_step xs0=x_step(0,0);

         for (std::size_t i_sample=1; i_sample<x.num_measures(); i_sample++)
          {
             if (valid_step(xs))
            {
                ts.push_back(t);
                ys.push_back(xs.y());
                t+=xs.dt();
                xs0=xs;
                xs=x[i_sample];
            }
             else if (((xs.x()==0)&&(x[i_sample].x()!=0))||(i_sample==x.num_measures()))
            {
                 xs0+=xs;
                 if (ys.empty())
                 {
                     ys.push_back(xs0.y());
                     ts.push_back(t);
                 }
                 else
                     ys.back()=xs0.y();
                 t+=xs.dt();
                 xs=x[i_sample];
            }
            else
            {
                xs+=x[i_sample];
            }
        }
         ts.push_back(t);
         ys.push_back(xs.y());
         t+=xs.dt();
         ts.push_back(t);
         ys.push_back(Markov_LA::NaN());
         t+=x[x.num_measures()].dt();
         ts.push_back(t);
         ys.push_back(Markov_LA::NaN());





         Markov_LA::M_Matrix<double> ty(ts.size(),2);
         for (std::size_t i=0; i< ts.size(); i++)
         {
             ty(i,0)=ts[i];
             ty(i,1)=ys[i];
         }
         std::string name="Avg_"+x.myName()+"_"+ToString(i_trace);
         double time_interval=x[x.num_measures()].dt();
         tr.push_back(Trace(name,x.toTx(),ty,time_interval));

    }
     std::string name="Avg_"+x.myName();

     Experiment result(name,tr);
     return result;
    }




 bool AverageExperiment::valid_step(const ABC_measure_step& xs)
 {
     Markov_LA::ToleranceComparison<double> tol;
     if (tol.isLess(xs.dt(),1.0/max_f_)) return false;
     if (!tol.isLess(xs.dt(),this->min_dt_)) return true;
     if (!tol.isLess(xs.y(),min_y_)) return true;
     if (!tol.isLess(xs.y()*xs.dt(),min_y_dt_)) return true;
     return false;

 }







 AverageExperiment::AverageExperiment(const std::string& name,
                                      double max_f,
        double min_dt,
        double min_y,
        double min_y_dt):
     name_(name),
     max_f_(max_f),
     min_dt_(min_dt),
     min_y_(min_y),
     min_y_dt_(min_y_dt){}

 AverageExperiment::AverageExperiment(const std::string name, AverageExperiment::Options op):
     name_(name),
     max_f_(op.real("maximal_frequency")),
     min_dt_(op.real("minimal_time_step")),
     min_y_(op.real("mininal_y_value")),
     min_y_dt_(op.real("minimal_product_y_dt")){}

 AverageExperiment::AverageExperiment():
     name_(),
     max_f_(),
     min_dt_(),
     min_y_(),
     min_y_dt_(){}

 ClassDescription AverageExperiment::GetDescription()const
{
    ClassDescription desc(myClass(),mySuperClass());;

    desc.push_back("name",name_);
    desc.push_back("maximal_frequency",max_f_);
    desc.push_back("minimal_time_step",min_dt_);
    desc.push_back("mininal_y_value",min_y_);
    desc.push_back("minimal_product_y_dt",min_y_dt_);

    return desc;
}

 bool AverageExperiment::LoadFromDescription(
     const ClassDescription& classDes)
 {
     if (classDes.ClassName()!=myClass())
     return false;
     std::string name;
      if (!ToValue(classDes["name"],name))
      return false;

      double maximal_frequency;
      if (!ToValue(classDes["maximal_frequency"],maximal_frequency))
      return false;


      double minimal_time_step;
     if (!ToValue(classDes["minimal_time_step"],minimal_time_step))
     return false;

     double mininal_y_value;
     if (!ToValue(classDes["mininal_y_value"],mininal_y_value))
     return false;

     double minimal_product_y_dt;
     if (!ToValue(classDes["minimal_product_y_dt"],minimal_product_y_dt))
     return false;


     *this=AverageExperiment(name,
                             maximal_frequency,
                  minimal_time_step,
                  mininal_y_value,
                  minimal_product_y_dt);

     return true;
 }





 AverageExperiment::Options::Options():
     BaseOptions("Deafault")
 {
     push_back("maximal_frequency",0.0,
               "measures taken at higher frequencies are averaged out",
               "it compulsively average measurements that are shorter than the measurement time "
               "that correspond to this frequency, even if they have more than the minimal current."
               "When the averaged interval gets longer than this value, it is tested using the other "
               "three comparisons. This value is important to remove the time correlation of the low pass filter. "
               "It should be at least equal to the filtering frequency. ");
     push_back("minimal_time_step",0.0,
               "if the measurements is longer than this value, it is not averaged",
               "it compares the duration of each measurement with this value: "
               "if it is longer, the interval is left as it is; "
               "if shorter, and it fails all the other two comparisons, "
               "the interval is lumped to the next and the resulting sum of measurements "
               "is compared again, until the sum of the intervals reaches or surpasses this value or the other"
               "two comparisons. A zero value implies no averaging at all."
               "This value is important for baseline measurements, where there is no much singnal");
     push_back("mininal_y_value",0.0,
               "if the absolute value of the current is bigger than this value, it is not averaged",
               "it compares the absolute value of each measurement with this value: "
               "if bigger, the measurement is left as it is; "
               "if smaller, the measurement is averaged with the next and compared in terms of the "
               "y x dt product. "
               "This value should be about 20-40 times the unitary conductance, so the gaussian approximation "
               "is right. ");
     push_back("minimal_product_y_dt",0.0,
               "if the time integral of the current gets bigger than this value, we stop adding intervals",
               "this value is important for current smaller than the minimal_y_value: when enough measurements "
               "had been added to a single averaged measure, the value of the integral of the current over time "
               "reaches this value. This value is important for the decay."
               "It should be 20-40 times the unitary conductance multiplied by the time constant of gating");

 }

 AverageExperiment::Options::Options(const std::string& name,
                                     double max_freq,
                                     double min_dt,
                                     double min_y,
                                     double min_y_dt):
     BaseOptions(name)
 {
     push_back("maximal_frequency",max_freq,
               "measures taken at higher frequencies are averaged out",
               "it compulsively average measurements that are shorter than the measurement time "
               "that correspond to this frequency, even if they have more than the minimal current."
               "When the averaged interval gets longer than this value, it is tested using the other "
               "three comparisons. This value is important to remove the time correlation of the low pass filter. "
               "It should be at least equal to the filtering frequency. ");
     push_back("minimal_time_step",min_dt,
               "it stops adding measurements when the maveraged step gets longer than this value",
               "it compares the duration of the growing averaged step with this value: "
               "if it is longer, it stops adding intervals; "
               "if shorter, it performs the other two comparisons, "
               "the interval is lumped to the next and the resulting sum of measurements "
               "is compared again, until the sum of the intervals reaches or surpasses this value or the other"
               "two comparisons. A zero value implies no averaging at all."
               "This value is important for baseline measurements, where there is no much singnal");
     push_back("mininal_y_value",min_y,
               "if the absolute value of the current is bigger than this value, it is not averaged",
               "it compares the absolute value of each measurement with this value: "
               "if bigger, the measurement is left as it is; "
               "if smaller, the measurement is averaged with the next and compared in terms of the "
               "y x dt product. "
               "This value should be about 20-40 times the unitary conductance, so the gaussian approximation "
               "is right. ");
     push_back("minimal_product_y_dt",min_y_dt,
               "if the time integral of the current gets bigger than this value, we stop adding intervals",
               "this value is important for current smaller than the minimal_y_value: when enough measurements "
               "had been added to a single averaged measure, the value of the integral of the current over time "
               "reaches this value. This value is important for the decay."
               "It should be 20-40 times the unitary conductance multiplied by the time constant of gating");
  }

 AverageExperiment::Options::Options(const Markov_IO::ABC_Options& O):
     BaseOptions(O.myName())
 {
     push_back("maximal_frequency",O.real("maximal_frequency"));
     push_back("minimal_time_step",O.real("minimal_time_step"));
     push_back("mininal_y_value",O.real("mininal_y_value"));
     push_back("minimal_product_y_dt",O.real("minimal_product_y_dt"));

 }
  std::string AverageExperiment::Options::myClass()const
  {return ClassName();}
  std::string AverageExperiment::Options::ClassName()
 {return "AverageExperiment_Options";}





}
