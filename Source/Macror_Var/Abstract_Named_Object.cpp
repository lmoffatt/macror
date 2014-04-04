#include <string>
#include "Macror_Var/Abstract_Named_Object.h"
#include "Macror_Var/Measurement_Unit.h"

#include "Macror_Var/Environment.h"
#include "Macror_Var/IdentifierName.h"

namespace  Macror_Var {

  std::string Abstract_Named_Object::ClassName()
  {
    return "Named_Object";
  }

  std::set<std::string> Abstract_Named_Object::SuperClasses()
  {
    auto mySC=Abstract_Object::SuperClasses();
    mySC.insert(ClassName());
    return mySC;
  }

  bool Abstract_Named_Object::refersToValidObjects() const
  {
    for (auto o:this->referencedObjects())
      {
        auto v =getEnvironment()->idN(o);
        if (v==nullptr)
          return false;
      }
    return true;
  }

  std::string Abstract_Named_Object::contextToString() const
  {
    std::string s;
    for (auto r : referencedObjects())
      {
        auto v=getEnvironment()->idN(r);
        if (v!=nullptr)
          s+=v->ToString();

      }
    return s;
  }

  bool Abstract_Named_Object::empty() const
  {
    return (getEnvironment()==nullptr&&
            idName().empty()&&
            Tip().empty()&&
            WhatThis().empty());

  }

  std::set<std::string> Abstract_Named_Object::mySuperClasses() const
  {
    return SuperClasses();
  }

  Abstract_Named_Object *Abstract_Named_Object::CreateObject(const std::string &text, std::size_t &cursor) const
  {
    auto tmp=create();
    auto out=tmp->ToObject(text,cursor);
    if (out==nullptr)
      delete tmp;
    return out;
  }

  std::string Abstract_Named_Object::myClass() const
  {
    return ClassName();
  }


}




#ifdef MACRO_TEST

#include "Tests/TESTS.h"
#include "Tests/ElementaryTest.h"




#endif //MACRO_TEST

