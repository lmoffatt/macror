#ifndef COMMANDS_H
#define COMMANDS_H
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


  namespace cmd {

    typedef StructureEnv_New* myC;




    static bool hasAll (const StructureEnv_New* cm,const StructureEnv_New* val,
                        const _private::Implements_Data_Type_New_StructureEnv* self
                        , std::string* error,const std::string& obj)
    {
      auto& fields=self->getFields();

      for (std::size_t i=0; i<fields.size(); ++i)
        {
          const Implements_Var& v=fields[i].first;
          if (!val->hasNameofType(v.id,v.data->myType(),false,error,obj))
            return false;
        }
      return true;

    }

    static bool hasMandatory (const StructureEnv_New* cm,const StructureEnv_New* val,
                              const _private::Implements_Data_Type_New_StructureEnv* self
                              , std::string* error,const std::string& obj)
    {
      auto& fields=self->getFields();

      for (std::size_t i=0; i<fields.size(); ++i)
        {
          const Implements_Var& v=fields[i].first;
          if (!val->hasNameofType(v.id,v.data->myType(),false,error,obj))
            return !fields[i].second;
        }
      return true;

    }
    static bool comply (const StructureEnv_New* cm,const StructureEnv_New* val,
                        const _private::Implements_Data_Type_New_StructureEnv* self
                        , std::string* error,const std::string& obj)
    {
      return hasMandatory(cm,val,self,error,obj);
    }

    static Implements_Data_Type_New<Implements_Var>*
    nextElement
    (const StructureEnv_New* cm
     ,const StructureEnv_New* val,
     std::size_t iField
     , const _private::Implements_Data_Type_New_StructureEnv*  self
     , std::string * whyNot, const std::string& masterObjective,
     Implements_Data_Type_New<Implements_Var>* source)
    {
      auto& fields=self->getFields();
      if (iField<fields.size())
        {
          const Implements_Var& v=fields[iField].first;
          if (source!=nullptr)
            {
              source->setVariable(v);
              return source;
            }
          else
            return Variable::types::varGiven::varType(v);
        }
      else
        {
          *whyNot=masterObjective+": iField="+std::to_string(iField)
              +" bigger than fields size()="
              +std::to_string(fields.size());
          return nullptr;
        }
    }

    struct  Save
    {
      static void save(Markov_CommandManagerVar* cm,
                       const std::string& pathfileName, const std::__cxx11::string varType="");


      static std::string myId(){return "save";}
      static std::string myIdType(){return Cls<myC>::name();}
      static std::string myTip(){return "save all the variables";}
      static std::string myWhatThis(){return "";}

      static   bool  run
              (Markov_CommandManagerVar* cm
              , const StructureEnv_New* arguments
              ,const Implements_Command_Type_New* self
              ,std::string* WhyFail, const std::string& masterObjective);

      static std::vector<std::pair<Implements_Var,bool>> getArgList()
      {
             return {};
      }

      static Implements_Command_Type_New* cmdType()
      {
        auto fields=getArgList();
        Implements_Var firstVar{};
        if (fields.size()>0)
            firstVar=fields[0].first;

        return new Implements_Command_Type_New(
              fields,
              &run,
              Variable::types::varGiven::varType(firstVar),
              &comply,
              &hasMandatory,
              &hasAll,
              &nextElement);
      }


    };



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


      static std::vector<std::pair<Implements_Var,bool>> getArgList()
      {
           return {{getMyVar<arg::typeName_Field>(),false}};

      }

      static Implements_Command_Type_New* cmdType()
      {
        auto fields=getArgList();
        Implements_Var firstVar;
        if (fields.size()>0)
            firstVar=fields[0].first;

        return new Implements_Command_Type_New(
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


      static std::vector<std::pair<Implements_Var,bool>> getArgList()
      {
           return {};

      }

      static Implements_Command_Type_New* cmdType()
      {
        auto fields=getArgList();
        Implements_Var firstVar{};
        if (fields.size()>0)
            firstVar=fields[0].first;

        return new Implements_Command_Type_New(
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
      }


      static std::vector<std::pair<Implements_Var,bool>> getArgList()
      {
           return {{getMyVar<arg::typeName_Field>(),false}};

      }

      static Implements_Command_Type_New* cmdType()
      {
        auto fields=getArgList();
        Implements_Var firstVar;
        if (fields.size()>0)
            firstVar=fields[0].first;

        return new Implements_Command_Type_New(
              fields,
              &run,
              Variable::types::varGiven::varType(firstVar),
              &comply,
              &hasMandatory,
              &hasAll,
              &nextElement);
      }

    };



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



#endif // COMMANDS_H
