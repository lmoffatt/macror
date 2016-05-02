#include"Markov_IO/Commands.h"
#include "Markov_IO/Implements_ComplexVar_New.h"

namespace Markov_IO_New {

  namespace cmd {


  void pushAllCommands(Implements_ComplexVar_New *cm)
  {
    cm->pushCommand(new ExitCommand(cm));
  }

  bool WhoCommand::who(Markov_CommandManagerVar *cm, const std::map<std::__cxx11::string, ABC_Var_New *> &, const Implements_Command_Type_New *, std::__cxx11::string *, const std::__cxx11::string &)
  {

    return true;
  }



};
};
