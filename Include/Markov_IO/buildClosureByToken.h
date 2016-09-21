#ifndef BUILDCLOSUREBYTOKEN_H
#define BUILDCLOSUREBYTOKEN_H



#include "Markov_IO/buildByToken.h"
#include "Markov_IO/Cls.h"
#include "Markov_IO/Closure.h"

#include "Markov_IO/Token_New.h"
#include "Markov_LA/Matrix.h"
#include "Markov_IO/Var.h"

#include <string>
#include <set>
#include <map>
#include <vector>
#include <deque>
#include <memory>
#include <utility>

namespace Markov_IO_New {




  class ABC_Type_of_Function;





  class ABC_BuildClosure : public ABC_BuildByToken_
  {
  public:


    virtual ABC_Closure* unloadClosure()=0;
    virtual bool unPopClosure(ABC_Closure* cl)=0;


    virtual bool hasMandatory()const
    {
      return isFinal();
    }

    virtual ~ABC_BuildClosure(){}

  };

  template <typename R>
  class ABC_BuildClosure_R : public ABC_BuildClosure
  {
  public:
    virtual ~ABC_BuildClosure_R(){}
    ABC_R_Closure<R>* unloadClosure()=0;
  };

  template <class myClosure> class ClosureType_Union;

  template <class myClosure>
  std::vector<std::unique_ptr<typename myClosure::buildClosure>>
  getBuildVector(const StructureEnv_New* cm
                 , const ClosureType_Union<myClosure>* t);


  template<class myClosure>
  class BuildClosure_Union: public  myClosure::buildClosure
  {
  public:
    typedef typename myClosure::returnedClosure  myReturn_Closure;

    typedef typename myClosure::buildClosure  baseBuild;
    virtual ~BuildClosure_Union(){}

    bool isFinal() const
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

    std::pair<std::string, std::set<std::string> > alternativesNext()const override
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


    bool hasNoArguments() const
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


    bool hasMandatory()const override
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


    bool pushToken(Token_New tok, std::string* whyNot,const std::string& masterObjective)override
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

    Token_New popBackToken() override
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


    myReturn_Closure* unloadClosure() override
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



    bool unPopClosure(ABC_Closure* cl) override
    {
      bool out;
      std::size_t iOv;
      while((!vecValue[iOv]->unPopClosure(cl)) &&(iOv < vecValue.size())) ++iOv;

      if (iOv>=vecValue.size())
        return false;
      else
        {
          std::string whyNot;

          std::deque<Token_New> tk;
          while(!vecValue[iOv]->isInitial())
            tk.push_back(vecValue[iOv]->popBackToken());
          for (std::size_t i=tk.size(); i>0; --i)
            pushToken(tk[i-1],&whyNot,"");
          return true;
        }
    }


    virtual void clear()
    {

    }




    virtual bool isInitial() const override
    {
      return nPushedTokens==0;
    }

    BuildClosure_Union(const StructureEnv_New* cm
                       , const ClosureType_Union<myClosure>* t)
      : p_(cm), vecValue(getBuildVector(cm,t))
    {
      nPushedTokensIn=std::vector<std::size_t>(vecValue.size(),0);
      nPushedTokens=0;
    }



    const StructureEnv_New* parent() const override {return p_;}

  private:
    const StructureEnv_New* p_;
    std::vector<std::unique_ptr<baseBuild>> vecValue;
    std::vector<size_t> nPushedTokensIn;
    std::size_t nPushedTokens;
  };


  template <class...C>
  class buildClosureByToken
  {
  };


  template<typename... Args>
  class buildClosureByToken<std::tuple<Args...>>
      :public ABC_BuildClosure_R<std::tuple<Args...>>

  {
  public:
    typedef Implements_Closure_Value<std::tuple<Args...>> myC;
    typedef std::tuple<Implements_Fn_Argument<Args>...> dataArgumentsTuple;
    typedef Implements_Closure_Type<std::tuple<Args...>>  vType;
    typedef std::tuple<std::unique_ptr<buildClosureByToken<Args>>...> buildTuple;
    typedef std::tuple<Args...> argTuple;


    enum DFA {
      S_Init, S_Header_Final,S_Element_Partial, S_Element_Final,S_Mandatory,
      S_Arguments_Final,
      S_Final};

    buildClosureByToken(const StructureEnv_New* paren,
                        const Implements_Closure_Type<std::tuple<Args...>>* typeVar):
      p_(paren),
      mystate(S_Init),
      varType_(typeVar)
    ,buildTupl_(getBuildTuple(paren,typeVar->getFnArguments(paren)
                              ,std::index_sequence_for<Args...>()))
    ,xTupl_()
    {
    }

    bool hasMandatory()const
    {
      return (mystate==S_Mandatory)
          ||(mystate==S_Arguments_Final)
          || (mystate==S_Final);

    }








    myC* unloadClosure() override
    {
      if (isFinal())
        {
          auto out=new Implements_Closure_Value<
              std::tuple<Args...>
              > (varType_,xTupl_,iArg_);
          xTupl_={};
          mystate=S_Init;
          iArg_=0;
          return out;
        }
      else return nullptr;
    }

    void unPop(myC* in)
    {
      iArg_=in->iArg();
      xTupl_=in->unloadTuple();
      mystate=S_Final;
    }

    bool unPopClosure(ABC_Closure* cl)
    {
      auto p=dynamic_cast<myC*>(cl);
      if (p!=nullptr)
        {
          unPop(p);
          return true;
        }
      else return false;
    }




    bool pushToken(Token_New t, std::string* whyNot, const std::string& masterObjective)override
    {
      const std::string objective=masterObjective+": "+"Token "+t.str()+" was not accepted by ";
      switch (mystate)
        {
        case S_Init:
          if (t.tok()==Token_New::LP)
            {
              if (hasMandatory_imp(parent()
                                   ,std::index_sequence_for<Args...>()
                                   ,iArg_,varType_->getFnArguments(parent())))
                mystate=S_Mandatory;
              else
                mystate=S_Header_Final;
              return true;
            }
          else
            {
              *whyNot=objective+"expected left parentesis";
              return false;
            }
        case S_Mandatory:
          if (t.tok()==Token_New::RP)
            {
              varType_->fill(parent(),xTupl_, iArg_);
              mystate=S_Final;
              return true;
            }
        case S_Header_Final:
        case S_Element_Partial:
        case S_Element_Final:
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
        case    S_Arguments_Final:
          if (t.tok()==Token_New::RP)
            {
              mystate=S_Final;
              return true;
            }
          else
            {
              *whyNot=objective+ "expected right parentheis";
              return false;
            }
        case S_Final:
          return false;

        }
    }



    std::pair<std::string,std::set<std::string>> alternativesNext()const override
    {

      switch (mystate)
        {
        case S_Init: return {"put the damm parenthesis",{"("}};
        case S_Arguments_Final : return {"we have all arguments",{")"}};
        case S_Final: return{};
        default:

          return alternativesNext_imp<0>
              (parent(),std::index_sequence_for<Args...>(),mystate,iArg_
               ,buildTupl_,
               varType_->getFnArguments(parent()));
        }
    }


    void clear()override
    {
      xTupl_={};
      mystate=S_Init;
      iArg_=0;
      clear_imp(std::index_sequence_for<Args...>(),buildTupl_);
    }

    //    virtual void reset_Type(const Implements_Data_Type_New<myC>* var)
    //    {
    //      clear();
    //      varType_=var;
    //      buildTupl_=getBuildTuple(parent(),varType_->getArgumentTypes()
    //                               ,std::index_sequence_for<Args...>());

    //    }


    Token_New popBackToken() override
    {
      switch (mystate)
        {
        case S_Init: return {};
        case S_Header_Final:
          mystate=S_Init;
          return Token_New(Token_New::LP);
        case S_Final:
          if (iArg_==std::tuple_size<std::tuple<Args...>>::value)
            mystate=S_Arguments_Final;
          else
            mystate=S_Mandatory;
          return Token_New(Token_New::RP);
        case S_Arguments_Final:
        case S_Mandatory:
        case S_Element_Final:
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
      return std::tuple<std::unique_ptr<buildClosureByToken<Args>>...> ( std::get<Is>(types).closureType(parent)->getBuildClosureByToken(parent)...
                                                                         );
    }

    template<std::size_t D>
    static bool pushToken_imp(const StructureEnv_New* cm,
                              DFA &state
                              ,std::size_t &i
                              ,buildTuple& b
                              ,const dataArgumentsTuple& a
                              ,std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...>& x
                              ,Token_New t, std::string* whyNot
                              , const std::string& masterObjective)
    {
      if(t.tok()==Token_New::RP)
        return true;
      else
        {
          *whyNot=masterObjective+" expected right parenthesis";
          return false;
        }
    }



    template<std::size_t D,std::size_t I, std::size_t...Is>
    static bool pushToken_imp(const StructureEnv_New* cm,
                              DFA &state
                              ,std::size_t &i
                              ,buildTuple& b
                              ,const dataArgumentsTuple& a
                              ,std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...>& x
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
          if (aT.isDefaulted())
            {
              std::get<I>(x).reset(aT.defaultValue());
              ++i;
              if (i==std::tuple_size<std::tuple<Args...>>::value)
                {
                  state=S_Arguments_Final;
                  return true;
                }
              return pushToken_imp<D,Is...>(cm,state,i,b,a,x,t,whyNot,masterObjective);

            }
          else if (!eB->pushToken(t,whyNot,masterObjective))
            {
              return false;
            }
          else if (eB->isFinal())
            {
              std::get<I>(x).reset(eB->unloadClosure());
              ++i;
              if (i==std::tuple_size<std::tuple<Args...>>::value)
                state=S_Arguments_Final;
              else if (hasMandatory_imp(cm,std::index_sequence_for<Args...>(),i,a))
                state=S_Mandatory;
              else
                state=S_Element_Final;
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
                              ,std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...>& x
                              ,Token_New t,
                              std::string* whyNot
                              , const std::string& masterObjective)
    {

      return pushToken_imp<0,Is...>(cm,state,i,b,a,x,t,whyNot,masterObjective);
    }





    template<std::size_t D>
    static bool hasMandatory_imp(const StructureEnv_New* cm,
                                 std::size_t i
                                 ,const dataArgumentsTuple& arg
                                 )
    {
      return true;
    }







    template<std::size_t D,std::size_t I, std::size_t ... Is>
    static bool hasMandatory_imp(const StructureEnv_New* cm,std::size_t i
                                 ,const dataArgumentsTuple& arg
                                 )
    {
      if (I<i)
        return hasMandatory_imp<D,Is...>(cm,i,arg);
      else
        {
          typedef typename std::tuple_element<I,std::tuple<Args...>>::type eType;
          const Implements_Fn_Argument<eType>& a=std::get<I>(arg);
          if (!a.isMandatory())
            return hasMandatory_imp<D,Is...>(cm,++i,arg);
          else
            return false;

        }
    }



    template<std::size_t ... Is>
    static bool hasMandatory_imp(const StructureEnv_New* cm,std::index_sequence<Is...>,std::size_t i
                                 ,const dataArgumentsTuple& arg
                                 )
    {
      return hasMandatory_imp<0,Is...>(cm,i,arg);
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
              std::pair<std::string,std::set<std::string>> out;
              if (state==S_Mandatory)
                out= {"mandatory arguments filled",{Token_New::toString(Token_New::RP)}};
              buildClosureByToken<eType>* eB=std::get<I>(b).get();
              out+={aT.id(),eB->alternativesNext().second};
              return out;
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
     ,const dataArgumentsTuple& a
     ,std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...>&x)
    {

      return {};

    }



    template<std::size_t D,std::size_t I,std::size_t... Is>
    static Token_New popBackToken_imp
    (const StructureEnv_New* cm,
     DFA &state
     ,std::size_t &i
     ,buildTuple& b
     ,const dataArgumentsTuple& a
     ,std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...>&x)
    {

      if (I<i)
        return popBackToken_imp<D,Is...>(cm,state,i,b,a,x);
      else
        {
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
                  eB->unPopClosure(std::get<I>(x).get());
                }
              out=eB->popBackToken();
              if (eB->isInitial())
                {
                  if (i==0)
                    state=S_Header_Final;
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
     ,std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...>& x)
    {
      return popBackToken_imp<0,Is...>(cm,state,i,b,a,x);

    }


    template<std::size_t...Is>
    static void clear_imp(std::index_sequence<Is...>,buildTuple& b)
    {
      auto l={(std::get<Is>(b)->clear(),1)...};
    }








    const StructureEnv_New* parent() const override {return p_;}

  private:
    const StructureEnv_New* p_;

    DFA mystate;
    const Implements_Closure_Type<std::tuple<Args...>> * varType_;
    std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...> xTupl_;
    std::size_t iArg_;
    buildTuple    buildTupl_;
  };








  template<>
  class buildClosureByToken<void*>
      :public ABC_BuildClosure
  {
  public:

    enum DFA {
      S_Init, S_Identifier_Partial,S_Identifier_Final, S_Closure_PARTIAL, S_Final
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



    ~buildClosureByToken();

    buildClosureByToken(const StructureEnv_New* parent,
                        const Implements_Closure_Type<void*> *varType);




    buildClosureByToken()=default;

    void clear()override
    {}

    virtual std::pair<std::string, std::set<std::string> > alternativesNext() const override;

    virtual Token_New popBackToken() override;



    virtual ABC_Closure* unloadClosure() override;

    bool unPopClosure(ABC_Closure* cl) override;



    const StructureEnv_New* parent() const override {return p_;}

  private:
    const StructureEnv_New* p_;
    DFA mystate;
    const Implements_Closure_Type<void*> * fnType_;
    const Implements_Identifier* idtype_;
    std::unique_ptr<buildByToken<std::string>> idB_;
    std::string idString_;
    const Implements_Closure_Type<void*> * rfnType_;

    std::unique_ptr<BuildClosure_Union<ABC_Function_Overload>> oUB_;
    std::unique_ptr<ABC_Closure> data_;



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
          if (idB_->pushToken(tok,whyNot,objective))
            {
              idObj_=idB_->unloadVar();
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
                  oUB_=getOverloadBuild(methodType_,parent());
                  nPushedTokensIn_=std::vector<std::size_t>(oUB_.size(),0);
                  nPushedTokens_=0;
                  if (isFinal(oUB_,nPushedTokens_,nPushedTokensIn_))
                    {
                      mystate =S_Closure_Final;
                      return true;
                    }
                  else if (hasMandatory(oUB_,nPushedTokens_,nPushedTokensIn_))
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
          if (pushToken(oUB_,nPushedTokens_,nPushedTokensIn_
                        ,tok, whyNot,objective))
            {
              if (isFinal(oUB_,nPushedTokens_,nPushedTokensIn_))
                {
                  if (tok.tok()!=Token_New::EOL)
                    {
                      mystate =S_Closure_Final;
                      return true;
                    }
                  else
                    {
                      data_.reset(unloadClosure(oUB_,nPushedTokens_,nPushedTokensIn_));
                      mystate=S_Final;
                      return true;
                    }
                }
              else  if (hasMandatory(oUB_,nPushedTokens_,nPushedTokensIn_))
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
              data_.reset(unloadClosure(oUB_,nPushedTokens_,nPushedTokensIn_));
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
    const Implements_Closure_Type<void*,C> * fnType_;
    std::unique_ptr<buildByToken<std::string>> idB_;
    std::string idObj_;
    Implements_Value_New<C>* objData_;
    const Implements_Data_Type_New<C>* objType_;
    std::unique_ptr<buildByToken<std::string>> idMethodB_;
    std::string idMethod_;
    const Implements_Closure_Type<void*,C> * methodType_;

    std::vector<std::unique_ptr<ABC_BuildClosure>> oUB_;
    std::vector<size_t> nPushedTokensIn_;
    std::size_t nPushedTokens_;
    std::unique_ptr<ABC_BuildClosure> valueB_;
    std::unique_ptr<ABC_Closure> data_;



  };



  template<typename R>
  class buildClosureByToken<R>
      :public ABC_BuildClosure_R<R>
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


    ~buildClosureByToken(){}



    ABC_R_Closure<R>* unloadClosure()
    {
      if (isFinal())
        {
          if(mystate==S_Id_Final)
            data_.reset(xB_->unloadClosure());
          else if (mystate==S_Data_Final)
            data_.reset(dataB_->unloadClosure());
          else
            data_.reset(fnB_->unloadClosure());
          ABC_R_Closure<R>* out;
          mystate=S_Init;
          out= data_.release();
          return out;
        }
      else
        return {};
    }

    bool unPopClosure(ABC_Closure* cl)
    {
      if (xB_->unPopClosure(cl))
        {
          mystate=S_Id_Final;
          return true;
        }
      else if (dataB_->unPopClosure(cl))
        {
          mystate=S_Data_Final;
          return true;
        }
      else if (fnB_->unPopClosure(cl))
        {
          mystate=S_Fn_Final;
          return true;
        }
      else return false;

    }




    buildClosureByToken(const StructureEnv_New* parent,
                        const Implements_Closure_Type<R> *varType):
      p_(parent),
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
      switch (mystate)
        {
        case S_Init: return {};
        case S_Id_Final:
        case S_Id_Partial:
          {
            auto out=xB_->popBackToken();
            if (xB_->isInitial())
              mystate=S_Init;
            else
              mystate=S_Id_Partial;
            return out;
          }
        case S_Data_Partial:
        case S_Data_Final:
          {
            auto out=dataB_->popBackToken();
            if (dataB_->isInitial())
              mystate=S_Init;
            else
              mystate=S_Data_Partial;
            return out;
          }
        case S_Fn_Final:
        case S_Fn_Partial:
          {
            auto out=fnB_->popBackToken();
            if (fnB_->isInitial())
              mystate=S_Init;
            else
              mystate=S_Fn_Partial;
            return out;
          }

        }
    }

    const StructureEnv_New* parent() const override {return p_;}

  private:
    const StructureEnv_New* p_;

    DFA mystate;
    const Implements_Closure_Type<R> * cType_;
    std::unique_ptr<buildClosureByToken<R,int>> dataB_;
    std::unique_ptr<buildClosureByToken<R,std::string>> xB_;
    std::unique_ptr<buildClosureByToken<R,void*>> fnB_;
    std::unique_ptr<ABC_R_Closure<R>> data_;
  };


  template<typename R>
  class buildClosureByToken<R, void* >
      :public ABC_BuildClosure_R<R>

  {
  public:

    typedef ABC_R_Closure<R> myC;

    enum DFA {
      S_Init, S_Identifier_Final, S_Closure_PARTIAL, S_Final
    } ;

    bool pushToken(Token_New tok, std::string* whyNot,const std::string& masterObjective)override;


    bool isFinal()const override;
    bool isInitial()const override;

    virtual bool hasMandatory()const override;


    ~buildClosureByToken();

    buildClosureByToken(const StructureEnv_New* parent,
                        const Implements_Closure_Type<R,void*> *varType);



    buildClosureByToken()=default;

    void clear()override;

    virtual std::pair<std::string, std::set<std::string> > alternativesNext() const override;

    virtual Token_New popBackToken() override;




    virtual myC* unloadClosure() override;



    virtual bool unPopClosure(ABC_Closure* cl);
    const StructureEnv_New* parent() const override;

  private:
    const StructureEnv_New* p_;
    DFA mystate;
    const Implements_Data_Type_New<R>* resultType_;
    const Implements_Closure_Type<R,void*> * fnType_;
    const Implements_Identifier* idtype_;
    std::unique_ptr<buildByToken<std::string>> idB_;
    std::string idString_;
    const Implements_Closure_Type<R,void*> * rfnType_;
    std::unique_ptr<BuildClosure_Union<ABC_Function_R_Overload<R>>> oUB_;
    std::unique_ptr<ABC_R_Closure<R>> data_;
  };







  template<typename R>
  class buildClosureByToken<R,std::string>
      :public ABC_BuildClosure_R<R>

  {
  public:
    typedef Implements_Closure_Value<R,std::string> myC;
    enum DFA {S_Init, S_Partial, S_Final};

    buildClosureByToken(const StructureEnv_New* parent,
                        const Implements_Closure_Type<R, std::string>* typeVar):
      p_(parent),
      mystate(S_Init),
      varType_(typeVar),
      xB_(typeVar->getIdentifierType(parent)->getBuildByToken(parent)),
      xC_()
    {

    }
    buildClosureByToken(const StructureEnv_New* parent):
      p_(parent),
      mystate(S_Init),
      varType_(),
      xB_(),
      xC_()
    {

    }




    myC* unloadClosure() override
    {
      if (isFinal())
        {
          xC_.reset(new Implements_Closure_Value<R,std::string>
                    (varType_,xB_->unloadVar()));

          auto out=xC_.release();
          xC_.reset();
          return out;
        }
      else return {};
    }

    void unPop(myC* in)
    {
      xC_.reset(in);
      xB_->unPop(xC_->unload());
      mystate= S_Final;
    }
    bool unPopClosure(ABC_Closure* cl)
    {
      auto p=dynamic_cast<myC*>(cl);
      if (p!=nullptr)
        {
          unPop(p);
          return true;
        }
      else return false;
    }



    bool pushToken(Token_New t, std::string* whyNot, const std::string& masterObjective)override
    {
      switch (mystate)
        {
        case S_Init:
        case S_Partial:
          if (!xB_->pushToken(t,whyNot,masterObjective))
            return false;
          else
            { if (xB_->isFinal())
                {
                  mystate=S_Final;
                  return true;
                }
              else
                {
                  mystate=S_Partial;
                  return true;
                }
            }
        case S_Final:
          return false;
        }
    }

    std::pair<std::string,std::set<std::string>> alternativesNext()const override
    {
      switch (mystate)
        {
        case S_Init:
        case S_Partial:
          return xB_->alternativesNext();
        case S_Final: return{};
        }
    }




    void clear()override
    {
      xB_->clear();
      xC_.reset();
    }

    virtual void reset_Type(const Implements_Closure_Type<R,std::string>*  var)
    {
      clear();
      varType_=var;
      xC_.reset();
      xB_->reset_Type(var->getIdentifierType(parent()));
    }



    virtual ~buildClosureByToken(){}


    Token_New popBackToken() override
    {

      switch (mystate)
        {
        case S_Init: return {};
        case S_Final:
        case S_Partial:
          {
            Token_New out=xB_->popBackToken();
            if (xB_->isInitial())
              {
                mystate=S_Init;
                return out;
              }
            else
              {
                mystate=S_Partial;
                return out;
              }
          }
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




    const StructureEnv_New* parent() const override {return p_;}

  private:
    const StructureEnv_New* p_;
    DFA mystate;
    const Implements_Closure_Type<R,std::string>*  varType_;
    std::unique_ptr<buildByToken<std::string>> xB_;
    std::unique_ptr<Implements_Closure_Value<R,std::string>> xC_;
  };





  template<typename R>
  class buildClosureByToken<R,int >
      :public ABC_BuildClosure_R<R>

  {
  public:

    enum DFA {S_Init, S_Partial, S_Final};

    typedef Implements_Closure_Value<R,int> myC;

    buildClosureByToken(const StructureEnv_New* parent,
                        const Implements_Closure_Type<R, int>* typeVar):
      p_(parent),
      mystate(S_Init),
      varType_(typeVar),
      xB_(typeVar->myResultType(parent)->getBuildByToken(parent)),
      xC_()
    {

    }
    buildClosureByToken(const StructureEnv_New* parent):
      p_(parent),
      mystate(S_Init),
      varType_(),
      xB_(),
      xC_()
    {

    }


    myC* unloadClosure() override
    {
      if (isFinal())
        {
          auto out=xC_.release();
          xC_.reset();
          return out;
        }
      else return {};
    }

    void unPop(myC* in)
    {
      xC_.reset(in);
      mystate= S_Final;
    }
    bool unPopClosure(ABC_Closure* cl)
    {
      auto p=dynamic_cast<myC*>(cl);
      if (p!=nullptr)
        {
          unPop(p);
          return true;
        }
      else return false;
    }


    bool pushToken(Token_New t, std::string* whyNot, const std::string& masterObjective)override
    {
      switch (mystate)
        {
        case S_Init:
        case S_Partial:
          if (!xB_->pushToken(t,whyNot,masterObjective))
            return false;
          else
            { if (xB_->isFinal())
                {
                  xC_.reset(new Implements_Closure_Value<R,int>(varType_,xB_->unloadVar()));
                  mystate=S_Final;
                  return true;
                }
              else
                {
                  mystate=S_Partial;
                  return true;
                }
            }
        case S_Final:
          return false;
        }
    }

    std::pair<std::string,std::set<std::string>> alternativesNext()const override
    {
      switch (mystate)
        {
        case S_Init:
        case S_Partial:
          return xB_->alternativesNext();
        case S_Final: return{};
        }
    }


    void clear()override
    {
      xB_->clear();
      xC_.reset();
    }



    virtual ~buildClosureByToken(){}


    Token_New popBackToken() override
    {

      switch (mystate)
        {
        case S_Init: return {};
        case S_Final:
          xB_->unPop(xC_->unload());
        case S_Partial:
          {
            Token_New out=xB_->popBackToken();
            if (xB_->isInitial())
              {
                mystate=S_Init;
                return out;
              }
            else
              {
                mystate=S_Partial;
                return out;
              }
          }
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
    const StructureEnv_New* parent() const override {return p_;}

  private:
    const StructureEnv_New* p_;
    DFA mystate;
    const Implements_Closure_Type<R,int>*  varType_;
    typedef  typename Implements_Data_Type_New<R>::myBuild myBuild;

    std::unique_ptr<myBuild> xB_;
    std::unique_ptr<Implements_Closure_Value<R,int>> xC_;
  };







  template<typename R, typename Fn,typename...Args>
  class buildClosureByToken<R,void,Fn,Args...>
      :public ABC_BuildClosure_R<R>
  {
  public:

    typedef Implements_Closure_Value<R,void,Fn,Args...> myC;

    enum DFA {
      S_Init=0, S_Closure_PARTIAL, S_Final
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
                  mystate=S_Final;
                  return true;
                }
              else
                {
                  mystate=S_Closure_PARTIAL;
                  return true;
                }
            }
          else
            return false;
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



    Implements_Closure_Value<R,void,Fn,Args...>* unloadClosure()
    {
      if (isFinal())
        {
          mystate=S_Init;
          valueCl_.reset(new myC(fnType_,tupleB_->unloadClosure()));

          Implements_Closure_Value<R,void,Fn,Args...>*out= valueCl_.release();
          tupleB_->clear();
          return out;
        }
      else
        return {};
    }

    void unPop(Implements_Closure_Value<R,void,Fn,Args...>* var)
    {
      valueCl_.reset(var);
      tupleB_->unPop(var->unload());

      mystate=S_Final;
    }

    bool unPopClosure(ABC_Closure* cl)
    {
      auto p=dynamic_cast<Implements_Closure_Value<R,void,Fn,Args...>*>(cl);
      if (p!=nullptr)
        {
          unPop(p);
          return true;
        }
      else return false;
    }

    buildClosureByToken(const StructureEnv_New* parent,
                        const Implements_Closure_Type<R,void,Fn,Args...> *varType):
      p_(parent),
      mystate(S_Init)
    ,fnType_(varType),
      tupleB_(varType->getArgumentsType(parent)->getBuildClosureByToken(parent))
    ,valueCl_(new Implements_Closure_Value<R,void,Fn,Args...>(varType,{})){

    }



    void clear()override
    {
      mystate=S_Init;
      tupleB_->clear();
    }



    virtual std::pair<std::string, std::set<std::string> > alternativesNext() const override

    {
      switch (mystate)
        {
        case S_Init:
        case S_Closure_PARTIAL:
          return tupleB_->alternativesNext();
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
          {
            Token_New out=tupleB_->popBackToken();
            if (tupleB_->isInitial())
              {
                mystate=S_Init;
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

    virtual bool hasMandatory()const override
    {
      return tupleB_->hasMandatory();
    }

    const StructureEnv_New* parent() const override {return p_;}

  private:
    const StructureEnv_New* p_;
    DFA mystate;
    const Implements_Closure_Type<R,void,Fn,Args...> * fnType_;
    std::unique_ptr<buildClosureByToken<std::tuple<Args...>>> tupleB_;
    std::unique_ptr<Implements_Closure_Value<R,void,Fn,Args...>> valueCl_;

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





    bool isFunction()const
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
          if (t.tok()==Token_New::EOL)
            return true;
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


    const StructureEnv_New* parent() const override {return p_;}

  private:
    const StructureEnv_New* p_;
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


    virtual ABC_Data_New* unloadData() override  {}

    virtual bool unpopData(ABC_Data_New* data) override  {}




    const StructureEnv_New* parent() const override {return p_;}

  private:
    const StructureEnv_New* p_;
    DFA mystate;
    Implements_Identifier* idType_;
    buildByToken<std::string> * idB_;
    std::string id_;
  };



}





#endif // BUILDCLOSUREBYTOKEN_H
