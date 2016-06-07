#include "Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_Console/Markov_CommandManager.h"
#include "Markov_IO/VarTempl.h"




#include "Markov_LA/matrixSum.h"

namespace Markov_IO_New {

  //  bool Implements_Data_Type_New<std::map<std::string, ABC_Var_New *> >::get(std::map<std::string, ABC_Var_New *> &v, ABC_Input *istream, const Implements_ComplexVar_New *cm, std::string *whyNot, const std::string &masterObjective) const
  //  {
  //    char c;
  //    const Implements_Data_Type_New<ABC_Var_New*>* etype=this->getElementDataType(cm);
  //    if (etype==nullptr)
  //      return false;
  //    while (!istream->nextCharIs('\n',c)){}
  //    if (!istream->nextCharIs('{',c))
  //      {
  //        *whyNot= masterObjective+": expected { found"+c;
  //        return false;
  //      }
  //    else
  //      {
  //        while (!istream->nextCharIs('}'))
  //          {
  //            ABC_Var_New* d;
  //            if (etype->get(d,istream,cm,whyNot,masterObjective))
  //              {
  //                v.insert({d->id(),d});
  //              }
  //            else
  //              return false;
  //          }
  //        if (isValueInDomain(cm,v,whyNot,masterObjective))
  //          return true;
  //        else
  //          return false;
  //      }

  //  }




  buildByToken<std::string> *Implements_Data_Type_New<std::string>::getBuildByToken(const StructureEnv_New *cm) const
  {
    return new buildByToken<std::string>(cm,this);
  }


  namespace _private {





    bool Implements_Data_Type_New_ABC_Data_New::putValue
    (const StructureEnv_New *cm
     , const ABC_Data_New *v
     , ABC_Output *ostream
     , std::string *whyNot
     , const std::string &masterObjective) const
    {
      if (isDataInDomain(cm,v,whyNot,masterObjective))
        {
          ostream->put(v->myType()+"=");
          const ABC_Type_of_Value* t=cm->idToType(v->myType(),whyNot,masterObjective);
          if (t==nullptr)
            return false;
          else
            {
              return t->putData(cm,v,ostream,whyNot,masterObjective);
            }
        }
      else return false;
    }

    //    bool Implements_Data_Type_New_ABC_Data_New::getValue(const StructureEnv_New *cm, ABC_Data_New *&v, ABC_Input *istream, std::string *whyNot, const std::string &masterObjective) const
    //    {
    //      std::string ids;
    //      std::string vars;
    //      std::string tip;
    //      std::string whatthis;
    //      char c;
    //      if (istream->nextCharIs('#',false))
    //        {
    //          if (!istream->nextCharIs('"',c))
    //            {
    //              *whyNot=masterObjective+": sintax error in tip: initial \" is absent";
    //              return false;
    //            }
    //          else
    //            {
    //              while((!istream->nextCharIs('"',false))
    //                    &&((!istream->nextCharIs('\n',c))))
    //                tip.push_back(c);
    //              while (c!='\n')
    //                istream->get(c);
    //            }
    //          if ((istream->nextCharIs('#',false))&&(istream->nextCharIs('#',false)))
    //            {
    //              if (!istream->nextCharIs('"',c))
    //                {
    //                  *whyNot=masterObjective
    //                      +": sintax error in whatthis: initial \" is absent";
    //                  return false;
    //                }
    //              else
    //                {
    //                  while(!istream->nextCharIs('"',c))
    //                    whatthis.push_back(c);
    //                  while (c!='\n')
    //                    istream->get(c);
    //                }

    //            }
    //        }
    //      if (!this->idType_->getValue(cm,ids,istream,whyNot,masterObjective))
    //        return false;
    //      else
    //        {
    //          if(!varType_->getValue(cm,vars,istream,whyNot,masterObjective))
    //            return false;
    //          else
    //            {
    //              auto va=cm->idToType(vars,whyNot,masterObjective);
    //              if (va==nullptr)
    //                return false;
    //              else
    //                {
    //                  ABC_Data_New* val;
    //                  if (!va->getData(cm,val,istream,whyNot,masterObjective))
    //                    return false;
    //                  else
    //                    {
    //                      v=va->getVar(cm,ids,vars,tip,whatthis,val);
    //                      return true;
    //                    }
    //                }
    //            }

    //        }

    //    }


    Implements_Data_Type_New_ABC_Data_New::~Implements_Data_Type_New_ABC_Data_New(){}













    template class Implements_Data_Type_New_M_Matrix<double>;

    template class Implements_Data_Type_New_M_Matrix<std::size_t>;

    Implements_Data_Type_New_Implements_Var::Implements_Data_Type_New_Implements_Var(Implements_Identifier *idType, Implements_Data_Type_New<ABC_Data_New *> *dataType, Implements_Data_Type_New_Implements_Var::typePredicate comply, Implements_Data_Type_New_Implements_Var::elemType getElement, Implements_Data_Type_New_Implements_Var::keyType getKey)
      :idType_(idType),dataType_(dataType),comply_(comply)
      ,getKey_(getKey),getElement_(getElement){}


    //    bool Implements_Data_Type_New_StructureEnv::getData(const StructureEnv_New *cm, StructureEnv_New* v, ABC_Input *istream, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) const
    //    {
    //      char c;


    //      const Implements_Data_Type_New<ABC_Data_New*>* etype=this->getElementDataType(cm);
    //      if (etype==nullptr)
    //        return false;
    //      while (!istream->nextCharIs('\n',true)){}
    //      if (!istream->nextCharIs('{',c))
    //        {
    //          *whyNot= masterObjective+": expected { found"+c;
    //          return false;
    //        }
    //      else
    //        {
    //          while (!istream->nextCharIs('}',false))
    //            {

    //              std::string name;

    //              ABC_Data_New* d;
    //              if (!etype->get(cm,d,istream,whyNot,masterObjective))
    //                return false;
    //              else
    //                {
    //                  v.insert({d->id(),d});
    //                }
    //            }
    //          if (!this->isValueInDomain(cm,v,whyNot,masterObjective))
    //            return false;
    //          else
    //            return true;
    //        }

    //    }

    //    buildByToken<StructureEnv_New*> *Implements_Data_Type_New_StructureEnv::getBuildByToken(const StructureEnv_New *cm) const
    //    {
    //      return new buildByToken<StructureEnv_New*>(cm,this);
    //    }

    //    bool Implements_Data_Type_New_StructureEnv::putValue
    //    (const StructureEnv_New *cm
    //     , const StructureEnv_New* &v
    //     , ABC_Output *ostream
    //     , std::__cxx11::string *whyNot
    //     , const std::__cxx11::string &masterObjective) const
    //    {
    //      if (this->isDataInDomain(cm,v,whyNot,masterObjective))
    //        {
    //          const Implements_Data_Type_New<ABC_Data_New*>* etype
    //              =this->getElementDataType(cm);
    //          ostream->put("\n{");
    //          const_iterator* it;
    //          for (it=begin(); *it!=*end();++*it)
    //            {
    //              auto itv=v.find((**it)->id());
    //              if (itv!=v.end())
    //                if(!etype->put(cm,itv->second,ostream,whyNot,masterObjective))
    //                  {
    //                    ostream->put(*whyNot);
    //                    return false;
    //                  }
    //            }
    //          delete it;
    //          ostream->put("}");
    //          return true;
    //        }
    //      else
    //        return false;
    //    }
















  };







  void StructureEnv_New::reset()
  {
    ids_.clear();
    all_.clear();
    allId_.clear();
    vars_.clear();
    types_.clear();
    cmds_.clear();
  }

  std::__cxx11::string StructureEnv_New::myType() const
  {
    return structType_;
  }

  const StructureEnv_New *StructureEnv_New::parent() const
  {
    return p_;
  }

  const ABC_Data_New *StructureEnv_New::idToValue(const std::__cxx11::string &name, const std::__cxx11::string &typeName, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) const
  {
    auto it=vars_.find(name);
    if (it!=vars_.end())
      {
        ABC_Data_New* v=it->second;
        if (v->isOfThisType(this,typeName,whyNot,masterObjective))
          return v;
        else return nullptr;
      }
    else if (parent()!=nullptr)
      return  parent()->idToValue(name, typeName,whyNot,masterObjective);
    else
      {
        if (whyNot!=nullptr)
          *whyNot=masterObjective+": "+name+" is not a var";
        return nullptr;
      }
  }





  const ABC_Data_New *StructureEnv_New::idToValue(const std::__cxx11::string &name, std::__cxx11::string *whyNot) const
  {
    auto it=vars_.find(name);
    if (it!=vars_.end())
      return it->second;
    else if (parent()!=nullptr)
      return  parent()->idToValue(name, whyNot);
    else
      {
        if (whyNot!=nullptr)
          *whyNot=name+" is not a var ";
        return nullptr;
      }
  }

  std::string StructureEnv_New::dataToId(const ABC_Data_New* data, std::__cxx11::string *whyNot, const std::string& objective) const
  {
    auto it=allId_.find(data);
    if (it!=allId_.end())
      return it->second;
    else if (parent()!=nullptr)
      return  parent()->dataToId(data, whyNot,objective);
    else
      {
        if (whyNot!=nullptr)
          *whyNot=objective+": data has no id ";
        return {};
      }
  }

  std::__cxx11::string StructureEnv_New::Tip(const std::__cxx11::string &id) const
  {
    auto it=idTipWt_.find(id);
    if (it!=idTipWt_.end())
      return it->second.first;
    else return {};
  }

  std::__cxx11::string StructureEnv_New::WhatThis(const std::__cxx11::string &id) const
  {
    auto it=idTipWt_.find(id);
    if (it!=idTipWt_.end())
      return it->second.second;
    else return {};
  }

  ABC_Data_New *StructureEnv_New::idToValue(const std::__cxx11::string &name, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObective)
  {
    auto it=vars_.find(name);
    if (it!=vars_.end())
      return it->second;
    else
      {
        if (whyNot!=nullptr)
          *whyNot=masterObective+": "+name+" is not a var";
        return nullptr;
      }
  }

  const ABC_Type_of_Value *StructureEnv_New::idToType(const std::__cxx11::string &name, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) const
  {
    auto it=types_.find(name);
    if (it!=types_.end())
      return it->second;
    else if (parent()!=nullptr)
      return  parent()->idToType(name,whyNot,masterObjective);
    else
      {
        if (whyNot!=nullptr)
          *whyNot=masterObjective+": "+name+" is not a type ";
        return nullptr;
      }

  }

  ABC_Type_of_Value *StructureEnv_New::idToType(const std::__cxx11::string &name, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective)
  {
    const std::string objective=masterObjective+": "+name+" is not a type";
    auto it=types_.find(name);
    if (it!=types_.end())
      return it->second;
    else
      {
        if (whyNot!=nullptr)
          *whyNot=objective;
        return nullptr;
      }

  }

  const Implements_Command_Type_New *StructureEnv_New::idToCommand(const std::__cxx11::string &name, std::__cxx11::string *whyNot, const std::__cxx11::string &masterobjective) const
  {
    auto it=cmds_.find(name);
    if (it!=cmds_.end())
      return it->second;
    else if (this->parent()!=nullptr)
      return  parent()->idToCommand(name, whyNot,masterobjective);
    else
      {
        *whyNot=name+" is not a command ";
        return nullptr;
      }
  }

  bool StructureEnv_New::hasName(const std::__cxx11::string &name, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective, bool recursive) const
  {
    const std::string objective=masterObjective+ ": "+name+"is not present ";
    if (all_.find(name)!=all_.end())
      {
        return true;
      }
    else if ((!recursive)|| (parent()==nullptr))
      {
        *whyNot=objective;
        return false;
      }
    else return parent()->hasName(name, whyNot,objective,recursive);
  }

  bool StructureEnv_New::isNameUnOcuppied(const std::__cxx11::string &name, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective, bool recursive) const
  {
    auto it=all_.find(name);
    if (it!=all_.end())
      {
        const ABC_Data_New* v=it->second;
        *whyNot=masterObjective+": "+name+" is currently a"+v->myType();
        return false;
      }
    else if (recursive&&(parent()!=nullptr))
      return parent()->isNameUnOcuppied(name,whyNot,masterObjective,recursive);
    else
      return true;
  }

  bool StructureEnv_New::hasType(const std::__cxx11::string &name, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective, bool recursive) const
  {
    const std::string objective=masterObjective+ ": "+name+"is not present ";
    if (types_.find(name)!=types_.end())
      {
        return true;
      }
    if (!recursive||(parent()==nullptr))
      {
        if (whyNot!=nullptr)
        *whyNot=objective;
        return false;
      }
    else return parent()->hasType(name, whyNot,objective,recursive);
  }

  bool StructureEnv_New::hasCommand(const std::__cxx11::string &name, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective, bool recursive) const
  {if (cmds_.find(name)!=cmds_.end())
      {
        return true;
      }
    if (!recursive||(parent()==nullptr))
      {
        *whyNot=masterObjective;
        return false;
      }
    else return parent()->hasCommand(name,whyNot,masterObjective,recursive);
  }

  Implements_Var StructureEnv_New::popVar()
  {
    Implements_Var iv;
    iv.id=std::move(ids_.back());
    ids_.pop_back();
    iv.data=all_[iv.id];
    all_.erase(iv.id);
    auto itv=vars_.find(iv.id);
    if (itv!=vars_.end())
      {
        vars_.erase(itv);
      }
    else
      {
        auto itt=types_.find(iv.id);
        if (itt!=types_.end())
          types_.erase(itt);
        else
          {
            auto itc=cmds_.find(iv.id);
            if (itc!=cmds_.end())
              cmds_.erase(itc);
          }
      }
     auto itw=this->idTipWt_.find(iv.id);
     if (itw!=idTipWt_.end())
       {
         iv.Tip=itw->second.first;
         iv.WhatThis=itw->second.second;
         idTipWt_.erase(itw);
       }
     return iv;

  }

  void StructureEnv_New::pushVar(const std::__cxx11::string &id, ABC_Data_New *var, std::__cxx11::string tip, std::__cxx11::string whatthis)
  {
    if (all_.find(id)!=all_.end())
      delete all_[id];
    else
      ids_.push_back(id);
    all_[id]=var;
    vars_[id]=var;
    idTipWt_[id]={tip,whatthis};
  }

  void StructureEnv_New::pushType(const std::__cxx11::string &id, ABC_Type_of_Value *tvar, std::__cxx11::string tip, std::__cxx11::string whatthis)
  {
    ;
    if (all_.find(id)!=all_.end())
      delete all_[id];
    else
      ids_.push_back(id);
    all_[id]=tvar;
    types_[id]=tvar;
    idTipWt_[id]={tip,whatthis};
  }

  void StructureEnv_New::pushCommand(const std::__cxx11::string &id, Implements_Command_Type_New *cmd, std::__cxx11::string tip, std::__cxx11::string whatthis)
  {
    ;
    if (all_.find(id)!=all_.end())
      delete all_[id];
    else
      ids_.push_back(id);
    all_[id]=cmd;
    cmds_[id]=cmd;
    idTipWt_[id]={tip,whatthis};
  }


  StructureEnv_New::StructureEnv_New(const StructureEnv_New *parent, const std::__cxx11::string &myType):
    p_(parent),structType_(myType),ids_(),all_(),vars_(),types_(),cmds_()
  {

  }

  std::map<std::__cxx11::string, ABC_Data_New *> &StructureEnv_New::getVars()
  {
    return vars_;
  }

  const std::map<std::__cxx11::string, ABC_Data_New *> &StructureEnv_New::getVars() const
  {
    return vars_;
  }

  std::map<std::__cxx11::string, ABC_Type_of_Value *> &StructureEnv_New::getTypes()
  {
    return types_;
  }

  const std::map<std::__cxx11::string, ABC_Type_of_Value *> &StructureEnv_New::getTypes() const
  {
    return types_;
  }

  std::map<std::__cxx11::string, Implements_Command_Type_New *> &StructureEnv_New::getCommands()
  {
    return cmds_;
  }

  const std::map<std::__cxx11::string, Implements_Command_Type_New *> &StructureEnv_New::getCommands() const
  {
    return cmds_;
  }

  bool StructureEnv_New::isOfThisType(const StructureEnv_New *cm, const std::__cxx11::string &generalType, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) const
  {
    if (myType()==generalType)
      return true;
    else
      {
        auto gTp
            =cm->idToType(generalType,whyNot,masterObjective);
        if (gTp==nullptr)
          return false;
        else
          return gTp->includesThisType(cm,generalType,whyNot,masterObjective);
      }

  }

  std::set<std::string> Implements_Identifier::alternativeNext(const StructureEnv_New *cm) const
  {
    std::set<std::string> o;
    if (isFixed_)
      o.insert(name_);
    else
      {
        if (isVar_)
          {
            if (isNew_)
              {
                o.insert(alternatives::newIdentifier());
                std::string varType="";
                if (!name_.empty())
                  varType=name_;
                auto sv= cm->getIdsOfVarType(varType,false);
                auto st=cm->getIdsOfTypeType(varType,true);
                for (auto& e:sv)
                  {
                    o.insert(Identifier::nextId(e));
                  }
                for (auto& e:st)
                  {
                    std::string s="my"+e;
                    std::string w;
                    if (cm->isNameUnOcuppied(s,&w,"",true))
                      alternatives::insert(o,s,e);
                  }
              }
            if (isUsed_)
              {

                std::string varType="";
                if (!name_.empty())
                  varType=name_;
                std::set<std::string> o2=
                    cm->getIdsOfVarType(varType,true);
                o.insert(o2.begin(),o2.end());
              }
          }

        if (isType_)
          {
            if (isNew_)
              {
                o.insert("<an unoccupied identifier>");
                std::string varType=name_;
                auto st=cm->getIdsOfTypeType(varType,true);
                for (auto& e:st)
                  {
                    o.insert(Identifier::nextId(e));
                  }
                for (auto& e:st)
                  {
                    std::string s="my"+e;
                    std::string w;
                    if (cm->isNameUnOcuppied(s,&w,"",true))
                      o.insert(s);
                  }
              }
            if (isUsed_)
              {
                std::string varType=name_;
                std::set<std::string> o2= cm->getIdsOfTypeType(varType,true);
                o.insert(o2.begin(),o2.end());
              }

          }
        if (isCommand_)
          {
            std::string commandType=name_;
            std::set<std::string> o2= cm->getIdsOfCmdType(commandType,true);
            o.insert(o2.begin(),o2.end());

          }
      }
    return o;
  }


  bool Implements_Identifier::isValueInDomain(const StructureEnv_New *cm, const std::string &idCandidate, std::string *whyNot, const std::string &objective) const
  {
    if (isFixed_)
      {
        if (idCandidate!=name_)
          {
            *whyNot=objective+": candiate "+idCandidate+"is not "+name_;
            return false;
          }
        else return true;
      }
    else
      if (isNew_&!isUsed_)
        {
          return cm->isNameUnOcuppied(idCandidate,whyNot,objective,false);
        }
      else if (isNew_)
        {
          if (Token_New::toKeyword(idCandidate)!=Token_New::IDENTIFIER)
            {
              *whyNot=objective+": "+idCandidate+" is not an identifier";
              return false;
            }
          else
            return true;
        }
      else if (name_.empty())
        {
          if (isVar_)
            {
              if (cm->hasName(idCandidate,whyNot,objective,true ))
                return true;
            }
          if (isType_)
            {
              if (cm->hasType(idCandidate,whyNot,objective,true ))
                return true;

            }
          if (isCommand_)
            {
              if (cm->hasCommand(idCandidate,whyNot,objective,true ))
                return true;
            }
          return false;
        }
      else if (isCommand_)
        return cm->hasCommand(idCandidate,whyNot,objective,true );
      else
        {
          std::string varType=name_;
          if (isVar_)
            return cm->hasNameofType(
                  idCandidate,varType,whyNot,objective,true);
          else if (isType_)
            return cm->hasTypeofType(
                  idCandidate,varType,whyNot,objective,true );
          else return false;
        }

  }



  std::string Implements_Identifier::toId
  (const std::string& name,
   bool isFixed,bool isVar, bool isType,
   bool isCommand,bool isNew, bool isUsed)
  {
    std::string id="_id";
    if (isFixed)
      {
        id+="Is"+name;
      }

    else
      {
        if (isVar&!isType)
          {
            id+="Var";
          }
        if (isType&!isVar)
          {
            id+="Typ";
          }
        if (isCommand)
          {
            id+="Cmd";
          }
        if (isNew&&!isUsed)
          {
            id+="New";
          }
        if (!isNew&&isUsed)
          {
            id+="Used";
          }
        if (!name.empty())
          {
            id+=name;
          }
      }
    return id;
  }

  void Real::push_Types(Markov_CommandManagerVar *cm)
  {
    cm->pushType(Cls<double>::name(),new Implements_Data_Type_New<double>(),"real number","a regular real number");
    cm->pushType<types::nonZero>();
  }


  template<typename T>
  void Matrix::push_Types(Markov_CommandManagerVar *cm)
  {
    cm->pushType(new vType<T>(cm));
  }

  void Identifier::push_Types(Markov_CommandManagerVar *cm)
  {
    cm->pushType<Identifier::types::idVar>();
    cm->pushType<Identifier::types::idVarNew>();
    cm->pushType<Identifier::types::idVarUsed>();
    cm->pushType<Identifier::types::idType>();
    cm->pushType<Identifier::types::idCmd>();
  }

  ABC_Type_of_Value::ABC_Type_of_Value():
    env_(new StructureEnv_New)
  {

  }



  // template Matrix<double>;
  // template Matrix<std::size_t>;




};
