#include <vector>
#include <cmath>
#include "Macror_Console/Macror_CommandManager.h"
#include "Macror_Console/KeyEvent.h"
#include "Macror_Console/Autocomplete.h"
#include "Macror_Console/CommandHistory.h"

namespace Macror_Console {


  bool Macror_Command_Manager::event(Base_Event *e)
  {
    if (e->myType()!=KeyEvent::Type())
      return currentLine_.eventKey(reinterpret_cast<KeyEvent*> (e));
    else
      return false;
  }



}
