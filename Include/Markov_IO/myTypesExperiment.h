#ifndef MYTYPESEXPERIMENT_H
#define MYTYPESEXPERIMENT_H
#include "Markov_IO/ABC_Experiment.h"
#include "Markov_IO/SinglePulses.h"
#include "Markov_Console/Markov_CommandManager.h"

#include "Markov_LA/matrixMaxMin.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_IO/VarTempl.h"
namespace Markov_IO_New {

  namespace _private
  {
    namespace _experiment {

      struct num_Tested_Concentrations_Field
      {
        typedef std::size_t myC;
        static std::string myId(){return "num_Tested_Concentrations";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "number of tested concentrations";}
        static std::string myWhatThis() {return "number of different concentrations tested in the program";}
      };


      inline
      std::size_t getNumConcentrations(const StructureEnv_New* cm)
      {
        std::size_t num;
        std::string WhyNot;
        if (!cm->getValueFromId(num_Tested_Concentrations_Field::myId(),num,&WhyNot,""))
          return 1;
        else return num;

      }
      inline
      std::size_t oneDim(const StructureEnv_New*)
      {
        return 1;
      }



      struct time_of_pulse_field
      {
        typedef  double myC;
        typedef  Real::types::positive vType;

        static std::string myId(){return "time_of_pulse";}
        static std::string myIdType(){return vType::myId();}
        static std::string myTip(){return "time to the begining of pulse";}
        static std::string myWhatThis() {return "";}
      };

      struct pulse_duration_field
      {
        typedef  double myC;
        typedef  Real::types::positive vType;

        static std::string myId(){return "pulse_duration";}
        static std::string myIdType(){return vType::myId();}
        static std::string myTip(){return "time duration of pulse";}
        static std::string myWhatThis() {return "";}
      };


      struct pulse_concentration_vector_type

      {
        typedef pulse_concentration_vector_type selfType;

        typedef double elem;
        typedef  ::Markov_LA::M_Matrix<elem> myC;
        typedef Implements_Data_Type_New<myC> vType;

        static std::string myId(){return "pulse_concentation_vector_type";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "list of concentration tested";}
        static std::string myWhatThis() {return "";}


        static bool comply
        (const StructureEnv_New* cm
         ,const myC & x
         ,const vType* self,
         std::string *WhyNot
         , const std::string& objective)
        {
            std::size_t numstates;
            if (!cm->getValueFromId(num_Tested_Concentrations_Field::myId(),numstates,WhyNot,objective))
              return false;
            if (!Matrix::Comply::Size<elem>(x,1,numstates,WhyNot,objective))
              return false;

            return true;
          }

        static const Implements_Data_Type_New<elem>* elementType
        (const StructureEnv_New* cm, std::string *whyNot,const std::string& masterObjective)
        {
          return cm->idToTyped<elem>(Real::types::positive::myId(),whyNot,masterObjective);
        }

        static std::size_t getColsNumber
        (const StructureEnv_New* cm
         ,const vType* cv)
        {
          return getNumConcentrations(cm);
        }

        static std::size_t getRowsNumber
        (const StructureEnv_New* cm
         ,const vType* cv)
        {
          return oneDim(cm);
        }

        static constexpr bool areColsFixed=false;
        static constexpr bool areRowsFixed=true;


        static Implements_Data_Type_New<myC>*
        varType(const StructureEnv_New* cm
                ,std::string* whyNot=nullptr,const std::string& masterObjective="")
        {
          auto d=elementType(cm,whyNot,masterObjective);
          if (d==nullptr)
            return nullptr;
          else
            {
              return new Implements_Data_Type_New<myC>
                  (d,&comply,nullptr,&getColsNumber,&getRowsNumber
                   ,areColsFixed,areRowsFixed);
            }
        }


        static void push_Types(Markov_CommandManagerVar *cm)
        {
          cm->pushType(myId(),varType(cm),myTip(),myWhatThis());
          cm->pushRegularType<elem>();
        }

      };

      struct pulse_concentration_vector_field
      {
        typedef  pulse_concentration_vector_type vType;
        typedef  typename vType::myC   myC;

        static std::string myId(){return "pulse_concentration_vector";}
        static std::string myIdType(){return vType::myId();}
        static std::string myTip(){return "list of concentrations during succesive pulsed applications";}
        static std::string myWhatThis() {return "";}
      };


      struct control_duration_field
      {
        typedef  double myC;
        typedef  Real::types::positive vType;

        static std::string myId(){return "control_duration";}
        static std::string myIdType(){return vType::myId();}
        static std::string myTip(){return "time duration of control pulse";}
        static std::string myWhatThis() {return "this pulse is set to establish the maximal response";}
      };


      struct control_concentration_field
      {
        typedef  double myC;
        typedef  Real::types::positive vType;

        static std::string myId(){return "control_concentration";}
        static std::string myIdType(){return vType::myId();}
        static std::string myTip(){return "concentration of the control pulse";}
        static std::string myWhatThis() {return "";}
      };


      struct trace_duration_type

      {
        typedef trace_duration_type selfType;

        typedef  double myC;
        typedef Implements_Data_Type_New<myC> vType;

        static std::string myId(){return "trace_duration_type";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "duration of trace";}
        static std::string myWhatThis() {return "it has to be greater than the sum "
              " of pulse duration and two times the time of pulse";}


        static bool comply
        (const StructureEnv_New* cm
         ,const myC & x
         ,const vType* self,
         std::string *WhyNot
         , const std::string& objective)
        {
            double time_of_pulse;
            double durpul;
            if (!cm->getValueFromId
                (time_of_pulse_field::myId(),time_of_pulse,WhyNot,objective))
              return false;
            if (!cm->getValueFromId
                (control_duration_field::myId(),durpul,WhyNot,objective))
              return false;
            if (x<2*time_of_pulse+durpul)
              return false;

            return true;
          }

        static std::set<std::string> alternativeNext
        (const StructureEnv_New* cm
         ,const vType* self)
        {
          double time_of_pulse;
          double durpul;
          std::string WhyNot;
          auto objective="";
          if (!cm->getValueFromId
              (time_of_pulse_field::myId(),time_of_pulse,&WhyNot,objective))
            return {};
          if (!cm->getValueFromId
              (control_duration_field::myId(),durpul,&WhyNot,objective))
            return {};

          return {std::to_string(2*time_of_pulse+durpul)+"<or greatear>"};
        }


        static Implements_Data_Type_New<myC>*
        varType(const StructureEnv_New* cm
                ,std::string* whyNot=nullptr,const std::string& masterObjective="")
        {
              return new Implements_Data_Type_New<myC>
                  (&comply,&alternativeNext);
        }


        static void push_Types(Markov_CommandManagerVar *cm)
        {
          cm->pushType(myId(),varType(cm),myTip(),myWhatThis());
        }

      };


      struct trace_duration_field
      {
        typedef  double myC;
        typedef  trace_duration_type vType;

        static std::string myId(){return "trace_duration_field";}
        static std::string myIdType(){return vType::myId();}
        static std::string myTip(){return "duration of trace";}
        static std::string myWhatThis() {return "";}
      };


      struct intertrace_interval_field
      {
        typedef  double myC;
        typedef  Real::types::positive vType;

        static std::string myId(){return "intertrace_interval";}
        static std::string myIdType(){return vType::myId();}
        static std::string myTip(){return "time duration of interval up to next trace";}
        static std::string myWhatThis() {return "this pulse is set to establish the maximal response";}
      };



      struct frequency_of_sampling_type

      {
        typedef frequency_of_sampling_type selfType;

        typedef  double myC;
        typedef Implements_Data_Type_New<myC> vType;

        static std::string myId(){return "frequency_of_sampling_type";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "frequency of sampling";}
        static std::string myWhatThis() {return "it has to be greater than the sum "
              " of pulse duration and two times the time of pulse";}


        static bool comply
        (const StructureEnv_New* cm
         ,const myC & x
         ,const vType* self,
         std::string *WhyNot
         , const std::string& objective)
        {
            double tracedur;
            if (!cm->getValueFromId
                (trace_duration_field::myId(),tracedur,WhyNot,objective))
              return false;
            if (x<3.0/tracedur)
              return false;

            return true;
          }

        static std::set<std::string> alternativeNext
        (const StructureEnv_New* cm
         ,const vType* self)
        {
          double tracedur;
          std::string WhyNot;
          auto objective="";
          if (!cm->getValueFromId
              (trace_duration_field::myId(),tracedur,&WhyNot,objective))
            return {};

          return {std::to_string(3.0/tracedur)+"<or greatear>"};
        }


        static Implements_Data_Type_New<myC>*
        varType(const StructureEnv_New* cm
                ,std::string* whyNot=nullptr,const std::string& masterObjective="")
        {
              return new Implements_Data_Type_New<myC>
                  (&comply,&alternativeNext);
        }


        static void push_Types(Markov_CommandManagerVar *cm)
        {
          cm->pushType(myId(),varType(cm),myTip(),myWhatThis());
        }

      };


      struct frequency_of_sampling_field
      {
        typedef  double myC;
        typedef  frequency_of_sampling_type vType;

        static std::string myId(){return "frequency_of_sampling";}
        static std::string myIdType(){return vType::myId();}
        static std::string myTip(){return "duration of trace";}
        static std::string myWhatThis() {return "";}
      };


      struct time_to_exchange_type

      {
        typedef time_to_exchange_type selfType;

        typedef  double myC;
        typedef Implements_Data_Type_New<myC> vType;

        static std::string myId(){return "time_to_exchange_type";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "time to complete exchange";}
        static std::string myWhatThis() {return "it has to be shorter than one third of the trace duration ";}


        static bool comply
        (const StructureEnv_New* cm
         ,const myC & x
         ,const vType* self,
         std::string *WhyNot
         , const std::string& objective)
        {
            double tracedur;
            if (!cm->getValueFromId
                (trace_duration_field::myId(),tracedur,WhyNot,objective))
              return false;
            if (x>tracedur/3.0)
              return false;


            return true;
          }

        static std::set<std::string> alternativeNext
        (const StructureEnv_New* cm
         ,const vType* self)
        {
          double tracedur;
          std::string WhyNot;
          auto objective="";
          if (!cm->getValueFromId
              (trace_duration_field::myId(),tracedur,&WhyNot,objective))
            return {};

          return {std::to_string(tracedur/3.0)+"<or smaller>"};
        }


        static Implements_Data_Type_New<myC>*
        varType(const StructureEnv_New* cm
                ,std::string* whyNot=nullptr,const std::string& masterObjective="")
        {
              return new Implements_Data_Type_New<myC>
                  (&comply,&alternativeNext);
        }


        static void push_Types(Markov_CommandManagerVar *cm)
        {
          cm->pushType(myId(),varType(cm),myTip(),myWhatThis());
        }

      };


      struct time_to_exchange_field
      {
        typedef  double myC;
        typedef  time_to_exchange_type vType;

        static std::string myId(){return "time_to_exchange";}
        static std::string myIdType(){return vType::myId();}
        static std::string myTip(){return "constant time of solution exchange";}
        static std::string myWhatThis() {return "";}
      };


      struct sub_step_time_type

      {
        typedef sub_step_time_type selfType;

        typedef  double myC;
        typedef Implements_Data_Type_New<myC> vType;

        static std::string myId(){return "sub_step_time_type";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "minimal step time for calculations";}
        static std::string myWhatThis() {return "it has to be shorter than one third of the trace duration ";}


        static bool comply
        (const StructureEnv_New* cm
         ,const myC & x
         ,const vType* self,
         std::string *WhyNot
         , const std::string& objective)
        {
            double tracedur;
            if (!cm->getValueFromId
                (trace_duration_field::myId(),tracedur,WhyNot,objective))
              return false;
            if (x>tracedur/3.0)
              return false;

            return true;
          }

        static std::set<std::string> alternativeNext
        (const StructureEnv_New* cm
         ,const vType* self)
        {
          double tracedur;
          std::string WhyNot;
          auto objective="";
          if (!cm->getValueFromId
              (trace_duration_field::myId(),tracedur,&WhyNot,objective))
            return {};

          return {std::to_string(tracedur/3.0)+"<or smaller>"};
        }


        static Implements_Data_Type_New<myC>*
        varType(const StructureEnv_New* cm
                ,std::string* whyNot=nullptr,const std::string& masterObjective="")
        {
              return new Implements_Data_Type_New<myC>
                  (&comply,&alternativeNext);
        }


        static void push_Types(Markov_CommandManagerVar *cm)
        {
          cm->pushType(myId(),varType(cm),myTip(),myWhatThis());
        }

      };


      struct sub_step_time_field
      {
        typedef  double myC;
        typedef  sub_step_time_type vType;

        static std::string myId(){return "sub_step_time";}
        static std::string myIdType(){return vType::myId();}
        static std::string myTip(){return "time step used for calculations";}
        static std::string myWhatThis() {return "";}
      };



      struct Single_Pulses_type {
        typedef ABC_Experiment myB;
        typedef Single_Pulses myD;
        typedef Implements_Data_Type_derived_class<myD,myB>  vType;

        static std::string myId(){return Cls<myD*>::name();}
        static std::string myIdType(){return Cls<myD*>::name();}
        static std::string myTip(){return "Single pulses protocol type";}
        static std::string myWhatThis(){return "";}

        static myD* map2obj(const StructureEnv_New* cm,
                            const StructureEnv_New* m
                            ,const vType* v
                            ,std::string* WhyNot,
                            const std::string& masterObjective)
        {

          num_Tested_Concentrations_Field::myC num_Tested_Concentrations;
          time_of_pulse_field::myC time_of_pulse;
          pulse_duration_field::myC pulse_duration;
          pulse_concentration_vector_field::myC pulse_concentration_vector;
          control_duration_field::myC control_duration;
          control_concentration_field::myC control_concentration;
          trace_duration_field::myC  trace_duration;
          intertrace_interval_field::myC intertrace_interval;
          frequency_of_sampling_field::myC frequency_of_sampling;
          time_to_exchange_field::myC time_to_exchange;
          sub_step_time_field::myC sub_step_time;



          if (!m->getDataValue<num_Tested_Concentrations_Field>
               (num_Tested_Concentrations,WhyNot,masterObjective))
            return nullptr;
          else if (!m->getDataValue<time_of_pulse_field>
                   (time_of_pulse,WhyNot,masterObjective))
            return nullptr;
          else if (!m->getDataValue<pulse_duration_field>
                   (pulse_duration,WhyNot,masterObjective))
            return nullptr;
          else if (!m->getDataValue<pulse_concentration_vector_field>
                   (pulse_concentration_vector,WhyNot,masterObjective))
            return nullptr;
          else if (!m->getDataValue<control_duration_field>
                   (control_duration,WhyNot,masterObjective))
            return nullptr;
          else if (!m->getDataValue<control_concentration_field>
                   (control_concentration,WhyNot,masterObjective))
            return nullptr;
          else if (!m->getDataValue<trace_duration_field>
                   ( trace_duration,WhyNot,masterObjective))
            return nullptr;
          else if (!m->getDataValue<intertrace_interval_field>
                   ( intertrace_interval,WhyNot,masterObjective))
            return nullptr;
          else if (!m->getDataValue<frequency_of_sampling_field>
                   ( frequency_of_sampling,WhyNot,masterObjective))
            return nullptr;
          else if (!m->getDataValue<time_to_exchange_field>
                   ( time_to_exchange,WhyNot,masterObjective))
            return nullptr;
          else if (!m->getDataValue<sub_step_time_field>
                   ( sub_step_time,WhyNot,masterObjective))
            return nullptr;
          else return new Single_Pulses
              (time_of_pulse,pulse_duration,pulse_concentration_vector
,control_duration,control_concentration,trace_duration,intertrace_interval,
              frequency_of_sampling,time_to_exchange,sub_step_time);

        }




        static  StructureEnv_New* obj2map
        (const StructureEnv_New* cm,
         const myD* x
         ,const vType* v
         , std::string* WhyNot, const std::string& masterObjective)
        {


          auto f=new StructureEnv_New(cm,Cls<myB>::name());
          f->pushVar<num_Tested_Concentrations_Field>(::Markov_LA::ncols(x->pulse_concentration()));
          f->pushVar<time_of_pulse_field>(x->time_of_pulse());
          f->pushVar<pulse_duration_field>(x->pulse_duration());
          f->pushVar< pulse_concentration_vector_field>(x->pulse_concentration());
          f->pushVar< control_duration_field>(x->control_duration());
          f->pushVar< control_concentration_field>(x->control_concentration());
          f->pushVar< trace_duration_field>(x->trace_duration());
          f->pushVar< intertrace_interval_field>(x->intertrace_interval());
          f->pushVar< frequency_of_sampling_field>(x->fs());
          f->pushVar< time_to_exchange_field>(x->time_to_exchange());
          f->pushVar< sub_step_time_field>(x->sub_step_time());
          return f;
        }

        static std::vector<std::pair<Implements_Var,bool>> getFields()
        {
          std::vector<std::pair<Implements_Var,bool>> f;
          f.push_back({getMyVar<num_Tested_Concentrations_Field>(),true});
          f.push_back({getMyVar<time_of_pulse_field>(),true});
          f.push_back({getMyVar<pulse_duration_field>(),true});
          f.push_back({getMyVar<pulse_concentration_vector_field>(),true});
          f.push_back({getMyVar<control_duration_field>(),true});


          f.push_back({getMyVar<control_concentration_field>(),true});
          f.push_back({getMyVar<trace_duration_field>(),true});
          f.push_back({getMyVar<intertrace_interval_field>(),true});
          f.push_back({getMyVar<frequency_of_sampling_field>(),true});
          f.push_back({getMyVar<time_to_exchange_field>(),true});
          f.push_back({getMyVar<sub_step_time_field>(),true});

          return f;
        }

        static void push_Types(Markov_CommandManagerVar *cm)
        {
          cm->pushRegularType<double>();
          pulse_concentration_vector_type::push_Types(cm);
          time_to_exchange_type::push_Types(cm);
          trace_duration_type::push_Types(cm);
          sub_step_time_type::push_Types(cm);
          frequency_of_sampling_type::push_Types(cm);
          cm->pushType(myId(),varType(cm),myTip(),myWhatThis());

        }


        static Implements_Data_Type_New<myD*>*
        varType(const StructureEnv_New* cm)
        {
          return new  Implements_Data_Type_derived_class<myD,myB>
              (getFields(),&obj2map,&map2obj,nullptr,nullptr);
        }


      };


      inline void push_Types(Markov_CommandManagerVar* cm)
      {
        Single_Pulses_type::push_Types(cm);
      }

    }



  };



}


#endif // MYTYPESEXPERIMENT_H
