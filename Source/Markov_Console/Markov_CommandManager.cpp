#include <string>
#include <algorithm>

#include "Markov_Console/Markov_CommandManager.h"
#include "Markov_Console/Help_File.h"
#include "Markov_Console/Markov_Script.h"

#include "Markov_Mol/ABC_MarkovModel.h"
#include "Markov_Mol/PatchModel.h"
#include "Markov_Mol/SimulationOptions.h"
#include "Markov_IO/FileDir.h"
#include "Markov_IO/Experiment.h"
#include "Markov_IO/MeasurementUnits.h"

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

#include "Markov_Mol/QMarkovModel.h"
#include "Markov_Mol/PatchModel.h"
#include "Markov_Mol/GaussianNoise.h"





#include "Markov_IO/STD_IO.h"

#define STRINGIZE2(s) #s
#define STRINGIZE(s) STRINGIZE2(s)


namespace Markov_Console
{

  Markov_CommandManager::Markov_CommandManager():
    dir_(),
    io_(new Markov_IO::STD_IO),
    vars(),
    tokens(),
    lastCmdRst(true)
  {
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


  std::string Markov_CommandManager::ver()const
  {
    std::string path=Markov_IO::getExecutableDir()+"/"+STRINGIZE(GIT_VER_PATH);
    std::fstream f(path.c_str());
    std::string lineHash;
    Markov_IO::safeGetline(f,lineHash);
    return lineHash;
  }

  std::string Markov_CommandManager::verDate()const
  {
    std::string path=Markov_IO::getExecutableDir()+"/"+STRINGIZE(GIT_VER_PATH);
    std::fstream f(path.c_str());
    std::string line;
    Markov_IO::safeGetline(f,line);
    std::string lineDate;
    Markov_IO::safeGetline(f,lineDate);
    return lineDate;
  }

  std::string Markov_CommandManager::uncommitedFiles()const
  {
    std::string path2=Markov_IO::getExecutableDir()+"/"+STRINGIZE(UNCOMMITED_PATH);
    std::fstream f2(path2.c_str());
    std::string lineUncommited0;
    std::string lineUncommited;
    while ( Markov_IO::safeGetline(f2,lineUncommited0))
      {
        lineUncommited+=lineUncommited0;
        if (Markov_IO::safeGetline(f2,lineUncommited0))
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
    std::string date_build=verDate()+"    build:"+ver();
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

  std::size_t Markov_CommandManager::getVersion(const std::string& line)const
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

  void Markov_CommandManager::add_unit(Markov_IO::ABC_Unit* u)
  {
    units[u->abbr()]=u;
  }



  void Markov_CommandManager::add_command(ABC_Command* cmd)
  {
    cmds[cmd->commandName()]=cmd;
  }

  void Markov_CommandManager::add_type(const std::string& name, const Markov_IO::ABC_Saveable* s)
  {
    types[name]=s;

  }

  void Markov_CommandManager::add_var(std::string name, Markov_IO::ABC_Saveable* s)
  {
    delete_var(name);
    vars[name]=s;
    varsl.push_back(name);
    autoCmptBySuperClass[s->mySuperClass()].push_back(name);
    autoCmptByClass[s->myClass()].push_back(name);

  }







  void Markov_CommandManager::erase_tokens(int n)
  {
    for (int i=0; i<n; i++) tokens.erase(tokens.begin());
  }

  bool Markov_CommandManager::checkVariable(std::string var, std::string type)
  {
    if (vars.find(var)!=vars.end())
      {
        return ((*vars[var]).mySuperClass()==type);
      }
    else return false;
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
    std::string fn=fname+".macror.txt";
    std::ifstream f(fn.c_str());
    return(!!f);
  }

  void Markov_CommandManager::runScript( std::string file)
  {
    Markov_Script(*this, file);
    std::cout << std::endl;
    std::cout << "Script completed." << std::endl;
  }


  void Markov_CommandManager::missing_parameter()
  {
    std::cout << "Missing Parameter" << std::endl;
  }

  void Markov_CommandManager::unknown_command()
  {
    std::cout << "Unknown Command" << std::endl;
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

    h.push_back(tokens);

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
                  std::cout<<cmd->output()<<"\n";
                if (!err.empty())
                  std::cerr<<cmd->errorMessage()<<"\n";
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
            else if (tokens[0].Name().c_str()=="RunScript")
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
    if (!res.empty())
      tokens.pop_back();
    return res;

  }

  std::string Markov_CommandManager::check_tokens() const
  {
    if (has_var(tokens[0].Name()))
      {
        return "";
      }

    if (has_command(tokens[0].Name()))
      {
        const ABC_Command* cmd=cmds.find(tokens[0].Name())->second;
        return cmd->check(tokens);
      }
    else if (has_script(tokens[0].Name()))
      {
        return "";
      }
    else return "unknown command";



  }




  std::vector<std::string> Markov_CommandManager::complete(const std::string& hint,const std::string& category)
  {
    if (has_superType(category))
      return autoCmptBySuperClass[category].complete(hint);
    else if (has_type(category))
      return autoCmptByClass[category].complete(hint);
    else
      return {"Error: ","\t wrong className"};

  }


  /*!
   * \brief Markov_CommandManager::complete list possible commands or options
   * \param hint characters to be matched
   * \return the list of matching commands or files or alias
   */

  std::vector<std::string> Markov_CommandManager::complete(const std::string& hint)
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

  std::vector<std::string> Markov_CommandManager::getVarsList(std::string className)const
  {
    std::vector<std::string> list;
    std::map<std::string,Markov_IO::ABC_Saveable*>::const_iterator it;
    for (it=vars.begin();it!=vars.end();++it)
      {
        if ((it->second->myClass()==className)||(it->second->mySuperClass()==className))
          {
            list.push_back(it->first);
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




  bool Markov_CommandManager::edit(const std::string& varname)
  {

    if (vars.find(varname)!=vars.end())
      {
        Markov_IO::ABC_Saveable* v=vars[varname];
        Markov_IO::ClassDescription desc=v->GetDescription();
        std::cout<<"Current value of ";
        std::cout<<varname<<", alias of "<<v->myName();
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








}




