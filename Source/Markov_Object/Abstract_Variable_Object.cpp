#include "Markov_Object/Abstract_Variable_Object.h"

namespace Markov_Object {
  std::string Abstract_Variable_Object::ClassName()
  {
    return "Variable_Object";
  }

  std::string Abstract_Variable_Object::myClass()const {
    return ClassName();
  }

  Class_info Abstract_Variable_Object::classInfo()
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

  Class_info Abstract_Variable_Object::myClassInfo() const
  {
    return classInfo();
  }


  std::set<std::string> Abstract_Variable_Object:: SuperClasses() {
    auto mySC=Abstract_Named_Object::SuperClasses();
    mySC.insert(ClassName());
    return mySC;
  }

}
