#ifndef ABSTRACT_NAMED_OBJECT_H
#define ABSTRACT_NAMED_OBJECT_H
#include "Markov_Object/Abstract_Object.h"
#include "Markov_Object/Environment.h"


namespace Markov_Object {



class Abstract_Named_Object:public virtual Abstract_Object
{
public:

  static std::string getName(const std::string& multiplelines, std::size_t& pos);
  static std::string getTip(const std::string& multiplelines, std::size_t& pos);
  static std::string getWhatThis(const std::string& multiplelines,std::size_t& pos);
  static std::string getName(const std::string& multiplelines);

  static std::string getTip(const std::string& multiplelines);

  static std::string getWhatThis(const std::string& multiplelines);


  static std::string nextLine(const std::string& lines,std::size_t& n);

  static std::string removeInitialSpaces(const std::string& line);

  static void skipSpaces(const std::string& line,std::size_t& n);


  static std::string ClassName();
  virtual std::string myClass()const override;

  static Class_info classInfo();
  virtual Class_info myClassInfo()const override;

  static std::set<std::string> SuperClasses();

  /// cast an Abstract_Object to Named_Object
  virtual Abstract_Named_Object* dynamicCast(Abstract_Object* o)const override;
  virtual const Abstract_Named_Object* dynamicCast(const Abstract_Object* o)const override;


  virtual Abstract_Named_Object* create()const=0;


  /// hopefully unique identifier of the object
  /// if not uniqueId returns false
  virtual std::string idName()const ;


  virtual bool isInternallyValid() const
  {
    std::size_t n=0;
    bool validName=variableName_==Abstract_Named_Object::getName(variableName_,n);
    bool validEnvironment=getEnvironment()!=nullptr;
    return validName&&validEnvironment;
  }

  /// it checks for the environment to reference it
  ///

  virtual bool isReferenced()const
  {
    if (getEnvironment()==nullptr)
      return false;
    else
      return getEnvironment()->idN(idName())==this;


  }



  /// returns true in case that the proposed idName is already present in the Environment
  /// in this case, the Environment is left unchanged
  virtual bool isDuplicate() const;



  virtual bool isValid()const override;



  /// hint about of the class nature
  virtual std::string Tip()const ;

  /// a short description of the class
  virtual std::string WhatThis()const ;


  virtual void setTip(const std::string& newTip) ;

  virtual void setWhatThis(const std::string &whatthis) ;


  virtual std::string ToString()const override;

  virtual bool ToObject(Environment* e,const std::string& text, std::size_t &cursor)  override;

  virtual bool ToObject(Environment* e,const std::string& text) override;



  virtual ~Abstract_Named_Object();
  Abstract_Named_Object(Environment* e,
               std::string variablename,
               std::string tip,
               std::string whatthis);

  Abstract_Named_Object(Environment* e);

  Abstract_Named_Object();


  Abstract_Named_Object(const Abstract_Named_Object& other);

private:
  std::string variableName_;
  std::string tip_;
  std::string whatThis_;
};


}



#ifdef MACRO_TEST


namespace  Markov_IO {

  std::string ToString(Markov_Object::Abstract_Named_Object*const & x);


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

      Abstract_Named_Object_Test(const Abstract_Named_Object* object):
        Abstract_Object_Test(object),
        named_object_(object){}

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
      const Abstract_Named_Object* named_object_;
    };





  }
}

#endif //MACRO_TEST




#endif // ABSTRACT_NAMED_OBJECT_H
