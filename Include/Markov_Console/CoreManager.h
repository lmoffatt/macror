#ifndef COREMANAGER
#define COREMANAGER


#include "Markov_IO/ABC_Var.h"

#include "Markov_Console/ABC_Command.h"


namespace Markov_Console {
  /**
   * @brief The CoreManager distribute the work among several managers
   */


  class HistoryManager; // (stores the history of expressions)


  class Command_Manager:public Markov_IO::Implements_Complex_Value
  {
  public:

    ABC_CommandVar* getCommand(const std::string commandName);

    std::set<std::string> getCategoryList(const std::string& category)const;



    Markov_IO::myType* getType(const std::string typeName);
  };



  class variable_Manager: public Markov_IO::Implements_Complex_Value
  {
  };

  class Script_Manager;

  class StateOfProgramManager;

  class EnvironmentManager
  {

  };


  class CoreManager{





  };




}


#endif // COREMANAGER

