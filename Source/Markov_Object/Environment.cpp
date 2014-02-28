#include "Markov_Object/Environment.h"
#include "Markov_Object/Abstract_Object.h"
#include "Markov_Object/Abstract_Variable_Object.h"
#include "Markov_Object/Abstract_Value_Object.h"
#include "Markov_Object/Measurement_Unit.h"
#include "Markov_Object/SimpleVariable.h"
#include "Markov_Object/SimpleVariableValue.h"
#include "Markov_Object/Quantity.h"


namespace Markov_Object {




  const Measurement_Unit *Environment::U(const std::string &unitAbreviation) const
  {
    auto it=idNames_.find(unitAbreviation);
    if (it!=idNames_.end())
        if (it->second->myClassInfo().superClasses.count(Measurement_Unit::ClassName())!=0)
          return dynamic_cast<const Measurement_Unit*> (it->second);
    return nullptr;
  }

  const Abstract_Named_Object *Environment::idN(const std::string &variablename) const
  {
    auto it=idNames_.find(variablename);
    if (it!=idNames_.end())
      return it->second;
    else return nullptr;

  }

  const Abstract_Variable_Object *Environment::V(const std::string &variablename) const
  {
    auto it=idNames_.find(variablename);
    if (it!=idNames_.end())
        if (it->second->belongsTo(Abstract_Variable_Object::ClassName()))
          return dynamic_cast<const Abstract_Variable_Object*> (it->second);
    return nullptr;
  }

  const Quantity *Environment::Q(const std::string &quantityName) const
  {
    auto it=idNames_.find(quantityName);
    if (it!=idNames_.end())
        if (it->second->belongsTo(Quantity::ClassName()))
          return dynamic_cast<const Quantity*> (it->second);
    return nullptr;

  }

  std::set<std::string> Environment::idNames() const
  {
    std::set<std::string> o;
    for (auto m:idNames_)
      {
        if (m.second!=nullptr)
          o.insert(m.first);

      }
    return o;

  }

  std::set<std::string> Environment::Variables() const
  {
    std::set<std::string> o;
    for (auto m:idNames_)
      {
        if ((m.second!=nullptr)&&(m.second->belongsTo(Abstract_Variable_Object::ClassName())))
          o.insert(m.first);
      }
    return o;
  }

  std::set<std::string> Environment::Magnitudes() const
  {
    std::set<std::string> o;
    for (auto m:idNames_)
      {
        if ((m.second!=nullptr)&&(m.second->belongsTo(Quantity::ClassName())))
          o.insert(m.first);
      }
    return o;

  }

  void Environment::add(Abstract_Named_Object *u)
  {
    auto it=idNames_.find(u->idName());
    if(it!=idNames_.end())
      {
        if (it->second==u)
          return;
        delete it->second;
      }
    idNames_[u->idName()]=u;
  }


  Abstract_Object*Environment::create(std::string classname)
  {
    auto it=classes_.find(classname);
    if (it!=classes_.end())
      return it->second->create();
    else
      return nullptr;

  }


  bool Environment::doesDynCast(const Abstract_Object*o, std::string classname)
  {
    // concrete classes
    auto it=classes_.find(classname);
    if (it!=classes_.end())
      {
        const Abstract_Object* c=it->second;
        return c->dynamicCast(o)!=nullptr;
      }
    else
      // Abstract classes one by one
      if (classname==Abstract_Object::ClassName())
        return dynamic_cast<const Abstract_Object*>(o)!=nullptr;
      else if (classname==Abstract_Valued_Object::ClassName())
        return dynamic_cast<const Abstract_Valued_Object*>(o)!=nullptr;
      else if (classname==Abstract_Value_Object::ClassName())
        return dynamic_cast<const Abstract_Value_Object*>(o)!=nullptr;
      else if (classname==Abstract_Variable_Object::ClassName())
        return dynamic_cast<const Abstract_Variable_Object*>(o)!=nullptr;
      else return false;

  }

  std::set<std::string> Environment::getSuperClasses(const std::string &classname)
  {
    // concrete classes
    Abstract_Object* o=create(classname);
    std::set<std::string> s;
    for (auto it:classes_)
      {
        const Abstract_Object* v=it.second;
        if (v->dynamicCast(o))
          s.insert(it.first);
      }
    // Abstract classes one by one
    if (dynamic_cast<const Abstract_Object*>(o)!=nullptr)
      s.insert(Abstract_Object::ClassName());
    if (dynamic_cast<const Abstract_Valued_Object*>(o)!=nullptr)
      s.insert(Abstract_Valued_Object::ClassName());
    if (dynamic_cast<const Abstract_Value_Object*>(o)!=nullptr)
      s.insert(Abstract_Value_Object::ClassName());
    if (dynamic_cast<const Abstract_Variable_Object*>(o)!=nullptr)
      s.insert(Abstract_Variable_Object::ClassName());
    if (dynamic_cast<const Abstract_Named_Object*>(o)!=nullptr)
      s.insert(Abstract_Named_Object::ClassName());

    return s;
  }

  bool Environment::empty() const
  {

    return idNames_.empty();
  }


  Environment::Environment()
    :
      idNames_{},
      classes_{}
  {
    classes_[Measurement_Unit::ClassName()]=new Measurement_Unit;
    classes_[SimpleVariable<double>::ClassName()]=new SimpleVariable<double>;
    classes_[SimpleVariable<std::size_t>::ClassName()]=new SimpleVariable<std::size_t>;
    classes_[SimpleVariableValue<double>::ClassName()]=new SimpleVariableValue<double>;
    classes_[SimpleVariableValue<std::size_t>::ClassName()]=new SimpleVariableValue<std::size_t>;
    classes_[Quantity::ClassName()]=new Quantity;
    classes_[QuantityExpression::ClassName()]=new QuantityExpression;

  }

  Environment::~Environment()
  {
    for (auto it:idNames_)
      delete it.second;
    for (auto it:classes_)
      delete it.second;
  }


}
