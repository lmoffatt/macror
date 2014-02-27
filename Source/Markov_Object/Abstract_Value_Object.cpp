#include "Markov_Object/Abstract_Value_Object.h"
#include "Markov_Object/Abstract_Variable_Object.h"

namespace Markov_Object {
  std::string Abstract_Value_Object::ClassName()
  {
    return "Value_Object";
  }

  std::string Abstract_Value_Object::myClass()const {
    return ClassName();
  }

  Class_info Abstract_Value_Object::classInfo()
  {
    return Class_info
    {
        {ClassName()},
        {SuperClasses()},
        false,
        false,
        false
      };

  }

  Class_info Abstract_Value_Object::myClassInfo() const
  {
    return classInfo();
  }


  std::set<std::string> Abstract_Value_Object:: SuperClasses() {
    auto mySC=Abstract_Object::SuperClasses();
    mySC.insert(ClassName());
    return mySC;
  }

  Abstract_Value_Object *Abstract_Value_Object::dynamicCast(Abstract_Object *o) const
  {
    return dynamic_cast<Abstract_Value_Object*> (o);
  }

  const Abstract_Value_Object *Abstract_Value_Object::dynamicCast(const Abstract_Object *o) const
  {
    return dynamic_cast<const Abstract_Value_Object*> (o);
  }


  Abstract_Value_Object::~Abstract_Value_Object(){}









}




Markov_Test::Markov_Object_Test::Abstract_Value_Test::Abstract_Value_Test(const Markov_Object::Abstract_Value_Object *object):
  Abstract_Object_Test(object),
  value_object_(object){}



#ifdef MACRO_TEST

#include "Tests/TESTS.h"
#include "Tests/ElementaryTest.h"




namespace Markov_Test
{
  namespace Markov_Object_Test
  {

    using namespace Markov_Object;


     MultipleTests variableMethodPostConditions(const Abstract_Value_Object* o)
    {
      MultipleTests M("variable() method",
                      "postconditions");

      if (o->invalid())
        {
          M.push_back(TEST_NEQ("returns a non empty string",
                               o->variable().empty(),
                               false));
        }

      return M;
      }





    MultipleTests unknownMethodPostConditions(const Abstract_Variable_Object* o)
    {
      MultipleTests M("unknown() method",
                      "postconditions");

      Abstract_Value_Object* u=o->unKnownValue();
      M.push_back(ElementaryTest("unknownValue it is, actually",
                                 "unKnownValue()->isUnknown()==true",
                                 u->isUnknown()==true));
      Abstract_Value_Object* ou=u->create();
      bool isu=ou->ToObject(u->ToString());
      M.push_back(ElementaryTest("serialize unknown value",
                                 "ToObject(unknownValue)==true",
                                 isu==true));

      M.push_back(TEST_EQ("same string",
                              u->ToString(),
                          ou->ToString()));

      return M;

    }






    MultipleTests Abstract_Value_Test::classInvariant() const
    {


      MultipleTests M("Abstract Value Tests",
                      "interface invariants");
      M.push_back(Abstract_Object_Test::classInvariant());

      M.push_back(variableMethodPostConditions(this->value_object_));
     // M.push_back(unknownMethodPostConditions(this->value_object_));

      return M;

    }



  }
}

#endif //MACRO_TEST


