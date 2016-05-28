#include"Markov_IO/Commands.h"
#include "Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_Console/Markov_CommandManager.h"

#include "Markov_IO/FileLoadSave.h"

namespace Markov_IO_New {

  namespace cmd {


    void pushAllCommands(StructureEnv_New *cm)
    {
//      cm->pushCommand(new ExitCommand(cm));
//      cm->pushCommand(new WhoCommand(cm));
//      cm->pushCommand(new SaveCommand(cm));
    }

//    void WhoCommand::who(Markov_CommandManagerVar *cm, std::__cxx11::string typeName)
//    {
//      std::set<std::string> out=cm->getIdsOfVarType(typeName,false);
//      for (auto& e:out)
//        {
//          cm->getIO()->put(e);
//          cm->getIO()->put("\t");
//          cm->getIO()->putNewLine();
//        }
//    }
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


//    void LoadCommand::load(Markov_CommandManagerVar *cm
//                           , const std::__cxx11::string &path){
//      std::ifstream f(path.c_str());
//      std::size_t numVar=0;
//      std::set<std::string> varnames;
//      //safeGetline allow loading windows files in linux
//      //TODO: check if it loads linux files in windows



//      //      while (true)
//      //        {
//      //          auto v=getValueFromStream(tok);
//      //          if (v!=nullptr)
//      //            {
//      //              numVar++;
//      //              auto w=getCommandManager()->getMeasureFromValue(v);
//      //              if (w!=nullptr)
//      //                getCommandManager()->pushChild(w);
//      //              else
//      //                getCommandManager()->pushChild(v);

//      //            }
//      //          else if (!f.eof())
//      //            {

//      //              std::string m="unrecognized variable; read text ";
//      //              m+=tok.putTokenBuffer();
//      //              getCommandManager()->putErrorOut(m);
//      //              f.close();
//      //              return false;
//      //            }
//      //          if (f.eof())
//      //            break;
//      //          tok.cleanRead();
//      //        }
//      //      getCommandManager()->putOut(Markov_IO::ToString(numVar)+" variables loaded from file "+ path+"\n");
//    }

//    void SaveCommand::save(Markov_CommandManagerVar *cm, const std::__cxx11::string &pathfileName)
//    {
//      fd::FileOut f(pathfileName);
//      std::string whyNot;
//      cm->getCmdType()->put(cm,cm->getVars(),&f,&whyNot,"");

//    }

//    bool SaveCommand::save
//    (Markov_CommandManagerVar *cm
//     , const std::map<std::__cxx11::string, ABC_Data_New *> & args
//     , const Implements_Command_Type_New * self
//     , std::__cxx11::string *whyNot
//     , const std::__cxx11::string &objective)
//    {
//      std::string dir=cm->getDir();
//      std::string path=dir+fd::File::slash()+"macror.txt";
//      save(cm,path);
//      std::cerr<<path;
//      return true;
//    }






  };
};
