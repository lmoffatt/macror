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
  class Abstract_Named_Object;

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


    virtual bool empty()const;



    /// checks for the existance of all refered objects
    virtual bool refersToValidObjects()const =0;



    virtual bool isValid()const;


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


    virtual bool ToObject(Environment* e,const std::string& text);

    static std::string classNameBeginMarker()
    {
      return "<";
    }
    static std::string classNameEndMarker();

    static std::string namePermittedCharacters();

    static std::string getClassName(const std::string& line,std::size_t pos);

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



  class Measurement_Unit;

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

    virtual const Measurement_Unit* myUnit()const=0;
    virtual ~Abstract_Valued_Object();

    Abstract_Valued_Object():
      Abstract_Object(){}

    Abstract_Valued_Object(Environment* E):
      Abstract_Object(E){}


  };


//  class FieldVariable: public Abstract_Variable_Object
//  {
//    // Abstract_Variable_Object interface
//  public:

//    virtual std::string ToString()const override;
//    virtual bool ToObject(Environment* e,const std::string& multipleLines,std::size_t& pos) override;
//    virtual Abstract_Variable_Object const * variable()const;

//    virtual Abstract_Variable_Object  * variable();


//    virtual bool setField(Abstract_Object*  o);


//    FieldVariable(Environment* e,
//                  Abstract_Variable_Object* var,
//                  std::string name,
//                  std::string tip,
//                  std::string whatthis);

//  private:
//    Abstract_Variable_Object * var_;

//  };



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








}









#ifdef MACRO_TEST


namespace  Markov_IO {

  std::string ToString(Markov_Object::Environment*const & x);
  std::string ToString(decltype (nullptr) const& x);
  std::string ToString(Markov_Object::Abstract_Object*const & x);


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





  }
}

#endif //MACRO_TEST


#endif // ABSTRACT_OBJECT_H
