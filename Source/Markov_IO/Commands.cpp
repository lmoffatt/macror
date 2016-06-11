#include"Markov_IO/Commands.h"
#include "Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_Console/Markov_CommandManager.h"

#include "Markov_IO/FileLoadSave.h"

#include <memory>
namespace Markov_IO_New {

  namespace cmd {


    void pushAllCommands(StructureEnv_New *cm)
    {
        cm->pushCommand<Exit>();
        cm->pushCommand<Who>();
        cm->pushCommand<Save>();
        cm->pushCommand<Load>();

    }

  void Who::who(Markov_CommandManagerVar *cm, std::__cxx11::string typeName)
    {
      std::vector<std::string> out=cm->getIdsOfVarType(typeName,false);
      for (auto& e:out)
        {
          cm->getIO()->put(e);
          cm->getIO()->put("\t");
          cm->getIO()->putNewLine();
        }
    }
//    bool WhoCommand::who(Markov_CommandManagerVar *cm, const std::map<std::__cxx11::string, ABC_Data_New *> &m, const Implements_Command_Type_New *
//                         , std::__cxx11::string * whynot, const std::__cxx11::string & objective)
//    {

//      if (m.empty())
//        {
//          who(cm,"");
//          return true;
//        }
//      else
//        {
//          std::string field;
//          if (get_var<arg::typeName_Field>(m,field,whynot,objective))
//            {
//              who(cm,field); return true;
//            }
//          else
//            return false;
//        }
//    }


    void Load::load(Markov_CommandManagerVar *cm
                           , const std::__cxx11::string &path){
      fd::FileIn f(path);
      std::size_t numVar=0;
      std::string whyNot;
      auto eType=cm->idToTyped<StructureEnv_New*>(ComplexVar::types::Var::myId());
      auto loadedEnv=new StructureEnv_New (cm,"load");
      if (eType->getValue(cm,loadedEnv,&f,&whyNot,""))
        {
          auto out=cm->loadVars(std::move(*loadedEnv),&whyNot,"",true);

          for (auto& e:out)
            cm->getIO()->put(e+"\t");
        }
      delete loadedEnv;
      //      getCommandManager()->putOut(Markov_IO::ToString(numVar)+" variables loaded from file "+ path+"\n");
    }

    bool Load::run(Markov_CommandManagerVar *cm, const StructureEnv_New *arguments, const Implements_Command_Type_New *self, std::__cxx11::string *WhyFail, const std::__cxx11::string &masterObjective)
    {
      std::string dir=cm->getDir();
      std::string path=dir+fd::File::slash()+"macror.txt";
      load(cm,path);
      std::cerr<<path;
      return true;
    }

    void Save::save(Markov_CommandManagerVar *cm
                    , const std::__cxx11::string &pathfileName
                    ,const std::string varType)
    {
      fd::FileOut f(pathfileName);
      std::string whyNot;
      auto eType=cm->idToTyped<StructureEnv_New*>(ComplexVar::types::Var::myId());
      if (!eType->putValue(cm,cm,&f,&whyNot,""))
          cm->getIO()->put(whyNot);

    }

    bool Save::run
    (Markov_CommandManagerVar* cm
    , const StructureEnv_New* arguments
    ,const Implements_Command_Type_New* self
    ,std::string* WhyFail, const std::string& masterObjective)
    {
      std::string dir=cm->getDir();
      std::string path=dir+fd::File::slash()+"macror.txt";
      save(cm,path);
      std::cerr<<path;
      return true;
    }






  };
};
