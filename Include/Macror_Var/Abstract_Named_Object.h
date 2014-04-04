#ifndef ABSTRACT_NAMED_OBJECT_H
#define ABSTRACT_NAMED_OBJECT_H

#include "Macror_Var/Abstract_Refers_Environment.h"
#include "Macror_Var/IdentifierName.h"
#include <memory>



namespace Macror_Var {

class Environment;

class Abstract_Named_Object:public Abstract_Refers_Environment
{
public:

  // reflection statics
  static std::string ClassName();

  static std::set<std::string> SuperClasses();

  // reflection overrides
  virtual std::string myClass()const override;
  virtual std::set<std::string> mySuperClasses()const override;


  // abtract overrides

  virtual Abstract_Named_Object* create()const override=0 ;

  /// returns the Environment where the object belongs


  /// if it is an unreferenced value without any referenced objects it returns a nullptr.


  virtual Abstract_Named_Object *
  CreateObject(const std::string &text, std::size_t &cursor) const override=0;


  /// identifier of the object
  virtual std::string idName()const =0;


 //Tip and whatthis
  /// hint about of the class nature
  virtual std::string Tip()const =0;
  /// a short description of the class
  virtual std::string WhatThis()const =0;

  virtual void setTip(const std::string& newTip)=0 ;
  virtual void setWhatThis(const std::string &whatthis)=0 ;




  // new abstract method, gives the list of objects referenced
  // for this object to has meaning
  virtual std::set<std::string> referencedObjects() const=0;


  //Helper methods for checking the referenced objects
  virtual bool refersToValidObjects()const;


  /// returns a string representation of the referenced objects
  virtual std::string contextToString()const;


/// constructors and destructor

  virtual ~Abstract_Named_Object()
  {}

  bool empty() const override;



  // Abstract_Object interface
};


}



#ifdef MACRO_TEST


namespace  Markov_IO {




}
#include "Tests/MultipleTests.h"
/*
namespace Markov_Test
{
  namespace Macror_Var_Test
  {

    using namespace Macror_Var;



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
*/
#endif //MACRO_TEST




#endif // ABSTRACT_NAMED_OBJECT_H
