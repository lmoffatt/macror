#include "Macror_Console/Macror_Application.h"
#include "Macror_Console/Macror_CommandManager.h"
#include "Macror_Console/KeyEvent.h"

std::vector<std::string> arguments(int argc,char ** argv)
{
  std::vector<std::string> out(argc);

  for (int i=0; i<argc; i++)
    out[i]=argv[i];
}


namespace Macror_Console {

  Macror_Console_Application::Macror_Console_Application(int argc, char **argv):
    arguments_(arguments(argc,argv)),
    active_objects_{},
    events_{},
    aboutToQuit_(false){

    active_objects_.push_back(new Macror_Command_Manager());
    events_.push_back(new KeyEvent());

  }

  void Macror_Console_Application::exec()
  {

    while (!aboutToQuit_)
      {
        dispatchEvent();
      }
    quit();
  }

  std::vector<std::string> Macror_Console_Application::getArguments()
  {
    return arguments_;
  }

  void Macror_Console_Application::dispatchEvent()
  {
    for (Base_Event* e: events_)
      {
        if (e->check())
          {
          for (Abstract_Handle_Events* o:active_objects_)
            {
            if (o->event(e))
              break;
            }
          }
      }
  }



}
