#include "Markov_Object/Environment.h"
#include "Markov_Object/Measurement_Unit.h"
#include "Markov_Object/SimpleVariable.h"
#include "Markov_Object/SimpleVariableValue.h"


namespace Markov_Object {




  const Measurement_Unit *Environment::U(const std::string &unitAbreviation) const
  {
    auto it=units_.find(unitAbreviation);
    if (it!=units_.end())
      return it->second;
    else return nullptr;
  }

  const Abstract_Named_Object *Environment::V(const std::string &variablename) const
  {
    auto it=variables_.find(variablename);
    if (it!=variables_.end())
      {
        Abstract_Named_Object* v=it->second;
        return v;
      }
    else return nullptr;
  }

  std::set<std::string> Environment::Variables() const
  {
    std::set<std::string> o;
    for (auto m:variables_)
      {
        if (dynamic_cast<Abstract_Value_Object*>(m.second)!=nullptr)
          o.insert(m.first);

      }
    return o;
  }

  void Environment::addUnit(Measurement_Unit *u)
  {
    auto it=units_.find(u->idName());
    if(it!=units_.end())
      {
        if (it->second==u)
          return;
        delete it->second;
      }
    units_[u->idName()]=u;
  }

  void Environment::addVariable(Abstract_Named_Object *v)
  {
    auto it=variables_.find(v->idName());
    if(it!=variables_.end())
      {
        if (it->second==v)
          return;
        delete it->second;
      }
    variables_[v->idName()]=v;
  }

  void Environment::add(Abstract_Named_Object *v)
  {
    if (v->myClassInfo().superClasses.count(Measurement_Unit::ClassName())!=0)
      {
        Measurement_Unit* u=dynamic_cast<Measurement_Unit*>(v);
        addUnit(u);
      }
    else
      {
        addVariable(v);
      }
  }

  Abstract_Object *Environment::create(std::string classname)
  {
    auto it=classes_.find(classname);
    if (it!=classes_.end())
      return it->second->create();
    else
      return nullptr;

  }


  bool Environment::doesDynCast(const Abstract_Object *o, std::string classname)
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

  return units_.empty()&&variables_.empty();
}


Environment::Environment()
  :
    units_{},
    variables_{},
    classes_{}
{
  classes_[Measurement_Unit::ClassName()]=new Measurement_Unit;
  classes_[SimpleVariable<double>::ClassName()]=new SimpleVariable<double>;
  classes_[SimpleVariable<std::size_t>::ClassName()]=new SimpleVariable<std::size_t>;
  classes_[SimpleVariableValue<double>::ClassName()]=new SimpleVariableValue<double>;
  classes_[SimpleVariableValue<std::size_t>::ClassName()]=new SimpleVariableValue<std::size_t>;
}

Environment::~Environment()
{
  for (auto it:units_)
    delete it.second;
  for (auto it:variables_)
    delete it.second;
  for (auto it:classes_)
    delete it.second;
}


}
