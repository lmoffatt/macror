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

  ABC_Type_of_Value::ABC_Type_of_Value(const Implements_ComplexVar_New *parent, const std::string &id, const std::string &var, const std::string &tip, const std::string &whatthis):
    Implements_ComplexVar_New(parent,id,var,tip,whatthis)
  {


    if (id.find(Identifier::types::idType::myId())==id.npos)
      idSelfType_=Identifier::types::idType::varType(this,this);
    else
      idSelfType_=nullptr;
  }



  buildByToken<std::string> *Implements_Data_Type_New<std::string>::getBuildByToken(const Implements_ComplexVar_New *cm) const
  {
    return new buildByToken<std::string>(cm,this);
  }


  namespace _private {



    std::string Implements_Data_Type_New_ABC_Var_New::ClassName()
    {
      return "Implements_Data_Type_New_of"+ABC_Var_New::ClassName();
    }

    std::string Implements_Data_Type_New_ABC_Var_New::myClass() const
    {
      return ClassName();
    }

    bool Implements_Data_Type_New_ABC_Var_New::isVarInDomain(const Implements_ComplexVar_New *cm, const ABC_Var_New * const val, std::string *whyNot, const std::string &masterObjective) const
    {
      if (this->idType_->isVarInDomain(cm,val->id(),whyNot,masterObjective))
        return false;
      else if (this->varType_->isVarInDomain(cm,val->myType(),whyNot,masterObjective))
        return false;
      else return true;
    }

    bool Implements_Data_Type_New_ABC_Var_New::put(const Implements_ComplexVar_New *cm, const ABC_Var_New *v, ABC_Output *ostream, std::string *whyNot, const std::string &masterObjective) const
    {
      if (isVarInDomain(cm,v,whyNot,masterObjective))
        {
          ostream->put(v->id()+":"+v->myType()+"=");
          const ABC_Type_of_Value* t=cm->idToType(v->myType(),whyNot,masterObjective);
          if (t==nullptr)
            return false;
          else
            {
              return t->put(cm,v->value(),ostream,whyNot,masterObjective);
            }
        }
      else return false;
    }

    bool Implements_Data_Type_New_ABC_Var_New::get(const Implements_ComplexVar_New *cm, ABC_Var_New *&v, ABC_Input *istream, std::string *whyNot, const std::string &masterObjective) const
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

    Implements_ComplexVar_New *Implements_Data_Type_New_ABC_Var_New::getComplexVarofTypeRep(const Implements_ComplexVar_New *cm, const ABC_Type_of_Value *var, std::string *whyNot, const std::string &masterObjective) const
    {
      if (getCvFromType_==nullptr)
        return nullptr;
      else
        {
          auto v=dynamic_cast<const Implements_Data_Type_New_ABC_Var_New*>(var);
          if (v==nullptr)
            return nullptr;
          else
            return (*getCvFromType_)(cm,v,whyNot,masterObjective);
        }
    }

    Implements_Data_Type_New_ABC_Var_New *Implements_Data_Type_New_ABC_Var_New::getTypeClassRep(const Implements_ComplexVar_New *cm, const Implements_ComplexVar_New *cvar, std::string *whyNot, const std::string &masterObjective) const
    {
      {
        if (getTypeFromCV_==nullptr)
          return nullptr;
        else
          {
            return (*getTypeFromCV_)(cm,cvar,whyNot,masterObjective);
          }
      }
    }

    Implements_Data_Type_New_ABC_Var_New::~Implements_Data_Type_New_ABC_Var_New(){}

    Implements_Data_Type_New_ABC_Var_New *Implements_Data_Type_New_ABC_Var_New::makeABC_Var_Type_Of_CV(const Implements_ComplexVar_New *cm, const Implements_Data_Type_New<std::map<std::string, ABC_Var_New *> > *varMap)
    {

    }

    buildByToken<std::string> *Implements_Data_Type_New_ABC_Var_New::getNewIdentifierBuildByToken(const Implements_ComplexVar_New *cm) const
    {

      return new buildByToken<std::string> (cm,idType_);
    }

    const Implements_Data_Type_New<std::map<std::string, ABC_Var_New *> > *Implements_Data_Type_New_ABC_Var_New::getParentType() const
    {
      return varMap_;
    }

    buildByToken<std::string> *Implements_Data_Type_New_ABC_Var_New::getVarIdentifierBuildByToken(const Implements_ComplexVar_New *cm, const std::string id) const
    {
      std::string whyNot;


      const ABC_Type_of_Value * t=parent()->idToType(id,&whyNot,"");
      if (t!=nullptr)
        {
          const Implements_Data_Type_New<std::string>* vt=t->getSelfIdType();

          return new buildByToken<std::string> (cm,vt);
        }
      else
        return nullptr;
    }

    buildByToken<std::string> *Implements_Data_Type_New_ABC_Var_New::getVarIdentifierBuildByToken(const Implements_ComplexVar_New *cm) const
    {
      return new buildByToken<std::string>(cm,varType_);
    }

    buildByToken<ABC_Var_New *> *Implements_Data_Type_New_ABC_Var_New::getBuildByToken(const Implements_ComplexVar_New *cm) const
    {
      return new buildByToken<ABC_Var_New*>(cm,this);
    }

    Implements_Data_Type_New_ABC_Var_New::Implements_Data_Type_New_ABC_Var_New
    (const Implements_ComplexVar_New *parent
     , const std::string &id
     , const std::string &var
     , const std::string &tip
     , const std::string &whatthis
     , const Implements_Data_Type_New<std::map<std::string, ABC_Var_New *> > *varMap
     , const Implements_Identifier *idType
     , const Implements_Identifier *varType
     , Implements_Data_Type_New_ABC_Var_New::typetypePredicate typeComply
     , Implements_Data_Type_New_ABC_Var_New::cvToType getTypeFromCV
     , Implements_Data_Type_New_ABC_Var_New::typeToCv getCvFromType)
      :
        Implements_Base_Type_New<ABC_Var_New*>
        (parent,id,var,tip,whatthis,nullptr,
         nullptr,typeComply,nullptr),
        varMap_(varMap), idType_(idType),varType_(varType)
      ,getTypeFromCV_(getTypeFromCV),getCvFromType_(getCvFromType)
    {
    }

    Implements_Data_Type_New_map_string_ABC_Var_New
    ::Implements_Data_Type_New_map_string_ABC_Var_New
    (const Implements_ComplexVar_New *parent
     , const std::string &id
     , const std::string &var
     , const std::string &tip
     , const std::string &whatthis
     , const std::vector<ABC_Var_New *> fields
     , Implements_Data_Type_New_map_string_ABC_Var_New::typePredicate complyPred, Implements_Data_Type_New_map_string_ABC_Var_New::typetypePredicate typeComply, Implements_Data_Type_New_map_string_ABC_Var_New::typeElementPredicate elemeComply, Implements_Data_Type_New_map_string_ABC_Var_New::typeValue defaultValue):
      Implements_Container_Type_New<Markov_IO_New::ABC_Var_New *, String_map>
      (parent,id,var,tip,whatthis,"_var"+id
       ,nullptr,nullptr
       ,nullptr,nullptr)
    ,comply_(complyPred)
    ,typeComply_(typeComply)
    ,elemComply_(elemeComply)
    ,default_(defaultValue)
    ,varEType_(nullptr)
    ,fields_(toMap(fields))
    ,vfields_(toVec(fields))
    {
      varEType_=Variable::types::varField::varType(parent,this);
    }




    template class Implements_Data_Type_New_M_Matrix<double>;

    template class Implements_Data_Type_New_M_Matrix<std::size_t>;

    Implements_Data_Type_New_map_string_ABC_Var_New::const_iterator *Markov_IO_New::_private::Implements_Data_Type_New_map_string_ABC_Var_New::begin() const
    {
      return new MyConstIterator(*this,0);
    }
    Implements_Data_Type_New_map_string_ABC_Var_New::const_iterator *Implements_Data_Type_New_map_string_ABC_Var_New::end() const
    {
      return new MyConstIterator(*this,vfields_.size());
    }
















  };








  void Implements_ComplexVar_New::pushCommand(Implements_Command_Type_New *cmd)
  {
    all_[cmd->id()]=cmd;
    cmds_[cmd->id()]=cmd;

  }

  std::set<std::string> Implements_Identifier::alternativeNext(const Implements_ComplexVar_New *cm) const
  {
    std::set<std::string> o;
    if (fieldType_!=nullptr)
      {
        if (it_!=nullptr)
          {
            std::string id=(**it_)->id();
            std::string w;
            if ((isNew_&&!cm->hasName(id,&w,"",false))
                ||(isUsed_&&cm->hasName(id,&w,"",false)))
              {
                alternatives::insert(o,**it_);
              }
          }
        else
          {
            auto& cv=fieldType_->getFields();
            for (auto& e:cv)
              {
                std::string id=e.first;
                std::string w;
                if ((isNew_&&!cm->hasName(id,&w,"",false))
                    ||(isUsed_&&cm->hasName(id,&w,"",false)))
                  {
                    alternatives::insert(o,e.second);
                  }
              }
          }
      }
    else
      if (isVar_)
        {
          if (isNew_)
            {
              o.insert(alternatives::newIdentifier());
              std::string varType="";
              if (type_!=nullptr)
                varType=type_->id();
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
            o.insert("<an unoccupied identifier>");
            std::string varType="";
            if (type_!=nullptr)
              varType=type_->id();
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

  bool Implements_Identifier::isVarInDomain(const Implements_ComplexVar_New *cm, const std::string &idCandidate, std::string *whyNot, const std::string &objective) const
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

  bool Implements_Identifier::isTypeIdentifierInDomain(const Implements_ComplexVar_New *cm, const Implements_Identifier *val, std::string *whyNot, const std::string &masterObjective) const
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


  std::string Implements_Identifier::toId
  (const ABC_Type_of_Value *type, const _private::Implements_Data_Type_New_map_string_ABC_Var_New *fieldType
   , const _private::MyConstIterator* it,bool isVar, bool isType, bool isCommand, bool isNew, bool isUsed)
  {
    std::string id="_id";
    if (it!=nullptr)
      {
        id+="FldIt";
        if (isNew&&!isUsed)
          {
            id+="New";
          }
        if (!isNew&&isUsed)
          {
            id+="Used";
          }
        if (fieldType!=nullptr)
          id+=fieldType->id();
        id+=(**it)->id();

      }

    else if (fieldType==nullptr)
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
        if (type!=nullptr)
          {
            id+=type->id();
          }
      }
    else
      {
        id+="Fld";
        if (isNew&&!isUsed)
          {
            id+="New";
          }
        if (!isNew&&isUsed)
          {
            id+="Used";
          }
        id+=fieldType->id();

      }
    return id;
  }

  void Real::push_Types(Markov_CommandManagerVar *cm)
  {
    cm->pushType(new Implements_Data_Type_New<double>(cm));
    cm->pushType(types::nonZero::varType(cm));
  }


  template<typename T>
  void Matrix::push_Types(Markov_CommandManagerVar *cm)
  {
    cm->pushType(new vType<T>(cm));
  }

  // template Matrix<double>;
  // template Matrix<std::size_t>;




};
