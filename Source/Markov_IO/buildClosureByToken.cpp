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
    ABC_BuildByToken_(p),
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












  std::pair<std::__cxx11::string, std::set<std::__cxx11::string> >
  buildClosureByToken<void *>::alternativesNext() const

  {
    std::pair<std::string, std::set<std::string> > out;
    switch (mystate)
      {
      case S_Init:
        return idObjB_->alternativesNext();
      case S_Closure_PARTIAL:
        return alternativesNext(vecValueB_,nPushedTokens_,nPushedTokensIn_);

      case S_Closure_Mandatory:
        {
          auto out= alternativesNext(vecValueB_,nPushedTokens_,nPushedTokensIn_);
          out.second.insert(alternatives::endOfLine());
          return out;
        }

      case S_Closure_Final:
        return {"ClassNamr()",{alternatives::endOfLine()}};

      case S_Final:
        return {};
      }
  }

  buildClosureByToken<void *>::buildClosureByToken(const StructureEnv_New *parent, const Implements_Closure_Type<void *> *varType)
    :
      ABC_BuildClosure(parent),
      mystate(S_Init),
      fnType_(varType),
      idtype_(varType->myFunctionIdentifier(parent)),
      idString_(),
      idB_(varType->myFunctionIdentifier(parent)->getBuildByToken(parent)),
      vecValueB_(varType->getOverloadBuild(parent,nullptr)),
      nPushedTokensIn_(),
      nPushedTokens_(0),
      valueB_(),
      data_(){
    nPushedTokensIn_=std::vector<std::size_t>(vecValueB_.size(),0);

  }


  void buildClosureByToken<void *>::reset_Type(Implements_Closure_Type<void *> *varType)
  {
    mystate=S_Init;
    fnType_=varType;
    idtype_=varType->myFunctionIdentifier(parent());
    idString_.clear();
    idObjB_.reset(varType->myFunctionIdentifier(parent())->getBuildByToken(parent()));
    vecValueB_=varType->getOverloadBuild(parent(),nullptr);
    nPushedTokensIn_=std::vector<std::size_t>(vecValueB_.size(),0);
    nPushedTokens_=0;
    valueB_.reset();
    data_.reset();

  }

  std::vector<std::unique_ptr<ABC_BuildClosure> > getOverloadBuilds(const Implements_Closure_Type<void *> *f, const StructureEnv_New *cm)
  {
    return f->getOverloadBuild(cm,nullptr);

  }









}
