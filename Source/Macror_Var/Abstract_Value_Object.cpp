#include "Macror_Var/Abstract_Value_Object.h"
#include "Macror_Var/Abstract_Variable_Object.h"

namespace Macror_Var {
  std::string Abstract_Value_Object::ClassName()
  {
    return "Value_Object";
  }

  std::string Abstract_Value_Object::myClass()const {
    return ClassName();
  }



  std::set<std::string> Abstract_Value_Object::mySuperClasses() const
  {
    return SuperClasses();
  }


  std::set<std::string> Abstract_Value_Object:: SuperClasses() {
    auto mySC=Abstract_Object::SuperClasses();
    mySC.insert(ClassName());
    return mySC;
  }



  Abstract_Value_Object::~Abstract_Value_Object(){}









}







#ifdef MACRO_TEST

#include "Tests/TESTS.h"
#include "Tests/ElementaryTest.h"


/*

namespace Markov_Test
{
  namespace Macror_Var_Test
  {

    using namespace Macror_Var;







    MultipleTests unknownMethodPostConditions(const Abstract_Variable_Object* o)
    {
      MultipleTests M("unknown() method",
                      "postconditions");

      std::shared_ptr<Abstract_Value_Object> u(o->unKnownValue());
      M.push_back(ElementaryTest("unknownValue it is, actually",
                                 "unKnownValue()->isUnknown()==true",
                                 u->isUnknown()==true));
      std::size_t n=0;

      return M;

    }






    MultipleTests Abstract_Value_Test::classInvariant() const
    {


      MultipleTests M("Abstract Value Tests",
                      "interface invariants");
      M.push_back(Abstract_Object_Test::classInvariant());

      // M.push_back(unknownMethodPostConditions(this->value_object_));

      return M;

    }



  }
}


*/
#endif //MACRO_TEST


