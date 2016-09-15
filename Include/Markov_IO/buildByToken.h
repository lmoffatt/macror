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


#include "Markov_IO/Token_New.h"
#include "Markov_IO/ABC_Var.h"
#include "Markov_Console/ABC_Command.h"
#include "Markov_IO/Validator.h"
#include <string>



namespace Markov_IO {



  class ABC_BuildByToken: public ABC_Base
  {
  public:
    enum MODE {DECLARATION,ASIGNATION,INITIALIZATION, UNDEFINED};

    static std::string ClassName();

    static std::set<std::string> SuperClasses();

    std::string myClass()const override;

    std::set<std::string> mySuperClasses()const override;

    MODE mode()const
    {
      return mode_;
    }

    void setDeclaration()
    {
      mode_=DECLARATION;
    }
    void setInitialization()
    {
      mode_=INITIALIZATION;
    }
    void setAssignation()
    {
      mode_=ASIGNATION;
    }

    bool isDeclaration()const
    {
      return mode_==DECLARATION;
    }

    bool isAssignation()const
    {
      return mode_==ASIGNATION;
    }
    bool isInitialization()const
    {
      return mode_==INITIALIZATION;
    }


    virtual bool pushToken(Token_New t, std::string& errorMessage)=0;
    std::string errorMessage()const;
    virtual  std::pair<std::string,std::set<std::string>> alternativesNext(Markov_Console::Markov_CommandManagerVar* cm)const=0;
    virtual Token_New popBackToken()=0;
    virtual bool isFinal()const=0;
    virtual bool isInitial()const=0;
    virtual bool isHollow()const=0;



    virtual ~ABC_BuildByToken();

    virtual void clear()
    {
      error_.clear();
    }

    const ABC_Value* parent()const;
  protected:
    MODE mode_=UNDEFINED;
    ABC_BuildByToken(const ABC_Value* p);
    std::string getErrorMessage  (std::string err);

    std::string getErrorMessage  (ABC_BuildByToken* child);

    std::string getErrorMessage  (Token_New::Value expected, Token_New found);
    std::string getErrorMessage  (std::string expected, Token_New found);
    std::string getErrorMessage  (const Markov_Console::ABC_CommandVar *cmd, const std::string &error);
    std::string getErrorMessage  (const Markov_Console::ABC_CommandVar *cmd
                                  , const ABC_Value *input, const std::string &error);

    std::string setErrorsMessage(std::vector<Token_New::Value> expected, Token_New found);


    void clearErrorMessage();

    virtual std::string getErrorMessage  (const Markov_Console::ABC_CommandVar *cmd, const ABC_Value *input, Token_New found);


  private:

    const ABC_Value* parent_;
    std::string error_;


  };

  template<typename C>
  class ABClass_buildByToken: public ABC_BuildByToken
  {
  public:
    static std::string ClassName()
    {
      return "ABC_BuildByToken_"+Cls<C>::name();
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Base::SuperClasses()+ClassName();
    }

    std::string myClass()const override
    {
      return ClassName();

    }

    std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }


    virtual C unloadVar()=0;

    virtual bool unPop(C var)=0;
    virtual ~ABClass_buildByToken(){}
  protected:
    ABClass_buildByToken(const ABC_Value* p):ABC_BuildByToken(p){}

  };

  class ABC_Value_ByToken:public ABClass_buildByToken<ABC_Value*>
  {
  protected:
    ABC_Value_ByToken(const ABC_Value* p):ABClass_buildByToken<ABC_Value*>(p){}

  public:

    static std::string ClassName()
    {
      return "ABC_Value_ByToken";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Base::SuperClasses()+ClassName();
    }

    std::string myClass()const override
    {
      return ClassName();

    }

    std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }

    virtual ~ABC_Value_ByToken(){}
    virtual void clear()=0;


  };







  template<typename C>
  class buildByToken: public ABClass_buildByToken<C>
  {
  public:

    static std::string ClassName()
    {
      return "build_"+Cls<C>::name();
    }

    static std::set<std::string> SuperClasses()
    {
      return ABClass_buildByToken<C>::SuperClasses()+ClassName();
    }

    std::string myClass()const override
    {
      return ClassName();

    }

    std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }


    buildByToken(const ABC_Value* parent):
      ABClass_buildByToken<C>(parent),
      x_(),
      isComplete_(false),
      varType_("")
    {
      ABC_BuildByToken::mode_=ABC_BuildByToken::INITIALIZATION;

    }

    buildByToken(const ABC_Value* parent,const std::string vartype):
      ABClass_buildByToken<C>(parent),
      x_(),
      isComplete_(false),
      varType_(vartype)
    {
      ABC_BuildByToken::mode_=ABC_BuildByToken::INITIALIZATION;

    }


    C unloadVar()override
    {
      auto out=std::move(x_);
      x_= {};
      isComplete_=false;
      ABC_BuildByToken::mode_=ABC_BuildByToken::UNDEFINED;
      return out;
    }

    bool pushToken(Token_New t, std::string& errorMessage)override
    {
      C d;
      if (!t.toValue(d))
        {
          errorMessage=t.str()+ " is not a "+Cls<C>::name();
        }
      else  if (ABClass_buildByToken<C>::parent()!=nullptr)
        {
          if (ABClass_buildByToken<C>::parent()->checkValue(varType_,d,errorMessage))
            {
              x_=d;
              isComplete_=true;
              return true;
            }
          else return false;
        }
      else
        {
          errorMessage=myClass()+" has no parent variable";
        }
    }



    std::pair<std::string,std::set<std::string>> alternativesNext(Markov_Console::Markov_CommandManagerVar* cm)const override
    {
      if (ABClass_buildByToken<C>::parent()!=nullptr)
        {
          auto a=ABClass_buildByToken<C>::parent()->idToValue(varType_)->alternativeValues();
          return {varType_,a};
        }
      else
        {
          return {varType_,{Implements_Simple_Value<C>::ClassName()}};
        }
    }


    void clear()override
    {
      ABC_BuildByToken::clear();
      isComplete_=false;
    }

    bool unPop(C var) override
    {
      x_=var;
      isComplete_=true;
      return true;
    }

    Token_New popBackToken() override
    {
      if (isFinal())
        {
          Token_New to(x_);
          isComplete_=false;
          return to;
        }
      else
        return {};
    }

    bool isFinal()const
    {
      return isComplete_;
    }

    bool isInitial()const override
    {
      return !isComplete_;
    }

    virtual bool isHollow()const override
    {
      return !isComplete_;
    }


  protected:
    C x_;
    bool isComplete_;
    std::string varType_;

  };








  template<typename T>
  class buildByToken<std::vector<T> >
      :public ABClass_buildByToken<std::vector<T>>
  {
  public:

    static std::string ClassName()
    {
      return "Build_vector_of_"+Cls<T>::name();
    }

    static std::set<std::string> SuperClasses()
    {
      return ABClass_buildByToken<std::vector<T>>::SuperClasses()+ClassName();
    }

    std::string myClass()const override
    {
      return ClassName();

    }

    std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }



    enum DAF {S_Init,S_Header2,S_Header_Final,S_Data_Partial,S_Data_Final,S_Final} ;


    void setVar(std::vector<T> var)
    {
      x_=var;
    }

    bool isFinal()const override
    {
      return mystate==S_Final;
    }

    bool isInitial()const override
    {
      return mystate==S_Init;
    }
    virtual bool isHollow()const override
    {
      switch (mystate) {
        case S_Init:
        case S_Header2:
        case S_Header_Final:
          return true;
          break;
        case S_Data_Partial:
        case S_Data_Final:
        case S_Final:
        default:
          return false;
        }
    }



    std::vector<T> unloadVar()
    {
      if (isFinal())
        {
          mystate=S_Init;
          return x_;
        }
      else
        return {};
    }

    bool unPop(std::vector<T> var)
    {
      x_=var;
      mystate=S_Final;
      return true;

    }

    buildByToken(const ABC_Value* parent):
      ABClass_buildByToken<std::vector<T>>(parent),
      mystate(S_Init),
      x_{},
      myChildState(parent){
      ABC_BuildByToken::mode_=ABC_BuildByToken::INITIALIZATION;

    }


    buildByToken(ABC_Value* parent,std::vector<T> v):
      ABClass_buildByToken<std::vector<T>>(parent),
      mystate(S_Init),
      x_{v},
      myChildState{parent}{}



    ~buildByToken(){
    }

    bool pushToken(Token_New tok, std::string& errorMessage)
    {
      switch (mystate)
        {
        case S_Init:
          if (tok.tok()!=Token_New::EOL)
            {
              errorMessage= ABC_BuildByToken:: ABC_BuildByToken::getErrorMessage   ("end of line",tok);
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
              errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::LSB,tok);
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
          if (!myChildState.pushToken(tok, errorMessage))
            {
              return false;
            }
          else
            {
              if(myChildState.isFinal())
                {
                  x_.push_back(myChildState.unloadVar());
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
          if (tok.tok()==Token_New::RSB)
            {
              mystate=S_Final;
              return true;
            }
          else if (!myChildState.pushToken(tok, errorMessage))
            {
              return false;
            }
          else
            {
              if(myChildState.isFinal())
                {
                  x_.push_back(myChildState.unloadVar());
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

    Token_New popBackToken()
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
            auto out= myChildState.popBackToken();
            if (myChildState.isInitial())
              {
                if (x_.empty())
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
            T d=x_.back();
            x_.pop_back();
            myChildState.unPop(d);
            auto to=myChildState.popBackToken();
            if (myChildState.isInitial())
              {
                if (x_.empty())
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

    std::pair<std::string,std::set<std::string>> alternativesNext(Markov_Console::Markov_CommandManagerVar* cm)const
    {
      switch (mystate)
        {
        case S_Init:
          return {myClass(),{Token_New::toString(Token_New::EOL)}};
          break;
        case S_Header2:
          return {myClass(),{Token_New::toString(Token_New::LSB)}};
        case S_Header_Final:
        case S_Data_Partial:
          return myChildState.alternativesNext(cm);
          break;
        case S_Data_Final:
          {
            auto out=myChildState.alternativesNext(cm);
            out.second.insert(Token_New::toString(Token_New::RSB));
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
      ABC_BuildByToken::clear();
      mystate=S_Init;
      x_.clear();
      myChildState.clear();

    }

  private:
    DAF mystate;
    std::vector<T> x_;
    buildByToken<T> myChildState;
    //   bool isComplete_;
  };


  template<typename K, typename T>
  class buildByToken<std::pair<K,T> >
      :public ABClass_buildByToken<std::pair<K,T>>
  {
  public:

    static std::string ClassName()
    {
      return "Build_pair_"+Cls<K>::name()+"_"+Cls<T>::name();
    }

    static std::set<std::string> SuperClasses()
    {
      return ABClass_buildByToken<std::pair<K,T>>::SuperClasses()+ClassName();
    }

    std::string myClass()const override
    {
      return ClassName();

    }

    std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }



    enum DAF {S_Init,S_First_Partial,S_First_Final,S_Separator_Final,S_Second_Partial,S_Final} ;


    void setVar(std::pair<K,T> var)
    {
      x_=var;
    }

    bool isFinal()const
    {
      return mystate==S_Final;
    }

    bool isInitial()const
    {
      return mystate==S_Init;
    }

    virtual bool isHollow()const override
    {
      switch (mystate) {
        case S_Init:
          return true;
          break;
        case S_First_Partial:
        case S_First_Final:
        case S_Separator_Final:
        case S_Second_Partial:
        case S_Final:
        default:
          return false;
        }
    }


    std::pair<K,T> unloadVar()
    {
      if (isFinal())
        {
          mystate=S_Init;
          return x_;
        }
      else
        return {};
    }

    bool unPop(std::pair<K,T> var) override
    {
      x_=var;
      mystate=S_Final;
      return true;

    }

    buildByToken(const ABC_Value* parent):
      ABClass_buildByToken<std::pair<K,T>>(parent),
      mystate(S_Init),
      x_{}
    ,first_(parent)
    ,second_(parent){
      ABC_BuildByToken::mode_=ABC_BuildByToken::INITIALIZATION;

    }


    buildByToken(ABC_Value* parent,std::pair<K,T> v):
      ABClass_buildByToken<std::pair<K,T>>(parent),
      mystate(S_Init),
      x_{}
    ,first_(parent)
    ,second_(parent){}



    ~buildByToken(){
    }

    bool pushToken(Token_New tok, std::string& errorMessage)
    {
      switch (mystate)
        {
        case S_Init:
        case S_First_Partial:
          if (!first_.pushToken(tok, errorMessage))
            {
              errorMessage= ABC_BuildByToken::getErrorMessage(errorMessage);
              return false;
            }
          else
            {
              if (first_.isFinal())
                mystate=S_First_Final;
              else
                mystate=S_First_Partial;
              return true;
            }
          break;
        case S_First_Final:
          if (tok.tok()!=Token_New::COLON)
            {
              errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::COLON, tok);
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
          if (!second_.pushToken(tok, errorMessage))
            {
              errorMessage= ABC_BuildByToken::getErrorMessage(errorMessage);
              return false;
            }
          else
            {
              if(second_.isFinal())
                {
                  x_.first=first_.unloadVar();
                  x_.second=second_.unloadVar();
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

    Token_New popBackToken()
    {
      switch (mystate)
        {
        case S_Init:
          return {};
          break;
        case S_First_Final:
          first_.unPop(x_.first);
        case S_First_Partial:
          {
            auto out= first_.popBackToken();
            if (first_.isInitial())
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
          second_.unPop(x_.second);
        case S_Second_Partial:
          {
            auto out= first_.popBackToken();
            if (first_.isInitial())
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

    std::pair<std::string,std::set<std::string>> alternativesNext(Markov_Console::Markov_CommandManagerVar* cm)const
    {
      switch (mystate)
        {
        case S_Init:
        case S_First_Partial:
          return first_.alternativesNext(cm);
          break;
        case S_First_Final:
          return {myClass(),{Token_New::toString(Token_New::COLON)}};
        case S_Separator_Final:
        case S_Second_Partial:
          return second_.alternativesNext(cm);
          break;
        case S_Final:
        default:
          return {};
          break;
        }

    }
    void clear()override
    {
      ABC_BuildByToken::clear();
      mystate=S_Init;
      first_.clear();
      second_.clear();
    }

  private:
    DAF mystate;
    std::pair<K,T> x_;
    buildByToken<K> first_;
    buildByToken<T> second_;

  };


  template<typename T>
  class buildByToken<Markov_LA::M_Matrix<T> >
      :public ABClass_buildByToken<Markov_LA::M_Matrix<T>>
  {
  public:

    static std::string ClassName()
    {
      return "Build_Matrix_of_"+Cls<T>::name();
    }

    static std::set<std::string> SuperClasses()
    {
      return ABClass_buildByToken<Markov_LA::M_Matrix<T>>::SuperClasses()+ClassName();
    }

    std::string myClass()const override
    {
      return ClassName();

    }

    std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }




    enum DAF {S_Init,S_Header_Final,S_Data_Partial,S_Data_Final,S_Final} ;


    void setVar(Markov_LA::M_Matrix<T> var)
    {
      x_=var;
    }

    bool isFinal()const override
    {
      return mystate==S_Final;
    }

    bool isInitial()const override
    {
      return mystate==S_Init;
    }

    virtual bool isHollow()const override
    {
      switch (mystate) {
        case S_Init:
        case S_Header_Final:
          return true;
          break;
        case S_Data_Partial:
        case S_Final:
        default:
          return false;
        }
    }



    Markov_LA::M_Matrix<T> unloadVar() override
    {
      if (isFinal())
        {
          mystate=S_Init;
          return x_;
        }
      else
        return {};
    }

    bool unPop(Markov_LA::M_Matrix<T> var) override
    {
      x_=var;
      mystate=S_Final;
      return true;
    }

    buildByToken(const ABC_Value* parent):
      ABClass_buildByToken<Markov_LA::M_Matrix<T>>(parent),
      mystate(S_Init),
      x_{}{
      ABC_BuildByToken::mode_=ABC_BuildByToken::INITIALIZATION;

    }


    buildByToken(ABC_Value* parent,Markov_LA::M_Matrix<T> v):
      ABClass_buildByToken<Markov_LA::M_Matrix<T>>(parent),
      mystate(S_Init),
      x_{v}{}



    ~buildByToken(){
    }

    bool pushToken(Token_New tok, std::string& errorMessage)
    {

      switch (mystate) {
        case S_Init:
          if (tok.tok()!=Token_New::EOL)
            {
              errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::EOL, tok);
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
          if (tok.tok()==Token_New::EOL)
            {
              if ((nCols_==0))
                {
                  nCols_=runCols_;
                  runCols_=0;
                  if (nCols_>0)
                    {
                      ++runRows_;
                      if (runRows_==nRows_)
                        {
                          x_=Markov_LA::M_Matrix<T>(nRows_,nCols_,buffer_);
                          mystate=S_Final;
                          return true;
                        }
                      else
                        {
                          mystate=S_Data_Partial;
                          return true;
                        }
                    }
                  else if (nRows_==0)
                    {
                      x_=Markov_LA::M_Matrix<T>(nRows_,nCols_,buffer_);
                      mystate=S_Final;
                      return true;
                    }
                  else
                    {
                      errorMessage= ABC_BuildByToken::getErrorMessage   (
                            "Error in matrix. nrows="+std::to_string(nRows_)
                            +"  nCols="+std::to_string(nCols_));
                      return false;
                    }

                }
              else if (nCols_==runCols_)
                {
                  runCols_=0;
                  ++runRows_;
                  if (runRows_==nRows_)
                    {
                      x_=Markov_LA::M_Matrix<T>(nRows_,nCols_,buffer_);
                      mystate=S_Final;
                      return true;
                    }
                  else
                    {
                      mystate=S_Data_Partial;
                      return true;
                    }

                }
              else if (runCols_==0)
                {
                  if ((nRows_==0)||(nRows_==runRows_))
                    {
                      nRows_=runRows_;
                      x_=Markov_LA::M_Matrix<T>(nRows_,nCols_,buffer_);
                      mystate=S_Final;
                      return true;
                    }
                  else
                    {
                      errorMessage= ABC_BuildByToken::getErrorMessage   (
                            "Error in matrix. nrows="+std::to_string(nRows_)
                            +"  nCols="+std::to_string(nCols_));
                      return false;
                    }}
              else  {
                  errorMessage= ABC_BuildByToken::getErrorMessage   (
                        "Error in matrix. nrows="+std::to_string(nRows_)
                        +"  nCols="+std::to_string(nCols_));
                  return false;
                }}

          else if (getValue(tok,v_,errorMessage))
            {
              if ((nCols_==0)||(runCols_<nCols_))
                {
                  if (hasFixedSize_)
                    buffer_[nCols_*runRows_+runCols_]=v_;
                  else
                    buffer_.push_back(v_);
                  ++runCols_;
                  mystate=S_Data_Partial;
                  return true;
                }
              else
                {
                  errorMessage= ABC_BuildByToken::getErrorMessage   (
                        "Error in matrix. nrows="+std::to_string(nRows_)
                        +"  nCols="+std::to_string(nCols_)
                        + "  running cols"+std::to_string(runCols_));
                  return false;
                }
            }
          else
            return false;
          break;
        case S_Final:
        default:
          return false;
          break;

        }
    }

    Token_New popBackToken()
    {

      if (mystate==S_Final)
        {
          buffer_.resize(nCols_*nRows_);
          for (std::size_t i=0; i<nRows_; ++i)
            for (std::size_t j=0; j<nCols_; ++j)
              buffer_[nCols_*i+j]=x_(i,j);
          mystate=S_Header_Final;
          runCols_=0;
          runRows_=nRows_;
          if (!hasFixedSize_) nRows_=0;
          return Token_New(Token_New::EOL);
        }
      else if (mystate==S_Header_Final)
        {
          if (runCols_==0)
            {
              if (runRows_==0)
                {
                  mystate=S_Init;
                  return Token_New(Token_New::EOL);
                }
              else
                {
                  --runRows_;
                  runCols_=nCols_;
                  if (!hasFixedSize_&&(runRows_==1))
                    nCols_=0;
                  return Token_New(Token_New::EOL);
                }
            }
          else
            {
              --runCols_;
              if (hasFixedSize_)
                v_=buffer_[nCols_*runRows_+runCols_];
              else
                {
                  v_=buffer_.back();
                  buffer_.pop_back();
                }
              return Token_New(v_);
            }

        }
      else return {};
    }

    std::pair<std::string,std::set<std::string>> alternativesNext(Markov_Console::Markov_CommandManagerVar* cm)const
    {
      switch (mystate)
        {
        case S_Init:
          return {myClass(),{Token_New::toString(Token_New::EOL)
                    ,Implements_Simple_Value<T>::ClassName()}};
          break;
        case S_Header_Final:
          if (!hasFixedSize_&&((nCols_==0)||(runCols_==0)))
            return {myClass(),{Token_New::toString(Token_New::EOL)
                      ,Implements_Simple_Value<T>::ClassName()}};
          else if ((runCols_==nCols_)||(hasFixedSize_&&(runRows_==nRows_)))
            return {myClass(),{Token_New::toString(Token_New::EOL)}};
          else
            return {myClass(),{Implements_Simple_Value<T>::ClassName()}};
          break;
        case S_Final:
        default:
          return {};
          break;
        }

    }

    void clear()override
    {
      ABC_BuildByToken::clear();
      isComplete_=false;
      mystate=S_Init;
      x_.clear();
      buffer_.clear();
      hasFixedSize_=false;

    }
  private:
    bool getValue(Token_New tok, T& v,std::string& errorMessage);
    DAF mystate;
    Markov_LA::M_Matrix<T> x_;
    T v_;
    std::size_t runCols_;
    std::size_t nCols_;
    std::size_t runRows_;
    std::size_t nRows_;
    bool hasFixedSize_;

    std::vector<T> buffer_;
    bool isComplete_;
  };

  template<>
  inline bool Markov_IO::buildByToken<Markov_LA::M_Matrix<double> >::getValue(
      Token_New tok, double &v,std::string& errorMessage)
  {
    if (tok.isReal())
      {
        v=tok.realValue();
        return true;
      }
    else
      {
        errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::REAL, tok);
        return false;
      }
  }

  template<>
  inline  bool Markov_IO::buildByToken<Markov_LA::M_Matrix<std::size_t> >::getValue(
      Token_New tok, std::size_t &v, std::string& errorMessage)
  {
    if (tok.isCount())
      {
        v=tok.count();
        return true;
      }
    else
      {
        errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::UNSIGNED, tok);
        return false;
      }  }

  template<>
  inline bool Markov_IO::buildByToken<Markov_LA::M_Matrix<int> >::getValue(
      Token_New tok, int &v, std::string& errorMessage)
  {
    if (tok.isInteger())
      {
        v=tok.intval();
        return true;
      }
    else
      {
        errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::INTEGER, tok);
        return false;
      }
  }





  template<typename T>
  class buildByToken<std::set<T>>
      :public ABClass_buildByToken<std::set<T>>

  {
  public:

    static std::string ClassName()
    {
      return "Build_set";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABClass_buildByToken<std::set<T>>::SuperClasses()+ClassName();
    }

    std::string myClass()const override
    {
      return ClassName();

    }

    std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }



    enum DAF {S_Init,S_Header2,S_Header_Final,S_Data_Partial,S_Data_Final,S_Final} ;


    void setVar(std::set<T> var)
    {
      x_=var;
    }

    bool isFinal()const
    {
      return mystate==S_Final;
    }


    bool unPop(std::set<T> var)
    {
      x_=var;
      mystate=S_Final;
      return true;

    }

    bool isInitial()const
    {
      return mystate==S_Header_Final;
    }

    virtual bool isHollow()const override
    {
      switch (mystate) {
        case S_Init:
        case S_Header2:
        case S_Header_Final:
          return true;
          break;
        case S_Data_Partial:
        case S_Data_Final:
        case S_Final:
        default:
          return false;
        }
    }


    std::set<T> unloadVar()
    {
      if (isFinal())
        {
          mystate=S_Header_Final;
          return x_;
        }
      else
        return {};
    }

    buildByToken(const ABC_Value* parent):
      ABClass_buildByToken<std::set<T>>(parent),
      mystate(S_Header_Final),
      x_{},
      myChildState(parent){}


    buildByToken(ABC_Value* parent,std::set<T> v):
      ABClass_buildByToken<std::set<T>>(parent),
      mystate(S_Header_Final),
      x_{v},
      myChildState{parent}{}



    ~buildByToken(){
    }

    bool pushToken(Token_New tok, std::string& errorMessage)
    {
      switch (mystate)
        {
        case S_Init:
          if (tok.tok()!=Token_New::EOL)
            {
              errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::EOL, tok);
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
              errorMessage=ABC_BuildByToken:: ABC_BuildByToken::getErrorMessage   (Token_New::LCB, tok);
              return false;
            }   else
            {
              mystate=S_Header_Final;
              return true;
            }
          break;
        case S_Header_Final:
        case S_Data_Partial:
          if (!myChildState.pushToken(tok, errorMessage))
            {
              return false;
            }
          else
            {
              if(myChildState.isFinal())
                {
                  x_.insert(myChildState.unloadVar());
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
          else if (!myChildState.pushToken(tok, errorMessage))
            {
              return false;
            }
          else
            {
              if(myChildState.isFinal())
                {
                  x_.insert(myChildState.unloadVar());
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
    Token_New popBackToken()
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
            auto out= myChildState.popBackToken();
            if (myChildState.isInitial())
              {
                if (x_.empty())
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
            T d=*(--x_.end());
            x_.erase(--x_.end());
            myChildState.unPop(d);
            auto to=myChildState.popBackToken();
            if (myChildState.isInitial())
              {
                if (x_.empty())
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

    std::pair<std::string,std::set<std::string>> alternativesNext(Markov_Console::Markov_CommandManagerVar* cm)const
    {
      switch (mystate)
        {
        case S_Init:
          return {myClass(),{Token_New::toString(Token_New::EOL)}};
          break;
        case S_Header2:
          return {myClass(),{Token_New::toString(Token_New::LCB)}};
        case S_Header_Final:
        case S_Data_Partial:
          return myChildState.alternativesNext(cm);
          break;
        case S_Data_Final:
          {
            auto out=myChildState.alternativesNext(cm);
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
      ABC_BuildByToken::clear();
      mystate=S_Init;
      x_.clear();
      myChildState.clear();

    }

  private:
    DAF mystate;
    std::set<T> x_;
    buildByToken<T> myChildState;
  };


  template<typename K, typename T>
  class buildByToken<std::map<K,T>>
      :public ABClass_buildByToken<std::map<K,T>>

  {
  public:


    static std::string ClassName()
    {
      return "Build_pair";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABClass_buildByToken<std::map<K,T>>::SuperClasses()+ClassName();
    }

    std::string myClass()const override
    {
      return ClassName();

    }

    std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }


    enum DAF {S_Init,S_Header2,S_Header_Final,S_Data_Partial,S_Data_Final,S_Final} ;


    void setVar(std::map<K,T> var)
    {
      x_=var;
    }

    bool isFinal()const
    {
      return mystate==S_Final;
    }

    bool isInitial()const override
    {
      return mystate==S_Header_Final;
    }


    virtual bool isHollow()const override
    {
      switch (mystate) {
        case S_Init:
        case S_Header2:
        case S_Header_Final:
          return true;
          break;
        case S_Data_Partial:
        case S_Data_Final:
        case S_Final:
        default:
          return false;
        }
    }


    bool unPop(std::map<K,T> var)override
    {
      x_=var;
      mystate=S_Final;
      return true;

    }

    std::map<K,T> unloadVar() override
    {
      if (isFinal())
        {
          mystate=S_Header_Final;
          return x_;
        }
      else
        return {};
    }

    buildByToken(const ABC_Value* parent):
      ABClass_buildByToken<std::map<K,T>>(parent),
      mystate(S_Header_Final),
      x_{},
      myChildState{parent}{
      ABC_BuildByToken::mode_=ABC_BuildByToken::INITIALIZATION;

    }


    buildByToken(ABC_Value* parent,std::map<K,T> v):
      ABClass_buildByToken<std::map<K,T>>(parent),
      mystate(S_Header_Final),
      x_{v},
      myChildState{parent}{}



    ~buildByToken(){
    }

    bool pushToken(Token_New tok, std::string& errorMessage) override
    {
      switch (mystate)
        {
        case S_Init:
          if (tok.tok()!=Token_New::EOL)
            {
              errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::EOL,tok);
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
              errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::LCB,tok);
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
          if (!myChildState.pushToken(tok, errorMessage))
            {
              return false;
            }
          else
            {
              if(myChildState.isFinal())
                {
                  x_.insert(myChildState.unloadVar());
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
          else if (!myChildState.pushToken(tok, errorMessage))
            {
              return false;
            }
          else
            {
              if(myChildState.isFinal())
                {
                  x_.insert(myChildState.unloadVar());
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
            auto out= myChildState.popBackToken();
            if (myChildState.isInitial())
              {
                if (x_.empty())
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
            std::pair<K,T> d=*(--x_.end());
            x_.erase(--x_.end());
            myChildState.unPop(d);
            auto to=myChildState.popBackToken();
            if (myChildState.isInitial())
              {
                if (x_.empty())
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

    std::pair<std::string,std::set<std::string>> alternativesNext(Markov_Console::Markov_CommandManagerVar* cm)const override
    {
      switch (mystate)
        {
        case S_Init:
          return {myClass(),{Token_New::toString(Token_New::EOL)}};
          break;
        case S_Header2:
          return {myClass(),{Token_New::toString(Token_New::LCB)}};
        case S_Header_Final:
        case S_Data_Partial:
          return myChildState.alternativesNext(cm);
          break;
        case S_Data_Final:
          {
            auto out=myChildState.alternativesNext(cm);
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
      ABC_BuildByToken::clear();
      mystate=S_Init;
      x_.clear();
      myChildState.clear();

    }

  private:
    DAF mystate;
    std::map<K,T> x_;
    buildByToken<std::pair<K,T>> myChildState;
  };

  class build_Implements_ValueId
      :public ABC_Value_ByToken

  {

  public:
    static std::string ClassName();

    static std::set<std::string> SuperClasses();

    std::string myClass()const override;

    std::set<std::string> mySuperClasses()const override;

    enum DFA {
      S_Init=0, TIP1, TIP2,WT0_ID0,WT2,WT3,ID1,ID2,WT1,ID0,S_Final
    } ;

    build_Implements_ValueId(const ABC_Value* p);


    void setId(Implements_ValueId* id);


    Implements_ValueId* unloadVar() override;

    void clear()override;

    bool pushToken(Token_New t, std::string& errorMessage) override;

    virtual bool  unPop(ABC_Value* var) override;


    std::pair<std::string,std::set<std::string>> alternativesNext(Markov_Console::Markov_CommandManagerVar* cm)const override;


    Token_New popBackToken() override;



    bool isFinal()const override;
    bool isInitial()const override;

    virtual bool isHollow()const override;

    ~build_Implements_ValueId();


  private:
    bool pushToken_Id(Token_New t, std::string& errorMessage);
    bool pushToken_tip(Token_New t, std::string &errorMessage);
    bool pushToken_whatthis(Token_New t, std::string &errorMessage);
    bool pushToken_var(Token_New t, std::string &errorMessage);
    std::pair<std::string,std::set<std::string>> alternativesNext_var()const ;


    Implements_ValueId* id_;
    DFA idstate;
    std::string varType_;
    // setter<buildByToken<C>,C>  set_;

  };



  class build_Implements_Refer_Var
      :public build_Implements_ValueId
  {
  public:


    static std::string ClassName()
    {
      return "build_Implements_Refer_Var";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Value_ByToken::SuperClasses()+ClassName();
    }

    std::string myClass()const override
    {
      return ClassName();

    }

    enum DFA {
      S_Init,S_ID_Partial,S_ID_Final,S_Header2,S_Header_Final,S_Data_Final,S_Final
    } ;




    build_Implements_Refer_Var(const ABC_Value* p):
      build_Implements_ValueId(p),
      mystate(S_Init),
      x_(new Implements_Refer_Var){
      setId(x_);
    }

    build_Implements_Refer_Var(const ABC_Value* p,Implements_ValueId* id):
      build_Implements_ValueId(p)
    ,mystate(S_ID_Final)
    ,x_(new Implements_Refer_Var(*id))
    {
      setId(x_);
    }

    void clear()override
    {
      ABClass_buildByToken::clear();
      delete x_;
      mystate=S_Init;
      x_=new Implements_Refer_Var;
      setId(x_);
    }


    Implements_Refer_Var * unloadVar()
    {
      if (isFinal())
        {
          auto out=x_;
          mystate=S_Init;
          x_=new Implements_Refer_Var;
          setId(x_);
          return out;
        }
      else return nullptr;
    }

    bool  unPop(ABC_Value* var)override
    {
      if (var->complyClass(Implements_Refer_Var::ClassName()))
        {
          mystate=S_Final;
          if (x_!=var)
            {
              delete x_;
              x_=dynamic_cast<Implements_Refer_Var*>(var);
            }
          return true;
        }
      else return false;
    }

    bool pushToken(Token_New t, std::string& errorMessage)
    {
      switch (mystate)
        {
        case S_Init:
        case S_ID_Partial:
          if (!build_Implements_ValueId::pushToken(t,errorMessage))
            {
              return false;
            }
          else if (build_Implements_ValueId::isFinal())
            {
              mystate=S_ID_Final;
            }
          else
            {
              mystate=S_ID_Partial;
            }
          return true;
          break;
        case S_ID_Final:
          if (t.tok()==Token_New::ASSIGN)
            {
              mystate=S_Header2;
              return true;
            }
          else
            {
              std::string e="Error in reference construction. Expected assign ""="" found: ";
              errorMessage= ABC_BuildByToken::getErrorMessage   (e+t.str());
              return false;
            }
          break;
        case S_Header2:
          if (t.tok()==Token_New::MUL)
            {
              mystate=S_Header_Final;
              return true;
            }
          else
            {
              errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::MUL,t);
              return false;
            } break;

        case S_Header_Final:
          if (t.tok()==Token_New::IDENTIFIER)
            {
              x_->setRefId(t.str());
              mystate=S_Data_Final;
              return true;
            }
          else
            {
              errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::IDENTIFIER,t);
              return false;
            }
          break;
        case S_Data_Final:
          if (t.tok()==Token_New::EOL)
            {
              mystate=S_Final;
              return true;
            }
          else
            {
              errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::EOL,t);
              return false;
            }
          break;
        case S_Final:
        default:
          return false;
          break;
        }
    }

    std::pair<std::string,std::set<std::string>> alternativesNext(Markov_Console::Markov_CommandManagerVar* cm)const
    {
      switch (mystate)
        {

        case S_Init:
        case S_ID_Partial:
          return build_Implements_ValueId::alternativesNext(cm);
          break;
        case S_ID_Final:
          return {myClass(),{Token_New::toString(Token_New::ASSIGN)}};
          break;
        case S_Header2:
          return {myClass(),{Token_New::toString(Token_New::MUL)}};
          break;
        case S_Header_Final:
          return {myClass(),{"variable_identifier"}};
          break;
        case S_Data_Final:
          return {myClass(),{Token_New::toString(Token_New::EOL)}};
          break;
        case S_Final:
        default:
          return{};
          break;
        }
    }


    Token_New popBackToken()
    {
      switch (mystate)
        {
        case S_Init:
          return {};
          break;
        case S_ID_Partial:
        case S_ID_Final:
          {
            auto out=build_Implements_ValueId::popBackToken();
            if (build_Implements_ValueId::isInitial())
              mystate=S_Init;
            else
              mystate=S_ID_Partial;
            return out;
          }
        case S_Header2:
          mystate=S_ID_Final;
          return Token_New(Token_New::ASSIGN);

        case S_Header_Final:
          mystate=S_Header2;
          return Token_New(Token_New::MUL);
          break;
        case S_Data_Final:
          {
            mystate=S_Header_Final;
            return Token_New(x_->refId());
          }
          break;
        case S_Final:
          {
            mystate=S_Data_Final;
            return Token_New(Token_New::EOL);
          }
          break;
        default:
          return{};
          break;
        }
    }




    bool isFinal()const
    {
      return mystate==S_Final;
    }
    bool isInitial()const
    {
      return mystate==S_Init;
    }

    bool isHollow()const
    {
      switch (mystate) {
        case S_Init:
        case S_ID_Partial:
        case S_ID_Final:
        case S_Header2:
        case S_Header_Final:
          return true;
        case S_Data_Final:
        case S_Final:
        default:
          return false;
        }
    }

    ~build_Implements_Refer_Var(){}


  private:
    DFA mystate;
    Implements_Refer_Var* x_;
  };



  template<typename T>
  class build_Implements_Simple_Value
      :public build_Implements_ValueId

  {
  public:

    static std::string ClassName()
    {
      std::string out="build_Simple_";
      return out+buildByToken<T>::ClassName();
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Value_ByToken::SuperClasses()+ClassName();
    }

    std::string myClass()const override
    {
      return ClassName();

    }


    enum DFA {
      S_Init,S_ID_Partial,S_ID_Final,S_Header_Final,S_Data_Partial,S_Data_Final,S_Final
    } ;




    build_Implements_Simple_Value(const ABC_Value* parent):
      build_Implements_ValueId(parent)
    ,mystate(S_Init)
    ,x_(new Implements_Simple_Value<T>)
    ,data_(parent){
      setId(x_);
    }

    build_Implements_Simple_Value(const ABC_Value* parent,
                                  Implements_ValueId* id):
      build_Implements_ValueId(parent)
    ,mystate(S_ID_Final)
    ,x_(new Implements_Simple_Value<T>(*id))
    ,data_(parent){
      setId(x_);
    }




    Implements_Simple_Value<T> * unloadVar()
    {
      auto out=x_;
      ABC_BuildByToken::clear();
      mystate=S_Init;
      x_=new Implements_Simple_Value<T>;
      return out;
    }

    bool  unPop(ABC_Value* var)
    {
      if (var->complyClass(Implements_Simple_Value<T>::ClassName()))
        {
          mystate=S_Final;
          delete x_;
          x_=dynamic_cast<Implements_Simple_Value<T>* >(var);
          setId(x_);
          return x_!=nullptr;
        }
      else return false;

    }

    bool pushToken(Token_New t, std::string& errorMessage)
    {
      switch (mystate)
        {
        case S_Init:
        case S_ID_Partial:
          if (!build_Implements_ValueId::pushToken(t, errorMessage))
            {
              return false;
            }
          else if (build_Implements_ValueId::isFinal())
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
          if (t.tok()==Token_New::ASSIGN)
            {
              mystate=S_Header_Final;
              return true;
            }
          else
            {
              errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::ASSIGN,t);
              return false;
            }
          break;
        case S_Header_Final:
        case S_Data_Partial:
          if (!data_.pushToken(t, errorMessage))
            {
              errorMessage=ABClass_buildByToken::getErrorMessage(errorMessage);
              return false;
            }
          else if (data_.isFinal())
            {
              x_->setValue(data_.unloadVar());
              mystate=S_Data_Final;
              return true;
            }
          else
            {
              mystate=S_Data_Partial;
              return true;
            }
          break;
        case S_Data_Final:
          if (t.tok()==Token_New::EOL)
            {
              mystate=S_Final;
              return true;
            }
          else
            {
              errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::EOL,t);
              return false;
            }
          break;
        case S_Final:
        default:
          return false;
          break;

        }

    }

    std::pair<std::string,std::set<std::string>> alternativesNext(Markov_Console::Markov_CommandManagerVar* cm)const
    {
      switch (mystate)
        {
        case S_Init:
        case S_ID_Partial:
          return build_Implements_ValueId::alternativesNext(cm);
          break;
        case S_ID_Final:
          return {myClass(),{Token_New::toString(Token_New::ASSIGN)}};
          break;
        case S_Header_Final:
        case S_Data_Partial:
          return data_.alternativesNext(cm);
          break;
        case S_Data_Final:
          return {myClass(),{Token_New::toString(Token_New::EOL)}};
          break;
        case S_Final:
        default:
          return {};
        }
    }


    Token_New popBackToken()
    {
      switch (mystate)
        {
        case S_Init:
          return {};
          break;
        case S_ID_Partial:
        case S_ID_Final:
          {
            auto out=build_Implements_ValueId::popBackToken();
            if (build_Implements_ValueId::isInitial())
              mystate=S_Init;
            else
              mystate=S_ID_Partial;
            return out;
          }
        case S_Header_Final:
          mystate=S_ID_Final;
          return Token_New(Token_New::ASSIGN);

        case S_Data_Partial:
          {
            auto out=data_.popBackToken();
            if (!data_.isInitial())
              mystate=S_Data_Partial;
            else
              mystate=S_Header_Final;
            return out;

          }
          break;
        case S_Data_Final:
          {
            data_.unPop(x_->value());
            auto out=data_.popBackToken();
            if (!data_.isInitial())
              mystate=S_Data_Partial;
            else
              mystate=S_Header_Final;
            return out;
          }

        case S_Final:
          mystate=S_Data_Final;
          return Token_New(Token_New::EOL);
          break;
        default:
          return{};
          break;
        }
    }




    bool isFinal()const
    {
      return mystate==S_Final;
    }
    bool isInitial()const
    {
      return mystate==S_Init;
    }


    bool isHollow()const override
    {
      switch (mystate) {
        case    S_Init:
        case     S_ID_Partial:
        case     S_ID_Final:
        case     S_Header_Final:
          return true;
          break;
        case     S_Data_Partial:
          return data_.isHollow();
        case     S_Data_Final:
        case     S_Final:
        default:
          return false;
        }
    }


  private:
    DFA mystate;
    Implements_ValueId id_;
    Implements_Simple_Value<T>* x_;
    buildByToken<T> data_;
    // setter<buildByToken<C>,C>  set_;
  };




  /*!
           * \brief The build_ABC_Value class
           *  sets the grammar of the command line
           *
           */

  class build_ABC_Value
      :public ABC_Value_ByToken
  {
  public:

    static std::string ClassName();

    static std::set<std::string> SuperClasses();

    std::string myClass()const override;


    enum DFA {
      S_Init,


      S_ID_Partial,
      S_ID_Final,

      S_Var_Partial,
      S_Final,
      S_NOT_Complex_Und,
      S_SimpMult_Und,
      S_Vec_Und,
      S_Set_or_Map,
      S_Set_or_Map2,
      S_Map_Und
    } ;




    build_ABC_Value(const ABC_Var* p);


    void clear()override;


    ABC_Value* unloadVar() override;

    bool  unPop(ABC_Value* var);


    bool pushToken(Token_New t, std::string& errorMessage);



    std::pair<std::string,std::set<std::string>> alternativesNext(Markov_Console::Markov_CommandManagerVar* cm)const;


    Token_New popBackToken();



    bool isFinal()const;

    bool isInitial()const;

    virtual bool isHollow()const;



    static build_Implements_ValueId *createBuild_Value(const ABC_Value *parent, ABC_Value *var);
  private:
    DFA mystate;
    ABC_Value* x_;
    build_Implements_ValueId   id_;
    build_Implements_ValueId* var_;


    Token_New previousTok_;
    std::vector<Token_New> prevTokens_;

    static std::vector<Token_New> definingState(build_Implements_ValueId* var,
                                                DFA &mystate);




    // buffer
    // setter<buildByToken<C>,C>  set_;
  };



  class build_Command_Input
      :public ABC_Value_ByToken
  {


    // ABC_BuildByToken interface
  public:
    virtual bool pushToken(Token_New t, std::string& errorMessage);

    std::pair<std::string,std::set<std::string>> alternativesNext(Markov_Console::Markov_CommandManagerVar* cm_)const;


    virtual Token_New popBackToken();
    virtual bool isFinal() const
    {
      return mystate==S_Final;
    }
    virtual bool isInitial() const
    {
      return mystate==S_Init;
    }
    virtual bool isHollow() const
    {

    }

    // ABClass_buildByToken interface
    build_Command_Input(Markov_Console::Markov_CommandManagerVar* cm_);


  public:
    virtual Markov_Console::ABC_CommandVar * unloadVar() override;

    void clear()override;

    virtual bool unPop(ABC_Value * var)override;

    virtual const Markov_Console::ABC_CommandVar* command()const
    {
      return cmd_;
    }
    virtual  Markov_Console::ABC_CommandVar* command()
    {
      return cmd_;
    }


    enum DFA {
      S_Init=0,
      S_ID_Final,
      S_Input_Partial,
      S_Mandatory_Final,
      S_Input_Final,
      S_Final
    } ;

    static bool hasAllInputs(const Markov_Console::ABC_CommandVar *v);
    static bool hasAllMandatoryInputs(const Markov_Console::ABC_CommandVar* cmd);


    bool processVariableInput(Token_New input);

    std::pair<std::string,std::set<std::string>> inputAlternativeNext()const;

    static bool hasNoInput(const ABC_Value *v);
    static bool hasNoOptionalInput(Markov_Console::ABC_CommandVar *cmd, const ABC_Value *v);
    static  Token_New popLastInput(ABC_Value *v);
    static ABC_Value *nextInput(Markov_Console::ABC_CommandVar *v, std::size_t& iInputField);
  private:
    const Markov_Console::Markov_CommandManagerVar* cm_;
    DFA mystate;
    Markov_Console::ABC_CommandVar* cmd_;
    mutable std::size_t iInputField_=0;

    // ABC_Base interface
  public:

    static std::string ClassName();

    static std::set<std::string> SuperClasses();

    virtual std::string myClass() const override;
    virtual std::set<std::string> mySuperClasses() const override;

  };



  /*!
           * \brief The build_Statement class
           * decide if it is either command, variable declaration, initialization or asignation
           */

  class build_Statement
      :public ABC_Value_ByToken
  {
  public:

    static std::string ClassName()
    {
      return "build_Statement";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Value_ByToken::SuperClasses()+ClassName();
    }

    std::string myClass()const override
    {
      return ClassName();

    }


    enum DFA {
      S_Init,
      S_Command_Partial,
      S_Command_Final,
      S_Expression_Partial,
      S_Expression_Final,
    } ;




    build_Statement(Markov_Console::Markov_CommandManagerVar* p);


    void clear()override
    {
      ABClass_buildByToken::clear();
      delete cmv_;
      v_.clear();
      c_.clear();
      mystate=S_Init;
      x_=nullptr;
      cmv_=nullptr;

    }

    ABC_Value* unloadVar()
    {
      if (mystate==S_Command_Final)
        {

          auto out=x_;
          mystate=S_Init;
          x_=nullptr;
          cmv_=nullptr;

          return out;
        }
      else
        {
          //         errorMessage=ABClass_buildByToken::ABC_BuildByToken::getErrorMessage  ("cannot unload beacause it is not in final state");

          return nullptr;

        }
    }

    bool isCommand()const
    {
      return mystate==S_Command_Final
          || mystate==S_Command_Partial;
    }
    bool isVar()const
    {
      return mystate==S_Expression_Final
          || mystate==S_Expression_Partial;

    }


    Markov_Console::ABC_CommandVar* unloadCommand()
    {
      if (mystate==S_Command_Final)
        {
          auto out=cmv_;
          mystate=S_Init;
          x_=nullptr;
          cmv_=nullptr;

          return out;
        }
      else
        {
          return nullptr;
          ABClass_buildByToken::ABC_BuildByToken::getErrorMessage  (cmv_,"cannot unload because it is not in final state");
        }
    }

    bool  unPop(ABC_Value* var)
    {
      return false;
    }


    bool pushToken(Token_New t, std::string& errorMessage);



    std::pair<std::string,std::set<std::string>>   alternativesNext(Markov_Console::Markov_CommandManagerVar* cm)const;


    Token_New popBackToken();



    bool isFinal()const
    {
      return mystate==S_Expression_Final
          || mystate==S_Command_Final;

    }

    bool isInitial()const
    {
      return mystate==S_Init;
    }

    virtual bool isHollow()const
    {
      switch (mystate) {
        case       S_Init:
        case     S_Command_Partial:
        case     S_Expression_Partial:
          return true;
        case     S_Command_Final:
        case     S_Expression_Final:

        default:
          return false;

        }
    }






    static build_Implements_ValueId *createBuild_Value(ABC_Value *var);
  private:
    DFA mystate;
    ABC_Value* x_;
    Markov_Console::ABC_CommandVar *cmv_;

    build_ABC_Value   v_;
    build_Command_Input c_;


  };







  class build_Implements_Complex_Value
      :public build_Implements_ValueId

  {
  public:

    static std::string ClassName()
    {
      return "build_Implements_Complex_Value";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Value_ByToken::SuperClasses()+ClassName();
    }

    std::string myClass()const override
    {
      return ClassName();

    }


    enum DFA {
      S_Init=0,
      S_ID_Partial,
      S_ID_Final,
      S_Header_2,
      S_Header_Final,
      S_Field_Partial,
      S_Field_Final,
      S_END_2,
      S_END_Final,
      S_Final
    } ;





    build_Implements_Complex_Value(const ABC_Value* parent):
      build_Implements_ValueId(parent)
    ,mystate(S_Init)
    ,x_(new Implements_Complex_Value)
    ,v_(parent)
    {
      setId(x_);
    }

    build_Implements_Complex_Value(const ABC_Value* parent,Implements_ValueId* id):
      build_Implements_ValueId(parent)
    ,mystate(S_ID_Final)
    ,x_(new Implements_Complex_Value(*id))
    ,v_(parent)
    {
      setId(x_);
    }

    void clear()override
    {
      ABClass_buildByToken::clear();
      delete x_;
      mystate=S_Init;
      x_=new Implements_Complex_Value;
      setId(x_);
    }


    Implements_Complex_Value* unloadVar() override
    {
      auto out=x_;
      mystate=S_Init;
      x_=new Implements_Complex_Value;
      setId(x_);
      return out;
    }
    virtual bool unPop(ABC_Value* var) override
    {
      if (var->complyClass(Implements_Complex_Value::ClassName()))
        {
          mystate=S_Final;
          if (x_!=var)
            delete x_;
          x_=dynamic_cast<Implements_Complex_Value*>(var);
          setId(x_);
          return true;
        }
      else return false;
    }

    bool pushToken(Token_New t, std::string& errorMessage)
    {
      switch (mystate)
        {
        case S_Init:
        case S_ID_Partial:
          if (!build_Implements_ValueId::pushToken(t,errorMessage))
            {
              return false;
            }
          else if (build_Implements_ValueId::isFinal())
            {
              mystate=S_ID_Final;
            }
          else
            {
              mystate=S_ID_Partial;
            }
          return true;
          break;
        case S_ID_Final:
          if (t.tok()==Token_New::BEGIN)
            {
              mystate=S_Header_2;
              return true;
            }
          else
            {
              errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::BEGIN,t);
              return false;
            }
          break;
        case S_Header_2:
          if (t.tok()==Token_New::EOL)
            {
              mystate=S_Header_Final;
              return true;
            }
          else
            {
              errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::EOL,t);
              return false;
            }break;
        case S_Header_Final:
        case S_Field_Partial:
          if (!v_.pushToken(t,errorMessage))
            {
              errorMessage=ABClass_buildByToken::getErrorMessage(errorMessage);
              return false;
            }
          else if (v_.isFinal())
            {
              x_->pushChild(v_.unloadVar());
              mystate=S_Field_Final;
            }
          else
            mystate=S_Field_Partial;
          return true;
          break;
        case S_Field_Final:
          // CAVEAT: in this way a complex class cannot define
          // its own type in its own body
          // because as soon as it tries to define itself it will enter the tail
          // definition
          if ((t.tok()==Token_New::IDENTIFIER)&&(t.str()==x_->myVar()))
            {
              mystate=S_END_2;
              return true;
            }
          else if (!v_.pushToken(t,errorMessage))
            {
              errorMessage=ABClass_buildByToken::getErrorMessage(errorMessage);
              return false;
            }
          else if (v_.isFinal())
            {
              x_->pushChild(v_.unloadVar());
              mystate=S_Field_Final;
            }
          else
            mystate=S_Field_Partial;
          return true;
          break;
        case S_END_2:
          if (t.tok()==Token_New::END)
            {
              mystate=S_END_Final;
              return true;
            }
          else
            {
              errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::END,t);
              return false;
            }
          break;
        case S_END_Final:
          if (t.tok()==Token_New::EOL)
            {
              mystate=S_Final;

              return true;
            }
          else
            {
              errorMessage= ABC_BuildByToken::getErrorMessage   (Token_New::EOL,t);
              return false;
            }
          break;
        case S_Final:
        default:
          return false;
          break;
        }
    }



    std::pair<std::string,std::set<std::string>> alternativesNext(Markov_Console::Markov_CommandManagerVar* cm)const
    {
      switch (mystate)
        {
        case S_Init:
        case S_ID_Partial:
          return build_Implements_ValueId::alternativesNext(cm);
          break;
        case S_ID_Final:
          return {myClass(),{Token_New::toString(Token_New::BEGIN)}};
          break;
        case S_Header_2:
          return {myClass(),{Token_New::toString(Token_New::EOL)}};
          break;

        case S_Header_Final:
        case S_Field_Partial:
          return v_.alternativesNext(cm);
        case S_Field_Final:

          {
            auto out =v_.alternativesNext(cm);
            out.second.insert(x_->myVar());
            return out;
          }
        case S_END_2:
          return {myClass(),{Token_New::toString(Token_New::END)}};
          break;
        case S_END_Final:
          return {myClass(),{Token_New::toString(Token_New::EOL)}};
          break;
          break;
        case S_Final:
        default:
          return {};
          break;
        }
    }


    Token_New popBackToken()

    {

      switch (mystate)
        {
        case S_Init:
          return {};
          break;

        case S_ID_Partial:
        case S_ID_Final:
          {
            auto out=build_Implements_ValueId::popBackToken();
            if (build_Implements_ValueId::isInitial())
              mystate=S_Init;
            else
              mystate= S_ID_Partial;
            return out;
          }
        case S_Header_2:
          mystate=S_ID_Final;
          return Token_New(Token_New::BEGIN);

        case S_Header_Final:
          mystate=S_Header_2;
          return Token_New(Token_New::EOL);
          break;
        case S_Field_Partial:
          {
            auto out=v_.popBackToken();
            if (!v_.isInitial())
              mystate=S_Field_Partial;
            else if (x_->numChilds()>0)
              mystate=S_Field_Final;
            else
              mystate=S_Header_Final;
            return out;

          }
          break;
        case S_Field_Final:
          {
            v_.unPop(x_->popLastChild());
            auto out=v_.popBackToken();
            if (!v_.isInitial())
              mystate=S_Field_Partial;
            else if (x_->numChilds()>0)
              mystate=S_Field_Final;
            else
              mystate=S_Header_Final;
            return out;
          }
          break;
        case S_END_2:
          mystate=S_Field_Final;
          return Token_New(x_->myVar());
          break;
        case S_END_Final:
          mystate=S_END_2;
          return Token_New(Token_New::BEGIN);
          break;
        case S_Final:
          mystate=S_END_Final;
          return Token_New(Token_New::EOL);
          break;
        default:
          return{};
          break;
        }
    }


    bool isFinal()const
    {
      return mystate==S_Final;
    }

    bool isInitial()const
    {
      return mystate==S_Init;
    }

    virtual bool isHollow()const
    {
      switch (mystate) {
        case     S_Init:
        case     S_ID_Partial:
        case      S_ID_Final:
          return true;
        case     S_Header_2:
        case     S_Header_Final:
        case     S_Field_Partial:
        case     S_Field_Final:
        case     S_END_2:
        case     S_END_Final:
        case     S_Final:

        default:
          return false;
        }
    }


  private:

    DFA mystate;
    Implements_Complex_Value* x_;
    build_ABC_Value v_;

  };







  template <typename T>
  ABC_Validator::State Validate(std::string& input,size_t &pos);


  template<>
  inline
  ABC_Validator::State Validate<std::string> (std::string&  ,size_t &)
  {
    return ABC_Validator::Acceptable;
  }

  template<>
  inline
  ABC_Validator::State Validate<double>(std::string&  input,std::size_t &pos)
  {


    std::stod(input,&pos);

    std::string rest=input.substr(pos);
    if (rest.empty()||(rest.find_first_not_of(" ")==rest.npos))
      return ABC_Validator::Acceptable;
    else if (((rest==".")&&input.find_first_of(".")==pos)
             || (((rest=="e")||(rest=="E")||(rest=="e-")||(rest=="E-"))
                 &&(rest.find_first_of("eE")==pos)))
      return ABC_Validator::Intermediate;
    else return ABC_Validator::Invalid;
  }

  template<>
  inline
  ABC_Validator::State Validate<int>(std::string&  input,size_t &pos)
  {
    int i=std::stoi(input,&pos);
    std::string rest=input.substr(pos);
    if (rest.empty()||(rest.find_first_not_of(" ")==rest.npos))
      return ABC_Validator::Acceptable;
    else  return ABC_Validator::Invalid;
  }

  template<>
  inline
  ABC_Validator::State Validate<std::size_t>(std::string&  input,size_t &pos)
  {
    int i=std::stoul(input,&pos);
    std::string rest=input.substr(pos);
    if (rest.empty()||(rest.find_first_not_of(" ")==rest.npos))
      return ABC_Validator::Acceptable;
    else  return ABC_Validator::Invalid;
  }






}




#endif // BUILDBYTOKEN


