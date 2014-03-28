#include "Markov_Object/Abstract_Variable_Object.h"
#include "Markov_Object/Environment.h"

namespace Markov_Object {
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

  Abstract_Variable_Object *Abstract_Variable_Object::dynamicCast(Abstract_Object *o) const
  {
    return dynamic_cast<Abstract_Variable_Object *>(o);
  }

  const Abstract_Variable_Object *Abstract_Variable_Object::dynamicCast(const Abstract_Object *o) const
  {
    return dynamic_cast<const Abstract_Variable_Object *>(o);
  }









}
