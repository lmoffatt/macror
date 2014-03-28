#include "Markov_Object/Environment.h"
#include "Markov_Object/Abstract_Object.h"
#include "Markov_Object/Abstract_Variable_Object.h"
#include "Markov_Object/Abstract_Value_Object.h"
#include "Markov_Object/Measurement_Unit.h"
#include "Markov_Object/SimpleVariable.h"
#include "Markov_Object/SimpleVariableValue.h"
#include "Markov_Object/Quantity.h"


namespace Markov_Object {





  std::shared_ptr< Abstract_Named_Object> Environment::idN(const std::string &variablename,
                                                           const std::string & className)
  {
    if (className==Quantity::ClassName())
      {
        auto it=Q_.find(variablename);
        if (it!=Q_.end())
          return it->second;
        else
          return nullptr;
      }
    else if (className==Measurement_Unit::ClassName())
      {
        auto it=U_.find(variablename);
        if (it!=U_.end())
          return it->second;
        else
          return nullptr;
      }
    else if (className==Abstract_Variable_Object::ClassName())
      {
        auto it=V_.find(variablename);
        if (it!=V_.end())
          return it->second;
        else
          return nullptr;
      }
    else
      return nullptr;
  }

  std::shared_ptr<const Abstract_Named_Object> Environment::idN(const std::string &variablename) const
  {
    auto n= variablename.find("::");
    if (n!=variablename.npos)
      {
        return idN(variablename.substr(0,n),variablename.substr(n+1));
      }
    else
      {
        auto it=V_.find(variablename);
        if (it!=V_.end())
          return it->second;
        else return std::shared_ptr<const Abstract_Named_Object>();
      }
  }

  std::shared_ptr<Measurement_Unit> Environment::U(const std::string &unitAbreviation)
  {
    auto it=U_.find(unitAbreviation);
    if (it!=U_.end())
      if (it->second->mySuperClasses().superClasses.count(Measurement_Unit::ClassName())!=0)
        return it->second;
    return nullptr;
  }


  std::shared_ptr<const Measurement_Unit> Environment::U(const std::string &unitAbreviation)const
  {
    auto it=U_.find(unitAbreviation);
    if (it!=U_.end())
      if (it->second->mySuperClasses().superClasses.count(Measurement_Unit::ClassName())!=0)
        return it->second;
    return nullptr;
  }

  std::shared_ptr<Abstract_Variable_Object> Environment::V(const std::string &variablename)
  {
    auto it=V_.find(variablename);
    if (it!=V_.end())
      if (it->second->belongsTo(Abstract_Variable_Object::ClassName()))
        return std::dynamic_pointer_cast< Abstract_Variable_Object> (it->second);
    return nullptr;
  }

  std::shared_ptr<Quantity> Environment::Q(const std::string &quantityName)
  {
    auto it=Q_.find(quantityName);
    if (it!=Q_.end())
      if (it->second->belongsTo(Quantity::ClassName()))
        return it->second;
    return nullptr;

  }

  std::shared_ptr<const Quantity> Environment::Q(const std::string &quantityName)const
  {
    auto it=Q_.find(quantityName);
    if (it!=Q_.end())
      return it->second;
    return nullptr;

  }

  std::shared_ptr<Measurement_Unit> Environment::Ud(const ScaledExpression &definition)
  {
    auto it=SU_.find(definition);
    if (it!=SU_.end())
      return it->second;
    return nullptr;
  }


  std::shared_ptr<const Quantity> Environment::Qd(const QuantityExpression &definition) const
  {
    auto it=QQ_.find(definition);
    if (it!=QQ_.end())
      return it->second;
    return nullptr;

  }

  std::shared_ptr< Quantity> Environment::Qd(const QuantityExpression &definition)
  {
    auto it=QQ_.find(definition);
    if (it!=QQ_.end())
      return it->second;
    return nullptr;

  }
  std::shared_ptr<const Measurement_Unit> Environment::Ud(const ScaledExpression &definition)const
  {
    auto it=SU_.find(definition);
    if (it!=SU_.end())
      return it->second;
    return nullptr;
  }



  std::shared_ptr<const Abstract_Variable_Object> Environment::
  V(const std::string &variablename)const
  {
    auto it=V_.find(variablename);
    if (it!=V_.end())
      if (it->second->belongsTo(Abstract_Variable_Object::ClassName()))
        return std::dynamic_pointer_cast< Abstract_Variable_Object> (it->second);
    return nullptr;
  }





  std::set<std::string> Environment::idNames() const
  {
    std::set<std::string> o;
    for (auto m:V_)
      {
        if (m.second!=nullptr)
          o.insert(m.first);

      }
    return o;

  }

  std::set<std::string> Environment::Variables() const
  {
    std::set<std::string> o;
    for (auto m:V_)
      {
        if ((m.second!=nullptr)&&(m.second->belongsTo(Abstract_Variable_Object::ClassName())))
          o.insert(m.first);
      }
    return o;
  }

  std::set<std::string> Environment::Magnitudes() const
  {
    std::set<std::string> o;
    for (auto m:V_)
      {
        if ((m.second!=nullptr)&&(m.second->belongsTo(Quantity::ClassName())))
          o.insert(m.first);
      }
    return o;

  }



  void Environment::add(std::shared_ptr<Abstract_Named_Object> u)
  {
    if (u->belongsTo(Quantity::ClassName()))
      {
        std::shared_ptr<Quantity> q=std::dynamic_pointer_cast<Quantity>(u);
        add(q);

      }
    else if (u->belongsTo(Measurement_Unit::ClassName()))
      {
        std::shared_ptr<Measurement_Unit> mu=std::dynamic_pointer_cast<Measurement_Unit>(u);
        add(mu);
      }
    else{
        V_[u->idName()]=std::dynamic_pointer_cast<Abstract_Variable_Object>(u);
        u->setEnvironment(this);
      }
  }

  void Environment::add(std::shared_ptr<Quantity> q)
  {
    Q_[q->idName()]=q;
    q->setEnvironment(this);

  }

  void Environment::add(std::shared_ptr<Measurement_Unit> m)
  {
    U_[m->idName()]=m;
    m->setEnvironment(this);

  }



  bool Environment::addDef(std::shared_ptr<Quantity> q)
  {
    auto def= q->baseDefinition();
    if (def.empty())
      return false;
    else

      {
        QQ_[def]=q;
        return true;
      }


  }

  bool Environment::addDef(std::shared_ptr<Measurement_Unit> m)
  {
    auto def= m->baseDefinition();
    if (def.empty())
      return false;
    else

      {
        SU_[def]=m;
        return true;
      }


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

    return V_.empty();
  }


  Environment::Environment()
    :
      V_{},
      Q_{},
      U_{},
      QQ_{},
      SU_{},
      classes_{}
  {
    classes_[Measurement_Unit::ClassName()]=new Measurement_Unit;
    classes_[SimpleVariable<double>::ClassName()]=new SimpleVariable<double>;
    classes_[SimpleVariable<std::size_t>::ClassName()]=new SimpleVariable<std::size_t>;
    classes_[SimpleVariableValue<double>::ClassName()]=new SimpleVariableValue<double>;
    classes_[SimpleVariableValue<std::size_t>::ClassName()]=new SimpleVariableValue<std::size_t>;
    classes_[Quantity::ClassName()]=new Quantity;
    classes_[ScaledExpression::ClassName()]=new ScaledExpression;
    classes_[QuantityExpression::ClassName()]=new QuantityExpression;


    add(std::make_shared<Quantity>(
          this,"L","L","distance","dimension of distance and length"));
    add(std::make_shared<Quantity>(
          this,"T","T","time","dimension of elapsed time"));
    add(std::make_shared<Quantity>(
          this,"M","M","mass","dimension of mass"));
    add(std::make_shared<Quantity>(
          this,"VELOCITY","L*T^-1","velocity","derivative of space over time"));
    add(std::make_shared<Quantity>(
          this,"ASCELERATION","VELOCITY*T^-1","asceleration",
          "second derivative of space over time"));
    add(std::make_shared<Quantity>(
          this,"FORCE","M*ASCELERATION","asceleration","second derivative of space over time"));
    add(std::make_shared<Markov_Object::Measurement_Unit>(
          this,"kg",1.0,"kg","M","kilogram","standard Unit of mass"));
    add(std::make_shared<Markov_Object::Measurement_Unit>
        (this,"s",1.0,"s","T","second","standard Unit of time"));
    add(std::make_shared< Markov_Object::Measurement_Unit >
        (this,"N",1.0,"kg*m*s^-2","FORCE","Newton","derived standard Unit of Force"));



  }

  Environment::~Environment()
  {
    for (auto it:classes_)
      delete it.second;
  }


}
