#include <string>
#include <algorithm>

#include "Markov_Console/Markov_CommandManager.h"
#include "Markov_Console/ExpressionManager.h"
#include "Markov_Console/Help_File.h"
#include "Markov_Console/CommandHistory.h"
#include "Markov_Mol/ABC_MarkovModel.h"
#include "Markov_Mol/PatchModel.h"
#include "Markov_IO/FileDir.h"
#include "Markov_IO/Experiment.h"



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
#include "Markov_IO/auxiliarIO.h"

#include "Markov_Mol/QMarkovModel.h"
#include "Markov_Mol/PatchModel.h"
#include "Markov_Mol/GaussianNoise.h"

#include "Markov_IO/FileLoadSave.h"


//#include "Markov_IO/Commands.h"
#include "Markov_IO/myTypes.h"
#include "Markov_IO/myTypesExperiment.h"

#include "Markov_IO/FileLoadSave.h"


#include "Markov_IO/Implements_path.h"

#include "Markov_IO/FunctionCommand.h"
#include "Markov_IO/Implements_Closures.h"


#include <random>
#include "Markov_IO/StructureEnv_templ.h"

#include "Markov_Bay/myTypes_Bayesian.h"

#include <random>
#define STRINGIZE2(s) #s
#define STRINGIZE(s) STRINGIZE2(s)


namespace Markov_IO_New
{


  bool Markov_CommandManagerVar::setDir(const std::string &dir)
  {
    if (!fd::isDir(dir))

      return false;
    else
      {
        this->setDataValue<pathName::vars::workingPath>(dir);
        return true;
      }
  }


  void Markov_CommandManagerVar::KeyEvent(Key k)
  {
    e->KeyEvent(this,getIO(),getH(),k);
  }


  void Markov_CommandManagerVar::run(ABC_Input *istream,ABC_Output * ostream,bool checkErrors)
  {
    std::string* whyNot=nullptr;
    if (checkErrors)
      whyNot=new std::string;
    bool s=true;
     while (s)
       {

         Implements_Var v;
          Implements_Var_Closure ic;
          ABC_Closure* c;
          while (istream->nextCharIs('\n',false)){}

          if (getCmdType()->getClosure(this,c,istream,whyNot,""))
            {
              if (ostream!=nullptr)
                 c->putMe(this,ostream,whyNot,"");
              c->evalData(this);

              }
          else if(getFnType()->getValue(this,ic,istream,whyNot,""))
            {
              if (ostream!=nullptr)
                 getFnType()->putValue(this,ic,ostream,whyNot,"");
              this->pushVar({ic.id,ic.closure->evalData(this),ic.Tip,ic.WhatThis});

            }
          else if (getVarType()->getValue(this,v,istream,whyNot,""))
            {
              if (ostream!=nullptr)
                 getVarType()->putValue(this,v,ostream,whyNot,"");
              this->pushVar(v);
            }
          else
            s=false;

    }
  }



  Markov_CommandManagerVar::Markov_CommandManagerVar():
    StructureEnv_New(nullptr,nullptr),
    io_(nullptr),
    vt_{Variable::types::varNew::varType()},
    cmdt_{new Implements_Closure_Type<void*>("",Identifier::types::idCmd::varType())},
    vct_{new Implements_Data_Type_New<Implements_Var_Closure>(
           "",nullptr,
           Identifier::types::idClosureNew::varType("")
           ,new Implements_Closure_Type<void*>()
           ,nullptr,nullptr)},
    e(nullptr),
    lastCmdRst{},
    program_ver_(ProgramVersion()),
    h_(new CommandHistory("")),
    sto_(std::mt19937_64())
  {
    pushVar<pathName::vars::workingPath>(Markov_IO_New::fd::getWorkingPath());

    pushRegularType<Markov_CommandManagerVar*>();
    pushVoidType();
    pushRegularType<bool>();

    Real::push_Types(this);
    Identifier::push_Types(this);
    Data::push_Types(this);
    Variable::push_Types(this);
    ComplexVar::push_Types(this);
    _private::_model::push_Types(this);
_private::_experiment::push_Types(this);
_private::_bayesian::push_Types(this);
    funct::pushAllFunctions(this);

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



  std::__cxx11::string Markov_CommandManagerVar::getDir() const
  {
    std::string dir;
    this->getDataValue<pathName::vars::workingPath>(dir);
    return dir;
  }



  std::string ProgramVersion::buildVersion()
  {
//    std::string d=Markov_IO_New::getExecutableDir();
//    std::string fname=STRINGIZE(GIT_VER_PATH);
//    std::string path=d+Markov_IO_New::FileDir::slash()+fname;
//    std::fstream f(path.c_str());
//    if (!(f))
//      {
//        f.close();
//        path=Markov_IO_New::getDirectory(d)+Markov_IO_New::FileDir::slash()+fname;
//        f.open(path.c_str());
//      }

//    std::string lineHash;
//    Markov_IO_New::safeGetline(f,lineHash);
//    return lineHash;
    return {};
  }

  std::string ProgramVersion::buildDate()
  {
//    std::string d=Markov_IO_New::getExecutableDir();
//    std::string fname=STRINGIZE(GIT_VER_PATH);
//    std::string path=d+Markov_IO_New::FileDir::slash()+fname;
//    std::fstream f(path.c_str());
//    if (!(f))
//      {
//        f.close();
//        path=Markov_IO_New::getDirectory(d)+Markov_IO_New::FileDir::slash()+fname;
//        f.open(path.c_str());
//      }
//    std::string line;
//    Markov_IO::safeGetline(f,line);
//    std::string lineDate;
//    Markov_IO::safeGetline(f,lineDate);
//    return lineDate;
    return {};
  }

  std::string ProgramVersion::uncommitedFiles()
  {
//    std::string d=Markov_IO::getExecutableDir();
//    std::string fname=STRINGIZE(UNCOMMITED_PATH);
//    std::string path=d+Markov_IO::FileDir::slash()+fname;
//    std::fstream f(path.c_str());
//    if (!(f))
//      {
//        f.close();
//        path=Markov_IO::getDirectory(d)+Markov_IO::FileDir::slash()+fname;
//        f.open(path.c_str());
//      }
//    std::string lineUncommited0;
//    std::string lineUncommited;
//    while ( Markov_IO::safeGetline(f,lineUncommited0))
//      {
//        lineUncommited+=lineUncommited0;
//        if (Markov_IO::safeGetline(f,lineUncommited0))
//          lineUncommited+=" "+lineUncommited0+"\n";
//      }
//    return lineUncommited;
    return {};
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






