#include"Markov_IO/Commands.h"
#include "Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_Console/Markov_CommandManager.h"

namespace Markov_IO_New {

  namespace cmd {


    void pushAllCommands(Implements_ComplexVar_New *cm)
    {
      cm->pushCommand(new ExitCommand(cm));
      cm->pushCommand(new WhoCommand(cm));

    }

    void WhoCommand::who(Markov_CommandManagerVar *cm, std::__cxx11::string typeName)
    {
      std::set<std::string> out=cm->getIdsOfVarType(typeName,false);
      for (auto& e:out)
        {
          cm->getIO()->put(e);
          cm->getIO()->put("\t");
          cm->getIO()->putNewLine();
        }
    }
    bool WhoCommand::who(Markov_CommandManagerVar *cm, const std::map<std::__cxx11::string, ABC_Var_New *> &m, const Implements_Command_Type_New *
                         , std::__cxx11::string * whynot, const std::__cxx11::string & objective)
    {

      if (m.empty())
        {
           who(cm,"");
          return true;
        }
      else
        {
          std::string field;
          if (get_var<arg::typeName_Field>(m,field,whynot,objective))
            {
              who(cm,field); return true;
            }
          else
            return false;
        }
    }





  };
};
