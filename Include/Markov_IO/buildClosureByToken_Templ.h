#ifndef BUILDCLOSUREBYTOKEN_TEMPL_H
#define BUILDCLOSUREBYTOKEN_TEMPL_H
#include"Markov_IO/buildClosureByToken.h"
#include "Markov_IO/Implements_Closures.h"
#include "Markov_IO/StructureEnv.h"
#include "Markov_IO/StructureEnv_templ.h"


namespace Markov_IO_New
{

  template<typename R>
  bool buildClosureByToken<R, void *>::unPopClosure(ABC_Closure *cl)
  {
    auto t= dynamic_cast<const ABC_Type_of_Function*>(cl->closureType(parent()));
    if (t==nullptr)
      return false;
    else
      {
        auto f=t->myFunctionType(parent());
        if (f==nullptr) return false;
        else
          {
            rfnType_=parent()->template idTo_R_Func<R>
                (f->getFunctionId(),resultType_->typeId());
            if (rfnType_==nullptr)
              return false;
            else
              {
                oUB_.reset
                    (rfnType_->getOverloadsTypes(parent())
                     ->getBuildClosureByToken(parent()));
                if(!oUB_->unPopClosure(cl))
                  {
                    return false;
                  }
                else
                  {
                    mystate=S_Final;
                    return true;

                  }
              }
          }
      }
  }

  template<typename R>
  bool buildClosureByToken<R, void *>::pushToken(Token_New tok, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective)

  {
    const std::string objective=masterObjective+":  rejected token "+tok.str();
    switch (mystate)
      {
      case S_Init:
        if (!idB_->pushToken(tok,whyNot,objective))
          {
            return false;
          }

          else{
            idString_=idB_->unloadVar();
            rfnType_=parent()->template idTo_R_Func<R>
                (idString_,resultType_->typeId(),whyNot,objective);
            if (rfnType_==nullptr)
              return false;
            else
              {
                oUB_.reset
                    (rfnType_->getOverloadsTypes(parent())
                     ->getBuildClosureByToken(parent()));
                if (oUB_->isFinal())
                  {
                    mystate=S_Final;
                    return true;
                  }
                else
                  {
                    mystate=S_Identifier_Final;
                    return true;

                  }
              }
          }
      case S_Identifier_Final:
      case S_Closure_PARTIAL:
        if (!oUB_->pushToken(tok, whyNot,objective))
          { return false;}
          else{
            if (oUB_->isFinal())
              {
                mystate=S_Final;
                return true;
              }
            else
              {
                mystate=S_Closure_PARTIAL;
                return true;
              }
          }
      case S_Final:
        return false;
      }
  }


  template<typename R>
  std::pair<std::string, std::set<std::string> >
  buildClosureByToken<R,void *>::alternativesNext() const
  {
    switch (mystate)
      {
      case S_Init:
        return idB_->alternativesNext();
      case S_Identifier_Final:
      case S_Closure_PARTIAL:
        return oUB_->alternativesNext();
      case S_Final:
        return {};
      }
  }

  template<typename R>
  Token_New buildClosureByToken<R,void *>::popBackToken()

  {
    switch (mystate)
      {
      case S_Init: return {};
      case S_Final:
      case S_Closure_PARTIAL:
        {
          Token_New out=oUB_->popBackToken();
          if (oUB_->isInitial()) mystate=S_Identifier_Final;
          else mystate=S_Closure_PARTIAL;
          return out;
        }
      case S_Identifier_Final:

          idB_->unPop(idString_);
          Token_New out=idB_->popBackToken();
          if (idB_->isInitial())
            {
              mystate=S_Init;
            }
          return out;
        }

  }


  template<typename R>
 ABC_R_Closure<R>*
  buildClosureByToken<R, void *>::unloadClosure()
  {
    if (isFinal())
      {
        data_.reset(oUB_->unloadClosure());
        ABC_R_Closure<R>* out=data_.release();
        mystate=S_Init;
        return out;
      }
    else return nullptr;


  }
 template<typename R>
 bool buildClosureByToken<R, void *>::isFinal() const
 {
   return mystate==S_Final;

 }

 template<typename R>
 bool buildClosureByToken<R, void *>::isInitial() const
 {
   return mystate==S_Init;

 }

 template<typename R>
 bool buildClosureByToken<R, void *>::hasMandatory() const
 {
   return mystate==S_Final;
 }

 template<typename R>
 buildClosureByToken<R, void *>::buildClosureByToken(const StructureEnv_New *parent, const Implements_Closure_Type<R, void *> *varType)
   :
     p_(parent)
   ,mystate(S_Init)
   ,resultType_(varType->myResultType(parent))
   ,fnType_(varType)
   ,idtype_(varType->myFunctionIdentifier(parent))
   ,idB_(varType->myFunctionIdentifier(parent)->getBuildByToken(parent))
   ,idString_()
   ,rfnType_()
   ,oUB_()
   ,data_(){}

 template<typename R>
 void buildClosureByToken<R, void *>::clear()
 {}

 template<typename R>
 const StructureEnv_New *buildClosureByToken<R, void *>::parent() const {return p_;}

 template<typename R>
  buildClosureByToken<R, void *>::~buildClosureByToken()
 {}


}


#endif // BUILDCLOSUREBYTOKEN_TEMPL_H
