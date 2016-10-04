#ifndef FUNCTIONCOMMAND_H
#define FUNCTIONCOMMAND_H

#include "Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_IO/Implements_path.h"
#include "Markov_IO/buildClosureByToken_Templ.h"

#include "Markov_IO/VarTempl.h"

#include "Markov_IO/buildClosureByToken.h"
#include "Markov_IO/Implements_Closures.h"
#include "Markov_Console/Markov_CommandManager.h"

#include "Markov_IO/myTypes.h"
#include "Markov_IO/myTypesExperiment.h"
#include "Markov_Bay/myTypes_Bayesian.h"

namespace Markov_Bay_New
{
  class LikelihoodEvaluation;
}


namespace Markov_IO_New
{
  namespace argFunc {
    struct typeName_Field
    {
      typedef std::string myC;
      typedef Identifier::types::idType myType;
      typedef Implements_Identifier vType;

      static std::string myId(){return "typeName";}
      static std::string myIdType(){return myType::myId();}
      static std::string myTip(){return "a type of variable";}
      static std::string myWhatThis() {return "different types of variables";}
    };

    struct fileName_FieldUsed
    {
      typedef std::string myC;
      typedef pathName::types::filenameUsed myType;
      typedef Implements_Identifier vType;

      static std::string myId(){return "typeName";}
      static std::string myIdType(){return myType::myId();}
      static std::string myTip(){return "a type of variable";}
      static std::string myWhatThis() {return "different types of variables";}
    };




  }




  namespace funct {

    void pushAllFunctions(Markov_CommandManagerVar *cm);


    namespace arg
    {


      struct workingPath_arg
      {
        typedef std::string myC;
        typedef Implements_Fn_Argument<myC> argType;




      };


    }






    struct Save {
      typedef Implements_Closure_Type<void*>  vType;

      static std::string myId(){return "save";}
      static std::string myTip(){return "Save variables";}
      static std::string myWhatThis(){return "";}

      struct save_cm
      {
        static void save(Markov_CommandManagerVar* cm,
                         const std::string& pathfileName);

        typedef save_cm selfType;

        typedef void returnType;
        typedef std::tuple<Markov_CommandManagerVar*,std::string> argTypes;

        typedef decltype(&save)  funType;

        typedef
        mp_append
        <
        Implements_Closure_Type<returnType,void,funType>,argTypes
        >
        ClosureType;


        static const Implements_Data_Type_New<returnType>*
        getReturnType(Markov_CommandManagerVar* cm)
        {
          return cm->idToTyped<returnType>(Cls<returnType>::name());
        }


        static Implements_Closure_Type<argTypes>*
        getArgumentTypes(Markov_CommandManagerVar* cm)
        {
          return new Implements_Closure_Type<argTypes>(
                Implements_Fn_Argument<Markov_CommandManagerVar*>
                (new _private::Implements_Closure_Value_Markov_CommandManagerVar_Self()),
                Implements_Fn_Argument<std::string>(cm,
                                                    "file name",
                                                    "macror.txt",
                                                    "filename where to save the data","")
                );

        }


        static ClosureType*
        closureType(Markov_CommandManagerVar* cm)
        {
          return new ClosureType(getReturnType(cm),save,getArgumentTypes(cm));
        }

        typedef mp_list<> dependsOn;
      };





      static vType*
      functionType(Markov_CommandManagerVar* cm)
      {
        auto out= new  Implements_Closure_Type<void*>
            (myId(),Identifier::types::idCmdGiven::varType(myId()));
        out->push_overload(cm,save_cm::closureType(cm));
        return out;



      }





    };


    struct Load {
      typedef Implements_Closure_Type<void*>  vType;

      static std::string myId(){return "load";}
      static std::string myTip(){return "load variables";}
      static std::string myWhatThis(){return "";}

      struct load_cm
      {
        static void load(Markov_CommandManagerVar* cm,
                         const std::string& pathfileName);

        typedef load_cm selfType;

        typedef void returnType;
        typedef std::tuple<Markov_CommandManagerVar*,std::string> argTypes;

        typedef decltype(&load)  functionType;

        typedef
        mp_append
        <
        Implements_Closure_Type<returnType,void,functionType>,argTypes
        >
        ClosureType;


        static const Implements_Data_Type_New<returnType>*
        getReturnType(Markov_CommandManagerVar* cm)
        {
          return cm->idToTyped<returnType>(Cls<returnType>::name());
        }


        static Implements_Closure_Type<argTypes>*
        getArgumentTypes(Markov_CommandManagerVar* cm)
        {
          return new Implements_Closure_Type<argTypes>(
                Implements_Fn_Argument<Markov_CommandManagerVar*>
                (new _private::Implements_Closure_Value_Markov_CommandManagerVar_Self()),
                Implements_Fn_Argument<std::string>(cm,
                                                    "file name",
                                                    "macror.txt",
                                                    "filename to load the data","")
                );

        }


        static ClosureType*
        closureType(Markov_CommandManagerVar* cm)
        {
          return new ClosureType(getReturnType(cm),load,getArgumentTypes(cm));
        }

        typedef mp_list<> dependsOn;
      };





      static vType*
      functionType(Markov_CommandManagerVar* cm)
      {
        auto out= new  Implements_Closure_Type<void*>
            (myId(),Identifier::types::idCmdGiven::varType(myId()));
        out->push_overload(cm,load_cm::closureType(cm));
        return out;



      }





    };


    struct Run {
      typedef Implements_Closure_Type<void*>  vType;

      static std::string myId(){return "run";}
      static std::string myTip(){return "run script file";}
      static std::string myWhatThis(){return "";}

      struct run_cm
      {
        static void run(Markov_CommandManagerVar* cm,
                        const std::string& pathfileNameIn,
                        const std::string& pathfileLog
                        , bool withError);

        typedef run_cm selfType;

        typedef void returnType;
        typedef std::tuple<Markov_CommandManagerVar*,std::string,std::string,bool> argTypes;

        typedef decltype(&run)  funType;

        typedef
        mp_append
        <
        Implements_Closure_Type<returnType,void,funType>,argTypes
        >
        ClosureType;


        static const Implements_Data_Type_New<returnType>*
        getReturnType(Markov_CommandManagerVar* cm)
        {
          return cm->idToTyped<returnType>(Cls<returnType>::name());
        }


        static Implements_Closure_Type<argTypes>*
        getArgumentTypes(Markov_CommandManagerVar* cm)
        {
          return new Implements_Closure_Type<argTypes>(
                Implements_Fn_Argument<Markov_CommandManagerVar*>
                (new _private::Implements_Closure_Value_Markov_CommandManagerVar_Self()),
                Implements_Fn_Argument<std::string>(cm,
                                                    "script file name",
                                                    "macror_script.txt",
                                                    "filename where the script is","")
                ,Implements_Fn_Argument<std::string>(cm,
                                                     "log file name",
                                                     "macror_script_log.txt",
                                                     "filename to log the read script","")
                ,Implements_Fn_Argument<bool>(cm,
                                              "check error?",
                                              true,
                                              "if true it checks consistency","")

                );

        }


        static ClosureType*
        closureType(Markov_CommandManagerVar* cm)
        {
          return new ClosureType(getReturnType(cm),run,getArgumentTypes(cm));
        }

        typedef mp_list<> dependsOn;
      };





      static vType*
      functionType(Markov_CommandManagerVar* cm)
      {
        auto out= new  Implements_Closure_Type<void*>
            (myId(),Identifier::types::idCmdGiven::varType(myId()));
        out->push_overload(cm,run_cm::closureType(cm));
        return out;



      }





    };


    struct Who {
      typedef Implements_Closure_Type<void*>  vType;

      static std::string myId(){return "who";}
      static std::string myTip(){return "list variables";}
      static std::string myWhatThis(){return "";}

      struct who_cm
      {
        static void who(Markov_CommandManagerVar* cm,
                        const std::string& pathfileName);

        typedef who_cm selfType;

        typedef void returnType;
        typedef std::tuple<Markov_CommandManagerVar*,std::string> argTypes;

        typedef decltype(&who)  functionType;

        typedef
        mp_append
        <
        Implements_Closure_Type<returnType,void,functionType>,argTypes
        >
        ClosureType;


        static const Implements_Data_Type_New<returnType>*
        getReturnType(Markov_CommandManagerVar* cm)
        {
          return cm->idToTyped<returnType>(Cls<returnType>::name());
        }


        static Implements_Closure_Type<argTypes>*
        getArgumentTypes(Markov_CommandManagerVar* cm)
        {
          return new Implements_Closure_Type<argTypes>(
                Implements_Fn_Argument<Markov_CommandManagerVar*>
                (new _private::Implements_Closure_Value_Markov_CommandManagerVar_Self()),
                Implements_Fn_Argument<std::string>(cm,
                                                    "variable name",
                                                    "",
                                                    "variable name or type","")
                );

        }


        static ClosureType*
        closureType(Markov_CommandManagerVar* cm)
        {
          return new ClosureType(getReturnType(cm),who,getArgumentTypes(cm));
        }

        typedef mp_list<> dependsOn;
      };





      static vType*
      functionType(Markov_CommandManagerVar* cm)
      {
        auto out= new  Implements_Closure_Type<void*>
            (myId(),Identifier::types::idCmdGiven::varType(myId()));
        out->push_overload(cm,who_cm::closureType(cm));
        return out;



      }





    };

    struct Exit {
      typedef Implements_Closure_Type<void*>  vType;

      static std::string myId(){return "exit";}
      static std::string myTip(){return "exit program";}
      static std::string myWhatThis(){return "";}

      struct exit_cm
      {
        static void exitProgram(Markov_CommandManagerVar* cm,
                                const std::string& pathfileName);

        typedef exit_cm selfType;

        typedef void returnType;
        typedef std::tuple<Markov_CommandManagerVar*,std::string> argTypes;

        typedef decltype(&exitProgram)  functionType;

        typedef
        mp_append
        <
        Implements_Closure_Type<returnType,void,functionType>,argTypes
        >
        ClosureType;


        static const Implements_Data_Type_New<returnType>*
        getReturnType(Markov_CommandManagerVar* cm)
        {
          return cm->idToTyped<returnType>(Cls<returnType>::name());
        }


        static Implements_Closure_Type<argTypes>*
        getArgumentTypes(Markov_CommandManagerVar* cm)
        {
          return new Implements_Closure_Type<argTypes>(
                Implements_Fn_Argument<Markov_CommandManagerVar*>
                (new _private::Implements_Closure_Value_Markov_CommandManagerVar_Self()),
                Implements_Fn_Argument<std::string>(cm,
                                                    "variable name",
                                                    "",
                                                    "variable name or type","")
                );

        }


        static ClosureType*
        closureType(Markov_CommandManagerVar* cm)
        {
          return new ClosureType(getReturnType(cm),exitProgram,getArgumentTypes(cm));
        }

        typedef mp_list<> dependsOn;
      };





      static vType*
      functionType(Markov_CommandManagerVar* cm)
      {
        auto out= new  Implements_Closure_Type<void*>
            (myId(),Identifier::types::idCmdGiven::varType(myId()));
        out->push_overload(cm,exit_cm::closureType(cm));
        return out;



      }





    };







    struct Simulate {
      typedef Implements_Closure_Type<void*>  vType;

      static std::string myId(){return "simulate";}
      static std::string myTip(){return "use model to simulate experiment";}
      static std::string myWhatThis(){return "";}

      struct simulate_cm
      {
        static Experiment*
        simulate(Markov_CommandManagerVar* cm,
                 Markov_Mol_New::ABC_PatchModel* p,
                 ABC_Experiment* experiment_in,
                 double time_step
                 , std::size_t num_steps,
                 std::size_t n_replicates);


        typedef simulate_cm selfType;

        typedef std::tuple<Markov_CommandManagerVar*,
        Markov_Mol_New::ABC_PatchModel*,
        ABC_Experiment*,
        double
        , std::size_t ,
        std::size_t > argTypes;

        typedef Experiment* returnType;

        typedef decltype(&simulate)  funType;

        typedef
        mp_append
        <
        Implements_Closure_Type<returnType,void,funType>,argTypes
        >
        ClosureType;


        static const Implements_Data_Type_New<returnType>*
        getReturnType(Markov_CommandManagerVar* cm)
        {
          return cm->idToTyped<returnType>(Cls<returnType>::name());
        }


        static Implements_Closure_Type<argTypes>*
        getArgumentTypes(Markov_CommandManagerVar* cm)
        {
          return new Implements_Closure_Type<argTypes>(
                Implements_Fn_Argument<Markov_CommandManagerVar*>
                (new _private::Implements_Closure_Value_Markov_CommandManagerVar_Self()),

                Implements_Fn_Argument<Markov_Mol_New::ABC_PatchModel*>
                (cm,"patchModel","simulated model",""),
                Implements_Fn_Argument<ABC_Experiment*>
                (cm,"experiment","simulated experiment", ""),
                Implements_Fn_Argument<double>(Real::types::positive()
                                               ,cm,"time_step","step time of simulation","")
                , Implements_Fn_Argument<std::size_t>
                (cm,"num_steps","number of substeps",""),
                Implements_Fn_Argument<std::size_t>
                (cm,"number_of_replicates",1,"number of times the simulation is run","")
                );

        }


        static ClosureType*
        closureType(Markov_CommandManagerVar* cm)
        {
          return new ClosureType(getReturnType(cm),simulate,getArgumentTypes(cm));
        }

        typedef mp_list<Experiment*> dependsOn;
      };





      static vType*
      functionType(Markov_CommandManagerVar* cm)
      {
        auto out= new  Implements_Closure_Type<void*>
            (myId(),Identifier::types::idFunGiven::varType(myId()));
        out->push_overload(cm,simulate_cm::closureType(cm));
        return out;



      }





    };





    struct Likelihood {
      typedef Implements_Closure_Type<void*>  vType;

      static std::string myId(){return "likelihood";}
      static std::string myTip(){return "calculates likelihood of a model to generate an experiment outcome";}
      static std::string myWhatThis(){return "";}

      struct likelihood_
      {

        static
        Markov_Bay_New::LikelihoodEvaluation*
        likelihood(const Markov_Mol_New::ABC_PatchModel *patch,
                   const ABC_Experiment *experiment,
                   const std::__cxx11::string &algorithm,
                   bool isaveraging,
                   bool zeroGuard);



        typedef likelihood_ selfType;

        typedef std::tuple<
        Markov_Mol_New::ABC_PatchModel*,
        ABC_Experiment*,
        std::string, bool, bool> argTypes;

        typedef   Markov_Bay_New::LikelihoodEvaluation*
        returnType;

        typedef decltype(&likelihood)  funType;

        typedef
        mp_append
        <
        Implements_Closure_Type<returnType,void,funType>,argTypes
        >
        ClosureType;


        static const Implements_Data_Type_New<returnType>*
        getReturnType(Markov_CommandManagerVar* cm)
        {
          return cm->idToTyped<returnType>(Cls<returnType>::name());
        }


        static Implements_Closure_Type<argTypes>*
        getArgumentTypes(Markov_CommandManagerVar* cm)
        {
          return new Implements_Closure_Type<argTypes>(
                Implements_Fn_Argument<Markov_Mol_New::ABC_PatchModel*>
                (cm,"patchModel","simulated model",""),
                Implements_Fn_Argument<ABC_Experiment*>
                (cm,"experiment","simulated experiment", ""),
                 Implements_Fn_Argument<std::string>
                (cm,"likelihood_algorithm","MacroDR","applied algorithm",""),
                Implements_Fn_Argument<bool>
                (cm,"isAveraging",true,"number of times the simulation is run",""),
                Implements_Fn_Argument<bool>
                (cm,"zero_guard",true,"number of times the simulation is run","")
                );

        }


        static ClosureType*
        closureType(Markov_CommandManagerVar* cm)
        {
          return new ClosureType(getReturnType(cm),likelihood,getArgumentTypes(cm));
        }

        typedef mp_list<Markov_Bay_New::LikelihoodEvaluation*> dependsOn;
      };





      static vType*
      functionType(Markov_CommandManagerVar* cm)
      {
        auto out= new  Implements_Closure_Type<void*>
            (myId(),Identifier::types::idFunGiven::varType(myId()));
        out->push_overload(cm,likelihood_::closureType(cm));
        return out;



      }





    };

    /*
    struct Likelihood {
      typedef Implements_Data_Type_Function  vType;

      static std::string myId(){return "likelihood";}
      static std::string myTip(){return "calculate likelihood of experiment";}
      static std::string myWhatThis(){return "";}

      struct likelihood_cm
      {
        static void
        likelihood(Markov_CommandManagerVar* cm,
                   Markov_Mol_New::ABC_PatchModel *patch,
                                         Markov_IO_New::ABC_Experiment* experiment,
                                         const std::string algorithm,
                                         bool isaveraging,
                                         bool zeroGuard,
                                         double dxForScore,
                                         bool showPartialLikelihood=false,
                                         bool showPredictedValue=false,
                                         bool runApproximation=false,
                                         std::size_t numSteps=100,
                                         std::size_t numSamples=1000);


        typedef likelihood_cm selfType;

        typedef void returnType;

        typedef std::tuple<
        Markov_CommandManagerVar*,
        Markov_Mol_New::ABC_PatchModel*,
        ABC_Experiment* ,
        std::string ,
        double
        , std::size_t ,
        std::size_t ,
        std::size_t
        > argTypes;

        typedef decltype(&likelihood)  functionType;

        typedef mp_append
        <Implements_Closure_Type_R_Fn_Args_Function<functionType,void>,argTypes
        >                        vType;

        typedef
        mp_insert
        <
        Implements_Fn_Argument<void>,argTypes
        >
        argFnTuple;


        typedef Implements_Fn_Argument<void>  returnFnType;





        static returnFnType
        getReturnFnType(Markov_CommandManagerVar* cm)
        {
          return {};
        }



        static argFnTuple
        getArgumentTypes(Markov_CommandManagerVar* cm)
        {
          return argFnTuple(
                Implements_Fn_Argument<Markov_CommandManagerVar*>
                (new Implements_Closure_Value_Markov_CommandManagerVar_Self),
                Implements_Fn_Argument<Markov_Mol_New::ABC_PatchModel*>
                (cm,"patchModel",_private::_model::patch::ABC_PatchModel_type(),"simulated model",""),
                Implements_Fn_Argument<ABC_Experiment*>
                (cm,"experiment",_private::_experiment::ABC_Experiment_type()
                 ,"simulated experiment", ""),
                Implements_Fn_Argument<std::string>
                (cm,"simulation_id",Identifier::types::idVarNew(),"mySimulation",false,"id for simulated experiment", "identifier to recover the simulated experiment"),
                Implements_Fn_Argument<double>
                (cm,"time_step",Real::types::positive(),"step time of simulation","")
                , Implements_Fn_Argument<std::size_t>
                (cm,"num_steps","number of substeps",""),
                Implements_Fn_Argument<std::size_t>
                (cm,"number_of_replicates",1,false,"number of times the simulation is run",""),
                Implements_Fn_Argument<std::size_t>
                (cm,"seed",0,false,"seed for the random generator","")
                );

        }


        static ABC_Type_of_Closure*
        varType(Markov_CommandManagerVar* cm)
        {
          return varTypeT<selfType>(likelihood,cm);
        }




        typedef mp_list<> dependsOn;
      };




      static  std::set<ABC_Type_of_Closure*> getOverrides(Markov_CommandManagerVar* cm)
      {
        std::set<ABC_Type_of_Closure*> out;

        out.push_back(likelihood_cm::varType(cm));
        return out;

      }

      static vType*
      functionType(Markov_CommandManagerVar* cm)
      {
        return new  Implements_Data_Type_Function
            (myId(),nullptr,Identifier::types::idFunct::varType(myId()),getOverrides(cm));
      }





    };

*/



  };

}


#endif // FUNCTIONCOMMAND_H
