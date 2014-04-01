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

  class TestResult
  {
  public:

    std::string error()const
    {
      std::string out;
      for (auto t:tests_)
        if (t.second!="OK")
           out+=t.first+": "+t.second;
      return out;
     }

    void addTest(const std::string& test, const std::string& result)
    {
      tests_[test]=result;
    }
    void addTest(const std::string& test, bool result)
    {
      if (result)
      tests_[test]="OK";
      else
        tests_[test]="FAIL";
    }
    TestResult& operator+=(const TestResult& other)
    {
      tests_.insert(other.tests_.begin(),other.tests_.end());
      return *this;
    }

  private:
    std::map<std::string,std::string> tests_;

  };




  class Abstract_Object
  {
  public:

    // static
    static std::string ClassName();

    static std::set<std::string> SuperClasses();


    //virtual implemented reflection
    virtual std::set<std::string> mySuperClasses()const;
    virtual std::string myClass()const;

    // virtual abstract
    virtual bool empty()const=0;


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

    virtual ~Abstract_Object();

  protected:
    virtual Abstract_Object*
    ToObject(const std::string& text, std::size_t &cursor) =0;

  };


  

  class Measurement_Unit;



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
