#include "Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_Console/Markov_CommandManager.h"


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
  //        if (isVarInDomain(cm,v,whyNot,masterObjective))
  //          return true;
  //        else
  //          return false;
  //      }

  //  }

  ABC_Type_of_Value::ABC_Type_of_Value(const Implements_ComplexVar_New *parent, const std::__cxx11::string &id, const std::__cxx11::string &var, const std::__cxx11::string &tip, const std::__cxx11::string &whatthis):
    Implements_ComplexVar_New(parent,id,var,tip,whatthis)
  {
    idSelfType_=Identifier::create_IdType_Used(this,id);

  }



  buildByToken<std::__cxx11::string> *Implements_Data_Type_New<std::string>::getBuildByToken(const Implements_ComplexVar_New *cm) const
  {
    return new buildByToken<std::string>(cm,this);
  }


  namespace _private {



    bool Implements_Data_Type_New_ABC_Var_New::isVarInDomain(const Implements_ComplexVar_New *cm, const ABC_Var_New * const val, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) const
    {
      if (this->idType_->isVarInDomain(cm,val->id(),whyNot,masterObjective))
        return false;
      else if (this->varType_->isVarInDomain(cm,val->myType(),whyNot,masterObjective))
        return false;
      else return true;
    }

    bool Implements_Data_Type_New_ABC_Var_New::get(const Implements_ComplexVar_New *cm, ABC_Var_New *&v, ABC_Input *istream, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) const
    {
      std::string ids;
      std::string vars;
      std::string tip;
      std::string whatthis;
      char c;
      if (istream->nextCharIs('#',false))
        {
          if (!istream->nextCharIs('"',c))
            {
              *whyNot=masterObjective+": sintax error in tip: initial \" is absent";
              return false;
            }
          else
            {
              while((!istream->nextCharIs('"',false))
                    &&((!istream->nextCharIs('\n',c))))
                tip.push_back(c);
              while (c!='\n')
                istream->get(c);
            }
          if ((istream->nextCharIs('#',false))&&(istream->nextCharIs('#',false)))
            {
              if (!istream->nextCharIs('"',c))
                {
                  *whyNot=masterObjective
                      +": sintax error in whatthis: initial \" is absent";
                  return false;
                }
              else
                {
                  while(!istream->nextCharIs('"',c))
                    whatthis.push_back(c);
                  while (c!='\n')
                    istream->get(c);
                }

            }
        }
      if (!this->idType_->get(cm,ids,istream,whyNot,masterObjective))
        return false;
      else
        {
          if(!varType_->get(cm,vars,istream,whyNot,masterObjective))
            return false;
          else
            {
              auto va=cm->idToType(vars,whyNot,masterObjective);
              if (va==nullptr)
                return false;
              else
                {
                  ABC_Value_New* val;
                  if (!va->get(cm,val,istream,whyNot,masterObjective))
                    return false;
                  else
                    {
                      v=va->getVar(cm,ids,vars,tip,whatthis,val);
                      return true;
                    }
                }
            }

        }

    }

    Implements_Data_Type_New_map_string_ABC_Var_New::Implements_Data_Type_New_map_string_ABC_Var_New(const Implements_ComplexVar_New *parent, const std::__cxx11::string &id, const std::__cxx11::string &var, const std::__cxx11::string &tip, const std::__cxx11::string &whatthis, const std::map<std::__cxx11::string, ABC_Var_New *> fields, Implements_Data_Type_New_map_string_ABC_Var_New::typePredicate complyPred, Implements_Data_Type_New_map_string_ABC_Var_New::typetypePredicate typeComply, Implements_Data_Type_New_map_string_ABC_Var_New::typeElementPredicate elemeComply, Implements_Data_Type_New_map_string_ABC_Var_New::typeValue defaultValue):
      Implements_Container_Type_New<Markov_IO_New::ABC_Var_New *, String_map>
      (parent,id,var,tip,whatthis,"_var"+id
       ,nullptr,nullptr
       ,nullptr,nullptr)
    ,comply_(complyPred)
    ,typeComply_(typeComply)
    ,elemComply_(elemeComply)
    ,default_(defaultValue)
    ,varEType_(nullptr)
    ,fields_(fields)
    {
      varEType_=Variable::create_varField(parent,this);
    }

















  };







  bool Identifier::S::comply_id_Var_Field_Used(const Implements_ComplexVar_New *p, const std::__cxx11::string &idCandidate, const Implements_ComplexVar_New *self, std::__cxx11::string *WhyNot, const std::__cxx11::string &objective)
  {
    std::string cvname=G::getComplexVarTypeId(self);
    const Implements_Data_Type_New<std::map<std::string,ABC_Var_New*>>* cmtype
        =dynamic_cast<const Implements_Data_Type_New<std::map<std::string,ABC_Var_New*>>*>
        (p->idToType(cvname,WhyNot,objective));
    if (cmtype==nullptr)
      {
        *WhyNot=objective+": "+cvname+ "is not an "+Implements_Data_Type_New<std::map<std::string,ABC_Var_New*>>
            ::ClassName();

        return false;
      }

    else return cmtype->hasName(idCandidate,WhyNot,objective,false)&&
        p->hasName(idCandidate,WhyNot,objective,false);
  }

  bool Identifier::S::typeComply_id_Cmd_Used_T(const Implements_ComplexVar_New *p, const Implements_Data_Type_New<std::__cxx11::string> *idtype, const Implements_ComplexVar_New *self, std::__cxx11::string *WhyNot, const std::__cxx11::string &objective)
  {
    if (idtype->id()==self->id())
      return true;
    else if( idtype->myType().find(V::idCmd())==0)
      {
        std::string varself=G::gettypeOfId(self);
        std::string vartest=G::gettypeOfId(idtype);

        const Implements_Command_Type_New *tself=p->idToCommand(
              varself,WhyNot,objective);
        return tself->includesThisType(p,vartest,WhyNot,objective);
      }
    else
      {
        *WhyNot=objective+": "+idtype->myType()+ "is not a "+V::idCmd();
        return false;
      }
  }


  void Implements_ComplexVar_New::pushCommand(Implements_Command_Type_New *cmd)
  {
    vars_[cmd->id()]=cmd;
    types_[cmd->id()]=cmd;
    cmds_[cmd->id()]=cmd;

  }

  std::set<std::__cxx11::string> Implements_Identifier::alternativeNext(const Implements_ComplexVar_New *cm) const
  {
    std::set<std::string> o;
    if (fieldType_!=nullptr)
      {
        auto& cv=fieldType_->getFields();
        for (auto& e:cv)
          {
            std::string id=e.first;
            std::string w;
            if ((isNew_&&!cm->hasName(id,&w,"",false))
                ||(isUsed_&&cm->hasName(id,&w,"",false)))
              {
                o.insert(id);
              }
          }

      }
    else
      if (isVar_)
        {
          if (isNew_)
            {
              std::string varType="";
              if (type_!=nullptr)
                varType=type_->id();
              auto sv= cm->getIdsOfVarType(varType,false);
              auto st=cm->getIdsOfTypeType(varType,true);
              std::set<std::string> o;
              for (auto& e:sv)
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

              std::string varType="";
              if (type_!=nullptr)
                varType=type_->id();
              std::set<std::string> o2=
                  cm->getIdsOfVarType(varType,true);
              o.insert(o2.begin(),o2.end());
            }
        }

    if (isType_)
      {
        if (isNew_)
          {
            std::string varType="";
            if (type_!=nullptr)
              varType=type_->id();
            auto st=cm->getIdsOfTypeType(varType,true);
            std::set<std::string> o;
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
            std::string varType="";
            if (type_!=nullptr)
              varType=type_->id();
            std::set<std::string> o2= cm->getIdsOfTypeType(varType,true);
            o.insert(o2.begin(),o2.end());
          }

      }
    if (isCommand_)
      {
        std::string commandType="";
        if (type_!=nullptr)
          commandType=type_->id();

        std::set<std::string> o2= cm->getIdsOfCmdType(commandType,true);
        o.insert(o2.begin(),o2.end());

      }
    return o;
  }

  bool Implements_Identifier::isVarInDomain(const Implements_ComplexVar_New *cm, const std::__cxx11::string &idCandidate, std::__cxx11::string *whyNot, const std::__cxx11::string &objective) const
  {
    if (fieldType_!=nullptr)
      {
        if (!fieldType_->hasFieldName(idCandidate,whyNot,objective))
          return false;
        if (isNew_&&isUsed_)
          return true;
        else if (isNew_)
          return cm->isNameUnOcuppied(idCandidate,whyNot,objective,false);
        else
          return cm->hasName(idCandidate,whyNot,objective,false);
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
      else if (type_==nullptr)
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
          std::string varType=type_->id();
          if (isVar_)
            return cm->hasNameofType(
                  idCandidate,varType,whyNot,objective,true);
          else if (isType_)
            return cm->hasTypeofType(
                  idCandidate,varType,whyNot,objective,true );
          else return false;
        }

  }

  bool Implements_Identifier::isTypeIdentifierInDomain(const Implements_ComplexVar_New *cm, const Implements_Identifier *val, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) const
  {

    if (isNew_ && !isUsed_ && val->isUsed_)
      {
        *whyNot=masterObjective+": "+id()+" only allow new identifiers and "
            + val->id()+" take used identifiers";
        return false;
      }
    else if (isUsed_&& !isNew_&& val->isNew_)
      {
        *whyNot=masterObjective+": "+id()+" only allow used identifiers and "
            + val->id()+" take new identifiers";
        return false;
      }
    else if (fieldType_!=nullptr)
      {
        if (val->fieldType_==nullptr)
          {
            *whyNot=masterObjective+": "+id()+" is a field identifier and "
                + val->id()+" is not";
            return false;
          }
        else if (!fieldType_->isTypeInDomain(cm,val->fieldType_,whyNot,masterObjective))
          return false;
        else return true;
      }
    else if (isVar_ && !isType_ && val->isType_)
      {
        *whyNot=masterObjective+": "+id()+" only allow var identifiers and "
            + val->id()+" take type identifiers";
        return false;
      }
    else if (isType_&& !isVar_&& val->isVar_)
      {
        *whyNot=masterObjective+": "+id()+" only allow type identifiers and "
            + val->id()+" take var identifiers";
        return false;
      }
    else if (isCommand_&& !val->isCommand_)
      {
        *whyNot=masterObjective+": "+id()+" only allow command identifiers and "
            + val->id()+" does not take command identifiers";
        return false;
      }
    else if (type_!=nullptr)
      {
        if (val->type_==nullptr)
          {
            *whyNot=masterObjective+": "+id()+" is a typed identifier and "
                + val->id()+" is not";
            return false;
          }
        else if (!type_->isTypeInDomain(cm,val->type_,whyNot,masterObjective))
          return false;
        else return true;
      }
    else
      return true;

  }

  std::__cxx11::string Implements_Identifier::toId(const ABC_Type_of_Value *type, const _private::Implements_Data_Type_New_map_string_ABC_Var_New *fieldType, bool isVar, bool isType, bool isCommand, bool isNew, bool isUsed)
  {
    std::string id="_id";
    if (fieldType==nullptr)
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
        if (type!=nullptr)
          {
            id+=type->id();
          }
      }
    else
      {
        id+="Fld"+fieldType->id();
      }
    if (isNew&&!isUsed)
      {
        id+="New";
      }
    if (!isNew&&isUsed)
      {
        id+="Used";
      }
    return id;
  }

  void Real::push_Types(Markov_CommandManagerVar *cm)
  {
    cm->pushType(new Implements_Data_Type_New<double>(cm));
    cm->pushType(nonZero::varType(cm));
  }

  void Identifier::push_Types(Markov_CommandManagerVar *cm)
  {
    cm->pushType(new Implements_Data_Type_New<std::string>(cm));
    cm->pushType(create_IdCmdUsed(cm));
    cm->pushType(create_IdNew(cm));
    cm->pushType(create_IdTypeNew(cm));
    cm->pushType(create_IdType_Used(cm));
    cm->pushType(create_IdVarUsed(cm));
    cm->pushType(create_IdValid(cm));
    cm->pushType(create_IdUsed(cm));
    cm->pushType(create_IdVarNew(cm));
    cm->pushType(create_IdVarNew(cm));
  }



};
