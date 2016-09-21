#ifndef STRUCTUREENV_H
#define STRUCTUREENV_H

#include "Markov_IO/Var.h"
#include "Markov_IO/buildByToken.h"

#include "Markov_IO/Closure_type.h"
#include "Markov_LA/matrixSum.h"

//#include "Markov_IO/Implements_function.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <tuple>
#include <type_traits>

namespace Markov_IO_New {

  class ABC_interfase
  {
  public:
    virtual void setSpacer(char sp)=0;
    virtual char getSpacer()const=0;
    virtual ~ABC_interfase(){} ;
  };

  class ABC_Output:public ABC_interfase
  {
  public:
    template<typename T>
    void put(const T& x, std::string* error)
    {
      *error=Cls<T>::name()+ "is not supported";
    }

    virtual void put(const std::string& s)=0;
    virtual void put(double x)=0;
    virtual void put(int n)=0;
    virtual void put(std::size_t n)=0;
    virtual void put(char c)=0;



    virtual ~ABC_Output(){}
  };

  class ABC_Input: public ABC_interfase
  {
  public:
    virtual bool getLine(std::string& line,std::string* whyNot,const std::string& masterObjective)=0;

    virtual  bool get( std::string& s,std::string* whyNot,const std::string& masterObjective)=0;
    virtual  bool get(double& x,std::string* whyNot,const std::string& masterObjective)=0;
    virtual  bool get(int& n,std::string* whyNot,const std::string& masterObjective)=0;
    virtual  bool get(std::size_t& n,std::string* whyNot,const std::string& masterObjective)=0;
    virtual  bool get(char& c,std::string* whyNot,const std::string& masterObjective)=0;
    virtual  bool get(char& c)=0;
    virtual bool nextCharIs(char c,char& found)=0;

    virtual bool nextCharIs(char c,bool advanceInFailure)=0;

    virtual bool testIfNextCharIs(char c)=0;

    virtual bool eof()const=0;
    virtual ~ABC_Input(){}
  };



  class StringInput: public ABC_Input
  {
  public:
    virtual bool getLine(std::string& line,std::string* whyNot,const std::string& masterObjective) override
    {
      std::getline(ss_,line);
      return ss_.good();
    }

    virtual  bool get( std::string& s,std::string* whyNot,const std::string& masterObjective) override {
      ss_>>s;
      return ss_.good();
    }
    virtual  bool get(double& x,std::string* whyNot,const std::string& masterObjective) override {
      ss_>>x;
      return ss_.good();
    }
    virtual  bool get(int& n,std::string* whyNot,const std::string& masterObjective) override {
      ss_>>n;
      return ss_.good();
    }
    virtual  bool get(std::size_t& n,std::string* whyNot,const std::string& masterObjective) override {
      ss_>>n;
      return ss_.good();
    }
    virtual bool get(char &c, std::string *whyNot, const std::string &masterObjective) override
    {
      ss_.get(c);
      return ss_.good();
    }
    virtual bool get(char &c) override
    {
      ss_.get(c);
      return ss_.good();

    }

    virtual bool nextCharIs(char c, char &found) override
    {

      ss_.get(found);
      while (found==' ') {ss_.get(found);}
      return found==c;
    }
    virtual bool nextCharIs(char c, bool advanceInFailure) override
    {
      char d;
      ss_.get(d);
      while (d==' ') {ss_.get(d);}
      if (d==c)
        return true;
      else if (!advanceInFailure)
        ss_.putback(d);
      return false;
    }
    virtual bool testIfNextCharIs(char c) override
    {
      char d;
      ss_.get(d);
      while (d==' ') {ss_.get(d);}
      ss_.putback(d);
      return  d==c;
    }


    virtual bool eof()const override
    {
      return ss_.eof();
    }
    virtual ~StringInput(){}


    StringInput(const std::string & s, char spacer=' ')
      : spacer_(spacer),ss_(s){}
    void setSpacer(char c)override{spacer_=c;}
    char  getSpacer()const override {return spacer_;}

  private:
    char spacer_;
    std::istringstream ss_;


  };


  class StringOutput:public ABC_Output  {
  public:
    template<typename T>
    void put(const T& x, std::string* error)
    {
      *error=Cls<T>::name()+ "is not supported";
    }

    virtual void put(const std::string& s) override
    {
      ss_<<s<<getSpacer();
    }

    virtual void put(double x) override
    {
      ss_<<x<<getSpacer();
    }

    virtual void put(int n)
    {
      ss_<<n<<getSpacer();
    }

    virtual void put(std::size_t n)
    {
      ss_<<n<<getSpacer();
    }

    virtual void put(char c)
    {
      ss_.put(c);
    }



    virtual ~StringOutput(){}
    StringOutput(char spacer=' ')
      : spacer_(spacer),ss_(){}

    std::string getString(){return ss_.str();}
    void setSpacer(char c)override{spacer_=c;}
    char  getSpacer()const override {return spacer_;}

  private:
    char spacer_;
    std::ostringstream ss_;
  };


  class Implements_Command_Type_New;



  class StructureEnv_New: public ABC_Data_New
  {
    // ABC_Value_New interface
  public:
    static std::string ClassName(){return "StructureEnv_New";}

    // no me queda claro
    StructureEnv_New(const StructureEnv_New& other)=default;

    virtual bool empty() const override {return idUsed_.empty();}

    virtual void reset() override;
    virtual ABC_Type_of_Value const* myType() const override;
    virtual Implements_Data_Type_New<StructureEnv_New*>  const* myTypeD() const {return strType_;}

    virtual std::string myTypeId()const override;

  public:

    const StructureEnv_New* parent()const;

    const ABC_Data_New* idToValue
    (const std::string& name
     , const std::string & typeName
     ,std::string* whyNot=nullptr, const std::string& masterObjective="")const;


    virtual bool isOfThisType(const StructureEnv_New* cm,
                              const std::string& generalType,
                              std::string* whyNot
                              ,const std::string &masterObjective)const override;


    std::vector<std::string> loadVars(StructureEnv_New other, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective, bool overwrite);

    ABC_Data_New* idToValue
    (const std::string& name
     , const std::string & typeName
     ,std::string* whyNot=nullptr, const std::string& masterObjective="");


    
    template <typename T>
    Implements_Value_New<T>*
    idToValued (const std::string& name
                , const std::string & typeName
                ,std::string* whyNot=nullptr, const std::string& masterObjective="")
    {
      return dynamic_cast<Implements_Value_New<T>*>(idToValue(name,typeName,whyNot,masterObjective));
    }

    
    
    const_Implements_Var idToVar
    (const std::string& name
     , const std::string & typeName=""
        ,std::string* whyNot=nullptr, const std::string& masterObjective="")const;


    Implements_Var idToVar
    (const std::string& name
     , const std::string & typeName=""
        ,std::string* whyNot=nullptr, const std::string& masterObjective="");


    const ABC_Data_New* idToValue(const std::string& name, std::string *whyNot=nullptr)const;

    ABC_Data_New* idToValue(const std::string& name, std::string* whyNot=nullptr, const std::string & masterObective="");

    virtual const ABC_Type_of_Value* idToType(const std::string& name, std::string *whyNot=nullptr, const std::string& masterObjective="")const;

    virtual ABC_Type_of_Value* idToType(const std::string& name, std::string *whyNot=nullptr,const std::string& masterObjective="");

    template<typename T>
    bool getDataFromId(const std::string& idname, T& x)const
    {
      ABC_Data_New* d=idToValue(idname)->clone();
      if (d!=nullptr)
        {
          auto o=dynamic_cast< Implements_Value_New<T>*>(d);
          if (o!=nullptr)
            {
              x=o->getValue();
              return true;
            }
          else return false;
        }
      else return false;
    }


    const Implements_Command_Type_New* idToCommand(const std::string& name, std::string *whyNot, const std::string& masterobjective)const;

    template<typename T>
    const Implements_Data_Type_New<T>* idToTyped(
        const std::string& name
        , std::string *whyNot=nullptr
        , const std::string& masterObjective="")const
    {
      const std::string objective
          =masterObjective
          +": "+name+ "is not a "+ Cls<T>::name();
      auto it=types_.find(name);
      if (it!=types_.end())
        {
          return dynamic_cast<Implements_Data_Type_New<T>*>(
                it->second);
        }
      else if (parent()!=nullptr)
        return  parent()->idToTyped<T>(name, whyNot,objective);
      else
        {   if (whyNot!=nullptr)
            *whyNot=objective+": name not found in type list";
          return nullptr;
        }

    }




    template<typename T>
    const Implements_Closure_Type<T>* idToTypeC(
        const std::string& name
        , std::string *whyNot=nullptr
        , const std::string& masterObjective="")const
    {
      const std::string objective
          =masterObjective
          +": "+name+ "is not a "+ Cls<T>::name();
      auto it=typeC_.find(name);
      if (it!=typeC_.end())
        {
          return dynamic_cast<Implements_Closure_Type<T>*>(it->second);
        }
      else if (parent()!=nullptr)
        return  parent()->idToTypeC<T>(name, whyNot,objective);
      else
        {   if (whyNot!=nullptr)
            *whyNot=objective+": name not found in type list";
          return nullptr;
        }

    }





    template<typename T>
    bool getValueFromId(const std::string& name
                        , T& value
                        ,std::string* whyNot=nullptr, const std::string& masterObjective="")const
    {

      std::string objective;
      if (whyNot!=nullptr)
        objective=masterObjective+": "+ name+" is not a "+Cls<T>::name();

      auto it=vars_.find(name);
      const ABC_Data_New* var=it->second;
      if (it!=vars_.end())
        {
          auto v=dynamic_cast<
              const Implements_Value_New<T>*>(var);
          if (v==nullptr)
            {
              return false;
            }
          else if (v->empty())
            {
              if (whyNot!=nullptr)
                *whyNot=objective+": varType not found";
              return false;
            }
          else
            {
              value=v->getValue();
              return true;
            }
        }

      else if (parent()!=nullptr)
        return  parent()->getValueFromId(name,value,whyNot,objective);
      else
        {
          if (whyNot!=nullptr)
            *whyNot=objective+": does not have it and it has no parent";
          return false;
        }
    }



    template<typename T>
    bool getValueFromId(const std::string& name
                        , T*& value
                        ,std::string* whyNot=nullptr, const std::string& masterObjective="")const
    {

      std::string objective;
      if (whyNot!=nullptr)
        objective=masterObjective+": "+ name+" is not a "+Cls<T*>::name();

      auto it=vars_.find(name);
      const ABC_Data_New* var=it->second;
      if (it!=vars_.end())
        {
          auto v=dynamic_cast<
              const Implements_Value_New<T*>*>(var);
          if (v==nullptr)
            {
              return false;
            }
          else if (v->empty())
            {
              if (whyNot!=nullptr)
                *whyNot=objective+": varType not found";
              return false;
            }
          else
            {
              value=cloneThis(v->getValue());
              return true;
            }
        }

      else if (parent()!=nullptr)
        return  parent()->getValueFromId(name,value,whyNot,objective);
      else
        {
          if (whyNot!=nullptr)
            *whyNot=objective+": does not have it and it has no parent";
          return false;
        }
    }



    template<typename T>
    bool setValueToId(const std::string& name
                      ,const T& value
                      ,std::string* whyNot=nullptr, const std::string& masterObjective="")
    {

      std::string objective;
      if (whyNot!=nullptr)
        objective=masterObjective+": "+ name+" is not a "+Cls<T>::name();

      auto it=vars_.find(name);
      ABC_Data_New* var=it->second;
      if (it!=vars_.end())
        {
          auto v=dynamic_cast<
              Implements_Value_New<T>*>(var);
          if (v==nullptr)
            {
              return false;
            }
          else if (v->empty())
            {
              if (whyNot!=nullptr)
                *whyNot=objective+": varType not found";
              return false;
            }
          else
            {
              v->getValue()=value;
              return true;
            }
        }

      else
        {
          if (whyNot!=nullptr)
            *whyNot=objective+": does not have it and it has no parent";
          return false;
        }
    }






    bool hasName(const std::string& name
                 , std::string* whyNot
                 ,const std::string &masterObjective,
                 bool recursive)const;



    bool hasNameofType(const std::string& name, const std::string& type,
                       bool recursive,
                       std::string* whyNot=nullptr
        , const std::string &masterObjective="")const;





    bool hasTypeofType(const std::string& name, const std::string& type,
                       std::string* whyNot
                       , const std::string &masterObjective, bool recursive)const;



    bool isNameUnOcuppied(const std::string& name,std::string* whyNot,const std::string &masterObjective, bool recursive)const;


    bool hasType(const std::string& name
                 , std::string* whyNot=nullptr
        ,const std::string &masterObjective="",
                 bool recursive=false)const;



    bool hasCommand(const std::string& name,   std::string* whyNot
                    ,const std::string &masterObjective,
                    bool recursive)const;



    void pushVar(Implements_Var v)
    {
      pushVar(v.id,v.data,v.Tip,v.WhatThis);
    }

    Implements_Var popVar();


    void pushVar(const std::string& id
                 ,ABC_Data_New* var
                 , std::string tip
                 , std::string whatthis);


    template<class Field>
    void pushVar(typename Field::myC val={}
        , const std::string myId=Field::myId()
        , const std::string& myTip=Field::myTip()
        , const std::string& myWhatThis=Field::myWhatThis()  )
    {
      if (myClassOf(val)==Cls<typename Field::myC>::name())

        pushVar(myId
                ,new Implements_Value_New<typename Field::myC>
                (idToTyped<typename Field::myC>(Field::myIdType()),val)
                ,myTip,myWhatThis);
      else
        pushVar(myId
                ,new Implements_Value_New<typename Field::myC>
                (idToTyped<typename Field::myC>(myClassOf(val)),val)
                ,myTip,myWhatThis);


    }

    template<class T>
    void pushData(const std::string& myId, T x, const std::string& myTip="", const std::string& myWhatThis="")
    {
      pushVar(myId
              ,new Implements_Value_New<T>
              (idToTyped<T>(Cls<T>::name()),x)
              ,myTip,myWhatThis);
    }



    template<class Field>
    bool getDataValue(typename Field::myC &val,std::string* whyNot=nullptr,const std::string &masterObjective="")const
    {
      return getValueFromId(Field::myId(),val,whyNot,masterObjective);
    }

    template<class Field>
    typename Field::myC getDataValueS(std::string* whyNot=nullptr,const std::string &masterObjective="")const
    {
      typename Field::myC val;
      getValueFromId(Field::myId(),val,whyNot,masterObjective);
      return val;
    }




    template<class Field>
    bool setDataValue(const typename Field::myC &val,std::string* whyNot=nullptr,const std::string &masterObjective="")
    {
      return setValueToId<typename Field::myC>
          (Field::myId(),val,whyNot,masterObjective);
    }









    template <typename T>
    void pushType(const std::string& id
                  ,Implements_Data_Type_New<T>* var
                  , std::string tip
                  , std::string whatthis);



    template<class Type>
    void pushType(const std::string& name)
    {
      if (!hasType(Type::myId(name)))
        pushType(Type::myId(name)
                 ,Type::varType(name)
                 ,Type::myTip(),Type::myWhatThis());
    }






    template<class Type>
    void pushType()
    {
      if (!hasType(Type::myId()))
        pushType<typename Type::myC>(Type::myId()
                 ,Type::varType()
                 ,Type::myTip()
                 ,Type::myWhatThis());
    }

    template<class T>
    void pushRegularType()
    {
      if (!hasType(Cls<T>::name()))
        pushType<T>(Cls<T>::name()
                 , new Implements_Data_Type_New<T>(),"a "+Cls<T>::name(),"");
    }

    void pushVoidType();



    void pushCommand(const std::string& id
                     ,Implements_Command_Type_New* var
                     , std::string tip
                     , std::string whatthis);


    template<class Type>
    void pushCommand()
    {
      pushCommand(Type::myId()
                  ,Type::cmdType(this)
                  ,Type::myTip()
                  ,Type::myWhatThis());
    }

    void pushFunction(const std::__cxx11::string &id
                      , Implements_Closure_Type<void*> *tvar
                      , std::__cxx11::string tip
                      , std::__cxx11::string whatthis);


    StructureEnv_New(const StructureEnv_New* parent, const Implements_Data_Type_New<StructureEnv_New *> *myType);

    StructureEnv_New(const StructureEnv_New* parent, const std::string& idType);


    StructureEnv_New(): StructureEnv_New(nullptr,nullptr){};


    std::vector<std::__cxx11::string> getIdsOfVarType(const std::string& varType, bool recursive)const;





    // Implements_Value_New interface

    std::set<std::string> getIdsOfTypeType(const std::string &typeType, bool recursive) const;
    std::string defaultIdOfVarType(const std::string &varType, bool recursive) const;
    std::string defaultIdOfTypeType(const std::string &typeType, bool recursive) const;
    std::string defaultIdOfCommand(const std::string &typeType, bool recursive) const;


    std::string defaultIdOfCmdType(const std::string &cmdType, bool recursive) const;
    std::set<std::string> getIdsOfCmdType(const std::string &cmdType, bool recursive) const;

    friend class buildByToken<std::map<std::string, ABC_Data_New *> >;


    std::map<std::string,ABC_Data_New*>& getVars();
    const std::map<std::string,ABC_Data_New*>& getVars()const;
    std::map<std::string,ABC_Type_of_Value*>& getTypes();
    const std::map<std::string,ABC_Type_of_Value*>& getTypes()const;
    std::map<std::string,Implements_Command_Type_New*>& getCommands();
    const std::map<std::string,Implements_Command_Type_New*>& getCommands()const;


  virtual StructureEnv_New *clone() const override
    {
      return new StructureEnv_New(*this);
    }
    virtual ABC_Data_New *create() const override
    {
      return new StructureEnv_New(p_,strType_);
    }


    std::string Tip(const std::string& id)const ;
    std::string WhatThis(const std::string& id) const;


    std::size_t numIdVars()const {return idVars_.size();}
    std::size_t numIdTypes()const {return idTypes_.size();}






    Implements_Closure_Type<void*> *idToFunc(const std::__cxx11::string &name, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective);

    const Implements_Closure_Type<void *> *idToFunc(const std::__cxx11::string &name, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) const;

    template<typename R>
    const Implements_Closure_Type<R,void *> *idTo_R_Func
    (const std::__cxx11::string &name,const std::string &typeName
     ,std::__cxx11::string *whyNot=nullptr, const std::__cxx11::string &masterObjective="") const;


    bool hasFunction(const std::__cxx11::string &name, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective, bool recursive) const;


    std::map<std::__cxx11::string, Implements_Closure_Type<void*> *> &getFunctions();

    const std::map<std::__cxx11::string, Implements_Closure_Type<void*> *> &getFunctions() const;

    bool hasFunction_returningType(const std::string &name, const std::string &type, std::string *whyNot, const std::string &masterObjective, bool recursive) const;


    std::set<std::string> getIdsOfFncType(const std::string &fucnType, bool recursive) const;


  private:


    const StructureEnv_New* p_;
    Implements_Data_Type_New<StructureEnv_New*> const* strType_;
    std::string structType_;
    std::set<std::string> idUsed_;
    std::vector<std::string> idVars_;
    std::vector<std::string> idFunctions_;
    std::vector<std::string> idTypes_;

    std::map<std::string,ABC_Data_New*> vars_;
    std::map<std::string,ABC_Type_of_Value*> types_;
    std::map<std::string,ABC_Type_of_Closure*> typeC_;
    std::map<std::string,Implements_Closure_Type<void*>* > funcs_;
    std::map<std::string,std::map<std::string,ABC_Function_Overload*> > R_funcs_;

    std::map<std::string,std::map<std::string,ABC_Type_of_Method*>> methods_;


    std::map<std::string,std::pair<std::string,std::string>> idTipWt_;
 };



}


#endif // STRUCTUREENV_H
