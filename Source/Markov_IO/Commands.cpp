#include"Markov_IO/Commands.h"
#include "Markov_IO/Implements_ComplexVar_New.h"

namespace Markov_IO_New {

  void pushAllCommands(Implements_ComplexVar_New *cm)
  {
    cm->pushCommand(new ExitCommand(cm));
  }




}
