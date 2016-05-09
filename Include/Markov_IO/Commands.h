#ifndef COMMANDS_H
#define COMMANDS_H
#include "Markov_IO/Implements_ComplexVar_New.h"


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

    struct fileName_Field
    {
      typedef std::string myC;
      typedef Identifier::types::idType myType;
      typedef Implements_Identifier vType;

      static std::string myId(){return "typeName";}
      static std::string myIdType(){return myType::myId();}
      static std::string myTip(){return "a type of variable";}
      static std::string myWhatThis() {return "different types of variables";}
    };

  }


  namespace cmd {

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

    class  SaveCommand : public Implements_Command_Type_New
    {

    };

    class LikelihoodCommand: public Implements_Command_Type_New
    {

    };
    class LoadCommand: public Implements_Command_Type_New
    {

    };
    class  ExportCommand: public Implements_Command_Type_New
    {

    };

    class MkdirCommand:public Implements_Command_Type_New
    {

    };
    class ExitCommand: public Implements_Command_Type_New
    {
    public:

      static bool exitProgram(Markov_CommandManagerVar* cm
                              , const std::map<std::string,ABC_Var_New*>&
                              ,const Implements_Command_Type_New*
                              ,std::string*, const std::string&)
      {
        exit(0);
        return true;
      }


      static std::string ClassName() {return "exit";}

      ExitCommand(const Implements_ComplexVar_New* cm):
        Implements_Command_Type_New(cm,ClassName(),
                                    Implements_Command_Type_New::ClassName(),
                                    "closes everything and exits the program"
                                    ," closes the program"
                                    ,{}
                                    ,&exitProgram )
      {}
      virtual ~ExitCommand(){}


    };

    class EditCommand: public Implements_Command_Type_New
    {

    };

    class   WhoCommand: public Implements_Command_Type_New

    {
    public:

      static void who(Markov_CommandManagerVar* cm,
                      std::string typeName);


      static bool who(Markov_CommandManagerVar* cm
                      , const std::map<std::string,ABC_Var_New*>&
                      , const Implements_Command_Type_New *, std::__cxx11::string *
                      , const std::string&);


      static std::string ClassName() {return "who";}

      WhoCommand(const Implements_ComplexVar_New* cm):
        Implements_Command_Type_New(cm,ClassName(),
                                    Implements_Command_Type_New::ClassName(),
                                    "list the availabe variables"
                                    ," "
                                    ,{{getMyVar<arg::typeName_Field>(),false}}
                                    ,&who )
      {}
      virtual ~WhoCommand(){}


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


    void pushAllCommands (Implements_ComplexVar_New* cm);
  };

}



#endif // COMMANDS_H
