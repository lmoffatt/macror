#ifndef ABSTRACT_VALUE_OBJECT_H
#define ABSTRACT_VALUE_OBJECT_H

#include "Markov_Object/Abstract_Object.h"

namespace Markov_Object {

  class Abstract_Variable_Object;


  class Abstract_Value_Object: public  virtual Abstract_Object
  {
  public:
    //static
    // reflection
    static std::string ClassName();

    static std::set<std::string> SuperClasses();


  // virtual overrides from Abstract_Object
    virtual std::string myClass()const  override;
    virtual std::set<std::string> mySuperClasses()const override;



    virtual Abstract_Value_Object* create()const override=0;


    virtual bool isUnknown()const=0;

    virtual std::string variable()const=0;

    Abstract_Value_Object(){}
    virtual ~Abstract_Value_Object();



  };

}




#ifdef MACRO_TEST


namespace  Markov_IO {



}
#include "Tests/MultipleTests.h"
/*

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



*/
#endif //MACRO_TEST



#endif // ABSTRACT_VALUE_OBJECT_H
