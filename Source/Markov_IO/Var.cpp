#include "Markov_IO/Var.h"
#include "Markov_IO/buildByToken.h"

namespace Markov_IO_New {

  bool Implements_ComplexVar_New::hasNameofType(const std::__cxx11::string &name, const std::__cxx11::string &type, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) const
  {
    auto it=vars_->find(name);
    if (it==vars_->end())
      {
        if(parent()==nullptr)
          {
            *whyNot=masterObjective+": "+name+" is not a name in "+this->id();
            return false;
          }
        else return parent()->hasNameofType(name, type,whyNot,masterObjective);
      }
    else
      {
        auto t=parent()->idToType(type,whyNot,masterObjective);
        if (t==nullptr)
          return false;
        else
          {
            const ABC_Var_New* v=it->second;
            return t->isInDomain(parent(),v->value(),whyNot);
          }
      }

  }

  std::set<std::__cxx11::string> Implements_ComplexVar_New::getIdsOfType(const std::__cxx11::string &varType) const
  {
    std::string whyNot;
    std::string objective;
    if (varType.empty())
      return getMapKeys(*vars_);
    else
      {
        const ABC_Type_of_Value* t=idToType(varType,&whyNot,objective);
        std::set<std::string> s;
        for (const auto &p:*vars_)
          {
            ABC_Var_New* var=p.second;
            std::string why;
            if (t->isInDomain(this,var->value(),&why))
              s.insert(var->id());
          }
        return s;
      }
  }




  ABClass_buildByToken<ABC_Var_New *> *Implements_Var_Data_Type::getBuildByToken(const Implements_ComplexVar_New *cm, std::__cxx11::string *whyNot, const std::__cxx11::string masterObjective) const
  {
    return new buildABC_Var(cm,this);
  }

  buildByToken<std::__cxx11::string> *Implements_Var_Data_Type::getNewIdentifierBuildByToken(const Implements_ComplexVar_New *cm) const
  {
    //return buildByToken<std::string>(cm,Implements_New_Identifier_Type_New(cm));
  }

  Implements_Identifier_Type_New::Implements_Identifier_Type_New(const Implements_ComplexVar_New *parent, const std::__cxx11::string &varTypeOfId, Implements_Data_Type_New::typePredicate complyPred, Implements_Data_Type_New::typeValue defaultValue, Implements_Data_Type_New::getSet alterNext):
    Implements_Data_Type_New<std::string>(parent,"id_"+varTypeOfId,ClassName()
                                          ,"id of a "+varTypeOfId,"",complyPred,defaultValue,alterNext)
  {
    G::pushTypeOfId(this,varTypeOfId);
  }

  void Implements_ComplexVar_New::G::pushTypeOfId(Implements_ComplexVar_New *self, std::__cxx11::string belongType)
  {
    self->pushChild(new Implements_Var_New<std::string>(
                      self,F::belongingType()
                      ,Implements_Type_Identifier_Type_New::ClassName(),
                      std::move(belongType),
                      "",""));

  }

  void Implements_ComplexVar_New::G::pushTypeOfElement(Implements_ComplexVar_New *self, std::__cxx11::string typeOfElement)
  {
    self->pushChild(new Implements_Var_New<std::string>(
                      self,F::elementType()
                      ,Implements_Type_Identifier_Type_New::ClassName(),
                      std::move(typeOfElement),
                      "",""));

  }

  void Implements_ComplexVar_New::G::pushTypeOfKey(Implements_ComplexVar_New *self, std::__cxx11::string typeOfKey)
  {
    self->pushChild(new Implements_Var_New<std::string>(
                      self,F::keyType()
                      ,Implements_Type_Identifier_Type_New::ClassName(),
                      std::move(typeOfKey),
                      "",""));

  }









  template<typename T>
  Implements_Data_Type_New<std::vector<T> >::Implements_Data_Type_New(const Implements_ComplexVar_New *parent, const std::__cxx11::string &id, const std::__cxx11::string &var, const std::__cxx11::string &tip, const std::__cxx11::string &whatthis, const std::__cxx11::string elementVar, Implements_Data_Type_New<std::vector<T> >::typePredicate complyPred, Implements_Data_Type_New<std::vector<T> >::typeValue defaultValue):
    ABC_Typed_Value<std::vector<T> >(parent,id,var,tip,whatthis)
  ,comply_(complyPred)
  ,default_(defaultValue)
  {
    Implements_ComplexVar_New::G::pushTypeOfElement(this,elementVar);
  }







}
