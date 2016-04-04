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


  template<typename T>
  bool Implements_Data_Type_class<T>::get(const Implements_ComplexVar_New *cm, T *&v, ABC_Input *istream, std::__cxx11::string *whyNot, std::__cxx11::string &MasterObjective) const
  {
    std::map<std::string,ABC_Var_New*> m;
    if (!CVtype_->get(cm,m,istream,whyNot,MasterObjective))
      return false;
    else
      {
        T* p=getClass(cm,m,whyNot,MasterObjective);
        if (p==nullptr)
          return false;
        else
          {
            if (!isInDomain(p,whyNot,MasterObjective))
              return false;
            else
              {
                v=p;
                return true;
              }

          }
      }
  }

};



};
