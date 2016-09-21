#include "Markov_IO/buildByToken.h"
#include "Markov_Console/Markov_CommandManager.h"

#include "Markov_IO/Var.h"
#include "Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_IO/buildByTokenTempl.h"
#include "Markov_IO/VarTempl.h"
#include "Markov_IO/StructureEnv_templ.h"

namespace Markov_IO_New {




  template<>
  std::pair<std::string, std::set<std::string> > buildByToken<std::string>::alternativesNext() const
  {

    return {varType_->typeId(),varType_->alternativeNext(this->parent())};
  }


  template <typename T>
  Token_New buildByToken<Markov_LA::M_Matrix<T>,true >::popBackToken()
  {
    if (isFinal())
      {
        buffer_.resize(nCols_*nRows_);
        for (std::size_t i=0; i<nRows_; ++i)
          for (std::size_t j=0; j<nCols_; ++j)
            buffer_[nCols_*i+j]=x_(i,j);

        if (hasFixedRows_)
          {
            runCols_=nCols_;
            runRows_=nRows_-1;
          }
        else
          {
            runCols_=0;
            runRows_=nRows_;
          }
      }
    std::string whyNot;
    std::string masterObjective;
    switch (mystate)
      {
      case S_Init:
        return {};

      case S_PInit_NFinal:
      case S_PInit_NData:
      case S_PInit_NBoth:
      case S_PInit_NEOL:
        {
          mystate=S_Init;
          return Token_New(Token_New::EOL);
        }

      case S_PData_NBoth:
      case S_PData_NData:
      case S_PData_NEOL:

        {
          if (eleB_->isInitial())
            {
              --runCols_;
              eleType_=dataType_->getElementType
                  (parent(),buffer_,nRows_,nCols_,runRows_,runCols_
                   ,&whyNot,masterObjective,eleType_);
              eleB_->reset_Type(eleType_);
              v_=buffer_[nCols_*runRows_+runCols_];
              eleB_->unPop(v_);

            }
          Token_New to=eleB_->popBackToken();
          if (!eleB_->isInitial())
            {
              mystate=S_PData_NData;
              return to;
            }
          else
            {
              if ((runRows_==0)&&(runCols_==0))
                mystate=S_PInit_NData;
              else if ((runRows_==0)&&(!hasFixedCols_)&&(runCols_>=nCols_Init_))
                {
                  nCols_=runCols_;
                  mystate=S_PBothData_NData;
                }
              else if (runCols_==0)
                {
                  if (hasFixedCols_||runRows_>0)
                    {
                      mystate=S_PEOL_NData;
                    }
                  else
                    {
                      mystate=S_PBothEOL_NData;
                    }
                }
              else
                {
                  mystate=S_PData_NData;
                }
              return to;
            }
        }

      case S_PBothData_NBoth:
      case S_PBothData_NData:
      case S_PBothData_NEOL:

        {
          Token_New to=eleB_->popBackToken();
          if (!eleB_->isInitial())
            {
              mystate=S_PData_NData;
              return to;
            }
          else
            {
              --runCols_;
              eleType_=dataType_->getElementType
                  (parent(),buffer_,nCols_,nRows_,runCols_,runRows_
                   ,&whyNot,masterObjective,eleType_);
              eleB_->reset_Type(eleType_);
              if ((runRows_==0)&&(runCols_==0))
                mystate=S_PInit_NBoth;
              else if ((runRows_==0)&&(!hasFixedCols_)&&(runCols_>=nCols_Init_))
                {
                  nCols_=runCols_;
                  mystate=S_PBothData_NBoth;
                }
              else if (runCols_==0)
                {
                  if (hasFixedCols_||runRows_>0)
                    {
                      mystate=S_PEOL_NBoth;
                    }
                  else
                    {
                      mystate=S_PBothEOL_NBoth;
                    }
                }
              else
                {
                  mystate=S_PData_NBoth;
                }
              return to;
            }
        }


      case S_PEOL_NFinal:
      case S_PEOL_NBoth:
      case S_PEOL_NData:
      case S_PEOL_NEOL:
        {
          if (runRows_==0)
            {
              mystate=S_PInit_NEOL;
            }
          else
            {
              --runRows_;
              runCols_=nCols_;
              if (hasFixedCols_||(runRows_>0))
                {
                  mystate=S_PData_NEOL;
                }
              else
                {
                  mystate=S_PBothData_NEOL;
                }
            }
          return Token_New(Token_New::EOL);

        }
      case S_PBothEOL_NFinal:
      case S_PBothEOL_NBoth:
      case S_PBothEOL_NData:
      case S_PBothEOL_NEOL:
        {
          if (runRows_==0)
            {
              mystate=S_PInit_NBoth;
            }
          else
            {
              --runRows_;
              runCols_=nCols_;
              if (hasFixedCols_||(runRows_>0))
                {
                  mystate=S_PData_NBoth;
                }
              else
                {
                  mystate=S_PBothData_NBoth;
                }
            }
          return Token_New(Token_New::EOL);

        }

      }


  }



  template<typename T>
  std::pair<std::__cxx11::string, std::set<std::__cxx11::string> > buildByToken<Markov_LA::M_Matrix<T>,true >::alternativesNext() const
  {
    std::pair<std::string,std::set<std::string>> out;
    switch (mystate) {
      case S_Init:
        return {dataType_->typeId(),{alternatives::endOfLine()}};

      case S_PInit_NData:
      case S_PEOL_NData:
      case S_PData_NData:
      case S_PBothData_NData:
      case S_PBothEOL_NData:

        return eleB_->alternativesNext();


      case S_PInit_NEOL:
      case S_PEOL_NEOL:
      case S_PData_NEOL:
      case S_PBothData_NEOL:
      case S_PBothEOL_NEOL:
        return {dataType_->typeId(),{alternatives::endOfLine()}};

      case S_PInit_NBoth:
      case S_PEOL_NBoth:
      case S_PData_NBoth:
      case S_PBothData_NBoth:
      case S_PBothEOL_NBoth:
        {
          out=eleB_->alternativesNext();
          out+= {dataType_->typeId(),{alternatives::endOfLine()}};
          return out;
        }
      case S_PEOL_NFinal:
      case S_PBothEOL_NFinal:
      case S_PInit_NFinal:
        return {};
        break;

      }

  }




  //  template<typename T>
  //  buildByToken<std::vector<T> >::buildByToken(const StructureEnv_New *parent, const Implements_Data_Type_New<std::vector<T> > *vecType)
  //    :
  //      p_(parent),
  //      mystate(S_Init),
  //      x_(),
  //      valueBuild_(vecType->getElementDataType(parent)->getBuildByToken(parent)),
  //      varType_(vecType){}



  buildByToken<ABC_Data_New *>::buildByToken
  (const StructureEnv_New *parent
   , const Implements_Data_Type_New<ABC_Data_New*> *varType):
    p_(parent),
    mystate(S_Init)
  ,dataType_(varType)
  ,idtypeB_(new buildByToken<std::string>(parent,varType->getElementType())),
    valueB_(nullptr),data_(nullptr)
  ,convertToClass_(varType->ConvertToClass()),classx_(nullptr){}

  void buildByToken<ABC_Data_New *>::clear()
  {
    mystate=S_Init;
    idtypeB_->clear();
  }



  bool buildByToken<ABC_Data_New *>::pushToken(Token_New tok, std::string *whyNot, const std::string &masterObjective)

  {
    const std::string objective=masterObjective+":  rejected token "+tok.str();
    switch (mystate)
      {
      case S_Init:
        if (idtypeB_->pushToken(tok,whyNot,objective))
          {
            idString_=idtypeB_->unloadVar();
            valueType_=parent()->idToType(idString_,whyNot,objective);
            if (valueType_==nullptr)
              return false;
            else
              {
                valueB_.reset(valueType_->getBuildByToken(parent()));
                if (valueB_==nullptr)
                  return false;
                else
                  {
                    mystate =S_ID_Final;
                    return true;
                  }
              }
          }
      case S_ID_Final:
        {
          if (tok.tok()!=Token_New::ASSIGN)
            {
              *whyNot=masterObjective+": expected \"=\" found "+tok.str();
              return false;
            }
          else
            {
              mystate=S_DATA_PARTIAL;
              return true;
            }
        }
      case S_DATA_PARTIAL:
        if (!valueB_->pushToken(tok, whyNot,objective))
          return false;
        else
          {
            if(valueB_->isFinal())
              {
                mystate=S_Data_Final;
                return true;
              }
            else
              {
                mystate=S_DATA_PARTIAL;
                return true;
              }
          }
      case S_Data_Final:
        if (tok.tok()!=Token_New::EOL)
          {
            *whyNot=objective+" is not an end of line";
            return false;
          }
        else
          {
            data_.reset(valueB_->unloadData());
            if (convertToClass_)
              {
                auto x=data_.get();
                const StructureEnv_New* c=dynamic_cast<StructureEnv_New*>(x);
                if (c!=nullptr)
                  {
                    auto y=valueType_->getClassRep
                        (parent(),c,whyNot, objective);
                    if (y!=nullptr)
                      classx_.reset(y);
                  }
                else
                  {
                    classx_.reset();
                  }
              }
            mystate=S_Final;
            return true;
          }

      case S_Final:
        return false;
      }
  }


  Token_New buildByToken<ABC_Data_New *>::popBackToken()

  {
    switch (mystate)
      {
      case S_Init:
        return {};
      case S_ID_Final:
        {
          idtypeB_->unPop(idString_);
          Token_New out=idtypeB_->popBackToken();
          mystate=S_Init;
          return out;
        }
      case S_DATA_PARTIAL:
        if (valueB_->isInitial())
          {
            mystate=S_ID_Final;
            return Token_New(Token_New::ASSIGN);
          }
        else
          return valueB_->popBackToken();
      case  S_Data_Final:
        {
          Token_New out=valueB_->popBackToken();
          mystate=S_DATA_PARTIAL;
          return out;
        }
      case  S_Final:
        {
          valueB_->unpopData(data_.release());
          classx_.reset();
          mystate=S_Data_Final;
          return Token_New(Token_New::EOL);
        }
      }
  }



  std::pair<std::__cxx11::string, std::set<std::__cxx11::string> > buildByToken<ABC_Data_New *>::alternativesNext() const

  {
    std::pair<std::string, std::set<std::string> > out;
    switch (mystate)
      {
      case S_Init:
        return idtypeB_->alternativesNext();
      case S_ID_Final:
        return {"ClassName()",{Token_New::toString(Token_New::ASSIGN)}};

      case S_DATA_PARTIAL:
        return valueB_->alternativesNext();

      case S_Data_Final:
        return {"ClassNamr()",{alternatives::endOfLine()}};

      case S_Final:
        return {};
      }
  }





  void buildByToken<ABC_Data_New *>::reset_Type(Implements_Data_Type_New<ABC_Data_New *> *dataTy)
  {
    if (dataType_!=dataTy)
      {
        dataType_=dataTy;
        convertToClass_=dataType_->ConvertToClass();
        idtype_=dataType_->getElementType();
        idtypeB_->reset_Type(idtype_);
      }
  }





  bool buildByToken<Implements_Var>::pushIdToken(Token_New tok, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective)
  {
    if (!idB_->pushToken(tok,whyNot,masterObjective))
      {
        return false;
      }
    else
      {
        iv_.id=idB_->unloadVar();
        dataTy_=ivarType_->getElementType(parent(),iv_,whyNot,masterObjective,dataTy_);
        dataB_->reset_Type(dataTy_);
        mystate =ID1;
        return true;
      }


  }




  bool buildByToken<Implements_Var>::pushToken(Token_New tok, std::string *whyNot, const std::string &masterObjective)

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
        if (tok.tok()==Token_New::COLON)
          {
            mystate =ID2;
            return true;
          }
        else
          {
            *whyNot=objective+": is not a \":\"";
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
            iv_.data=dataB_->unloadVar();
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



  Token_New buildByToken<Implements_Var>::popBackToken()
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
        return Token_New(Token_New::COLON);
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
          dataB_->unpopData(iv_.data);
          iv_.data={};
          Token_New out=dataB_->popBackToken();
          if (dataB_->isInitial())
            mystate=ID2;
          else
            mystate=S_DATA_PARTIAL;
          return out;

        }
      }
  }



  void buildByToken<Implements_Var>::reset_Type(Implements_Data_Type_New<Implements_Var> *ivTy)
  {
    ivarType_=ivTy;
    idType_=ivarType_->getKeyType(parent())->clone();
    idB_->reset_Type(idType_);
    mystate=S_Init;
    iv_.clear();
  }


  buildByToken<StructureEnv_New*>::
  buildByToken(const StructureEnv_New *parent,
               const Implements_Data_Type_New
               <StructureEnv_New* > *typeVar):
    p_(parent),
    mystate(S_Init)
  ,varMapType_(typeVar)
  ,ivType_(typeVar->getElementType()->clone())
  ,ivBuild_(new buildByToken<Implements_Var>(StEnv_,ivType_))
  ,StEnv_(new StructureEnv_New(parent,varMapType_))
  ,iv_()
  ,iField_(0)

  {}

  bool buildByToken<StructureEnv_New *>::
  pushToken(Token_New tok, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective)

  {
    const std::string objective=masterObjective+": pushToken("+
        tok.str()+") fails";

    switch (mystate)
      {
      case S_Init:
        if (tok.tok()!=Token_New::EOL)
          {
            *whyNot=objective+" is not an end of line";
            return false;
          }
        else
          {
            mystate=S_Header2;
            return true;
          }
      case S_Header2:
        if (tok.tok()!=Token_New::LCB)
          {
            *whyNot=objective+" is not an "+Token_New::toString(Token_New::LCB);
            return false;
          }   else
          {
            mystate=S_Header_Final;
            return true;
          }
      case S_Header_Final:
        if (tok.tok()==Token_New::EOL)
          {
            mystate=S_Data_Separator_Final;
            return true;
          }
        else
          {
            *whyNot=masterObjective+": "+tok.str()
                +" is not end of line";
            return false;
          }
      case S_Data_Partial:
        if (!ivBuild_->pushToken(tok, whyNot, objective))
          {
            return false;
          }
        else
          {
            if(ivBuild_->isFinal())
              {
                iv_=ivBuild_->unloadVar();
                StEnv_->pushVar(iv_);
                if (varMapType_->hasAllFields(parent(),StEnv_,whyNot,masterObjective))
                  {
                    mystate=S_All;
                    return true;
                  }
                else
                  {
                    ++iField_;
                    ivType_=varMapType_->getElementType
                        (parent(),StEnv_,iField_,whyNot,masterObjective,ivType_);
                    ivBuild_->reset_Type(ivType_);
                    if (varMapType_->hasMandatoryFields
                        (parent(),StEnv_,whyNot,masterObjective))
                      {
                        mystate=S_Mandatory;
                        return true;
                      }
                    else
                      {
                        mystate=S_Data_Separator_Final;
                        return true;

                      }
                  }
              }
            else
              {
                mystate=S_Data_Partial;
                return true;
              }
          }
      case S_All:
        if (tok.tok()==Token_New::RCB)
          {
            mystate=S_Final;
            return true;
          }
        else
          {
            *whyNot=masterObjective+": expecte }, all fields filled";
            return false;
          }

      case S_Mandatory:
        if (tok.tok()==Token_New::RCB)
          {
            mystate=S_Final;
            return true;
          }
      case S_Data_Separator_Final:
        if (!ivBuild_->pushToken(tok, whyNot,objective))
          {
            return false;
          }
        else
          {
            mystate=S_Data_Partial;
            return true;
          }

      case S_Final:
        return false;
      }
  }



  
  std::pair<std::__cxx11::string, std::set<std::__cxx11::string> >
  buildByToken<StructureEnv_New *>::alternativesNext() const
  {
    std::pair<std::__cxx11::string, std::set<std::__cxx11::string> > out;
    switch (mystate)
      {
      case S_Init:
        return {this->StEnv_->myTypeId(),{alternatives::endOfLine()}};
      case S_Header2:
        return {this->StEnv_->myTypeId(),{Token_New::toString(Token_New::LCB)}};
      case S_Header_Final:
        return {this->StEnv_->myTypeId(),{alternatives::endOfLine()}};
      case S_Data_Partial:
      case S_Data_Separator_Final:
        return ivBuild_->alternativesNext();
      case S_All:
        return {this->StEnv_->myTypeId(),{Token_New::toString(Token_New::RCB)}};
      case S_Mandatory:
        out={this->StEnv_->myTypeId(),{Token_New::toString(Token_New::RCB)}};
        out+=ivBuild_->alternativesNext();
        return out;
      case S_Final:
        return out;
      }
    
  }
  
  Token_New buildByToken<StructureEnv_New *>::popBackToken()

  {

    Token_New out;
    switch (mystate)
      {
      case S_Init:
        return {};
      case S_Header2:
        mystate=S_Init;
        return Token_New(Token_New::EOL);
      case S_Header_Final:
        mystate=S_Header2;
        return Token_New(Token_New::LCB);
      case S_Mandatory:
      case S_Data_Separator_Final:
        if (StEnv_->empty())
          {
            mystate=S_Header_Final;
            return Token_New(Token_New::EOL);

          }
        else
          {
            iv_=StEnv_->popVar();
            --iField_;
            std::string whyNot;
            ivType_=varMapType_->getElementType
                (parent(),StEnv_,iField_,&whyNot,"",ivType_);
            ivBuild_->reset_Type(ivType_);
            ivBuild_->unPop(iv_);
            mystate=S_Data_Partial;
            return ivBuild_->popBackToken();

          }
      case S_Data_Partial:
        out= ivBuild_->popBackToken();
        if (! ivBuild_->isInitial())
          mystate=S_Data_Partial;
        else  if (varMapType_->hasMandatoryFields
                  (parent(),StEnv_))
          mystate=S_Mandatory;
        else
          mystate=S_Data_Separator_Final;
        return out;
      case S_All:
        {
          iv_=StEnv_->popVar();
          std::string whyNot;
          ivType_=varMapType_->getElementType
              (parent(),StEnv_,iField_,&whyNot,"",ivType_);
          ivBuild_->reset_Type(ivType_);
          ivBuild_->unPop(iv_);
          mystate=S_Data_Partial;
          return ivBuild_->popBackToken();
        }
      case S_Final:
        if (varMapType_->hasAllFields
            (parent(),StEnv_))
          mystate=S_All;
        else
          mystate=S_Mandatory;
        return Token_New(Token_New::RCB);

      }
  }



  bool buildByToken<StructureEnv_New *>::unpopData(ABC_Data_New *data)
  {
    auto cm=dynamic_cast<StructureEnv_New*>(data);
    if (cm!=nullptr)
      return unPop(cm);
    else
      return false;
  }


  void buildByToken<StructureEnv_New *>::reset_Type(const Implements_Data_Type_New<StructureEnv_New *> *typeVar)
  {

  }




  ABC_Data_New *buildByToken<StructureEnv_New *,true>::unloadData()
  {

    return unloadVar();
  }

  StructureEnv_New  *buildByToken<StructureEnv_New *>::unloadVar()
  {
    if (isFinal())
      {
        StructureEnv_New * out=StEnv_;
        StEnv_=new StructureEnv_New(parent(),varMapType_);
        iv_={};
        mystate=S_Init;
        iField_=0;
        return out;

      }
    else return nullptr;
  }



  bool buildByToken<StructureEnv_New *>::unPop(StructureEnv_New *var)
  {
    StEnv_=var;
    mystate=S_Final;
    iField_=var->numIdVars();
    return true;


  }



 /* template <typename Fn,typename R ,typename... Args>
   buildByToken<Implements_Closure_Value_R_Fn_Args_Function<Fn, R,Args...> *, true>::buildByToken
  (const StructureEnv_New *parent
   , const Implements_Data_Type_New<Implements_Closure_Value_R_Fn_Args_Function<Fn, R,Args...> *> *varType):
     p_(parent),
     mystate(S_Init)
   ,fnType_(varType), tupleType_(varType->getArgumentsType(parent)),
    tupleB_(varType->getArgumentsType(parent)->getBuildByToken(parent))
    ,valueCl_(new myC(varType)){}





   template <typename Fn,typename R , typename... Args>
  bool buildByToken<Implements_Closure_Value_R_Fn_Args_Function<Fn,R, Args...> *, true>::pushToken(Token_New tok, std::string *whyNot, const std::string &masterObjective)

  {
    const std::string objective=masterObjective+":  rejected token "+tok.str();
    switch (mystate)
      {
      case S_Init:
      case S_Closure_PARTIAL:
        if (tupleB_->pushToken(tok,whyNot,objective))
          {
             if (tupleB_->isFinal())
                  {
                    mystate =S_Closure_Final;
                    return true;
                  }
                else if (tupleB_->hasMandatory())
                  {
                    mystate=S_Closure_Mandatory;
                    return true;
                  }
                else
                  {
                    mystate=S_Closure_PARTIAL;
                    return true;
                  }
              }
        else return false;

      case S_Closure_Mandatory:
        if (tupleB_->pushToken(tok, whyNot,objective))
          {
            if (tupleB_->isFinal())
              {
                mystate =S_Closure_Final;
                return true;
              }
            else if (tupleB_->hasMandatory())
              {
                mystate=S_Closure_Mandatory;
                return true;
              }
            else
              {
                mystate=S_Closure_PARTIAL;
                return true;
              }
          }

      case S_Closure_Final:
        if (tok.tok()!=Token_New::EOL)
          {
            *whyNot=objective+" is not an end of line";
            return false;
          }
        else
          {
            valueCl_.reset(new myC(tupleB_.unloadVar()));
            mystate=S_Final;
            return true;
          }

      case S_Final:
        return false;
      }
  }



  template <typename Fn, typename R ,typename... Args>
  Token_New buildByToken<Implements_Closure_Value_R_Fn_Args_Function<Fn, R, Args...> *, true>::popBackToken()

  {
    switch (mystate)
      {
      case S_Init:
        return {};
      case S_Closure_PARTIAL:
      case S_Closure_Mandatory:
      case S_Closure_Final:
        {
              Token_New out=tupleB_->popBackToken();
              if (tupleB_->hasMandatory())
                {
                  mystate=S_Closure_Mandatory;
                  return out;
                }
              else
                {
                  mystate=S_Closure_PARTIAL;
                  return out;
                }
          }
      case  S_Final:
        {
          return {};
        }
      }
  }




  template <typename Fn, typename R ,typename... Args>
  std::pair<std::__cxx11::string, std::set<std::__cxx11::string> >
  buildByToken<Implements_Closure_Value_R_Fn_Args_Function<Fn,R, Args...> *, true>::alternativesNext() const

  {
    std::pair<std::string, std::set<std::string> > out;
    switch (mystate)
      {
      case S_Init:
      case S_Closure_PARTIAL:
        return tupleB_->alternativesNext();

      case S_Closure_Mandatory:
        {
          auto out=tupleB_->alternativesNext();
          out.second.insert(alternatives::endOfLine());
          return out;
        }

      case S_Closure_Final:
        return {"ClassNamr()",{alternatives::endOfLine()}};

      case S_Final:
        return {};
      }
  }





  template <typename Fn, typename R ,typename... Args>
  void buildByToken<Implements_Closure_Value_R_Fn_Args_Function<Fn, R,Args...> *, true>::
  reset_Type(Implements_Data_Type_New<ABC_Closure *> *dataTy)
  {
    if (fnType_!=dataTy)
      {
        fnType_=dataTy;
      }
  }

*/















  template class buildByToken<double>;
  template class buildByToken<std::vector<double>>;


  template class buildByToken<int>;
  template class buildByToken<std::vector<int>>;

  template class buildByToken<std::size_t>;
  template class buildByToken<std::set<double>>;

  template class buildByToken<std::string>;
  template class buildByToken<std::map<std::size_t,double>>;


  template class buildByToken<Markov_LA::M_Matrix<double>>;
  template  class buildByToken<Markov_LA::M_Matrix<std::size_t>>;



  template <typename T>
  ABC_Data_New *buildByToken<std::set<T> ,true>::unloadData()
  {
    return new Implements_Value_New<std::set<T>
        > (dataType_,unloadVar());
  }


  buildByToken<Implements_Var>::buildByToken(const StructureEnv_New *parent, const Implements_Data_Type_New<Implements_Var> *varType):
    p_(parent),
    mystate(S_Init),ivarType_(varType),idType_(varType->getKeyType(parent)->clone()),
    dataTy_(varType->getElementType(parent)->clone()),
    idB_(new buildByToken<std::string>(parent,idType_)),dataB_(new buildByToken<ABC_Data_New*>(parent,dataTy_)),iv_()

  {

  }

  void buildByToken<Implements_Var>::clear()
  {
    mystate=S_Init;
    iv_.clear();
    idB_->clear();
    dataB_->clear();

  }




  ABC_Data_New *buildByToken<Markov_CommandManagerVar *, true>::unloadData()
  {
    return nullptr;
  }

  const Implements_Identifier *getIdentifierType(const ABC_Type_of_Value *t)
  {
    return Identifier::types::idType::varType(t->typeId());
  }

  bool BuildByTokenString_Union::pushToken(Token_New tok, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective)
  {
    bool out=false;
    for (std::size_t i=0; i<vecValue.size(); ++i)
      {
        if (nPushedTokensIn[i]==nPushedTokens)
          {
            if (vecValue[i]->pushToken(tok,whyNot,masterObjective))
              {
                out=true;
                ++nPushedTokensIn[i];
              }
          }
      }
    if (out)
      ++nPushedTokens;
    return out;

  }

  std::pair<std::__cxx11::string, std::set<std::__cxx11::string> > BuildByTokenString_Union::alternativesNext() const
  {
    std::pair<std::string, std::set<std::string> > out;
    for (std::size_t i=0; i<vecValue.size(); ++i)
      {
        if (nPushedTokensIn[i]==nPushedTokens)
          {
            out+=vecValue[i]->alternativesNext();
          }
      }
    return out;

  }

  Token_New BuildByTokenString_Union::popBackToken()
  {
    Token_New out;
    if (nPushedTokens>0)
      {
        for (std::size_t i=0; i<vecValue.size(); ++i)
          {
            if (nPushedTokensIn[i]==nPushedTokens)
              {
                out=vecValue[i]->popBackToken();
                --nPushedTokensIn[i];
              }
          }
        --nPushedTokens;
      }
    return out;

  }

  bool BuildByTokenString_Union::isFinal() const
  {
    bool out=false;
    for (std::size_t i=0; i<vecValue.size(); ++i)
      {
        if (nPushedTokensIn[i]==nPushedTokens)
          {
            if (vecValue[i]->isFinal())
              out=true;
            else
              return false;
          }
      }
    return out;

  }

  bool BuildByTokenString_Union::isInitial() const
  {
    for (std::size_t i=0; i<vecValue.size(); ++i)
      {
        if ((nPushedTokensIn[i]==nPushedTokens)&& vecValue[i]->isInitial())
          {
            return true;
          }
      }
    return false;

  }

  BuildByTokenString_Union::~BuildByTokenString_Union(){}

  void BuildByTokenString_Union::clear()
  {
    for (std::size_t i=0; i<vecValue.size(); ++i)
      {
        vecValue[i]->clear();
        nPushedTokensIn[i]=0;

      }
    nPushedTokens=0;
  }

  ABC_Data_New *BuildByTokenString_Union::unloadData()
  {
    for (std::size_t i=0; i<vecValue.size(); ++i)
      {
        if ((nPushedTokensIn[i]==nPushedTokens)&& vecValue[i]->isFinal())
          {
            return vecValue[i]->unloadData();
          }
      }
    return nullptr;

  }

  bool BuildByTokenString_Union::unpopData(ABC_Data_New *data)
  {
    return false;
  }

  BuildByTokenString_Union::BuildByTokenString_Union(const StructureEnv_New *cm, const Identifier_Union *t)
    :p_(cm),
      uType_(t),vecValue(getBuildByTokenVector(cm,t)),nPushedTokensIn(),nPushedTokens(0){
    nPushedTokensIn=std::vector<std::size_t>(vecValue.size(),0);
  }
































};




namespace Markov_IO_New_Test{

  void test()
  {
    /*
             StructureEnv_New* cm(nullptr,"cm","cm","","");
             Implements_Data_Type_New<std::set<double>> dset(&cm,"set_double",Implements_Data_Type_New<std::set<double>>::ClassName(),"","","",nullptr,nullptr,nullptr,{},nullptr,nullptr);

             Implements_Data_Type_New<std::vector<double>> dv(&cm,"set_double",Implements_Data_Type_New<std::set<double>>::ClassName(),"","","",nullptr,nullptr,nullptr,{},nullptr,nullptr);

             Implements_Data_Type_New<Markov_LA::M_Matrix<double>> dmt(&cm,"set_double",Implements_Data_Type_New<std::set<double>>::ClassName(),"","","",nullptr,nullptr,nullptr,{},nullptr,nullptr,nullptr,nullptr,false,false);


             Implements_Data_Type_New<std::pair<std::string,double>> dp(&cm,"set_double",Implements_Data_Type_New<std::set<double>>::ClassName(),"","","","",nullptr,nullptr,nullptr,nullptr,{});

             Implements_Data_Type_New<std::map<std::string,double>> dm(&cm,"set_double",Implements_Data_Type_New<std::set<double>>::ClassName(),"","","","",nullptr,nullptr,nullptr,nullptr,{},nullptr,nullptr);



             buildByToken<std::set<double>> b(&cm,&dset);
             std::string whynot;
             b.pushToken(Token_New('{'), &whynot," const std::string& masterObjective");
             buildByToken<std::pair<std::string,double>> pp(&cm,&dp);
             buildByToken<std::map<std::string,double>> pm(&cm,&dm);

             buildByToken<std::vector<double>> v(&cm,&dv);

             buildByToken<Markov_LA::M_Matrix<double>> mat(&cm,&dmt);
         */
  }


}







