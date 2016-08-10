#ifndef FUNCTIONCOMMAND_H
#define FUNCTIONCOMMAND_H

#include "Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_IO/Implements_path.h"

namespace Markov_IO_New
{
  namespace arg {
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


  namespace fcmd {



    namespace arg
    {
      struct void_arg
      {
        typedef void myC;
        typedef Implements_Fn_Argument<myC> argType;

        argType* arg(){return new argType();}

      };

      struct workingPath_arg
      {
        typedef std::string myC;
        typedef Implements_Fn_Argument<myC> argType;




      };


    }




    struct  Save
    {
      static void save(Markov_CommandManagerVar* cm,
                       const std::string& pathfileName, const std::__cxx11::string varType="");


      static std::string myId(){return "save";}
      static std::string myTip(){return "save all the variables";}
      static std::string myWhatThis(){return "";}



      static   bool  run
      (Markov_CommandManagerVar* cm
       , const StructureEnv_New* arguments
       ,const Implements_Command_Type_New* self
       ,std::string* WhyFail, const std::string& masterObjective);



    };



    struct Save_fcn {
      typedef Implements_Data_Type_Function  vType;

      struct save_cm
      {
        static void save(Markov_CommandManagerVar* cm,
                         const std::string& pathfileName, const std::__cxx11::string varType="");

        typedef void returnType;
        typedef std::tuple<Markov_CommandManagerVar*,std::string> argTypes;

        typedef decltype(&save)  functionType;

        typedef mp_append
        <Implements_Data_Type_FnClosure<functionType,void>,argTypes
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
                Implements_Fn_Argument<Markov_CommandManagerVar*>(cm),
                Implements_Fn_Argument<std::string>("macror.txt")
                );

        }

        static ABC_Type_of_Closure*
        varType(Markov_CommandManagerVar* cm)
        {

          return new Implements_Data_Type_FnClosure<
              functionType,returnType,Markov_CommandManagerVar*,std::string>
              (&save
               ,getReturnFnType(cm), getArgumentTypes(cm));
        }




        typedef mp_list<> dependsOn;
      };

      static std::string myId(){return "save";}
      static std::string myIdType(){}
      static std::string myTip(){return "Program of change in concentrations for a single trace";}
      static std::string myWhatThis(){return "";}


      static Implements_Identifier* myIdIdentifier(const Markov_CommandManagerVar* cm)
      {

      }

     static  std::vector<ABC_Type_of_Closure*> getOverrides(Markov_CommandManagerVar* cm)
      {
        std::vector<ABC_Type_of_Closure*> out;

        out.push_back(save_cm::varType(cm));
        return out;

      }

      static vType*
      varType(Markov_CommandManagerVar* cm)
      {
        return new  Implements_Data_Type_Function
            (myId(),nullptr,myIdIdentifier(cm),getOverrides(cm));
      }





    };

    /*
    struct Load
    {
      static void load(Markov_CommandManagerVar* cm,
                       const std::string& pathfileName);


      static std::string myId(){return "load";}
      static std::string myIdType(){return Cls<myC>::name();}
      static std::string myTip() {return "list the availabe variables";}

      static std::string myWhatThis(){return "";};

      static   bool  run
      (Markov_CommandManagerVar* cm
       , const StructureEnv_New* arguments
       ,const Implements_Command_Type_New* self
       ,std::string* WhyFail, const std::string& masterObjective);


      static std::vector<std::pair<Implements_Var,bool>>
      getArgList(const StructureEnv_New* cm)
      {
        return {{getMyVar<arg::typeName_Field>(cm),false}};

      }

      static Implements_Command_Type_New* cmdType(const StructureEnv_New* cm)
      {
        auto fields=getArgList(cm);
        Implements_Var firstVar;
        if (fields.size()>0)
          firstVar=fields[0].first;

        return new Implements_Command_Type_New(myId(),nullptr,
                                               fields,
                                               &run,
                                               Variable::types::varGiven::varType(firstVar),
                                               &comply,
                                               &hasMandatory,
                                               &hasAll,
                                               &nextElement);
      }




    };


    struct Exit

    {

      static bool exitProgram(Markov_CommandManagerVar* cm
                              , const StructureEnv_New*&
                              ,const Implements_Command_Type_New*
                              ,std::string*, const std::string&)
      {
        exit(0);
        return true;
      }

      static std::string myId(){return "exit";}
      static std::string myIdType(){return Cls<myC>::name();}
      static std::string myTip() {return "closes everything and exits the program";}

      static std::string myWhatThis(){return "";}

      static   bool  run
      (Markov_CommandManagerVar* cm
       , const StructureEnv_New* arguments
       ,const Implements_Command_Type_New* self
       ,std::string* WhyFail, const std::string& masterObjective)
      {
        exit(0);
        return true;

      }


      static std::vector<std::pair<Implements_Var,bool>> getArgList(const StructureEnv_New* cm)
      {
        return {};

      }

      static Implements_Command_Type_New* cmdType(const StructureEnv_New* cm)
      {
        auto fields=getArgList(cm);
        Implements_Var firstVar{};
        if (fields.size()>0)
          firstVar=fields[0].first;

        return new Implements_Command_Type_New(myId(),nullptr,
                                               fields,
                                               &run,
                                               Variable::types::varGiven::varType(firstVar),
                                               &comply,
                                               &hasMandatory,
                                               &hasAll,
                                               &nextElement);
      }






    };

    struct   Who

    {
    public:

      static void who(Markov_CommandManagerVar* cm,
                      std::string typeName);


      static std::string myId(){return "who";}
      static std::string myIdType(){return Cls<myC>::name();}
      static std::string myTip() {return "list the availabe variables";}

      static std::string myWhatThis(){return "";}

      static   bool  run
      (Markov_CommandManagerVar* cm
       , const StructureEnv_New* arguments
       ,const Implements_Command_Type_New* self
       ,std::string* WhyFail, const std::string& masterObjective)
      {
        std::string typeName= arguments->getDataValueS<arg::typeName_Field>();
        who(cm,typeName);
        return true;
      }


      static std::vector<std::pair<Implements_Var,bool>> getArgList(const StructureEnv_New* cm)
      {
        return {{getMyVar<arg::typeName_Field>(cm),false}};

      }

      static Implements_Command_Type_New* cmdType(const StructureEnv_New* cm)
      {
        auto fields=getArgList(cm);
        Implements_Var firstVar;
        if (fields.size()>0)
          firstVar=fields[0].first;

        return new Implements_Command_Type_New(myId(),nullptr,
                                               fields,
                                               &run,
                                               Variable::types::varGiven::varType(firstVar),
                                               &comply,
                                               &hasMandatory,
                                               &hasAll,
                                               &nextElement);
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


    void pushAllCommands (StructureEnv_New* cm);
  };

}


#endif // FUNCTIONCOMMAND_H
