#ifndef ABSTRACT_OBJECT_H
#define ABSTRACT_OBJECT_H

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>
//#include "Markov_LA/Matrix.h"



namespace Markov_Object
{
  class Environment;

  class Abstract_Object
  {
  public:
    static std::string ClassName();
    virtual std::string myClass()const=0;
    virtual std::set<std::string> mySuperClasses()const;
    virtual Environment* getEnvironment()const =0;
    virtual std::string ToString()const=0;

    virtual bool ToObject(Environment* e,const std::string& text, std::size_t &cursor)=0;



    virtual bool isCreateable()const=0;
    virtual bool isClonable()const=0;
    virtual Abstract_Object* copyTo(Environment* e)const=0;
    virtual Abstract_Object* create()const=0;

    virtual ~Abstract_Object();

  };



  class Named_Object:public virtual Abstract_Object
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
    virtual std::string idName()const ;

    /// hint about of the class nature
    virtual std::string Tip()const ;

    /// a short description of the class
    virtual std::string WhatThis()const ;
    virtual Environment* getEnvironment() const override;


    virtual void setTip(const std::string& newTip) ;

    virtual void setWhatThis(const std::string &whatthis) ;


    virtual std::string ToString()const override;
    virtual bool ToObject(Environment* e,const std::string& text, std::size_t &cursor)  override;
    virtual bool isClonable()const override { return false;}
    virtual Named_Object* copyTo(Environment* e)const override { return nullptr;}

    virtual bool isCreateable()const override { return true;}



    virtual ~Named_Object();
    Named_Object(Environment* e,
                 std::string variablename,
                 std::string tip,
                 std::string whatthis);

    Named_Object(Environment* e);

  protected:
    virtual void setEnvironment(Environment *e);



  private:

    Environment* e_;
    std::string variableName_;
    std::string tip_;
    std::string whatThis_;

  };


  class Base_Unit:public virtual Named_Object
  {
  public:
    static std::string getUnit(const std::string& singleLine);
    static std::string ClassName();

    virtual std::string myClass()const override;

    virtual std::string abbr()const;

    virtual std::string ToString()const;
    virtual bool ToObject(Environment* e,const std::string& multipleLines,std::size_t& pos);

    virtual bool isCreateable()const;

    virtual Abstract_Object* create()const;

    virtual std::size_t numFields()const{return 0;}



    Base_Unit(std::string abbreviation,
              std::string name,
              Environment* e,
              std::string tip,
              std::string whatthis);

    Base_Unit(Environment* e);



  private:

    std::string abbr_;
  };



  class Abstract_Valued_Object:public virtual Abstract_Object
  {
  public:
    static std::string ClassName();
    virtual std::string myClass()const ;
    virtual std::set<std::string> mySuperClasses()const ;

    virtual const Base_Unit* myUnit()const=0;
    virtual ~Abstract_Valued_Object();

  };

  class Abstract_Value_Object;


  class Abstract_Variable_Object: public Named_Object
  {
  public:

    static std::string ClassName();
    virtual std::string myClass()const override;
    virtual std::set<std::string> mySuperClasses()const override;
    virtual ~Abstract_Variable_Object();


    virtual Abstract_Variable_Object* create() const=0;


    virtual Abstract_Value_Object* defaultValue()const=0;

    Abstract_Variable_Object(Environment* e,
                             std::string variablename,
                             std::string tip,
                             std::string whatthis)
      :  Named_Object(e,variablename,tip,whatthis)
    {}

    Abstract_Variable_Object(Environment* e)
      :
        Named_Object(e){}
  };


  class Abstract_Value_Object: public  virtual Abstract_Object
  {
  public:
    static std::string ClassName();

    virtual std::string myClass()const override;
    virtual std::set<std::string> mySuperClasses()const override;
    virtual ~Abstract_Value_Object();

    virtual bool isClonable()const;
    virtual bool isCreateable()const;
    virtual Abstract_Value_Object* create()const;
    virtual Environment* getEnvironment() const override
    {
      return variable()->getEnvironment();
    }
    virtual const Abstract_Variable_Object* variable()const=0;
  };



  template<typename T>
  class SimpleVariableValue;

  template<typename T>
  class SimpleVariable: public Abstract_Variable_Object,public Abstract_Valued_Object
  {
  public:

    static std::string ClassName();
    virtual std::string myClass()const override;
    virtual std::set<std::string> mySuperClasses()const override;
    virtual const Base_Unit* myUnit()const ;

    virtual std::string ToString()const override;
    virtual bool ToObject(Environment* e,const std::string& multipleLines,std::size_t& pos) override;

    virtual SimpleVariableValue<T>* defaultValue()const override;


    virtual bool isCreateable()const;
    virtual SimpleVariable<T>* create()const;

    SimpleVariable(Environment *e);






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

    // Abstract_Object interface
  public:
    virtual std::size_t numFields() const
    {
      return 0;
    }
  };


  template<typename T>
  class SimpleVariableValue: public Abstract_Value_Object,public Abstract_Valued_Object
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
    virtual bool ToObject(Environment* e,const std::string& multipleLines,std::size_t& pos)override;


    virtual SimpleVariableValue<T>* copyTo(Environment* e)const;

    SimpleVariableValue(std::string variablename,
                        T defaultValue,
                        std::string unit,
                        Environment *e);
    ~SimpleVariableValue();

  private:
    const SimpleVariable<T>* variable_;
    const Base_Unit* unit_;
    T value_;

    // Abstract_Object interface
  };


  class FieldVariable: public Abstract_Variable_Object
  {
    // Abstract_Variable_Object interface
  public:
    virtual Abstract_Value_Object *defaultValue() const;

    virtual std::string ToString()const override;
    virtual bool ToObject(Environment* e,const std::string& multipleLines,std::size_t& pos) override;
    virtual Abstract_Variable_Object const * variable()const;

    virtual Abstract_Variable_Object  * variable();


    virtual bool setField(Abstract_Object*  o);


    FieldVariable(Environment* e,
                  Abstract_Variable_Object* var,
                  std::string name,
                  std::string tip,
                  std::string whatthis);

  private:
    Abstract_Variable_Object * var_;

  };



  //  class Complex_Object:public Abstract_Variable_Object

  //  {
  //  public:
  //    virtual std::string beginLine()const;
  //    virtual std::string endLine()const;
  //    static std::string beginLabel();
  //    static std::string endLabel();
  //    static std::string getClassName(const std::string& singleLine);
  //    static std::string getFieldName(const std::string& singleLine);

  //    static std::string ClassName();
  //    virtual std::string myClass()const override;
  //    virtual std::set<std::string> mySuperClasses()const override;

  //    virtual std::size_t numFields()const override;

  //    virtual std::string fieldName(std::size_t i)const;

  //    virtual FieldVariable const * fieldVariable(const std::string& fieldname)const;

  //    virtual FieldVariable  * fieldVariable(const std::string& fieldname);


  //    virtual bool hasField(const std::string& fieldN)const;




  //    virtual bool setField(const std::string& fieldN,Abstract_Object*  o);


  //    virtual bool push_back(const std::string &fieldname,
  //                           Abstract_Object* object);


  //    virtual std::string ToString()const override;
  //    virtual bool ToObject(Environment* e,const std::string& multipleLines,std::size_t& pos) override;
  //    virtual bool IsObject(const std::string& singleLine) const override;



  //    Complex_Object(Environment* e,
  //                   std::string name,
  //                   std::string tip,
  //                   std::string whatthis);

  //    ~Complex_Object();

  //  private:
  //    std::vector<std::string> fieldNames_;
  //    std::map<std::string,Abstract_Object*> fieldVariables_;

  //  };


  //  class Composite_Variable;
  //  class Complex_Variable_Value:public Abstract_Value_Object,public Complex_Object
  //  {
  //  public:
  //    static std::string ClassName();
  //    virtual std::string myClass()const override;
  //    virtual std::set<std::string> mySuperClasses()const override;

  //    virtual Abstract_Value_Object const * fieldVariable(const std::string& fieldname)const;
  //    virtual Abstract_Value_Object * fieldVariable(const std::string& fieldname);

  //    virtual bool setField(const std::string& fieldN,Abstract_Value_Object*  o);

  //    virtual const Abstract_Variable_Object* variable()const override;


  //    virtual bool push_back(const std::string &fieldname,
  //                           Abstract_Value_Object *object);


  //    Complex_Variable_Value(Environment* e,
  //                           std::string name,
  //                           std::string tip,
  //                           std::string whatthis,
  //                           std::string complexvar);

  //    ~Complex_Variable_Value();

  //  private:
  //    const Composite_Variable* cmplxvar_;
  //  };


  //  class Composite_Variable:public Abstract_Variable_Object, public Complex_Object
  //  {
  //  public:

  //    static std::string ClassName();
  //    virtual std::string myClass()const override;
  //    virtual std::set<std::string> mySuperClasses()const override;


  //    virtual Abstract_Variable_Object const * fieldVariable(const std::string& fieldname)const;

  //    virtual Abstract_Variable_Object  * fieldVariable(const std::string& fieldname);


  //    virtual bool setField(const std::string& fieldN,Abstract_Variable_Object*  o);


  //    virtual bool push_back(const std::string &fieldname,
  //                           Abstract_Variable_Object* object);


  //    virtual Complex_Variable_Value* defaultValue()const override;

  //    virtual Composite_Variable* create() const {}
  //    virtual bool isCreateable()const {return false;}


  //    Composite_Variable(Environment* e,
  //                       std::string name,
  //                       std::string tip,
  //                       std::string whatthis);

  //    ~Composite_Variable();
  //  private:

  //    std::map<std::string,std::pair<std::string,std::string>> fieldTipWhatThis_;
  //    std::vector<std::string> fieldNames_;
  //    std::map<std::string,Abstract_Object*> fieldVariables_;

  //  };






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
    const Named_Object* V(const std::string& variablename,const std::string& variabletype)const
    {
      auto it=variables_.find(variablename);
      if (it!=variables_.end())
        {
          Named_Object* v=it->second;
          if (v->mySuperClasses().find(variabletype)!=v->mySuperClasses().end())
            return v;
        }
      return nullptr;
    }

    void addUnit(Base_Unit* u)
    {
      units_[u->abbr()]=u;
    }

    void addVariable(Named_Object* v)
    {
      variables_[v->idName()]=v;
    }

  private:
    std::map<std::string,Base_Unit*> units_;
    std::map<std::string,Named_Object*> variables_;

  };




}





#endif // ABSTRACT_OBJECT_H




#ifdef MACRO_TEST


#include "Tests/MultipleTests.h"
namespace Markov_Test
{
  namespace Markov_Object_Test
  {

    using namespace Markov_Object;

    class Abstract_Object_Test
    {
    public:

      virtual MultipleTests classInvariant()const;

      Abstract_Object_Test(const Abstract_Object& object);

      virtual~Abstract_Object_Test();
      static std::string TestName();

      virtual std::string myTest()const;


    protected:
      const Abstract_Object* object_;
    };

  }
}

#endif //MACRO_TEST


