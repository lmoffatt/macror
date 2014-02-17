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
    bool refersEnvironment;
    bool hasIdName;
    bool isValued;
  };

  class Environment;
  class Named_Object;

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


    /// returns the Environment where the object belongs
    /// if it is an unreferenced value without any referenced objects it returns a nullptr.
    virtual Environment* getEnvironment()const
    {
      return E_;
    }


    virtual bool empty()const
    {
      return ToString().empty();
    }



    /// checks for the existance of all refered objects
    virtual bool refersToValidObjects()const
    {return true;}


    virtual bool isValid()const
    {
      return isInternallyValid()&&refersToValidObjects();
    }


    // returns the set of all the objects referenced by this to make itself meaningfull
    virtual std::set<std::string> referencedObjects()const=0;




    /// creates a object of current Class
    virtual Abstract_Object* create()const=0;



    /// cast an Abstract_Object to myClass
    virtual Abstract_Object* dynamicCast(Abstract_Object* o)const;


    virtual const Abstract_Object* dynamicCast(const Abstract_Object* o)const;


    /// returns enough information to make an InternallyValid copy of the object.
    /// if is an empty object it returns enough information to make another empty object
    virtual std::string ToString()const=0;


    /// returns a string representation of the referenced objects

    virtual std::string contextToString()const;







    // if the object is not of myClass, it returns false
    // if the object is of myClass, it returns true and it uses the text to
    // reasign its internal structure accordingly with it
    virtual bool ToObject(Environment* e,const std::string& text, std::size_t &cursor)=0;


    virtual bool ToObject(Environment* e,const std::string& text)
    {
      std::size_t n=0;
      return ToObject(e,text,n);
    }

    static std::string classNameBeginMarker()
    {
      return "<";
    }
    static std::string classNameEndMarker()
    {
      return ">";
    }

    static std::string namePermittedCharacters()
    {
      return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789_";
    }

    static std::string getClassName(const std::string& line,std::size_t pos)
    {
      auto n0=line.find_first_of(classNameBeginMarker(),pos);
      auto nend=line.find_first_of(classNameEndMarker(),n0);

      std::string name=line.substr(n0,nend);
      if (name.empty())
        return name;
      auto m=name.find_first_not_of(namePermittedCharacters(),0);

      if (m!=name.npos)
        return name;
      else
        return "";
    }




    Abstract_Object():
      E_(nullptr){}

    Abstract_Object(Environment* E):
      E_(E){}



    virtual ~Abstract_Object();


  protected:
    virtual void setEnvironment(Environment* E)
    {
      E_=E;
    }
  private:
    Environment* E_;

  };



  class Named_Object:public virtual Abstract_Object
  {
  public:

    static std::string getName(const std::string& multiplelines, std::size_t& pos);
    static std::string getTip(const std::string& multiplelines, std::size_t& pos);
    static std::string getWhatThis(const std::string& multiplelines,std::size_t& pos);
    static std::string getName(const std::string& multiplelines)
    {
      std::size_t n=0;
      return getName(multiplelines,n);
    }

    static std::string getTip(const std::string& multiplelines)
    {
      std::size_t n=0;
      return getTip(multiplelines,n);
    }

    static std::string getWhatThis(const std::string& multiplelines)
    {
      std::size_t n=0;
      return getWhatThis(multiplelines,n);
    }


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


    virtual Named_Object* create()const=0;


    /// hopefully unique identifier of the object
    /// if not uniqueId returns false
    virtual std::string idName()const ;


    virtual bool isInternallyValid() const
    {
      std::size_t n=0;
      bool validName=variableName_==Named_Object::getName(variableName_,n);
      bool validEnvironment=getEnvironment()!=nullptr;
      return validName&&validEnvironment;
    }

    /// it checks for the environment to reference it
    ///

    virtual bool isReferenced()const;



    /// returns true in case that the proposed idName is already present in the Environment
    /// in this case, the Environment is left unchanged
    virtual bool isDuplicate()const;



    virtual bool isValid()const override
    {
      return Abstract_Object::isValid()&&isReferenced();
    }



    /// hint about of the class nature
    virtual std::string Tip()const ;

    /// a short description of the class
    virtual std::string WhatThis()const ;


    virtual void setTip(const std::string& newTip) ;

    virtual void setWhatThis(const std::string &whatthis) ;


    virtual std::string ToString()const override;

    virtual bool ToObject(Environment* e,const std::string& text, std::size_t &cursor)  override;

    virtual bool ToObject(Environment* e,const std::string& text) override
    {
      std::size_t n=0;
      return ToObject(e,text,n);
    }



    virtual ~Named_Object();
    Named_Object(Environment* e,
                 std::string variablename,
                 std::string tip,
                 std::string whatthis);

    Named_Object(Environment* e);

    Named_Object();


    Named_Object(const Named_Object& other):
      Abstract_Object(other.getEnvironment()),
      variableName_(other.variableName_),
      tip_(other.tip_),
      whatThis_(other.whatThis_){}

  private:
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


    static Class_info classInfo();
    virtual Class_info myClassInfo()const override;

    static std::set<std::string> SuperClasses();

    /// cast an Abstract_Object to Base_Unit
    virtual Base_Unit * dynamicCast(Abstract_Object* o)const override;
    virtual const Base_Unit * dynamicCast(const Abstract_Object* o)const override;


    virtual std::string longName()const;

    virtual std::string ToString()const;
    virtual bool ToObject(Environment* e,const std::string& multipleLines,std::size_t& pos);

    virtual bool isCreateable()const;

    virtual Base_Unit* create()const;

    virtual std::set<std::string> referencedObjects()const
    {
      return std::set<std::string>();
    }


    virtual std::size_t numFields()const{return 0;}

    Base_Unit();

    Base_Unit(std::string abbreviation,
              std::string name,
              Environment* e,
              std::string tip,
              std::string whatthis);

    Base_Unit(Environment* e);


  private:

    std::string longName_;

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


    virtual bool refersToValidObjects()const override
    {
      bool validUnit=myUnit()!=nullptr;
      return validUnit;
    }




    Abstract_Valued_Object():
      Abstract_Object(){}

    Abstract_Valued_Object(Environment* E):
      Abstract_Object(E){}


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

    virtual Abstract_Value_Object* unKnownValue()const=0;


    virtual bool isValidValue(const Abstract_Value_Object* v)const=0;



    Abstract_Variable_Object(Environment* e,
                             std::string variablename,
                             std::string tip,
                             std::string whatthis)
      : Abstract_Object(e),
        Named_Object(e,variablename,tip,whatthis)
    {}

    Abstract_Variable_Object(Environment* e)
      :
        Named_Object(e){}

    Abstract_Variable_Object(){}

    Abstract_Variable_Object(const Abstract_Variable_Object& other):
      Abstract_Object(other.getEnvironment()),
      Named_Object(other)
    {}


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

    virtual Abstract_Value_Object* create()const=0;

    virtual const Abstract_Variable_Object* variable()const=0;

    Abstract_Value_Object():
      Abstract_Object(){}

    Abstract_Value_Object(Environment* E):
      Abstract_Object(E){}

    virtual bool isUnknown()const=0;

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
    virtual bool ToObject(Environment* e,const std::string& multipleLines,std::size_t& pos) override;

    virtual SimpleVariableValue<T>* defaultValue()const override;

    virtual SimpleVariableValue<T>* unKnownValue()const override
    {
      return new SimpleVariableValue<T>(idName(),
                                        SimpleVariableValue<T>::unknownValue(),
                                        myUnit()->idName(),
                                        getEnvironment());

    }


    virtual std::set<std::string> referencedObjects()const
    {
      return {unitId_};
    }



    virtual bool isValidValue(const Abstract_Value_Object* ob)const
    {
      return ob->variable()==this;
    }

    virtual bool isCreateable()const;
    virtual SimpleVariable<T>* create()const;

    SimpleVariable(Environment *e);


    SimpleVariable();

    SimpleVariable(const SimpleVariable<T>& other):
      Abstract_Object(other.getEnvironment()),
      Abstract_Variable_Object(other),
      Abstract_Valued_Object(other.getEnvironment()),
      defautValue_(other.defautValue_),
      unitId_(other.unitId_){}






    SimpleVariable(std::string name,
                   T defaultValue,
                   std::string unit,
                   Environment *e,
                   std::string tip,
                   std::string whatthis);
    ~SimpleVariable();
  private:
    T defautValue_;
    std::string unitId_;

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

    virtual SimpleVariableValue<T> *create() const
    {
      return new SimpleVariableValue<T>;
    }

    virtual bool isInternallyValid() const
    {
      bool validVariableId=!variableId_.empty()&&
          (variableId_==Named_Object::getName(variableId_));
      bool validUnit=!unitId_.empty()&&(unitId_==Base_Unit::getUnit(unitId_));
      return validUnit&&validVariableId;
    }



    virtual bool refersToValidObjects() const override
    {
      bool validUnit=myUnit()!=nullptr;
      bool validVar=variable()!=nullptr;
      return validUnit&& validVar;
    }
    virtual std::set<std::string> referencedObjects() const
    {
      std::set<std::string> s;
      s.insert(unitId_);
      s.insert(variableId_);
      return s;
    }
    virtual bool hasIdName() const
    {
      return false;
    }
    static T get(const std::string &singleLine,std::size_t* pos);
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
    virtual bool ToObject(Environment* e,const std::string& multipleLines,std::size_t& pos)override;


    static T unknownValue();

    virtual bool isUnknown()const override;


    SimpleVariableValue();
    SimpleVariableValue(std::string variablename,
                        T defaultValue,
                        std::string unit,
                        Environment *e);
    ~SimpleVariableValue();

  private:
    std::string variableId_;
     std::string unitId_;
     T value_;

  };


  class FieldVariable: public Abstract_Variable_Object
  {
    // Abstract_Variable_Object interface
  public:

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
    const Base_Unit* U(const std::string& unitAbreviation)const
    {
      auto it=units_.find(unitAbreviation);
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

    std::set<std::string> Variables()const
    {
      std::set<std::string> o;
      for (auto m:variables_)
        {
          if (dynamic_cast<Abstract_Value_Object*>(m.second)!=nullptr)
            o.insert(m.first);

        }
      return o;
    }

    void addUnit(Base_Unit* u)
    {
      auto it=units_.find(u->idName());
      if(it!=units_.end())
        {
          if (it->second==u)
            return;
          delete it->second;
        }
      units_[u->idName()]=u;
    }

    void addVariable(Named_Object* v)
    {
      auto it=variables_.find(v->idName());
      if(it!=variables_.end())
        {
          if (it->second==v)
            return;
          delete it->second;
        }
      variables_[v->idName()]=v;
    }

    void add(Named_Object* v)
    {
      if (v->myClassInfo().superClasses.count(Base_Unit::ClassName())!=0)
        {
          Base_Unit* u=dynamic_cast<Base_Unit*>(v);
          addUnit(u);
        }
      else
        {
          addVariable(v);
        }
    }




    Abstract_Object* create(std::string classname);


    bool doesDynCast(const Abstract_Object* o,std::string classname);

    std::set<std::string> getSuperClasses(const std::string& classname);

    bool empty()const
    {

      return units_.empty()&&variables_.empty();
    }

    Environment();

    ~Environment()
    {
      for (auto it:units_)
        delete it.second;
      for (auto it:variables_)
        delete it.second;
      for (auto it:classes_)
        delete it.second;
    }

  private:
    std::map<std::string,Base_Unit*> units_;
    std::map<std::string,Named_Object*> variables_;
    std::map<std::string,Abstract_Object*> classes_;

  };




}





#endif // ABSTRACT_OBJECT_H




#ifdef MACRO_TEST


namespace  Markov_IO {

  std::string ToString(Markov_Object::Environment*const & x);
  std::string ToString(decltype (nullptr) const& x);
  std::string ToString(Markov_Object::Abstract_Object*const & x);
  std::string ToString(Markov_Object::Named_Object*const & x);


}
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

      Abstract_Object_Test(const Abstract_Object* object);

      virtual~Abstract_Object_Test();
      static std::string TestName();

      virtual std::string myTest()const;


    protected:
      const Abstract_Object* object_;
    };


    class Named_Object_Test:public Abstract_Object_Test
    {
    public:

      virtual MultipleTests classInvariant()const;

      Named_Object_Test(const Named_Object* object):
        Abstract_Object_Test(object),
        named_object_(object){}

      virtual~Named_Object_Test(){}
      static std::string TestName()
      {
        return "Named_Object_Test";
      }

      virtual std::string myTest()const
      {
        return TestName();
      }


    protected:
      const Named_Object* named_object_;
    };


    class Abstract_Value_Test:public Abstract_Object_Test
    {
    public:

      virtual MultipleTests classInvariant()const;

      Abstract_Value_Test(const Abstract_Value_Object* object):
        Abstract_Object_Test(object),
        value_object_(object){}

      virtual~Abstract_Value_Test(){}
      static std::string TestName()
      {
        return "Abstract_Value_Test";
      }

      virtual std::string myTest()const
      {
        return TestName();
      }


    protected:
      const Abstract_Value_Object* value_object_;
    };



  }
}

#endif //MACRO_TEST


