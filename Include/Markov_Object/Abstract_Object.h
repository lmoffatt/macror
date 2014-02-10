#ifndef ABSTRACT_OBJECT_H
#define ABSTRACT_OBJECT_H

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>


#include <limits>

//#include "Markov_LA/Matrix.h"



namespace Markov_Object
{

  struct Class_info
  {
    std::string ClassName;
    std::set<std::string> superClasses;
    bool hasIdName;
    bool isValued;

  };

  class Environment;

  class Abstract_Object
  {
  public:

  // class properties
    static std::string ClassName()
    {
      return "Abstract_Object";
    }

    static Class_info classInfo();

    virtual Class_info myClassInfo()const;

    virtual std::string myClass()const;

    static std::set<std::string> SuperClasses();


  // Domain integrity of all internal values of the object
    // the referenced keys has to be formally valid but
   // it does not check it existance
    virtual bool isInternallyValid()const=0;


    /// if it is an unreferenced value without any referenced objects it returns false
    virtual bool refersEnvironment()const=0;

    /// returns the Environment where the object belongs
    /// if it is an unreferenced value without any referenced objects it returns a nullptr.
    virtual Environment* getEnvironment()const =0;


     /// checks for the existance of all refered objects
    virtual bool refersToValidObjects()const=0;

    virtual bool isValid()const
    {
      return isInternallyValid()&&refersToValidObjects();
    }


    // returns the set of all the objects referenced by this to make itself meaningfull
    virtual std::set<const Abstract_Object*> referencedObjects()const=0;



    /// creates a object of current Class
    virtual Abstract_Object* create()const=0;



    /// cast an Abstract_Object to myClass
    virtual Abstract_Object* dynamicCast(Abstract_Object* o)const;


    virtual const Abstract_Object* dynamicCast(const Abstract_Object* o)const;


    /// returns enough information to make an InternallyValid copy of the object.
    /// if is an empty object it returns enough information to make another empty object
    virtual std::string ToString()const=0;


    /// returns a string representation of the referenced objects
    virtual std::string contextToString()const
    {
      std::string s;
      for (auto r : referencedObjects())
        s+=r->ToString();
      return s;
    }



    // if the object is not of myClass, it returns a nullptr
    // otherwise it returns a new pointer with an object build with text
    // if text is Tostring, it should return an internallyvalid copy of the object
    // objects that are referenceable are also incoporated to the Environment
    virtual Abstract_Object* ToObject(Environment* e,const std::string& text, std::size_t &cursor)=0;






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

    static Class_info classInfo();
    virtual Class_info myClassInfo()const override;

    static std::set<std::string> SuperClasses();

    /// cast an Abstract_Object to Named_Object
    virtual Named_Object* dynamicCast(Abstract_Object* o)const override;
    virtual const Named_Object* dynamicCast(const Abstract_Object* o)const override;


    /// hopefully unique identifier of the object
    /// if not uniqueId returns false
    virtual std::string idName()const ;

    virtual bool hasIdName()const { return true;}

    virtual bool isInternallyValid() const
    {
      std::size_t n=0;
      bool validName=variableName_==Named_Object::getName(variableName_,n);
      bool validEnvironment=e_!=nullptr;
      return validName&&validEnvironment;
    }



    /// returns false in case that the proposed idName is already present in the Environment
    /// in this case, the Environment is left unchanged
    virtual bool isDuplicate()const
    {
      return isDuplicate_;
    }





    /// hint about of the class nature
    virtual std::string Tip()const ;

    /// a short description of the class
    virtual std::string WhatThis()const ;

    virtual Environment* getEnvironment() const override;


    virtual void setTip(const std::string& newTip) ;

    virtual void setWhatThis(const std::string &whatthis) ;


    virtual std::string ToString()const override;

    virtual Named_Object* ToObject(Environment* e,const std::string& text, std::size_t &cursor)  override;




    virtual ~Named_Object();
    Named_Object(Environment* e,
                 std::string variablename,
                 std::string tip,
                 std::string whatthis);

    Named_Object(Environment* e);

    Named_Object();

  protected:
    virtual void setEnvironment(Environment *e);



  private:
    Environment* e_;
    std::string variableName_;
    std::string tip_;
    std::string whatThis_;
    bool isDuplicate_;
};


  class Base_Unit:public virtual Named_Object
  {
  public:
    static std::string getUnit(const std::string& singleLine);

    static std::string ClassName();
    virtual std::string myClass()const override;
    /// cast an Abstract_Object to Base_Unit
    virtual Base_Unit * dynamicCast(Abstract_Object* o)const override;
    virtual const Base_Unit * dynamicCast(const Abstract_Object* o)const override;


    virtual std::string abbr()const;

    virtual std::string ToString()const;
    virtual Base_Unit* ToObject(Environment* e,const std::string& multipleLines,std::size_t& pos);

    virtual bool isCreateable()const;

    virtual Base_Unit* create()const;

    virtual std::size_t numFields()const{return 0;}

    Base_Unit();

    Base_Unit(std::string abbreviation,
              std::string name,
              Environment* e,
              std::string tip,
              std::string whatthis);

    Base_Unit(Environment* e);

    virtual bool refersEnvironment() const
    {
      return false;
    }
    virtual bool refersToValidObjects() const
    {
      return true;
    }
    virtual bool isValid() const
    {
      return !abbr_.empty();
    }
    virtual std::set<const Abstract_Object *> referencedObjects() const
    {
      return std::set<const Abstract_Object *>();
    }
    virtual std::string contextToString() const
    {
      return std::string();
    }

    virtual bool hasIdName() const
    {
      return true;
    }
    virtual bool isValued() const
    {
      return false;
    }



  private:

    std::string abbr_;

    };



  class Abstract_Valued_Object:public virtual Abstract_Object
  {
  public:
    static std::string ClassName();
    virtual std::string myClass()const override;
    static Class_info classInfo();
    virtual Class_info myClassInfo()const override;

    static std::set<std::string> SuperClasses() ;
    /// cast an Abstract_Object to Abstract_Valued_Object
    virtual Abstract_Valued_Object * dynamicCast(Abstract_Object* o)const override;
    virtual const Abstract_Valued_Object * dynamicCast(const Abstract_Object* o)const override;


    virtual const Base_Unit* myUnit()const=0;
    virtual ~Abstract_Valued_Object();


    virtual bool refersEnvironment()const
    {return true;}

    virtual bool refersToValidObjects()const
    {
    bool validUnit=myUnit()!=nullptr;
    return validUnit;
    }

    // returns the set of all the objects referenced by this to make itself meaningfull
    virtual std::set<const Abstract_Object*> referencedObjects()const
    {
      std::set<const Abstract_Object *> s;
      if (myUnit())
        s.insert(myUnit());
      return s;
    }


  };

  class Abstract_Value_Object;


  class Abstract_Variable_Object: public Named_Object
  {
  public:

    static std::string ClassName();
    virtual std::string myClass()const override;
    static Class_info classInfo();
    virtual Class_info myClassInfo()const override;

    static std::set<std::string> SuperClasses();
    virtual ~Abstract_Variable_Object();
    /// cast an Abstract_Object to Abstract_Variable_Object
    virtual Abstract_Variable_Object * dynamicCast(Abstract_Object* o)const override;
    virtual const Abstract_Variable_Object * dynamicCast(const Abstract_Object* o)const override;


    virtual Abstract_Variable_Object* create() const=0;


    virtual Abstract_Value_Object* defaultValue()const=0;


    virtual bool isValueValid(const Abstract_Value_Object* v)const;

    Abstract_Variable_Object(Environment* e,
                             std::string variablename,
                             std::string tip,
                             std::string whatthis)
      : Named_Object(e,variablename,tip,whatthis)
    {}

    Abstract_Variable_Object(Environment* e)
      :
        Named_Object(e){}

    Abstract_Variable_Object(){}


  };


  class Abstract_Value_Object: public  virtual Abstract_Object
  {
  public:
    static std::string ClassName();

    virtual std::string myClass()const override;
    static Class_info classInfo();
    virtual Class_info myClassInfo()const override;

    static std::set<std::string> SuperClasses();
    /// cast an Abstract_Object to Abstract_Value_Object
    virtual Abstract_Value_Object * dynamicCast(Abstract_Object* o)const override;
    virtual const Abstract_Value_Object * dynamicCast(const Abstract_Object* o)const override;

    virtual ~Abstract_Value_Object();

    virtual bool isClonable()const;
    virtual Abstract_Value_Object* create()const;
    virtual Environment* getEnvironment() const override
    {
      return variable()->getEnvironment();
    }
    virtual const Abstract_Variable_Object* variable()const=0;
    virtual bool isValued() const
    {
      return true;
    }

  };



  template<typename T>
  class SimpleVariableValue;

  template<typename T>
  class SimpleVariable: public Abstract_Variable_Object,public Abstract_Valued_Object
  {
  public:

    static std::string ClassName();
    virtual std::string myClass()const override;
    static Class_info classInfo();
    virtual Class_info myClassInfo()const override;

    static std::set<std::string> SuperClasses();

    /// cast an Abstract_Object to SimpleVariable<T>
    virtual SimpleVariable<T> * dynamicCast(Abstract_Object* o)const override;
    virtual const SimpleVariable<T> * dynamicCast(const Abstract_Object* o)const override;


    virtual const Base_Unit* myUnit()const ;

    virtual std::string ToString()const override;
    virtual SimpleVariable* ToObject(Environment* e,const std::string& multipleLines,std::size_t& pos) override;

    virtual SimpleVariableValue<T>* defaultValue()const override;

    virtual bool isValueValid(const Abstract_Value_Object* ob)const
    {
      return ob->myClassInfo().superClasses.count(defaultValue()->myClass())!=0;
    }

    virtual bool isCreateable()const;
    virtual SimpleVariable<T>* create()const;

    SimpleVariable(Environment *e);


    SimpleVariable();



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

    // Abstract_Object interface
  public:
    virtual bool isValued() const;
  };





template<typename T>
bool SimpleVariable<T>::isValued() const
{
  return false;
}


  template<typename T>
  class SimpleVariableValue: public Abstract_Value_Object,public Abstract_Valued_Object
  {
  public:

    virtual bool isClonable() const
    {
      return true;
    }
    virtual SimpleVariableValue<T> *create() const
    {
      return new SimpleVariableValue<T>;
    }

    virtual bool isInternallyValid() const
    {
      bool validVariable= variable()!=nullptr;
      if (validVariable)
        {
      bool validUnit=myUnit()!=nullptr;
      return validUnit&&validVariable;
        }
      else return validVariable;
    }



    virtual bool refersEnvironment() const
    {
      return true;
    }
    virtual bool refersToValidObjects() const
    {
      bool validUnit=myUnit()!=nullptr;
      bool validVar=variable()!=nullptr;
      return validUnit&& validVar;
    }
    virtual std::set<const Abstract_Object *> referencedObjects() const
    {
      auto s=Abstract_Valued_Object::referencedObjects();
      if (variable())
        s.insert(variable());
      return s;
    }
    virtual bool hasIdName() const
    {
      return false;
    }
    static T get(const std::string &singleLine);
    static bool is(const std::string& singleLine);

    virtual std::string myClass()const override;

    static std::string ClassName();
    static Class_info classInfo();
    virtual Class_info myClassInfo()const override;

    static std::set<std::string> SuperClasses();

    /// cast an Abstract_Object to SimpleVariableValue<T>
    virtual SimpleVariableValue<T> * dynamicCast(Abstract_Object* o)const override;
    virtual const SimpleVariableValue<T> * dynamicCast(const Abstract_Object* o)const override;


    virtual const Base_Unit* myUnit()const override;

    virtual const SimpleVariable<T>* variable()const override;

    virtual T value() const;

    virtual std::string ToString()const override;
    virtual SimpleVariableValue<T>* ToObject(Environment* e,const std::string& multipleLines,std::size_t& pos)override;



    SimpleVariableValue();
    SimpleVariableValue(std::string variablename,
                        T defaultValue,
                        std::string unit,
                        Environment *e);
    ~SimpleVariableValue();

  private:
    const SimpleVariable<T>* variable_;
    const Base_Unit* unit_;
    T value_;
  };


  class FieldVariable: public Abstract_Variable_Object
  {
    // Abstract_Variable_Object interface
  public:
    virtual Abstract_Value_Object *defaultValue() const;

    virtual std::string ToString()const override;
    virtual FieldVariable* ToObject(Environment* e,const std::string& multipleLines,std::size_t& pos) override;
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
  //    static std::set<std::string> SuperClasses();

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
  //    static std::set<std::string> SuperClasses();

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
  //    static std::set<std::string> SuperClasses();


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
    const Named_Object* V(const std::string& variablename)const
    {
      auto it=variables_.find(variablename);
      if (it!=variables_.end())
        {
          Named_Object* v=it->second;
            return v;
        }
      else return nullptr;
    }

    void addUnit(Base_Unit* u)
    {
      units_[u->abbr()]=u;
    }

    void addVariable(Named_Object* v)
    {
      variables_[v->idName()]=v;
    }

    Abstract_Object* create(std::string classname);


    bool doesDynCast(const Abstract_Object* o,std::string classname);

    std::set<std::string> getSuperClasses(const std::string& classname);

    Environment();

  private:
    std::map<std::string,Base_Unit*> units_;
    std::map<std::string,Named_Object*> variables_;
    std::map<std::string,Abstract_Object*> classes_;

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


