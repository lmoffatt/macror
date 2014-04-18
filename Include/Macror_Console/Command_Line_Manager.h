#ifndef COMMAND_LINE_MANAGER_H
#define COMMAND_LINE_MANAGER_H

#include <vector>
#include "Macror_Console/KeyEvent.h"


namespace Macror_Console {

class Macror_Command_Manager;

class Command_Line_Manager
{
public:
  bool eventKey(KeyEvent *e);
  virtual void suggestAlternatives(const std::vector<std::string> &res);

  Command_Line_Manager(Macror_Command_Manager* cm):
    cm_(cm),
    commandWord_{},
    commandLine_{},
    tail_{},
    currChar_{},
    currKey_{KeyEvent::Key_Other},
    previousKey_{KeyEvent::Key_Other}{}


private:
  Macror_Command_Manager* cm_;

  std::string commandWord_;
  std::string  commandLine_;
  std::string tail_;

  std::string currChar_;

  KeyEvent::Key currKey_;
  KeyEvent::Key previousKey_;

};
}
#endif // COMMAND_LINE_MANAGER_H
