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

        typedef decltype(&save)  functionType;

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
            (myId(),Identifier::types::idFunct::varType(myId()));
        out->push_overload(cm,save_cm::closureType(cm));
        return out;



      }





    };


/*
    struct Load {
      typedef Implements_Closure_Type<void*>  vType;

      static std::string myId(){return "load";}
      static std::string myTip(){return "load variables";}
      static std::string myWhatThis(){return "";}

      struct load_cm
      {
        static void load(Markov_CommandManagerVar* cm,
                         const std::string& pathfileName);

        typedef void returnType;
        typedef std::tuple<Markov_CommandManagerVar*,std::string> argTypes;

        typedef decltype(&load)  functionType;

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
                Implements_Fn_Argument<std::string>("macror.txt")
                );

        }


        static ABC_Type_of_Function*
        varType(Markov_CommandManagerVar* cm);




        typedef mp_list<> dependsOn;
      };




      static  std::set<ABC_Type_of_Function*> getOverrides(Markov_CommandManagerVar* cm)
      {
        std::set<ABC_Type_of_Function*> out;

        out.insert(load_cm::varType(cm));
        return out;

      }

      static vType*
      functionType(Markov_CommandManagerVar* cm)
      {
        return new  Implements_Closure_Type<void*>
            (myId(),nullptr,Identifier::types::idFunct::varType(myId()),getOverrides(cm));
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
                        const std::string& typeName);

        typedef void returnType;
        typedef std::tuple<Markov_CommandManagerVar*,std::string> argTypes;

        typedef decltype(&who)  functionType;

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
                Implements_Fn_Argument<std::string>("")
                );

        }


        static ABC_Type_of_Function*
        varType(Markov_CommandManagerVar* cm);




        typedef mp_list<> dependsOn;
      };




      static  std::set<ABC_Type_of_Function*> getOverrides(Markov_CommandManagerVar* cm)
      {
        std::set<ABC_Type_of_Function*> out;

        out.insert(who_cm::varType(cm));
        return out;

      }

      static vType*
      functionType(Markov_CommandManagerVar* cm)
      {
        return new  Implements_Closure_Type<void*>
            (myId(),nullptr,Identifier::types::idFunct::varType(myId()),getOverrides(cm));
      }

    };




    struct Exit {
      typedef Implements_Closure_Type<void*>  vType;

      static std::string myId(){return "exit";}
      static std::string myTip(){return "Exit Program";}
      static std::string myWhatThis(){return "";}

      struct exit_cm
      {
        static void exitProgram(Markov_CommandManagerVar* cm,
                                const std::string& pathfileName);

        typedef exit_cm selfType;

        typedef void returnType;
        typedef std::tuple<Markov_CommandManagerVar*, std::string> argTypes;

        typedef decltype(&exitProgram)  functionType;

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
                Implements_Fn_Argument<std::string>("")
                );

        }


        static ABC_Type_of_Function*
        varType(Markov_CommandManagerVar* cm)
        {
          return varTypeT<selfType>(exitProgram,cm);
        }




        typedef mp_list<> dependsOn;
      };




      static  std::set<ABC_Type_of_Function*> getOverrides(Markov_CommandManagerVar* cm)
      {
        std::set<ABC_Type_of_Function*> out;

        out.insert(exit_cm::varType(cm));
        return out;

      }

      static vType*
      functionType(Markov_CommandManagerVar* cm)
      {
        return new  Implements_Closure_Type<void*>
            (myId(),nullptr,Identifier::types::idFunct::varType(myId()),getOverrides(cm));
      }





    };




    struct Simulate {
      typedef Implements_Closure_Type<void*>  vType;

      static std::string myId(){return "simulate";}
      static std::string myTip(){return "simulate experiment";}
      static std::string myWhatThis(){return "";}

      struct simulate_cm
      {
        static void
        simulate(Markov_CommandManagerVar* cm,
                 Markov_Mol_New::ABC_PatchModel* p,
                 ABC_Experiment* experiment_in,
                 std::string experiment_out,
                 double time_step
                 , std::size_t num_steps,
                 std::size_t n_replicates,
                 std::size_t seed);

        typedef simulate_cm selfType;

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

        typedef decltype(&simulate)  functionType;

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


        static ABC_Type_of_Function*
        varType(Markov_CommandManagerVar* cm)
        {
          return varTypeT<selfType>(simulate,cm);
        }




        typedef mp_list<> dependsOn;
      };




      static  std::set<ABC_Type_of_Function*> getOverrides(Markov_CommandManagerVar* cm)
      {
        std::set<ABC_Type_of_Function*> out;

        out.insert(simulate_cm::varType(cm));
        return out;

      }

      static vType*
      functionType(Markov_CommandManagerVar* cm)
      {
        return new  Implements_Closure_Type<void*>
            (myId(),nullptr,Identifier::types::idFunct::varType(myId()),getOverrides(cm));
      }





    };


    */
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


    class CdCommand: public Implements_Command_Type_New
    {

    };

    class HelpCommand: public Implements_Command_Type_New
    {

    };

    class SimulateCommand: public Implements_Command_Type_New
    {

    };

    class   OptimizeCommand: public Implements_Command_Type_New
    {

    };

    class    DirCommand : public Implements_Command_Type_New
    {

    };


    class LikelihoodCommand: public Implements_Command_Type_New
    {
    };
    class  ExportCommand: public Implements_Command_Type_New
    {

    };

    class MkdirCommand:public Implements_Command_Type_New
    {

    };

    class EditCommand: public Implements_Command_Type_New
    {

    };


    class ClearCommand: public Implements_Command_Type_New
    {

    };

    class  CreateCommand: public Implements_Command_Type_New
    {

    };

    class ShowCommand: public Implements_Command_Type_New
    {

    };

    class ModelCommand: public Implements_Command_Type_New
    {

    };

    class AverageCommand: public Implements_Command_Type_New
    {

    };


  };

}


#endif // FUNCTIONCOMMAND_H
