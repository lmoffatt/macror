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

//#include "Markov_Console/MacorCoreApplication.h"



#include "Markov_IO/FileDir.h"

#include "Markov_Bay/ABC_Result.h"

#include "Markov_Console/ExpressionManager.h"


namespace Markov_Console
{

  class ExpressionManager;




  class ProgramVersion:public Markov_IO::Implements_Complex_Value
    {
  public:
      ProgramVersion():
   //     Markov_IO::Implements_ValueId("Program_Environment","","environment at file creation","")
   //   ,
        Markov_IO::Implements_Complex_Value("Program_Environment","","environment at file creation","")
      {
        push_backVal("Program",programName());
        push_backVal("ver",programVersion());
        push_backVal("buildHash",buildVersion());
        push_backVal("buildDate",buildDate());
        push_backVal("UncommitedFiles",uncommitedFiles());
      }

      static std::string programName(){ return "MacroConsole";}

      static std::string programVersion(){ return "0.2";}

      static std::string buildVersion();
      static std::string buildDate();
      static std::string uncommitedFiles();

      static std::string mySpacer(){return ">>";}

      virtual std::string version()const;
      virtual std::string wellcomeMessage(unsigned ncols=80)const;

      virtual std::string spacer()const{return mySpacer();}

  };






  /**
  @brief Markov_CommandManager manages the commands
  to be executed, keep the declared variables and
  allow to make runs.

  @warning declared variables in MacroR languaje can't be redeclared.
  */







  class Markov_CommandManagerVar: public Markov_IO::Implements_Complex_Value
  {
  public:

   //  bool processTokens(Markov_IO::Token_Stream &t) override;

     void KeyEvent(Markov_IO::Key k);


    Markov_CommandManagerVar();
    virtual ~Markov_CommandManagerVar();

 //   static std::string getHelpDir();

    static std::string directory();

    static std::string idVarName();

    static std::string idTypeName();

    static std::string fileName();

    static std::string testName();

    static std::string idCommandName();


//    virtual  std::vector<std::string>
//    complete(const std::string &hint,
//             const std::string& category)const;


//    virtual  std::map<std::string,std::vector<std::string>>
//    complete(const std::string &hint,
//             const std::vector<std::pair<std::string, bool>>& categories)const;




    virtual std::string  getDir()const;

    virtual bool setDir(const std::string& dir);

    virtual Markov_IO::ABC_IO* getIO()const;

    virtual void setIO(Markov_IO::ABC_IO* io);


    virtual CommandHistory& getH();


    virtual void add_var(Markov_IO::ABC_Var *v);

    virtual void run(ABC_CommandVar *v)
    {
      if (v!=nullptr)
        {
      auto c=getCommand(v->id());
      if (c!=nullptr)
        {
          c->run(v);
        }
        }
    }



    ABC_CommandVar const* getCommand(const std::string& cmdlabel)const;

    ABC_CommandVar * getCommand(const std::string& cmdlabel);

    Markov_IO::ABC_Var* getVar(const std::string& name);



    virtual  bool has_command(const std::string& name)const;

    virtual bool has_var(const std::string& name)const;


    
const Markov_IO::Implements_Identifier_Class* getIdList(const std::string& name)const;


    ProgramVersion& getProgram();



  protected:
    Markov_IO::ABC_IO* io_;

    ExpressionManager* e;

    ProgramVersion program_ver_;

    std::string dir_;

    std::map<std::string, ABC_CommandVar*> cmds;

    std::map<std::string, Markov_IO::ABC_Var*> variables_;


     std::map<std::string,Markov_IO::Implements_Identifier_Class*> idLists_;



    Autocomplete varsl;

    std::map<std::string,Autocomplete> autoCmptByCategories;


    std::deque<Token> tokens;

    bool lastCmdRst;

    CommandHistory h;

    virtual void Loadcommands();
    virtual void LoadTypes();

    virtual void UpdateIdLists();

    // ABC_Environment interface
  public:
    virtual void putOut(const std::string &m) const;
    virtual void putErrorOut(const std::string &m) const;

    virtual ABC_Command *getCommand(const Markov_IO::Token_New &t);


    virtual std::set<std::string> getCommandList()const;
    bool processCommand(ExpressionManager &e);
    Markov_IO::ABC_Value *getClass(std::string name);

    void push_var(Markov_IO::ABC_Var *v);
  };



  class Markov_CommandManager: public Markov_IO::ABC_Environment
  {
  public:

    virtual void KeyEvent(Markov_IO::Key k);


    Markov_CommandManager();
    virtual ~Markov_CommandManager();

    std::string buildVersion()const;
    std::string buildDate()const;
    std::string uncommitedFiles()const;

    virtual std::string version()const;
    virtual std::string wellcomeMessage(unsigned ncols=80)const;



    virtual bool next_instruction();
    virtual void clear_tokens();

    virtual void add_tokens(std::string commandLine);

    //  virtual void add_tokens(Markov_IO::Token_Buffer&& buffer);


    virtual std::string add_single_token(const std::string &command);

    virtual std::string check_tokens();


    //      virtual bool check_tokens(const Markov_IO::Token_Buffer &b, std::string candidate, std::string *errMessage);


    virtual std::string try_world(Markov_Console::ExpressionManager& exp){}


    virtual std::vector<std::string> complete(Markov_Console::ExpressionManager& exp){}



    virtual std::vector<std::string> complete(const std::string& hint);

    virtual std::vector<std::string> complete(const std::string &hint, const std::string& category);

    virtual bool runLine(std::string commandLine);

    //virtual std::map<std::string, ABC_Command*>& getCommands() {return cmds;}

    virtual Markov_IO::ABC_Saveable* getVar(const std::string& varName);
    virtual const Markov_IO::ABC_Saveable* getType(const std::string& varName)const;

    virtual bool getVar(const std::string& varName,Markov_IO::ABC_Saveable*& varType);

    virtual bool getVarCopy(const std::string& varName,Markov_IO::ABC_Saveable*& varType)const;

    virtual std::vector<std::string> getVarsList();
    virtual std::vector<std::string> getVarsList(Markov_IO::ABC_Saveable* varType)const;
    virtual std::vector<std::string> getVarsList(std::string className)const
    {
      std::vector<std::string> list;
      auto l=getListComplying(className);
      for (std::string el:l)
        {
          if (idToValue(el,className)!=nullptr)
            {
              list.push_back(el);
            }
        }
      return list;
    }

    virtual std::vector<std::string> getTypesList();



    virtual void printErrorMessage(const std::string& errorMessage, ABC_Command*);



    virtual std::string  getDir()const {return dir_;}
    virtual bool setDir(const std::string& dir);

    virtual Markov_IO::ABC_IO* getIO()const {return io_;}
    virtual void setIO(Markov_IO::ABC_IO* io){io_=io;}


    virtual CommandHistory& getH(){return h;}

    virtual void add_command(ABC_Command* cmd);
    virtual void add_type(const std::string& name, const Markov_IO::ABC_Saveable *s);

    virtual void add_var(std::string name, Markov_IO::ABC_Saveable* s);




    virtual void erase_tokens(int n);

    virtual  bool edit(const std::string& varname);
    virtual  bool edit(Markov_IO::ClassDescription& varname);




    virtual  bool checkVariable(std::string var, std::string superClass) const;

    virtual std::vector<std::string> getSiblings(std::string name) const;
    virtual std::vector<std::string> getVarSiblings(std::string name) const;


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

    static bool isMacroFile(const std::string& path);
    static Autocomplete LoadFiles(const std::string& dir);
    static std::size_t getVersion(const std::string& line);

    static std::string getHelpDir();


  protected:
    Markov_IO::ABC_IO* io_;

    ExpressionManager* e;

    std::string dir_;

    std::map<std::string, ABC_Command*> cmds;

    std::map<std::string, Markov_IO::ABC_Value*> classTypes;


    Autocomplete cmdsl;


    std::map<std::string, Markov_IO::ABC_Saveable*> vars;



    std::map<std::string, std::map<std::string, Markov_IO::ABC_Saveable*> > varByType;

    Autocomplete varsl;


    std::map<std::string, const Markov_IO::ABC_Saveable*>  types;
    Autocomplete typesl;
    Autocomplete supertypesl;
    Autocomplete filesl;



    std::map<std::string, const Markov_IO::ABC_Object*>  regulartypes;


    std::map<std::string, std::vector<std::string> > childs;

    std::map<std::string, std::string > parent;

    std::map<std::string,Autocomplete> autoCmptBySuperClass;

    std::map<std::string,Autocomplete> autoCmptByClass;


    std::map<std::string,Autocomplete> autoCmptByKind;


    std::deque<Token> tokens;

    bool lastCmdRst;

    CommandHistory h;

    virtual void Loadcommands();
    virtual void LoadTypes();


    // ABC_Environment interface
  public:
    virtual void putOut(const std::string &m) const
    {
      getIO()->put(m);
    }
    virtual void putErrorOut(const std::string &m) const
    {
      getIO()->putError(m);
    }

    virtual ABC_Command *getCommand(const Markov_IO::Token_New &t);
    Markov_IO::ABC_Value *getClass(std::string name);
  };

}

#endif // MARKOV_COMMANDMANAGER_H
