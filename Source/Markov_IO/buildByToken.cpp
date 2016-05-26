#include "Markov_IO/buildByToken.h"
#include "Markov_Console/Markov_CommandManager.h"

#include "Markov_IO/Var.h"
#include "Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_IO/buildByTokenTempl.h"

namespace Markov_IO_New {

  const StructureEnv_New* ABC_BuildByToken::parent() const
  {
    return parent_;
  }

  ABC_BuildByToken::ABC_BuildByToken(const StructureEnv_New *p):parent_(p){}



  template<>
  std::pair<std::string, std::set<std::string> > buildByToken<std::string>::alternativesNext() const
  {

    std::string whynot;
    std::string id=parent()->dataToId(varType_,&whynot,"");
    return {id,varType_->alternativeNext(this->parent())};
  }




  template<typename T>
  buildByToken<std::vector<T> >::buildByToken(const StructureEnv_New *parent, const Implements_Data_Type_New<std::vector<T> > *vecType)
    :
      ABC_BuildByToken(parent),
      mystate(S_Init),
      x_(),
      valueBuild_(vecType->getElementBuildByToken(parent)),
      varType_(vecType){}




  template<typename T>
  std::pair<std::__cxx11::string, std::set<std::__cxx11::string> > Markov_IO_New::buildByToken<Markov_LA::M_Matrix<T> >::alternativesNext() const
  {
    std::pair<std::string,std::set<std::string>> out;
    switch (mystate) {
      case S_Init:

        if ((hasFixedCols_)&&(nCols_==0))
          {
            return {parent()->dataToId(dataType_),{alternatives::endOfLine()}};
          }
        else if (nCols_==0)
          {
            out=eleB_->alternativesNext();
            out+= {parent()->dataToId(dataType_),{alternatives::endOfLine()}};
            return out;
          }
        else
          {
            return eleB_->alternativesNext();
          }

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
        return {parent()->dataToId(dataType_),{alternatives::endOfLine()}};

      case S_PInit_NBoth:
      case S_PEOL_NBoth:
      case S_PData_NBoth:
      case S_PBothData_NBoth:
      case S_PBothEOL_NBoth:
        {
          out=eleB_->alternativesNext();
          out+= {parent()->dataToId(dataType_),{alternatives::endOfLine()}};
          return out;
        }
      case S_PEOL_NFinal:
      case S_PBothEOL_NFinal:
      case S_PInit_NFinal:
        return {};
        break;

      }

  }



  buildByToken<ABC_Data_New *>::buildByToken(const StructureEnv_New *parent
                                             , const Implements_Data_Type_New<ABC_Data_New*> *varType,
                                             bool convertTOClass):
    ABC_BuildByToken(parent),
    mystate(S_Init),dataType_(varType),idtypeB_(varType->getVarIdentifierBuildByToken(parent)),
    valueB_(nullptr),data_(nullptr),convertToClass_(convertTOClass),classx_(nullptr){}




  bool buildByToken<ABC_Data_New *>::pushToken(Token_New tok, std::string *whyNot, const std::string &masterObjective)

  {
    const std::string objective=masterObjective+":  rejected token "+tok.str();
    switch (mystate)
      {
      case S_Init:
        if (idtypeB_->pushToken(tok,whyNot,objective))
          {
            auto idTypeS=idtypeB_->unloadVar();
            valueType_=parent()->idToType(idTypeS,whyNot,objective);
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
          if (tok.tok()!=Token_New::EQ)
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
        if (tok.tok()==Token_New::EOL)
          {
            mystate =S_Final;
            return true;
          }
        else
          {
            *whyNot=objective+": is not an end of line";
            return false;
          }

      case S_Final:
      default:
        return false;
      }
  }






  void buildByToken<ABC_Data_New *>::reset_Type(Implements_Data_Type_New<ABC_Data_New *> *dataTy)
  {
    if (dataType_!=dataTy)
      {
        dataType_=dataTy;
        convertToClass_=dataType_->ConvertToClass();
        std::string whyNot,masterObjective;
        idtype_=dataType_->getElementType(parent(),data_.get(),&whyNot,masterObjective,idtype_);
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
            mystate =S_Data_Final;
            return true;
          }
        else
          {
            mystate=S_DATA_PARTIAL;
            return true;
          }
      case S_Data_Final:
        if (tok.tok()==Token_New::EOL)
          {
            mystate =S_Final;
            return true;
          }
        else
          {
            *whyNot=objective+": is not an end of line";
            return false;
          }

      case S_Final:
      default:
        return false;
      }
  }





  void buildByToken<Implements_Var>::reset_Type(Implements_Data_Type_New<Implements_Var> *ivTy)
  {
    ivarType_=ivTy;
    std::string whyNot,masterObjective;
    idType_=ivarType_->getKeyType(parent(),iv_,&whyNot,masterObjective,idType_);
    idB_->reset_Type(idType_);
  }


  buildByToken<StructureEnv_New*>::
  buildByToken(const StructureEnv_New *parent,
               const Implements_Data_Type_New
               <StructureEnv_New* > *typeVar):
    ABC_BuildByToken(parent),
    mystate(S_Init)
    ,varMapType_(typeVar)
    ,ivType_(typeVar->getElementType()->clone())
    ,ivBuild_(new buildByToken<Implements_Var>(StEnv_,ivType_))
    ,StEnv_(new StructureEnv_New(parent,""))
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
                ++iField_;
                ivType_=varMapType_->getElementType
                    (parent(),StEnv_,iField_,whyNot,masterObjective,ivType_);
                ivBuild_->reset_Type(ivType_);
                mystate=S_Data_Separator_Final;
                return true;
              }
            else
              {
                mystate=S_Data_Partial;
                return true;
              }
          }
      case S_Data_Separator_Final:
        if (varMapType_->hasMandatoryFields(parent(),StEnv_,whyNot,masterObjective))
          {
            if (tok.tok()==Token_New::RCB)
              {
                mystate=S_Final;
                return true;
              }
            else if (varMapType_->hasAllFields(parent(),StEnv_,whyNot,masterObjective))
              {
                *whyNot=masterObjective+": expecte }, all fields filled";
                return false;
              }
          }
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


  void buildByToken<StructureEnv_New *>::reset_Type(const Implements_Data_Type_New<StructureEnv_New *> *typeVar)
  {

  }




  ABC_Data_New *Markov_IO_New::buildByToken<StructureEnv_New *>::unloadData()
  {

    return unloadVar();
  }


  build_Command_Input::build_Command_Input(
      const StructureEnv_New *cm,
      const Implements_Command_Type_New * vCmd):
    buildByToken<Markov_IO_New::Implements_Command_Arguments *> (cm,vCmd),
     cmdty_(vCmd), cmdArg_(new Implements_Command_Arguments(cm,"_Arg"+cm->dataToId(vCmd))),
 ivType_(vCmd->getElementType()->clone()),
  iv_(),
ivB_(new build_Argument_Input(cmdArg_,ivType_))
  ,iArg_(0)
  {}

  void build_Command_Input::reset_Type(const Implements_Command_Type_New *cmdty)
  {

    buildByToken<StructureEnv_New*>::reset_Type (cmdty);
     cmdty_=cmdty;
     cmdArg_->reset();
     ivType_=cmdty->getElementType()->clone();
      iv_;
      ivB_->reset_Type(ivType_);
   iArg_=0;

  }

  bool build_Command_Input::pushToken(Token_New t, std::string *whyNot, const std::string &masterObjective)

  {
    const std::string objective=masterObjective;
    switch (mystate)
      {

      case  S_Mandatory_Final:
        if (t.tok()==Token_New::EOL)
          {
            mystate=S_Final;
            return true;
          }
        [[clang::fallthrough]];
      case S_Init:
      case S_Input_Partial:
      case S_Argument_Partial:
        if (!ivB_->pushToken(t,whyNot,objective))
          return false;
        else if (!ivB_->isFinal())
          {
            mystate=S_Argument_Partial;
            return true;
          }
        else
          {
            iv_=ivB_->unloadVar();
            cmdArg_->pushVar(iv_);
            if (cmdty_->hasAllFields(parent(),cmdArg_))
              {
                mystate=S_Input_Final;
                return true;
              }
            else
              {
               ivType_=cmdty_->getElementType
                   (parent(),cmdArg_,iArg_,whyNot,masterObjective,ivType_);
                if (ivType_==nullptr)
                  return false;
                ivB_->reset_Type(ivType_);
                bool isMandatory=cmdty_->hasMandatoryFields(parent(),cmdArg_);
                if (!isMandatory)
                  {
                    mystate=S_Input_Partial;
                  }
                else
                  mystate=S_Mandatory_Final;
                return true;
              }

          }
      case S_Input_Final:
        if (t.tok()!=Token_New::EOL)
          {
            *whyNot=objective+": no more inputs accepted "+
                t.str()+ " is not an end of line";
            return false;
          }
        else
          {
            mystate=S_Final;
            return true;
          }
      case S_Final:
        return false;
      }

  }




  std::pair<std::__cxx11::string, std::set<std::__cxx11::string> > build_Command_Input::alternativesNext() const

  {

    std::pair<std::__cxx11::string, std::set<std::__cxx11::string> >
        out={parent()->dataToId(cmdty_),{alternatives::endOfLine()}};

    switch (mystate)
      {
      case  S_Mandatory_Final:
        out+=ivB_->alternativesNext();
        return out;
      case S_Init:
      case S_Input_Partial:
      case S_Argument_Partial:
        return ivB_->alternativesNext();
      case S_Input_Final:
        return out;
      case S_Final:
        return {};
      }

  }





  build_Statement::build_Statement(
      Markov_CommandManagerVar *p
      , const Implements_Data_Type_New<Implements_Var> *varType
      ,const Implements_Data_Type_New<std::string> *idCmd
      , bool convertToClass):
    ABC_BuildByToken(p),
    mystate(S_Init),
    v_(varType->getBuildByToken(p)),
    idCmd_(idCmd->getBuildByToken(p)),
    cmdTy_(nullptr),
    c_(nullptr),

    cmv_(nullptr),
    x_()

     {}

  void build_Statement::clear()
  {
    delete cmv_;
    v_->clear();
    idCmd_->clear();
    delete c_;
    c_=nullptr;
    mystate=S_Init;
    x_.clear();
    cmv_=nullptr;

  }

  bool build_Statement::pushToken
  (Token_New t
   , std::__cxx11::string *whyNot
   , const std::__cxx11::string &masterObjective)

  {
    const std::string objective=masterObjective;
    switch (mystate)
      {
      case S_Init:
        if (idCmd_->pushToken(t, whyNot,objective))
          {
            if (idCmd_->isFinal())
              {
                std::string idC=idCmd_->unloadVar();
                std::string whynot;
                 cmdTy_=parent()->idToCommand(idC,&whynot,"");
                 c_->reset_Type(cmdTy_);
                if (c_->isFinal())
                  {
                    cmv_=c_->unloadVar();
                    mystate=S_Command_Final;
                  }
                else
                  mystate=S_Command_Partial;
                return true;
              }
            else
              {
                mystate=S_Command_Id_Partial;
                return true;
              }
          }
        else if (v_->pushToken(t, whyNot, objective))
          {
            mystate=S_Expression_Partial;
            return true;
          }
        else
          {
            if (t.tok()==Token_New::EOL)
              return true;
            else
              {
                *whyNot=objective+": unknown command or variable";
                return false;
              }
          }
      case S_Command_Id_Partial:
        if (idCmd_->pushToken(t, whyNot,objective))
          {
            if (idCmd_->isFinal())
              {
                std::string idC=idCmd_->unloadVar();
                std::string whynot;
                 cmdTy_=parent()->idToCommand(idC,&whynot,"");
                 c_->reset_Type(cmdTy_);
                if (c_->isFinal())
                  {
                    cmv_=c_->unloadVar();
                    mystate=S_Command_Final;
                  }
                else
                  mystate=S_Command_Partial;
                return true;
              }
            else
              {
                mystate=S_Command_Id_Partial;
                return true;
              }
          }
        else
          {
            return false;
          }
      case S_Command_Partial:
        if (!c_->pushToken(t, whyNot,objective))
          {
            return false;
          }
        else
          {
            if (c_->isFinal())
              {
                cmv_=c_->unloadVar();
                mystate=S_Command_Final;
              }
            else
              mystate=S_Command_Partial;
            return true;
          }
      case S_Expression_Partial:
        if (!v_->pushToken(t, whyNot,objective))
          {
            return false;
          }
        else
          {
            if (v_->isFinal())
              {
                mystate=S_Expression_Final;
                x_=v_->unloadVar();
              }
            else
              mystate=S_Expression_Partial;
            return true;
          }
      case S_Command_Final:
      case S_Expression_Final:
        return false;
      }

  }


  build_Statement::build_Statement(Markov_CommandManagerVar *p):
    build_Statement(p,p->getVarType(),p->getIdCmd(),true){}





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
  ABC_Data_New *Markov_IO_New::buildByToken<std::vector<T> >::unloadData()
  {
    return new Implements_Value_New<std::vector<T>
        >(parent()->dataToId(varType_),unloadVar());
  }

  template <typename T>
  ABC_Data_New *buildByToken<std::set<T> >::unloadData()
  {
    return new Implements_Value_New<std::set<T>
        > (parent()->dataToId(dataType_),unloadVar());
  }


  template <typename T>
  Token_New buildByToken<Markov_LA::M_Matrix<T> >::popBackToken()
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





namespace Markov_IO {

  std::string ABC_BuildByToken::ClassName()
  {
    return "ABC_BuildByToken";
  }

  std::set<std::string> ABC_BuildByToken::SuperClasses()
  {
    return ABC_Base::SuperClasses()+ClassName();
  }

  std::string ABC_BuildByToken::myClass() const
  {
    return ClassName();

  }

  std::set<std::string> ABC_BuildByToken::mySuperClasses() const
  {
    return SuperClasses();
  }



  ABC_BuildByToken::~ABC_BuildByToken(){}



  const ABC_Value *ABC_BuildByToken::parent() const
  {
    return parent_;
  }

  ABC_BuildByToken::ABC_BuildByToken(const ABC_Value *p):parent_(p){}




  std::string ABC_BuildByToken::getErrorMessage(std::string errorMessage)
  {
    return "Error in "+myClass()+" : "+errorMessage;
  }

  std::string ABC_BuildByToken::getErrorMessage(Token_New::Value expected, Token_New found)
  {
    return "Error in "+myClass()+" : expected: "
        +Token_New::toString(expected)+"; found: "
        +found.str();
  }

  std::string ABC_BuildByToken::getErrorMessage(std::string expected, Token_New found)
  {
    return "Error in "+myClass()+" : expected: "
        +expected+"; found: "
        +found.str();
  }

  std::string ABC_BuildByToken::getErrorMessage(const Markov_Console::ABC_CommandVar* cmd,
                                                const ABC_Value* input, const std::string& error)
  {
    std::string err="Error in command: "+cmd->id() +", field: "+input->id()+" "+error;
    return err;
  }

  std::string ABC_BuildByToken::getErrorMessage(const Markov_Console::ABC_CommandVar* cmd,const std::string& error)
  {
    std::string err="Error in "+myClass()+" for command "+cmd->id() +" "+error;
    return err;
  }


  std::string  ABC_BuildByToken::getErrorMessage(const Markov_Console::ABC_CommandVar* cmd,
                                                 const ABC_Value* input, Token_New found)
  {
    std::string err="Error in "+myClass()+" for command "+cmd->id() +"  : expected: ";
    for (unsigned i=0; i<input->numChilds(); ++i)
      {
        std::string idith=input->ith_ChildName(i);
        auto oith=input->idToValue(idith);
        if (oith->empty())
          err+=oith->id()+" ("+oith->myVar()+")"+ " or ";
      }
    err.substr(0,err.size()-3);
    err+="; found: " +found.str();
    return err;
  }



  std::string ABC_BuildByToken::setErrorsMessage(std::vector<Token_New::Value> expected, Token_New found)
  {
    std::string estr="Error in "+myClass()+" : expected: ";
    for (auto ex:expected)
      estr+=Token_New::toString(ex)+" or ";
    estr.substr(0,estr.size()-3);
    estr+="; found: " +found.str();
    return estr;
  }




  template class buildByToken<double>;
  template class buildByToken<std::vector<double>>;


  template class buildByToken<int>;
  template class buildByToken<std::vector<int>>;

  template class buildByToken<std::size_t>;
  template class buildByToken<std::vector<std::size_t>>;

  template class buildByToken<std::string>;
  template class buildByToken<std::vector<std::string>>;



  template class buildByToken<std::set<double>>;



  template class buildByToken<Markov_LA::M_Matrix<double>>;

  std::string build_ABC_Value::ClassName()
  {
    return "build_ABC_Value";
  }

  std::set<std::string> build_ABC_Value::SuperClasses()
  {
    return ABC_Value_ByToken::SuperClasses()+ClassName();
  }

  std::string build_ABC_Value::myClass() const
  {
    return ClassName();

  }

  build_ABC_Value::build_ABC_Value(const ABC_Var *p):
    ABC_Value_ByToken(p),
    mystate{S_Init}
  ,x_(nullptr)
  ,id_(p)
  ,var_(nullptr)
  ,previousTok_{}
  , prevTokens_{}{}

  void build_ABC_Value::clear()
  {
    ABClass_buildByToken::clear();
    delete x_;
    mystate=S_Init;
    x_=nullptr;


  }

  ABC_Value *build_ABC_Value::unloadVar()
  {
    if (isFinal())
      {
        auto out=x_;
        mystate=S_Init;
        x_=nullptr;

        return out;
      }
    else return nullptr;
  }

  bool build_ABC_Value::unPop(ABC_Value *var)
  {
    if (x_!=var)
      {
        auto v=createBuild_Value(parent(),var);
        if (v!=nullptr)
          {
            delete x_;
            x_=var;
            delete var_;
            var_=v;
            mystate=S_Final;
            return true;
          }
        else return false;
      }
    else
      return true;
  }

  bool build_ABC_Value::pushToken( Token_New t, std::string& errorMessage)
  {
    switch (mystate)
      {
      case S_Init:
      case S_ID_Partial:
        if (!id_.pushToken(t,errorMessage))
          {
            errorMessage= ABC_BuildByToken::getErrorMessage(errorMessage);
            return false;
          }
        else if (id_.isFinal())
          {

            mystate=S_ID_Final;
            return true;
          }
        else
          {
            mystate=S_ID_Partial;
            return true;
          }
        break;
      case S_ID_Final:
        if (t.tok()==Token_New::BEGIN)
          {
            var_=new build_Implements_Complex_Value(id_.unloadVar());
            var_->pushToken(t,errorMessage);
            mystate=S_Var_Partial;
            return true;
          }
        else if (t.tok()==Token_New::ASSIGN)
          {
            prevTokens_.push_back(t);
            mystate=S_NOT_Complex_Und;
            return true;
          }
        else
          {
            ABC_BuildByToken::setErrorsMessage({Token_New::BEGIN,Token_New::ASSIGN},t);
            return false;
          }
        break;
      case S_Var_Partial:
        if(!var_->pushToken(t,errorMessage))
          {
            errorMessage= ABC_BuildByToken::getErrorMessage(errorMessage);
            return false;
          }
        else if (var_->isFinal())
          {
            mystate=S_Final;
            x_=var_->unloadVar();
            return true;
          }
        else
          {
            mystate=S_Var_Partial;
            return true;
          }
        break;
      case S_NOT_Complex_Und:
        if (t.tok()==Token_New::MUL)
          {
            var_=new build_Implements_Refer_Var(id_.unloadVar());
          }
        else if (t.tok()==Token_New::REAL)
          {
            var_=new build_Implements_Simple_Value<double>(id_.unloadVar());
          }
        else if (t.tok()==Token_New::INTEGER)
          {
            var_=new build_Implements_Simple_Value<int>(id_.unloadVar());
          }
        else if (t.tok()==Token_New::UNSIGNED)
          {
            var_=new build_Implements_Simple_Value<std::size_t>(id_.unloadVar());
          }
        else if (t.tok()==Token_New::IDENTIFIER)
          {
            var_=new build_Implements_Simple_Value<std::string>(id_.unloadVar());
          }
        else if (t.tok()==Token_New::EOL)
          {
            prevTokens_.push_back(t);
            mystate=S_SimpMult_Und;
            return true;
          }
        else
          {
            ABC_BuildByToken::setErrorsMessage({Token_New::MUL
                                                ,Token_New::REAL
                                                ,Token_New::UNSIGNED
                                                ,Token_New::INTEGER
                                                ,Token_New::IDENTIFIER
                                                ,Token_New::EOL}
                                               ,t);
            return false;
          }
        prevTokens_.push_back(t);
        for (auto to:prevTokens_)
          if (var_->pushToken(to,errorMessage))
            {
              errorMessage= ABC_BuildByToken::getErrorMessage(errorMessage);
              return false;
            }

        mystate=S_Var_Partial;
        return true;
        break;
      case S_SimpMult_Und:
        if (t.tok()==Token_New::LSB)
          {
            prevTokens_.push_back(t);
            mystate=S_Vec_Und;
            return true;
          }
        else if (t.tok()==Token_New::LCB)
          {
            prevTokens_.push_back(t);
            mystate=S_Set_or_Map;
            return true;
          }
        else if (t.tok()==Token_New::REAL)
          {
            var_=new build_Implements_Simple_Value<Markov_LA::M_Matrix<double>>(id_.unloadVar());
          }
        else if (t.tok()==Token_New::INTEGER)
          {
            var_=new build_Implements_Simple_Value<Markov_LA::M_Matrix<int>>(id_.unloadVar());
          }
        else if (t.tok()==Token_New::UNSIGNED)
          {
            var_=new build_Implements_Simple_Value<Markov_LA::M_Matrix<std::size_t>>(id_.unloadVar());
          }
        else
          {
            ABC_BuildByToken::setErrorsMessage({Token_New::LCB
                                                ,Token_New::LSB
                                                ,Token_New::REAL
                                                ,Token_New::UNSIGNED
                                                ,Token_New::INTEGER
                                               }
                                               ,t);
            return false;
          }

        prevTokens_.push_back(t);

        for (auto to:prevTokens_)
          if (var_->pushToken(to, errorMessage))
            {
              errorMessage=ABC_BuildByToken::getErrorMessage(errorMessage);
              return false;
            }

        mystate=S_Var_Partial;
        return true;
        break;
      case S_Vec_Und:
        if (t.tok()==Token_New::REAL)
          {
            var_=new build_Implements_Simple_Value<std::vector<double>>(id_.unloadVar());
          }
        else if (t.tok()==Token_New::INTEGER)
          {

            var_=new build_Implements_Simple_Value<std::vector<int>>(id_.unloadVar());
          }

        else if (t.tok()==Token_New::UNSIGNED)
          {

            var_=new build_Implements_Simple_Value<std::vector<std::size_t>>(id_.unloadVar());
          }
        else if ((t.tok()==Token_New::IDENTIFIER)||(t.tok()==Token_New::STRING))
          {

            var_=new build_Implements_Simple_Value<std::vector<std::string>>(id_.unloadVar());
          }
        else
          {
            ABC_BuildByToken::setErrorsMessage({Token_New::MUL
                                                ,Token_New::REAL
                                                ,Token_New::UNSIGNED
                                                ,Token_New::INTEGER
                                                ,Token_New::IDENTIFIER
                                                ,Token_New::STRING}
                                               ,t);
            return false;
          }

        // update var_ processing also all the tokens in buffer
        prevTokens_.push_back(t);

        for (auto to:prevTokens_)
          if (var_->pushToken(to, errorMessage))
            {
              errorMessage=ABC_BuildByToken::getErrorMessage(errorMessage);
              return false;
            }
        mystate=S_Var_Partial;
        return true;
        break;
      case S_Set_or_Map:
        // does not allow set of vectors nor maps with vectors as keys
        // we can include those by including the [ token
        if (t.isReal()||t.tok()==Token_New::IDENTIFIER
            ||t.tok()==Token_New::STRING)
          {
            prevTokens_.push_back(t);
            previousTok_=t;
            mystate=S_Set_or_Map2;
            return true;
          }
        else
          {
            ABC_BuildByToken::setErrorsMessage({Token_New::REAL
                                                ,Token_New::UNSIGNED
                                                ,Token_New::INTEGER
                                                ,Token_New::IDENTIFIER
                                                ,Token_New::STRING}
                                               ,t);
            return false;
          }
      case S_Set_or_Map2:
        if (t.tok()==Token_New::COLON)
          {
            prevTokens_.push_back(t);
            mystate=S_Map_Und;
            return true;
          }
        // else it is a set or nothing
        else if (previousTok_.tok()==Token_New::REAL&&t.isReal())
          {
            var_=new build_Implements_Simple_Value<std::set<double>>(id_.unloadVar());
          }
        else if (previousTok_.tok()==Token_New::INTEGER&&t.isInteger())    {
            var_=new build_Implements_Simple_Value<std::set<int>>(id_.unloadVar());
          }
        else if (previousTok_.tok()==Token_New::UNSIGNED&&t.isCount())    {
            var_=new build_Implements_Simple_Value<std::set<std::size_t>>(id_.unloadVar());
          }
        else if ((previousTok_.tok()==Token_New::IDENTIFIER
                  ||previousTok_.tok()==Token_New::STRING)
                 &&(t.tok()==Token_New::IDENTIFIER
                    ||t.tok()==Token_New::STRING))
          {
            var_=new build_Implements_Simple_Value<std::set<std::string>>(id_.unloadVar());
          }
        else
          {
            ABC_BuildByToken::getErrorMessage({Token_New::COLON,static_cast<char>(previousTok_.tok())},t);
            return false;
          }
        prevTokens_.push_back(t);

        for (auto to:prevTokens_)
          if (var_->pushToken(to, errorMessage))
            {
              errorMessage=ABC_BuildByToken::getErrorMessage(errorMessage);
              return false;
            }
        mystate=S_Var_Partial;
        return true;

        break;
      case S_Map_Und:
        if (previousTok_.tok()==Token_New::REAL)
          {
            if (t.tok()==Token_New::REAL)
              {
                var_=new build_Implements_Simple_Value<std::map<double,double>>(id_.unloadVar());
              }
            else   if (t.tok()==Token_New::INTEGER)
              {
                var_=new build_Implements_Simple_Value<std::map<double,int>>(id_.unloadVar());
              }
            else   if (t.tok()==Token_New::UNSIGNED) {
                var_=new build_Implements_Simple_Value<std::map<double,std::size_t>>(id_.unloadVar());
              }
            else   if ((t.tok()==Token_New::IDENTIFIER||t.tok()==Token_New::STRING)) {
                var_=new build_Implements_Simple_Value<std::map<double,std::string>>(id_.unloadVar());
              }
          }
        if (previousTok_.tok()==Token_New::INTEGER)
          {
            if (t.tok()==Token_New::REAL)
              {
                var_=new build_Implements_Simple_Value<std::map<int,double>>(id_.unloadVar());
              }
            else   if (t.tok()==Token_New::INTEGER)
              {
                var_=new build_Implements_Simple_Value<std::map<int,int>>(id_.unloadVar());
              }
            else   if (t.tok()==Token_New::UNSIGNED) {
                var_=new build_Implements_Simple_Value<std::map<int,std::size_t>>(id_.unloadVar());
              }
            else   if ((t.tok()==Token_New::IDENTIFIER||t.tok()==Token_New::STRING)) {
                var_=new build_Implements_Simple_Value<std::map<int,std::string>>(id_.unloadVar());
              }
          }
        if (previousTok_.tok()==Token_New::UNSIGNED)
          {
            if (t.tok()==Token_New::REAL)
              {
                var_=new build_Implements_Simple_Value<std::map<std::size_t,double>>(id_.unloadVar());
              }
            else   if (t.tok()==Token_New::INTEGER)
              {
                var_=new build_Implements_Simple_Value<std::map<std::size_t,int>>(id_.unloadVar());
              }
            else   if (t.tok()==Token_New::UNSIGNED) {
                var_=new build_Implements_Simple_Value<std::map<std::size_t,std::size_t>>(id_.unloadVar());
              }
            else   if ((t.tok()==Token_New::IDENTIFIER||t.tok()==Token_New::STRING)) {
                var_=new build_Implements_Simple_Value<std::map<std::size_t,std::string>>(id_.unloadVar());
              }
          }
        if ((previousTok_.tok()==Token_New::IDENTIFIER
             ||previousTok_.tok()==Token_New::STRING))

          {
            if (t.tok()==Token_New::REAL)
              {
                var_=new build_Implements_Simple_Value<
                    std::map<std::string,double>>(id_.unloadVar());
              }
            else   if (t.tok()==Token_New::INTEGER)
              {
                var_=new build_Implements_Simple_Value<
                    std::map<std::string,int>>(id_.unloadVar());
              }
            else   if (t.tok()==Token_New::UNSIGNED) {
                var_=new build_Implements_Simple_Value
                    <std::map<std::string,std::size_t>>(id_.unloadVar());
              }
            else   if ((t.tok()==Token_New::IDENTIFIER||t.tok()==Token_New::STRING)) {
                var_=new build_Implements_Simple_Value<
                    std::map<std::string,std::string>>(id_.unloadVar());
              }
          }
        else
          {
            ABC_BuildByToken::setErrorsMessage({Token_New::MUL
                                                ,Token_New::REAL
                                                ,Token_New::UNSIGNED
                                                ,Token_New::INTEGER
                                                ,Token_New::IDENTIFIER
                                                ,Token_New::EOL}
                                               ,t);
            return false;
          }
        prevTokens_.push_back(t);

        for (auto to:prevTokens_)
          if (var_->pushToken(to, errorMessage))
            {
              errorMessage=ABC_BuildByToken::getErrorMessage(errorMessage);
              return false;
            }
        mystate=S_Var_Partial;
        return true;
        break;

      case S_Final:
      default:
        return false;
        break;

      }

  }

  std::pair<std::string, std::set<std::string>> build_ABC_Value::alternativesNext(Markov_Console::Markov_CommandManagerVar *cm) const
  {
    switch (mystate)
      {
      case S_Init:
      case S_ID_Partial:
        return id_.alternativesNext(cm);
        break;
      case S_ID_Final:
        return {"class or object",{Token_New::toString(Token_New::BEGIN)
                  , Token_New::toString(Token_New::ASSIGN)}};
        break;
      case S_NOT_Complex_Und:
        return {"simple object",{Token_New::toString(Token_New::EOL)
                  ,Token_New::toString(Token_New::MUL)
                  ,Implements_Simple_Value<double>::ClassName()
                  ,Implements_Simple_Value<std::size_t>::ClassName()
                  ,Implements_Simple_Value<int>::ClassName()
                  ,Implements_Simple_Value<std::string>::ClassName()}};
        break;
      case S_SimpMult_Und:
        return {"complex object",{Token_New::toString(Token_New::LSB)  //map or set
                  ,Token_New::toString(Token_New::LCB)  //vector
                  ,Implements_Simple_Value<double>::ClassName()   //matrix of doubles
                  ,Implements_Simple_Value<std::size_t>::ClassName()  // matrix of counts
                  ,Implements_Simple_Value<int>::ClassName()}};  //matrix of integers
        break;
      case S_Vec_Und:
        return {"Vector of",{Implements_Simple_Value<double>::ClassName()
                  ,Implements_Simple_Value<std::size_t>::ClassName()
                  ,Implements_Simple_Value<int>::ClassName()
                  ,Implements_Simple_Value<std::string>::ClassName()}};
        break;
      case S_Set_or_Map:
        return {"set or map",{Implements_Simple_Value<double>::ClassName()
                  ,Implements_Simple_Value<std::size_t>::ClassName()
                  ,Implements_Simple_Value<int>::ClassName()
                  ,Implements_Simple_Value<std::string>::ClassName()}};
        break;
      case S_Set_or_Map2:
        switch (previousTok_.tok()) {
          case Token_New::REAL:
            return {"map or set",{Token_New::toString(Token_New::COLON)  //map
                      ,Implements_Simple_Value<double>::ClassName()}}; //set of doubles
            break;
          case Token_New::INTEGER:
            return {"map or set",{Token_New::toString(Token_New::COLON)  //map
                      ,Implements_Simple_Value<int>::ClassName()}}; //set of doubles
            break;
          case Token_New::UNSIGNED:
            return {"map or set",{Token_New::toString(Token_New::COLON)  //map
                      ,Implements_Simple_Value<std::size_t>::ClassName()}}; //set of doubles
            break;
          case Token_New::IDENTIFIER:
          case Token_New::STRING:

            return {"map or set",{Token_New::toString(Token_New::COLON)  //map
                      ,Implements_Simple_Value<std::string>::ClassName()}}; //set of doubles
            break;

          default:
            return {};
            break;
          }
        break;
      case S_Map_Und:
        return {"map ",{Implements_Simple_Value<double>::ClassName()
                  ,Implements_Simple_Value<std::size_t>::ClassName()
                  ,Implements_Simple_Value<int>::ClassName()
                  ,Implements_Simple_Value<std::string>::ClassName()}};
        break;
      case S_Var_Partial:
        return var_->alternativesNext(cm);
        break;
      case S_Final:
      default:
        return {};
        break;
      }

  }

  Token_New build_ABC_Value::popBackToken()
  {

    switch (mystate)
      {
      case S_Init:
        return {};
        break;

      case S_ID_Final:
        id_.unPop(var_->unloadVar()); // intended followthrough
      case S_ID_Partial:
        {
          auto out=id_.popBackToken();
          if (id_.isInitial())
            mystate=S_Init;
          else
            mystate= S_ID_Partial;
          return out;
        }

      case S_Final:
        var_->unPop(x_);  // intended followthrough
      case S_Var_Partial:
        {
          auto out=var_->popBackToken();
          if (var_->isHollow())
            {
              prevTokens_=definingState(var_,mystate);
            }
          else
            mystate=S_Var_Partial;
          return out;
        }
        break;
      case S_NOT_Complex_Und:
        {
          prevTokens_.pop_back();
          mystate=S_ID_Final;
          return Token_New(Token_New::ASSIGN);
        }
        break;

      case S_SimpMult_Und:
        {
          prevTokens_.pop_back();
          mystate=S_ID_Final;
          return Token_New(Token_New::EOL);
        }
        break;
      case  S_Vec_Und:

        prevTokens_.pop_back();
        mystate=S_SimpMult_Und;
        return Token_New(Token_New::LSB);
        break;


      case  S_Set_or_Map:
        prevTokens_.pop_back();
        mystate=S_SimpMult_Und;
        return Token_New(Token_New::LCB);
        break;
      default:
        return{};
        break;
      }
  }

  bool build_ABC_Value::isFinal() const
  {
    return mystate==S_Final;

  }

  bool build_ABC_Value::isInitial() const
  {
    return mystate==S_Init;
  }

  bool build_ABC_Value::isHollow() const
  {
    switch (mystate) {
      case       S_Init:
      case     S_ID_Partial:
      case     S_ID_Final:
        return true;
      case  S_Var_Partial:
      case     S_Final:
      case     S_NOT_Complex_Und:
      case   S_SimpMult_Und:
      case  S_Vec_Und:
      case   S_Set_or_Map:
      case     S_Set_or_Map2:
      case S_Map_Und:
      default:
        return false;

      }
  }

  build_Implements_ValueId *build_ABC_Value::createBuild_Value(const ABC_Value * parent,
                                                               ABC_Value *var)
  {
    //TODO: this seems to be very uneficient.
    // I can think later of a better way..Like figuring out first all the superclasses of var and
    // then look in a table which classname it belongs to.

    if (var->complyClass(Implements_Complex_Value::ClassName()))
      {
        return new build_Implements_Complex_Value(parent);
      }
    else if (var->complyClass(Implements_Refer_Var::ClassName()))
      {
        return new build_Implements_Refer_Var(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<double>::ClassName()))
      {
        return new build_Implements_Simple_Value<double>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<int>::ClassName()))
      {
        return new build_Implements_Simple_Value<int>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<std::size_t>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::size_t>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<std::string>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::string>(parent);
      }

    // vectors
    else if (var->complyClass(Implements_Simple_Value<std::vector<double>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::vector<double>>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<std::vector<int>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::vector<int>>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<std::vector<std::size_t>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::vector<std::size_t>>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<std::vector<std::string>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::vector<std::string>>(parent);
      }
    //sets
    else if (var->complyClass(Implements_Simple_Value<std::set<double>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::set<double>>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<std::set<int>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::set<int>>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<std::set<std::size_t>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::set<std::size_t>>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<std::set<std::string>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::set<std::string>>(parent);
      }

    // matrix

    else if (var->complyClass(Implements_Simple_Value<Markov_LA::M_Matrix<double>>::ClassName()))
      {
        return new build_Implements_Simple_Value<Markov_LA::M_Matrix<double>>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<Markov_LA::M_Matrix<int>>::ClassName()))
      {
        return new build_Implements_Simple_Value<Markov_LA::M_Matrix<int>>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<Markov_LA::M_Matrix<std::size_t>>::ClassName()))
      {
        return new build_Implements_Simple_Value<Markov_LA::M_Matrix<std::size_t>>(parent);
      }

    //maps

    else if (var->complyClass(Implements_Simple_Value<std::map<double,double>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<double,double>>(parent);

      }
    else if (var->complyClass(Implements_Simple_Value<std::map<double,int>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<double,int>>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<std::map<double,std::size_t>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<double,std::size_t>>(parent);
      }
    else if (var->complyClass(Implements_Simple_Value<std::map<double,std::string>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<double,std::string>>(parent);


      }



    else if (var->complyClass(Implements_Simple_Value<std::map<int,double>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<int,double>>(parent);


      }
    else if (var->complyClass(Implements_Simple_Value<std::map<int,int>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<int,int>>(parent);


      }
    else if (var->complyClass(Implements_Simple_Value<std::map<int,std::size_t>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<int,std::size_t>>(parent);

      }
    else if (var->complyClass(Implements_Simple_Value<std::map<int,std::string>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<int,std::string>>(parent);


      }





    else if (var->complyClass(Implements_Simple_Value<std::map<std::size_t,double>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::size_t,double>>(parent);


      }
    else if (var->complyClass(Implements_Simple_Value<std::map<std::size_t,int>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::size_t,int>>(parent);


      }
    else if (var->complyClass(Implements_Simple_Value<std::map<std::size_t,std::size_t>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::size_t,std::size_t>>(parent);


      }
    else if (var->complyClass(Implements_Simple_Value<std::map<std::size_t,std::string>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::size_t,std::string>>(parent);


      }



    else if (var->complyClass(Implements_Simple_Value<std::map<std::string,double>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::string,double>>(parent);


      }
    else if (var->complyClass(Implements_Simple_Value<std::map<std::string,int>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::string,int>>(parent);


      }
    else if (var->complyClass(Implements_Simple_Value<
                              std::map<std::string,std::size_t>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::string,std::size_t>>(parent);


      }
    else if (var->complyClass(Implements_Simple_Value<
                              std::map<std::string,std::string>>::ClassName()))
      {
        return new build_Implements_Simple_Value<std::map<std::string,std::string>>(parent);


      }
    else return nullptr;
  }



  std::vector<Token_New> build_ABC_Value::definingState(build_Implements_ValueId *var, build_ABC_Value::DFA &mystate)
  {
    if (var->myClass()==build_Implements_Complex_Value::ClassName())
      {
        mystate=S_ID_Final;
        return {};
      }
    else if ((var->myClass()==build_Implements_Refer_Var::ClassName())
             ||(var->myClass()==build_Implements_Simple_Value<double>::ClassName())
             ||(var->myClass()==build_Implements_Simple_Value<int>::ClassName())
             ||(var->myClass()==build_Implements_Simple_Value<std::size_t>::ClassName())
             ||(var->myClass()==build_Implements_Simple_Value<std::string>::ClassName()))
      {
        mystate=S_NOT_Complex_Und;
        return {{Token_New::ASSIGN}};
      }
    else if  (var->myClass()==build_Implements_Simple_Value<
              Markov_LA::M_Matrix<double>>::ClassName())
      {
        mystate=S_SimpMult_Und;
        return {{Token_New::ASSIGN},{Token_New::EOL}};

      }
    else if  (var->myClass()==build_Implements_Simple_Value<
              std::vector<double>>::ClassName())
      {
        mystate=S_Vec_Und;
        return {{Token_New::ASSIGN},{Token_New::EOL},{Token_New::LSB}};

      }
    else if  ((var->myClass()==build_Implements_Simple_Value<
               std::set<double>>::ClassName())
              ||(var->myClass()==build_Implements_Simple_Value<
                 std::map<double,double>>::ClassName()))
      {
        mystate=S_Set_or_Map;
        return {{Token_New::ASSIGN},{Token_New::EOL},{Token_New::LCB}};

      }
    else
      {
        mystate=S_Final;
        return {};
      }

  }

  bool build_Command_Input::pushToken( Token_New t, std::string& errorMessage)
  {
    switch (mystate)
      {
      case S_Init:
        if (t.tok()==Token_New::IDENTIFIER)
          {

            if (cm_->has_command(t.identifier()))
              {
                cmd_=cm_->getCommand(t.identifier())->clone();
                if (hasAllInputs(cmd_))
                  mystate=S_Input_Final;
                else if (hasAllMandatoryInputs(cmd_))
                  mystate=S_Mandatory_Final;
                return true;
              }
            else
              {
                getErrorMessage("a valid command",t);
                return false;
              }
          }
        else
          {
            getErrorMessage("a valid command",t);

            return false;
          }
        break;
      case  S_Mandatory_Final:
        if (t.tok()==Token_New::EOL)
          {
            mystate=S_Final;
            return true;
          }
        else if (processVariableInput(t))
          {
            if (hasAllInputs(cmd_))
              mystate=S_Input_Final;
            else mystate=S_Mandatory_Final;
            return true;

          }
        else return false;

        break;
      case S_ID_Final:
      case S_Input_Partial:
        if (processVariableInput(t))
          {
            if (hasAllInputs(cmd_))
              mystate=S_Input_Final;
            else if (hasAllMandatoryInputs(cmd_))
              mystate=S_Mandatory_Final;
            else
              mystate=S_Input_Partial;
            return true;

          }
        else return false;
        break;

      case S_Input_Final:
        if (t.tok()==Token_New::EOL)
          {
            mystate=S_Final;
            return true;
          }
      case S_Final:
      default:
        return false;
        break;

      }

  }

  std::pair<std::string, std::set<std::string>> build_Command_Input::alternativesNext(Markov_Console::Markov_CommandManagerVar *cm) const
  {
    switch (mystate)
      {
      case S_Init:
        return {"command",parent()->getCommandList()};
        break;
      case S_ID_Final:
      case S_Input_Partial:
      case S_Mandatory_Final:
        return inputAlternativeNext();
        break;
      case S_Final:
        return {cmd_->id(),{Token_New::toString(Token_New::EOL)}};
      default:
        return {};
        break;
      }
  }




  Token_New build_Command_Input::popBackToken()
  {
    switch (mystate)
      {
      case S_Init:
        return {};
        break;
      case S_ID_Final:
        {
          mystate=S_Init;
          Token_New out(cmd_->id());
          return out;
        }
        break;
      case S_Input_Final:
      case S_Input_Partial:
      case S_Mandatory_Final:
        if (hasNoInput(cmd_))
          {
            mystate=S_Init;
            Token_New out(cmd_->id());
            return out;
          }
        else
          {
            Token_New out=popLastInput(cmd_);
            if (hasNoInput(cmd_))
              mystate=S_ID_Final;
            else if (hasAllMandatoryInputs(cmd_))
              mystate=S_Mandatory_Final;
            else
              mystate=S_Input_Partial;
            return out;
          }
        break;
      case S_Final:
        if (hasAllInputs(cmd_))
          mystate=S_Input_Final;
        else
          mystate=S_Mandatory_Final;
        return Token_New(Token_New::EOL);
        break;
      default:
        return {};
      }
  }



  build_Command_Input::build_Command_Input(Markov_Console::Markov_CommandManagerVar *cm):
    ABC_Value_ByToken(cm)
  , cm_(cm)
  , mystate(S_Init)
  , cmd_(nullptr)

  ,iInputField_(0){}
  Markov_Console::ABC_CommandVar *build_Command_Input::unloadVar()
  {
    ABClass_buildByToken::clear();
    Markov_Console::ABC_CommandVar* out=cmd_;
    mystate=S_Init;
    cmd_=nullptr;
    return out;
  }

  void build_Command_Input::clear()
  {
    ABClass_buildByToken::clear();
    delete cmd_;
    mystate=S_Init;
    cmd_=nullptr;
  }

  bool build_Command_Input::unPop(ABC_Value *var)
  {
    /// do some checking later
    ///
    ///
    Markov_Console::ABC_CommandVar* cmd=dynamic_cast<Markov_Console::ABC_CommandVar*>(var);

    if ((cmd!=nullptr)&&(hasAllInputs(cmd)))
      {
        mystate=S_Final;
        cmd_=cmd;
        return true;

      }
    else
      return false;


  }



  bool build_Command_Input::hasAllInputs(const Markov_Console::ABC_CommandVar *v)
  {
    if (v==nullptr)
      return true;
    else
      {
        for (unsigned i=0; i<v->numChilds(); ++i)
          {
            auto o=v->idToValue(v->ith_ChildName(i));
            if ((o==nullptr)||(o->empty()))
              return false;
          }
        return true;
      }
  }


  bool build_Command_Input::hasNoInput(const ABC_Value *v)
  {
    if (v==nullptr)
      return true;
    else
      {
        for (unsigned i=0; i<v->numChilds(); ++i)
          {
            auto o=v->idToValue(v->ith_ChildName(i));
            if ((o!=nullptr)&&(!o->empty()))
              return false;
          }
        return true;
      }
  }


  Token_New build_Command_Input::popLastInput(ABC_Value *v)
  {
    std::size_t i=v->numChilds();
    std::string idith=v->ith_ChildName(i);
    auto oith=v->idToValue(idith);
    while ((i>0)&&((oith==nullptr)||(oith->empty())))
      {
        --i;
        idith=v->ith_ChildName(i);
        oith=v->idToValue(idith);

      }
    if (oith->empty())
      return {};
    else
      {
        if (oith->myClass()==Implements_Refer_Var::ClassName())
          {
            Token_New o(oith->refId());
            oith->clear();
            return o;
          }
        else if (oith->myClass()==Implements_Simple_Value<std::string>::ClassName())
          {
            auto sv=dynamic_cast<Implements_Simple_Value<std::string>*> (oith);
            Token_New o(sv->value());
            oith->clear();
            return o;
          }
        else if (oith->myClass()==Implements_Simple_Value<double>::ClassName())
          {
            auto sv=dynamic_cast<Implements_Simple_Value<double>*> (oith);
            Token_New o(sv->value());
            oith->clear();
            return o;
          }
        else if (oith->myClass()==Implements_Simple_Value<std::size_t>::ClassName())
          {
            auto sv=dynamic_cast<Implements_Simple_Value<std::size_t>*> (oith);
            Token_New o(sv->value());
            oith->clear();
            return o;
          }
        else return {};

      }
  }






  ABC_Value* build_Command_Input::nextInput(Markov_Console::ABC_CommandVar *v,std::size_t& iInputField)
  {

    std::string idith=v->ith_ChildName(iInputField);
    auto oith=v->idToValue(idith);
    while ((iInputField<v->numChilds())&&((oith==nullptr)||(!oith->empty())))
      {
        ++iInputField;
        idith=v->ith_ChildName(iInputField);
        oith=v->idToValue(idith);
      }
    if (iInputField<v->numChilds())
      return oith;
    else return nullptr;


  }


  std::string build_Command_Input::ClassName()
  {
    return "build_Command_Input";
  }

  std::set<std::string> build_Command_Input::SuperClasses()
  {
    return ABC_Value_ByToken::SuperClasses()+ClassName();
  }

  std::string build_Command_Input::myClass() const
  {
    return ClassName();
  }

  std::set<std::string> build_Command_Input::mySuperClasses() const
  {
    return SuperClasses();
  }




  bool build_Command_Input::hasAllMandatoryInputs(const Markov_Console::ABC_CommandVar *cmd)
  {
    if (cmd==nullptr)
      return true;
    else
      {
        for (unsigned i=0; i<cmd->numMandatoryInputs(); ++i)
          {
            auto o=cmd->idToValue(cmd->ith_ChildName(i));
            if ((o==nullptr)||(o->refId().empty()))
              return false;
          }
        return true;
      }

  }


  bool build_Command_Input::hasNoOptionalInput(Markov_Console::ABC_CommandVar *cmd
                                               , const ABC_Value *v)
  {
    if (v==nullptr)
      return true;
    else
      {
        for (unsigned i=cmd->numMandatoryInputs();i<v->numChilds(); ++i)
          {
            auto o=v->idToValue(v->ith_ChildName(i));
            if ((o!=nullptr)&&(!o->refId().empty()))
              return false;
          }
        return true;
      }

  }



  bool build_Command_Input::processVariableInput( Token_New input)
  {

    ABC_Value* oith=nextInput(cmd_,iInputField_);

    if (oith==nullptr)
      {
        ABC_BuildByToken::getErrorMessage(cmd_,"no inputs left");
        return false;
      }
    else if (iInputField_<cmd_->numMandatoryInputs())
      {
        std::string error;
        if (oith->setThisValue(input,error))
          return true;
        else
          {
            getErrorMessage(cmd_,oith,error);
            return false;
          }
      }
    else
      {
        std::string errorF;
        bool res=oith->setThisValue(input,errorF);

        std::size_t iend=iInputField_;
        std::string errorTotal;

        while (!res)
          {
            errorTotal+=errorF;
            errorF.clear();
            ++iInputField_;
            if (iInputField_>=cmd_->numChilds())
              iInputField_=cmd_->numMandatoryInputs();
            if (iInputField_==iend)
              break;
            oith=nextInput(cmd_,iInputField_);
            res=oith->setThisValue(input,errorF);
          }
        if (res)
          return true;
        else
          {
            getErrorMessage(cmd_,errorTotal);
            return false;
          }

      }
  }

  std::pair<std::string, std::set<std::string>> build_Command_Input::inputAlternativeNext() const
  {
    ABC_Value* oith=nextInput(cmd_,iInputField_);

    if (oith==nullptr)
      {
        return {"full",{}};
      }
    else
      {
        return {oith->id(),oith->alternativeValues()};
      }


  }

  build_Statement::build_Statement(Markov_Console::Markov_CommandManagerVar *p):
    ABC_Value_ByToken(p),
    mystate{S_Init}
  ,x_(nullptr)
  ,cmv_(nullptr)
  ,v_(p)
  ,c_(p){}

  bool build_Statement::pushToken( Token_New t, std::string& errorMessage)
  {
    switch (mystate)
      {
      case S_Init:
        if (c_.pushToken(t, errorMessage))
          {
            if (c_.isFinal())
              {
                cmv_=c_.unloadVar();
                x_=cmv_;
                mystate=S_Command_Final;
                return true;
              }
            else
              {
                mystate=S_Command_Partial;
                return true;
              }
          }
        else if (v_.pushToken(t, errorMessage))
          {
            mystate=S_Expression_Partial;
            return true;
          }
        else
          {
            if (t.tok()==Token_New::EOL)
              return true;
            else
              errorMessage=getErrorMessage(t.str()+": unknown command or variable");

            return false;
          }
        break;
      case S_Command_Partial:
        if (!c_.pushToken(t, errorMessage))
          {
            errorMessage=ABClass_buildByToken::getErrorMessage(errorMessage);
            return false;
          }
        else
          {
            if (c_.isFinal())
              {
                cmv_=c_.unloadVar();
                x_=cmv_;
                mystate=S_Command_Final;
              }
            else
              mystate=S_Command_Partial;
            return true;
          }
        break;
      case S_Expression_Partial:
        if (!v_.pushToken(t, errorMessage))
          {
            errorMessage=ABC_BuildByToken::getErrorMessage(errorMessage);
            return false;
          }
        else
          {
            if (v_.isFinal())
              {
                mystate=S_Expression_Final;
                x_=v_.unloadVar();

              }
            else
              mystate=S_Expression_Partial;
            return true;
          }
        break;
      case S_Command_Final:
      case S_Expression_Final:
      default:
        return false;
        break;
      }

  }

  std::pair<std::string, std::set<std::string>> build_Statement::alternativesNext(Markov_Console::Markov_CommandManagerVar *cm) const
  {
    switch (mystate)
      {
      case S_Init:
        return  {"comands or variables",c_.alternativesNext(cm).second+v_.alternativesNext(cm).second};
        break;
      case S_Command_Partial:
        return c_.alternativesNext(cm);
        break;
      case S_Expression_Partial:
        return c_.alternativesNext(cm);
        break;
      case S_Command_Final:
      case S_Expression_Final:
      default:
        return {};
        break;
      }

  }

  Token_New build_Statement::popBackToken()
  {
    switch (mystate)
      {

      case S_Command_Final:
        c_.unPop(cmv_);  // intended followthrough

      case S_Command_Partial:
        {
          auto out=c_.popBackToken();
          if (c_.isInitial())
            mystate=S_Init;
          else
            mystate=S_Command_Partial;
          return out;
        }
        break;

      case S_Expression_Final:
        v_.unPop(x_);  // intended followthrough

      case S_Expression_Partial:
        {
          auto out=v_.popBackToken();
          if (v_.isInitial())
            mystate=S_Init;
          else
            mystate=S_Expression_Partial;
          return out;
        }
        break;
      case S_Init:
      default:
        return {};
        break;

      }

  }

  std::string build_Implements_ValueId::ClassName()
  {
    return "build_Implements_ValueId";
  }

  std::set<std::string> build_Implements_ValueId::SuperClasses()
  {
    return ABC_Value_ByToken::SuperClasses()+ClassName();
  }

  std::string build_Implements_ValueId::myClass() const
  {
    return ClassName();

  }

  std::set<std::string> build_Implements_ValueId::mySuperClasses() const
  {
    return SuperClasses();
  }

  build_Implements_ValueId::build_Implements_ValueId(const ABC_Value *p):
    ABC_Value_ByToken(p),
    id_(nullptr),
    idstate(S_Init){}

  void build_Implements_ValueId::setId(Implements_ValueId *id)
  {
    delete id_;
    id_=id;
  }

  Implements_ValueId *build_Implements_ValueId::unloadVar()
  {
    if (isFinal())
      {
        auto out=id_;
        idstate=S_Init;
        id_=new Implements_ValueId;
        return out;
      }
    else return nullptr;
  }

  void build_Implements_ValueId::clear()
  {
    ABClass_buildByToken::clear();
    delete id_;
    idstate=S_Init;
    id_=new Implements_ValueId;
  }

  bool build_Implements_ValueId::pushToken(Token_New t, std::string &errorMessage)
  {
    switch (idstate)
      {
      case S_Init:
        if (t.tok()==Token_New::HASH)
          {
            idstate=TIP1;
            return true;
          }
        else if (t.tok()==Token_New::IDENTIFIER)
          {
            if (pushToken_Id(t,errorMessage))
              {
                idstate =ID1;
                return true;
              }
          }
        else
          {
            ABC_BuildByToken::setErrorsMessage({Token_New::HASH,Token_New::IDENTIFIER},t);
            return false;
          }
        break;
      case TIP1:
        if (t.tok()==Token_New::STRING)
          {
            idstate =TIP2;
            if (id_==nullptr)
              id_=new Implements_ValueId;
            id_->setTip(t.str());
            return true;
          }
        else
          {
            std::string e= "wrong Tip. Expected a string. Received: ";
            errorMessage= ABC_BuildByToken::getErrorMessage   (e,t);
            return false;
          }
        break;
      case TIP2:
        if (t.tok()==Token_New::EOL)
          {
            idstate =WT0_ID0;
            return true;
          }
        else
          {
            std::string e= "Error in Tip. Expected a return. Received: ";
            errorMessage= ABC_BuildByToken::getErrorMessage   (e,t);
            return false;
          }
        break;
      case WT0_ID0:
        if (t.tok()==Token_New::HASH)
          {
            idstate =WT1;
            return true;
          }
        else if (t.tok()==Token_New::IDENTIFIER)
          {
            if (pushToken_Id(t,errorMessage))
              {
                idstate =ID1;
                return true;
              }
            else
              return false;
          }
        else  {
            ABC_BuildByToken::setErrorsMessage({Token_New::HASH,Token_New::IDENTIFIER},t);
            return false;
          }
        break;
      case WT1:
        if (t.tok()==Token_New::HASH)
          {
            idstate =WT2;
            return true;
          }
        else  {
            errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::HASH,t);
            return false;
          }
        break;
      case WT2:
        if(t.tok()==Token_New::STRING)
          {
            idstate =WT3;
            if (id_==nullptr)
              id_=new Implements_ValueId;
            id_->setWhatThis(t.str());
            return true;
          }
        else
          {
            errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::STRING,t);
            return false;
          }       break;
      case WT3:
        if (t.tok()==Token_New::EOL)
          {
            idstate =ID0;
            return true;
          }
        else
          {
            errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::EOL,t);
            return false;
          }   break;

      case ID0:
        if (t.tok()==Token_New::IDENTIFIER)
          {
            if (pushToken_Id(t,errorMessage))
              {
                idstate =ID1;
                return true;
              }
            else return false;
          }
        else
          {
            errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::IDENTIFIER,t);
            return false;
          }        break;
      case ID1:
        if (t.tok()==Token_New::COLON)
          {
            idstate =ID2;
            return true;
          }
        else
          {
            errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::COLON,t);
            return false;
          }
        break;
      case ID2:
        if (t.tok()==Token_New::IDENTIFIER)
          {
            if (pushToken_var(t,errorMessage))
              {
                idstate =S_Final;
                return true;
              }
            else
              return false;
          }
        else
          {
            errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::IDENTIFIER,t);
            return false;
          }
        break;
      case S_Final:
      default:
        return false;
        break;
      }
  }

  bool build_Implements_ValueId::unPop(ABC_Value *var)
  {
    if (var->complyClass(Implements_ValueId::ClassName()))
      {
        idstate =S_Final;
        if (id_!=var)
          delete id_;
        id_=dynamic_cast<Implements_ValueId*>(var);
        return true;
      }
    else
      return false;
  }

  std::pair<std::string, std::set<std::string> > build_Implements_ValueId::alternativesNext(Markov_Console::Markov_CommandManagerVar *cm) const
  {
    switch (idstate ) {
      case S_Init:
        return {myClass(),{Token_New::toString(Token_New::HASH)
                  ,"["+Implements_New_Identifier_Class::ClassName()+"]"}};
        break;

        break;
      case TIP1:
        return {myClass(),{"tip_string"}};
        break;
      case TIP2:
        return {myClass(),{Token_New::toString(Token_New::EOL)}};
        break;
      case WT0_ID0:
        if (parent()!=nullptr)
          {

            return {myClass(),{Token_New::toString(Token_New::HASH)
                      ,"variable_identifier"}};
          }
        break;
      case WT1:
        return {myClass(),{Token_New::toString(Token_New::HASH)}};
        break;
      case WT2:
        return {myClass(),{"what_this"}};
        break;
      case WT3:
        return {myClass(),{Token_New::toString(Token_New::EOL)}};
        break;
      case ID0:
        return {myClass(),{"variable_identifier"}};
        break;
      case ID1:
        return {myClass(),{Token_New::toString(Token_New::COLON)}};
        break;
      case ID2:
        return {myClass(),{"variable_type"}};
        break;
      case S_Final:
      default:
        return {};
        break;
      }
  }

  Token_New build_Implements_ValueId::popBackToken()
  {
    switch (idstate ) {
      case S_Final:
        idstate =ID2;
        return Token_New(id_->myVar());
        break;
      case ID2:
        idstate =ID1;
        return Token_New(Token_New::COLON);
        break;
      case ID1:
        if (!id_->Tip().empty()&&!id_->WhatThis().empty())
          idstate =ID0;
        else if (!id_->Tip().empty())
          idstate =WT0_ID0;
        else
          idstate =S_Init;
        return Token_New(id_->id());
        break;
      case ID0:
        idstate =WT3;
        return Token_New(Token_New::EOL);
        break;
      case WT3:
        idstate =WT2;
        return Token_New(id_->WhatThis());
        break;
      case WT2:
        idstate =WT1;
        return Token_New(Token_New::HASH);
        break;
      case WT1:
        idstate =WT0_ID0;
        return Token_New(Token_New::HASH);
        break;
      case WT0_ID0:
        idstate =TIP2;
        return Token_New(Token_New::EOL);
        break;
      case TIP2:
        idstate =TIP1;
        return Token_New(id_->Tip());
        break;
      case TIP1:
        idstate =S_Init;
        return Token_New(Token_New::HASH);
        break;
      case S_Init:
      default:
        return {};
        break;


      }
  }

  bool build_Implements_ValueId::isFinal() const
  {
    return idstate==S_Final;
  }

  bool build_Implements_ValueId::isInitial() const
  {
    return idstate==S_Init;
  }

  bool build_Implements_ValueId::isHollow() const
  {
    return isInitial();
  }

  build_Implements_ValueId::~build_Implements_ValueId(){}

  bool build_Implements_ValueId::pushToken_Id(Token_New t, std::string &errorMessage)
  {
    if (parent()->idToValue(t.identifier())!=nullptr)
      {
        errorMessage="occupied identifier";
        return false;
      }
    else
      {
        if (id_==nullptr)
          id_=new Implements_ValueId;
        id_->setId(t.identifier());
        return true;
      }
  }

  bool build_Implements_ValueId::pushToken_var(Token_New t, std::string &errorMessage)
  {
    if (parent()!=nullptr)
      {
        auto v=parent()->idToValue(t.identifier());
        if (v!=nullptr)
          {
            if (v->complyVar(varType_,&errorMessage))
              {
                if (id_==nullptr)
                  id_=new Implements_ValueId;
                id_->setVar(t.str());
                return true;
              }
            else
              {
                return false;
              }
          }
        else return false;
      }

    else return false;
  }

  std::pair<std::string, std::set<std::string> > build_Implements_ValueId::alternativesNext_var() const
  {
    if (varType_.empty())
      {
        auto s= parent()->getVarList();
        return {"select a variable type",s};
      }
    else
      {
        auto s=parent()->getListComplying(varType_);
        return {"select a"+varType_,s};
      }

  }


}


