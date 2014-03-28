#ifndef ABSTRACT_NAMED_OBJECT_H
#define ABSTRACT_NAMED_OBJECT_H
#include <memory>

#include "Markov_Object/Abstract_Object.h"

#include "IdentifierName.h"


namespace Markov_Object {

class Environment;

class Abstract_Named_Object:public virtual Abstract_Object
{
public:
// static helper methods
  static std::string getTip(const std::string& multiplelines, std::size_t& pos);
  static std::string getWhatThis(const std::string& multiplelines,std::size_t& pos);

  static std::string getTip(const std::string& multiplelines);
  static std::string getWhatThis(const std::string& multiplelines);


  static std::string nextLine(const std::string& lines,std::size_t& n);
  static std::string removeInitialSpaces(const std::string& line);



  // reflection statics
  static std::string ClassName();

  static std::set<std::string> SuperClasses();

  // reflection overrides
  virtual std::string myClass()const override;
  virtual std::set<std::string> mySuperClasses()const override;
  virtual Abstract_Named_Object* dynamicCast(Abstract_Object* o)const override;
  virtual const Abstract_Named_Object* dynamicCast(const Abstract_Object* o)const override;


  // abtract overrides

  virtual Abstract_Named_Object* create()const override=0 ;

  /// returns the Environment where the object belongs


  /// if it is an unreferenced value without any referenced objects it returns a nullptr.

  // implemented overrides
  virtual TestResult test()const override;
  virtual bool empty() const override;

  virtual std::string ToString()const override;

  virtual Abstract_Named_Object *
  CreateObject(const std::string &text, std::size_t &cursor) const override
  {
    auto tmp=create();
    auto out=tmp->ToObject(text,cursor);
    if (out==nullptr)
      delete tmp;
    return out;
  }


  /// identifier of the object
  virtual std::string idName()const ;


 //Tip and whatthis
  /// hint about of the class nature
  virtual std::string Tip()const ;
  /// a short description of the class
  virtual std::string WhatThis()const ;

  virtual void setTip(const std::string& newTip) ;
  virtual void setWhatThis(const std::string &whatthis) ;









/// constructors and destructor

  virtual ~Abstract_Named_Object();
  Abstract_Named_Object( Environment*  e,
               std::string variablename,
               std::string tip,
               std::string whatthis);

  Abstract_Named_Object(Environment*  e);

  Abstract_Named_Object();



  Abstract_Named_Object(const Abstract_Named_Object& other);


protected:
  // new helper methods: they add the created variable to the environment
  virtual Abstract_Named_Object* ToObject(const std::string& text, std::size_t &cursor)override;

private:
  std::string variableName_;
  std::string tip_;
  std::string whatThis_;

  // Abstract_Object interface
};


}



#ifdef MACRO_TEST


namespace  Markov_IO {




}
#include "Tests/MultipleTests.h"
namespace Markov_Test
{
  namespace Markov_Object_Test
  {

    using namespace Markov_Object;



    class Abstract_Named_Object_Test:public Abstract_Object_Test
    {
    public:

      virtual MultipleTests classInvariant()const;

      Abstract_Named_Object_Test(std::set<std::shared_ptr< Abstract_Named_Object>> objects):
        Abstract_Object_Test(
          std::set<std::shared_ptr< Abstract_Object>>(objects.begin(),objects.end())),
        named_objects_(objects){}

      virtual~Abstract_Named_Object_Test(){}
      static std::string TestName()
      {
        return "Abstract_Named_Object_Test";
      }

      virtual std::string myTest()const
      {
        return TestName();
      }


    protected:
       std::set<std::shared_ptr< Abstract_Named_Object>> named_objects_;
    };





  }
}

#endif //MACRO_TEST




#endif // ABSTRACT_NAMED_OBJECT_H
