#ifndef ABSTRACT_VALUE_OBJECT_H
#define ABSTRACT_VALUE_OBJECT_H

#include "Markov_Object/Abstract_Object.h"

namespace Markov_Object {

  class Abstract_Variable_Object;


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

}




#ifdef MACRO_TEST


namespace  Markov_IO {

  std::string ToString(Markov_Object::Environment*const & x);
  std::string ToString(decltype (nullptr) const& x);
  std::string ToString(Markov_Object::Abstract_Object*const & x);
  std::string ToString(Markov_Object::Abstract_Named_Object*const & x);


}
#include "Tests/MultipleTests.h"
namespace Markov_Test
{
  namespace Markov_Object_Test
  {

    using namespace Markov_Object;

    class Abstract_Value_Test:public Abstract_Object_Test
    {
    public:

      virtual MultipleTests classInvariant()const;

      Abstract_Value_Test(const Abstract_Value_Object* object);

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



#endif // ABSTRACT_VALUE_OBJECT_H
