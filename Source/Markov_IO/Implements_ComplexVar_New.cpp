#include "Markov_IO/Implements_ComplexVar_New.h"

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
    idSelfType_=Identifier::create_IdType(this,id);

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


  };

  bool Identifier::S::comply_id_Field(const Implements_ComplexVar_New *p, const std::__cxx11::string &idCandidate, const Implements_ComplexVar_New *self, std::__cxx11::string *WhyNot, const std::__cxx11::string &objective)
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

  bool Identifier::S::typeComply_id_Cmd_T(const Implements_ComplexVar_New *p, const Implements_Data_Type_New<std::__cxx11::string> *idtype, const Implements_ComplexVar_New *self, std::__cxx11::string *WhyNot, const std::__cxx11::string &objective)
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



};
