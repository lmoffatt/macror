#ifndef MARKOV_COMMANDMANAGER_H
#define MARKOV_COMMANDMANAGER_H

#include <map>
#include <vector>
#include <deque>

#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <algorithm>

#include "Markov_IO/ABC_IO.h"
#include "Markov_Mol/ABC_MarkovModel.h"
#include "Markov_Mol/ExperimentSimulation.h"

#include "Markov_IO/ABC_Options.h"


#include "Markov_Console/ABC_Command.h"
#include "Markov_Console/CommandHistory.h"
#include "Markov_Console/Autocomplete.h"

#include "Markov_IO/FileDir.h"

#include "Markov_Bay/ABC_Result.h"

namespace Markov_IO
{
  class ABC_Unit;
}


namespace Markov_Console
{

/**
  @brief Markov_CommandManager manages the commands
  to be executed, keep the declared variables and
  allow to make runs.

  @warning declared variables in MacroR languaje can't be redeclared.
  */


class Markov_CommandManager
{
public:
    Markov_CommandManager();
    ~Markov_CommandManager();

    virtual std::string build()const;
    virtual std::string buildDate()const;
    virtual std::string uncommitedFiles()const;

    virtual std::string version()const;
    virtual std::string wellcomeMessage(unsigned ncols=80)const;

    std::size_t getVersion(const std::string& line)const;


    virtual bool next_instruction();

    virtual void add_tokens(std::string commandLine);

    virtual std::string add_single_token(const std::string &command);

    virtual std::string check_tokens();


    virtual std::vector<std::string> complete(const std::string& hint);

    virtual std::vector<std::string> complete(const std::string& hint,const std::string& category);

    virtual bool runLine(std::string commandLine);

    //virtual std::map<std::string, ABC_Command*>& getCommands() {return cmds;}

    virtual Markov_IO::ABC_Saveable* getVar(const std::string& varName);
    virtual const Markov_IO::ABC_Saveable* getType(const std::string& varName)const;

    virtual bool getVar(const std::string& varName,Markov_IO::ABC_Saveable*& varType);

    virtual bool getVarCopy(const std::string& varName,Markov_IO::ABC_Saveable*& varType)const;

    virtual std::vector<std::string> getVarsList();
    virtual std::vector<std::string> getVarsList(Markov_IO::ABC_Saveable* varType)const;
    virtual std::vector<std::string> getVarsList(std::string className)const;

    virtual std::vector<std::string> getTypesList();



    virtual void printErrorMessage(const std::string& errorMessage,ABC_Command* source);



        virtual Markov_IO::FileDir& getDir() {return dir_;}
    virtual const Markov_IO::FileDir& getDir()const {return dir_;}

    virtual Markov_IO::ABC_IO* getIO(){return io_;}
    virtual void setIO(Markov_IO::ABC_IO* io){io_=io;}


    virtual CommandHistory& getH(){return h;}

    virtual void add_unit(Markov_IO::ABC_Unit* u);
    virtual void add_command(ABC_Command* cmd);
    virtual void add_type(const std::string& name, const Markov_IO::ABC_Saveable *s);

    virtual void add_var(std::string name, Markov_IO::ABC_Saveable* s);




    virtual void erase_tokens(int n);

    virtual  bool edit(const std::string& varname);
    virtual  bool edit(Markov_IO::ClassDescription& varname);




    virtual  bool checkVariable(std::string var, std::string superClass) const;

    virtual std::vector<std::string> getSiblings(std::string name) const;
    virtual  std::vector<std::string> getChilds(std::string name)const;



    virtual  void runScript(std::string file);
    virtual  void missing_parameter();
    virtual  void unknown_command();

    virtual  bool has_command(const std::string& name)const;
    virtual  bool has_var(const std::string& name) const;
    virtual  bool has_type(const std::string& name) const;
    virtual  bool has_superType(const std::string& name) const;

    virtual  bool has_script(const std::string& fname) const;

    virtual  void delete_var(const std::string& name);

    virtual bool lastCommandResult()const;


protected:
    Markov_IO::FileDir dir_;
    Markov_IO::ABC_IO* io_;
    std::map<std::string, Markov_IO::ABC_Unit*> units;
    std::map<std::string, ABC_Command*> cmds;
    Autocomplete cmdsl;


    std::map<std::string, Markov_IO::ABC_Saveable*> vars;

    std::map<std::string, std::map<std::string, Markov_IO::ABC_Saveable*> > varByType;

    Autocomplete varsl;


    std::map<std::string, const Markov_IO::ABC_Saveable*>  types;

    std::map<std::string, const Markov_IO::ABC_Object*>  regulartypes;


    std::map<std::string, std::vector<std::string> > childs;

    std::map<std::string, std::string > parent;

    std::map<std::string,Autocomplete> autoCmptBySuperClass;

    std::map<std::string,Autocomplete> autoCmptByClass;

    /*
    std::map<std::string, Markov_Mol::ABC_PatchModel*> patchs;
    Autocomplete patchsl;
    std::map<std::string, Markov_Mol::ABC_Markov_Model*> models;
    Autocomplete modelsl;
    std::map<std::string, const Markov_Mol::ABC_Markov_Model*> modelsConst;
    std::map<std::string, Markov_IO::ABC_Experiment*> experiments;
    Autocomplete experimentsl;
    std::map<std::string, Markov_IO::Parameters*> parameters;

    std::map<std::string, Markov_Mol::Experiment_simulation*> simulations;

    std::map<std::string, Markov_IO::ABC_Options*> options;

    Autocomplete simulationOptionsl;

    std::map<std::string, Markov_Bay::ABC_Result*> results;

     */


    std::deque<Token> tokens;

    bool lastCmdRst;

    CommandHistory h;

    virtual void Loadcommands();
    virtual void LoadTypes();

};

}

#endif // MARKOV_COMMANDMANAGER_H
