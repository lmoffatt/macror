#ifndef MARKOV_COMMANDMANAGER_H
#define MARKOV_COMMANDMANAGER_H


#include "Markov_IO/Implements_ComplexVar_New.h"

#include "Markov_IO/ABC_IO.h"

#include <random>




namespace Markov_IO_New
{
  class ExpressionManager;
  class CommandHistory;

  class ProgramVersion:public StructureEnv_New
    {
  public:
    virtual ~ProgramVersion(){}
    ProgramVersion()
   //     Markov_IO::Implements_ValueId("Program_Environment","","environment at file creation","")
   //   ,
    //    StructureEnv_New(nullptr,"Program_Environment","","environment at file creation","")
      {
//        push_backVal("Program",programName());
//        push_backVal("ver",programVer());
//        push_backVal("buildHash",buildVersion());
//        push_backVal("buildDate",buildDate());
//        push_backVal("UncommitedFiles",uncommitedFiles());
      }

      static std::string programName(){ return "MacroConsole";}

      static std::string programVer(){ return "0.2";}

      static std::string buildVersion();
      static std::string buildDate();
      static std::string uncommitedFiles();

      static std::string mySpacer(){return ">>";}

      virtual std::string version()const{return programVer();}
      virtual std::string wellcomeMessage(unsigned ncols=80)const;



      virtual std::string spacer()const{return mySpacer();}

  };

  

  /**
  @brief Markov_CommandManager manages the commands
  to be executed, keep the declared variables and
  allow to make runs.

  @warning declared variables in MacroR languaje can't be redeclared.
  */



  class Markov_CommandManagerVar: public StructureEnv_New
  {
  public:

   //  bool processTokens(Markov_IO::Token_Stream &t) override;

     void KeyEvent(Key k);

     static std::string ClassName(){return "Markov_CommandManagerVar";}

    Markov_CommandManagerVar();
    virtual ~Markov_CommandManagerVar()
    {

    }

    virtual ABC_IO* getIO()const {return io_;}
    virtual void setIO(ABC_IO* io){io_=io;}

    virtual CommandHistory& getH();

    const Implements_Data_Type_New<Implements_Var>* getVarType()
    {
      return vt_;
    }

    const Implements_Closure_Type<void*>* getFnType()
    {
      return ct_;
    }


    const Implements_Data_Type_New<std::string>* getIdCmd()
    {
      return idCmd_;
    }

    ProgramVersion &getProgram()
    {
      return program_ver_;
    }


    typedef  Implements_Data_Type_New<StructureEnv_New* > vType;




    void run(const Implements_Command_Arguments* arg);

    std::string getDir() const;

    bool setDir(const std::string &dir);


    template<class Type>
    void pushFunction()
    {
      StructureEnv_New::pushFunction(Type::myId()
                  ,Type::functionType(this)
                  ,Type::myTip()
                  ,Type::myWhatThis());
    }

   std::mt19937_64& sto()
   {
     return sto_;
   }


  protected:
    ABC_IO* io_;
    Implements_Data_Type_New<Implements_Var>* vt_;
    Implements_Closure_Type<void*>* ct_;

    Implements_Identifier* idCmd_;
    ExpressionManager* e;
    bool lastCmdRst;
    ProgramVersion program_ver_;
    CommandHistory* h_;
    std::mt19937_64 sto_;

  };


  template <typename T>
  const Implements_Value_New<T>*
  cm_idToValued(const Markov_CommandManagerVar *cm
                , const std::string& id
                , const std::string & typeId)
  {
    return cm->idToValued<T>(id,typeId);
  }

  template <typename T>
  const Implements_Data_Type_New<T> *cm_resultType(const ABC_R_Closure<T> *cl, const Markov_CommandManagerVar *cm)
  {
    return cl->resultType(cm);
  }
  template <typename T>
   Implements_Value_New<T>*
  cm_idToValued( Markov_CommandManagerVar *cm
                , const std::string& id
                , const std::string & typeId)
  {
    return cm->idToValued<T>(id,typeId);
  }

  template<typename T>
  bool cm_getDataFromId(const Markov_CommandManagerVar* cm
                        ,const std::string& idname, T& x)
  {
    return cm->getDataFromId(idname,x);
  }


}



#endif // MARKOV_COMMANDMANAGER_H
