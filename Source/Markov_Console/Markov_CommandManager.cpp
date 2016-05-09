#include <string>
#include <algorithm>

#include "Markov_Console/Markov_CommandManager.h"
#include "Markov_Console/ExpressionManager.h"
#include "Markov_Console/Help_File.h"
#include "Markov_Console/Markov_Script.h"

#include "Markov_Mol/ABC_MarkovModel.h"
#include "Markov_Mol/PatchModel.h"
#include "Markov_Mol/SimulationOptions.h"
#include "Markov_IO/FileDir.h"
#include "Markov_IO/Experiment.h"

#include "Markov_Bay/YfitLikelihoodEvaluation.h"
#include "Markov_Bay/MarkovLikelihood.h"

#include "Markov_Bay/SimpleOptimization.h"

#include "Markov_IO/auxiliarIO.h"


#include "Markov_IO/Experiment.h"
#include "Markov_IO/Trace.h"
#include "Markov_IO/SinglePulses.h"
#include "Markov_IO/SinglePulses2.h"
#include "Markov_IO/ExperimentAverage.h"
#include "Markov_IO/PulsesProgram.h"
#include "Markov_Mol/ExperimentSimulation.h"
#include "Markov_IO/RandomPulses.h"
#include "Markov_IO/PulsesTrace.h"
#include "Markov_IO/Object.h"
#include "Markov_IO/auxiliarIO.h"

#include "Markov_Mol/QMarkovModel.h"
#include "Markov_Mol/PatchModel.h"
#include "Markov_Mol/GaussianNoise.h"

#include "Markov_IO/FileLoadSave.h"


#include "Markov_IO/Commands.h"
#include "Markov_IO/myTypes.h"
#include "Markov_IO/FileLoadSave.h"


#define STRINGIZE2(s) #s
#define STRINGIZE(s) STRINGIZE2(s)


namespace Markov_IO_New
{


  bool Markov_CommandManagerVar::setDir(const std::string &dir)
  {
    if (!fd::isDir(dir))
      return false;
    dir_=dir;
    //autoCmptByCategories[directory()]=Autocomplete(Markov_IO::getSubDirs(dir));
    //TODO                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            : include this former functionality (list of macror files)
    // filesl=LoadFiles(dir);
    return true;
  }


  void Markov_CommandManagerVar::KeyEvent(Key k)
  {
    e->KeyEvent(this,getIO(),getH(),k);
  }

  Markov_CommandManagerVar::Markov_CommandManagerVar():
   Implements_ComplexVar_New(nullptr,"CommandManager","CommandManager","",""),
  io_(nullptr),
    vt_{Variable::types::varNew::varType(this)},
    idCmd_(Identifier::types::idCmd::varType(this)),
    e(nullptr),
    lastCmdRst{},
    program_ver_(ProgramVersion()),
    dir_{Markov_IO_New::fd::getWorkingPath()},
    h_(new CommandHistory(""))
{
  setParentValue(nullptr);

  cmd::pushAllCommands(this);
_private::push_Types(this);
 Identifier::push_Types(this);

  e=new ExpressionManager(this);

  //    auto dirs=Markov_IO::getSubDirs(dir_);
  //    filesl=LoadFiles(getDir());
  //    autoCmptByKind[ABC_Command::directory()]=Autocomplete(dirs);
  //    autoCmptByKind[ABC_Command::fileName()]=LoadFiles(getDir());

//  Loadcommands();
  //    cmdsl=Autocomplete(cmds);
//  LoadTypes();

  //  UpdateIdLists();
  }

  CommandHistory &Markov_CommandManagerVar::getH()
  {
   return *h_;
  }

  void Markov_CommandManagerVar::run(const Implements_Command_Arguments *arg)
  {
    std::string dummyError;
    const Implements_Command_Type_New* ctp=idToCommand(arg->myType(),&dummyError,"");
    ctp->run(this,arg->value()->getValued(),&dummyError,"");
  }



  std::string ProgramVersion::buildVersion()
  {
    std::string d=Markov_IO::getExecutableDir();
    std::string fname=STRINGIZE(GIT_VER_PATH);
    std::string path=d+Markov_IO::FileDir::slash()+fname;
    std::fstream f(path.c_str());
    if (!(f))
      {
        f.close();
        path=Markov_IO::getDirectory(d)+Markov_IO::FileDir::slash()+fname;
        f.open(path.c_str());
      }

    std::string lineHash;
    Markov_IO::safeGetline(f,lineHash);
    return lineHash;
  }

  std::string ProgramVersion::buildDate()
  {
    std::string d=Markov_IO::getExecutableDir();
    std::string fname=STRINGIZE(GIT_VER_PATH);
    std::string path=d+Markov_IO::FileDir::slash()+fname;
    std::fstream f(path.c_str());
    if (!(f))
      {
        f.close();
        path=Markov_IO::getDirectory(d)+Markov_IO::FileDir::slash()+fname;
        f.open(path.c_str());
      }
    std::string line;
    Markov_IO::safeGetline(f,line);
    std::string lineDate;
    Markov_IO::safeGetline(f,lineDate);
    return lineDate;
  }

  std::string ProgramVersion::uncommitedFiles()
  {
    std::string d=Markov_IO::getExecutableDir();
    std::string fname=STRINGIZE(UNCOMMITED_PATH);
    std::string path=d+Markov_IO::FileDir::slash()+fname;
    std::fstream f(path.c_str());
    if (!(f))
      {
        f.close();
        path=Markov_IO::getDirectory(d)+Markov_IO::FileDir::slash()+fname;
        f.open(path.c_str());
      }
    std::string lineUncommited0;
    std::string lineUncommited;
    while ( Markov_IO::safeGetline(f,lineUncommited0))
      {
        lineUncommited+=lineUncommited0;
        if (Markov_IO::safeGetline(f,lineUncommited0))
          lineUncommited+=" "+lineUncommited0+"\n";
      }
    return lineUncommited;
  }

  std::string ProgramVersion::wellcomeMessage(unsigned ncols)const
  {
    std::string wllc;
    std::string decorating_line(ncols,'#');
    std::string vers=version();
    std::string motto="Statistically Sound Molecular Kinetics";
    std::string date_build=buildDate()+"    build:"+buildVersion();
    std::string updatesMss="updates in http://code.google.com/p/macror/";
    std::string helpmss="enter help for help";

    wllc+=decorating_line+"\n";

    int pos0=0;
    if (ncols>vers.size())
      pos0=(ncols-vers.size())/2;
    wllc+=std::string(pos0,' ')+vers+"\n";

    pos0=0;
    if (ncols>motto.size())
      pos0=(ncols-motto.size())/2;
    wllc+=std::string(pos0,' ')+motto+"\n";

    pos0=0;
    if (ncols>date_build.size())
      pos0=(ncols-date_build.size())/2;
    wllc+=std::string(pos0,' ')+date_build+"\n";

    wllc+=decorating_line+"\n";

    std::string uncomf=uncommitedFiles();
    if (!uncomf.empty())
      {
        std::string warnmg="Warning: there are uncommited files, build number refers to a previous build";
        wllc+=warnmg+"\n";
        wllc+=uncomf+"\n";
      }

    wllc+=updatesMss+"\n";
    wllc+=helpmss+"\n";
    return wllc;
  }



};





namespace Markov_Console
{



/*
  bool Markov_CommandManagerVar::processTokens(Markov_IO::Token_Stream &t)
  {
    if (t.currToken().tok()==Markov_IO::Token_New::IDENTIFIER)
      {
        auto id=t.currToken().str();
        if (has_command(id))
          {
            return getCommand(id)->processTokens(t);
          }
        else if (has_var(id)&&(t.nextToken(1).tok()==Markov_IO::Token_New::EOL))
          {
            return getCommand("show")->processTokens(t);
          }
        else
          {
            // v is a naked pointer, it has to be deleted
            auto v=Markov_IO::ABC_Var::getValueFromStream(t);
            if (v!=nullptr)
              {
                Markov_IO::ABC_Value* c=getClass(v->myVar());
                auto d=c->toIndicatedVar(v);

                if (d!=nullptr)
                  {
                    delete v;
                    if (!has_var(d->id()))
                      add_var(d);
                    else
                      delete d;
                  }
                else
                  {
                    if (!has_var(v->id()))
                      add_var(v);
                    else
                      delete v;
                  }
                return true;
              }
            else
              return false;

          }
      }
    else
      return false;
  }



*/





  void Markov_CommandManagerVar::KeyEvent(Markov_IO::Key k)
  {
    e->KeyEvent(this,getIO(),getH(),k);
  }

  Markov_CommandManagerVar::Markov_CommandManagerVar():
    io_(nullptr),
    e(new ExpressionManager(this)),

    dir_{Markov_IO::getWorkingPath()},
    cmds{},
    variables_{},
    varsl{},
    tokens{},
    lastCmdRst{},
    h("")

  {
    setParentValue(nullptr);

    //    auto dirs=Markov_IO::getSubDirs(dir_);
    //    filesl=LoadFiles(getDir());
    //    autoCmptByKind[ABC_Command::directory()]=Autocomplete(dirs);
    //    autoCmptByKind[ABC_Command::fileName()]=LoadFiles(getDir());

    Loadcommands();
    //    cmdsl=Autocomplete(cmds);
    LoadTypes();

    UpdateIdLists();
  }











//  std::string Markov_CommandManagerVar::getHelpDir()
//  {
//    return STRINGIZE(HELP_PATH);
//  }

  std::string Markov_CommandManagerVar::directory()
  {
    return "Directory";
  }

  std::string Markov_CommandManagerVar::idVarName()  {
    return "IdVar";
  }

  std::string Markov_CommandManagerVar::idTypeName()
  {
    return "IdType";
  }

  std::string Markov_CommandManagerVar::fileName()
  {
    return "FileName";
  }

  std::string Markov_CommandManagerVar::testName()
  {
    return "IdTest";
  }

  std::string Markov_CommandManagerVar::idCommandName()
  { return "IdCommand";}

//  std::vector<std::string> Markov_CommandManagerVar::complete(const std::string &hint, const std::string &category) const

//  {
//    auto it= autoCmptByCategories.find(category);
//    if (it!=autoCmptByCategories.end())
//      {
//        Autocomplete a=it->second;
//        return a.complete(hint);
//      }
//    else
//      {
//        return {};
//      }
//  }

//  std::map<std::string, std::vector<std::string> > Markov_CommandManagerVar::complete(const std::string &hint, const std::vector<std::pair<std::string, bool> > &categories) const
//  {
//    std::map<std::string,std::vector<std::string>> out;
//    for (std::pair<std::string,bool> cat:categories)
//      {
//        auto v=complete(hint,cat.first);
//        if (!v.empty())
//          out[cat.first]=v;
//      }
//    return out;

//  }





  std::string Markov_CommandManagerVar::getDir() const {return dir_;}

  bool Markov_CommandManagerVar::setDir(const std::string &dir)
  {
    if (!Markov_IO::IsDir(dir))
      return false;
    dir_=dir;
    autoCmptByCategories[directory()]=Autocomplete(Markov_IO::getSubDirs(dir));
    //TODO: include this former functionality (list of macror files)
    // filesl=LoadFiles(dir);
    return true;
  }

  Markov_IO::ABC_IO *Markov_CommandManagerVar::getIO() const {return io_;}

  void Markov_CommandManagerVar::setIO(Markov_IO::ABC_IO *io){io_=io;}

  CommandHistory &Markov_CommandManagerVar::getH(){return h;}





  Markov_CommandManagerVar::~Markov_CommandManagerVar()
  {

  }


  std::string ProgramVersion::buildVersion()
  {
    std::string d=Markov_IO::getExecutableDir();
    std::string fname=STRINGIZE(GIT_VER_PATH);
    std::string path=d+Markov_IO::FileDir::slash()+fname;
    std::fstream f(path.c_str());
    if (!(f))
      {
        f.close();
        path=Markov_IO::getDirectory(d)+Markov_IO::FileDir::slash()+fname;
        f.open(path.c_str());
      }

    std::string lineHash;
    Markov_IO::safeGetline(f,lineHash);
    return lineHash;
  }

  std::string ProgramVersion::buildDate()
  {
    std::string d=Markov_IO::getExecutableDir();
    std::string fname=STRINGIZE(GIT_VER_PATH);
    std::string path=d+Markov_IO::FileDir::slash()+fname;
    std::fstream f(path.c_str());
    if (!(f))
      {
        f.close();
        path=Markov_IO::getDirectory(d)+Markov_IO::FileDir::slash()+fname;
        f.open(path.c_str());
      }
    std::string line;
    Markov_IO::safeGetline(f,line);
    std::string lineDate;
    Markov_IO::safeGetline(f,lineDate);
    return lineDate;
  }

  std::string ProgramVersion::uncommitedFiles()
  {
    std::string d=Markov_IO::getExecutableDir();
    std::string fname=STRINGIZE(UNCOMMITED_PATH);
    std::string path=d+Markov_IO::FileDir::slash()+fname;
    std::fstream f(path.c_str());
    if (!(f))
      {
        f.close();
        path=Markov_IO::getDirectory(d)+Markov_IO::FileDir::slash()+fname;
        f.open(path.c_str());
      }
    std::string lineUncommited0;
    std::string lineUncommited;
    while ( Markov_IO::safeGetline(f,lineUncommited0))
      {
        lineUncommited+=lineUncommited0;
        if (Markov_IO::safeGetline(f,lineUncommited0))
          lineUncommited+=" "+lineUncommited0+"\n";
      }
    return lineUncommited;
  }

  std::string ProgramVersion::wellcomeMessage(unsigned ncols)const
  {
    std::string wllc;
    std::string decorating_line(ncols,'#');
    std::string vers=version();
    std::string motto="Statistically Sound Molecular Kinetics";
    std::string date_build=buildDate()+"    build:"+buildVersion();
    std::string updatesMss="updates in http://code.google.com/p/macror/";
    std::string helpmss="enter help for help";

    wllc+=decorating_line+"\n";

    int pos0=0;
    if (ncols>vers.size())
      pos0=(ncols-vers.size())/2;
    wllc+=std::string(pos0,' ')+vers+"\n";

    pos0=0;
    if (ncols>motto.size())
      pos0=(ncols-motto.size())/2;
    wllc+=std::string(pos0,' ')+motto+"\n";

    pos0=0;
    if (ncols>date_build.size())
      pos0=(ncols-date_build.size())/2;
    wllc+=std::string(pos0,' ')+date_build+"\n";

    wllc+=decorating_line+"\n";

    std::string uncomf=uncommitedFiles();
    if (!uncomf.empty())
      {
        std::string warnmg="Warning: there are uncommited files, build number refers to a previous build";
        wllc+=warnmg+"\n";
        wllc+=uncomf+"\n";
      }

    wllc+=updatesMss+"\n";
    wllc+=helpmss+"\n";
    return wllc;
  }


  std::string ProgramVersion::version()const
  {
    std::string version="MacroConsole 0.1";
    return version;
  }






  bool Markov_CommandManagerVar::has_command(const std::string& name)const{
    return (cmds.find(name)!=cmds.end());
  }

  void Markov_CommandManagerVar::add_var(Markov_IO::ABC_Var *v)
  {
    if (v!=nullptr)
      {
        Markov_IO::ABC_Value* c=getClass(v->myVar());
        auto d=c->toIndicatedVar(v);

        if (d!=nullptr)
          {
            delete v;
            if (!has_var(d->id()))
              push_var(d);
            else
              delete d;
          }
        else
          {
            if (!has_var(v->id()))
              push_var(v);
            else
              delete v;
          }
      }
  }

  const ABC_CommandVar *Markov_CommandManagerVar::getCommand(const std::string &cmdlabel) const
  {
    auto it=cmds.find(cmdlabel);
    if (it!=cmds.end())
      return it->second;
    else
      return nullptr;
  }

  ABC_CommandVar *Markov_CommandManagerVar::getCommand(const std::string &cmdlabel)
  {
    auto it=cmds.find(cmdlabel);
    if (it!=cmds.end())
      return it->second;
    else
      return nullptr;
  }

  Markov_IO::ABC_Var *Markov_CommandManagerVar::getVar(const std::string &name)
  {
    auto it=variables_.find(name);
    if (it!=variables_.end())
      return it->second;
    else
      return nullptr;


  }

  void Markov_CommandManagerVar::push_var(Markov_IO::ABC_Var *v)
  {
    if (!has_child(v->id()))
      {
        pushChild(v);
        variables_[v->id()]=v;
        autoCmptByCategories[idVarName()].push_back(v->id());
      }
  }


  bool Markov_CommandManagerVar::has_var(const std::string& name)const{
    return (variables_.find(name)!=variables_.end());
  }

  const Markov_IO::Implements_Identifier_Class *Markov_CommandManagerVar::getIdList(const std::string &name) const
  {
    auto it=idLists_.find(name);
    if (it!=idLists_.end())
      {
        return it->second;
      }
    else
      return nullptr;
  }

  ProgramVersion &Markov_CommandManagerVar::getProgram()
  {
    return program_ver_;
  }

  void Markov_CommandManagerVar::putOut(const std::string &m) const
  {
    getIO()->put(m);
  }

  void Markov_CommandManagerVar::putErrorOut(const std::string &m) const
  {
    getIO()->putError(m);
  }

  ABC_Command *Markov_CommandManagerVar::getCommand(const Markov_IO::Token_New &t){}

  std::set<std::string> Markov_CommandManagerVar::getCommandList() const
  {
      return Markov_IO::getLables(cmds);
  }








  Markov_IO::ABC_Value* Markov_CommandManagerVar::getClass(std::string name)
  {

  }
























}




namespace Markov_Console
{









  std::string Markov_CommandManager::getHelpDir()
  {
    return STRINGIZE(HELP_PATH);
  }




  void Markov_CommandManager::KeyEvent(Markov_IO::Key k)
  {
    e->KeyEvent(nullptr,getIO(),getH(),k);
  }

  Markov_CommandManager::Markov_CommandManager():
    io_(nullptr),
    dir_{Markov_IO::getWorkingPath()},
    cmds{},
    cmdsl{},
    vars{},
    varByType{},
    varsl{},
    types{},
    regulartypes{},
    childs{},
    parent{},
    autoCmptBySuperClass{},
    autoCmptByClass{},
    tokens{},
    lastCmdRst{},
    h("")

  {
    auto dirs=Markov_IO::getSubDirs(dir_);
    filesl=LoadFiles(getDir());
    autoCmptByKind[ABC_Command::directory()]=Autocomplete(dirs);
    autoCmptByKind[ABC_Command::fileName()]=LoadFiles(getDir());

    Loadcommands();
    cmdsl=Autocomplete(cmds);
    LoadTypes();
  }

  Markov_CommandManager::~Markov_CommandManager()
  {
    for (std::map<std::string,Markov_IO::ABC_Saveable*>::iterator
         it=vars.begin();
         it!=vars.end();
         ++it)
      delete it->second;
    for (std::map<std::string,ABC_Command*>::iterator
         it=cmds.begin();
         it!=cmds.end();
         ++it)
      delete it->second;

  }


  std::string Markov_CommandManager::buildVersion()const
  {
    std::string d=Markov_IO::getExecutableDir();
    std::string fname=STRINGIZE(GIT_VER_PATH);
    std::string path=d+Markov_IO::FileDir::slash()+fname;
    std::fstream f(path.c_str());
    if (!(f))
      {
        f.close();
        path=Markov_IO::getDirectory(d)+Markov_IO::FileDir::slash()+fname;
        f.open(path.c_str());
      }

    std::string lineHash;
    Markov_IO::safeGetline(f,lineHash);
    return lineHash;
  }

  std::string Markov_CommandManager::buildDate()const
  {
    std::string d=Markov_IO::getExecutableDir();
    std::string fname=STRINGIZE(GIT_VER_PATH);
    std::string path=d+Markov_IO::FileDir::slash()+fname;
    std::fstream f(path.c_str());
    if (!(f))
      {
        f.close();
        path=Markov_IO::getDirectory(d)+Markov_IO::FileDir::slash()+fname;
        f.open(path.c_str());
      }
    std::string line;
    Markov_IO::safeGetline(f,line);
    std::string lineDate;
    Markov_IO::safeGetline(f,lineDate);
    return lineDate;
  }

  std::string Markov_CommandManager::uncommitedFiles()const
  {
    std::string d=Markov_IO::getExecutableDir();
    std::string fname=STRINGIZE(UNCOMMITED_PATH);
    std::string path=d+Markov_IO::FileDir::slash()+fname;
    std::fstream f(path.c_str());
    if (!(f))
      {
        f.close();
        path=Markov_IO::getDirectory(d)+Markov_IO::FileDir::slash()+fname;
        f.open(path.c_str());
      }
    std::string lineUncommited0;
    std::string lineUncommited;
    while ( Markov_IO::safeGetline(f,lineUncommited0))
      {
        lineUncommited+=lineUncommited0;
        if (Markov_IO::safeGetline(f,lineUncommited0))
          lineUncommited+=" "+lineUncommited0+"\n";
      }
    return lineUncommited;
  }

  std::string Markov_CommandManager::wellcomeMessage(unsigned ncols)const
  {
    std::string wllc;
    std::string decorating_line(ncols,'#');
    std::string vers=version();
    std::string motto="Statistically Sound Molecular Kinetics";
    std::string date_build=buildDate()+"    build:"+buildVersion();
    std::string updatesMss="updates in http://code.google.com/p/macror/";
    std::string helpmss="enter help for help";

    wllc+=decorating_line+"\n";

    int pos0=0;
    if (ncols>vers.size())
      pos0=(ncols-vers.size())/2;
    wllc+=std::string(pos0,' ')+vers+"\n";

    pos0=0;
    if (ncols>motto.size())
      pos0=(ncols-motto.size())/2;
    wllc+=std::string(pos0,' ')+motto+"\n";

    pos0=0;
    if (ncols>date_build.size())
      pos0=(ncols-date_build.size())/2;
    wllc+=std::string(pos0,' ')+date_build+"\n";

    wllc+=decorating_line+"\n";

    std::string uncomf=uncommitedFiles();
    if (!uncomf.empty())
      {
        std::string warnmg="Warning: there are uncommited files, build number refers to a previous build";
        wllc+=warnmg+"\n";
        wllc+=uncomf+"\n";
      }

    wllc+=updatesMss+"\n";
    wllc+=helpmss+"\n";
    return wllc;
  }


  std::string Markov_CommandManager::version()const
  {
    std::string version="MacroConsole 0.1";
    return version;
  }

  std::size_t Markov_CommandManager::getVersion(const std::string& line)
  {
    if (line.find("MacroR")==0)
      {
        std::size_t n=line.find_last_of('.');
        if (n!=line.npos)
          {
            std::string num=line.substr(n+1);
            std::size_t ver;
            if (Markov_IO::ToValue(num,ver))
              return ver;
            else
              return 0;
          }
        else
          return 0;
      }
    return 0;
  }




  void Markov_CommandManager::add_command(ABC_Command* cmd)
  {
    cmds[cmd->commandName()]=cmd;
    cmdsl.push_back(cmd->commandName());
  }

  void Markov_CommandManager::add_type(const std::string& name, const Markov_IO::ABC_Saveable* s)
  {
    types[name]=s;
    typesl.push_back(name);
    autoCmptByKind[ABC_Command::typeName()].push_back(name);
  }

  void Markov_CommandManager::add_var(std::string name, Markov_IO::ABC_Saveable* s)
  {
    delete_var(name);
    vars[name]=s;
    autoCmptByKind[ABC_Command::varName()].push_back(name);
    varsl.push_back(name);
    autoCmptBySuperClass[s->mySuperClass()].push_back(name);
    autoCmptByClass[s->myClass()].push_back(name);

  }







  void Markov_CommandManager::erase_tokens(int n)
  {
    for (int i=0; i<n; i++) tokens.erase(tokens.begin());
  }

  bool Markov_CommandManager::checkVariable(std::string var, std::string type)const
  {
    auto itkind=autoCmptByKind.find(type);

    if (itkind!=autoCmptByKind.end())
      {
        return itkind->second.has(var);
      }
    else
      {
        auto itype=regulartypes.find(type);
        if (itype!=regulartypes.end())
          {
            //TODO: replace with ABC_Var logic
            Markov_IO::ABC_Object* o=itype->second->create();

            return Markov_IO::ToObject(var,o);
          }
        else
          {
            auto it=vars.find(var);
            if (it!=vars.end())
              {
                return ((*it).second->mySuperClass()==type)||((*it).second->myClass()==type);
              }
            else
              {
                return false;
              }
          }
      }
  }
  bool Markov_CommandManager::has_var(const std::string& name)const {
    return (vars.find(name)!=vars.end());
  }




  bool Markov_CommandManager::has_type(const std::string& name)const
  {
    return (types.find(name)!=types.end());
  }

  bool Markov_CommandManager::has_superType(const std::string& name)const
  {
    return (childs.find(name)!=childs.end());
  }


  bool Markov_CommandManager::has_command(const std::string& name)const{
    return (cmds.find(name)!=cmds.end());
  }


  bool Markov_CommandManager::has_script(const std::string& fname)const
  {
    std::string fn=fname;
    fn=+".macror.txt";
    std::ifstream f(fn.c_str());
    return(!!f);
  }

  void Markov_CommandManager::runScript( std::string file)
  {
    Markov_Script(this, file);
    std::cout << std::endl;
    std::cout << "Script completed." << std::endl;
  }


  void Markov_CommandManager::missing_parameter()
  {
    std::cout << "Missing Parameter" << std::endl;
  }

  void Markov_CommandManager::unknown_command()
  {
    getIO()->putError("Unknown Command\n");
  }




  void Markov_CommandManager::printErrorMessage(const std::string& errorMessage, ABC_Command* )
  {
    std::cout<<errorMessage<<"\n";
  }




  /**
           Execute the next instruction in the list of inserted instruction
           @pre one or more instructions have to be inserted
           @post if the inserted instruction is valid it runs, else
           an error is written at stdout
           */
  bool Markov_CommandManager::next_instruction()
  {
    if (tokens.size()==0) return false;

    // check if it is an assigment or not

    //  h.push_back(tokens);

    bool isAssigment=(tokens.size()>2)&&(tokens[1].get_token()==Token::ASSIGN);

    if (!isAssigment)
      {
        switch (tokens[0].get_token())
          {
          case Token::IDENTIFIER:
            if (has_var(tokens[0].Name()))
              {
                std::stringstream ss("show");
                Token t;
                t.get(ss);
                tokens.push_front(t);
              }

            if (has_command(tokens[0].Name()))
              {
                ABC_Command* cmd=cmds[tokens[0].Name()];
                tokens.erase(tokens.begin());
                lastCmdRst=cmd->run(tokens);
                auto out=cmd->output();
                auto err=cmd->errorMessage();
                if (!out.empty())
                  getIO()->put(out+"\n");
                if (!err.empty())
                  getIO()->putError(err+"\n");
              }
            else if (has_script(tokens[0].Name()))
              {
                runScript(tokens[0].Name()+".macror.txt");
              }/*
                     else if (tokens[0].Name()=="model")
                     {
                         if (tokens.size()<2)
                         {
                             std::cerr<<"enter \n model channel    or \n model patch \n";
                         }
                         else if (tokens[1].Name()=="channel")
                         {
                             if (tokens.size()<3)
                                 model_channel("mychannel");
                             else model_channel(tokens[2].Name());
                         }
                         else if (tokens[1].Name()=="patch")
                         {
                             if (tokens.size()<3)
                                 model_patch("mypatch");
                             else model_patch(tokens[2].Name());
                         }

                     }*/
            /*    else if (tokens[0].Name()=="option")
                     {
                         if (tokens.size()<2)
                         {
                             std::cout<<"enter:  \n"
                                        "\t option simulate    or \n"
                                        "\t option likelihood  or \n"
                                        "\t option optimize    \n";
                         }
                         else if (tokens.size()<3)
                             option(tokens[1].Name(),"");
                         else
                             option(tokens[1].Name(),tokens[2].Name());
                     }*/
            /*        else if (tokens[0].Name()=="experiment")
                     {
                         if (tokens.size()<2)
                             experiment("myexperiment");
                         else experiment(tokens[1].Name());
                     }*/
            else if (tokens[0].Name()=="RunScript")
              {
                if (tokens.size()<2) missing_parameter();
                else runScript(tokens[1].Name());
              }
            else
              {
                unknown_command();
                return false;
              }

            //std::cout << std::endl;
            return true;
          default:
            return false;

          }

      }
    return false;
  }
  /**
           Insert a string with one or more intructions to be executed
           */
  void Markov_CommandManager::add_tokens(std::string commandLine)
  {
    // construct a stream from the string
    std::stringstream strstr(commandLine);

    Token t;
    tokens.clear();
    while (strstr>>t)
      tokens.push_back(t);
  }



  void Markov_CommandManager::clear_tokens()
  {
    tokens.clear();
  }





  /*!
            * \brief Markov_CommandManager::add_single_token adds one token to the current command line
            * \param command  the added token
            */



  std::string Markov_CommandManager::add_single_token(const std::string& command)
  {
    // construct a stream from the string
    std::stringstream strstr(command);

    Token t;
    while (strstr>>t)
      tokens.push_back(t);
    std::string res= check_tokens();
    if (!res.empty()&&!tokens.empty())
      tokens.pop_back();
    return res;

  }




  std::string Markov_CommandManager::check_tokens()
  {
    if (has_var(tokens[0].Name()))
      {
        return "";
      }

    if (has_command(tokens[0].Name()))
      {
        ABC_Command* cmd=cmds.find(tokens[0].Name())->second;
        return cmd->check(tokens);
      }
    else if (has_script(tokens[0].Name()))
      {
        return "";
      }
    else return "unknown command";



  }


  ABC_Command* Markov_CommandManager::getCommand(const Markov_IO::Token_New& t)
  {
    if (t.tok()!=Markov_IO::Token_New::IDENTIFIER)
      return nullptr;
    else
      {
        auto it=cmds.find(t.toString());
        if (it!=cmds.end())
          return it->second;
        else
          return nullptr;
      }
  }



  Markov_IO::ABC_Value* Markov_CommandManager::getClass(std::string name)
  {
    auto it=classTypes.find(name);
    if (it!=classTypes.end())
      return it->second;
    else
      return
          nullptr;

  }







  std::vector<std::string> Markov_CommandManager::complete(const std::string& hint,
                                                           const std::string& category)
  {
    auto itkind=autoCmptByKind.find(category);
    if (has_superType(category))
      return autoCmptBySuperClass[category].complete(hint);
    else if (has_type(category))
      return autoCmptByClass[category].complete(hint);
    else   if (itkind!=autoCmptByKind.end())
      return autoCmptByKind[category].complete(hint);
    else
      return {};


  }


  /*!
            * \brief Markov_CommandManager::complete list possible commands or options
            * \param hint characters to be matched
            * \return the list of matching commands or files or alias
            */

  std::vector<std::string> Markov_CommandManager::complete(const std::string &hint)
  {
    if (tokens.empty())
      return cmdsl.complete(hint);
    else {
        Token t=tokens[0];
        if ( t.get_token()==Token::IDENTIFIER )
          {
            if (this->has_command(t.Name()))
              {
                ABC_Command* cmd=cmds[t.Name()];
                return cmd->complete(hint,tokens);
              }
          }

      }
    return std::vector<std::string>();
  }


  bool Markov_CommandManager::runLine(std::string commandLine)
  {
    std::deque<Token> tokensBuffer=tokens;
    add_tokens(commandLine);
    while(!tokens.empty())
      {
        if (!next_instruction())
          {
            tokens=tokensBuffer;
            return false;

          }
      }
    tokens=tokensBuffer;
    return true;
  }


  std::vector<std::string> Markov_CommandManager::getSiblings(std::string name)const
  {
    std::map<std::string, std::string>::const_iterator itp=parent.find(name);
    if (itp!=parent.end())
      {
        auto it=childs.find(itp->second);
        if (it!=childs.end())
          return it->second;

      }
    return std::vector<std::string>();
  }

  std::vector<std::string> Markov_CommandManager::getVarSiblings(std::string name)const
  {
    std::map<std::string, std::string>::const_iterator itp=parent.find(name);
    if (itp!=parent.end())
      {
        auto it=childs.find(itp->second);
        if (it!=childs.end())
          return it->second;

      }
    return std::vector<std::string>();
  }


  std::vector<std::string> Markov_CommandManager::getChilds(std::string name)const
  {
    std::map<std::string, std::vector<std::string> >::const_iterator itp=childs.find(name);
    if (itp!=childs.end())
      {
        return itp->second;

      }
    return std::vector<std::string>();
  }

  std::vector<std::string> Markov_CommandManager::getTypesList()
  {
    std::vector<std::string> typelist(types.size());
    std::size_t i=0;
    for (auto it:types)
      {
        typelist[i]=it.first;
        i++;
      }
    return typelist;
  }



  const Markov_IO::ABC_Saveable* Markov_CommandManager::getType(const std::string& typeName)const
  {
    Markov_IO::ABC_Saveable* v=0;
    std::map<std::string,const Markov_IO::ABC_Saveable*>::const_iterator it;
    it=types.find(typeName);
    if(it==types.end())
      return v;
    else
      return it->second;
  }


  Markov_IO::ABC_Saveable* Markov_CommandManager::getVar(const std::string& varName)
  {
    Markov_IO::ABC_Saveable* v=0;
    if (!has_var(varName))
      return v;
    return vars[varName];
  }

  bool Markov_CommandManager::getVarCopy(const std::string& varName,
                                         Markov_IO::ABC_Saveable*& varType)const
  {

    std::map<std::string,Markov_IO::ABC_Saveable*>::const_iterator it=vars.find(varName);
    if (it==vars.end())
      return false;

    Markov_IO::ABC_Saveable* var=varType->create(it->second->myClass());
    if (var)
      {
        *var=*it->second;
        delete varType;
        varType=var;
        return true;
      }
    else
      return false;

  }


  bool Markov_CommandManager::getVar(const std::string& varName,
                                     Markov_IO::ABC_Saveable*& varType)
  {
    Markov_IO::ABC_Saveable* v;
    if (!has_var(varName))
      return false;
    v=vars[varName];


    Markov_IO::ABC_Saveable* var=varType->create(v->myClass());
    if (var)
      {
        varType=v;
        delete var;
        return true;
      }
    else
      {
        delete var;
        return false;
      }

  }


  std::vector<std::string> Markov_CommandManager::getVarsList(Markov_IO::ABC_Saveable* varType) const
  {

    std::vector<std::string> list;
    std::map<std::string,Markov_IO::ABC_Saveable*>::const_iterator it;
    for (it=vars.begin();it!=vars.end();++it)
      {
        Markov_IO::ABC_Saveable* var=varType->create(it->second->myClass());
        if (var)
          {
            list.push_back(it->first);
            delete var;
          }
      }
    return list;
  }





  std::vector<std::string> Markov_CommandManager::getVarsList()
  {
    std::vector<std::string> varList;
    for (std::map<std::string,Markov_IO::ABC_Saveable*>::const_iterator it
         =vars.begin();
         it!=vars.end();++it)
      {
        varList.push_back(it->first);

      }

    auto l=getDataList();
    varList.insert(varList.begin(),l.begin(),l.end());
    return varList;
  }






  void Markov_CommandManager::delete_var(const std::string& name)
  {
    if (has_var(name))
      {
        delete vars[name];
        vars.erase(name);
      }
    else if (name=="all")
      {
        for (std::map<std::string,Markov_IO::ABC_Saveable*>::iterator
             it=vars.begin();
             it!=vars.end();
             ++it)
          delete it->second;
        vars.clear();
      }


  }



  bool Markov_CommandManager::edit(Markov_IO::ClassDescription& classDes)
  {
    Markov_IO::ClassDescription desc=classDes;
    while (true)
      {
        std::cout<<"Enter either:\n"
                   "(0) a current variable name of the corresponding superClass \n"
                   "(1) ""all"" for editing all the items one by one or \n";
        std::cout<<" (2) the name or (number) of an item of the variable or\n";
        std::cout<<" (3) ""save"" for saving the variable"<<std::endl;
        std::cout<<" (4) ""exit"" for exit without saving changes"<<std::endl;
        std::string resp;
        getline(std::cin, resp);
        std::size_t first=0;
        std::size_t last=0;
        if (checkVariable(resp,desc.SuperClass()))
          {
            std::cout<<"use variable?"<<resp<<"\n"<<*vars[resp]<<std::endl;
            std::cout<<"enter ""yes"" or ""no""";
            std::string resp2;
            getline(std::cin,resp2);
            if (resp2=="yes")
              {
                Markov_IO::ABC_Saveable* s=vars[resp];
                classDes=s->GetDescription();
                return true;
              }
          }
        else if (resp=="all")
          {
            first=0; last=desc.size();
          }
        else if (Markov_IO::ToValue(resp,first)&&(first<desc.size()))
          {
            last=first+1;
          }
        else if (desc.HasElementName(resp))
          {
            first=desc.NameIndex(resp);last=first+1;
          }
        else {
            first=0; last=0;
          }
        for (std::size_t i=first; i<last; i++)
          {
            std::string name=desc.ElementName(i);
            std::cout<<name<<" current value"<<std::endl;
            std::cout<<ToString(*desc[name])<<std::endl;
            if (desc[name]->mySuperClass()==Markov_IO::ABC_Object::ClassName())
              {
                std::cout<<"enter "<<name<< " new value [end with blank line]"<<std::endl;
                std::string value,line;
                getline(std::cin, line);
                value=value+line+"\n";
                while (!line.empty())
                  {
                    getline(std::cin, line);
                    value=value+line+"\n";
                  }
                desc.ReplaceElement(name,value);
              }
            else
              {
                Markov_IO::ABC_Saveable* os=
                    dynamic_cast<const Markov_IO::ABC_Saveable*>(desc[name])->clone();
                Markov_IO::ClassDescription fieldDes=os->GetDescription();

                edit(fieldDes);
                os->LoadFromDescription(fieldDes);
                desc.ReplaceElement(name,*os);
                delete os;
              }

          }
        if (resp=="save")
          {
            std::cout<<"Class Description"<<"\n"<<desc<<"\n";

            classDes=desc;
            std::cout<<"Saving successfull. New value"<<std::endl;

            return true;
          }
        else if (resp=="exit")
          return false;
      }
  }

  bool Markov_CommandManager::setDir(const std::string& dir)
  {
    if (!Markov_IO::IsDir(dir))
      return false;
    dir_=dir;
    autoCmptByKind[ABC_Command::directory()]=Autocomplete(Markov_IO::getSubDirs(dir));
    filesl=LoadFiles(dir);
    return true;
  }




  bool Markov_CommandManager::edit(const std::string& varname)
  {

    if (vars.find(varname)!=vars.end())
      {
        Markov_IO::ABC_Saveable* v=vars[varname];
        Markov_IO::ClassDescription desc=v->GetDescription();
        std::cout<<"Current value of ";
        std::cout<<varname<<", alias of "<<v->id();
        std::cout<<" a "<<v->myClass()<<"  "<<v->mySuperClass()<<std::endl;
        for (std::size_t i=0; i<desc.size(); i++)
          {
            std::cout<<"("<<i<<")"<<desc.ElementName(i)<<std::endl;
            std::cout<<desc.ElementValue(i)<<std::endl;
          }
        bool isEdited=edit(desc);
        bool desValid=false;
        if (isEdited)
          desValid=v->LoadFromDescription(desc);
        if (isEdited && desValid)
          {
            std::cout<<"Saving successfull. New value"<<std::endl;
            std::cout<<*vars[varname];
            return true;
          }
        else
          {
            std::cout<<"Saving unsuccessfull."<<std::endl;
            return false;
          }

      }
    return false;
  }





  bool Markov_CommandManager::lastCommandResult()const
  {
    return lastCmdRst;
  }


  bool Markov_CommandManager::isMacroFile(const std::string& path)
  {
    if (!Markov_IO::IsFile(path))
      return false;
    std::ifstream f(path);
    if (!f)
      return false;
    std::string line;
    Markov_IO::safeGetline(f,line);
    auto vernumber=Markov_CommandManager::getVersion(line);
    return vernumber>0;

  }


  Autocomplete Markov_CommandManager::LoadFiles(const std::string& dir)
  {
    Autocomplete res;
    Markov_IO::FileDir d(dir);
    d.begin();
    while(d.next())
      {
        if (isMacroFile(d.FileName()))
          res.push_back(d.FileName());

      }

    return res;


  }





}




