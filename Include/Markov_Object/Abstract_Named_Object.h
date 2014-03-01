#ifndef ABSTRACT_NAMED_OBJECT_H
#define ABSTRACT_NAMED_OBJECT_H
#include <memory>

#include "Markov_Object/Abstract_Object.h"
#include "Markov_Object/Environment.h"


namespace Markov_Object {



class Abstract_Named_Object:public virtual Abstract_Object
{
public:
// static helper methods
  static std::string getName(const std::string& multiplelines, std::size_t& pos);
  static std::string getTip(const std::string& multiplelines, std::size_t& pos);
  static std::string getWhatThis(const std::string& multiplelines,std::size_t& pos);

  static std::string getName(const std::string& multiplelines);
  static std::string getTip(const std::string& multiplelines);
  static std::string getWhatThis(const std::string& multiplelines);


  static std::string nextLine(const std::string& lines,std::size_t& n);
  static std::string removeInitialSpaces(const std::string& line);

  static void skipSpaces(const std::string& line,std::size_t& n);

  // reflection statics
  static std::string ClassName();
  static Class_info classInfo();
  static std::set<std::string> SuperClasses();

  // reflection overrides
  virtual std::string myClass()const override;
  virtual Class_info myClassInfo()const override;
  virtual Abstract_Named_Object* dynamicCast(Abstract_Object* o)const override;
  virtual const Abstract_Named_Object* dynamicCast(const Abstract_Object* o)const override;


  // abtract overrides

  virtual Abstract_Named_Object* create()const override=0 ;

  /// returns the Environment where the object belongs


  /// if it is an unreferenced value without any referenced objects it returns a nullptr.

  // implemented overrides
  virtual bool invalid() const override;
  virtual bool empty() const override;

  virtual std::string ToString()const override;
  virtual bool ToObject(const std::string& text, std::size_t &cursor) override ;




  // new implemented virtual methods
// Environment
  virtual Environment *getEnvironment()const;


  /// identifier of the object
  virtual std::string idName()const ;

  /// it checks for the environment to reference this object
  virtual bool isReferenced()const;

  /// returns true in case that the proposed idName is already present in the Environment
  /// in this case, the Environment is left unchanged
  virtual bool isDuplicate() const;



  // new helper methods
  virtual bool ToObject(Environment* E,const std::string& text, std::size_t &cursor);
  virtual bool ToObject(Environment* E,const std::string& text);


 //Tip and whatthis
  /// hint about of the class nature
  virtual std::string Tip()const ;
  /// a short description of the class
  virtual std::string WhatThis()const ;

  virtual void setTip(const std::string& newTip) ;
  virtual void setWhatThis(const std::string &whatthis) ;




// new abstract method, gives the list of objects referenced
  // for this object to has meaning
  virtual std::set<std::string> referencedObjects() const=0;


  //Helper methods for checking the referenced objects
  virtual bool refersToValidObjects()const;
  /// returns a string representation of the referenced objects
  virtual std::string contextToString()const;





/// constructors and destructor

  virtual ~Abstract_Named_Object();
  Abstract_Named_Object(Environment* e,
               std::string variablename,
               std::string tip,
               std::string whatthis);

  Abstract_Named_Object(Environment* e);

  Abstract_Named_Object();



  Abstract_Named_Object(const Abstract_Named_Object& other);

protected:
  virtual void setEnvironment(Environment* E);

private:
  Environment* E_;
  std::string variableName_;
  std::string tip_;
  std::string whatThis_;
};


}



#ifdef MACRO_TEST


namespace  Markov_IO {

  std::string ToString(Markov_Object::Abstract_Named_Object*const & x);
  std::string ToString(const std::shared_ptr< Markov_Object::Abstract_Named_Object> &x);


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
