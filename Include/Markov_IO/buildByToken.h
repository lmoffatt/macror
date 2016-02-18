#ifndef BUILDBYTOKEN
#define BUILDBYTOKEN


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
    void setErrorMessage(std::string err);

    void setErrorMessage(ABC_BuildByToken* child);

    void setErrorMessage(Token_New::Value expected, Token_New found);
    void setErrorMessage(std::string expected, Token_New found);
    void setErrorMessage(const Markov_Console::ABC_CommandVar *cmd, const std::string &error);
    void setErrorMessage(const Markov_Console::ABC_CommandVar *cmd
                         , const ABC_Value *input, const std::string &error);

    void setErrorsMessage(std::vector<Token_New::Value> expected, Token_New found);


    void clearErrorMessage();

    virtual void setErrorMessage(const Markov_Console::ABC_CommandVar *cmd, const ABC_Value *input, Token_New found);


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
      return "ABC_BuildByToken";
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

    static std::string ClassName();

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

    bool pushToken(Token_New t, std::string& errorMessage)override;


    std::pair<std::string,std::set<std::string>> alternativesNext(Markov_Console::Markov_CommandManagerVar* cm)const override
    {
      return {myClass(),{Implements_Simple_Value<C>::ClassName()}};
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

    Token_New popBackToken() override;

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







  template<>
  inline std::string buildByToken<double>::ClassName()
  {
    return "build_double";
  }

  template<>
  inline  bool buildByToken<double>::pushToken(Token_New to, std::string& errorMessage)
  {
    if (!to.isReal())
      {
        setErrorMessage(Token_New::REAL,to);
        return false;
      }
    else
      {
        auto n=to.realValue();
        if (parent()!=nullptr)
          {
            if (parent()->checkValue(varType_,n,errorMessage))
              {
                x_=n;
                isComplete_=true;
                return true;
              }
            else return false;
          }
        else
          {
            errorMessage=myClass()+" has no parent variable";
          }  clearErrorMessage();
      }
  }



  template<>
  inline  Token_New buildByToken<double>::popBackToken()
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

  template<>
  inline std::string buildByToken<int>::ClassName()
  {
    return "build_int";
  }

  template<>
  inline  bool buildByToken<int>::pushToken(Token_New to, std::string& errorMessage)
  {
    if (!to.isInteger())
      {
        std::string err=to.str()+" is not an integer number";
        setErrorMessage(Token_New::INTEGER,to);
        return false;
      }
    else
      {
        if (parent()!=nullptr)
          {
            auto n=to.intval();
            if (parent()->checkValue(varType_,n,errorMessage))
              {
                x_=n;
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
  }

  template<>
  inline  Token_New buildByToken<int>::popBackToken()
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


  template<>
  inline std::string buildByToken<std::size_t>::ClassName()
  {
    return "build_count";
  }


  template<>
  inline  bool buildByToken<std::size_t>::pushToken(Token_New to, std::string& errorMessage)
  {
    if (!to.isCount())
      {
        setErrorMessage(Token_New::UNSIGNED,to);
        return false;
      }
    else
      {
        if (parent()!=nullptr)
          {
            auto n=to.count();
            if (parent()->checkValue(varType_,n,errorMessage))
              {
                x_=n;
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
  }


  template<>
  inline  Token_New buildByToken<std::size_t>::popBackToken()
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

  template<>
  inline std::string buildByToken<std::string>::ClassName()
  {
    return "build_string";
  }



  template<>
  inline  bool buildByToken<std::string>::pushToken(Token_New to, std::string& errorMessage)
  {
    std::string s=to.str();

    if (parent()!=nullptr)
      {
        if (parent()->checkValue(varType_,s,errorMessage))
          {
            x_=to.str();
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

  template<>
  inline  Token_New buildByToken<std::string>::popBackToken()
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

  template<typename T>
  class buildByToken<std::vector<T> >
      :public ABClass_buildByToken<std::vector<T>>
  {
  public:

    static std::string ClassName()
    {
      return "Build_vector";
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
              ABC_BuildByToken::setErrorMessage("end of line",tok);
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
              ABC_BuildByToken::setErrorMessage(Token_New::LSB,tok);
              return false;
            }
          else
            {
              ABC_BuildByToken::clearErrorMessage();
              mystate=S_Header_Final;
              return true;
            }
          break;
        case S_Header_Final:
        case S_Data_Partial:
          if (!myChildState.pushToken(tok, errorMessage))
            {
              ABC_BuildByToken::setErrorMessage(&myChildState);
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
              ABC_BuildByToken::setErrorMessage(&myChildState);
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
      return "Build_pair";
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
              ABC_BuildByToken::setErrorMessage(&first_);
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
              ABC_BuildByToken::setErrorMessage(Token_New::COLON, tok);
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
              ABC_BuildByToken::setErrorMessage(&second_);
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
      return "Build_Matrix";
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
        case S_Header_Final:
          return true;
          break;
        case S_Data_Partial:
        case S_Final:
        default:
          return false;
        }
    }



    Markov_LA::M_Matrix<T> unloadVar()
    {
      if (isFinal())
        {
          mystate=S_Init;
          return x_;
        }
      else
        return {};
    }

    bool unPop(Markov_LA::M_Matrix<T> var)
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
              ABC_BuildByToken::setErrorMessage(Token_New::EOL, tok);
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
                      ABC_BuildByToken::setErrorMessage(
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
                      ABC_BuildByToken::setErrorMessage(
                            "Error in matrix. nrows="+std::to_string(nRows_)
                            +"  nCols="+std::to_string(nCols_));
                      return false;
                    }}
              else  {
                  ABC_BuildByToken::setErrorMessage(
                        "Error in matrix. nrows="+std::to_string(nRows_)
                        +"  nCols="+std::to_string(nCols_));
                  return false;
                }}

          else if (getValue(tok,v_))
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
                  ABC_BuildByToken::setErrorMessage(
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
    bool getValue(Token_New tok, T& v);
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
      Token_New tok, double &v)
  {
    if (tok.isReal())
      {
        v=tok.realValue();
        return true;
      }
    else
      {
        ABC_BuildByToken::setErrorMessage(Token_New::REAL, tok);
        return false;
      }
  }

  template<>
  inline  bool Markov_IO::buildByToken<Markov_LA::M_Matrix<std::size_t> >::getValue(
      Token_New tok, std::size_t &v)
  {
    if (tok.isCount())
      {
        v=tok.count();
        return true;
      }
    else
      {
        ABC_BuildByToken::setErrorMessage(Token_New::UNSIGNED, tok);
        return false;
      }  }

  template<>
  inline bool Markov_IO::buildByToken<Markov_LA::M_Matrix<int> >::getValue(
      Token_New tok, int &v)
  {
    if (tok.isInteger())
      {
        v=tok.intval();
        return true;
      }
    else
      {
        ABC_BuildByToken::setErrorMessage(Token_New::INTEGER, tok);
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
              ABC_BuildByToken::setErrorMessage(Token_New::EOL, tok);
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
              ABC_BuildByToken::setErrorMessage(Token_New::LCB, tok);
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
              ABC_BuildByToken::setErrorMessage(&myChildState);
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
              ABC_BuildByToken::setErrorMessage(&myChildState);
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
              ABC_BuildByToken::setErrorMessage(Token_New::EOL,tok);
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
              ABC_BuildByToken::setErrorMessage(Token_New::LCB,tok);
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
              ABC_BuildByToken::setErrorMessage(&myChildState);
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
              ABC_BuildByToken::setErrorMessage(&myChildState);
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
    static std::string ClassName()
    {
      return "build_Implements_ValueId";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Value_ByToken::SuperClasses()+ClassName();
    }

    std::string myClass()const override
    {
      return ClassName();

    }

    std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }

    enum DFA {
      S_Init=0, TIP1, TIP2,WT0_ID0,WT2,WT3,ID1,ID2,WT1,ID0,S_Final
    } ;

    build_Implements_ValueId(const ABC_Value* p):
      ABC_Value_ByToken(p),
      id_(nullptr),
      idstate(S_Init){}


    void setId(Implements_ValueId* id)
    {
      delete id_;
      id_=id;
    }


    Implements_ValueId* unloadVar() override
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

    void clear()override
    {
      ABClass_buildByToken::clear();
      delete id_;
      idstate=S_Init;
      id_=new Implements_ValueId;
    }

    bool pushToken(Token_New t, std::string& errorMessage) override
    {
      switch (idstate) {
        case S_Init:
          if (t.tok()==Token_New::HASH)
            {
              idstate=TIP1;
              return true;
            }
          else if (t.tok()==Token_New::IDENTIFIER)
            {
              if (parent()->idToValue(t.identifier())!=nullptr)
                {

                }
              parent()->isValidId(t.identifier());
              if (id_==nullptr)
                id_=new Implements_ValueId;
              id_->setId(t.str());

              idstate =ID1;
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
              ABC_BuildByToken::setErrorMessage(e,t);
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
              ABC_BuildByToken::setErrorMessage(e,t);
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
              idstate =ID1;
              if (id_==nullptr)
                id_=new Implements_ValueId;
              id_->setId(t.str());
              return true;
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
              ABC_BuildByToken::setErrorMessage(Token_New::HASH,t);
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
              ABC_BuildByToken::setErrorMessage(Token_New::STRING,t);
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
              ABC_BuildByToken::setErrorMessage(Token_New::EOL,t);
              return false;
            }   break;

        case ID0:
          if (t.tok()==Token_New::IDENTIFIER)
            {
              idstate =ID1;
              if (id_==nullptr)
                id_=new Implements_ValueId;
              id_->setId(t.str());
              return true;
            }
          else
            {
              ABC_BuildByToken::setErrorMessage(Token_New::IDENTIFIER,t);
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
              ABC_BuildByToken::setErrorMessage(Token_New::COLON,t);
              return false;
            }
          break;
        case ID2:
          if (t.tok()==Token_New::IDENTIFIER)
            {
              idstate =S_Final;
              if (id_==nullptr)
                id_=new Implements_ValueId;
              id_->setVar(t.str());
              return true;
            }
          else
            {
              ABC_BuildByToken::setErrorMessage(Token_New::IDENTIFIER,t);
              return false;
            }
          break;
        case S_Final:
        default:
          return false;
          break;
        }
    }

    virtual bool  unPop(ABC_Value* var) override
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


    std::pair<std::string,std::set<std::string>> alternativesNext(Markov_Console::Markov_CommandManagerVar* cm)const override
    {
      switch (idstate ) {
        case S_Init:
          return {myClass(),{Token_New::toString(Token_New::HASH)
                    ,"[variable_identifier]"}};
          break;

          break;
        case TIP1:
          return {myClass(),{"tip_string"}};
          break;
        case TIP2:
          return {myClass(),{Token_New::toString(Token_New::EOL)}};
          break;
        case WT0_ID0:
          return {myClass(),{Token_New::toString(Token_New::HASH)
                    ,"variable_identifier"}};
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


    Token_New popBackToken() override
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



    bool isFinal()const override
    {
      return idstate==S_Final;
    }
    bool isInitial()const override
    {
      return idstate==S_Init;
    }

    virtual bool isHollow()const override
    {
      return isInitial();
    }

    ~build_Implements_ValueId(){}


  private:
    Implements_ValueId* id_;
    DFA idstate;

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
              ABC_BuildByToken::setErrorMessage(e+t.str());
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
              ABC_BuildByToken::setErrorMessage(Token_New::MUL,t);
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
              ABC_BuildByToken::setErrorMessage(Token_New::IDENTIFIER,t);
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
              ABC_BuildByToken::setErrorMessage(Token_New::EOL,t);
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
              ABC_BuildByToken::setErrorMessage(Token_New::ASSIGN,t);
              return false;
            }
          break;
        case S_Header_Final:
        case S_Data_Partial:
          if (!data_.pushToken(t, errorMessage))
            {
              ABC_BuildByToken::setErrorMessage(&data_);
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
              ABC_BuildByToken::setErrorMessage(Token_New::EOL,t);
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


    ABC_Value* unloadVar();

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

    virtual std::__cxx11::string myClass() const override;
    virtual std::set<std::__cxx11::string> mySuperClasses() const override;

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
          ABClass_buildByToken::setErrorMessage("cannot unload beacause it is not in final state");

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
          ABClass_buildByToken::setErrorMessage(cmv_,"cannot unload because it is not in final state");
        }
    }

    bool  unPop(ABC_Value* var)
    {
      return false;
    }


    bool pushToken(Token_New t, std::string& errorMessage);



    std::pair<std::string,std::set<std::string>> alternativesNext(Markov_Console::Markov_CommandManagerVar* cm)const;


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


    Implements_Complex_Value* unloadVar()
    {
      auto out=x_;
      mystate=S_Init;
      x_=new Implements_Complex_Value;
      setId(x_);
      return out;
    }
    virtual bool unPop(ABC_Value* var)
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
              ABC_BuildByToken::setErrorMessage(Token_New::BEGIN,t);
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
              ABC_BuildByToken::setErrorMessage(Token_New::EOL,t);
              return false;
            }break;
        case S_Header_Final:
        case S_Field_Partial:
          if (!v_.pushToken(t,errorMessage))
            {
              ABC_BuildByToken::setErrorMessage(&v_);
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
              ABC_BuildByToken::setErrorMessage(&v_);
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
              ABC_BuildByToken::setErrorMessage(Token_New::END,t);
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
              ABC_BuildByToken::setErrorMessage(Token_New::EOL,t);
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


