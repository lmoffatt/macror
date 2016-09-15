#ifndef BUILDBYTOKEN
#define BUILDBYTOKEN


#include "Markov_IO/Cls.h"

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
  
  
  
  template <class T, bool isClass>
  class buildByToken;



  
  class StructureEnv_New;
  class ABC_Data_New;
  
  class ABC_Type_of_Value;
  
  class ABC_Type_of_Function;
  
  
  
  
  class Implements_Complex_Data_Type;
  
  class Implements_Command_Arguments;
  
  class Implements_Command_Type_New;
  
  class Implements_Identifier;
  class Identifier_Union;
  
  template<typename T>
  class Implements_Fn_Argument;
  
  class Markov_CommandManagerVar;
  
  class ABC_BuildByToken_
  {
  public:
    
    
    virtual bool pushToken(Token_New t
                           , std::string* whyNot
                           , const std::string& masterObjective)=0;
    
    virtual  std::pair<std::string,std::set<std::string>> alternativesNext()const=0;
    
    virtual Token_New popBackToken()=0;
    virtual bool isFinal()const=0;
    virtual bool isInitial()const=0;
    
    virtual ~ABC_BuildByToken_(){}
    
    virtual void clear()=0;
    
    virtual const StructureEnv_New* parent()const=0;

  };
  


  class ABC_BuildByToken: public ABC_BuildByToken_
  {
  public:

    virtual ~ABC_BuildByToken(){}

    virtual void clear()=0;


    virtual ABC_Data_New* unloadData()=0;

    virtual bool unpopData(ABC_Data_New* data)=0;


  };


  template<class myType> class Type_Union;



  template <class myTypeOfValue>
  std::vector<typename myTypeOfValue::myBuild*>
  getBuildByTokenVector(const StructureEnv_New *cm, const Type_Union<myTypeOfValue>* t);

  template<class myType_of_Value>
  class BuildByToken_Union: public myType_of_Value::myBuild
  {
  public:
    typedef typename myType_of_Value::myBuild   closBuild;

    virtual bool pushToken(Token_New tok
                           , std::string* whyNot
                           , const std::string& masterObjective)
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

    virtual  std::pair<std::string,std::set<std::string>> alternativesNext()const
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

    virtual Token_New popBackToken()
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

    virtual bool isFinal()const
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
    virtual bool isInitial()const
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

    virtual ~BuildByToken_Union(){}

    virtual void clear()
    {
      for (std::size_t i=0; i<vecValue.size(); ++i)
        {
          vecValue[i]->clear();
          nPushedTokensIn[i]=0;

        }
      nPushedTokens=0;
    }

    virtual ABC_Data_New* unloadData()
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

    virtual bool unpopData(ABC_Data_New* data)
    {
      return false;
    }
    BuildByToken_Union(const StructureEnv_New* cm,
                       const Type_Union<myType_of_Value>* t)
      :p_(cm),
        uType_(t),vecValue(getBuildByTokenVector(cm,t)),nPushedTokensIn(),nPushedTokens(0){
      nPushedTokensIn=std::vector<std::size_t>(vecValue.size(),0);
    }

    const StructureEnv_New* parent() const override {return p_;}

  private:
    const StructureEnv_New* p_;
    const Type_Union<myType_of_Value>* uType_;
    std::vector<closBuild*> vecValue;
    std::vector<std::size_t> nPushedTokensIn;
    std::size_t nPushedTokens;
  };




  
  template<typename T,bool isClass=
           !(std::is_arithmetic<T>::value
           || std::is_same<T,std::string>::value)  >
  class buildByToken;
  
  
  




  const Implements_Identifier* getIdentifierType(const ABC_Type_of_Value* t);
  
  template<typename T>
  class buildByToken<T,false>
      :public ABC_BuildByToken
      
  {
  public:
    
    buildByToken(const StructureEnv_New* parent,
                 const Implements_Data_Type_New<T>* typeVar):
      p_(parent),
      varType_(typeVar),
      x_(),
      isComplete_(false)
    {
      
    }
    
    buildByToken()=default;

    T unloadVar()
    {
      auto out=std::move(x_);
      x_= {};
      isComplete_=false;
      return out;
    }
    
    bool pushToken(Token_New t, std::string* whyNot, const std::string& masterObjective)override;
    
    std::pair<std::string,std::set<std::string>> alternativesNext()const override;
    
    
    void clear()override
    {
      x_={};
      isComplete_=false;
    }
    
    virtual void reset_Type(const Implements_Data_Type_New<T>* var)
    {
      clear();
      varType_=var;
    }
    
    bool unPop(T var)
    {
      x_=std::move(var);
      isComplete_=true;
      return true;
    }
    
    
    
    
    
    
    
    Token_New popBackToken() override
    {
      if (isFinal())
        {
          Token_New to(std::move(x_));
          isComplete_=false;
          x_={};
          return to;
        }
      else
        return {};
    }
    
    bool isFinal()const override
    {
      return isComplete_;
    }
    
    bool isInitial()const override
    {
      return !isComplete_;
    }
    
    
    virtual ABC_Data_New* unloadData()override
    {
      return new Implements_Value_New<T>
          (varType_,unloadVar());
    }
    
    virtual bool unpopData(ABC_Data_New* data) override
    {
      auto d=dynamic_cast<Implements_Value_New<T>*>(data);
      if (d!=nullptr)
        {
          varType_=d->myTypeD();
          return unPop(d->unloadValue());
        }
      else return false;
    }
    

    virtual ~buildByToken(){}
    const StructureEnv_New* parent() const override {return p_;}

  private:
    const StructureEnv_New* p_;
    const Implements_Data_Type_New<T>* varType_;
    T x_;
    bool isComplete_;
  };
  
  
  class BuildByTokenString_Union: public buildByToken<std::string>
  {

  public:


    virtual bool pushToken(Token_New tok
                           , std::string* whyNot
                           , const std::string& masterObjective);

    virtual  std::pair<std::string,std::set<std::string>> alternativesNext()const;

    virtual Token_New popBackToken();

    virtual bool isFinal()const;
    virtual bool isInitial()const;

    virtual ~BuildByTokenString_Union();

    virtual void clear();

    virtual ABC_Data_New* unloadData();

    virtual bool unpopData(ABC_Data_New* data);

    BuildByTokenString_Union(const StructureEnv_New* cm,
                             const Identifier_Union* t);

    const StructureEnv_New* parent() const override {return p_;}

  private:
    const StructureEnv_New* p_;
    const Identifier_Union* uType_;
    std::vector<buildByToken<std::string>*> vecValue;
    std::vector<std::size_t> nPushedTokensIn;
    std::size_t nPushedTokens;
  };

  
  
  
  
  
  template<typename... Args>
  class buildByToken<std::tuple<Args...>,true>
      :public ABC_BuildByToken
      
  {
  public:
    typedef std::tuple<Args...> myC;
    
    
    typedef std::tuple<const Implements_Data_Type_New<Args>*...> dataArgumentsTuple;
    
    
    typedef Implements_Data_Type_New<myC>  vType;
    
    enum DFA {
      S_Init, S_Element_Partial, S_Element_Final,S_Mandatory,S_Final};
    
    buildByToken(const StructureEnv_New* paren,
                 const Implements_Data_Type_New<std::tuple<Args...>>* typeVar):
      p_(paren),
      mystate(S_Init),
      varType_(typeVar)
    ,tuVarTypes_(typeVar->getArgumentTypes())
    ,buildTupl_(getBuildTuple(paren,typeVar->getArgumentTypes()
                              ,std::index_sequence_for<Args...>()))
    ,xTupl_()
    ,iArg_(0)
    {
    }
    
    template<std::size_t ...Is>
    static std::tuple<buildByToken<Args>*...> getBuildTuple
    (const StructureEnv_New* parent,
     const std::tuple<const Implements_Data_Type_New<Args>*...>& types
     , const std::index_sequence<Is...> )
    {
      return std::tuple<buildByToken<Args>*...> (
            std::get<Is>(types)->getBuildByToken(parent)...
            );
    }
    
    myC unloadVar()
    {
      if ((iArg_ )< (std::tuple_size<myC>::value))
        varType_->template fill_imp<0>(xTupl_,iArg_,varType_->getArguments());
      auto out=std::move(xTupl_);
      xTupl_= {};
      mystate=S_Init;
      iArg_=0;
      return out;
    }
    
    template<std::size_t D>
    static bool pushToken_imp(const StructureEnv_New* cm,
                              DFA &state,std::size_t &i
                              ,std::tuple<buildByToken<Args>*...>& b
                              ,const dataArgumentsTuple& a
                              ,myC& x
                              ,Token_New t, std::string* whyNot
                              , const std::string& masterObjective)
    {
      return t.tok()==Token_New::EOL;
    }
    
    
    
    template<std::size_t D,std::size_t I, std::size_t...Is>
    static bool pushToken_imp(const StructureEnv_New* cm,
                              DFA &state,std::size_t &i
                              ,std::tuple<buildByToken<Args>*...>& b
                              ,const dataArgumentsTuple& a
                              ,myC& x
                              ,Token_New t, std::string* whyNot
                              , const std::string& masterObjective)
    {
      if (I<i)
        return pushToken_imp<D,Is...>(cm,state,i,b,a,x,t,whyNot,masterObjective);
      else
        {
          typedef typename std::tuple_element<I,myC>::type eType;
          buildByToken<eType>* eB=std::get<I>(b);
          if (!eB->pushToken(t,whyNot,masterObjective))
            {
              return false;
            }
          else if (eB->isFinal())
            {
              std::get<I>(x)=eB->unloadVar();
              ++i;
              if (i==std::tuple_size<myC>::value)
                state=S_Final;
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
                              ,std::tuple<buildByToken<Args>*...>& b
                              ,const dataArgumentsTuple& a
                              ,myC& x
                              ,Token_New t, std::string* whyNot
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
          typedef typename std::tuple_element<I,dataArgumentsTuple>::type aType;
          aType a=std::get<I>(arg);
          if (a==nullptr)
            return isMandatory_imp<D,Is...>(cm,++i,arg);
          else
            return true;

        }
    }



    template<std::size_t ... Is>
    static bool isMandatory_imp(const StructureEnv_New* cm,std::index_sequence<Is...>,std::size_t i
                                ,const dataArgumentsTuple& arg
                                )
    {
      return isMandatory_imp<0,Is...>(cm,i,arg);
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
                               ,varType_->getArguments()
                               ,xTupl_
                               ,t
                               ,whyNot
                               ,objective);
        case    S_Final:
          return false;

        }
    }




    template<std::size_t D>
    static std::pair<std::string,std::set<std::string>> alternativesNext_imp
    (const StructureEnv_New* cm,
     DFA state,std::size_t i
     ,const std::tuple<buildByToken<Args>*...>& b,
     const dataArgumentsTuple& arg)
    {
      return {};
    }



    template<std::size_t D,std::size_t I, std::size_t... Is>
    static std::pair<std::string,std::set<std::string>> alternativesNext_imp
    (const StructureEnv_New* cm,
     DFA state,std::size_t i
     ,const std::tuple<buildByToken<Args>*...>& b,
     const dataArgumentsTuple& arg)
    {
      if (state==S_Final)
        return {};
      if (I<i)
        return alternativesNext_imp<D,Is...>(cm,state,i,b,arg);
      else
        {
          typedef typename std::tuple_element<I,dataArgumentsTuple>::type eType;
          buildByToken<eType>* eB=std::get<I>(b);
          const Implements_Data_Type_New<eType>* v=std::get<I>(arg);
          auto out=eB->alternativesNext();
          std::string id=v->typeId();
          return {id,out.second};
        }
    }

    template<std::size_t... Is>
    static std::pair<std::string,std::set<std::string>> alternativesNext_imp
    (const StructureEnv_New* cm,
     std::index_sequence<Is...>,DFA state,std::size_t i
     ,const std::tuple<buildByToken<Args>*...>& b,
     const dataArgumentsTuple& arg)
    {
      return alternativesNext_imp<0,Is...>(cm,state,i,b,arg);

    }



    std::pair<std::string,std::set<std::string>> alternativesNext()const override
    {
      return alternativesNext_imp<0>
          (parent(),std::index_sequence_for<Args...>(),mystate,iArg_
           ,buildTupl_,
           varType_->getArguments());
    }


    void clear()override
    {
      xTupl_={};
      mystate=S_Init;
      iArg_=0;
    }

    virtual void reset_Type(const Implements_Data_Type_New<myC>* var)
    {
      clear();
      varType_=var;
      buildTupl_=getBuildTuple(parent(),varType_->getArgumentTypes()
                               ,std::index_sequence_for<Args...>());

    }

    bool unPop(myC var)
    {
      xTupl_=std::move(var);
      mystate=S_Final;
      iArg_=std::tuple_size<myC>::value;
      return true;
    }

    template<std::size_t D>
    static Token_New popBackToken_imp(const StructureEnv_New* cm,
                                      DFA &state,std::size_t &i
                                      ,std::tuple<buildByToken<Args>*...>& b
                                      ,const dataArgumentsTuple& a,
                                      myC& x)
    {

      return {};

    }



    template<std::size_t D,std::size_t I,std::size_t... Is>
    static Token_New popBackToken_imp(const StructureEnv_New* cm,
                                      DFA &state
                                      ,std::size_t &i
                                      ,std::tuple<buildByToken<Args>*...>& b
                                      ,const dataArgumentsTuple& a
                                      , myC& x)
    {
      if (I<i)
        return popBackToken_imp<D,Is...>(cm,state,i,b,a,x);
      else {
          typedef typename std::tuple_element<I,myC>::type eType;
          Implements_Fn_Argument<eType> aT=std::get<I>(a);
          if (aT.isDefaulted())
            {
              --i;
              return popBackToken_imp<D,Is...>(cm,state,i,b,a,x);


            }
          else
            {
              buildByToken<eType>* eB=std::get<I>(b);
              Token_New out;
              if (eB->isInitial())
                {
                  eB->unPop(std::get<I>(x));
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
     ,std::tuple<buildByToken<Args>*...>& b
     ,const dataArgumentsTuple& a
     ,myC& x)
    {
      return popBackToken_imp<0,Is...>(cm,state,i,b,a,x);

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
                                   ,varType_->getArguments()
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

    bool hasMandatory()const
    {
      return (mystate==S_Mandatory)
          &&(mystate==S_Final);

    }

    virtual ABC_Data_New* unloadData()override
    {
      return new Implements_Value_New<myC>(varType_,unloadVar());
    }

    virtual bool unpopData(ABC_Data_New* data) override
    {
      auto d=dynamic_cast<Implements_Value_New<myC>*>(data);
      if (d!=nullptr)
        {
          varType_=d->myTypeD();
          return unPop(d->unloadValue());
        }
      else return false;
    }
    buildByToken(){}


    virtual ~buildByToken(){}

    std::size_t iArg()const {return iArg_;}

    const StructureEnv_New* parent() const override {return p_;}

    private:
      const StructureEnv_New* p_;
    DFA mystate;
    const Implements_Data_Type_New<std::tuple<Args...>>* varType_;
    std::tuple<const Implements_Data_Type_New<Args>*...> tuVarTypes_;
    std::tuple<buildByToken<Args>*...> buildTupl_;
    std::tuple<Args...> xTupl_;
    std::size_t iArg_;
  };





  template<typename T>
  std::pair<std::string, std::set<std::string> > buildByToken<T,false>::alternativesNext() const
  {
    std::string whynot;
    std::string id=varType_->typeId();
    return {id,varType_->alternativeNext(parent())};
  }

  template<>
  std::pair<std::string, std::set<std::string> > buildByToken<std::string>::alternativesNext() const;



  template<typename T>
  class buildByToken<std::vector<T>,true>
      :public ABC_BuildByToken
  {
  public:


    enum DAF {S_Init,S_Header2,S_Header_Final,S_Data_Partial,S_Data_Final,S_Final};



    bool isFinal()const override
    {
      return mystate==S_Final;
    }

    bool isInitial()const override
    {
      return mystate==S_Init;
    }



    std::vector<T> unloadVar()
    {
      if (isFinal())
        {
          mystate=S_Init;
          auto o=std::move(idC_);
          idC_={};
          return o;
        }
      else
        return {};
    }

    bool unPop(std::vector<T> var)
    {
      idC_=std::move(var);
      mystate=S_Final;
      return true;
    }

    buildByToken(const StructureEnv_New* parent,
                 const Implements_Data_Type_New<std::vector<T>>* vecType)
      :
        p_(parent),
        varType_(vecType),
        elemType_(vecType->getElementDataType(parent)->clone()),
        valueBuild_(new buildByToken<T>(parent,elemType_)),
        idC_(),
        mystate(S_Init)
    {}


     buildByToken(){}
    ~buildByToken(){
    }

    bool pushToken(Token_New tok, std::string* whyNot,const std::string& masterObjective)
    {
      const std::string objective=masterObjective;
      switch (mystate)
        {
        case S_Init:
          if (tok.tok()!=Token_New::EOL)
            {
              *whyNot=objective+": end of line was expected";
              return false;
            }
          else
            {
              mystate=S_Header2;
              return true;
            }
          break;
        case S_Header2:
          if (tok.tok()!=Token_New::LSB)
            {
              *whyNot=objective+": \"[\" was expected";
              return false;
            }
          else
            {
              mystate=S_Header_Final;
              return true;
            }
          break;
        case S_Header_Final:
        case S_Data_Partial:
          if (!valueBuild_->pushToken(tok, whyNot,objective))
            return false;
          else
            {
              if(valueBuild_->isFinal())
                {
                  idC_.push_back(valueBuild_->unloadVar());
                  mystate=S_Data_Final;
                  return true;
                }
              else
                {
                  mystate=S_Data_Partial;
                  return true;
                }
            }
          break;
        case S_Data_Final:
          {
            if (varType_->hasFixedSize()&&varType_->getSize(parent())==idC_.size())
              {
                if (tok.tok()!=Token_New::RSB)
                  {
                    *whyNot=objective+" ] expected";
                    return false;
                  }
                else
                  {
                    mystate=S_Final;
                    return true;
                  }
              }
            else if (varType_->hasFixedSize())
              {

                if (!valueBuild_->pushToken(tok, whyNot,objective))
                  {
                    return false;
                  }
                else
                  {
                    if(valueBuild_->isFinal())
                      {
                        idC_.push_back(valueBuild_->unloadVar());
                        mystate=S_Data_Final;
                        return true;
                      }
                    else
                      {
                        mystate=S_Data_Partial;
                        return true;
                      }
                  }
              }
            else  if ((tok.tok()==Token_New::RSB)&&varType_->getSize(parent())<=idC_.size())
              {
                mystate=S_Final;
                return true;
              }
            else  if (!valueBuild_->pushToken(tok, whyNot,objective))
              {
                return false;
              }
            else
              {
                if(valueBuild_->isFinal())
                  {
                    idC_.push_back(valueBuild_->unloadVar());
                    mystate=S_Data_Final;
                    return true;
                  }
                else
                  {
                    mystate=S_Data_Partial;
                    return true;
                  }
              }

          }
        case S_Final:
        default:
          return false;
          break;
        }

    }

    Token_New popBackToken() override
    {
      switch (mystate)
        {
        case S_Init:
          return {};
          break;
        case S_Header2:
          mystate=S_Init;
          return Token_New(Token_New::EOL);
          break;
        case S_Header_Final:
          mystate=S_Header2;
          return Token_New(Token_New::LSB);
          break;
        case S_Data_Partial:
          {
            auto out= valueBuild_->popBackToken();
            if (valueBuild_->isInitial())
              {
                if (idC_.empty())
                  mystate=S_Header_Final;
                else
                  mystate=S_Data_Final;
              }
            else mystate=S_Data_Partial;
            return out;
          }
          break;
        case S_Data_Final:
          {
            T d=idC_.back();
            idC_.pop_back();
            valueBuild_->unPop(d);
            auto to=valueBuild_->popBackToken();
            if (valueBuild_->isInitial())
              {
                if (idC_.empty())
                  mystate=S_Header_Final;
                else
                  mystate=S_Data_Final;
              }
            else mystate=S_Data_Partial;
            return to;
          }
          break;
        case S_Final:
          mystate=S_Data_Final;
          return Token_New(Token_New::RSB);
          break;
        default:
          return {};
          break;
        }
    }

    std::pair<std::string,std::set<std::string>> alternativesNext()const
    {
      switch (mystate)
        {
        case S_Init:
          return {"ClassName()",{alternatives::endOfLine()}};
          break;
        case S_Header2:
          return {"ClassName()",{Token_New::toString(Token_New::LSB)}};
        case S_Header_Final:
        case S_Data_Partial:
          return valueBuild_->alternativesNext();
          break;
        case S_Data_Final:
          {
            if (varType_->hasFixedSize()&&varType_->getSize(parent())==idC_.size())
              {
                return {"ClassName()",{Token_New::toString(Token_New::RSB)}};
              }
            else if (varType_->hasFixedSize()||varType_->getSize(parent())>idC_.size())
              {

                return valueBuild_->alternativesNext();
              }
            else
              {
                auto out=valueBuild_->alternativesNext();
                out.second.insert(Token_New::toString(Token_New::RSB));
                return out;

              }

          }
        case S_Final:
        default:
          return {};
          break;
        }

    }

    void clear()override
    {
      mystate=S_Init;
      idC_.clear();
      valueBuild_->clear();

    }

    virtual ABC_Data_New* unloadData()override
    {    return new Implements_Value_New<std::vector<T>>(varType_,unloadVar());

    }

    virtual bool unpopData(ABC_Data_New* data) override
    {

      auto d=dynamic_cast<Implements_Value_New<std::vector<T>>*>(data);
      if (d!=nullptr)
        {
          varType_=d->myTypeD();
          return unPop(d->unloadValue());
        }
      else return false;
    }


    const StructureEnv_New* parent() const override {return p_;}

  private:
    const StructureEnv_New* p_;
    const Implements_Data_Type_New<std::vector<T>> * varType_;
    Implements_Data_Type_New<T>* elemType_;
    buildByToken<T> * valueBuild_;
    std::vector<T> idC_;
    DAF mystate;
  };


  template<typename K, typename T>
  class buildByToken<std::pair<K,T>,true>
      :public ABC_BuildByToken  {

  public:
    typedef std::pair<K,T>  myC;

    enum DAF {S_Init,S_First_Partial,S_First_Final
              ,S_Separator_Final,S_Second_Partial,S_Final} ;




    bool isFinal()const
    {
      return mystate==S_Final;
    }

    bool isInitial()const
    {
      return mystate==S_Init;
    }



    std::pair<K,T> unloadVar()
    {
      if (isFinal())
        {
          mystate=S_Init;
          std::pair<K,T> out=std::move(idC_);
          idC_={};

          return out;
        }
      else
        return {};
    }





    bool unPop(std::pair<K,T> var)
    {
      idC_=var;
      mystate=S_Final;
      return true;

    }

    buildByToken(const StructureEnv_New* parent,
                 const Implements_Data_Type_New<std::pair<K,T>>* typeVar):
      p_(parent),
      mystate(S_Init),
      idC_(),
      first_(typeVar->getKeyDataType(parent)->getBuildByToken(parent))
    ,second_(typeVar->getElementDataType(parent)->getBuildByToken(parent))
    {

    }


    buildByToken(){}

    ~buildByToken(){
    }




    bool pushToken(Token_New tok, std::string* whyNot, const std::string& masterObjective)override

    {
      const std::string objective=masterObjective;
      //+": Token "+tok.str()+ "rejected by class "+ClassName();
      switch (mystate)
        {
        case S_Init:
        case S_First_Partial:
          if (!first_->pushToken(tok, whyNot,objective))
            return false;
          else
            {
              if (first_->isFinal())
                mystate=S_First_Final;
              else
                mystate=S_First_Partial;
              return true;
            }
          break;
        case S_First_Final:
          if (tok.tok()!=Token_New::COLON)
            {
              
              *whyNot=objective+" : as a colon was expected";
              return false;
            }
          else
            {
              mystate=S_Separator_Final;
              return true;
            }
          break;
        case S_Separator_Final:
        case S_Second_Partial:
          if (!second_->pushToken(tok, whyNot,objective))
            {
              return false;
            }
          else
            {
              if(second_->isFinal())
                {
                  idC_.first=first_->unloadVar();
                  idC_.second=second_->unloadVar();
                  mystate=S_Final;
                  return true;
                }
              else
                {
                  mystate=S_Second_Partial;
                  return true;
                }
            }
          break;
        case S_Final:
        default:
          return false;
          break;
        }

    }

    Token_New popBackToken() override
    {
      switch (mystate)
        {
        case S_Init:
          return {};
          break;
        case S_First_Final:
          first_->unPop(idC_.first);
        case S_First_Partial:
          {
            auto out= first_->popBackToken();
            if (first_->isInitial())
              {
                mystate=S_Init;
              }
            else mystate=S_First_Partial;
            return out;
          }
          break;
        case S_Separator_Final:
          return Token_New(Token_New::COLON);
          break;
        case S_Final:
          second_->unPop(idC_.second);
        case S_Second_Partial:
          {
            auto out= first_->popBackToken();
            if (first_->isInitial())
              {
                mystate=S_Init;
              }
            else mystate=S_First_Partial;
            return out;
          }
          break;
        default:
          return {};
          break;
        }
    }

    std::pair<std::string,std::set<std::string>> alternativesNext()const
    {
      switch (mystate)
        {
        case S_Init:
        case S_First_Partial:
          return first_->alternativesNext();
          break;
        case S_First_Final:
          return {"myClass()",{Token_New::toString(Token_New::COLON)}};
        case S_Separator_Final:
        case S_Second_Partial:
          return second_->alternativesNext();
          break;
        case S_Final:
        default:
          return {};
          break;
        }

    }
    void clear()override
    {
      mystate=S_Init;
      first_->clear();
      second_->clear();
    }

    virtual ABC_Data_New* unloadData()override
    {
      return new Implements_Value_New<std::pair<K,T>> (parent()->dataToId(pairType_),unloadVar());
    }

    virtual bool unpopData(ABC_Data_New* data) override
    {
      auto d=dynamic_cast<Implements_Value_New<myC>*>(data);
      if (d!=nullptr)
        {
          pairType_=d->myTypeD();
          return unPop(d->unloadValue());
        }
      else return false;
    }

    const StructureEnv_New* parent() const override {return p_;}

  private:
    const StructureEnv_New* p_;

    DAF mystate;
    std::pair<K,T> idC_;
    buildByToken<K>* first_;
    buildByToken<T>* second_;
    const Implements_Data_Type_New<std::pair<K,T>>* pairType_;
  };






  template<typename T>
  class buildByToken<Markov_LA::M_Matrix<T>,true>
      :public ABC_BuildByToken
  {
  public:

    enum DAF { S_Init
               ,S_PInit_NData,S_PInit_NEOL,S_PInit_NBoth,S_PInit_NFinal
               ,S_PEOL_NData,S_PEOL_NEOL,S_PEOL_NBoth,S_PEOL_NFinal
               ,S_PData_NData,S_PData_NEOL,S_PData_NBoth
               ,S_PBothData_NData,S_PBothData_NEOL,S_PBothData_NBoth
               ,S_PBothEOL_NData,S_PBothEOL_NEOL,S_PBothEOL_NBoth,S_PBothEOL_NFinal
             } ;

    bool isFinal()const override
    {
      return (mystate==S_PInit_NFinal)
          ||(mystate==S_PEOL_NFinal)
          ||(mystate==S_PBothEOL_NFinal);
    }

    bool isInitial()const override
    {
      return mystate==S_Init;
    }

    Markov_LA::M_Matrix<T> unloadVar()
    {
      if (isFinal())
        {
          Markov_LA::M_Matrix<T> out=std::move(x_);
          mystate=S_Init;
          x_={};
          return out;
        }
      else
        return {};
    }


    bool unPop(Markov_LA::M_Matrix<T> var)
    {
      x_=var;
      mystate=S_PEOL_NFinal;
      return true;
    }

    buildByToken(const StructureEnv_New* parent,
                 const _private::Implements_Data_Type_New_M_Matrix<T>* typeVar);

    buildByToken(){}

    virtual ~buildByToken(){
    }

    bool pushToken(Token_New tok, std::string* whyNot, const std::string& masterObjective) override
    {
      const std::string objective=masterObjective;
      //+": "+ClassName()+"::pushToken of "+tok.str()+" fails";

      switch (mystate) {
        case S_Init:
          if (tok.tok()!=Token_New::EOL)
            {
              *whyNot=objective+": not an end of line";
              return false;
            }

          else if ((hasFixedCols_)&&(nCols_==0))
            {
              mystate=S_PInit_NFinal;
              return true;
            }
          else if (nCols_==0)
            {
              mystate=S_PInit_NBoth;
              return true;
            }
          else
            {
              eleType_=dataType_->getElementType
                  (parent(),buffer_,nRows_,nCols_,runRows_,runCols_
                   ,whyNot,masterObjective,eleType_);
              
              mystate=S_PInit_NData;
              return true;
            }

        case S_PInit_NData:
        case S_PEOL_NData:
        case S_PData_NData:
        case S_PBothData_NData:
        case S_PBothEOL_NData:


          if(!eleB_->pushToken(tok,whyNot,masterObjective))
            return false;
          else if (eleB_->isFinal())
            {
              v_=eleB_->unloadVar();
              if (nCols_*runRows_+runCols_<buffer_.size())
                buffer_[nCols_*runRows_+runCols_]=v_;
              else
                buffer_.push_back(v_);
              
              ++runCols_;
              if (hasFixedCols_||(runRows_>0))
                {
                  if (runCols_==nCols_)
                    {
                      mystate=S_PData_NEOL;
                      return true;
                    }
                  else
                    {
                      eleType_=dataType_->getElementType
                          (parent(),buffer_,nRows_,nCols_,runRows_,runCols_
                           ,whyNot,masterObjective,eleType_);
                      eleB_->reset_Type(eleType_);
                      mystate=S_PData_NData;
                      return true;
                    }
                }
              else
                {
                  eleType_=dataType_->getElementType
                      (parent(),buffer_,nRows_,nCols_,runRows_,runCols_
                       ,whyNot,masterObjective,eleType_);
                  eleB_->reset_Type(eleType_);
                  if(runCols_<nCols_)
                    {
                      mystate=S_PData_NData;
                      return true;
                    }
                  else
                    {
                      mystate=S_PData_NBoth;
                      return true;
                    }
                }
              
            }
          else
            {
              mystate=S_PData_NData;
              return true;
            }

        case S_PInit_NEOL:
        case S_PEOL_NEOL:
        case S_PData_NEOL:
        case S_PBothData_NEOL:
        case S_PBothEOL_NEOL:
          if (tok.tok()!=Token_New::EOL)
            {
              *whyNot=masterObjective+": expected end of line";
            }
          else
            {
              ++runRows_;
              runCols_=0;
              
              
              if (hasFixedRows_&&(runRows_==nRows_))
                {
                  x_=Markov_LA::M_Matrix<T>(nRows_,nCols_,buffer_);
                  mystate=S_PEOL_NFinal;
                  return true;
                }
              else
                {
                  eleType_=dataType_->getElementType
                      (parent(),buffer_,nRows_,nCols_,runRows_,runCols_
                       ,whyNot,masterObjective,eleType_);
                  eleB_->reset_Type(eleType_);
                  if (runRows_<nRows_)
                    {
                      mystate=S_PEOL_NData;
                      return true;
                    }
                  else
                    {
                      mystate=S_PEOL_NBoth;
                      return true;
                    }
                }
            }

        case S_PInit_NBoth:
        case S_PEOL_NBoth:
        case S_PData_NBoth:
        case S_PBothData_NBoth:
        case S_PBothEOL_NBoth:
          if(eleB_->pushToken(tok,whyNot,masterObjective))
            {
              if (eleB_->isFinal())
                {
                  v_=eleB_->unloadVar();
                  if (nCols_*runRows_+runCols_<buffer_.size())
                    buffer_[nCols_*runRows_+runCols_]=v_;
                  else
                    buffer_.push_back(v_);
                  ++runCols_;

                  if ((mystate==S_PEOL_NBoth)||(mystate==S_PInit_NBoth))
                    {
                      if (hasFixedCols_||(runRows_>0))
                        {
                          if (runCols_==nCols_)
                            {
                              mystate=S_PBothData_NEOL;
                              return true;
                            }
                          else
                            {
                              eleType_=dataType_->getElementType
                                  (parent(),buffer_,nRows_,nCols_,runRows_,runCols_
                                   ,whyNot,masterObjective,eleType_);
                              eleB_->reset_Type(eleType_);
                              mystate=S_PBothData_NData;
                              return true;
                            }
                        }
                      else
                        {
                          eleType_=dataType_->getElementType
                              (parent(),buffer_,nRows_,nCols_,runRows_,runCols_
                               ,whyNot,masterObjective,eleType_);
                          eleB_->reset_Type(eleType_);
                          if(runCols_<nCols_)
                            {
                              mystate=S_PBothData_NData;
                              return true;
                            }
                          else
                            {
                              mystate=S_PBothData_NBoth;
                              return true;
                            }
                        }
                    }
                  else
                    {
                      mystate=S_PBothData_NBoth;
                      return true;
                    }

                }
              
              else
                {
                  mystate=S_PBothData_NData;
                  return true;
                }
              
            }
          else     if (tok.tok()!=Token_New::EOL)
            {
              *whyNot=masterObjective+": expected data or end of line";
            }
          else if ((mystate==S_PEOL_NBoth)||(mystate==S_PBothEOL_NBoth)||(mystate==S_PInit_NBoth))
            {
              x_=Markov_LA::M_Matrix<T>(runRows_,nCols_,buffer_);
              mystate=S_PBothEOL_NFinal;
              return true;
            }
          else
            {
              if (runRows_==0&&!hasFixedCols_)
                nCols_=runCols_;
              ++runRows_;
              if (!hasFixedRows_)
                nRows_=runRows_;
              runCols_=0;
              if (hasFixedRows_&&(runRows_==nRows_))
                {
                  x_=Markov_LA::M_Matrix<T>(nRows_,nCols_,buffer_);
                  mystate=S_PBothEOL_NFinal;
                  return true;
                }
              else
                {
                  eleType_=dataType_->getElementType
                      (parent(),buffer_,nRows_,nCols_,runRows_,runCols_
                       ,whyNot,masterObjective,eleType_);
                  eleB_->reset_Type(eleType_);
                  if (runRows_<nRows_)
                    {
                      mystate=S_PBothEOL_NData;
                      return true;
                    }
                  else
                    {
                      mystate=S_PBothEOL_NBoth;
                      return true;
                    }
                }
            }
        case S_PEOL_NFinal:
        case S_PBothEOL_NFinal:
        case S_PInit_NFinal:
          return false;
          break;

        }
    }

    Token_New popBackToken()override;

    std::pair<std::string,std::set<std::string>> alternativesNext()const override;

    void clear()override
    {
      isComplete_=false;
      mystate=S_Init;
      x_.clear();
      buffer_.clear();
      hasFixedRows_=false;

    }

    virtual ABC_Data_New* unloadData()override
    {
      return new Implements_Value_New<Markov_LA::M_Matrix<T>> (dataType_,unloadVar());
    }

    virtual bool unpopData(ABC_Data_New* data) override
    {
      auto d=dynamic_cast< Implements_Value_New<Markov_LA::M_Matrix<T>>*>(data);
      if (d!=nullptr)
        {
          dataType_=d->myTypeD();
          return unPop(d->unloadValue());
        }
      else return false;
    }
    const StructureEnv_New* parent() const override {return p_;}

    private:
      const StructureEnv_New* p_;
    DAF mystate;
    const Implements_Data_Type_New<Markov_LA::M_Matrix<T>>* dataType_;
    const Implements_Data_Type_New<T>* eleTypeInit_;
    Implements_Data_Type_New<T>* eleType_;
    buildByToken<T>* eleB_;
    Markov_LA::M_Matrix<T> x_;
    bool hasFixedCols_;
    bool hasFixedRows_;
    std::size_t runCols_;
    std::size_t nCols_;
    std::size_t nCols_Init_;
    std::size_t runRows_;
    std::size_t nRows_;
    std::size_t nRows_Init_;
    T v_;
    std::vector<T> buffer_;
    bool isComplete_;
  };

  template<typename T>
  class buildByToken<std::set<T>,true>
      :public ABC_BuildByToken  {
  public:



    enum DAF {S_Init,S_Header2,S_Header_Final,S_Data_Partial,S_Data_Final,S_Final} ;




    bool isFinal()const
    {
      return mystate==S_Final;
    }


    bool unPop(std::set<T> var)
    {
      idC_=var;
      mystate=S_Final;
      return true;

    }

    bool isInitial()const
    {
      return mystate==S_Header_Final;
    }



    std::set<T> unloadVar()
    {
      if (isFinal())
        {
          mystate=S_Header_Final;
          std::set<T> out=std::move(idC_);
          idC_={};
          return out;
        }
      else
        return {};
    }

    buildByToken(const StructureEnv_New* parent,
                 const Implements_Data_Type_New<std::set<T>>* typeVar):
      p_(parent),
      mystate(S_Header_Final),
      idC_{},
      dataType_(typeVar),
      valueBuild_(typeVar->getElementDataType(parent)->getBuildByToken(parent)){}


    buildByToken(){}

    ~buildByToken(){
    }

    bool pushToken(Token_New tok, std::string* whyNot, const std::string& masterObjective)
    {
      const std::string objective=masterObjective+": "+"::pushToken("+
          tok.str()+") fails";

      switch (mystate)
        {
        case S_Init:
          if (tok.tok()!=Token_New::EOL)
            {
              *whyNot=objective+" is not an end of line";
              return false;
            }  else
            {
              mystate=S_Header2;
              return true;
            }
          break;
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
          break;
        case S_Header_Final:
        case S_Data_Partial:
          if (!valueBuild_->pushToken(tok, whyNot, objective))
            {
              return false;
            }
          else
            {
              if(valueBuild_->isFinal())
                {
                  idC_.insert(valueBuild_->unloadVar());
                  mystate=S_Data_Final;
                  return true;
                }
              else
                {
                  mystate=S_Data_Partial;
                  return true;
                }
            }
          break;
        case S_Data_Final:
          if (tok.tok()==Token_New::RCB)
            {
              mystate=S_Final;
              return true;
            }
          else if (!valueBuild_->pushToken(tok, whyNot,objective))
            {
              return false;
            }
          else
            {
              if(valueBuild_->isFinal())
                {
                  idC_.insert(valueBuild_->unloadVar());
                  mystate=S_Data_Final;
                  return true;
                }
              else
                {
                  mystate=S_Data_Partial;
                  return true;
                }
            }
          break;
        case S_Final:
        default:
          return false;
          break;
        }

    }
    Token_New popBackToken() override
    {
      switch (mystate)
        {
        case S_Init:
          return {};
          break;
        case S_Header2:
          mystate=S_Header_Final;
          return Token_New(Token_New::EOL);
          break;
        case S_Header_Final:
          mystate=S_Header2;
          return Token_New(Token_New::LCB);
          break;
        case S_Data_Partial:
          {
            auto out= valueBuild_->popBackToken();
            if (valueBuild_->isInitial())
              {
                if (idC_.empty())
                  mystate=S_Header_Final;
                else
                  mystate=S_Data_Final;
              }
            else mystate=S_Data_Partial;
            return out;
          }
          break;
        case S_Data_Final:
          {
            T d=*(--idC_.end());
            idC_.erase(--idC_.end());
            valueBuild_->unPop(d);
            auto to=valueBuild_->popBackToken();
            if (valueBuild_->isInitial())
              {
                if (idC_.empty())
                  mystate=S_Header_Final;
                else
                  mystate=S_Data_Final;
              }
            else mystate=S_Data_Partial;
            return to;
          }
          break;
        case S_Final:
          mystate=S_Data_Final;
          return Token_New(Token_New::RCB);
          break;
        default:
          return {};
          break;
        }
    }

    std::pair<std::string,std::set<std::string>> alternativesNext()const
    {
      switch (mystate)
        {
        case S_Init:
          return {"myClass()",{alternatives::endOfLine()}};
          break;
        case S_Header2:
          return {"myClass()",{Token_New::toString(Token_New::LCB)}};
        case S_Header_Final:
        case S_Data_Partial:
          return valueBuild_->alternativesNext();
          break;
        case S_Data_Final:
          {
            auto out=valueBuild_->alternativesNext();
            out.second.insert(Token_New::toString(Token_New::RCB));
            return out;
          }
          break;
        case S_Final:
        default:
          return {};
          break;
        }

    }



    void clear()override
    {
      mystate=S_Init;
      idC_.clear();
      valueBuild_->clear();

    }

    virtual ABC_Data_New* unloadData()override;

    virtual bool unpopData(ABC_Data_New* data) override
    {
      auto d=dynamic_cast<Implements_Value_New<std::set<T>>*>(data);
      if (d!=nullptr)
        {
          dataType_=d->myTypeD();
          return unPop(d->unloadValue());
        }
      else return false;
    }


    const StructureEnv_New* parent() const override {return p_;}

  private:
    const StructureEnv_New* p_;
    DAF mystate;
    std::set<T> idC_;
    const Implements_Data_Type_New<std::set<T>>* dataType_;
    buildByToken<T>* valueBuild_;
  };




  template<typename K, typename T>
  class buildByToken<std::map<K,T>,true>
      :public ABC_BuildByToken

  {
  public:

    enum DAF {S_Init,S_Header2,S_Header_Final,S_First_Partial,S_First_Final,S_Separator_Final,S_Second_Partial,S_Second_Final,S_Data_Final,S_Final} ;



    bool isFinal()const
    {
      return mystate==S_Final;
    }

    bool isInitial()const override
    {
      return mystate==S_Header_Final;
    }


    bool unPop(std::map<K,T> var)
    {
      idC_=var;
      mystate=S_Final;
      return true;

    }

    std::map<K,T> unloadVar()
    {
      if (isFinal())
        {
          mystate=S_Header_Final;
          std::map<K,T> out=std::move(idC_);
          idC_={};
          return out;
        }
      else
        return {};
    }


    buildByToken(const StructureEnv_New* parent,
                 const Implements_Data_Type_New<std::map<K,T>>* typeVar):
      p_(parent),
      mystate(S_Header_Final),
      idC_{},
      varType_(typeVar),
      keyBuild_(typeVar->getKeyType(parent)->getBuildByToken(parent)),
      valBuild_(typeVar->getElementType(parent)->getBuildByToken(parent))
    {}


    buildByToken(){}

    ~buildByToken(){
    }

    bool pushToken(Token_New tok, std::string* whyNot, const std::string& masterObjective) override
    {
      const std::string objective=masterObjective;
      //+" : "+ClassName()+"::pushToken("+tok.str()+")";
      switch (mystate)
        {
        case S_Init:
          if (tok.tok()!=Token_New::EOL)
            {
              *whyNot=objective+": is not end of line";
              return false;
            }
          else
            {
              mystate=S_Header2;
              return true;
            }
          break;
        case S_Header2:
          if (tok.tok()!=Token_New::LCB)
            {
              *whyNot=objective+": is not { ";
              return false;
            }
          else
            {
              mystate=S_Header_Final;
              return true;
            }
          break;
        case S_Header_Final:
        case S_Second_Final:
          if (tok.tok()==Token_New::RCB)
            {
              mystate=S_Final;
              return true;
            }
        case S_First_Partial:
          if (!keyBuild_->pushToken(tok, whyNot,objective))
            return false;
          else
            {
              if (keyBuild_->isFinal())
                mystate=S_First_Final;
              else
                mystate=S_First_Partial;
              return true;
            }
          break;
        case S_First_Final:
          if (tok.tok()!=Token_New::COLON)
            {
              
              *whyNot=objective+" : as a colon was expected";
              return false;
            }
          else
            {
              mystate=S_Separator_Final;
              return true;
            }
          break;
        case S_Separator_Final:
        case S_Second_Partial:
          if (!valBuild_->pushToken(tok, whyNot,objective))
            {
              return false;
            }
          else
            {
              if(valBuild_->isFinal())
                {
                  idC_.insert({keyBuild_->unloadVar(),
                               valBuild_->unloadVar()});
                  mystate=S_Second_Final;
                  return true;
                }
              else
                {
                  mystate=S_Second_Partial;
                  return true;
                }
            }
          break;
        case S_Final:
        default:
          return false;
          break;
        }

    }
    Token_New popBackToken() override
    {
      switch (mystate)
        {
        case S_Init:
          return {};
          break;
        case S_Header2:
          mystate=S_Header_Final;
          return Token_New(Token_New::EOL);
          break;
        case S_Header_Final:
          mystate=S_Header2;
          return Token_New(Token_New::LCB);
          break;

        case S_First_Final:
          keyBuild_->unPop(pair_.first);
        case S_First_Partial:
          {
            auto out= keyBuild_->popBackToken();
            if (keyBuild_->isInitial())
              {
                if (idC_.empty())
                  mystate=S_Header_Final;
                else
                  {
                    mystate=S_First_Partial;
                  }
              }
            else mystate=S_First_Partial;
            return out;
          }
          break;
        case S_Separator_Final:
          keyBuild_->unPop(pair_.first);
          return Token_New(Token_New::COLON);
          break;
        case S_Second_Final:
          {
            auto rit=--idC_.end();
            pair_=*rit;
            idC_.erase(rit);
          }
          valBuild_->unPop(pair_.second);
        case S_Second_Partial:
          {
            auto out= valBuild_->popBackToken();
            if (valBuild_->isInitial())
              {
                mystate=S_Separator_Final;
              }
            else mystate=S_Second_Partial;
            return out;
          }


          break;
        case S_Final:
          mystate=S_Data_Final;
          return Token_New(Token_New::RCB);
          break;
        default:
          return {};
          break;
        }
    }

    std::pair<std::string,std::set<std::string>> alternativesNext()const override
    {
      switch (mystate)
        {
        case S_Init:
          return {"myClass()",{alternatives::endOfLine()}};
          break;
        case S_Header2:
          return {"",{Token_New::toString(Token_New::LCB)}};
        case S_Header_Final:
          return keyBuild_->alternativesNext();
          break;
        case S_Data_Final:
          {
            auto out=keyBuild_->alternativesNext();
            out.second.insert(Token_New::toString(Token_New::RCB));
            return out;
          }
          break;
        case S_Final:
        default:
          return {};
          break;
        }

    }

    void clear()override
    {
      mystate=S_Init;
      idC_.clear();
      keyBuild_->clear();

    }

    virtual ABC_Data_New* unloadData()override
    {
      return new Implements_Value_New<std::map<K,T>
          > (varType_,unloadVar());
    }

    virtual bool unpopData(ABC_Data_New* data) override
    {
      auto d=dynamic_cast<Implements_Value_New<std::map<K,T>>*>(data);
      if (d!=nullptr)
        {
          varType_=d->myTypeD();
          return unPop(d->unloadValue());
        }
      else return false;
    }




    const StructureEnv_New* parent() const override {return p_;}

    private:
      const StructureEnv_New* p_;
    DAF mystate;
    std::pair<K,T> pair_;
    std::map<K,T> idC_;
    const Implements_Data_Type_New<std::map<K,T>>* varType_;
    buildByToken<K>* keyBuild_;
    buildByToken<T>* valBuild_;
  };

  template<>
  class buildByToken<ABC_Data_New*>
      :public ABC_BuildByToken
  {
  public:

    enum DFA {
      S_Init=0,S_ID_Final, S_DATA_PARTIAL, S_Data_Final,S_Final
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

    buildByToken(){}

    ~buildByToken(){}



    ABC_Data_New* unloadVar()
    {
      if (isFinal())
        {
          ABC_Data_New* out;
          mystate=S_Init;
          if (classx_!=nullptr)
            out=classx_.release();
          else
            out= data_.release();
          return out;
        }
      else
        return {};
    }

    bool unPop(ABC_Data_New* var)
    {
      data_.reset(var)  ;
      mystate=S_Final;
      return true;

    }

    buildByToken(const StructureEnv_New* parent,
                 const Implements_Data_Type_New<ABC_Data_New *> *varType);

    void clear()override;

    virtual ABC_Data_New* unloadData()override
    {
      return unloadVar();
    }
    virtual bool unpopData(ABC_Data_New* data) override
    {
      return unPop(data);
    }


    virtual std::pair<std::string, std::set<std::string> > alternativesNext() const override;

    virtual Token_New popBackToken() override;

    virtual void reset_Type(Implements_Data_Type_New<ABC_Data_New*> *dataTy);


    const StructureEnv_New* parent() const override {return p_;}

  private:
    const StructureEnv_New* p_;
    DFA mystate;
    const Implements_Data_Type_New<ABC_Data_New*> * dataType_;
    const Implements_Identifier* idtype_;
    std::string idString_;
    std::unique_ptr<buildByToken<std::string>> idtypeB_;
    std::unique_ptr<ABC_BuildByToken> valueB_;
    const ABC_Type_of_Value* valueType_;
    std::unique_ptr<ABC_Data_New> data_;
    bool convertToClass_;
    std::unique_ptr<ABC_Data_New> classx_;


  };





  template<>
  class buildByToken<Implements_Var>
      :public ABC_BuildByToken
  {
  public:

    enum DFA {
      S_Init=0, TIP1, TIP2,WT0_ID0,WT2,WT3,ID1,ID2,WT1,ID0,
      S_DATA_PARTIAL,
      S_Final
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

    buildByToken(){}

    ~buildByToken(){}



    Implements_Var unloadVar()
    {
      if (isFinal())
        {
          Implements_Var out=iv_;
          iv_={};
          return out;
        }
      else
        return {};
    }

    virtual ABC_Data_New* unloadData()override
    {
      return nullptr;
    }

    virtual bool unpopData(ABC_Data_New* data) override
    {
      return false;
    }


    bool unPop(Implements_Var var)
    {
      iv_=var;
      mystate=S_Final;
      return true;

    }

    buildByToken(const StructureEnv_New* parent,
                 const Implements_Data_Type_New<Implements_Var> *varType);




    void clear()override;


    virtual void reset_Type(Implements_Data_Type_New<Implements_Var> *ivTy);
    const StructureEnv_New* parent() const override {return p_;}

    private:
      const StructureEnv_New* p_;

    DFA mystate;
    const Implements_Data_Type_New<Implements_Var> * ivarType_;
    Implements_Identifier* idType_;
    Implements_Data_Type_New<ABC_Data_New*>* dataTy_;
    std::unique_ptr<buildByToken<std::string>> idB_;
    std::unique_ptr<buildByToken<ABC_Data_New*>> dataB_;
    Implements_Var iv_;

  private:
    bool pushIdToken(Token_New tok, std::string* whyNot,const std::string& masterObjective);



  public:
    virtual std::pair<std::string, std::set<std::string> > alternativesNext() const override

    {
      std::pair<std::string, std::set<std::string> > out;
      switch (mystate)
        {
        case S_Init:
          out.first="Tip";
          out.second={"#"};
          out+=idB_->alternativesNext();
          return out;


        case TIP1:
          out.first="Write a tip";
          out.second={"<Tip>"};
          return out;
        case TIP2:
          out.first="Expected end of line";
          out.second={"\n"};
          return out;
        case WT0_ID0:
          out.first="Whatthis";
          out.second={"#"};
          out+=idB_->alternativesNext();
          return out;


        case WT1:
          out.first="# for Whatthis";
          out.second={"#"};
          [[clang::fallthrough]];
        case WT2:
          out.first="Write an extended description";
          out.second={"<WhatThis>"};
          return out;

        case WT3:
          out.first="Expected end of line";
          out.second={"\n"};
          return out;
        case ID0:
          return  idB_->alternativesNext();

        case ID1:
          out.first=" token \":\"";
          out.second={":"};
          return out;
        case ID2:
        case S_DATA_PARTIAL:
          return dataB_->alternativesNext();
        case S_Final:
          return {};
        }
    }

    virtual Token_New popBackToken() override;
  };




  namespace _private{
    class MyConstIterator;
  }

  template<>
  class buildByToken<StructureEnv_New*,true>
      :public ABC_BuildByToken

  {
  public:


    enum DAF {S_Init
              ,S_Header2
              ,S_Header_Final
              ,S_Data_Partial
              ,S_Data_Separator_Final
              ,S_Mandatory
              ,S_All
              ,S_Final} ;



    bool isFinal()const override
    {
      return mystate==S_Final;
    }

    bool isInitial()const override
    {
      return mystate==S_Init;
    }

    bool unPop(StructureEnv_New* var);

    StructureEnv_New* unloadVar();

    virtual void reset_Type(const Implements_Data_Type_New<StructureEnv_New*>* typeVar);

    buildByToken(const StructureEnv_New* parent,
                 const Implements_Data_Type_New<StructureEnv_New*>* typeVar);


    buildByToken(const StructureEnv_New* parent);

    buildByToken(){}

    ~buildByToken(){
    }

    bool pushToken
    (Token_New tok
     , std::string* whyNot
     , const std::string& masterObjective) override;



    Token_New popBackToken() override;

    std::pair<std::string,std::set<std::string>> alternativesNext()const override;


    void clear()override
    {
      // no se que hace
    }



    virtual ABC_Data_New* unloadData()override;
    virtual bool unpopData(ABC_Data_New* data) override;

    const StructureEnv_New* parent() const override {return p_;}

    private:
      const StructureEnv_New* p_;

    DAF mystate;
    const Implements_Data_Type_New<StructureEnv_New*>* varMapType_;
    StructureEnv_New*  StEnv_;
    Implements_Data_Type_New<Implements_Var>* ivType_;
    buildByToken<Implements_Var>* ivBuild_;
    Implements_Var  iv_;
    std::size_t iField_;
  };





  template<>
  class buildByToken<Markov_CommandManagerVar*,true>
      :public ABC_BuildByToken

  {
  public:


    virtual bool pushToken(Token_New t
                           , std::string* whyNot
                           , const std::string& masterObjective)
    {
      return true;
    }

    virtual  std::pair<std::string,std::set<std::string>> alternativesNext()const
    {
      return {};
    }

    virtual Token_New popBackToken()
    {
      return {};
    }
    virtual bool isFinal()const
    {
      return !empty_;
    }
    virtual bool isInitial()const
    {
      return empty_;
    }
    buildByToken(){}

    virtual ~buildByToken(){}

    virtual void clear()
    {
      empty_=true;
    }


    virtual ABC_Data_New* unloadData();

    Markov_CommandManagerVar* unloadVar()
    {
      return nullptr;
    }

    bool unPop(Markov_CommandManagerVar* cm)
    {
      return true;
    }

    virtual bool unpopData(ABC_Data_New* data)
    {
      return true;
    }



    buildByToken(const StructureEnv_New* cm,
                 const Implements_Data_Type_New<Markov_CommandManagerVar*>*  type):
      p_(cm),empty_(false),type_(type){}


    const StructureEnv_New* parent() const override {return p_;}

    private:
      const StructureEnv_New* p_;
    bool empty_;
    const Implements_Data_Type_New<Markov_CommandManagerVar*>*  type_;
  };





  template<typename T>
  class buildByToken<T,true>: public ABC_BuildByToken
  {
  public:
    enum DFA {
      S_Init=0, S_DATA_PARTIAL, S_Data_Final,S_Final
    } ;


    buildByToken(const StructureEnv_New* parent,
                 const Implements_Data_Type_New<T>* typeVar):
      p_(parent),
      varType_(typeVar),
      bStr_(typeVar->getComplexVarType(parent)->getBuildByToken(parent)),
      idC_(),
      mystate(S_Init)
    {

    }


    T unloadVar()
    {
      if (isFinal())
        {
          auto out=std::move(idC_);
          idC_= {};
          mystate=S_Init;
          return out;
        }
      else return {};
    }

    bool pushToken(Token_New t, std::string* whyNot, const std::string& masterObjective)override
    {
      switch (mystate)
        {
        case S_Init:
        case S_DATA_PARTIAL:
          if (!bStr_->pushToken(t,whyNot,masterObjective))
            return false;
          else
            if (bStr_->isFinal())
              {
                StructureEnv_New* c=bStr_->unloadVar();
                mystate=S_Data_Final;
                if (c!=nullptr)
                  {
                    bool success;
                    idC_=varType_->getClass
                        (parent(),c,success,whyNot, masterObjective);
                    if (!success) return false;
                    else
                      return varType_->isValueInDomain(parent(),idC_,whyNot,masterObjective);


                  }
                else return false;

              }
            else
              {
                mystate=S_DATA_PARTIAL;
                return true;

              }
        case S_Data_Final:
          {
            if (t.tok()!=Token_New::EOL)
              {
                *whyNot=masterObjective+" is not an end of line";
                return false;
              }
            else
              {
                mystate=S_Final;
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
        case S_DATA_PARTIAL:

          return bStr_->alternativesNext();

        case S_Data_Final:
          return {"ClassNamr()",{alternatives::endOfLine()}};

        case S_Final:
          return {};
        }

    }

    void clear()override
    {
      idC_={};
      bStr_->clear();
      mystate=S_Init;
    }

    virtual void reset_Type(const Implements_Data_Type_New<T>* var)
    {
      clear();
      varType_=var;
      bStr_->reset_Type(var->getComplexVarType(parent()));
    }

    bool unPop(T var)
    {
      if (isFinal())
        {
          idC_=std::move(var);
          std::string whyNot;
          StructureEnv_New* c=varType_->getComplexMap(parent(),idC_,&whyNot,"");
          bStr_->unPop(c);
          return true;
        }
      else return false;
    }


    Token_New popBackToken() override
    {
      Token_New out;
      switch (mystate)
        {
        case S_Init:
          return {};
        case S_Data_Final:
        case S_DATA_PARTIAL:
          {
            out= bStr_->popBackToken();
            if (bStr_->isInitial())
              mystate=S_Init;
            else
              mystate=S_DATA_PARTIAL;
            return out;
          }
        case S_Final:
          {
            std::string whyNot;
            StructureEnv_New* c=varType_->getComplexMap(parent(),idC_,&whyNot,"");
            bStr_->unPop(c);
            mystate=S_Data_Final;
            return Token_New(Token_New::EOL);

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


    virtual ABC_Data_New* unloadData()override
    {
      return new Implements_Value_New<T>
          (varType_,unloadVar());
    }

    virtual bool unpopData(ABC_Data_New* data) override
    {
      auto d=dynamic_cast<Implements_Value_New<T>*>(data);
      if (d!=nullptr)
        {
          varType_=d->myTypeD();
          return unPop(d->unloadValue());
        }
      else return false;
    }

    buildByToken(){}

    virtual ~buildByToken(){}
    const StructureEnv_New* parent() const override {return p_;}

    private:
      const StructureEnv_New* p_;
    const Implements_Data_Type_New<T>* varType_;
    buildByToken<StructureEnv_New*>* bStr_;
    T idC_;
    DFA mystate;
  };




  template<typename T>
  class buildByToken<T*,true>: public ABC_BuildByToken
  {
  public:
    enum DFA {
      S_Init=0, S_DATA_PARTIAL, S_Data_Final,S_Identifier_Partial,S_Final,
    } ;


    buildByToken(const StructureEnv_New* parent,
                 const Implements_Data_Type_New<T*>* typeVar):
      p_(parent),
      varType_(typeVar),
      bStr_(typeVar->getComplexVarType(parent)->getBuildByToken(parent)),
      bId_(typeVar->getVarIdType(parent)->getBuildByToken(parent)),
      idC_(),
      id_of_x_(""),
      mystate(S_Init)
    {

    }

    buildByToken(){}

    T* unloadVar()
    {
      if (isFinal())
        {
          auto out=idC_;
          idC_= nullptr;
          mystate=S_Init;
          return out;
        }
      else return {};
    }

    bool pushToken(Token_New t, std::string* whyNot, const std::string& masterObjective)override
    {
      switch (mystate)
        {
        case S_Init:
        case S_Identifier_Partial:
          if (bId_->pushToken(t,whyNot,masterObjective))
            {
              if (bId_->isFinal())
                {
                  id_of_x_=bId_->unloadVar();
                  if (!parent()->getDataFromId(id_of_x_,idC_))
                    return false;
                  else
                    {
                      mystate=S_Final;
                      return true;
                    }
                }
              else
                {
                  mystate=S_Identifier_Partial;
                  return true;
                }
            }
          if (mystate==S_Identifier_Partial)
            return false;
        case S_DATA_PARTIAL:
          if (!bStr_->pushToken(t,whyNot,masterObjective))
            return false;
          else if (bStr_->isFinal())
            {
              StructureEnv_New* c=bStr_->unloadVar();
              mystate=S_Data_Final;
              if (c!=nullptr)
                {
                  idC_=varType_->getClass
                      (parent(),c,whyNot, masterObjective);
                  id_of_x_.clear();
                  return varType_->isValueInDomain(parent(),idC_,whyNot,masterObjective);


                }
              else return false;

            }
          else
            {
              mystate=S_DATA_PARTIAL;
              return true;

            }

        case S_Data_Final:
          {
            if (t.tok()!=Token_New::EOL)
              {
                *whyNot=masterObjective+" is not an end of line";
                return false;
              }
            else
              {
                mystate=S_Final;
                return true;
              }


          }
        case S_Final:
          return false;
        }
    }

    std::pair<std::string,std::set<std::string>> alternativesNext()const override
    {
      std::pair<std::string,std::set<std::string>> out;
      switch (mystate)
        {
        case S_Init:
          out=bId_->alternativesNext();
          out+=bStr_->alternativesNext();
          return out;
        case S_DATA_PARTIAL:
          return bStr_->alternativesNext();

        case S_Identifier_Partial:
          return bId_->alternativesNext();
        case S_Data_Final:
          return {"ClassNamr()",{alternatives::endOfLine()}};

        case S_Final:
          return {};
        }

    }

    void clear()override
    {
      idC_={};
      bStr_->clear();
      bId_->clear();
      id_of_x_.clear();
      mystate=S_Init;
    }

    virtual void reset_Type(const Implements_Data_Type_New<T*>* var)
    {
      clear();
      varType_=var;
      bStr_->reset_Type(var->getComplexVarType(parent()));
      bId_->reset_Type(getIdentifierType(var));
    }

    bool unPop(T* var)
    {
      if (isFinal())
        {
          idC_=var;
          std::string whyNot;
          StructureEnv_New* c=varType_->getComplexMap(parent(),idC_,&whyNot,"");
          bStr_->unPop(c);
          return true;
        }
      else return false;
    }


    Token_New popBackToken() override
    {
      Token_New out;
      switch (mystate)
        {
        case S_Init:
          return {};
        case S_Data_Final:
        case S_DATA_PARTIAL:
          {
            out= bStr_->popBackToken();
            if (bStr_->isInitial())
              mystate=S_Init;
            else
              mystate=S_DATA_PARTIAL;
            return out;
          }
        case S_Identifier_Partial:
          {
            out=bId_->popBackToken();
            if (bId_->isInitial())
              mystate=S_Init;
            else
              mystate=S_Identifier_Partial;
            return out;
          }
        case S_Final:
          {
            if (id_of_x_.empty())
              {
                std::string whyNot;
                StructureEnv_New* c=varType_->getComplexMap(parent(),idC_,&whyNot,"");
                bStr_->unPop(c);
                mystate=S_Data_Final;
                return Token_New(Token_New::EOL);
              }
            else
              {
                bId_->unPop(id_of_x_);
                Token_New out=bId_->popBackToken();
                if (bId_->isInitial())
                  mystate=S_Init;
                else
                  mystate=S_Identifier_Partial;
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


    virtual ABC_Data_New* unloadData()override
    {
      return new Implements_Value_New<T*>
          (varType_,unloadVar());
    }

    virtual bool unpopData(ABC_Data_New* data) override
    {
      if (data->myType()==varType_)
        {
          auto d=dynamic_cast<Implements_Value_New<T*>*>(data);
          return unPop(d->unloadValue());
        }
      else return false;
    }


    virtual ~buildByToken(){}
    const StructureEnv_New* parent() const override {return p_;}

  private:
    const StructureEnv_New* p_;
    const Implements_Data_Type_New<T*>* varType_;
    buildByToken<StructureEnv_New*>* bStr_;
    buildByToken<std::string>* bId_;

    T* idC_;
    std::string id_of_x_;
    DFA mystate;
  };


  template<typename D,class B>
  class buildByTokenD: public buildByToken<B*,true>
  {
  public:
    enum DFA {
      S_Init=0, S_DATA_PARTIAL, S_Data_Final,S_Identifier_Partial, S_Final
    } ;


    buildByTokenD(const StructureEnv_New* parent,
                  const Implements_Data_Type_New<D*>* typeVar):
      buildByToken<B*>(parent,typeVar),
      varType_(typeVar),
      bStr_(typeVar->getComplexVarType(parent)->getBuildByToken(parent)),
      bId_(getIdentifierType(typeVar)->getBuildByToken(parent)),
      idC_(),
      id_of_x_(),
      mystate(S_Init)
    {

    }
buildByTokenD(){}

    D* unloadVar()
    {
      if (isFinal())
        {
          auto out=idC_;
          idC_= nullptr;
          mystate=S_Init;
          return out;
        }
      else return {};
    }

    bool pushToken(Token_New t, std::string* whyNot, const std::string& masterObjective)override
    {
      switch (mystate)
        {
        case S_Init:
        case S_Identifier_Partial:
          if (bId_->pushToken(t,whyNot,masterObjective))
            {
              if (bId_->isFinal())
                {
                  id_of_x_=bId_->unloadVar();
                  if (!this->parent()->getDataFromId(id_of_x_,idC_))
                    return false;
                  else
                    {
                      mystate=S_Final;
                      return true;
                    }
                }
              else
                {
                  mystate=S_Identifier_Partial;
                  return true;
                }
            }
          if (mystate==S_Identifier_Partial)
            return false;
        case S_DATA_PARTIAL:
          if (!bStr_->pushToken(t,whyNot,masterObjective))
            return false;
          else
            if (bStr_->isFinal())
              {
                StructureEnv_New* c=bStr_->unloadVar();
                mystate=S_Data_Final;
                if (c!=nullptr)
                  {
                    idC_=varType_->getClass
                        (this->parent(),c,whyNot, masterObjective);
                    return varType_->isValueInDomain(
                          this->parent(),idC_,whyNot,masterObjective);


                  }
                else return false;

              }
            else
              {
                mystate=S_DATA_PARTIAL;
                return true;

              }
        case S_Data_Final:
          {
            if (t.tok()!=Token_New::EOL)
              {
                *whyNot=masterObjective+" is not an end of line";
                return false;
              }
            else
              {
                mystate=S_Final;
                return true;
              }


          }
        case S_Final:
          return false;
        }
    }

    std::pair<std::string,std::set<std::string>> alternativesNext()const override
    {
      std::pair<std::string,std::set<std::string>> out;
      switch (mystate)
        {
        case S_Init:
          out=bId_->alternativesNext();
          out+=bStr_->alternativesNext();
          return out;
        case S_DATA_PARTIAL:
          return bStr_->alternativesNext();

        case S_Identifier_Partial:
          return bId_->alternativesNext();
        case S_Data_Final:
          return {"ClassNamr()",{alternatives::endOfLine()}};

        case S_Final:
          return {};
        }

    }

    void clear()override
    {
      idC_={};
      bStr_->clear();
      bId_->clear();
      mystate=S_Init;
    }

    virtual void reset_Type(const Implements_Data_Type_New<D*>* var)
    {
      clear();
      varType_=var;
      bStr_->reset_Type(var->getComplexVarType(this->parent()));
      bId_->reset_Type(var->getVarIdType(this->parent()));

    }

    bool unPop(D* var)
    {
      if (isFinal())
        {
          idC_=var;
          std::string whyNot;
          StructureEnv_New* c=varType_->getComplexMap(this->parent(),idC_,&whyNot,"");
          bStr_->unPop(c);
          return true;
        }
      else return false;
    }


    Token_New popBackToken() override
    {
      Token_New out;
      switch (mystate)
        {
        case S_Init:
          return {};
        case S_Data_Final:
        case S_DATA_PARTIAL:
          {
            out= bStr_->popBackToken();
            if (bStr_->isInitial())
              mystate=S_Init;
            else
              mystate=S_DATA_PARTIAL;
            return out;
          }
        case S_Identifier_Partial:
          {
            out=bId_->popBackToken();
            if (bId_->isInitial())
              mystate=S_Init;
            else
              mystate=S_Identifier_Partial;
            return out;
          }
        case S_Final:
          {
            if (id_of_x_.empty())
              {
                std::string whyNot;
                StructureEnv_New* c=varType_->getComplexMap(this->parent(),idC_,&whyNot,"");
                bStr_->unPop(c);
                mystate=S_Data_Final;
                return Token_New(Token_New::EOL);
              }
            else
              {
                bId_->unPop(id_of_x_);
                Token_New out=bId_->popBackToken();
                if (bId_->isInitial())
                  mystate=S_Init;
                else
                  mystate=S_Identifier_Partial;
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


    virtual ABC_Data_New* unloadData()override
    {
      return new Implements_Value_New<D*>
          (varType_,unloadVar());
    }

    virtual bool unpopData(ABC_Data_New* data) override
    {
      if (data->myType()==varType_)
        {
          auto d=dynamic_cast<Implements_Value_New<D*>*>(data);
          return unPop(d->unloadValue());
        }
      else return false;
    }


    virtual ~buildByTokenD(){}
    const StructureEnv_New* parent() const override {return p_;}

    private:
      const StructureEnv_New* p_;
    const Implements_Data_Type_New<D*>* varType_;
    buildByToken<StructureEnv_New*>* bStr_;
    buildByToken<std::string>* bId_;
    D* idC_;
    std::string id_of_x_;
    DFA mystate;
  };






  class build_Argument_Input: public buildByToken<Implements_Var>
  {
  public:
    using buildByToken<Implements_Var>::buildByToken;

  };


  template<>
  class buildByToken<Implements_Command_Arguments*>
      :public buildByToken<StructureEnv_New*> {
  public:
    using
    buildByToken<StructureEnv_New*>::buildByToken;
    buildByToken(){}

    ~buildByToken(){}
  };


  class build_Command_Input
      :public buildByToken<Implements_Command_Arguments*>//public buildByToken<Implements_Command_Fields*>
  {
    // ABC_BuildByToken interface
  public:

    virtual bool pushToken(Token_New t, std::string* whyNot, const std::string& masterObjective) override;


    std::pair<std::string,std::set<std::string>> alternativesNext()const override;


    virtual Token_New popBackToken()override;

    virtual bool isFinal() const override
    {
      return mystate==S_Final;
    }
    virtual bool isInitial() const override
    {
      return mystate==S_Init;
    }

    // ABClass_buildByToken interface
    build_Command_Input
    (const StructureEnv_New *cm
     ,const Implements_Command_Type_New *vCmd);



    virtual Implements_Command_Arguments* unloadVar()
    {
      if (isFinal())
        {
          Implements_Command_Arguments* out=cmdArg_;
          cmdArg_=nullptr;
          return out;
        }
      else
        return nullptr;

    }

    void clear()override
    {

    }

    virtual bool unPop(Implements_Command_Arguments*  var)
    {
      cmdArg_=var;


    }


    enum DFA {
      S_Init=0,
      S_Argument_Partial,
      S_Input_Partial,
      S_Mandatory_Final,
      S_Input_Final,
      S_Final
    } ;


    std::pair<std::string,std::set<std::string>> inputAlternativeNext()const;

    virtual void reset_Type(const Implements_Command_Type_New* cmdty);


    const StructureEnv_New* parent() const override {return p_;}

    private:
      const StructureEnv_New* p_;

    DFA mystate;
    const Implements_Command_Type_New* cmdty_;
    Implements_Command_Arguments* cmdArg_;
    Implements_Var iv_;
    Implements_Data_Type_New<Implements_Var> * ivType_;

    build_Argument_Input* ivB_;
    std::size_t iArg_;


  };









  /*!
           * \brief The build_Statement class
           * decide if it is either command, variable declaration, initialization or asignation
           */

  class build_Statement
      :public ABC_BuildByToken
  {
  public:
    enum DFA {
      S_Init,
      S_Command_Id_Partial,
      S_Command_Partial,
      S_Command_Final,
      S_Expression_Partial,
      S_Expression_Final,
    } ;


    build_Statement(Markov_CommandManagerVar *p);

    build_Statement(
        Markov_CommandManagerVar* p,
        const Implements_Data_Type_New<Implements_Var> *varType
        ,const Implements_Data_Type_New<std::string> *idCmd
        ,bool convertToClass);


    virtual ~build_Statement(){}

    void clear()override;

    ABC_Data_New* unloadData()override {return nullptr;}

    virtual bool unpopData(ABC_Data_New* data) override
    {
      return false;
    }

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
      return mystate==S_Command_Final
          || mystate==S_Command_Final
          || mystate==S_Command_Partial;
    }
    bool isVar()const
    {
      return mystate==S_Expression_Final
          || mystate==S_Expression_Partial;

    }


    Implements_Command_Arguments* unloadCommandArguments()
    {
      if (isFinal())
        return cmv_;
      else return nullptr;
    }



    bool  unPop(ABC_Data_New* var)
    {
      return false;
    }






    Token_New popBackToken()override;



    bool isFinal()const override
    {
      return mystate==S_Expression_Final
          || mystate==S_Command_Final;

    }

    bool isInitial()const override
    {
      return mystate==S_Init;
    }






    const StructureEnv_New* parent() const override {return p_;}

    private:
      const StructureEnv_New* p_;

    DFA mystate;
    buildByToken<Implements_Var>*   v_;
    buildByToken<std::string>* idCmd_;
    std::string idC_;

    const Implements_Command_Type_New* cmdTy_;
    build_Command_Input* c_;

    Implements_Command_Arguments* cmv_;
    Implements_Var x_;

    // ABC_BuildByToken interface
  public:
    virtual bool pushToken(Token_New t, std::string *whyNot, const std::string &masterObjective) override;
    virtual std::pair<std::string, std::set<std::string> > alternativesNext() const override

    {
      std::pair<std::string,std::set<std::string>> out;
      switch (mystate)
        {
        case S_Init:
          out=idCmd_->alternativesNext();
          out+=v_->alternativesNext();
          return out;
        case S_Command_Id_Partial:
          return idCmd_->alternativesNext();
        case S_Command_Partial:
          return c_->alternativesNext();
        case S_Expression_Partial:
          return v_->alternativesNext();
        case S_Command_Final:
        case S_Expression_Final:
          return {};

        }

    }

  };






};



//#include "Markov_IO/Implements_ComplexVar_New.h"





namespace Markov_IO_New_Test{


  using namespace Markov_IO_New;

  void test();





}



#endif // BUILDBYTOKEN


