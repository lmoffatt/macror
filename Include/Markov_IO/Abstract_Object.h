#ifndef ABSTRACT_OBJECT_H
#define ABSTRACT_OBJECT_H
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include "Markov_LA/Matrix.h"





namespace Markov_IO
{

  class Environment;

  class Abstract_Object
  {
  public:

    static std::string ClassName();
    virtual std::string myClass()const=0;
    virtual std::set<std::string> mySuperClasses()const;
    virtual std::string idName()const=0;

    /// hint about of the class nature
    virtual std::string Tip()const=0;

    /// a short description of the class
    virtual std::string WhatThis()const=0;
    virtual Environment* getEnvironment()const =0;


    virtual void setTip(const std::string& newTip)=0;

    virtual void setWhatThis(const std::string& whatthis)=0;


    virtual std::string ToString()const=0;
    virtual bool IsObject(const std::string& singleLine)const=0;
    virtual bool ToObject(const std::string& text, std::size_t &cursor)=0;
    virtual std::size_t numFields()const=0;

    Abstract_Object();
    virtual ~Abstract_Object();


    virtual bool isClonable()const=0;
    virtual bool isCreateable()const=0;
    virtual Abstract_Object* clone()const=0;
    virtual Abstract_Object* create()const=0;

 //   virtual Abstract_Object* parent()=0;
 //   virtual std::vector<Abstract_Object*> childs()=0;

 //   virtual std::vector<Abstract_Object*> clients()=0;



  };


  class A_Named_Object:public virtual Abstract_Object
  {
  public:

    static std::string getName(const std::string& multiplelines, std::size_t& pos);
    static std::string getTip(const std::string& multiplelines, std::size_t& pos);
    static std::string getWhatThis(const std::string& multiplelines,std::size_t& pos);

    static std::string nextLine(const std::string& lines,std::size_t& n);

    static std::string removeInitialSpaces(const std::string& line);

    static std::string ClassName();
    virtual std::string myClass()const override;
    virtual std::set<std::string> mySuperClasses()const;
    virtual std::string idName()const override;

    /// hint about of the class nature
    virtual std::string Tip()const override;

    /// a short description of the class
    virtual std::string WhatThis()const override;
    virtual Environment* getEnvironment() const override;


    virtual void setTip(const std::string& newTip) override;

    virtual void setWhatThis(const std::string &whatthis) override;


    virtual std::string ToString()const override;
    virtual bool ToObject(const std::string& text, std::size_t &cursor)  override;
    virtual std::size_t numFields()const override;



    virtual ~A_Named_Object();
    A_Named_Object(Environment* e,
                    std::string variablename,
                    std::string tip,
                    std::string whatthis);

  private:

    Environment* e_;
    std::string variableName_;
    std::string tip_;
    std::string whatThis_;

  };


  class Base_Unit:public virtual A_Named_Object
  {
  public:
    static std::string getUnit(const std::string& singleLine);
    static std::string ClassName();

    virtual std::string myClass()const;

    virtual std::string abbr()const;

    virtual std::string ToString()const;
    virtual bool ToObject(const std::string& multipleLines,std::size_t& pos);
    virtual bool IsObject(const std::string& singleLine)const override;

    virtual bool isClonable()const;
    virtual bool isCreateable()const;
    virtual Abstract_Object* clone()const;
    virtual Abstract_Object* create()const;



    Base_Unit(std::string abbreviation,
              std::string name,
              Environment* e,
              std::string tip,
              std::string whatthis);

  private:

    std::string abbr_;
  };



  class Valued_Object:public virtual Abstract_Object
  {
  public:
    static std::string ClassName();
    virtual std::string myClass()const override;
    virtual std::set<std::string> mySuperClasses()const override;

    virtual const Base_Unit* myUnit()const=0;
    virtual ~Valued_Object();

  };

  class Value_Object;


  class Variable_Object: public virtual Abstract_Object
  {
  public:

    static std::string ClassName();
    virtual std::string myClass()const override;
    virtual std::set<std::string> mySuperClasses()const override;
    virtual ~Variable_Object();


    virtual bool isClonable()const;
    virtual Variable_Object* clone()const;

    virtual Value_Object* defaultSample()const=0;

  };


  class Value_Object: public virtual Abstract_Object
  {
  public:
    static std::string ClassName();

    virtual std::string myClass()const override;
    virtual std::set<std::string> mySuperClasses()const override;
    virtual ~Value_Object();

    virtual bool isClonable()const;
    virtual bool isCreateable()const;
    virtual Value_Object* create()const;

    virtual const Variable_Object* variable()const=0;

  };





  template<typename T>
  class SimpleVariableValue;

  template<typename T>
  class SimpleVariable: public Variable_Object,public Valued_Object,public A_Named_Object
  {
  public:

    static std::string ClassName();
    virtual std::string myClass()const override;
    virtual std::set<std::string> mySuperClasses()const override;
    virtual SimpleVariable<T>* clone() const{}

    virtual const Base_Unit* myUnit()const ;

    virtual std::string ToString()const override;
    virtual bool ToObject(const std::string& multipleLines,std::size_t& pos) override;
    virtual bool IsObject(const std::string& singleLine)const override;

    virtual SimpleVariableValue<T>* defaultSample()const override;


    virtual bool isCreateable()const;
    virtual SimpleVariable<T>* create()const;





    SimpleVariable(std::string name,
                   T defaultValue,
                   std::string unit,
                   Environment *e,
                   std::string tip,
                   std::string whatthis);
    ~SimpleVariable();
  private:
    T defautValue_;
    const Base_Unit* u_;
  };


  template<typename T>
  class SimpleVariableValue: public Value_Object,public Valued_Object, public A_Named_Object
  {
  public:

    static T get(const std::string &singleLine);
    static bool is(const std::string& singleLine);

    virtual std::string myClass()const override;

    static std::string ClassName();
    virtual std::set<std::string> mySuperClasses()const override;

    virtual const Base_Unit* myUnit()const override;

    virtual const SimpleVariable<T>* variable()const override;

    virtual T value() const;

    virtual std::string ToString()const override;
    virtual bool ToObject(const std::string& multipleLines,std::size_t& pos)override;
    virtual bool IsObject(const std::string& singleLine)const override;


    virtual SimpleVariableValue<T>* clone()const;

    SimpleVariableValue(std::string variablename,
                        T defaultValue,
                        std::string unit,
                        Environment *e,
                        std::string name,
                        std::string tip,
                        std::string whatthis);
    ~SimpleVariableValue();

  private:
    const SimpleVariable<T>* variable_;
    const Base_Unit* unit_;
    T value_;
  };




  class Complex_Object:public A_Named_Object

  {
  public:
    virtual std::string beginLine()const;
    virtual std::string endLine()const;
    static std::string beginLabel();
    static std::string endLabel();
    static std::string getClassName(const std::string& singleLine);
    static std::string getFieldName(const std::string& singleLine);

    static std::string ClassName();
    virtual std::string myClass()const override;
    virtual std::set<std::string> mySuperClasses()const override;

    virtual std::size_t numFields()const override;

    virtual std::string fieldName(std::size_t i)const;

    virtual Abstract_Object const * fieldVariable(const std::string& fieldname)const;

    virtual Abstract_Object  * fieldVariable(const std::string& fieldname);


    virtual bool hasField(const std::string& fieldN)const;


    virtual bool setField(const std::string& fieldN,Abstract_Object*  o);


    virtual bool push_back(const std::string &fieldname,
                           Abstract_Object* object);


    virtual std::string ToString()const override;
    virtual bool ToObject(const std::string& multipleLines,std::size_t& pos) override;
    virtual bool IsObject(const std::string& singleLine) const override;



    Complex_Object(Environment* e,
                     std::string name,
                     std::string tip,
                     std::string whatthis);

    ~Complex_Object();

  private:
    std::vector<std::string> fieldNames_;
    std::map<std::string,Abstract_Object*> fieldVariables_;
  };


  class Complex_Variable;
  class Complex_Variable_Value:public Value_Object,public Complex_Object
  {
  public:
    static std::string ClassName();
    virtual std::string myClass()const override;
    virtual std::set<std::string> mySuperClasses()const override;

    virtual Value_Object const * fieldVariable(const std::string& fieldname)const;
    virtual Value_Object * fieldVariable(const std::string& fieldname);

    virtual bool setField(const std::string& fieldN,Value_Object*  o);
    virtual bool push_back(const std::string &fieldname,
                           Value_Object *object);

    virtual const Variable_Object* variable()const override;


    virtual Complex_Variable_Value* clone()const override{}


    Complex_Variable_Value(Environment* e,
                     std::string name,
                     std::string tip,
                     std::string whatthis,
                          std::string complexvar);

    ~Complex_Variable_Value();

  private:
    const Complex_Variable* cmplxvar_;
  };


  class Complex_Variable:public Variable_Object, public Complex_Object
  {
  public:

    static std::string ClassName();
    virtual std::string myClass()const override;
    virtual std::set<std::string> mySuperClasses()const override;


    virtual Variable_Object const * fieldVariable(const std::string& fieldname)const;

    virtual Variable_Object  * fieldVariable(const std::string& fieldname);


   virtual bool setField(const std::string& fieldN,Variable_Object*  o);


    virtual bool push_back(const std::string &fieldname,
                           Variable_Object* object);


    virtual Complex_Variable_Value* defaultSample()const override;

    virtual Complex_Variable* create() const {}
    virtual bool isCreateable()const {return false;}


    Complex_Variable(Environment* e,
                     std::string name,
                     std::string tip,
                     std::string whatthis);

    ~Complex_Variable();
};






class Environment
{
public:
  const Base_Unit* U(const std::string& unitNameorAbreviation)const
  {
    auto it=units_.find(unitNameorAbreviation);
    if (it!=units_.end())
      return it->second;
    else return nullptr;
  }
  const Variable_Object* V(const std::string& variablename,const std::string& variabletype)const
  {
    auto it=variables_.find(variablename);
    if (it!=variables_.end())
      {
        Variable_Object* v=it->second;
        if (v->mySuperClasses().find(variabletype)!=v->mySuperClasses().end())
          return v;
      }
    return nullptr;
  }

  void addUnit(Base_Unit* u)
  {
    units_[u->abbr()]=u;
  }

  void addVariable(Variable_Object* v)
  {
    variables_[v->idName()]=v;
  }

private:
  std::map<std::string,Base_Unit*> units_;
  std::map<std::string,Variable_Object*> variables_;

};




}












#endif // ABSTRACT_OBJECT_H
