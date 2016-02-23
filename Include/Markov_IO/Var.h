#ifndef VAR_H
#define VAR_H

#include "Markov_LA/Matrix.h"


#include <string>
#include <map>
#include <set>
#include <vector>



namespace Markov_IO_New {


  // forward declarations



  template<class C,typename T>
  using setter=void (C::*)(T);

  template<class C,typename T>
  using getter=T(C::*)()const;

  template<class C,typename T>
  using refgetter=const T&(C::*)()const;

  template<class C,typename T>
  using refsetter=T&(C::*)();

  //using valuePredicate=bool(*)(const ABC_Value*);
  //  using valueStringPredicate=bool(*)(const ABC_Value*, const std::string&);


  using namePredicate=bool(*)(const std::string&);

  template<typename C>
  struct Cls
  {
    static std::string name() { return C::ClassName() ;}
  };

  template<typename C>
  struct Cls<C*>
  {
    static std::string name() { return C::ClassName() ;}
  };


  template<typename T>
  struct Cls<std::vector<T>>
  {
    static std::string name() { return "vector_of_"+Cls<T>::name() ;}
  };

  template<typename T>
  struct Cls<std::set<T>>
  {
    static std::string name() {return "set_of_"+Cls<T>::name();}
  };

  template<typename K,typename T>
  struct Cls<std::pair<K,T>>
  {
    static std::string name() { return "pair_of_"+Cls<K>::name()+"_and_"+Cls<T>::name() ;}
  };

  template<typename K,typename T>
  struct Cls<std::map<K,T>>
  {
    static std::string name(){return "map_of_"+Cls<K>::name()+"_on_"+Cls<T>::name();}
  };


  template<typename T>
  struct Cls<Markov_LA::M_Matrix<T>>
  {
    static std::string name() { return "matrix_of_"+Cls<T>::name() ;}
  };


  template<>
  struct Cls<int>
  {
    static std::string name() {return "integer";}
  };

  template<>
  struct Cls<double>
  {
    static std::string name(){return "double";}
  };

  template<>
  struct Cls<std::string>
  {
    static std::string name(){return "string";}
  };

  template<>
  struct Cls<std::size_t>
  {
    static std::string name(){return "count";}
  };


   class ABC_Var_New;
   class ABC_Value_New;


  template<class T>
  T dynamicCast(ABC_Var_New* v, std::string* whyNot);

  template<class T>
  T dynamicCast(ABC_Value_New* v, std::string* whyNot);

  std::set<std::string> operator+(std::set<std::string>&& tok1,
                                  std::string &&s);


  std::set<std::string> operator+(std::set<std::string> &&ss1,
                                  std::set<std::string> &&ss2);



  class ABC_Value_New
  {
  public:
    static std::string ClassName()
    {
      return "ABC_Value_New";
    }

    virtual std::string myClass()const
    {
      return ClassName();
    }


    virtual std::string storedClass() const=0;

    virtual bool empty()const =0;

    virtual void reset()=0;

    virtual ~ABC_Value_New(){}

    /// template methods
    ///

    //TODO: ver cual es la forma mas conveniente de manejar la propiedad de T, especialmente si esgrand

    template<typename T>
    const T *getValue()const;

    template<typename T>
    T* getValue();

    template<typename T>
    bool setValue(const T& val);


  };


  template<class T>
  class ABC_Var_Typed;

  template<class T>
  class ABC_Value_Typed: public ABC_Value_New
  {

    // ABC_Value_New interface
  public:
    static std::string ClassName()
    {
      return "ABC_Value_Typed_of_"+Cls<T>::name();
    }

    virtual std::string myClass()const
    {
      return ClassName();
    }

    virtual std::__cxx11::string storedClass() const override
    {
      return Cls<T>::name();
    }

    virtual const T* getValued()const=0;

    virtual T* getValued()=0;

    virtual bool setValue(T* val,std::string *whyNot)=0;

    virtual ~ABC_Value_Typed(){}
  };

  template <typename T>
  class ABC_Typed_Value;

  template<typename T>
  class Implements_Value_New: public ABC_Value_Typed<T>
  {
  public:
    static std::string ClassName()
    {
      return "Implements_Value_Typed"+Cls<T>::name();
    }

    virtual std::string myClass()const
    {
      return ClassName();
    }


    // ABC_Value_New interface
  public:
    virtual bool empty() const override
    {
      return empty_;
    }

    virtual void reset() override
    {
      *data_={};
      empty_=true;
    }
    // ABC_Value_Typed interface
  public:
    virtual const T *getValued() const override
    {
      return data_;
    }
    virtual T *getValued() override
    {
      return data_;
    }
    virtual bool setValue(T *val,std::string *whyNot) override
    {
      delete data_;
      data_=val;
      empty_=false;
      return true;
    }



    Implements_Value_New():
      data_{new T{}}, empty_(true){}
    Implements_Value_New(T* datum):
      data_(datum), empty_(false){}

    ~Implements_Value_New(){delete data_;}

  private:

    T* data_;
    bool empty_;
  };



  class Implements_ComplexVar_New;


  struct Var_id
  {
    std::string idName;
    std::string var;
    ABC_Value_New* value;
    std::string tip;
    std::string whathis;
    static std::string ClassName(){return "Var_id";}
    std::string id()const {return idName;}
  };



  class ABC_Type_of_Value;
  template <typename T>
  class ABC_Typed_Value;

  class ABC_Var_New: public ABC_Value_Typed<Var_id>
  {

    // ABC_Value_New interface
  public:
    static std::string ClassName()
    {
      return "ABC_Value_New";
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }

    virtual ABC_Value_New* value()=0;

    virtual const ABC_Value_New* value()const=0;

    virtual const Implements_ComplexVar_New* parent()const =0;
    virtual void setParentValue(const Implements_ComplexVar_New* par)=0;

    virtual std::string id()const=0;


    virtual std::string Tip()const=0;
    virtual std::string WhatThis()const=0;

    virtual void setId(const std::string& idName)=0;


    virtual std::string refId()const=0;

    virtual std::string myType()const=0;


    virtual ~ABC_Var_New(){}

  };

  template<typename T>
  class Implements_Var_New: public ABC_Var_New
  {
    // ABC_Value_New interface
  public:
    static std::string ClassName()
    {
      return "Implements_Var_New_of"+Cls<T>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }

    virtual const Implements_ComplexVar_New* parent()const override
    {
      return p_;
    }
    virtual void setParentValue(const Implements_ComplexVar_New* par) override
    {
      p_=par;
    }

    virtual std::string id()const override
    {
      return v_.idName;
    }


    virtual std::string Tip()const override
    {
      return v_.tip;
    }
    virtual std::string WhatThis()const override
    {
      return v_.whathis;
    }

    virtual void setId(const std::string& idName) override
    {
      v_.idName=idName;
    }


    virtual std::string refId()const override
    {
      return v_.idName;
    }

    virtual std::string myType()const override
    {
      return v_.var;
    }

    virtual ABC_Value_Typed<T>* value()
    {
      return x_;
    }

    virtual const ABC_Value_Typed<T>* value()const
    {
      return x_;
    }




    virtual ~Implements_Var_New()
    {
      delete v_.value;
    }




    // ABC_Value_New interface
  public:
    virtual bool empty() const override
    {
      return value()->empty();
    }
    virtual void reset() override
    {
      delete x_;
      value()->reset();
    }

    // ABC_Value_Typed interface
  public:
    virtual const Var_id *getValued() const override
    {
      return &v_;
    }
    virtual Var_id *getValued() override
    {
      return &v_;
    }
    virtual bool setValue(Var_id *val,std::string *whyNot) override
    {
      auto x= (dynamicCast<Implements_Value_New<T>*>(v_.value,whyNot));
      if (x==nullptr)
        return false;
      else
        {
          x_=x;
          v_=*val;
          return true;
        }
    }
    Implements_Var_New(const Implements_ComplexVar_New* parent,
                       const std::string& id,
                       const std::string& var,
                       const std::string& tip,
                       const std::string& whatthis):
      p_(parent),
      x_(new Implements_Value_New<T>()),
      v_({id,var,x_,tip,whatthis}){
      v_.value=x_;
    }


  private:
    const Implements_ComplexVar_New* p_;
    Implements_Value_New<T>* x_;
    Var_id v_;

  };


  class Token_New
  {
  public:
    ///
    /// \brief isNameChar check if a char is allowed on identifiers
    /// \param ch inspected char
    /// \return true if is a char allowed in identifiers
    ///
    static bool isNameChar(char ch);
    static bool isSpaceChar(char ch);
    static bool isRealNumberChar(char ch);

    static std::string toString(double number);
    static std::string toString(int number);
    static std::string toString(std::size_t number);
    enum  Value: char {
      EMPTY,
      ANY,
      IDENTIFIER,
      STRING,
      INTEGER,
      UNSIGNED,
      REAL,
      INVALID,

      EOL='\n',
      HASH='#',
      PLUS='+',
      MINUS='-',
      MUL='*',
      DIV='/',
      EXPONENT='^',

      DOT='.',
      COLON=':',
      COMMA=',',
      SEMICOLON=';',
      ASSIGN='=',

      LP='(',
      RP=')',
      LSB='[',
      RSB=']',
      LCB='{',
      RCB='}',
      NOT='~',
      AND='&',
      OR='|',
      LSS='<',
      GTR='>',

      DCOLON,//::
      LEQ,// <=
      EQ, //==
      NEQ, //~=
      GEQ, // >=

      WHILE, //while
      DO,  //do
      IF, //if
      THEN, // then
      BEGIN, //begin
      END, // end
      ELSE, // else
      SWITCH, //switch
      CASE   // case
    };




    static bool oneCharIsEnough(Value v);

    std::istream& get(std::istream& stream);
    std::string str()const;

    std::string identifier()const;
    static std::string identifier(const std::string idWithSPace);

    double realValue()const;
    int  intval()const;

    std::size_t count()const;

    Value tok()const;

    std::string toString()const;

    template<typename T>
    bool toValue(T& val)const;

    bool isReal()const;
    bool isInteger()const;
    bool isCount()const;



    ///
    /// \brief toKeyword convert a string to the corresponding token value, a keyword, an identifier or a string
    /// \param identifier a string to be checked
    /// \return the identified keyword or the value IDENTIFIER
    ///
    static Value toKeyword(std::string identifier);
    static Value toToken(char ch);

    static std::string toString(Value identifier);




    Token_New();

    explicit Token_New(double d);

    explicit Token_New(int n);

    explicit Token_New(std::size_t s);

    Token_New(const std::string &d);

    static Token_New toToken(const std::string &d, std::size_t& pos)
    {
      pos=0;
      Token_New t;
      while ((pos<d.size()) && t.CharIsSuccesfullyFeed(d[pos])) ++pos;
      return t;
    }

    Token_New(Value v);

    explicit Token_New(char ch);

    friend class Token_Stream;

    enum DAF{
      S_Init, S_Partial, S_Final
    };


    void clear();

    bool pushChar(char c);

    char popLastChar();

    bool CharIsSuccesfullyFeed(char ch);



    bool isFinal()const
    {
      return myState_==S_Final;
    }
    bool isInitial()const
    {
      return myState_==S_Init;
    }

    bool isValid()const
    {
      return curr_tok!=INVALID;
    }

    static bool canBePartial(Value v);
  private:
    Value curr_tok;
    DAF myState_;
    double number_;
    int int_;
    std::size_t size_;
    std::string str_;

  };


  class ABC_Output
  {
  public:
    virtual void put(const std::string& s)=0;
    virtual void put(double x)=0;
    virtual void put(int n)=0;
    virtual void put(std::size_t n)=0;
    virtual void put(char c)=0;

    template<typename T>
    void put(const std::vector<T>& v)
    {
      put('[');
      for (auto& e:v)
        { put(e); put('\t');}
      put(']');
    }

    virtual ~ABC_Output(){}
  };

  class ABC_Input
  {
  public:

    virtual  bool get( std::string& s,std::string* whyNot)=0;
    virtual  bool get(double& x,std::string* whyNot)=0;
    virtual  bool get(int& n,std::string* whyNot)=0;
    virtual  bool get(std::size_t& n,std::string* whyNot)=0;
    virtual  bool get(char& c,std::string* whyNot)=0;

    template<typename T>
    bool get(T& x, std::string* error);
    virtual ~ABC_Input(){}
  };

  class ABC_BuildByToken
  {
  public:

    virtual bool pushToken(Token_New t, std::string& errorMessage)=0;

    std::string errorMessage()const;
    virtual  std::pair<std::string,std::set<std::string>> alternativesNext()const=0;

    virtual Token_New popBackToken()=0;
    virtual bool isFinal()const=0;
    virtual bool isInitial()const=0;
    virtual bool isHollow()const=0;

    virtual ~ABC_BuildByToken();

    virtual void clear()=0;

    const Implements_ComplexVar_New* parent()const;
  protected:
    ABC_BuildByToken(const Implements_ComplexVar_New* p);

  private:

    const Implements_ComplexVar_New* parent_;


  };

  template<typename C>
  class ABClass_buildByToken: public ABC_BuildByToken
  {
  public:

    virtual C unloadVar()=0;

    virtual bool unPop(C var)=0;
    virtual ~ABClass_buildByToken(){}
  protected:
    ABClass_buildByToken(const Implements_ComplexVar_New* p):ABC_BuildByToken(p){}

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



    buildByToken(const Implements_ComplexVar_New* parent,const std::string vartype):
      ABClass_buildByToken<C>(parent),
      x_(),
      isComplete_(false),
      varType_(vartype)
    {

    }


    C unloadVar()override
    {
      auto out=std::move(x_);
      x_= {};
      isComplete_=false;
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



    std::pair<std::string,std::set<std::string>> alternativesNext()const override
    {
      if (this->parent()!=nullptr)
        {
          std::set<std::string> a=this->parent()->idToValueType(varType_)->alternativeNext();
          return {varType_,a};
        }
      else
        {
          return {varType_,{Cls<C>::name()}};
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



  class ABC_Type_of_Value:public ABC_Var_New
  {
  public:
    static std::string ClassName()
    {
      return "ABC_Type_of_Value";
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }

    virtual bool put(const ABC_Value_New* v,ABC_Output* ostream,std::string* error)const=0;

    virtual bool get(ABC_Value_New* v, ABC_Input* istream,std::string* error )const=0;

    virtual ABC_BuildByToken* getBuildByToken()const=0;

    virtual ABC_Value_New* empty_Value()const=0;

    virtual ABC_Value_New* default_Value()const=0;


    virtual std::set<std::string> alternativeNext()const=0;


    virtual bool isInDomain(const ABC_Value_New* v, std::string *whyNot)const=0;


  };

  template<typename T>
  class ABC_Typed_Value:public ABC_Type_of_Value
  {
  public:
    static std::string ClassName()
    {
      return "ABC_Typed_Var_of_"+Cls<T>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }

    virtual bool isInDomain(const ABC_Value_New* v, std::string *whyNot)const
    {
      auto x=dynamicCast<const ABC_Value_Typed<T>* >(v,whyNot);
      if (x==nullptr)
        {
          return false;
        }
      else
        return isInDomain(x->getValued(),whyNot);
    }

    virtual bool put(const ABC_Value_New* v,ABC_Output* ostream,std::string* whyNot)const
    {
      auto x=dynamicCast<const ABC_Value_Typed<T>* >(v,whyNot);
      if (x==nullptr)
        {
          return false;
        }
      else
        return put(x->getValued(),ostream,whyNot);
    }

    virtual bool get(ABC_Value_New* v, ABC_Input* istream,std::string* whyNot )const
    {
      auto x=dynamicCast<ABC_Value_Typed<T>* >(v,whyNot);
      if (x==nullptr)
        {
          return false;
        }
      else
        return get(x->getValued(),istream,whyNot);

    }





    virtual bool put(const T* v,ABC_Output* ostream,std::string* error)const=0;

    virtual bool get(T*& v, ABC_Input* istream,std::string* whyNot )const=0;

    virtual ABClass_buildByToken<T>* getBuildByToken()const=0;

    virtual T* getEmpty_Valued()const=0;

    virtual T* getDefault_Valued()const=0;


    virtual bool isInDomain(const T &val, std::__cxx11::string *whyNot) const;


    virtual ~ABC_Typed_Value(){}


  };



  template<typename T>
  class Implements_Type_New:public ABC_Typed_Value<T>
  {
  public:
    static std::string ClassName()
    {
      return "Implements_Type_New"+Cls<T>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }


    virtual bool put(const T* v,ABC_Output* ostream,std::string* error)const
    {
      ostream->put(*v);
      return true;
    }

    virtual bool get(T*& v, ABC_Input* istream,std::string* whyNot )const
    {

      if (!istream->get(v,whyNot))
        return false;
      else
        return isInDomain(*v,whyNot);
    }

    virtual std::set<std::string> alternativeNext()const
    {
      return {};
    }

    virtual buildByToken<T>* getBuildByToken()const
    {
      return new buildByToken<T>(this->parent(),this->id());
    }


    virtual ~Implements_Type_New(){}


    Implements_Type_New()
    {}

  private:



    // ABC_Value_New interface
  public:
    virtual bool empty() const override;
    virtual void reset() override;

    // ABC_Value_Typed interface
  public:
    virtual const T *getValued() const override;
    virtual T *getValued() override;
    virtual bool setValue(T *val) override;

    // ABC_Var_New interface
  public:
    virtual ABC_Value_New *value() override;
    virtual const ABC_Value_New *value() const override;
    virtual const Implements_ComplexVar_New *parent() const override;
    virtual void setParentValue(const Implements_ComplexVar_New *par) override;
    virtual std::__cxx11::string id() const override;
    virtual std::__cxx11::string Tip() const override;
    virtual std::__cxx11::string WhatThis() const override;
    virtual void setId(const std::__cxx11::string &idName) override;
    virtual std::__cxx11::string refId() const override;
    virtual std::__cxx11::string myType() const override;

  };







  class Implements_ComplexVar_New: public Implements_Var_New<std::map<std::string,ABC_Var_New*>>
  {
  public:
    static std::string ClassName()
    {
      return "ABC_Value_New";
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }

    virtual const ABC_Var_New* idToVar(const std::string& name)const
    {
      auto it=m_->find(name);
      if (it!=m_->end())
        return it->second;
      else if (parent()!=nullptr)
        return  parent()->idToVar(name);
      else return nullptr;
    }

    virtual ABC_Var_New* idToVar(const std::string& name)
    {
      auto it=m_->find(name);
      if (it!=m_->end())
        return it->second;
      else
        return nullptr;
    }

    virtual const ABC_Type_of_Value* idToValueType(const std::string& name,std::string * whyNot)const
    {
      auto it=m_->find(name);
      if (it!=m_->end())
        return dynamicCast<const ABC_Type_of_Value*>(it->second,whyNot);
      else if (parent()!=nullptr)
        return  parent()->idToValueType(name,whyNot);
      else return nullptr;

    }

    template<typename T>
    const ABC_Typed_Value<T>* idToValueTyped(const std::string& name,std::string *whyNot)const
    {
      auto it=m_->find(name);
      if (it!=m_->end())
        {
          return dynamicCast<const ABC_Typed_Value<T>*>(it->second,whyNot);
        }

      else if (parent()!=nullptr)
        return  parent()->idToValueTyped<T>(name,whyNot);
      else return nullptr;
    }


    template<typename T>
    bool getValueFromId(const std::string& name, const T*& value,std::string* whyNot)const
    {
      auto it=m_->find(name);
      if (it!=m_->end())
        {
          auto v=dynamicCast<const ABC_Value_Typed<T>*>(it->second,whyNot);
          if (v==nullptr)
            {
              return false;
            }
          else if (v->empty())
            {
              *whyNot="variable is empty";
              return false;
            }
          else
            {
              value=v->getValued();
              return true;
            }
        }

      else if (parent()!=nullptr)
        return  parent()->getValueFromId(name,value,whyNot);
      else
        {
          *whyNot=id()+" does not have it and it has no parent";
          return false;
        }
    }







    bool hasName(const std::string& name, std::string* whoHasIt)const
    {
      if (m_->find(name)!=m_->end())
        {
          *whoHasIt=id();
          return true;
        }
      if (parent()==nullptr)
        return false;
      else return parent()->hasName(name, whoHasIt);
    }


    template <typename T>
    bool insertChild(const std::string& id,
                     const std::string& var,
                     T* value,
                     const std::string& tip
                     ,const std::string& whatthis
                     ,std::string *whyNot)
    {
      std::string whoHasIt;
      if (hasName(id,&whoHasIt))
        {
          *whyNot=id+" exists in"+whoHasIt;
          return false;
        }
      else
        {
          auto v=idToValueTyped<T>(var,whyNot);
          if (v==nullptr)
            return false;
          else
            {
              if (!v->isInDomain(value,whyNot))
                return false;
              else
                {
                  pushChild(new Implements_Var_New(this,{id,var,value,tip,whatthis}));
                  return true;
                }}}
    }





    virtual bool removeChild(const std::string& name)
    {
      return m_->erase(name)==1;

    }

    virtual void pushChild(ABC_Var_New* var)
    {
      (*m_)[var->id()]=var;
    }



    Implements_ComplexVar_New(const Implements_ComplexVar_New* parent,
                              const std::string& id
                              ,const std::string& var
                              ,const std::string& tip
                              ,const std::string& whatthis):
      Implements_Var_New(parent,
                         id,var,tip,whatthis)
    {

      m_=this->getValued()->value->getValue<std::map<std::string,ABC_Var_New*>>();
    }


    // ABC_Value_Typed interface

  private:
    std::map<std::string,ABC_Var_New*>* m_;
  };


  class ABC_Command: public ABC_Var_New
  {





  };









  ///--------------------------------------------------------------------
  ///-------------------------------------------------------------------
  ///

  /// Template implementations
  ///
  ///






  template<class L>
  L dynamicCast(ABC_Var_New* v, std::string* whyNot)
  {
    auto r=dynamic_cast<L>(v);
    if (r==nullptr)
      {
        *whyNot=v->id()+ "is not a "+Cls<L>::name();
      }
    return r;

  }

  template<class L>
  L dynamicCast(ABC_Value_New* v, std::string* whyNot)
  {
    auto r=dynamic_cast<L>(v);
    if (r==nullptr)
      {
        *whyNot=v->myClass()+ "is not a "+Cls<L>::name();
      }
    return r;

  }







  template<typename T>
  const T* ABC_Value_New::getValue()const
  {
    if (storedClass()==Cls<T>::name())
      {
        auto v =dynamic_cast<const ABC_Value_Typed<T>*>(this);
        return v->getValued();
      }
    else
      return nullptr;
  }

  template<typename T>
  T *ABC_Value_New::getValue()
  {
    if (storedClass()==Cls<T>::name())
      {
        auto v =dynamic_cast< ABC_Value_Typed<T>*>(this);
        return v->getValued();
      }
    else
      return nullptr;

  }

  template<typename T>
  bool ABC_Value_New::setValue(const T& val)
  {
    if (storedClass()==Cls<T>::name())
      {
        auto v =dynamic_cast< ABC_Value_Typed<T>*>(this);
        v->setValue(val);
        return true;
      }
    else
      return false;

  }




}




#ifdef dsgds

namespace choto {






  class ABC_Value: public ABC_Put, public ABC_Base
  {
  public:

    //*****************************************************************
    //                          Static methods
    //*****************************************************************


    static bool isValidId(std::string name);

    static std::string nextId(const std::string& idTemplate);
    static std::size_t getVersionNumber(const std::string& id);

    static std::string ClassName();

    static std::set<std::string> SuperClasses();

    /// creates an ABC_Value of the right kind of within Complex_Value/Simple_Value
    /// No parent, it should be either deleted or rooted
    static ABC_Value* getValueFromStream(Token_Stream &t);



    //******************************************************************
    //                      Abstract methods
    //******************************************************************


    //**********************************************


    /// it returns a copy of the value representation of the object
    /// it works as a Parameter
    virtual ABC_Value* to_PlainValue() const =0;

    virtual ABC_Value* to_PlainValue(const ABC_Measure* measure)const =0;



    /// indicates whether it contains data
    virtual bool empty()const =0;

    /// removes all data, but keeps the fields intact

    virtual void clear()=0;


    /// indicates if it is a variable
    virtual bool isVar()const{ return false;}


    virtual bool isData()const {return false;}

    virtual bool isCommand()const {return false;}


    virtual Token_Stream toTokens()const=0;

    virtual std::string Tip()const=0;
    virtual std::string WhatThis()const=0;

    /// creates an empty object of the same class
    virtual ABC_Value* create()const=0;  // ABC_Put::create() // same myClass?

    /// creates a stand alone copy of the object,
    /// however it does not have the same parent
    virtual ABC_Value* clone()const=0;   //


    virtual std::string id()const=0;
    virtual void setId(const std::string& idName)=0;


    virtual std::string refId()const=0;

    virtual std::string myVar()const=0;


    virtual void setVar(const std::string& varname)=0;

    virtual bool isRootedVariable()const=0;



    ///FIXME: see what to to with it
    virtual const ABC_Var* myVarPtr()const=0;

    virtual ABC_Var* myVarPtr(ABC_Value* parent)const=0;



    virtual bool isValueOfThisVar(const ABC_Value* v)const=0;




    /// necessary for GUI, not very elegant
    virtual std::set<std::string> modes()const =0;
    virtual bool complyModes(const std::string mode) const=0;





    // invariant varCreate()->processTokens(toTokens())=true


    virtual std::size_t numChilds()const=0;

    virtual bool isMyParent(const ABC_Value* aParent)const =0;
    virtual const ABC_Value* parentValue()const =0;

    virtual void setParentValue(ABC_Value* par)=0;

    virtual std::string ith_ChildName(std::size_t i)const=0;

    virtual const ABC_Value* idToValue(const std::string& name)const=0;
    virtual ABC_Value* idToValue(const std::string &name)=0;
    virtual bool removeChild(const std::string& name)=0;


    virtual const ABC_Value* idToValue(const std::string& name,const std::string& kind)const=0;
    virtual ABC_Value* idToValue(const std::string &name, const std::string &kind) =0;

    virtual void pushChild(ABC_Value* var)=0;


    //TODO: probably remove putOut and PutErrorOut and state explicitely the IO
    virtual void putOut(const std::string& m)const=0;
    virtual void putErrorOut(const std::string& m)const=0;


    virtual ~ABC_Value();
    virtual bool isInDomain(const ABC_Value* value)const=0;

    virtual void reset()=0;

    virtual void setTip(const std::string& tip)=0;
    virtual void setWhatThis(const std::string& whatThis)=0;



    //*****************************************************************
    //                        virtual methods
    //******************************************************************

    virtual bool processTokens(Token_Stream& t)=0;
    /// si myClass==SomeClass::ClassName()  => static_cast<SomeClass*>(this)!=nullptr
    virtual std::string myClass() const;


    virtual bool setThisValue(Token_New tok,std::string& error)=0;

    virtual std::set<std::string> alternativeValues()const=0;




    virtual std::set<std::string> mySuperClasses() const;

    /// si complyClass(SomeClass::ClassName())  => static_cast<SomeClass*>(this)!=nullptr
    virtual bool complyClass(const std::string classname)const ;

    virtual bool complyVar(const std::string& var,std::string * errormessage=nullptr)const;


    virtual std::string toString()const;   //

    virtual std::ostream& put(std::ostream& s) const;





    //*****************************************************************
    //                    non-virtual methods
    //******************************************************************



    /// it uses the information in source to build a fully formed
    /// object
    /// Invariant *this==parentValue()->getChild(myVar())->cloneFromValue(getValueFromStream(this->toTokens));
    ///
    ABC_Value* toIndicatedVar(const ABC_Value *source) const;



    ABC_Measure* getMeasureFromValue(ABC_Value * v);

    bool has_child(const std::string& name)const;

    std::set<std::__cxx11::string> getListComplying(const std::string& var)const;

    std::set<std::__cxx11::string> getDataList()const;
    std::set<std::__cxx11::string> getVarList()const;
    std::set<std::__cxx11::string> getCommandList()const;

    virtual std::set<std::__cxx11::string> getChildList(valuePredicate P)const;
    virtual std::set<std::__cxx11::string> getChildList(valueStringPredicate P,const std::string& name)const;

    void pushIdChild(const std::string& id,ABC_Value* var);



    // ********************************************************
    //                Template public methods
    //***********************************************************


  public:

    template<typename T>
    bool getVal(const std::string& name, T& value)const;


    template<typename T>
    bool moveVal(const std::string& name, T& value);


    template<typename T>
    bool checkValue(const std::string& varName, T& value, std::string& errorMessage)const;


    template<typename T>
    T& getReference(const std::string& name, T& value);

    template<typename T>
    void push_backVal(const std::string& name,
                      T value,
                      const std::string& classname="",
                      const std::string& tip="",
                      const std::string & whatthis="");

    void push_backVarRef(const std::string& name,
                         const std::string& idRef,
                         const std::string& classname="",
                         const std::string& tip="",
                         const std::string & whatthis="");



    template<typename T>
    bool replaceValue(const std::string& name, const T& value);

    template<typename Enum>
    void push_back_CategoryItem(const std::string & name,
                                Enum i,
                                const std::string& tip="",
                                const std::string & whatthis="");






    //******************************************************************
    //              protected Abstract methods
    //******************************************************************


  protected:
    virtual ABC_Var* toSameVar(const ABC_Value* source)const=0;


    virtual ABC_Measure* toMeasure(const ABC_Value* source)const=0;


    virtual ABC_Var* toPlainSameVar()const=0;


    virtual ABC_Measure* toPlainMeasure()const=0;






    //******************************************************************
    //              protected static members
    //******************************************************************



  protected:



  };






  class Implements_ValueId:  public ABC_Value
  { // ABC_Var interface
  public:

    virtual ABC_Value* create()const override;

    virtual Implements_ValueId* clone() const override;
    virtual void reset() override;






    virtual std::string myVar() const override;

    virtual void setVar(const std::string& varname)override;

    virtual Token_Stream toTokens() const override;

    virtual bool processTokens( Token_Stream& tok) override;

    virtual std::string id()const override;
    virtual void setId(const std::string& IdName)override;

    virtual std::string Tip()const override;
    virtual std::string WhatThis()const override;
    virtual void setTip(const std::string& tip)override;
    virtual void setWhatThis(const std::string& whatThis)override;

    bool isRootedVariable()const override;

    bool isMyParent(const ABC_Value* aParent) const override;
    const ABC_Value *parentValue() const override;
    virtual std::size_t numChilds() const override;
    virtual std::string ith_ChildName(std::size_t) const override;
    virtual const ABC_Value* idToValue(const std::string& idName)const override;
    virtual ABC_Value* idToValue(const std::string &) override;

    virtual bool removeChild(const std::string& ) override;
    virtual const ABC_Value* idToValue(const std::string&idName, const std::string&varName)const  override;
    virtual ABC_Value* idToValue(const std::string &, const std::string &) override;
    virtual void pushChild  (ABC_Value *) override;

    virtual std::string refId()const override;

    //TODO: there are two concepts here: the current holder of the id in parent and the var that is pointed by myVar
    virtual ABC_Var* myVarPtr(ABC_Value* parent) const override;
    virtual const ABC_Value* myVarPtr() const  override;


    virtual bool complyModes(const std::string m)const override;
    virtual std::set<std::string> modes()const override;
  protected:
    virtual void setParentValue(ABC_Value *par)override;
  public:
    virtual bool isInDomain(const ABC_Value* value)const override;
    Implements_ValueId(const std::string& name,
                       const std::string& className,
                       const std::string &tip,
                       const std::string &whatthis);

    Implements_ValueId(const ABC_Value& other);

    Implements_ValueId()=default;
    Implements_ValueId(const Implements_ValueId& other)=default;
    Implements_ValueId& operator=(const Implements_ValueId& other)=default;

    Implements_ValueId(Implements_ValueId&& other)=default;
    Implements_ValueId& operator=(Implements_ValueId&& other)=default;

    virtual ~Implements_ValueId();


    virtual void putOut(const std::string& m)const;
    virtual void putErrorOut(const std::string& m)const;


    virtual ABC_Value* to_PlainValue() const override;
    virtual ABC_Value* to_PlainValue(const ABC_Measure* )const override;

    virtual ABC_Value* toMeasure(const ABC_Value* )const override;


    virtual ABC_Var* toSameVar(const ABC_Value* )const override;


    virtual ABC_Value* toPlainMeasure()const override;


    virtual ABC_Var* toPlainSameVar()const override;


  protected:

    std::string id_;
    std::string var_;
    const ABC_Value* p_;
    std::string tip_;
    std::string whatThis_;


    // ABC_Value interface
  public:
    virtual bool empty() const override
    {
      return id_.empty();
    }
    virtual void clear() override
    {

    }

    // ABC_Value interface
  public:
    virtual bool isValueOfThisVar(const ABC_Value *v) const override
    {
      if (v->myVar()==id())
        return true;
      else
        return false;
    }

    // ABC_Value interface
  public:
    virtual bool setThisValue(Token_New tok, std::string &error) override
    {
      error=id()+"is a "+myClass()+": it cannot be set with a single token";
      return false;
    }

    virtual std::set<std::string> alternativeValues()const override
    {
      return {};

    }
  };



  template<typename T>
  class Implements_Simple_Class;



  template<typename T>
  class ABC_Simple_Value;

  template<typename T>
  class ABC_Simple_Class//:  public Implements_ValueId
  {
  public:

    //    static std::string ClassName();

    //    static std::set<std::string> SuperClasses()
    //    {
    //      return ABC_Value::SuperClasses()+ClassName();
    //    }

    //    virtual std::set<std::string> mySuperClasses()const override
    //    {
    //      return SuperClasses();
    //    }

    virtual T defaultValue()const=0;
    virtual T minValue()const=0;
    virtual T maxValue()const=0;
    virtual T emptyValue()const=0;
    virtual T unknownValue()const=0;
    virtual void setDefaultValue(T val)=0;
    virtual void setminValue(T val)=0;
    virtual void setmaxValue(T val)=0;

    virtual bool checkValue(const T& val, std::string& error_message)const=0;


    virtual std::string units()const=0;
    virtual void setUnits(std::string newunits)=0;



    //    virtual bool complyModes(const std::string mode)const override=0;

    //    virtual std::set<std::string> modes()const override=0;
    virtual ~ABC_Simple_Class(){}
  };




  template<typename T>
  class ABC_Simple_Value: public  Implements_ValueId
  {
    // ABC_Var interface
  public:
    ABC_Simple_Value(const std::string& name,
                     const std::string& className,
                     const std::string &tip,
                     const std::string &whatthis):
      Implements_ValueId(name,className,tip,whatthis){}

    ABC_Simple_Value():Implements_ValueId(){}



    virtual T value()const=0;
    virtual void setValue(T val)=0;
    virtual void moveVal(T& ){}

    virtual const T& refval()const=0;

    virtual T& refval()=0;

    virtual bool checkValue(const T& val, std::string& error)const=0;


    static std::set<std::string> SuperClasses()
    {
      return ABC_Value::SuperClasses()+ClassName();
    }

    static std::string ClassName()
    {
      return "Simple_Value";
    }




    virtual const ABC_Simple_Class<T>* motherClassType()const
    {
      return dynamic_cast<const ABC_Simple_Class<T>*> (myVarPtr());
    }

    virtual  ABC_Simple_Class<T>* motherClassType(ABC_Value* v)
    {
      return dynamic_cast<ABC_Simple_Class<T>*> (myVarPtr(v));
    }


    virtual ~ABC_Simple_Value(){}

  };






  template<typename T>
  class Implements_Simple_Value: public ABC_Simple_Value<T>
  {
    // ABC_Var interface
  public:

    static std::string ClassName();

    static std::set<std::string> SuperClasses()
    {
      return ABC_Simple_Value<T>::SuperClasses()+ClassName();
    }

    virtual std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }

    virtual Implements_Simple_Value<T>* create() const override
    {
      return new Implements_Simple_Value<T>();
    }

    virtual Implements_Simple_Value<T>* clone() const override
    {
      return new Implements_Simple_Value<T>(*this);
    }

    virtual void reset() override
    {
      if ((this->parentValue()!=nullptr)&&(!this->isRootedVariable()))
        {
          auto s=dynamic_cast<const Implements_Simple_Value<T>*>(this->parentValue()->idToValue(this->id()));
          if (s!=nullptr)
            *this=*s;

        }
    }
    virtual  T value()const override
    {
      return value_;
    }

    virtual void moveVal(T& val)
    {
      val=std::move(value_);
      empty_=true;
    }

    virtual void setValue(T val) override
    {
      value_=std::move(val);
      empty_=false;
    }
    virtual const T& refval()const override
    {
      return value_;
    }
    virtual T& refval() override
    {
      return value_;
    }

    virtual Token_Stream toTokens() const override
    {
      Token_Stream out=Implements_ValueId::toTokens();
      out.getToken()<<"="<<value()<<"\n";
      return out;
    }



    bool processTokens( Token_Stream& t) override
    {
      bool out=Implements_ValueId::processTokens(t);
      if (!out)
        return out;
      else
        {
          t.tokenAdvance(2);
          if (t.currToken().tok()!=Token_New::ASSIGN)
            {
              return false;
            }
          ++t;
          T val;
          if (!toValue(t,val))
            {
              return false;
            }
          else
            {
              setValue(val);
              if (t.currToken().tok()==Token_New::EOL)
                ++t;
              return true;
            }
        }
    }
    // ABC_Var interface


    Implements_Simple_Value(std::string id,
                            T val,
                            std::string className,
                            const std::string& tip="",
                            const std::string& whatthis=""):
      ABC_Simple_Value<T>(id,className,tip,whatthis),
      value_(val),empty_(false){}


    Implements_Simple_Value(bool,
                            std::string id,
                            std::string className,
                            const std::string& tip="",
                            const std::string& whatthis=""):
      ABC_Simple_Value<T>(id,className,tip,whatthis),
      value_{},empty_(true){}



    Implements_Simple_Value():
      ABC_Simple_Value<T>(),
      value_(),empty_(true){}

    Implements_Simple_Value(const Implements_ValueId& id):
      ABC_Simple_Value<T>(id.id(),id.myVar(),id.Tip(),id.WhatThis()),
      value_(),empty_(true){}


    Implements_Simple_Value(const Implements_Simple_Value<T>& other)=default;

    Implements_Simple_Value(Implements_Simple_Value<T>&& other)=default;

    Implements_Simple_Value& operator=(const Implements_Simple_Value<T>& other)=default;
    /* {
        if (this!=&other)
          *this=Implements_Simple_Value<T>(other);
        return *this;
      }
  */
    Implements_Simple_Value& operator=(Implements_Simple_Value<T>&& other)=default;

    virtual ~Implements_Simple_Value(){}

    virtual Implements_Simple_Value<T>* to_PlainValue()const  override
    {
      return clone();
    }

    bool empty()const override
    {
      return empty_;
    }

    void clear()override
    {
      value_=T{};
      empty_=true;

    }


  protected:


    T value_;
    bool empty_;


    // ABC_Simple_Value interface
  public:
    virtual bool checkValue(const T &val, std::string& error) const override
    {
      if (this->motherClassType()!=nullptr)
        return this->motherClassType()->checkValue(val,error);
      else
        return true;
    }



    // ABC_Value interface
  public:
    virtual std::set<std::string> alternativeValues()const override
    {
      if (this->myVarPtr()!=nullptr)
        return this->myVarPtr()->alternativeValues();
      else
        return {};

    }
    virtual bool setThisValue(Token_New tok, std::string &error) override
    {
      error=tok.str()+" is not of "+ClassName();
      return false;
    }
  };


  template<>
  std::string Implements_Simple_Value<int>::ClassName();

  template<>
  std::string Implements_Simple_Value<std::string>::ClassName();


  template<>
  inline
  bool Implements_Simple_Value<int>::setThisValue(Token_New tok, std::string& error)
  {
    int v;
    if (tok.toValue(v))
      {
        if (checkValue(v,error))
          {
            setValue(v);
            return true;
          }
        else return false;
      }
    else
      {
        error=tok.str()+" is not of "+ClassName();
        return false;
      }
  }


  template<>
  inline
  bool Implements_Simple_Value<std::string>::setThisValue(Token_New tok, std::string& error)
  {
    std::string s;
    if (tok.toValue(s))
      {
        if (checkValue(s,error))
          {
            setValue(s);
            return true;
          }
        else return false;
      }
    else
      {
        error=tok.str()+" is not of "+ClassName();
        return false;
      }
  }







  class Implements_Complex_Value:  public  Implements_ValueId
  {
    // ABC_Var interface
  public:
    static std::string ClassName();
    virtual Implements_Complex_Value* create() const override;
    virtual Implements_Complex_Value* clone() const override;
    virtual void reset() override;

    virtual std::size_t numChilds() const override;
    virtual std::string ith_ChildName(std::size_t i) const override;

    virtual  std::set<std::string>
    getChildList(valuePredicate P) const override;
    virtual std::set<std::string>
    getChildList(valueStringPredicate P,const std::string& name)const override;


    virtual const ABC_Value* idToValue(const std::string& name)const override;
    virtual  ABC_Value* idToValue(const std::string& name)override;



    virtual ABC_Value* popLastChild();



    virtual bool removeChild(const std::string& name)override;

    virtual const ABC_Value* idToValue(const std::string& name,
                                       const std::string &myclass)const override;
    virtual ABC_Value* idToValue(const std::string& name, const std::string &myclass) override;
    virtual void pushChild(ABC_Value *var) override;



    Implements_Complex_Value(
        const std::string& id,
        const std::string className,
        const std::string & tip,
        const std::string& whatthis,
        const std::vector<std::pair<std::string,std::string>>& childsNameClass={});


    Implements_Complex_Value(const ABC_Value& other);



    Implements_Complex_Value()=default;


    Implements_Complex_Value(const Implements_Complex_Value& other);

    Implements_Complex_Value(Implements_Complex_Value&& other);

    Implements_Complex_Value& operator=(Implements_Complex_Value&& other);




    Implements_Complex_Value& operator=(const Implements_Complex_Value& other);

    void privateDelete();


    virtual ~Implements_Complex_Value();

    virtual Token_Stream toTokens() const override;

    virtual bool processTokens( Token_Stream& t) override;



    virtual ABC_Value* toPlainMeasure()const override;


    virtual ABC_Var* toPlainSameVar()const override;





    virtual ABC_Value* to_PlainValue()const override;
    //    virtual bool loadFromObjectValue(const ABC_Value* source)override
    //    {
    //      if (sameFields(source))
    //        {
    //          *this=Implements_Complex_Value(*source);
    //          return true;
    //        }
    //      else
    //        return false;
    //    }

  protected:
    void cloneChids();

    void resetChildsParent();
    std::vector<std::string> ids_;
    std::map<std::string,ABC_Value*> vars_;


    // ABC_Value interface
  public:
    virtual bool empty() const override
    {
      for (auto& p:vars_)
        {
          if ((p.second!=nullptr)&&(!p.second->empty()))
            return false;
        }
      return true;
    }
    virtual void clear() override
    {
      for (auto& p:vars_)
        {
          if (p.second!=nullptr)
            p.second->clear();
        }

    }
  };





  template<class C>
  class ABCObject // :  virtual public Implements_ValueId
  {
    // ABC_Var interface
  public:
    virtual C* getObject() =0;

    virtual const C* getObject()const =0;
    virtual void setObject(C** obj)=0;


    virtual ~ABCObject(){}
  };



  template<class C,typename T>
  class Implements_ValMethod_Var: public ABC_Simple_Value<T>, public ABCObject<C>
  {
    // ABC_Var interface
  public:
    static std::string ClassName()
    {
      return C::ClassName()+"_method";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Value::SuperClasses()+ClassName();
    }

    virtual std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }

    virtual Implements_ValMethod_Var<C,T>* create() const override
    {
      return new Implements_ValMethod_Var<C,T>;
    }

    virtual Implements_ValMethod_Var<C,T>* clone() const override
    {
      return new Implements_ValMethod_Var<C,T>(*this);
    }




    virtual void reset() override
    {
      if ((this->parentValue()!=nullptr)&&(!this->isRootedVariable()))
        {
          auto s=dynamic_cast<const Implements_ValMethod_Var<C,T>*>(this->parentValue()->idToValue(this->id()));
          if (s!=nullptr)
            *this=*s;

        }
    }
    virtual C* getObject() override
    {
      if (objectPtr_!=nullptr)
        return *objectPtr_;
      else
        return nullptr;
    }

    virtual const C* getObject()const override
    {
      if (objectPtr_!=nullptr)
        return *objectPtr_;
      else
        return nullptr;
    }
    virtual void setObject(C** obj) override
    {
      objectPtr_=obj;
    }


    virtual T& refval() override
    {
      return empty_;
    }

    virtual const T& refval() const override
    {
      return empty_;
    }

    T value()const override
    {
      if ((this->getObject()==nullptr))
        return empty_;
      if (get_!=nullptr)
        return (this->getObject()->*get_)();
      else
        return empty_;
    }

    void setValue(T val) override
    {
      if ((this->getObject()!=nullptr)&& (set_!=nullptr))
        ((this->getObject()->*set_))(val);

    }



    Token_Stream toTokens() const override
    {
      auto out=Implements_ValueId::toTokens();
      out.getToken()<<"="<<value()<<"\n";
      return out;
    }

    bool processTokens( Token_Stream&  t) override
    {
      if (!Implements_ValueId::processTokens(t))
        return false;
      else
        {
          t.tokenAdvance(2);
          if (t.currToken().tok()!=Token_New::ASSIGN)
            return false;
          ++t;
          T val{};
          if (!toValue(t,val))
            return false;
          else
            {
              setValue(val);
              if (t.currToken().tok()==Token_New::EOL)
                ++t;
              return true;
            }
        }
    }



    // ABC_Var interface

    Implements_ValMethod_Var(std::string id,
                             C** objectPtr,
                             getter<C,T> getterMethod,
                             setter<C,T> setterMethod,
                             std::string className=ClassName(),
                             const std::string& tip="",
                             const std::string& whatthis=""):
      ABC_Simple_Value<T>(id,className,tip,whatthis),
      objectPtr_(objectPtr),
      get_(getterMethod),
      set_(setterMethod)
    {}



    Implements_ValMethod_Var()=default;


    Implements_ValMethod_Var(const Implements_ValMethod_Var<C,T>& other)=default;


    Implements_ValMethod_Var(Implements_ValMethod_Var<C,T>&& other)=default;




    Implements_ValMethod_Var& operator=( Implements_ValMethod_Var<C,T>&& other)=default;


    Implements_ValMethod_Var& operator=(const Implements_ValMethod_Var<C,T>& other)=default;

    virtual ~Implements_ValMethod_Var(){}

    virtual Implements_Simple_Value<T>* to_PlainValue()const  override
    {
      return new Implements_Simple_Value<T>(this->id(),this->value(),this->myVar(),this->Tip(), this->WhatThis());
    }







    //    virtual bool loadFromObjectValue(const ABC_Value* var) override
    //    {
    //      if ((var!=nullptr)&&(this->id()==var->id()))
    //        {
    //          auto o=dynamic_cast<const ABC_Simple_Value<T>*>(var);
    //          if(o!=nullptr)
    //            {
    //              setValue(o->value());
    //              if (!o->Tip().empty())
    //                this->setTip(o->Tip());
    //              if (!o->WhatThis().empty())
    //                this->setWhatThis(o->WhatThis());
    //              return true;
    //            }
    //          else
    //            return false;
    //        }
    //      else
    //        return false;
    //    }
  protected:
    C** objectPtr_;
    getter<C,T> get_;
    setter<C,T> set_;
    T empty_=T();

    // ABC_Value interface
  public:
    virtual bool empty() const override
    {
      return (get_==nullptr)&&(set_==nullptr);
    }
    virtual void clear() override
    {
      objectPtr_=nullptr;
      get_=nullptr;
      set_=nullptr;

    }

    // ABC_Simple_Value interface
  public:
    virtual bool checkValue(const T &val,std::string& error) const override
    {
      if (this->motherClassType()!=nullptr)
        return this->motherClassType()->checkValue(val,error);
      else
        return true;

    }
  };



  template<class C,typename T>
  class Implements_PointerMember_Var: public ABC_Simple_Value<T>, public ABCObject<C>
  {
    // ABC_Var interface
  public:
    static std::string ClassName()
    {
      return C::ClassName()+"_method";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Value::SuperClasses()+ClassName();
    }

    virtual std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }

    virtual Implements_PointerMember_Var<C,T>* create() const override
    {
      return new Implements_PointerMember_Var<C,T>;
    }

    virtual Implements_PointerMember_Var<C,T>* clone() const override
    {
      return new Implements_PointerMember_Var<C,T>(*this);
    }

    virtual C* getObject() override
    {
      if (objectPtr_!=nullptr)
        return *objectPtr_;
      else
        return nullptr;
    }

    virtual const C* getObject()const override
    {
      if (objectPtr_!=nullptr)
        return *objectPtr_;
      else
        return nullptr;
    }
    virtual void setObject(C** obj) override
    {
      objectPtr_=obj;
    }


    virtual T& refval() override
    {
      return empty_;
    }

    virtual const T& refval() const override
    {
      return empty_;
    }

    T value()const override
    {
      if ((this->getObject()==nullptr))
        return empty_;
      if (m_!=nullptr)
        return this->getObject()->*m_;
      else
        return empty_;
    }

    void moveVal(T &val)  override
    {
      return  val;
    }


    void setValue(T val) override
    {
      if ((this->getObject()!=nullptr)&& (m_!=nullptr))
        (this->getObject()->*m_)=val;

    }



    Token_Stream toTokens() const override
    {
      auto out=Implements_ValueId::toTokens();
      out<<"="<<toToken(value())<<"\n";
      return out;
    }

    bool processTokens(Token_Stream& t) override
    {
      if (!Implements_ValueId::processTokens(t))
        return false;
      else
        {
          if (t.currToken().tok()!=Token_New::ASSIGN)
            return false;
          ++t;
          T val{};
          if (!toValue(t,val))
            return false;
          else
            {
              setValue(val);
              if (t.currToken().tok()==Token_New::EOL)
                ++t;
              return true;
            }
        }
    }



    // ABC_Var interface


    Implements_PointerMember_Var(std::string id,
                                 C** objectPtr,
                                 T C::* memberPointer,
                                 std::string className=ClassName(),
                                 const std::string& tip="",
                                 const std::string& whatthis=""):
      Implements_ValueId(id,className,tip,whatthis),
      objectPtr_(objectPtr),
      m_(memberPointer)
    {}


    Implements_PointerMember_Var()=default;


    Implements_PointerMember_Var(const Implements_PointerMember_Var<C,T>& other)=default;


    Implements_PointerMember_Var(Implements_PointerMember_Var<C,T>&& other)=default;




    Implements_PointerMember_Var& operator=( Implements_PointerMember_Var<C,T>&& other)=default;


    Implements_PointerMember_Var& operator=(const Implements_PointerMember_Var<C,T>& other)=default;

    virtual ~Implements_PointerMember_Var(){}

    virtual Implements_Simple_Value<T>* to_PlainValue()const  override
    {
      return new Implements_Simple_Value<T>(
            nullptr,this->id(),this->value(),this->myVar(),this->Tip(), this->WhatThis());
    }

    //    virtual bool loadFromObjectValue(const ABC_Value* var) override
    //    {
    //      if ((var!=nullptr)&&(this->id()==var->id()))
    //        {
    //          auto o=dynamic_cast<const ABC_Simple_Value<T>*>(var);
    //          if(o!=nullptr)
    //            {
    //              setValue(o->value());
    //              if (!o->Tip().empty())
    //                this->setTip(o->Tip());
    //              if (!o->WhatThis().empty())
    //                this->setWhatThis(o->WhatThis());
    //              return true;
    //            }
    //          else
    //            return false;
    //        }
    //      else
    //        return false;
    //    }
  protected:
    C** objectPtr_;
    T C::* m_;
    T empty_=T();


    // ABC_Value interface
  public:
    virtual bool empty() const override
    {
      return m_==nullptr;
    }
    virtual void clear() override
    {
      m_=nullptr;
    }
  };


  template<class C,typename T>
  class Implements_RefMethod_Var: public ABC_Simple_Value<T>, public ABCObject<C>
  {
    // ABC_Var interface
  public:
    static std::string ClassName()
    {
      return C::ClassName()+"_method";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Value::SuperClasses()+ClassName();
    }

    virtual std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }

    virtual Implements_RefMethod_Var<C,T>* create() const override
    {
      return new Implements_RefMethod_Var<C,T>;
    }

    virtual Implements_RefMethod_Var<C,T>* clone() const override
    {
      return new Implements_RefMethod_Var<C,T>(*this);
    }

    virtual C* getObject() override
    {
      if (objectPtr_!=nullptr)
        return *objectPtr_;
      else
        return nullptr;
    }

    virtual const C* getObject()const override
    {
      if (objectPtr_!=nullptr)
        return *objectPtr_;
      else
        return nullptr;
    }
    virtual void setObject(C** obj) override
    {
      objectPtr_=obj;
    }


    virtual T& refval() override
    {
      if ((this->getObject()==nullptr))
        return empty_;
      if (rget_!=nullptr)
        return (this->getObject()->*rset_)();
      else
        return empty_;
    }

    virtual const T& refval() const override
    {
      if ((this->getObject()==nullptr))
        return empty_;
      if (rget_!=nullptr)
        return (this->getObject()->*rget_)();
      else
        return empty_;
    }

    T value()const override
    {
      if ((this->getObject()==nullptr))
        return empty_;
      else if (rget_!=nullptr)
        return (this->getObject()->*rget_)();
      else
        return empty_;
    }




    void setValue(T val) override
    {
      if ((this->getObject()!=nullptr)&& (rset_!=nullptr))
        (this->getObject()->*rset_)()=val;

    }


    Token_Stream toTokens() const override
    {
      auto out=Implements_ValueId::toTokens();
      out.getToken()<<"="<<value()<<"\n";
      return out;
    }

    bool processTokens( Token_Stream& t) override
    {
      if (!Implements_ValueId::processTokens(t))
        return false;
      else
        {
          t.tokenAdvance(2);
          if (t.currToken().tok()!=Token_New::ASSIGN)
            return false;
          ++t;
          T val{};
          if (!toValue(t,val))
            return false;
          else
            {
              setValue(val);
              if (t.currToken().tok()==Token_New::EOL)
                ++t;
              return true;
            }
        }
    }



    // ABC_Var interface

    Implements_RefMethod_Var(std::string id,
                             C** object,
                             refgetter<C,T> refgetterMethod,
                             refsetter<C,T> refsetterMethod,
                             std::string className=ClassName(),
                             const std::string& tip="",
                             const std::string& whatthis=""):
      ABC_Simple_Value<T>(id,className,tip,whatthis),
      objectPtr_(object),
      rget_(refgetterMethod),
      rset_(refsetterMethod){}


    Implements_RefMethod_Var()=default;


    Implements_RefMethod_Var(const Implements_RefMethod_Var<C,T>& other)=default;


    Implements_RefMethod_Var(Implements_RefMethod_Var<C,T>&& other)=default;




    Implements_RefMethod_Var& operator=( Implements_RefMethod_Var<C,T>&& other)=default;


    Implements_RefMethod_Var& operator=(const Implements_RefMethod_Var<C,T>& other)=default;

    virtual ~Implements_RefMethod_Var(){}


    virtual Implements_Simple_Value<T>* to_PlainValue()const  override
    {
      return new Implements_Simple_Value<T>(this->id(),this->value(),this->myVar(),this->Tip(), this->WhatThis());
    }

    //    virtual bool loadFromObjectValue(const ABC_Value* var) override
    //    {
    //      if ((var!=nullptr)&&(this->id()==var->id()))
    //        {
    //          auto o=dynamic_cast<const ABC_Simple_Value<T>*>(var);
    //          if(o!=nullptr)
    //            {
    //              setValue(o->value());
    //              if (!o->Tip().empty())
    //                this->setTip(o->Tip());
    //              if (!o->WhatThis().empty())
    //                this->setWhatThis(o->WhatThis());
    //              return true;
    //            }
    //          else
    //            return false;
    //        }
    //      else
    //        return false;
    //    }
    // ABC_Value interface
  public:
    virtual bool empty() const override
    {
      return (rget_==nullptr)&&(rset_==nullptr);
    }
    virtual void clear() override
    {
      rget_=nullptr;
      rset_=nullptr;
    }


  protected:
    C** objectPtr_;
    refgetter<C,T> rget_;
    refsetter<C,T> rset_;
    T empty_=T();



    // ABC_Simple_Value interface
  public:
    virtual bool checkValue(const T &val, std::string& error) const override
    {
      if (this->motherClassType()!=nullptr)
        return this->motherClassType()->checkValue(val,error);
      else
        return true;

    }
  };



  template<class C,typename Enum>
  class Implements_EnumMethod_Var: public ABC_Simple_Value<Enum>, public ABCObject<C>
  {
    // ABC_Var interface
  public:
    static std::string ClassName();

    static std::set<std::string> SuperClasses()
    {
      return ABC_Value::SuperClasses()+ClassName();
    }

    virtual std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }

    virtual Implements_EnumMethod_Var<C,Enum>* create() const override
    {
      return new Implements_EnumMethod_Var<C,Enum>;
    }

    virtual Implements_EnumMethod_Var<C,Enum>* clone() const override
    {
      return new Implements_EnumMethod_Var<C,Enum>(*this);
    }

    virtual C* getObject() override
    {
      if (objectPtr_!=nullptr)
        return *objectPtr_;
      else
        return nullptr;
    }

    virtual const C* getObject()const override
    {
      if (objectPtr_!=nullptr)
        return *objectPtr_;
      else
        return nullptr;
    }
    virtual void setObject(C** obj) override
    {
      objectPtr_=obj;
    }


    virtual Enum& refval() override
    {
      return empty_;
    }

    virtual const Enum& refval() const override
    {
      return empty_;
    }

    Enum value()const override
    {
      if ((this->getObject()==nullptr))
        return empty_;
      if (get_!=nullptr)
        return (this->getObject()->*get_)();
      else
        return empty_;
    }

    void setValue(Enum val) override
    {
      if ((this->getObject()!=nullptr)&& (set_!=nullptr))
        ((this->getObject()->*set_))(val);

    }

    bool setCategory(std::string cat)
    {
      auto it=strToEnum.find(cat);
      if (it!=strToEnum.end())
        {
          setValue(it->second);
          return true;
        }
      else
        return false;
    }

    std::string Category()const
    {
      Enum i=value();
      for (auto& e:strToEnum)
        {
          if (e.second==i)
            return e.first;
        }
      return {};
    }


    Token_Stream toTokens() const override
    {
      auto out=Implements_ValueId::toTokens();
      out.getToken()<<"="<<Category()<<"\n";
      return out;
    }

    bool processTokens(Token_Stream& t) override
    {
      if (!Implements_ValueId::processTokens(t))
        return false;
      else
        {
          t.tokenAdvance(2);
          if (t.currToken().tok()!=Token_New::ASSIGN)
            return false;
          ++t;
          std::string val{};
          if (!toValue(t,val))
            return false;
          else if (!setCategory(val))
            return false;
          else
            {
              if (t.currToken().tok()==Token_New::EOL)
                ++t;
              return true;
            }
        }
    }



    // ABC_Var interface

    Implements_EnumMethod_Var(std::string id,
                              C** objectPtr,
                              getter<C,Enum> getterMethod,
                              setter<C,Enum> setterMethod,
                              std::string className=ClassName(),
                              const std::string& tip="",
                              const std::string& whatthis=""):
      ABC_Simple_Value<Enum>(id,className,tip,whatthis),
      objectPtr_(objectPtr),
      get_(getterMethod),
      set_(setterMethod)
    {}



    Implements_EnumMethod_Var()=default;


    Implements_EnumMethod_Var(const Implements_EnumMethod_Var<C,Enum>& other)=default;


    Implements_EnumMethod_Var(Implements_EnumMethod_Var<C,Enum>&& other)=default;




    Implements_EnumMethod_Var& operator=( Implements_EnumMethod_Var<C,Enum>&& other)=default;


    Implements_EnumMethod_Var& operator=(const Implements_EnumMethod_Var<C,Enum>& other)=default;

    virtual ~Implements_EnumMethod_Var(){}

    typedef Implements_EnumMethod_Var<C,Enum> CC;
    virtual void reset() override
    {
      if ((this->parentValue()!=nullptr)&&(!this->isRootedVariable()))
        {
          auto s=dynamic_cast<const Implements_EnumMethod_Var<C,Enum>*>(this->parentValue()->idToValue(this->id()));
          if (s!=nullptr)
            *this=*s;

        }
    }

    virtual Implements_Simple_Value<std::string>* to_PlainValue()const  override
    {
      return new Implements_Simple_Value<std::string>(this->id(),this->Category(),this->myVar(),this->Tip(), this->WhatThis());
    }

    //    virtual bool loadFromObjectValue(const ABC_Value* var) override
    //    {
    //      if ((var!=nullptr)&&(this->id()==var->id()))
    //        {
    //          auto o=dynamic_cast<const ABC_Simple_Value<std::string>*>(var);
    //          if(o!=nullptr)
    //            {

    //              setCategory(o->value());
    //              if (!o->Tip().empty())
    //                this->setTip(o->Tip());
    //              if (!o->WhatThis().empty())
    //                this->setWhatThis(o->WhatThis());
    //              return true;
    //            }
    //          else
    //            return false;
    //        }
    //      else
    //        return false;
    //    }

    // ABC_Value interface
  public:
    virtual bool empty() const override
    {
      return (get_==nullptr)&&(set_==nullptr)&&strToEnum.empty();
    }
    virtual void clear() override
    {
      get_=nullptr;
      set_=nullptr;
      strToEnum.clear();
    }

  protected:
    C** objectPtr_;
    getter<C,Enum> get_;
    setter<C,Enum> set_;
    Enum empty_=Enum();
    static std::map<std::string,Enum> strToEnum;

    // ABC_Simple_Value interface
  public:
    virtual bool checkValue(const Enum &, std::string& error) const override
    {
      return true;
    }
  };



  template<typename Enum>
  class Implements_Categorical: public Implements_Simple_Value<std::string>
  {
  public:
    static std::string ClassName()
    {
      return "Category";
    }

    static std::set<std::string> SuperClasses();

    virtual std::set<std::string> mySuperClasses() const override;


    // ABC_Var interface
  public:
    std::string Category()const;

    Enum Rank()const;

    void updateCat();
    void updateRank();

    void setCategory(const std::string& cat);

    void setRank(Enum i);

    Implements_Categorical( const std::string& idName,Enum i,
                            const std::string& tip="",
                            const std::string & whatthis="");
    Implements_Categorical(const std::string& idName,
                           const std::string &cat,
                           const std::string& tip="",
                           const std::string & whatthis="");



    virtual const Implements_Categorical* myVarPtr()const override;
    virtual Implements_Categorical* myVarPtr(ABC_Value* aParent) const override;


    virtual Implements_Categorical<Enum> *to_PlainValue() const override;

    typedef Implements_Categorical<Enum> C;
    virtual void reset() override
    {
      if ((parentValue()!=nullptr)&&(!isRootedVariable()))
        {

          auto r=dynamic_cast<const C*>(parentValue()->idToValue(id()));
          if (r!=nullptr)
            *this=*r;

        }

    }



  private:
    static std::map<std::string,Enum> strToEnum;
    Enum rank_;
  };






  template <class C>
  class Implements_Class_Reflection: public Implements_Complex_Value, public ABCObject<C>
  {
    // ABC_Var interface
  public:
    static std::string ClassName()
    {
      return C::ClassName()+"_reflection";
    }


    virtual C* getObject() override
    {
      return object_;
    }

    virtual const C* getObject()const override
    {
      return object_;
    }
    virtual void setObject(C** obj) override
    {
      object_=*obj;
    }


    virtual Implements_Class_Reflection<C>* create() const override
    {
      return new Implements_Class_Reflection<C>();
    }

    virtual Implements_Class_Reflection<C>* clone() const override
    {
      return new Implements_Class_Reflection<C>(*this);
    }

    virtual void reset() override
    {
      if ((parentValue()!=nullptr)&&(!isRootedVariable()))
        {
          auto s=dynamic_cast<const Implements_Class_Reflection<C>*>(parentValue()->idToValue(id()));
          if (s!=nullptr)
            *this=*s;

        }
    }



  protected:
    template<typename T>
    void push_backVarPointer(const std::string& name,
                             T C::* value,
                             const std::string& classname="",
                             const std::string& tip="",
                             const std::string & whatthis="");

    template<typename T>
    void push_backValMethod(const std::string& name,
                            getter<C,T> getmethod,
                            setter<C,T> setmethod,
                            const std::string& classname="",
                            const std::string& tip="",
                            const std::string & whatthis="");

    template<typename Enum>
    void push_backEnumValMethod(const std::string& name,
                                getter<C,Enum> getmethod,
                                setter<C,Enum> setmethod,
                                const std::string& classname="",
                                const std::string& tip="",
                                const std::string & whatthis="");

    template<typename T>
    void push_backRefMethod(const std::string& name,
                            refgetter<C,T> rgetmethod,
                            refsetter<C,T> rsetmethod,
                            const std::string& classname="",
                            const std::string& tip="",
                            const std::string & whatthis="");

  public:

    Implements_Class_Reflection(const std::string& id,
                                const std::string& myVar,
                                C* object,
                                const std::string & tip,
                                const std::string& whatthis):
      //Implements_ValueId(id,myVar,tip,whatthis),
      Implements_Complex_Value(id,myVar,tip,whatthis),
      object_(object)
    {}


    Implements_Class_Reflection()=default;

    Implements_Class_Reflection(const Implements_Class_Reflection& other)
      :  //Implements_ValueId(other),
        Implements_Complex_Value(other),
        object_(other.object_)
    {
      resetChildsObject();
    }

    Implements_Class_Reflection(Implements_Class_Reflection&& other):
      Implements_ValueId(other),
      Implements_Complex_Value(std::move(other)),
      object_(std::move(other.object_))

    {
      other.object_=nullptr;
      resetChildsObject();
    }

    Implements_Class_Reflection& operator=(Implements_Class_Reflection&& other)
    {
      if (this!=&other)
        {
          Implements_Complex_Value::operator =(std::move(other));
          object_=std::move(other.object_);
          other.object_=nullptr;
          resetChildsObject();
        }
      return *this;
    }

    Implements_Class_Reflection& operator=(const Implements_Class_Reflection& other)
    {
      if (this!=&other)
        {
          operator=(Implements_Class_Reflection(other));
          resetChildsObject();
        }
      return *this;
    }

    virtual ~Implements_Class_Reflection(){}

    virtual ABC_Value* to_PlainValue()const override
    {
      auto out= new Implements_Complex_Value(id(),myVar(),Tip(),WhatThis());
      for (std::size_t i=0; i<numChilds(); ++i)
        {
          auto a=idToValue(ith_ChildName(i));
          auto e=a->to_PlainValue();
          out->pushChild(e);
        }
      return out;
    }
    //    virtual bool loadFromObjectValue(const ABC_Value* source)override
    //    {
    //      if (sameFields(source))
    //        {
    //          for (std::size_t i=0; i<this->numChilds(); ++i)
    //            {
    //              auto s=source->getChild(this->ith_ChildName(i));
    //              if (s!=nullptr)
    //                {
    //                  this->getChild(ith_ChildName(i))->loadFromObjectValue(s);
    //                }
    //            }
    //          return true;
    //        }
    //      else
    //        return false;
    //    }



  protected:
    virtual void initComplexVar(){}

    virtual void resetChildsObject()
    {
      for (std::size_t i=0; i<numChilds(); i++)
        {
          ABC_Value* a=this->idToValue(ith_ChildName(i));
          ABCObject<C>* c=dynamic_cast<ABCObject<C>*>(a);
          if (c!=nullptr)
            {
              c->setObject(&object_);
            }
        }
    }

    C* object_;


  };





  template<typename T>
  class Implements_Simple_Class:
      public ABC_Simple_Class<T>,
      public Implements_Class_Reflection<Implements_Simple_Class<T>>
  {
    typedef Implements_Simple_Class<T> C;
    // ABC_Var interface
  public:

    static std::string ClassName()
    {
      return Implements_Simple_Value<T>::ClassName()+"_class";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Value::SuperClasses()+ClassName();
    }

    virtual std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }

    T defaultValue()const override
    {
      return default_;
    }
    T minValue()const override
    {
      return min_;
    }
    T maxValue()const override
    {
      return max_;
    }
    T emptyValue()const override
    {
      return T();
    }
    T unknownValue()const override
    {
      return std::numeric_limits<T>::quiet_NaN();
    }

    void setDefaultValue(T val) override
    {
      default_=val;
    }


    void setminValue(T val) override
    {
      min_=val;
    }

    void setmaxValue(T val) override
    {
      max_=val;
    }

    std::string units()const override
    {
      return units_;

    }

    void setUnits(std::string newunits) override
    {
      units_=newunits;
    }

    virtual bool complyModes(const std::string mode) const override
    {
      return mode_.find(mode)!=mode_.end();
    }

    virtual std::set<std::string> modes()const override
    {
      return mode_;
    }
    Implements_Simple_Class(std::string id,
                            std::string measureunits,
                            std::set<std::string> modes,
                            T defaultValue=T(),
                            T minValue=T(),
                            T maxValue=T(),
                            std::string className=ClassName(),
                            std::string tip="",
                            std::string whatthis=""):
      //  Implements_ValueId(id,className,tip,whatthis),
      Implements_Class_Reflection<C>(id,className,this,tip,whatthis),
      mode_(modes),
      units_(measureunits),
      default_{defaultValue},
      min_(minValue),
      max_(maxValue)
    {
      this->push_backValMethod("units",&C::units,&C::setUnits,"measure unit",
                               "it does not allow conversions yet");
      this->push_backValMethod("defaultValue",&C::defaultValue,&C::setDefaultValue,"default value",
                               "suggested value, used for default constructor");


      this->push_backValMethod("min",&C::minValue,&C::setminValue,"min value",
                               "mandatory min value, in I/O interaction it enforces it");

      this->push_backValMethod("max",&C::maxValue,&C::setmaxValue,"max value",
                               "mandatory max value, in I/O interaction it enforces it");

    }


    Implements_Simple_Class()=default;

    Implements_Simple_Class(const Implements_Simple_Class& other)=default;
    Implements_Simple_Class(Implements_Simple_Class&& other)=default;

    Implements_Simple_Class& operator=(const Implements_Simple_Class& other)=default;

    Implements_Simple_Class& operator=(Implements_Simple_Class&& other)=default;



    virtual ~Implements_Simple_Class(){}


    virtual bool isInDomain(const ABC_Value *value) const  override
    {
      auto p=dynamic_cast<const ABC_Simple_Value<T>* > (value);
      if (p!=nullptr)
        {
          if ((minValue()!=emptyValue())&&(p->value()<minValue()))
            return false;
          else if ((maxValue()!=emptyValue())&&(p->value()>maxValue()))
            return false;
          else return true;
        }
      else
        return false;
    }


    static std::string ValueToString(const T& x)
    {
      std::stringstream ss;
      ss<<x;
      return ss.str();
    }
  private:
    std::set<std::string> mode_;
    std::string units_;
    T default_;
    T min_;
    T max_;

    // ABC_Simple_Class interface
  public:
    virtual bool checkValue(const T &val, std::string& error_message) const override
    {
      if ((minValue()!=emptyValue())&&(val<minValue()))
        {
          error_message=ValueToString(val)+" is less than the minimal value "+ValueToString(minValue());
          return false;
        }
      else if ((maxValue()!=emptyValue())&&(val>maxValue()))
        {
          error_message=ValueToString(val)+" is more than the maximal value "+ValueToString(maxValue());
          return false;
        }
      else return true;

    }
  };








  class Implements_Refer_Var:public Implements_ValueId
  {
    // ABC_Var interface
  public:

    static std::string ClassName();

    virtual std::string refId()const override;


    void setRefId(const std::string& ref_id);


    Implements_Refer_Var(const std::string &idName,
                         const std::string& refClass,
                         const std::string &refName,
                         const std::string& tip,
                         const std::string& whatthis);


    Implements_Refer_Var(const Implements_ValueId& id);



    Implements_Refer_Var()=default;




  private:

    const ABC_Value* refVar()const ;
    std::string refId_;
    // ABC_Var interface
  public:
    virtual Implements_Refer_Var* clone() const override;


    virtual Token_Stream toTokens() const override;
    virtual bool processTokens(Token_Stream& t)override;


    virtual std::string ith_ChildName(std::size_t i)const  override;

    virtual const ABC_Value* idToValue(const std::string& name)const  override;
    virtual ABC_Value* idToValue(const std::string &)  override;

    virtual const ABC_Value* idToValue(const std::string& name,const std::string& kind)const  override;
    virtual ABC_Value* idToValue(const std::string &name, const std::string &kind)  override;


    virtual void pushChild(ABC_Value*) override;


    // ABC_Value interface
  public:
    virtual bool empty() const override
    {
      return this->refId_.empty();
    }
    virtual void clear() override
    {
      refId_.clear();
    }

    // ABC_Value interface
  public:
    virtual bool setThisValue(Token_New tok, std::string& error) override
    {
      auto o=parentValue()->idToValue(tok.str());
      if (o!=nullptr)
        {
          std::string whyComplies;
          if ( o->complyVar(myVar(),&whyComplies))
            {
              setRefId(tok.str());
              return true;
            }
          else
            {
              error=whyComplies;
              return false;
            }
        }
      else
        {
          error=tok.str()+" variable was not found";
          return false;

        }

    }


    virtual std::set<std::string> alternativeValues()const override
    {
      if (this->myVarPtr()!=nullptr)
        return this->myVarPtr()->alternativeValues();
      else
        return {};

    }

  };


  template<>
  inline
  std::string Implements_Simple_Value<std::string>::ClassName()
  {
    return "Simple_name_var";
  }


  class Implements_Complex_Class: public Implements_Complex_Value
  {
  public:

    struct fieldDef{
      std::string superClass;
      std::string tip;
      std::string whatthis;
      bool isMandatory;

    };

    Implements_Complex_Class(const std::string &id,
                             const std::string &className,
                             const std::string &tip,
                             const std::string &whatthis,
                             const std::map<std::string, fieldDef> m);


    Implements_Complex_Class(){}


    virtual bool isInDomain(const ABC_Value *value) const  override;
    // ABC_Complex_Var interface
  public:
    virtual void push_back(const std::string& idName,
                           const std::string& classname,
                           const std::string& tip,
                           const std::string& whatthis,
                           bool mandatory);


    virtual bool isMandatory(const std::string id)const;

    virtual std::size_t numMandatoryChilds()const;

    virtual ABC_Measure* toPlainMeasure()const override
    {
      return Implements_Complex_Value::to_PlainValue();
    }


  private:
    std::set<std::string> isMandatory_;


  };





  class Parameters;

  class ABC_Parameterizable: public ABC_Value

  {
  public:
    ///virtual copy constructors
    virtual ABC_Parameterizable* clone() const override=0;
    ///virtual default constructors
    virtual ABC_Parameterizable* create() const override=0;

    virtual ~ABC_Parameterizable(){}


    static std::string ClassName()
    {
      return "Parameterizable";
    }

    std::string myVar()const override;



    //virtual std::ostream& put(std::ostream&) const=0;

    /// Apply the matching parameters
    virtual int apply_parameters(const Parameters& p)=0;
    // object inspectors


    /// Returns the parameters of the object
    virtual const Parameters& get_parameters()const=0;

    /*    /// It returns a name for the object that identifies its architecture
            virtual std::string name()const=0; */



  };








  /*
    class Implements_Categorical;


    template<>
    std::string Implements_Simple_Value<std::map<std::string,int>>::ClassName();


    class Implements_Categorical_Class : public Implements_Simple_Value<std::map<std::string,int>>
    {
    public:

      static std::string ClassName();

      static std::set<std::string> SuperClasses();

      virtual std::set<std::string> mySuperClasses()override;

      virtual std::string Category(int i)const;

      virtual int Rank(const std::string name)const;

      std::string defaultCategory()const;

      // ABC_Var interface
    public:

      Implements_Categorical_Class(ABC_Var* parent,
                                   const std::string& categoryName,
                                   std::vector<std::string> categoriesList ,
                                   const std::string& defaultCategoryName);

      Implements_Categorical_Class(ABC_Var* parent,
                                   const std::string& categoryName,
                                   std::map<std::string,int> categoriesRank,
                                   const std::string& defaultCategoryName);

      Implements_Categorical_Class(ABC_Var* parent,
                                   const std::string& categoryName,
                                   std::map<int,std::string> RankCategories,
                                   const std::string& defaultCategoryName);


      virtual bool isInDomain(const ABC_Var *value) const;
      virtual  ABC_Var *varTemplate() const;
    private:
      std::string default_;
      std::map<int,std::string> revMap_;

    };

  */

  template<>
  std::string Implements_Simple_Value<std::vector<std::string>>::ClassName();


  template<>
  std::string Implements_Simple_Value<Markov_LA::M_Matrix<double>>::ClassName();



  inline std::ostream& operator<<(std::ostream& os, std::vector<std::string> data );

  template<>
  inline bool ABC_Value::getVal(const std::string &name, const ABC_Value  *& value) const
  {
    const ABC_Value* o=idToValue(name);
    if (o!=nullptr)
      {
        value=o;
        return true;
      }
    else
      return false;
  }

  template<typename T>
  bool ABC_Value::getVal(const std::string &name, T &value) const
  {
    auto a=idToValue(name);
    if (a==nullptr)
      return false;
    const ABC_Simple_Value<T>* o=dynamic_cast<const ABC_Simple_Value<T>*>(a);

    if (o!=nullptr)
      {
        value=o->value();
        return true;
      }
    else
      {
        //        auto t=a->toTokens();
        //        t.setPos(0);
        //        Implements_Simple_Value<T> v{};
        //        if (v.processTokens(t))
        //          {
        //            value=v.value();
        //            return true;
        //          }
        //        else
        return false;
      }
  }

  template<typename T>
  bool ABC_Value::moveVal(const std::string &name, T &value)
  {
    auto a=idToValue(name);
    if (a==nullptr)
      return false;
    ABC_Simple_Value<T>* o=dynamic_cast<ABC_Simple_Value<T>*>(a);

    if (o!=nullptr)
      {
        o->moveVal(value);
        removeChild(name);
        return true;
      }
    else
      {
        auto t=a->toTokens();
        Implements_Simple_Value<T> v{};
        if (v.processTokens(t))
          {
            v.moveVal(value);
            return true;
          }
        else
          return false;
      }
  }



  template<typename T>
  T& ABC_Value::getReference(const std::string &name, T &value)
  {
    auto a=idToValue(name);
    if (a==nullptr)
      return value;

    ABC_Simple_Value<T>* o=dynamic_cast< ABC_Simple_Value<T>*>(a);

    if (o!=nullptr)
      {
        return o->refval();
      }
    else
      {
        auto t=a->toTokens();
        Implements_Simple_Value<T> v{};
        std::size_t pos=0;
        if (v.processTokens(t,pos,nullptr))
          {
            return v.refval();
          }
        else
          return value;
      }
  }

  template<>
  inline ABC_Value*& ABC_Value::getReference(const std::string &name, ABC_Value  *& value)
  {
    ABC_Value* o=idToValue(name);
    if (o!=nullptr)
      {
        value=o;
        return value;
      }
    else
      return value;
  }


  template<typename T>
  bool ABC_Value::checkValue(const std::string &varName, T &value, std::__cxx11::string &errorMessage) const
  {
    auto a=idToValue(varName);
    if (a==nullptr)
      {
        errorMessage=varName+" is not a registered identifier";
        return false;
      }
    else
      {
        const ABC_Simple_Class<T>* o=dynamic_cast<const ABC_Simple_Class<T>*>(a);

        if (o!=nullptr)
          {
            return o->checkValue(value,errorMessage);
          }
        else
          {
            errorMessage=varName+" is not a "+ABC_Simple_Value<T>::ClassName();
            return false;
          }
      }
  }


  template<typename T>
  void ABC_Value::push_backVal(const std::string &name,
                               T value,
                               const std::string &classname,
                               const std::string& tip,
                               const std::string & whatthis)
  {
    std::string c=classname;
    if (c.empty())
      c=Implements_Simple_Value<T>::ClassName();
    Implements_Simple_Value<T>* o=new Implements_Simple_Value<T>(name,value,c,tip,whatthis);
    pushChild(o);

  }

  inline
  void ABC_Value::push_backVarRef(const std::string &name, const std::string &idRef, const std::string &classname, const std::string &tip, const std::string &whatthis)
  {
    std::string c=classname;
    if (c.empty())
      c=Implements_Refer_Var::ClassName();
    auto o=new Implements_Refer_Var(name,c,idRef,tip,whatthis);
    pushChild(o);

  }





  template<class C> template<typename T>
  void Implements_Class_Reflection<C>::push_backVarPointer(const std::string &name,
                                                           T C::* value,
                                                           const std::string &classname,
                                                           const std::string& tip,
                                                           const std::string & whatthis)
  {
    std::string c=classname;
    if (c.empty())
      c=Implements_Simple_Value<T>::ClassName();
    auto o=new Implements_PointerMember_Var<C,T>(name,&object_,value,c,tip,whatthis);
    pushChild(o);
  }


  template<class C> template<typename T>
  void Implements_Class_Reflection<C>::push_backValMethod(const std::string& name,
                                                          getter<C,T> getmethod,
                                                          setter<C,T> setmethod,
                                                          const std::string& classname,
                                                          const std::string& tip,
                                                          const std::string & whatthis)
  {
    std::string c=classname;
    if (c.empty())
      c=Implements_ValMethod_Var<C,T>::ClassName();
    Implements_ValMethod_Var<C,T>* o=new Implements_ValMethod_Var<C,T>(name,&object_,getmethod,setmethod,c,tip,whatthis);
    pushChild(o);

  }






  template<class C>  template<typename Enum>
  void Implements_Class_Reflection<C>::push_backEnumValMethod(const std::string& name,
                                                              getter<C,Enum> getmethod,
                                                              setter<C,Enum> setmethod,
                                                              const std::string& classname,
                                                              const std::string& tip,
                                                              const std::string & whatthis)
  {
    std::string c=classname;
    if (c.empty())
      c=Implements_EnumMethod_Var<C,Enum>::ClassName();
    Implements_EnumMethod_Var<C,Enum>* o=new Implements_EnumMethod_Var<C,Enum>(name,&object_,getmethod,setmethod,c,tip,whatthis);
    pushChild(o);

  }




  template<class C>template<typename T>
  void Implements_Class_Reflection<C>::push_backRefMethod(const std::string& name,
                                                          refgetter<C,T> rgetmethod,
                                                          refsetter<C,T> rsetmethod,
                                                          const std::string& classname,
                                                          const std::string& tip,
                                                          const std::string & whatthis)
  {
    std::string c=classname;
    if (c.empty())
      c=Implements_RefMethod_Var<C,T>::ClassName();
    auto o=new Implements_RefMethod_Var<C,T>(name,&object_,rgetmethod,rsetmethod,c,tip,whatthis);
    pushChild(o);

  }













  template<>
  inline  void ABC_Value::push_backVal(const std::string &name,
                                       ABC_Value* value,
                                       const std::string &classname,
                                       const std::string& tip,
                                       const std::string & whatthis)

  {
    if (value!=nullptr)
      {
        if (!name.empty())
          value->setId(name);
        if (!classname.empty())
          value->setVar(classname);
        if (!tip.empty())
          value->setTip(tip);
        if (!whatthis.empty())
          value->setWhatThis(whatthis);
        pushChild(value);

      }
  }

  template<typename T>
  bool ABC_Value::replaceValue(const std::string &name, const T &value)
  {
    ABC_Value*p=idToValue(name);
    Implements_Simple_Value<T>* o=dynamic_cast<Implements_Simple_Value<T>*>(p);

    if (o!=nullptr)
      {
        o->setValue(value);
        return true;
      }
    else
      return false;
  }



  template<>
  inline  bool ABC_Value::replaceValue(const std::string &name, ABC_Value* const& value)
  {
    if ((value==nullptr)||(value->id()!=name)||(idToValue(name)==nullptr))
      return false;
    pushChild(value);
    return true;
  }



  template<typename Enum>
  std::set<std::string> Implements_Categorical<Enum>::SuperClasses()
  {
    return Implements_Simple_Value<int>::SuperClasses()+ClassName();
  }

  template<typename Enum>
  std::set<std::string> Implements_Categorical<Enum>::mySuperClasses() const
  {
    return SuperClasses();
  }

  template<typename Enum>
  std::string Implements_Categorical<Enum>::Category() const
  {
    return value();
  }

  template<typename Enum>
  Enum Implements_Categorical<Enum>::Rank() const
  {
    return rank_;
  }

  template<typename Enum>
  void Implements_Categorical<Enum>::updateCat()
  {
    for (auto& p:strToEnum)
      if (p.second==rank_)
        {
          setValue(p.first);
          break;
        }
  }

  template<typename Enum>
  void Implements_Categorical<Enum>::updateRank()
  {
    rank_=strToEnum[value()];
  }

  template<typename Enum>
  void Implements_Categorical<Enum>::setCategory(const std::string &cat)
  {
    push_backVal(cat);
    updateRank();
  }

  template<typename Enum>
  void Implements_Categorical<Enum>::setRank(Enum i)
  {
    rank_=i;
    updateCat();
  }

  template<typename Enum>
  Implements_Categorical<Enum>::Implements_Categorical(const std::string &idName,
                                                       Enum i,
                                                       const std::string& tip,
                                                       const std::string & whatthis):
    Implements_Simple_Value<std::string>(idName,"",ClassName(),tip,whatthis),
    rank_{i}
  {
    updateCat();
  }


  template<typename Enum>
  Implements_Categorical<Enum>::Implements_Categorical(const std::string &idName,
                                                       const std::string & cat,
                                                       const std::string& tip,
                                                       const std::string & whatthis):
    Implements_Simple_Value<std::string>(idName,cat,ClassName(),tip,whatthis),
    rank_{}
  {
    updateRank();
  }



  template<typename Enum>
  const Implements_Categorical<Enum> *Implements_Categorical<Enum>::myVarPtr() const
  {
    return dynamic_cast<const Implements_Categorical<Enum>*>(parentValue()->idToValue(myVar()));
  }


  template<typename Enum>
  Implements_Categorical<Enum> *Implements_Categorical<Enum>::myVarPtr(ABC_Value* v)const
  {
    if (isMyParent(v))
      {
        return dynamic_cast< Implements_Categorical<Enum>*>(v->idToValue(myVar()));
      }
    else
      return nullptr;
  }


  template<typename Enum>
  Implements_Categorical<Enum> *Implements_Categorical<Enum>::to_PlainValue()const
  {
    return nullptr;
  }

  template<typename Enum>
  void ABC_Value::push_back_CategoryItem(const std::string &name, Enum i,
                                         const std::string& tip,
                                         const std::string & whatthis)
  {
    pushChild(new Implements_Categorical<Enum>(name,i,tip,whatthis));

  }




  inline
  std::set<std::string> operator+(std::set<std::string>&& tok1,
                                  std::string &&s)
  {
    tok1.insert(s);
    return tok1;
  }

  inline std::set<std::string> operator+(std::set<std::string> &&ss1,
                                         std::set<std::string> &&ss2)
  {
    ss1.insert(ss2.begin(),ss2.end());
    return ss1;
  }




  template<typename T>
  inline std::set<std::string> getLables(const std::map<std::string,T>& m)
  {
    std::set<std::string> o;
    for (auto& e:m)
      o.insert(e.first);
    return o;

  }


  class Implements_Identifier_Class: public Implements_Simple_Class<std::string>
  {
  public:
    static std::string ClassName(){return "Implements_Identifier_Class";}
    std::string myClass()const override {return ClassName();}

    Implements_Identifier_Class(const std::string& id
                                , const std::string& tip
                                ,const std::string& whatthis
                                , const std::set<std::string> acceptedIdentifiers)
      :
        Implements_Simple_Class<std::string>(id,"",{},"","","",ClassName(),tip,whatthis)
      ,ids_(acceptedIdentifiers)
    {}



    virtual void push_Identifier(const std::string& label)
    {
      ids_.insert(label);
    }

    virtual void remove_Identifier(const std::string& label)
    {
      ids_.erase(label);
    }

    template<class C>
    void add_Identifiers(const C& s)
    {
      ids_.insert(s.begin(),s.end());
    }

    const std::set<std::string>& idSet()const {return ids_;}




  private:
    std::set<std::string> ids_;


    // ABC_Value interface
  public:
    virtual bool isInDomain(const ABC_Value *value) const override
    {
      std::string val;
      const ABC_Simple_Value<std::string>* o=dynamic_cast<const ABC_Simple_Value<std::string>*>(value);

      if (o!=nullptr)
        {
          return true;
        }
      else
        {
          return false;
        }
    }

    // ABC_Simple_Class interface
  public:
    virtual bool checkValue(const std::string &val, std::__cxx11::string& error_message) const override
    {
      if(ids_.find(val)!=ids_.end())
        return true;
      else
        {
          error_message=val+" not in "+id()+" list";
          return false;
        }
    }


    // ABC_Value interface
  public:
    virtual std::set<std::__cxx11::string> alternativeValues() const override
    {
      return idSet();
    }
  };






  class Implements_New_Identifier_Class: public Implements_Simple_Class<std::string>
  {
  public:
    static std::string ClassName(){return "Implements_New_Identifier_Class";}
    std::string myClass()const override {return ClassName();}

    std::string identifierType()const {return identifierType_;}


    Implements_New_Identifier_Class(const std::string& id
                                    ,const std::string& IdentifierType
                                    ,const std::string& defaultIdentifier
                                    , Markov_Console::Markov_CommandManagerVar* cm
                                    , const std::string& tip
                                    ,const std::string& whatthis
                                    )
      :
        Implements_Simple_Class<std::string>(id,"",{},defaultIdentifier
                                             ,"","",ClassName(),tip,whatthis)
      ,identifierType_(IdentifierType),cm_(cm)
    {}


  private:
    std::string identifierType_;
    Markov_Console::Markov_CommandManagerVar* cm_;


    // ABC_Value interface
  public:
    virtual bool isInDomain(const ABC_Value *value) const override;

    // ABC_Simple_Class interface
  public:
    virtual bool checkValue(const std::string &val, std::__cxx11::string& error_message) const override;


    // ABC_Value interface
  public:
    virtual std::set<std::__cxx11::string> alternativeValues() const override;
  };



  //  template<typename T>
  //  std::string ABC_Simple_Class<T>::ClassName()
  //  {
  //    return Implements_Simple_Value<T>::ClassName()+"_abs_SC";
  //  }


}


#endif



#endif // VAR_H
