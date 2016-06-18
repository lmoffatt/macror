#ifndef MYTYPESEXPERIMENT_H
#define MYTYPESEXPERIMENT_H
#include "Markov_IO/ABC_Experiment.h"
#include "Markov_IO/SinglePulses.h"

#include "Markov_IO/PulsesTrace.h"
#include "Markov_IO/ABC_Trace.h"

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


      template<typename numField>
      std::size_t getNum(const StructureEnv_New* cm)
      {
        std::size_t num;
        std::string WhyNot;
        if (!cm->getValueFromId(numField::myId(),num,&WhyNot,""))
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
          return getNum<num_Tested_Concentrations_Field>(cm);
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


        static void push_Types(StructureEnv_New *cm)
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


        static void push_Types(StructureEnv_New *cm)
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


        static void push_Types(StructureEnv_New *cm)
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


        static void push_Types(StructureEnv_New *cm)
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


        static void push_Types(StructureEnv_New *cm)
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

        static void push_Types(StructureEnv_New *cm)
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
/******
 *
 *    fields of Pulses_trace
 *
 * **/



      struct number_of_concentration_changes_Field
      {
        typedef std::size_t myC;
        typedef Implements_Data_Type_New<myC>  vType;
        static std::string myId(){return "number_of_concentration_changes";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "number of changes in concentrations";}
        static std::string myWhatThis() {return "";}

      };



      struct time_of_each_concentration_change_type

      {
        typedef time_of_each_concentration_change_type selfType;

        typedef double elem;
        typedef  ::Markov_LA::M_Matrix<elem> myC;
        typedef Implements_Data_Type_New<myC> vType;

        static std::string myId(){return "time_of_each_concentration_change_vector_type";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "time for each concentration change";}
        static std::string myWhatThis() {return "";}


        static bool comply
        (const StructureEnv_New* cm
         ,const myC & x
         ,const vType* self,
         std::string *WhyNot
         , const std::string& objective)
        {
            std::size_t numstates;
            if (!cm->getValueFromId
                (number_of_concentration_changes_Field::myId()
                 ,numstates,WhyNot,objective))
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


        /// increasing
        static Implements_Data_Type_New<elem>* nextElement (
            const StructureEnv_New* cm
            ,const std::vector<elem>& val,
            std::size_t nrow, std::size_t ncol
            ,std::size_t i, std::size_t j
            ,const Implements_Data_Type_New<myC>* self
            , std::string * whyNot, const std::string& masterObjective,
            Implements_Data_Type_New<elem>* source)
        {
          if (j==0)
            return Real::types::Zero::varType(source);
          else
            return Real::types::greaterThan::varType(source,val[j-1]);
        }




        static std::size_t getColsNumber
        (const StructureEnv_New* cm
         ,const vType* cv)
        {
          return getNum<number_of_concentration_changes_Field>(cm);
        }

        static std::size_t getRowsNumber
        (const StructureEnv_New* cm
         ,const vType* cv)
        {
          return oneDim(cm);
        }

        static constexpr bool areColsFixed=true;
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
                  (d,&comply,&nextElement,&getColsNumber,&getRowsNumber
                   ,areColsFixed,areRowsFixed);
            }
        }


        static void push_Types(StructureEnv_New *cm)
        {
          cm->pushType(myId(),varType(cm),myTip(),myWhatThis());
          cm->pushRegularType<elem>();
        }

      };

      struct time_of_each_concentration_change_field
      {
        typedef  time_of_each_concentration_change_type vType;
        typedef  typename vType::myC   myC;

        static std::string myId(){return "time_of_each_concentration_change";}
        static std::string myIdType(){return vType::myId();}
        static std::string myTip(){return "time of each change in concentration of concentrations during succesive pulsed applications";}
        static std::string myWhatThis() {return "";}
      };




      struct concentration_at_each_time_type

      {
        typedef concentration_at_each_time_type selfType;

        typedef double elem;
        typedef  ::Markov_LA::M_Matrix<elem> myC;
        typedef Implements_Data_Type_New<myC> vType;

        static std::string myId(){return "concentration_at_each_time_type";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "concentration after each change";}
        static std::string myWhatThis() {return "";}


        static bool comply
        (const StructureEnv_New* cm
         ,const myC & x
         ,const vType* self,
         std::string *WhyNot
         , const std::string& objective)
        {
            std::size_t numstates;
            if (!cm->getValueFromId
                (number_of_concentration_changes_Field::myId()
                 ,numstates,WhyNot,objective))
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


        /// increasing
        static Implements_Data_Type_New<elem>* nextElement (
            const StructureEnv_New* cm
            ,const std::vector<elem>& val,
            std::size_t nrow, std::size_t ncol
            ,std::size_t i, std::size_t j
            ,const Implements_Data_Type_New<myC>* self
            , std::string * whyNot, const std::string& masterObjective,
            Implements_Data_Type_New<elem>* source)
        {
          return source;
        }




        static std::size_t getColsNumber
        (const StructureEnv_New* cm
         ,const vType* cv)
        {
          return getNum<number_of_concentration_changes_Field>(cm);
        }

        static std::size_t getRowsNumber
        (const StructureEnv_New* cm
         ,const vType* cv)
        {
          return oneDim(cm);
        }

        static constexpr bool areColsFixed=true;
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
                  (d,&comply,&nextElement,&getColsNumber,&getRowsNumber
                   ,areColsFixed,areRowsFixed);
            }
        }


        static void push_Types(StructureEnv_New *cm)
        {
          cm->pushType(myId(),varType(cm),myTip(),myWhatThis());
          cm->pushRegularType<elem>();
        }

      };

      struct concentration_at_each_time_field
      {
        typedef  time_of_each_concentration_change_type vType;
        typedef  typename vType::myC   myC;

        static std::string myId(){return "concentration_at_each_time";}
        static std::string myIdType(){return vType::myId();}
        static std::string myTip(){return "concentration after each corresponding change";}
        static std::string myWhatThis() {return "";}
      };






      struct Pulses_trace_type {
        typedef ABC_trace myB;
        typedef Pulses_trace myD;
        typedef Implements_Data_Type_derived_class<myD,myB>  vType;

        static std::string myId(){return Cls<myD*>::name();}
        static std::string myIdType(){return Cls<myD*>::name();}
        static std::string myTip(){return "Program of change in concentrations for a single trace";}
        static std::string myWhatThis(){return "";}

        template<typename Field>
        static bool isMandatory() {return true;}


        template<typename Field>
        static typename Field::myC get(const myD* x);




        static myD* map2obj(const StructureEnv_New* cm,
                            const StructureEnv_New* m
                            ,const vType* v
                            ,std::string* WhyNot,
                            const std::string& masterObjective)
        {

           return map2objTempl<Pulses_trace_type
               ,time_of_each_concentration_change_field
               ,concentration_at_each_time_field
               ,trace_duration_field
               ,frequency_of_sampling_field
               ,time_to_exchange_field
               ,sub_step_time_field
               ,intertrace_interval_field>(cm,m,v,WhyNot,masterObjective);

        }


        static  StructureEnv_New* obj2map
        (const StructureEnv_New* cm,
         const myD* x
         ,const vType* v
         , std::string* WhyNot, const std::string& masterObjective)
        {
          return obj2mapTempl<Pulses_trace_type
              ,number_of_concentration_changes_Field
              ,time_of_each_concentration_change_field
              ,concentration_at_each_time_field
              ,trace_duration_field
              ,frequency_of_sampling_field
              ,time_to_exchange_field
              ,sub_step_time_field
              ,intertrace_interval_field>(cm,x,v,WhyNot,masterObjective);

        }

        static std::vector<std::pair<Implements_Var,bool>> getFields()
        {
          return getFieldsTempl<Pulses_trace_type
              ,number_of_concentration_changes_Field
              ,time_of_each_concentration_change_field
              ,concentration_at_each_time_field
              ,trace_duration_field
              ,frequency_of_sampling_field
              ,time_to_exchange_field
              ,sub_step_time_field
              ,intertrace_interval_field>();

        }

        static Implements_Data_Type_New<myD*>*
        varType(const StructureEnv_New* cm)
        {
          return new  Implements_Data_Type_derived_class<myD,myB>
              (getFields(),&obj2map,&map2obj,nullptr,nullptr);
        }





        static void push_Types(StructureEnv_New *cm)
        {
          push_TypesTempl<Pulses_trace_type
              ,number_of_concentration_changes_Field
              ,time_of_each_concentration_change_field
              ,concentration_at_each_time_field
              ,trace_duration_field
              ,frequency_of_sampling_field
              ,time_to_exchange_field
              ,sub_step_time_field
              ,intertrace_interval_field>(cm);
        }
       };

      template<>
      inline
      typename number_of_concentration_changes_Field::myC
      Pulses_trace_type::get<number_of_concentration_changes_Field>
      (const typename Pulses_trace_type::myD* x)
      {
         return x->number_of_concentration_changes();
      }


      template<>
      inline
      typename time_of_each_concentration_change_field::myC
      Pulses_trace_type::get<time_of_each_concentration_change_field>
      (const typename Pulses_trace_type::myD* x)
      {
         return x->time_of_each_concentration_change();
      }

      template<>
      inline
      typename concentration_at_each_time_field::myC
      Pulses_trace_type::get<concentration_at_each_time_field>
      (const typename Pulses_trace_type::myD* x)
      {
         return x->concentration_at_each_time();
      }

      template<>
      inline
      typename trace_duration_field::myC
      Pulses_trace_type::get<trace_duration_field>
      (const typename Pulses_trace_type::myD* x)
      {
         return x->trace_duration();
      }

      template<>
      inline
      typename frequency_of_sampling_field::myC
      Pulses_trace_type::get<frequency_of_sampling_field>
      (const typename Pulses_trace_type::myD* x)
      {
         return x->frequency_of_sampling();
      }
      template<>
      inline
      typename time_to_exchange_field::myC
      Pulses_trace_type::get<time_to_exchange_field>
      (const typename Pulses_trace_type::myD* x)
      {
         return x->time_to_exchange();
      }

      template<>
      inline
      typename time_to_exchange_field::myC
      Pulses_trace_type::get<sub_step_time_field>
      (const typename Pulses_trace_type::myD* x)
      {
         return x->sub_step_time();
      }

      template<>
      inline
      typename time_to_exchange_type::myC
      Pulses_trace_type::get<time_to_exchange_type>
      (const typename Pulses_trace_type::myD* x)
      {
         return x->time_to_exchange();
      }


      template<>
      inline
      typename intertrace_interval_field::myC
      Pulses_trace_type::get<intertrace_interval_field>
      (const typename Pulses_trace_type::myD* x)
      {
         return x->time_to_next_trace();
      }





      inline void push_Types(StructureEnv_New *cm)
      {
        Single_Pulses_type::push_Types(cm);
        Pulses_trace_type::push_Types(cm);
      }

    }



  };



}


#endif // MYTYPESEXPERIMENT_H
