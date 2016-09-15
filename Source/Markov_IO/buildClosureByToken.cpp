#include "Markov_IO/buildClosureByToken.h"
#include "Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_IO/Implements_Closures.h"
#include "Markov_IO/StructureEnv_templ.h"

namespace Markov_IO_New
{




  build_StatementNew::build_StatementNew(const StructureEnv_New *p
                                         , const Implements_Data_Type_New<Implements_Var> *varType
                                         , const Implements_Closure_Type<void *> *clType
                                         ):
    p_(p),
    mystate(S_Init),
    v_(varType->getBuildByToken(p)),
    cb_(clType->getBuildClosureByToken(p)),
    cl_(),
    x_()

  {}

  void build_StatementNew::clear()
  {
    v_->clear();
    mystate=S_Init;
    x_.clear();
    cb_->clear();

  }


inline
  Token_New build_StatementNew::popBackToken()
  {
    switch (mystate)
      {
      case S_Init: return {};
      case S_Function_Final:
    //    cb_->UnPopClosure(cl_.release());

      case S_Function_Partial:
        {
          Token_New out =cb_->popBackToken();
          if (cb_->isInitial())
            mystate=S_Init;
          else
            mystate=S_Expression_Partial;
          return out;
        }

      case S_Expression_Final:
        v_->unPop(x_);

      case S_Expression_Partial:
        {
          Token_New out =v_->popBackToken();
          if (v_->isInitial())
            mystate=S_Init;
          else
            mystate=S_Expression_Partial;
          return out;
        }


      }
  }














  bool Markov_IO_New::buildClosureByToken<void *>::pushToken(Token_New tok, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective)

  {
    const std::string objective=masterObjective+":  rejected token "+tok.str();
    switch (mystate)
      {
      case S_Init:
        if (idB_->pushToken(tok,whyNot,objective))
          {
            idString_=idB_->unloadVar();
            rfnType_=parent()->idToFunc(idString_,whyNot,objective);
            if (rfnType_==nullptr)
              return false;
            else
              {
                oUB_.reset
                    (rfnType_->getOverloadsTypes(parent())->getBuildClosureByToken(parent()));
                if (oUB_->isFinal())
                  {
                    data_.reset
                        (oUB_->unloadClosure());
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
        if (oUB_->pushToken(tok, whyNot,objective))
          {
            if (oUB_->isFinal())
              {
                data_.reset(oUB_->unloadClosure());
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

  Markov_IO_New::buildClosureByToken<void *>::~buildClosureByToken(){}

  Markov_IO_New::buildClosureByToken<void *>::buildClosureByToken(const StructureEnv_New *parent, const Implements_Closure_Type<void *> *varType)
    :
      p_(parent)
    ,mystate(S_Init)
    ,fnType_(varType)
    ,idtype_(varType->myFunctionIdentifier(parent))
    ,idB_(varType->myFunctionIdentifier(parent)->getBuildByToken(parent))
    ,idString_()
    ,rfnType_()
    ,oUB_(varType->getOverloadsTypes(parent)->getBuildClosureByToken(parent))
    ,data_(){}









}
