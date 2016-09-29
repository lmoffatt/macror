#include "Markov_IO/buildClosureByToken.h"
#include "Markov_IO/buildClosureByToken_Templ.h"

#include "Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_IO/Implements_Closures.h"
#include "Markov_IO/StructureEnv_templ.h"
namespace Markov_IO_New
{




  build_StatementNew::build_StatementNew
  (const StructureEnv_New *p
   , const Implements_Data_Type_New<Implements_Var> *varType
   , const Implements_Data_Type_New<Implements_Var_Closure> *varClosureType
   , const Implements_Closure_Type<void *> *cmdType
   ):
    p_(p),
    mystate(S_Init),
    v_(varType->getBuildByToken(p)),
    vc_(varClosureType->getBuildByToken(p)),
    cb_(cmdType->getBuildClosureByToken(p))

  {}

  void build_StatementNew::clear()
  {
    v_->clear();
    mystate=S_Init;
    vc_->clear();
    cb_->clear();

  }

  Token_New build_StatementNew::popBackToken()
  {
    switch (mystate)
      {
      case S_Init: return {};
      case S_Command_Final:
      case S_Command_Partial:
        {
          Token_New out =cb_->popBackToken();
          if (cb_->isInitial())
            mystate=S_Init;
          else
            mystate=S_Expression_Partial;
          return out;
        }

      case S_Expression_Final:
      case S_Expression_Partial:
        {
          Token_New out =v_->popBackToken();
          if (v_->isInitial())
            mystate=S_Init;
          else
            mystate=S_Expression_Partial;
          return out;
        }

      case S_Assigment_Final:
      case S_Assigment_Partial:
        {
          Token_New out =vc_->popBackToken();
          if (vc_->isInitial())
            mystate=S_Init;
          else
            mystate=S_Assigment_Partial;
          return out;
        }
      case S_Assigment_Expression_Partial:
        {
          Token_New out =v_->popBackToken();
          vc_->popBackToken();
          if (v_->isInitial())
            mystate=S_Init;
          else
            mystate=S_Assigment_Expression_Partial;
          return out;
        }


      }
  }


  bool buildClosureByToken<void *>::pushToken(Token_New tok, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective)

  {
    const std::string objective=masterObjective+":  rejected token "+tok.str();
    switch (mystate)
      {
      case S_Init:
      case S_Identifier_Partial:
        if (!idB_->pushToken(tok,whyNot,objective))
          {
            return false;
          }
        else
          {
            if (idB_->isFinal())
              {
                idString_=idB_->unloadVar();
                rfnType_=parent()->idToFunc(idString_,whyNot,objective);
                if (rfnType_==nullptr)
                  return false;
                else
                  {
                    oUB_.reset
                        (rfnType_->getOverloadsTypes(parent())
                         ->getBuildClosureByToken(parent()));
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
            else
              {
                mystate=S_Identifier_Partial;
                return true;
              }
          }
      case S_Identifier_Final:
      case S_Closure_PARTIAL:
        if (!oUB_->pushToken(tok, whyNot,objective))
          {
            return false;
          }
        else if (oUB_->isFinal())
          {
            mystate=S_Final;
            return true;
          }
        else
          {
            mystate=S_Closure_PARTIAL;
            return true;
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
    ,oUB_()
    ,data_(){}


  std::pair<std::string, std::set<std::string> >
  Markov_IO_New::buildClosureByToken<void *>::alternativesNext() const
  {
    switch (mystate)
      {
      case S_Init:
      case S_Identifier_Partial:
        return idB_->alternativesNext();
      case S_Identifier_Final:
      case S_Closure_PARTIAL:
        return oUB_->alternativesNext();
      case S_Final:
        return {};
      }
  }

  Token_New Markov_IO_New::buildClosureByToken<void *>::popBackToken()

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
      case S_Identifier_Partial:
        Token_New out=idB_->popBackToken();
        if (idB_->isInitial())
          {
            mystate=S_Init;
          }
        else
          {
            mystate=S_Identifier_Partial;
          }
        return out;
      }

  }
  ABC_Closure *buildClosureByToken<void *>::unloadClosure()
  {
    if (isFinal())
      {
        data_.reset(oUB_->unloadClosure());
        ABC_Closure* out=data_.release();
        mystate=S_Init;
        return out;
      }
    else return nullptr;


  }

  bool buildClosureByToken<void *>::unPopClosure(ABC_Closure *cl)
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
            rfnType_=f;
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








  bool buildByToken<Implements_Var_Closure>::pushIdToken(Token_New tok, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective)
  {
    if (!idB_->pushToken(tok,whyNot,masterObjective))
      {
        return false;
      }
    else
      {
        iv_.id=idB_->unloadVar();
        dataTy_=ivarType_->getElementType(parent(),iv_,whyNot,masterObjective,dataTy_);
        dataB_.reset(dataTy_->getBuildClosureByToken(parent()));
        mystate =ID1;
        return true;
      }


  }




  bool buildByToken<Implements_Var_Closure>::pushToken(Token_New tok, std::string *whyNot, const std::string &masterObjective)

  {
    const std::string objective=masterObjective+":  rejected token "+tok.str();
    switch (mystate)
      {
      case S_Init:
        {
          if (tok.tok()==Token_New::HASH)
            {
              mystate=TIP1;
              return true;
            }
          else if (tok.tok()==Token_New::IDENTIFIER)
            {
              return pushIdToken(tok,whyNot, objective);
            }
          else
            {
              *whyNot=objective+": is not a \"#\" nor an identifier";
              return false;
            }

        }
      case TIP1:
        if (tok.tok()==Token_New::STRING)
          {
            mystate =TIP2;
            iv_.Tip=tok.str();
            return true;
          }
        else
          {
            *whyNot=objective+": is not a string";
            return false;
          }
      case TIP2:
        if (tok.tok()==Token_New::EOL)
          {
            mystate =WT0_ID0;
            return true;
          }
        else
          {
            *whyNot=objective+": is not an end of line";
            return false;
          }
      case WT0_ID0:
        if (tok.tok()==Token_New::HASH)
          {
            mystate =WT1;
            return true;
          }
        else if (tok.tok()==Token_New::IDENTIFIER)
          {
            return pushIdToken(tok,whyNot, objective);

          }
        else
          {
            *whyNot=objective+": is not an identifier, nor a \"#\"";

            return false;
          }
      case WT1:
        if (tok.tok()==Token_New::HASH)
          {
            mystate =WT2;
            return true;
          }
        else  {
            *whyNot=objective+": is not a \"#\"";

            return false;
          }
      case WT2:
        if(tok.tok()==Token_New::STRING)
          {
            mystate =WT3;
            iv_.WhatThis=tok.str();
            return true;
          }
        else
          {
            *whyNot=objective+": is not a string";
            return false;
          }
      case WT3:
        if (tok.tok()==Token_New::EOL)
          {
            mystate =ID0;
            return true;
          }
        else
          {
            *whyNot=objective+": is not a string";
            return false;
          }
      case ID0:
        return pushIdToken(tok,whyNot, objective);

      case ID1:
        if (tok.tok()==Token_New::ASSIGN)
          {
            mystate =ID2;
            return true;
          }
        else
          {
            *whyNot=objective+": is not a \"=\"";
            return false;
          }
      case ID2:
      case S_DATA_PARTIAL:
        if (!dataB_->pushToken(tok,whyNot,objective))
          {
            return false;
          }
        else if (dataB_->isFinal())
          {
            iv_.closure.reset(dataB_->unloadClosure());
            mystate =S_Final;
            return true;
          }
        else
          {
            mystate=S_DATA_PARTIAL;
            return true;
          }

      case S_Final:
      default:
        return false;
      }
  }



  Token_New buildByToken<Implements_Var_Closure>::popBackToken()
  {
    switch (mystate) {
      case S_Init: return {};
      case  TIP1:
        mystate= S_Init;
        return Token_New(Token_New::HASH);
      case  TIP2:
        {
          Token_New out(""""+std::move(iv_.Tip)+"""");
          iv_.Tip.clear();
          mystate =TIP1;
          return out;
        }

      case WT0_ID0:
        mystate =TIP2;
        return Token_New(Token_New::EOL);
      case WT1:
        mystate =WT0_ID0;
        return Token_New(Token_New::HASH);
      case WT2:
        mystate =WT1;
        return Token_New(Token_New::HASH);

      case WT3:
        {
          Token_New out(""""+std::move(iv_.WhatThis)+"""");
          iv_.WhatThis.clear();
          mystate =WT2;
          return out;
        }

      case ID1:
        {
          idB_->unPop(std::move(iv_.id));
          iv_.id={};
          if (!iv_.WhatThis.empty())
            mystate=ID0;
          else if(!iv_.Tip.empty())
            mystate=WT0_ID0;
          else
            mystate=S_Init;
          return idB_->popBackToken();
        }
      case ID2:
        mystate =ID1;
        return Token_New(Token_New::ASSIGN);
      case ID0:
        mystate =WT3;
        return Token_New(Token_New::EOL);
      case  S_DATA_PARTIAL:
        {
          Token_New out=dataB_->popBackToken();
          if (dataB_->isInitial())
            mystate=ID2;
          else
            mystate=S_DATA_PARTIAL;
          return out;
        }
      case S_Final:
        {
          dataB_->unPopClosure(iv_.closure.release());
          Token_New out=dataB_->popBackToken();
          if (dataB_->isInitial())
            mystate=ID2;
          else
            mystate=S_DATA_PARTIAL;
          return out;

        }
      }
  }




  buildByToken<Implements_Var_Closure>::buildByToken(const StructureEnv_New *parent, const Implements_Data_Type_New<Implements_Var_Closure> *varType):
    p_(parent),
    mystate(S_Init),ivarType_(varType),idType_(varType->getKeyType(parent)->clone()),
    dataTy_(varType->getElementType(parent)->clone()),
    idB_(new buildByToken<std::string>(parent,idType_)),dataB_(new buildClosureByToken<void *>(parent,dataTy_)),iv_()

  {

  }

  void buildByToken<Implements_Var_Closure>::clear()
  {
    mystate=S_Init;
    iv_.clear();
    idB_->clear();
    dataB_.reset();

  }















}
