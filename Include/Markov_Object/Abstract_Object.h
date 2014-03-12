#ifndef ABSTRACT_OBJECT_H
#define ABSTRACT_OBJECT_H

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <memory>


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

  class Abstract_Object
  {
  public:

    // static
    static std::string ClassName();
    static Class_info classInfo();
    static std::set<std::string> SuperClasses();


    //virtual implemented reflection
    virtual Class_info myClassInfo()const;
    virtual std::string myClass()const;
    /// cast an Abstract_Object to myClass
    virtual Abstract_Object* dynamicCast(Abstract_Object* o)const;
    virtual const Abstract_Object* dynamicCast(const Abstract_Object* o)const;



    // virtual abstract
    virtual bool empty()const=0;
    virtual bool invalid()const=0;

    /// creates a object of current Class
    virtual Abstract_Object* create()const=0;


    /// returns enough information to make an InternallyValid copy of the object.
    /// if is an empty object it returns enough information to make another empty object
    virtual std::string ToString()const=0;

    // if the object is not of myClass, it returns nullptr
    // if the object is of myClass, it returns true and it uses the text to
    // build an object
    virtual Abstract_Object*
    CreateObject(const std::string& text, std::size_t &cursor)const =0;


    //implemented helper methods
    virtual bool belongsTo(const std::string classname)const;
    //constructors destructors


    // new implemented virtual methods
    // Environment
    virtual Environment* getEnvironment();

    virtual Environment const * getEnvironment()const;

    // new abstract method, gives the list of objects referenced
    // for this object to has meaning
    virtual std::set<std::string> referencedObjects() const=0;


    //Helper methods for checking the referenced objects
    virtual bool refersToValidObjects()const;


    /// returns a string representation of the referenced objects
    virtual std::string contextToString()const;

    Abstract_Object(const Abstract_Object& other ):
      E_(other.E_){}


    Abstract_Object(Environment *E);

    Abstract_Object();

    virtual ~Abstract_Object();
friend class Environment;

  protected:
    virtual Abstract_Object*
    ToObject(const std::string& text, std::size_t &cursor) =0;

    virtual void setEnvironment(Environment *E);



  private:
    Environment* E_;




  };




  class Measurement_Unit;

  class Abstract_Valued_Object//:public virtual Abstract_Object
  {
  public:
    static std::string ClassName();
    virtual std::string myClass()const ;
    static Class_info classInfo();
    virtual Class_info myClassInfo()const ;

    static std::set<std::string> SuperClasses() ;
    /// cast an Abstract_Object to Abstract_Valued_Object
    virtual Abstract_Valued_Object * dynamicCast(Abstract_Object* o)const ;
    virtual const Abstract_Valued_Object * dynamicCast(const Abstract_Object* o)const ;

    virtual std::string myUnit()const=0;
    virtual ~Abstract_Valued_Object();

    Abstract_Valued_Object(){}



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

      Abstract_Object_Test(const std::set<std::shared_ptr< Abstract_Object>> &objects);

      virtual~Abstract_Object_Test();
      static std::string TestName();

      virtual std::string myTest()const;


    protected:
      std::set<std::shared_ptr< Abstract_Object>> objects_;
    };





  }
}

#endif //MACRO_TEST


#endif // ABSTRACT_OBJECT_H
