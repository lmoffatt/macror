#ifndef COMMANDS_H
#define COMMANDS_H
#include "Markov_IO/Implements_ComplexVar_New.h"


namespace Markov_IO_New
{


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
                                  ,nullptr,nullptr,nullptr,&exitProgram )
                                  {}
    virtual ~ExitCommand(){}


  };

  class EditCommand: public Implements_Command_Type_New
  {

  };

  class   WhoCommand: public Implements_Command_Type_New
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


  void pushAllCommands (Implements_ComplexVar_New* cm);


}



#endif // COMMANDS_H
