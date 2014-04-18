#ifndef MACROR_CONSOLE_H
#define MACROR_CONSOLE_H
#include "Macror_Console/Base_Event.h"



namespace Macror_Console {

  class Macror_Console: public Abstract_Handle_Events
  {
  public:
    virtual bool event(Base_Event *e);



  };

}




#endif // MACROR_CONSOLE_H
