#ifndef BUILDCLOSUREBYTOKEN_H
#define BUILDCLOSUREBYTOKEN_H



#include "Markov_IO/buildByToken.h"
#include "Markov_IO/Cls.h"
#include "Markov_IO/Closure.h"

#include "Markov_IO/Token_New.h"
#include "Markov_LA/Matrix.h"
#include "Markov_IO/Var.h"
#include "Markov_IO/Implements_function.h"

#include <string>
#include <set>
#include <map>
#include <vector>
#include <memory>
#include <utility>

namespace Markov_IO_New {




  class ABC_Type_of_Function;





  class ABC_BuildClosure : public ABC_BuildByToken_
  {
  public:


    virtual ABC_Closure* unloadClosure()=0;
    virtual bool hasMandatory()const=0;
    virtual bool hasNoArguments()const =0;

    virtual ~ABC_BuildClosure(){}

  protected:
    ABC_BuildClosure(const StructureEnv_New* p):ABC_BuildByToken_(p){}
  };




  template <class...C>
  class buildClosureByToken
  {
  };


  template<typename... Args>
  class buildClosureByToken<std::tuple<Args...>>
      :public ABC_BuildClosure

  {
  public:
    typedef Implements_Closure_Value<std::tuple<Args...>> myC;
    typedef std::tuple<Implements_Fn_Argument<Args>...> dataArgumentsTuple;
    typedef Implements_Closure_Type<std::tuple<Args...>>  vType;
    typedef std::tuple<std::unique_ptr<buildClosureByToken<Args>>...> buildTuple;
    typedef std::tuple<Args...> argTuple;


    enum DFA {
      S_Init, S_Element_Partial, S_Element_Final,S_Mandatory,S_Final};

    buildClosureByToken(const StructureEnv_New* paren,
                        const Implements_Closure_Type<std::tuple<Args...>>* typeVar):
      ABC_BuildClosure(paren),
      mystate(S_Init),
      varType_(typeVar)
    ,buildTupl_(getBuildTuple(paren,typeVar->getFnArguments(paren)
                              ,std::index_sequence_for<Args...>()))
    ,xTupl_()
    ,iArg_(0)
    {
      if (isMandatory_imp(parent(),std::index_sequence_for<Args...>(),iArg_,varType_->getFnArguments(parent())))
        mystate=S_Init;
      else
        mystate=S_Mandatory;

    }

    bool hasMandatory()const
    {
      return (mystate==S_Mandatory)
          &&(mystate==S_Final);

    }


    virtual bool UnPopClosure(ABC_Closure* cl)
    {
      return false;
    }


    virtual bool hasNoArguments()const
    {

    }




    myC* unloadClosure() override
    {
      if ((iArg_ )< (std::tuple_size<std::tuple<Args...>>::value))
        varType_->fill_imp(xTupl_.get(),iArg_,varType_->getFnArguments(parent()),
                           std::index_sequence_for<Args...>());
      auto out=xTupl_.release();
      xTupl_= {};
      mystate=S_Init;
      iArg_=0;
      return out;
    }





    bool pushToken(Token_New t, std::string* whyNot, const std::string& masterObjective)override
    {
      const std::string objective=masterObjective+": "+"Token "+t.str()+" was not accepted by ";
      switch (mystate)
        {
        case S_Init:
        case S_Element_Partial:
        case S_Element_Final:
        case S_Mandatory:
          return pushToken_imp(parent()
                               ,std::index_sequence_for<Args...>()
                               ,mystate
                               ,iArg_
                               ,buildTupl_
                               ,varType_->getFnArguments(parent())
                               ,xTupl_
                               ,t
                               ,whyNot
                               ,objective);
        case    S_Final:
          return false;

        }
    }



    std::pair<std::string,std::set<std::string>> alternativesNext()const override
    {
      return alternativesNext_imp<0>
          (parent(),std::index_sequence_for<Args...>(),mystate,iArg_
           ,buildTupl_,
           varType_->getFnArguments(parent()));
    }


    void clear()override
    {
      xTupl_={};
      mystate=S_Init;
      iArg_=0;
    }

//    virtual void reset_Type(const Implements_Data_Type_New<myC>* var)
//    {
//      clear();
//      varType_=var;
//      buildTupl_=getBuildTuple(parent(),varType_->getArgumentTypes()
//                               ,std::index_sequence_for<Args...>());

//    }

    bool unPop(myC var)
    {
      xTupl_=std::move(var);
      mystate=S_Final;
      iArg_=std::tuple_size<myC>::value;
      return true;
    }

    Token_New popBackToken() override
    {
      switch (mystate)
        {
        case S_Init: return {};
        case S_Element_Final:
        case S_Final:
          --iArg_;
        case S_Element_Partial:
          return popBackToken_imps(parent()
                                   ,std::index_sequence_for<Args...>()
                                   ,mystate
                                   ,iArg_
                                   ,buildTupl_
                                   ,varType_->getFnArguments(parent())
                                   ,xTupl_);
        }
    }

    bool isFinal()const override
    {
      return mystate==S_Final;
    }

    bool isInitial()const override
    {
      return mystate==S_Init;
    }




    virtual ~buildClosureByToken(){}

    std::size_t iArg()const {return iArg_;}


  protected:
    template<std::size_t ...Is>
    static buildTuple getBuildTuple
    (const StructureEnv_New* parent,
     const dataArgumentsTuple& types
     , const std::index_sequence<Is...> )
    {
      return std::tuple<std::unique_ptr<buildClosureByToken<Args>>...> (
            std::get<Is>(types).closureType(parent)->getBuildClosureByToken(parent)...
            );
    }

    template<std::size_t D>
    static bool pushToken_imp(const StructureEnv_New* cm,
                              DFA &state,std::size_t &i
                              ,buildTuple& b
                              ,const dataArgumentsTuple& a
                              ,std::unique_ptr<myC>& x
                              ,Token_New t, std::string* whyNot
                              , const std::string& masterObjective)
    {
      return t.tok()==Token_New::EOL;
    }



    template<std::size_t D,std::size_t I, std::size_t...Is>
    static bool pushToken_imp(const StructureEnv_New* cm,
                              DFA &state,std::size_t &i
                              ,buildTuple& b
                              ,const dataArgumentsTuple& a
                              ,std::unique_ptr<myC>& x
                              ,Token_New t, std::string* whyNot
                              , const std::string& masterObjective)
    {
      if (I<i)
        return pushToken_imp<D,Is...>(cm,state,i,b,a,x,t,whyNot,masterObjective);
      else
        {
          typedef typename std::tuple_element<I,argTuple>::type eType;
          buildClosureByToken<eType>* eB=std::get<I>(b).get();
          Implements_Fn_Argument<eType> aT=std::get<I>(a);
          if ((t.tok()==Token_New::EOL)||(aT.isDefaulted()))
            {
              std::get<I>(x->getTuple()).reset(aT.defaultValue());
              ++i;
              if (i==std::tuple_size<std::tuple<Args...>>::value)
                {
                  state=S_Final;
                  return true;
                }
              else if (isMandatory_imp(cm,std::index_sequence_for<Args...>(),i,a))
                state=S_Element_Final;
              else
                state=S_Mandatory;
              return pushToken_imp<D,Is...>(cm,state,i,b,a,x,t,whyNot,masterObjective);

            }
          else if (!eB->pushToken(t,whyNot,masterObjective))
            {
              return false;
            }
          else if (eB->isFinal())
            {
              std::get<I>(x->getTuple()).reset(eB->unloadClosure());
              ++i;
              if (i==std::tuple_size<std::tuple<Args...>>::value)
                state=S_Final;
              else if (isMandatory_imp(cm,std::index_sequence_for<Args...>(),i,a))
                state=S_Element_Final;
              else
                state=S_Mandatory;
              return true;
            }
          else
            {
              state=S_Element_Partial;
              return true;
            }

        }
    }



    template<std::size_t...Is>
    static bool pushToken_imp(const StructureEnv_New* cm,
                              std::index_sequence<Is...>
                              ,DFA &state
                              ,std::size_t &i
                              ,std::tuple<std::unique_ptr<buildClosureByToken<Args>>...>& b
                              ,const dataArgumentsTuple& a
                              ,std::unique_ptr<myC>& x
                              ,Token_New t,
                              std::string* whyNot
                              , const std::string& masterObjective)
    {

      return pushToken_imp<0,Is...>(cm,state,i,b,a,x,t,whyNot,masterObjective);
    }





    template<std::size_t D>
    static bool isMandatory_imp(const StructureEnv_New* cm,
                                std::size_t i
                                ,const dataArgumentsTuple& arg
                                )
    {
      return false;
    }





    template<std::size_t D,std::size_t I, std::size_t ... Is>
    static bool isMandatory_imp(const StructureEnv_New* cm,std::size_t i
                                ,const dataArgumentsTuple& arg
                                )
    {
      if (I<i)
        return isMandatory_imp<D,Is...>(cm,i,arg);
      else
        {
          typedef typename std::tuple_element<I,std::tuple<Args...>>::type eType;
          const Implements_Fn_Argument<eType>& a=std::get<I>(arg);
          if (a.isDefaulted())
            return isMandatory_imp<D,Is...>(cm,++i,arg);
          else
            return a.isMandatory();

        }
    }



    template<std::size_t ... Is>
    static bool isMandatory_imp(const StructureEnv_New* cm,std::index_sequence<Is...>,std::size_t i
                                ,const dataArgumentsTuple& arg
                                )
    {
      return isMandatory_imp<0,Is...>(cm,i,arg);
    }


    template<std::size_t D>
    static std::pair<std::string,std::set<std::string>> alternativesNext_imp
    (const StructureEnv_New* cm,
     DFA state,std::size_t i
     ,const buildTuple& b
     ,const dataArgumentsTuple& arg)
    {
      return {};
    }



    template<std::size_t D,std::size_t I, std::size_t... Is>
    static std::pair<std::string,std::set<std::string>> alternativesNext_imp
    (const StructureEnv_New* cm,
     DFA state
     ,std::size_t i
     ,const buildTuple& b
     ,const dataArgumentsTuple& arg)
    {
      if (state==S_Final)
        return {};
      if (I<i)
        return alternativesNext_imp<D,Is...>(cm,state,i,b,arg);
      else
        {
          typedef typename std::tuple_element<I,std::tuple<Args...>>::type eType;
          const Implements_Fn_Argument<eType>& aT=std::get<I>(arg);
          if (aT.isDefaulted())
            {
              ++i;
              return alternativesNext_imp<D,Is...>(cm,state,i,b,arg);
            }
          else
            {
              buildClosureByToken<eType>* eB=std::get<I>(b).get();
              auto out=eB->alternativesNext();
              std::string id=aT.id();
              return {id,out.second};
            }
        }
    }

    template<std::size_t... Is>
    static std::pair<std::string,std::set<std::string>> alternativesNext_imp
    (const StructureEnv_New* cm,
     std::index_sequence<Is...>
     ,DFA state
     ,std::size_t i
     ,const buildTuple& b
     ,const dataArgumentsTuple& arg)
    {
      return alternativesNext_imp<0,Is...>(cm,state,i,b,arg);

    }




    template<std::size_t D>
    static Token_New popBackToken_imp
    (const StructureEnv_New* cm,
     DFA &state,std::size_t &i
     , buildTuple& b
     ,const dataArgumentsTuple& a,
     std::unique_ptr<myC>&  x)
    {

      return {};

    }



    template<std::size_t D,std::size_t I,std::size_t... Is>
    static Token_New popBackToken_imp(const StructureEnv_New* cm,
                                      DFA &state
                                      ,std::size_t &i
                                      ,buildTuple& b
                                      ,const dataArgumentsTuple& a
                                      ,std::unique_ptr<myC>&  x)
    {
      if (I<i)
        return popBackToken_imp<D,Is...>(cm,state,i,b,a,x);
      else {
          typedef typename std::tuple_element<I,std::tuple<Args...>>::type eType;
          auto aT=std::get<I>(a);
          if (aT.isDefaulted())
            {
              --i;
              return popBackToken_imp<D,Is...>(cm,state,i,b,a,x);


            }
          else
            {
              buildClosureByToken<eType>* eB=std::get<I>(b).get();
              Token_New out;
              if (eB->isInitial())
                {
                  eB->unPop(std::get<I>(x->getTuple()).get());
                }
              out=eB->popBackToken();
              if (eB->isInitial())
                {
                  if (i==0)
                    state=S_Init;
                  else
                    {
                      state=S_Element_Final;
                    }
                }
              else
                state=S_Element_Partial;
              return out;
            }
        }
    }


    template<std::size_t... Is>
    static Token_New popBackToken_imps
    (const StructureEnv_New* cm,
     std::index_sequence<Is...>
     ,DFA &state
     ,std::size_t &i
     ,buildTuple& b
     ,const dataArgumentsTuple& a
     ,std::unique_ptr<myC>& x)
    {
      return popBackToken_imp<0,Is...>(cm,state,i,b,a,x);

    }










  protected:
    DFA mystate;
    std::size_t iArg_;
    const Implements_Closure_Type<std::tuple<Args...>>* varType_;
    buildTuple    buildTupl_;
    std::unique_ptr<Implements_Closure_Value<std::tuple<Args...>>> xTupl_;
  };






  template<>
  class buildClosureByToken<void*>
      :public ABC_BuildClosure
  {
  public:

    enum DFA {
      S_Init=0, S_Closure_PARTIAL, S_Closure_Mandatory,S_Closure_Final,S_Final
    } ;

    bool pushToken(Token_New tok, std::string* whyNot,const std::string& masterObjective)override;

    bool isFinal()const override
    {
      return mystate==S_Final;

    }
    bool isInitial()const override
    {
      return mystate==S_Init;

    }

    virtual bool hasMandatory()const override
    {
      return (mystate==S_Closure_Mandatory)
          && (mystate==S_Closure_Final)
          && (mystate==S_Final);
    }


    ~buildClosureByToken(){}


    virtual bool hasNoArguments()const override
    {
      return hasNoArguments(vecValueB_,nPushedTokens_,nPushedTokensIn_);
    }


    buildClosureByToken(const StructureEnv_New* parent,
                        const Implements_Closure_Type<void*> *varType);


    void clear()override
    {}



    virtual std::pair<std::string, std::set<std::string> > alternativesNext() const override;

    virtual Token_New popBackToken() override;

    virtual void reset_Type(Implements_Closure_Type<void*> *dataTy);






    virtual ABC_Closure* unloadClosure() override
    {
      if (isFinal())
        {
          ABC_Closure* out=data_.release();
          mystate=S_Init;
          nPushedTokens_=0;
          return out;
        }
      else return nullptr;


    }



  protected:
    DFA mystate;
    const Implements_Closure_Type<void*> * fnType_;
    const Implements_Identifier* idtype_;
    std::string idString_;
    std::unique_ptr<buildByToken<std::string>> idObjB_;
    std::vector<std::unique_ptr<ABC_BuildClosure>> vecValueB_;
    std::vector<size_t> nPushedTokensIn_;
    std::size_t nPushedTokens_;
    std::unique_ptr<ABC_BuildClosure> valueB_;
    std::unique_ptr<ABC_Closure> data_;


    static bool isFinal(const std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t nPushedTokens,const std::vector<std::size_t> & nPushedTokensIn)
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

    static std::pair<std::string, std::set<std::string> > alternativesNext(const std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t nPushedTokens,const std::vector<std::size_t> & nPushedTokensIn)
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


    static bool hasNoArguments(const std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t nPushedTokens,const std::vector<std::size_t> & nPushedTokensIn)
    {
      for (std::size_t i=0; i<vecValue.size(); ++i)
        {
          if (nPushedTokensIn[i]==nPushedTokens)
            {
              return vecValue[i]->hasNoArguments();
            }
        }
      return false;
    }


    static bool hasMandatory
    (const std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue
     , std::size_t nPushedTokens,const std::vector<std::size_t> & nPushedTokensIn)
    {
      for (std::size_t i=0; i<vecValue.size(); ++i)
        {
          if (nPushedTokensIn[i]==nPushedTokens)
            {
              if (vecValue[i]->hasMandatory())
                return true;
            }
        }
      return false;
    }


    static bool pushToken(std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t &nPushedTokens, std::vector<std::size_t> & nPushedTokensIn,Token_New tok, std::string* whyNot,const std::string& masterObjective)
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
      if (out) ++nPushedTokens;
      return out;

    }

    static Token_New popBackToken(std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t &nPushedTokens, std::vector<std::size_t> & nPushedTokensIn)
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


    static ABC_Closure* unloadClosure(std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t &nPushedTokens, std::vector<std::size_t> & nPushedTokensIn)
    {
      for (std::size_t i=0; i<vecValue.size(); ++i)
        {
          if ((nPushedTokensIn[i]==nPushedTokens)&& vecValue[i]->hasMandatory())
            {
              return vecValue[i]->unloadClosure();
            }
        }
      return nullptr;
    }




    static bool isInitial(const std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t nPushedTokens, const std::vector<std::size_t> & nPushedTokensIn)
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

  };


  template<class C>
  class buildClosureByToken<void*,C>
      :public ABC_BuildClosure
  {
  public:

    enum DFA {
      S_Init=0, S_Obj_Final,S_Obj_Separator_Final,
      S_Closure_PARTIAL, S_Closure_Mandatory,S_Closure_Final,S_Final
    } ;

    bool pushToken(Token_New tok, std::string* whyNot,const std::string& masterObjective)override

    {
      const std::string objective=masterObjective+":  rejected token "+tok.str();
      switch (mystate)
        {
        case S_Init:
          if (idObjB_->pushToken(tok,whyNot,objective))
            {
              idObj_=idObjB_->unloadVar();
              objData_=parent()->template idToValued<C>(idObj_,whyNot,objective);
              if (objData_==nullptr)
                return false;
              else
                {
                  objType_=objData_->myTypeD(parent());
                  idMethodB_=objType_->getMethodIdentifier()->getBuildByToken(parent());
                  mystate=S_Obj_Final;
                  return true;
                }
            }
          else { return false;}
        case S_Obj_Final:
          if (tok.tok()!=Token_New::DOT)
            return false;
          else
            {
              mystate=S_Obj_Separator_Final;
              return true;
            }
        case S_Obj_Separator_Final:
          if (!idMethodB_->pushToken(tok,whyNot,objective))
            {
              return false;
            }
          else
            {
              idMethod_=idMethodB_->unloadVar();
              methodType_=objType_->idToMethod(idMethod_,whyNot,objective);
              if (methodType_==nullptr)
                return false;
              else
                {
                  vecValueB_=getOverloadBuild(methodType_,parent());
                  nPushedTokensIn_=std::vector<std::size_t>(vecValueB_.size(),0);
                  nPushedTokens_=0;
                  if (isFinal(vecValueB_,nPushedTokens_,nPushedTokensIn_))
                    {
                      mystate =S_Closure_Final;
                      return true;
                    }
                  else if (hasMandatory(vecValueB_,nPushedTokens_,nPushedTokensIn_))
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
            }

        case S_Closure_PARTIAL:
        case S_Closure_Mandatory:
          if (pushToken(vecValueB_,nPushedTokens_,nPushedTokensIn_
                        ,tok, whyNot,objective))
            {
              if (isFinal(vecValueB_,nPushedTokens_,nPushedTokensIn_))
                {
                  if (tok.tok()!=Token_New::EOL)
                    {
                      mystate =S_Closure_Final;
                      return true;
                    }
                  else
                    {
                      data_.reset(unloadClosure(vecValueB_,nPushedTokens_,nPushedTokensIn_));
                      mystate=S_Final;
                      return true;
                    }
                }
              else  if (hasMandatory(vecValueB_,nPushedTokens_,nPushedTokensIn_))
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
              data_.reset(unloadClosure(vecValueB_,nPushedTokens_,nPushedTokensIn_));
              mystate=S_Final;
              return true;
            }

        case S_Final:
          return false;
        }
    }

    bool isFinal()const override
    {
      return mystate==S_Final;

    }
    bool isInitial()const override
    {
      return mystate==S_Init;

    }

    virtual bool hasMandatory()const override
    {
      return (mystate==S_Closure_Mandatory)
          && (mystate==S_Closure_Final)
          && (mystate==S_Final);
    }


    ~buildClosureByToken(){}


    virtual bool hasNoArguments()const override
    {
      return hasNoArguments(vecValueB_,nPushedTokens_,nPushedTokensIn_);
    }


    buildClosureByToken(const StructureEnv_New* parent,
                        const Implements_Closure_Type<void*> *varType);

    void clear()override
    {}


    virtual bool UnPopClosure(ABC_Closure* cl)override
    {
      return false;
    }

    virtual std::pair<std::string, std::set<std::string> > alternativesNext() const override;

    virtual Token_New popBackToken() override;

    virtual void reset_Type(Implements_Closure_Type<void*> *dataTy);






    virtual ABC_Closure* unloadClosure() override
    {
      if (isFinal())
        {
          ABC_Closure* out=data_.release();
          mystate=S_Init;
          nPushedTokens_=0;
          return out;
        }
      else return nullptr;


    }



  protected:
    DFA mystate;
    const Implements_Closure_Type<void*,C> * fnType_;
    std::unique_ptr<buildByToken<std::string>> idObjB_;
    std::string idObj_;
    Implements_Value_New<C>* objData_;
    const Implements_Data_Type_New<C>* objType_;
    std::unique_ptr<buildByToken<std::string>> idMethodB_;
    std::string idMethod_;
    const Implements_Closure_Type<void*,C> * methodType_;

    std::vector<std::unique_ptr<ABC_BuildClosure>> vecValueB_;
    std::vector<size_t> nPushedTokensIn_;
    std::size_t nPushedTokens_;
    std::unique_ptr<ABC_BuildClosure> valueB_;
    std::unique_ptr<ABC_Closure> data_;


    static bool isFinal(const std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t nPushedTokens,const std::vector<std::size_t> & nPushedTokensIn)
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

    static std::pair<std::string, std::set<std::string> > alternativesNext(const std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t nPushedTokens,const std::vector<std::size_t> & nPushedTokensIn)
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


    static bool hasNoArguments(const std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t nPushedTokens,const std::vector<std::size_t> & nPushedTokensIn)
    {
      for (std::size_t i=0; i<vecValue.size(); ++i)
        {
          if (nPushedTokensIn[i]==nPushedTokens)
            {
              return vecValue[i]->hasNoArguments();
            }
        }
      return false;
    }


    static bool hasMandatory(const std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t nPushedTokens,const std::vector<std::size_t> & nPushedTokensIn)
    {
      for (std::size_t i=0; i<vecValue.size(); ++i)
        {
          if (nPushedTokensIn[i]==nPushedTokens)
            {
              if (vecValue[i]->hasMandatory())
                return true;
            }
        }
      return false;
    }


    static bool pushToken(std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t &nPushedTokens, std::vector<std::size_t> & nPushedTokensIn,Token_New tok, std::string* whyNot,const std::string& masterObjective)
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
      if (out) ++nPushedTokens;
      return out;

    }

    static Token_New popBackToken(std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t &nPushedTokens, std::vector<std::size_t> & nPushedTokensIn)
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


    static ABC_Closure* unloadClosure(std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t &nPushedTokens, std::vector<std::size_t> & nPushedTokensIn)
    {
      for (std::size_t i=0; i<vecValue.size(); ++i)
        {
          if ((nPushedTokensIn[i]==nPushedTokens)&& vecValue[i]->hasMandatory())
            {
              return vecValue[i]->unloadClosure();
            }
        }
      return nullptr;
    }




    static bool isInitial(const std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t nPushedTokens, const std::vector<std::size_t> & nPushedTokensIn)
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

  };



  template<typename R>
  class buildClosureByToken<R>
      :public ABC_BuildClosure
  {
  public:

    enum DFA {
      S_Init=0,
      S_Data_Partial, S_Data_Final,
      S_Id_Partial, S_Id_Final,
      S_Fn_Partial, S_Fn_Final
    } ;

    bool pushToken(Token_New tok, std::string* whyNot,const std::string& masterObjective)override
    {
      switch (mystate)

        {
        case S_Init:

          {
            if (xB_->pushToken(tok,whyNot,masterObjective))
              {
                if (xB_->isFinal())
                  {
                    mystate=S_Id_Final;
                    data_.reset(xB_->unloadClosure());
                  }
                else
                  mystate=S_Id_Partial;
                return true;
              }
            else if (fnB_->pushToken(tok,whyNot,masterObjective))
              {
                if (fnB_->isFinal())
                  {
                    mystate=S_Fn_Final;
                    data_.reset(fnB_->unloadClosure());
                  }
                else
                  mystate=S_Fn_Partial;
                return true;
              }
            else if (dataB_->pushToken(tok,whyNot,masterObjective))
              {
                if (dataB_->isFinal())
                  {

                    data_.reset(dataB_->unloadClosure());

                    mystate=S_Data_Final;
                  }
                else
                  mystate=S_Data_Partial;
                return true;
              }
            else return false;
          }
        case S_Id_Partial:
          {
            if (xB_->pushToken(tok,whyNot,masterObjective))
              {
                if (xB_->isFinal())
                  {
                    mystate=S_Id_Final;
                    data_.reset(xB_->unloadClosure());
                  }
                else
                  {
                    mystate=S_Id_Partial;
                  }
                return true;
              }
            else return false;
          }
        case S_Fn_Partial:
          {
            if (fnB_->pushToken(tok,whyNot,masterObjective))
              {
                if (fnB_->isFinal())
                  {
                    mystate=S_Fn_Final;
                    data_.reset(fnB_->unloadClosure());

                  }
                else
                  mystate=S_Fn_Partial;
                return true;
              }
            else return false;
          }
        case S_Data_Partial:
          {
            if (dataB_->pushToken(tok,whyNot,masterObjective))
              {
                if (dataB_->isFinal())
                  {

                    data_.reset(dataB_->unloadClosure());

                    mystate=S_Data_Final;
                  }
                else
                  mystate=S_Data_Partial;
                return true;
              }
            else return false;
          }
        case S_Data_Final:
        case S_Id_Final:
        case S_Fn_Final:
          return false;
        }
    }

    bool isFinal()const override
    {
      return mystate==S_Data_Final
          || mystate==S_Id_Final
          || mystate==S_Fn_Final;

    }
    bool isInitial()const override
    {
      return mystate==S_Init;

    }

    virtual bool hasMandatory()const override
    {
    }

    virtual bool hasNoArguments()const{}


    ~buildClosureByToken(){}



    ABC_R_Closure<R>* unloadClosure()
    {
      if (isFinal())
        {
          ABC_R_Closure<R>* out;
          mystate=S_Init;
          out= data_.release();
          return out;
        }
      else
        return {};
    }

    bool unPop(ABC_R_Closure<R>* var)
    {
      return false;

    }

    buildClosureByToken(const StructureEnv_New* parent,
                        const Implements_Closure_Type<R> *varType):
      ABC_BuildClosure(parent),
      mystate(S_Init),cType_(varType),
      dataB_(varType->myConstantType(parent)->getBuildClosureByToken(parent)),
      xB_(varType->myIdentifierType(parent)->getBuildClosureByToken(parent)),
      fnB_(varType->myFunctionType(parent)->getBuildClosureByToken(parent)),
      data_(){}

    void clear()override
    {}



    virtual std::pair<std::string, std::set<std::string> > alternativesNext() const override
    {
      std::pair<std::string, std::set<std::string> > out;
      switch (mystate)
        {
        case S_Init:
          {
            out=xB_->alternativesNext();
            out+=fnB_->alternativesNext();
            out+=dataB_->alternativesNext();
            return out;
          }
        case S_Id_Partial:  return xB_->alternativesNext();
        case S_Fn_Partial:  return fnB_->alternativesNext();
        case S_Data_Partial: return dataB_->alternativesNext();

        case S_Id_Final:
        case S_Fn_Final:
        case S_Data_Final:
          return {};

        }
    }

    virtual Token_New popBackToken() override
    {

    }

    virtual void reset_Type(Implements_Data_Type_New<ABC_Closure*> *dataTy)
    {

    }







  protected:
    DFA mystate;
    const Implements_Closure_Type<R> * cType_;
    std::unique_ptr<buildClosureByToken<R,int>> dataB_;
    std::unique_ptr<buildClosureByToken<R,std::string>> xB_;
    std::unique_ptr<buildClosureByToken<R,void*>> fnB_;
    std::unique_ptr<ABC_R_Closure<R>> data_;
  };


  template<typename R>
  class buildClosureByToken<R, void* >
      :public ABC_BuildClosure
  {
  public:

    typedef ABC_R_function<R> myC;

    enum DFA {
      S_Init=0, S_Closure_PARTIAL, S_Closure_Mandatory,S_Closure_Final,S_Final
    } ;

    bool pushToken(Token_New tok, std::string* whyNot,const std::string& masterObjective)override;

    bool isFinal()const override
    {
      return mystate==S_Final;

    }
    bool isInitial()const override
    {
      return mystate==S_Init;

    }

    virtual bool hasMandatory()const override
    {
      return (mystate==S_Closure_Mandatory)
          && (mystate==S_Closure_Final)
          && (mystate==S_Final);
    }


    ~buildClosureByToken(){}


    virtual bool hasNoArguments()const override
    {
      return hasNoArguments(vecValueB_,nPushedTokens_,nPushedTokensIn_);
    }

    bool unPop(ABC_Closure* var)
    {
      data_.reset(var)  ;
      mystate=S_Final;
      return true;

    }

    buildClosureByToken(const StructureEnv_New* parent,
                        const Implements_Closure_Type<R,void*> *varType);

    void clear()override
    {}




    virtual std::pair<std::string, std::set<std::string> > alternativesNext() const override;

    virtual Token_New popBackToken() override;

    virtual void reset_Type(Implements_Data_Type_New<ABC_Closure*> *dataTy);



    virtual ABC_R_function<R>* unloadClosure() override
    {
      if (isFinal())
        {
          ABC_R_function<R>* out=data_.release();
          mystate=S_Init;
          nPushedTokens_=0;
          return out;
        }
      else return nullptr;


    }



  protected:
    DFA mystate;
    const Implements_Data_Type_New<ABC_Closure*> * fnType_;

    const Implements_Identifier* idtype_;
    std::string idString_;
    std::unique_ptr<buildByToken<std::string,false>> idObjB_;
    std::vector<std::unique_ptr<ABC_BuildClosure>> vecValueB_;
    std::vector<size_t> nPushedTokensIn_;
    std::size_t nPushedTokens_;
    std::unique_ptr<ABC_BuildClosure> valueB_;
    std::unique_ptr<ABC_R_function<R>> data_;

    static bool isFinal(const std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t nPushedTokens,const std::vector<std::size_t> & nPushedTokensIn)
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

    static std::pair<std::string, std::set<std::string> > alternativesNext(const std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t nPushedTokens,const std::vector<std::size_t> & nPushedTokensIn)
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


    static bool hasNoArguments(const std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t nPushedTokens,const std::vector<std::size_t> & nPushedTokensIn)
    {
      for (std::size_t i=0; i<vecValue.size(); ++i)
        {
          if (nPushedTokensIn[i]==nPushedTokens)
            {
              return vecValue[i]->hasNoArguments();
            }
        }
      return false;
    }


    static bool hasMandatory(const std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t nPushedTokens,const std::vector<std::size_t> & nPushedTokensIn)
    {
      for (std::size_t i=0; i<vecValue.size(); ++i)
        {
          if (nPushedTokensIn[i]==nPushedTokens)
            {
              if (vecValue[i]->hasMandatory())
                return true;
            }
        }
      return false;
    }


    static bool pushToken(std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t &nPushedTokens, std::vector<std::size_t> & nPushedTokensIn,Token_New tok, std::string* whyNot,const std::string& masterObjective)
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
      if (out) ++nPushedTokens;
      return out;

    }

    static Token_New popBackToken(std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t &nPushedTokens, std::vector<std::size_t> & nPushedTokensIn)
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


    static ABC_Closure* unloadClosure(std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t &nPushedTokens, std::vector<std::size_t> & nPushedTokensIn)
    {
      for (std::size_t i=0; i<vecValue.size(); ++i)
        {
          if ((nPushedTokensIn[i]==nPushedTokens)&& vecValue[i]->hasMandatory())
            {
              return vecValue[i]->unloadClosure();
            }
        }
      return nullptr;
    }




    static bool isInitial(const std::vector<std::unique_ptr<ABC_BuildClosure>>& vecValue, std::size_t nPushedTokens, const std::vector<std::size_t> & nPushedTokensIn)
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

  };



  template<typename T>
  class buildClosureByToken<T,std::string>
      :public ABC_BuildClosure

  {
  public:
    typedef Implements_Closure_Value<T,std::string> myC;

    buildClosureByToken(const StructureEnv_New* parent,
                        const Implements_Closure_Type<T, std::string>* typeVar):
      ABC_BuildClosure(parent),
      varType_(typeVar),
      xB_(typeVar->getIdentifierType(parent)->getBuildByToken(parent)),
      xC_(nullptr)
    {

    }
    myC* unloadClosure()
    {
      return xC_.release();
    }

    bool pushToken(Token_New t, std::string* whyNot, const std::string& masterObjective)override
    {
      bool out=xB_->pushToken(t,whyNot,masterObjective);
      if (out && (xB_->isFinal()))
        {
          xC_.reset(new Implements_Closure_Value<T,std::string>(varType_,xB_->unloadVar()));
        }
      return out;
    }

    std::pair<std::string,std::set<std::string>> alternativesNext()const override
    {
      return xB_->alternativesNext();
    }


    void clear()override
    {
      xB_->clear();
      xC_.reset();
    }

    virtual void reset_Type(const Implements_Closure_Type<T,std::string>*  var)
    {
      clear();
      varType_=var;
      xC_.reset();
      xB_->reset_Type(var->getIdentifierType(parent()));
    }



    virtual ~buildClosureByToken(){}


    Token_New popBackToken() override
    {
      return xB_->popBackToken();
    }

    bool isFinal()const override
    {
      return xB_->isFinal();
    }

    bool isInitial()const override
    {
      return xB_->isInitial();
    }



    virtual bool hasMandatory()const{}
    virtual bool hasNoArguments()const{}


  protected:
    const Implements_Closure_Type<T,std::string>*  varType_;
    std::unique_ptr<buildByToken<std::string>> xB_;
    std::unique_ptr<Implements_Closure_Value<T,std::string>> xC_;
  };





  template<typename T>
  class buildClosureByToken<T,int >
      :public ABC_BuildClosure

  {
  public:
    typedef Implements_Closure_Value<T,int> myC;

    buildClosureByToken(const StructureEnv_New* parent,
                        const Implements_Closure_Type<T, int>* typeVar):
      ABC_BuildClosure(parent),
      varType_(typeVar),
      xB_(typeVar->myResultType(parent)->getBuildByToken(parent)),
      xC_()
    {

    }
    myC* unloadClosure() override
    {
      auto out=xC_.release();
      xC_.reset();
      return out;
    }

    bool pushToken(Token_New t, std::string* whyNot, const std::string& masterObjective)override
    {
      bool out=xB_->pushToken(t,whyNot,masterObjective);
      if (out && (xB_->isFinal()))
        {
          xC_.reset(new Implements_Closure_Value<T,int>(varType_,xB_->unloadVar()));
        }
      return out;
    }

    std::pair<std::string,std::set<std::string>> alternativesNext()const override
    {
      return xB_->alternativesNext();
    }


    void clear()override
    {
      xB_->clear();
      xC_.reset();
    }

//    virtual void reset_Type(const Implements_Closure_Type<T,int>*  var)
//    {
//      clear();
//      varType_=var;
//      xC_.reset();
//      xB_->reset_Type(var->getVarIdType(parent()));
//    }



    virtual ~buildClosureByToken(){}


    Token_New popBackToken() override
    {
      return xB_->popBackToken();
    }

    bool isFinal()const override
    {
      return xB_->isFinal();
    }

    bool isInitial()const override
    {
      return xB_->isInitial();
    }


    virtual bool hasMandatory()const{}
    virtual bool hasNoArguments()const{}



  protected:
    const Implements_Closure_Type<T,int>*  varType_;
    typedef  typename Implements_Data_Type_New<T>::myBuild myBuild;

    std::unique_ptr<myBuild> xB_;
    std::unique_ptr<Implements_Closure_Value<T,int>> xC_;
  };







  template<typename Fn, typename R,typename...Args>
  class buildClosureByToken<void,Fn,R,Args...>
      :public ABC_BuildClosure
  {
  public:

    typedef Implements_Closure_Value<void,Fn,R,Args...> myC;


    enum DFA {
      S_Init=0, S_Closure_PARTIAL, S_Closure_Mandatory,S_Closure_Final,S_Final
    } ;

    bool pushToken(Token_New tok, std::string* whyNot,const std::string& masterObjective)override

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
                  if (tok.tok()!=Token_New::EOL)
                    mystate =S_Closure_Final;
                  else
                    {
                      valueCl_.reset(new myC(fnType_,tupleB_->unloadClosure()));
                      mystate=S_Final;
                    }
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
                  if (tok.tok()!=Token_New::EOL)
                    mystate =S_Closure_Final;
                  else
                    {
                      valueCl_.reset(new myC(fnType_,tupleB_->unloadClosure()));
                      mystate=S_Final;
                      return true;
                    }
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
              valueCl_.reset(new myC(fnType_,tupleB_->unloadClosure()));
              mystate=S_Final;
              return true;
            }

        case S_Final:
          return false;
        }
    }


    bool isFinal()const override
    {
      return mystate==S_Final;

    }
    bool isInitial()const override
    {
      return mystate==S_Init;

    }


    ~buildClosureByToken(){}



    ABC_Closure* unloadVar()
    {
      if (isFinal())
        {
          ABC_Closure* out;
          mystate=S_Init;
          out= valueCl_.release();
          return out;
        }
      else
        return {};
    }

    bool unPop(ABC_Closure* var)
    {
      return false;
    }

    buildClosureByToken(const StructureEnv_New* parent,
                        const Implements_Closure_Type<void,Fn,R,Args...> *varType):
      ABC_BuildClosure(parent),
      mystate(S_Init)
    ,fnType_(varType), tupleType_(varType->getArgumentsType(parent)),
      tupleB_(varType->getArgumentsType(parent)
              ->getBuildClosureByToken(parent))
    ,valueCl_(new Implements_Closure_Value<void,Fn,R,Args...>(varType,{})){

      if (tupleB_->isFinal())
        {
          mystate =S_Closure_Final;
        }
      else if (tupleB_->hasMandatory())
        {
          mystate=S_Closure_Mandatory;
        }
      else
        {
          mystate=S_Closure_PARTIAL;
        }

    }




    void clear()override
    {}



    virtual std::pair<std::string, std::set<std::string> > alternativesNext() const override

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


    virtual Token_New popBackToken() override

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


    virtual void reset_Type(Implements_Data_Type_New<ABC_Closure*> *dataTy)
    {
    }



    virtual bool hasNoArguments()const override
    {
      return isInitial();
    }

    virtual bool hasMandatory()const override
    {
      return (mystate==S_Closure_Mandatory)
          || (mystate==S_Closure_Final)
          || (mystate==S_Final);
    }

    virtual ABC_Closure* unloadClosure() override
    {

      return unloadVar();

    }


  protected:
    DFA mystate;
    const Implements_Closure_Type<void,Fn,R,Args...> * fnType_;
    const Implements_Closure_Type<std::tuple<Args...>> * tupleType_;
    std::unique_ptr<buildClosureByToken<std::tuple<Args...>>> tupleB_;
    std::unique_ptr<Implements_Closure_Value<void,Fn,R,Args...>> valueCl_;

  };


  /*!
           * \brief The build_Statement class
           * decide if it is either command, variable declaration, initialization or asignation
           */




  class build_StatementNew
      :public ABC_BuildByToken_
  {
  public:
    enum DFA {
      S_Init,
      S_Function_Partial,
      S_Function_Final,
      S_Expression_Partial,
      S_Expression_Final

    } ;


    build_StatementNew(const StructureEnv_New *p,
                       const Implements_Data_Type_New<Implements_Var> *varType
                       , const Implements_Closure_Type<void *> *clType);


    virtual ~build_StatementNew(){}

    void clear()override;


    Implements_Var unloadVar()
    {
      if (mystate!=S_Expression_Final)
        {

          return {};
        }
      else
        {
          auto out=x_;
          mystate=S_Init;
          x_.data=nullptr;
          return out;

        }
    }





    bool isCommand()const
    {
      return mystate==S_Function_Final
          || mystate==S_Function_Final
          || mystate==S_Function_Partial;
    }
    bool isVar()const
    {
      return mystate==S_Expression_Final
          || mystate==S_Expression_Partial;

    }


    ABC_Closure* unloadClosure()
    {
      if (isFinal())
        return cl_.release();
      else return nullptr;
    }



    Token_New popBackToken()override;



    bool isFinal()const override
    {
      return mystate==S_Expression_Final
          || mystate==S_Function_Final;

    }

    bool isInitial()const override
    {
      return mystate==S_Init;
    }

  public:
    virtual bool pushToken(Token_New t, std::string *whyNot, const std::string &masterObjective) override

    {
      const std::string objective=masterObjective;
      switch (mystate)
        {
        case S_Init:
          if (cb_->pushToken(t, whyNot,objective))
            {
              mystate=S_Function_Partial;
              return true;
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
        case S_Function_Partial:
          if (!cb_->pushToken(t, whyNot,objective))
            {
              return false;
            }
          else
            {
              if (cb_->isFinal())
                {
                  mystate=S_Function_Final;
                  cl_.reset(cb_->unloadClosure());
                }
              else
                mystate=S_Function_Partial;
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
        case S_Function_Final:
        case S_Expression_Final:
          return false;
        }

    }

    virtual std::pair<std::string, std::set<std::string> > alternativesNext() const override

    {
      std::pair<std::string,std::set<std::string>> out;
      switch (mystate)
        {
        case S_Init:
          out=cb_->alternativesNext();
          out+=v_->alternativesNext();
          return out;
        case S_Function_Partial:
          return cb_->alternativesNext();
        case S_Expression_Partial:
          return v_->alternativesNext();
        case S_Function_Final:
        case S_Expression_Final:
          return {};

        }

    }


  private:
    DFA mystate;
    std::unique_ptr<buildByToken<Implements_Var>>   v_;
    std::unique_ptr<buildClosureByToken<void*>> cb_;
    std::unique_ptr<ABC_Closure> cl_;
    Implements_Var x_;

    // ABC_BuildByToken interface

  };




  class build_Statement_on_Id
      :public ABC_BuildByToken

  {
  public:
    enum DFA {
      S_Init,
      S_IdPartial,
      S_IdFinal,
      S_Final
    } ;


    virtual bool pushToken(Token_New t
                           , std::string* whyNot
                           , const std::string& masterObjective) override
    {
      switch (mystate)
        {
        case S_Init:
        case S_IdPartial:
          {
            if (!idB_->pushToken(t,whyNot,masterObjective))
              return false;
            else
              {
                if (idB_->isFinal())
                  {
                    id_=idB_->unloadVar();
                    mystate=S_IdFinal;
                    return true;
                  }
                else
                  {
                    mystate=S_IdPartial;
                    return true;
                  }
              }
          }

        case S_IdFinal:
          {
            if (t.tok()==Token_New::EOL)
              {

              }
          }
        case S_Final:
          return false;
        }


    }

    virtual  std::pair<std::string,std::set<std::string>> alternativesNext()const override  {}

    virtual Token_New popBackToken() override  {}
    virtual bool isFinal()const override  {}
    virtual bool isInitial()const override  {}

    virtual ~build_Statement_on_Id(){}

    virtual void clear() override  {}

    const StructureEnv_New* parent()const;

    virtual ABC_Data_New* unloadData() override  {}

    virtual bool unpopData(ABC_Data_New* data) override  {}




  private:
    DFA mystate;
    Implements_Identifier* idType_;
    buildByToken<std::string> * idB_;
    std::string id_;
  };



}





#endif // BUILDCLOSUREBYTOKEN_H
