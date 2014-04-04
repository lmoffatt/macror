#include "Macror_Var/Abstract_Variable_Object.h"
#include "Macror_Var/Environment.h"

namespace Macror_Var {
  std::string Abstract_Variable_Object::ClassName()
  {
    return "Variable_Object";
  }

  std::string Abstract_Variable_Object::myClass()const {
    return ClassName();
  }



  std::set<std::string> Abstract_Variable_Object::mySuperClasses() const
  {
    return SuperClasses();
  }


  std::set<std::string> Abstract_Variable_Object:: SuperClasses() {
    auto mySC=Abstract_Named_Object::SuperClasses();
    mySC.insert(ClassName());
    return mySC;
  }


  Abstract_Variable_Object::~Abstract_Variable_Object(){}


  Abstract_Variable_Object::Abstract_Variable_Object(const Abstract_Variable_Object &other):
    Abstract_Named_Object(other)
  {}

  Abstract_Variable_Object::Abstract_Variable_Object(Environment *e, std::string variablename, std::string tip, std::string whatthis)
    :  Abstract_Named_Object(e,variablename,tip,whatthis)
  {}










}
