#ifndef ABC_VAR_H
#define ABC_VAR_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <deque>
#include <sstream>
#include <iostream>
#include <limits>
#include <utility>
#include "Markov_LA/Matrix.h"
namespace  Markov_IO {

  class ABC_Var;

  class Token_New
  {
  public:
    static bool isNameChar(char ch);
    static bool isSpaceChar(char ch);
    static bool isRealNumberChar(char ch);

    static std::string toString(double number);
    static std::string toString(int number);
    static std::string toString(std::size_t number);
    enum Value {
      IDENTIFIER,
      STRING,
      PATH,
      INTEGER,
      UNSIGNED,
      REAL,
      NUMBER,
      INVALID,

      EOL='\n',
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
      NOT='~',
      AND='&',
      OR='|',
      LSS='<',
      GTR='>',
      HASH, // '#',

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
    std::istream& get(std::istream& stream);
    std::string str()const;
    double realValue()const;
    int  intval()const;

    std::size_t count()const;

    Value tok()const;

    std::string toString()const;

    bool isReal()const;
    bool isInteger()const;
    bool isCount()const;



    static Value toKeyword(std::string identifier);
    static std::string toString(Value identifier);



    Token_New()=default;

    Token_New(double d);

    Token_New(int n);

    Token_New(std::size_t s);

    Token_New(std::string d);

    Token_New(Value v);

  private:
    Value curr_tok;
    double number_;
    int int_;
    std::size_t size_;
    std::string str_;
  };


  std::deque<Token_New>& operator<<(std::deque<Token_New>& tok1,
                                    const std::deque<Token_New>& tok2);

  std::deque<Token_New>& operator<<(std::deque<Token_New>& tok,
                                    const std::string& text);

  std::deque<Token_New>& operator<<(std::deque<Token_New>& tok,
                                    const char* text);


  std::deque<Token_New>& operator<<(std::deque<Token_New>& tok,
                                    double d);

  template<typename T>
  std::deque<Token_New>& operator<<(std::deque<Token_New>& tok, std::vector<T> v)
  {
    tok<<"\n[";
    for (const T& e:v)
      tok<<e;
    tok<<"]"<<"\n";
    return tok;
  }

  template<typename T>
  std::deque<Token_New>& operator<<(std::deque<Token_New>& tok, Markov_LA::M_Matrix<T> m)
  {
    tok<<"\n";
    for (std::size_t i=0; i<Markov_LA::nrows(m); ++i)
      {
        for(std::size_t j=0; j<Markov_LA::ncols(m); ++j)
          {
            tok<<m(i,j);
          }
        tok<<"\n";
      }
    tok<<"\n";
    return tok;
  }

  template<typename K,typename T>
  std::deque<Token_New>& operator<<(std::deque<Token_New>& tok, std::pair<K,T> e)
  {
    tok<<e.first<<":"<<e.second;
    return tok;
  }

  template<typename K,typename T>
  std::deque<Token_New>& operator<<(std::deque<Token_New>& tok, std::map<K,T> m)
  {
    tok<<"\n[";
    for (auto& e:m)
      tok<<e;
    tok<<"]"<<"\n";
    return tok;
  }


  template<typename T>
  inline std::deque<Token_New> toToken(const T& val)
  {
    std::deque<Token_New> out;
    out<<val;
    return out;
  }

  bool toValue(const std::deque<Token_New> &tok,double &val,std::size_t& i);


  bool toValue(const std::deque<Token_New> &tok,
               int &val,
               std::size_t& i);

  bool toValue(const std::deque<Token_New> &tok,
               std::size_t &val,
               std::size_t& i);


  bool toValue(const std::deque<Token_New> &tok,
               std::string &val,
               std::size_t& i);


  bool toValue(const std::deque<Token_New> &tok,
               bool &val,
               std::size_t& i);


  template<typename T>
  bool toValue(const std::deque<Token_New> &tok,
               std::vector<T> &vec,
               std::size_t& i)
  {
    // checks the initial squarebracket
    if ((!(i+1<tok.size()))||
        (tok.at(i).tok()!=Token_New::EOL)||
        (tok.at(i+1).tok()!=Token_New::LSB))
      return false;
    i+=2;
    T val;
    if (!toValue(tok,val,i))
      return false;
    else
      {
        vec.push_back(val);
        while (toValue(tok,val,i))
          {
            vec.push_back(val);
          }
        if ((!(i<tok.size()))||(tok.at(i).tok()!=Token_New::RSB))
          return false;
        ++i;
        return true;
      }
  }

  template<typename T>
  inline bool toValue(const std::deque<Token_New> &tok,
                      Markov_LA::M_Matrix<T> &m,
                      std::size_t& i)
  {
    if ((!(i<tok.size()))||
        (tok.at(i).tok()!=Token_New::EOL))
      return false;
    ++i;
    std::vector<T> v;
    T val;
    if (Markov_LA::size(m)==0)// we have to determine the size ourselves
      {
        std::size_t ncols=0;
        std::size_t icol=0;
        std::size_t irow=0;
        while (toValue(tok,val,i))
          {
            ++irow;
            ++icol;
            v.push_back(val);
            while (toValue(tok,val,i)) // advances only on success
              {
                icol++;
                v.push_back(val);
              }
            // we consider as candidates all the things until there is and end of line
            if (ncols==0)
              ncols=icol;
            else if (ncols!=icol)
              return false;
            icol=0;
            ++i;
          }
        m=Markov_LA::M_Matrix<T>(irow,ncols,v);
        return true;
        // lets see if there are more things
      }
    else
      {
        for (std::size_t ii=0; ii<Markov_LA::nrows(m); ++ii)
          {
            for (std::size_t j=0; j<Markov_LA::ncols(m); ++j)
              {
                if (toValue(tok,val,i))
                  m(ii,j)=val;
                else
                  return false;
              }
            if ((i>=tok.size())||(tok.at(i).tok()!=Token_New::EOL))
              return false;
            else
              ++i;
          }
        return true;
      }
  }


  template<typename K,typename T>
  inline bool toValue(const std::deque<Token_New> &tok,
                      std::pair<K,T>& p,
                      std::size_t& i)
  {
    if (!(i+2<tok.size()))
      return false;
    auto pos0=i;

    K k;
    T t;
    if (tok.at(i+1).tok()!=Token_New::COLON)
      return false;
    if (!toValue(tok,k,i))
      return false;
    ++i;
    if (!toValue(tok,t,i))
      {
        i=pos0;
        return false;
      }
    else
      {
        p.first=k;
        p.second=t;
        return true;
      }
  }

  template<typename K,typename T>
  inline bool toValue(const std::deque<Token_New> &tok,
                      std::map<K,T> &map,
                      std::size_t& i)
  {
    // checks the initial squarebracket
    if ((!(i+1<tok.size()))||
        (tok.at(i).tok()!=Token_New::EOL)||
        (tok.at(i+1).tok()!=Token_New::LSB))
      return false;
    i+=2;
    std::pair<K,T> val;
    if (!toValue(tok,val,i))
      return false;
    else
      {
        map.insert(val);
        while (toValue(tok,val,i))
          {
            map.insert(val);
          }
        if ((!(i<tok.size()))||(tok.at(i).tok()!=Token_New::RSB))
          return false;
        ++i;
        return true;
      }
  }



  std::set<std::string> operator+(std::set<std::string>&& tok1,
                                  std::string &&s);


  std::set<std::string> operator+(std::set<std::string> &&ss1,
                                  std::set<std::string> &&ss2);



  template<class C,typename T>
  using setter=void (C::*)(T);

  template<class C,typename T>
  using getter=T(C::*)()const;

  template<class C,typename T>
  using refgetter=const T&(C::*)()const;

  template<class C,typename T>
  using refsetter=T&(C::*)();





  class ABC_Var
  {
  public:
    static ABC_Var* getFromTokens(ABC_Var* parent,
                                  const std::deque<Token_New>& tokensList,
                                  std::size_t& pos);

    static bool isValidId(std::string name);

    static std::string ClassName();

    static std::set<std::string> SuperClasses();


    virtual ABC_Var* varCreate()const=0;
    virtual ABC_Var* varClone()const=0;

    virtual bool isRootedVariable()const=0;

    virtual std::string id()const=0;
    virtual void setId(const std::string& idName)=0;

    virtual std::string Tip()const=0;
    virtual std::string WhatThis()const=0;
    virtual void setTip(const std::string& tip)=0;
    virtual void setWhatThis(const std::string& whatThis)=0;

    virtual std::string refId()const=0;

    virtual std::string myClass()const=0;
    virtual void setClass(const std::string& classname)=0;

    virtual std::set<std::string> mySuperClasses() const;

    virtual bool complyClass(const std::string classname)const ;

    virtual const ABC_Var* motherClass()const=0;

    virtual ABC_Var* motherClass()=0;

    virtual std::set<std::string> modes()const =0;
    virtual bool complyModes(const std::string mode) const=0;

    virtual std::string toString()const;
    
    
    virtual std::deque<Token_New> toTokens()const=0;

    virtual bool processTokens(const std::deque<Token_New>& tokenList,
                               std::size_t& pos)=0;

    // invariant varCreate()->processTokens(toTokens())=true


    

    virtual ABC_Var* to_ComplexVar() const =0;
    
    virtual bool loadFromComplexVar(const ABC_Var* source)=0;
    //


    
    virtual std::size_t numChildVars()const=0;

    virtual ABC_Var* parentVar()=0;
    virtual const ABC_Var* parentVar()const =0;

    virtual void setParentVar(ABC_Var* par)=0;

    virtual std::string ith_VarName(std::size_t i)const=0;
    virtual std::string childClass(const std::string& idName)const=0;


    virtual const ABC_Var* getChildVar(const std::string& name)const=0;
    virtual ABC_Var* getChildVar(const std::string &name)=0;

    virtual const ABC_Var* getChildVar(const std::string& name,const std::string& kind)const=0;
    virtual ABC_Var* getChildVar(const std::string &name, const std::string &kind) =0;

    virtual bool addChildVar(ABC_Var* var)=0;

    virtual ~ABC_Var(){}
    virtual bool isInDomain(const ABC_Var* value)const=0;

    virtual ABC_Var* varTemplate()const=0;

    virtual void reset()=0;

    
    template<typename T>
    bool getValue(const std::string& name, T& value)const;

    template<typename T>
    bool push_backVar(const std::string& name,
                      T value,
                      const std::string& classname="",
                      const std::string& tip="",
                      const std::string & whatthis="");



    bool push_backVarRef(const std::string& name,
                         const std::string& idRef,
                         const std::string& classname="",
                         const std::string& tip="",
                         const std::string & whatthis="");



    template<typename T>
    bool replaceValue(const std::string& name, const T& value);

    template<typename Enum>
    bool push_back_CategoryItem(const std::string & name,
                                Enum i,
                                const std::string& tip="",
                                const std::string & whatthis="");



    bool sameFields(const ABC_Var* other)const
    {
      if ((other==nullptr)||(numChildVars()!=other->numChildVars()))
        return false;
      for (std::size_t i=0; i<numChildVars(); ++i)
        {
          auto name=ith_VarName(i);
          auto cl=childClass(name);
          auto o=other->getChildVar(name,cl);
          if (o==nullptr)
            return false;
        }
      return true;
    }



  };



  class Implements_VarId: virtual public ABC_Var
  { // ABC_Var interface
  public:

    virtual ABC_Var* varCreate()const override
    {
      return new Implements_VarId;
    }

    virtual Implements_VarId* varClone() const override
    {
      return new Implements_VarId(*this);
    }
    virtual void reset() override
    {
      if ((parentVar()!=nullptr)&&(!isRootedVariable()))
        {
          auto s=dynamic_cast<Implements_VarId*>(parentVar()->getChildVar(id()));
          if (s!=nullptr)
            *this=*s;

        }

    }



    virtual std::string myClass() const override;
    virtual void setClass(const std::string& classname)override;

    virtual std::deque<Token_New> toTokens() const override;
    virtual bool processTokens(const std::deque<Token_New> &t,std::size_t& pos) override;
    virtual std::string id()const override;
    virtual void setId(const std::string& IdName)override;

    virtual std::string Tip()const override;
    virtual std::string WhatThis()const override;
    virtual void setTip(const std::string& tip)override;
    virtual void setWhatThis(const std::string& whatThis)override;


    bool isRootedVariable()const override;

    ABC_Var *parentVar() override;
    const ABC_Var *parentVar() const override;
    virtual std::size_t numChildVars() const override;
    virtual std::string ith_VarName(std::size_t) const override;
    virtual std::string childClass(const std::string &) const override;
    virtual const ABC_Var* getChildVar(const std::string&)const override;
    virtual ABC_Var* getChildVar(const std::string &) override;
    virtual const ABC_Var* getChildVar(const std::string&, const std::string&)const  override;
    virtual ABC_Var* getChildVar(const std::string &, const std::string &) override;
    virtual bool addChildVar(ABC_Var *) override;
    virtual std::string refId()const override;
    virtual ABC_Var* motherClass() override;
    virtual const ABC_Var* motherClass() const  override;
    virtual bool complyModes(const std::string )const override
    {
      return false;
    }
    virtual std::set<std::string> modes()const override
    {
      return {};
    }
    virtual void setParentVar(ABC_Var *par)override;
    virtual bool isInDomain(const ABC_Var* value)const override;
    virtual ABC_Var* varTemplate()const  override;
    Implements_VarId(ABC_Var* parent,
                     const std::string& name,
                     const std::string& className,
                     const std::string &tip,
                     const std::string &whatthis);

    Implements_VarId(const ABC_Var& other);

    Implements_VarId()=default;
    Implements_VarId(const Implements_VarId& other)=default;
    Implements_VarId& operator=(const Implements_VarId& other)=default;

    Implements_VarId(Implements_VarId&& other)=default;
    Implements_VarId& operator=(Implements_VarId&& other)=default;

    virtual ~Implements_VarId(){}

    virtual bool loadFromComplexVar(const ABC_Var*)override;
    virtual ABC_Var* to_ComplexVar() const override;



  protected:
    std::string id_;
    std::string class_;
    ABC_Var* p_;
    std::string tip_;
    std::string whatThis_;

  };

  template<typename T>
  class Implements_Simple_Class;



  template<typename T>
  class ABC_Simple_Var;

  template<typename T>
  class ABC_Simple_Class:  public  virtual Implements_VarId
  {
  public:

    static std::string ClassName();

    static std::set<std::string> SuperClasses()
    {
      return ABC_Var::SuperClasses()+ClassName();
    }

    virtual std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }

    virtual T defaultValue()const=0;
    virtual T minValue()const=0;
    virtual T maxValue()const=0;
    virtual T emptyValue()const=0;
    virtual T unknownValue()const=0;
    virtual void setDefaultValue(T val)=0;
    virtual void setminValue(T val)=0;
    virtual void setmaxValue(T val)=0;
    virtual std::string units()const=0;
    virtual void setUnits(std::string newunits)=0;
    virtual bool complyModes(const std::string mode)const override=0;
    virtual std::set<std::string> modes()const override=0;
    virtual ~ABC_Simple_Class(){}
    virtual  ABC_Simple_Var<T>* varTemplate()const override=0;
  };




  template<typename T>
  class ABC_Simple_Var: public virtual Implements_VarId
  {
    // ABC_Var interface
  public:
    virtual T value()const=0;
    virtual void setValue(T val)=0;

    virtual const T& refval()const=0;

    virtual T& refval()=0;

    virtual const ABC_Simple_Class<T>* motherClassType()const
    {
      return dynamic_cast<const ABC_Simple_Class<T>*> (motherClass());
    }

    virtual  ABC_Simple_Class<T>* motherClassType()
    {
      return dynamic_cast<ABC_Simple_Class<T>*> (motherClass());
    }


    virtual ~ABC_Simple_Var(){}

  };





  template<typename T>
  class Implements_Simple_Var: public ABC_Simple_Var<T>
  {
    // ABC_Var interface
  public:
    static std::string ClassName();

    static std::set<std::string> SuperClasses()
    {
      return ABC_Var::SuperClasses()+ClassName();
    }

    virtual std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }

    virtual Implements_Simple_Var<T>* varCreate() const override
    {
      return new Implements_Simple_Var<T>();
    }

    virtual Implements_Simple_Var<T>* varClone() const override
    {
      return new Implements_Simple_Var<T>(*this);
    }

    virtual void reset() override
    {
      if ((this->parentVar()!=nullptr)&&(!this->isRootedVariable()))
        {
          auto s=dynamic_cast<Implements_Simple_Var<T>*>(this->parentVar()->getChildVar(this->id()));
          if (s!=nullptr)
            *this=*s;

        }
    }
    virtual  T value()const override
    {
      return value_;
    }

    virtual void setValue(T val) override
    {
      value_=std::move(val);
    }
    virtual const T& refval()const override
    {
      return value_;
    }
    virtual T& refval() override
    {
      return value_;
    }

    virtual std::deque<Token_New> toTokens() const override
    {
      auto out=Implements_VarId::toTokens();
      out<<"="<<toToken(value())<<"\n";
      return out;
    }

    bool processTokens(const std::deque<Token_New>& t,std::size_t &pos) override
    {
      if (!Implements_VarId::processTokens(t,pos))
        return false;
      else
        {
          if (t.at(pos).tok()!=Token_New::ASSIGN)
            return false;
          ++pos;
          T val;
          if (!toValue(t,val,pos))
            return false;
          else
            {

              setValue(val);
              if (t.at(pos).tok()==Token_New::EOL)
                ++pos;
              return true;
            }
        }
    }
    // ABC_Var interface

    Implements_Simple_Var(ABC_Var* parent,
                          std::string id,
                          T val,
                          std::string className=ClassName(),
                          const std::string& tip="",
                          const std::string& whatthis=""):
      Implements_VarId(parent,id,className,tip,whatthis),
      value_(val){}


    Implements_Simple_Var()=default;

    Implements_Simple_Var(const Implements_Simple_Var<T>& other)=default;

    Implements_Simple_Var(Implements_Simple_Var<T>&& other)=default;

    Implements_Simple_Var& operator=(const Implements_Simple_Var<T>& other)=default;
    /* {
      if (this!=&other)
        *this=Implements_Simple_Var<T>(other);
      return *this;
    }
*/
    Implements_Simple_Var& operator=(Implements_Simple_Var<T>&& other)=default;

    virtual ~Implements_Simple_Var(){}

    virtual Implements_Simple_Var<T>* to_ComplexVar()const  override
    {
      return varClone();
    }



    virtual bool loadFromComplexVar(const ABC_Var* ) override
    {
      return false;
    }



  private:
    T value_;

  };








  class Implements_Complex_Var: virtual public  Implements_VarId
  {
    // ABC_Var interface
  public:
    static std::string ClassName();
    virtual Implements_Complex_Var* varCreate() const override
    {
      return new Implements_Complex_Var;
    }
    virtual Implements_Complex_Var* varClone() const override
    {
      return new Implements_Complex_Var(*this);
    }
    virtual void reset() override
    {
      if ((parentVar()!=nullptr)&&(!isRootedVariable()))
        {
          auto s=dynamic_cast<Implements_Complex_Var*>(parentVar()->getChildVar(id()));
          if (s!=nullptr)
            *this=*s;

        }

    }

    virtual std::size_t numChildVars() const override;
    virtual std::string ith_VarName(std::size_t i) const override;
    virtual std::string childClass(const std::string &idName) const override;
    virtual const ABC_Var* getChildVar(const std::string& name)const override;
    virtual  ABC_Var* getChildVar(const std::string& name)override;
    virtual const ABC_Var* getChildVar(const std::string& name,
                                       const std::string &myclass)const override;
    virtual ABC_Var* getChildVar(const std::string& name, const std::string &myclass) override;
    virtual bool addChildVar(ABC_Var *var) override;
    Implements_Complex_Var(
        ABC_Var *parent,
        const std::string& id,
        const std::string className,
        const std::string & tip,
        const std::string& whatthis,
        const std::vector<std::pair<std::string,std::string>>& childsNameClass={});


    Implements_Complex_Var(const ABC_Var& other):
      Implements_VarId(other)
    {

      for (std::size_t i=0; i<other.numChildVars(); ++i)
        {
          std::string name=other.ith_VarName(i);
          auto o=other.getChildVar(name);
          if (o!=nullptr)
            addChildVar(o->varClone());
          childclss_[name]=other.childClass(name);
        }
    }



    Implements_Complex_Var()=default;


    Implements_Complex_Var(const Implements_Complex_Var& other)
      :
        Implements_VarId(other),
        ids_(other.ids_),
        childclss_(other.childclss_),
        vars_(other.vars_)
    {
      cloneChids();
      resetChildsParent();
    }

    Implements_Complex_Var(Implements_Complex_Var&& other):
      Implements_VarId(std::move(other)),
      ids_(std::move(other.ids_)),
      childclss_(std::move(other.childclss_)),
      vars_(std::move(other.vars_))
    {
      resetChildsParent();
    }

    Implements_Complex_Var& operator=(Implements_Complex_Var&& other)
    {
      if (this!=&other)
        {
          privateDelete();
          Implements_VarId::operator =(std::move(other));
          ids_=std::move(other.ids_);
          childclss_=std::move(other.childclss_);
          vars_=std::move(other.vars_);
          resetChildsParent();
        }
      return *this;
    }




    Implements_Complex_Var& operator=(const Implements_Complex_Var& other)
    {
      if (this!=&other)
        {
          *this=Implements_Complex_Var(other);
          resetChildsParent();

        }
      return *this;
    }

    void privateDelete()
    {
      for (auto& id:vars_)
        {
          auto o=id.second;
          delete o;
        }
    }


    virtual ~Implements_Complex_Var(){
      privateDelete();
    }

    virtual std::deque<Token_New> toTokens() const override;

    virtual bool processTokens(const std::deque<Token_New> &tokenList,std::size_t &pos) override;






    virtual ABC_Var* to_ComplexVar()const override
    {
      return new Implements_Complex_Var(*this);
    }
    virtual bool loadFromComplexVar(const ABC_Var* source)override
    {
      if (sameFields(source))
        {
          *this=Implements_Complex_Var(*source);
          return true;
        }
      else
        return false;
    }

  protected:
    void cloneChids()
    {
      for (auto& it:vars_)
        {
          if (it.second!=nullptr)
            {
              ABC_Var* n=it.second->varClone();

              it.second=n;
            }
        }
    }

    void resetChildsParent()
    {
      for (auto& it:vars_)
        {
          if (it.second!=nullptr)
            {
              it.second->setParentVar(this);
            }
        }
    }
    std::vector<std::string> ids_;
    std::map<std::string, std::string> childclss_;
    std::map<std::string,ABC_Var*> vars_;

  };



  template<class C>
  class ABCObject:  virtual public Implements_VarId
  {
    // ABC_Var interface
  public:
    virtual C* getObject() =0;

    virtual const C* getObject()const =0;
    virtual void setObject(C** obj)=0;


    virtual ~ABCObject(){}
  };



  template<class C,typename T>
  class Implements_ValMethod_Var: public ABC_Simple_Var<T>, public ABCObject<C>
  {
    // ABC_Var interface
  public:
    static std::string ClassName()
    {
      return C::ClassName()+"_method";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Var::SuperClasses()+ClassName();
    }

    virtual std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }

    virtual Implements_ValMethod_Var<C,T>* varCreate() const override
    {
      return new Implements_ValMethod_Var<C,T>;
    }

    virtual Implements_ValMethod_Var<C,T>* varClone() const override
    {
      return new Implements_ValMethod_Var<C,T>(*this);
    }




    virtual void reset() override
    {
      if ((this->parentVar()!=nullptr)&&(!this->isRootedVariable()))
        {
          auto s=dynamic_cast<Implements_ValMethod_Var<C,T>*>(this->parentVar()->getChildVar(this->id()));
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



    std::deque<Token_New> toTokens() const override
    {
      auto out=Implements_VarId::toTokens();
      out<<"="<<toToken(value())<<"\n";
      return out;
    }

    bool processTokens(const std::deque<Token_New>& t,std::size_t &pos) override
    {
      if (!Implements_VarId::processTokens(t,pos))
        return false;
      else
        {
          if (t.at(pos).tok()!=Token_New::ASSIGN)
            return false;
          ++pos;
          T val{};
          if (!toValue(t,val,pos))
            return false;
          else
            {
              setValue(val);
              if (t.at(pos).tok()==Token_New::EOL)
                ++pos;
              return true;
            }
        }
    }



    // ABC_Var interface

    Implements_ValMethod_Var(ABC_Var* parent,
                             std::string id,
                             C** objectPtr,
                             getter<C,T> getterMethod,
                             setter<C,T> setterMethod,
                             std::string className=ClassName(),
                             const std::string& tip="",
                             const std::string& whatthis=""):
      Implements_VarId(parent,id,className,tip,whatthis),
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

    virtual Implements_Simple_Var<T>* to_ComplexVar()const  override
    {
      return new Implements_Simple_Var<T>(
            nullptr,this->id(),this->value(),this->myClass(),this->Tip(), this->WhatThis());
    }







    virtual bool loadFromComplexVar(const ABC_Var* var) override
    {
      if ((var!=nullptr)&&(this->id()==var->id()))
        {
          auto o=dynamic_cast<const ABC_Simple_Var<T>*>(var);
          if(o!=nullptr)
            {
              setValue(o->value());
              if (!o->Tip().empty())
                this->setTip(o->Tip());
              if (!o->WhatThis().empty())
                this->setWhatThis(o->WhatThis());
              return true;
            }
          else
            return false;
        }
      else
        return false;
    }
  protected:
    C** objectPtr_;
    getter<C,T> get_;
    setter<C,T> set_;
    T empty_=T();
  };



  template<class C,typename T>
  class Implements_PointerMember_Var: public ABC_Simple_Var<T>, public ABCObject<C>
  {
    // ABC_Var interface
  public:
    static std::string ClassName()
    {
      return C::ClassName()+"_method";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Var::SuperClasses()+ClassName();
    }

    virtual std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }

    virtual Implements_PointerMember_Var<C,T>* varCreate() const override
    {
      return new Implements_PointerMember_Var<C,T>;
    }

    virtual Implements_PointerMember_Var<C,T>* varClone() const override
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

    void setValue(T val) override
    {
      if ((this->getObject()!=nullptr)&& (m_!=nullptr))
        (this->getObject()->*m_)=val;

    }



    std::deque<Token_New> toTokens() const override
    {
      auto out=Implements_VarId::toTokens();
      out<<"="<<toToken(value())<<"\n";
      return out;
    }

    bool processTokens(const std::deque<Token_New>& t,std::size_t &pos) override
    {
      if (!Implements_VarId::processTokens(t,pos))
        return false;
      else
        {
          if (t.at(pos).tok()!=Token_New::ASSIGN)
            return false;
          ++pos;
          T val{};
          if (!toValue(t,val,pos))
            return false;
          else
            {
              setValue(val);
              if (t.at(pos).tok()==Token_New::EOL)
                ++pos;
              return true;
            }
        }
    }



    // ABC_Var interface


    Implements_PointerMember_Var(ABC_Var* parent,
                                 std::string id,
                                 C** objectPtr,
                                 T C::* memberPointer,
                                 std::string className=ClassName(),
                                 const std::string& tip="",
                                 const std::string& whatthis=""):
      Implements_VarId(parent,id,className,tip,whatthis),
      objectPtr_(objectPtr),
      m_(memberPointer)
    {}


    Implements_PointerMember_Var()=default;


    Implements_PointerMember_Var(const Implements_PointerMember_Var<C,T>& other)=default;


    Implements_PointerMember_Var(Implements_PointerMember_Var<C,T>&& other)=default;




    Implements_PointerMember_Var& operator=( Implements_PointerMember_Var<C,T>&& other)=default;


    Implements_PointerMember_Var& operator=(const Implements_PointerMember_Var<C,T>& other)=default;

    virtual ~Implements_PointerMember_Var(){}

    virtual Implements_Simple_Var<T>* to_ComplexVar()const  override
    {
      return new Implements_Simple_Var<T>(
            nullptr,this->id(),this->value(),this->myClass(),this->Tip(), this->WhatThis());
    }

    virtual bool loadFromComplexVar(const ABC_Var* var) override
    {
      if ((var!=nullptr)&&(this->id()==var->id()))
        {
          auto o=dynamic_cast<const ABC_Simple_Var<T>*>(var);
          if(o!=nullptr)
            {
              setValue(o->value());
              if (!o->Tip().empty())
                this->setTip(o->Tip());
              if (!o->WhatThis().empty())
                this->setWhatThis(o->WhatThis());
              return true;
            }
          else
            return false;
        }
      else
        return false;
    }
  protected:
    C** objectPtr_;
    T C::* m_;
    T empty_=T();

  };


  template<class C,typename T>
  class Implements_RefMethod_Var: public ABC_Simple_Var<T>, public ABCObject<C>
  {
    // ABC_Var interface
  public:
    static std::string ClassName()
    {
      return C::ClassName()+"_method";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Var::SuperClasses()+ClassName();
    }

    virtual std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }

    virtual Implements_RefMethod_Var<C,T>* varCreate() const override
    {
      return new Implements_RefMethod_Var<C,T>;
    }

    virtual Implements_RefMethod_Var<C,T>* varClone() const override
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



    std::deque<Token_New> toTokens() const override
    {
      auto out=Implements_VarId::toTokens();
      out<<"="<<toToken(value())<<"\n";
      return out;
    }

    bool processTokens(const std::deque<Token_New>& t,std::size_t &pos) override
    {
      if (!Implements_VarId::processTokens(t,pos))
        return false;
      else
        {
          if (t.at(pos).tok()!=Token_New::ASSIGN)
            return false;
          ++pos;
          T val{};
          if (!toValue(t,val,pos))
            return false;
          else
            {
              setValue(val);
              if (t.at(pos).tok()==Token_New::EOL)
                ++pos;
              return true;
            }
        }
    }



    // ABC_Var interface

    Implements_RefMethod_Var(ABC_Var* parent,
                             std::string id,
                             C** object,
                             refgetter<C,T> refgetterMethod,
                             refsetter<C,T> refsetterMethod,
                             std::string className=ClassName(),
                             const std::string& tip="",
                             const std::string& whatthis=""):
      Implements_VarId(parent,id,className,tip,whatthis),
      objectPtr_(object),
      rget_(refgetterMethod),
      rset_(refsetterMethod){}


    Implements_RefMethod_Var()=default;


    Implements_RefMethod_Var(const Implements_RefMethod_Var<C,T>& other)=default;


    Implements_RefMethod_Var(Implements_RefMethod_Var<C,T>&& other)=default;




    Implements_RefMethod_Var& operator=( Implements_RefMethod_Var<C,T>&& other)=default;


    Implements_RefMethod_Var& operator=(const Implements_RefMethod_Var<C,T>& other)=default;

    virtual ~Implements_RefMethod_Var(){}


    virtual Implements_Simple_Var<T>* to_ComplexVar()const  override
    {
      return new Implements_Simple_Var<T>(
            nullptr,this->id(),this->value(),this->myClass(),this->Tip(), this->WhatThis());
    }

    virtual bool loadFromComplexVar(const ABC_Var* var) override
    {
      if ((var!=nullptr)&&(this->id()==var->id()))
        {
          auto o=dynamic_cast<const ABC_Simple_Var<T>*>(var);
          if(o!=nullptr)
            {
              setValue(o->value());
              if (!o->Tip().empty())
                this->setTip(o->Tip());
              if (!o->WhatThis().empty())
                this->setWhatThis(o->WhatThis());
              return true;
            }
          else
            return false;
        }
      else
        return false;
    }
  protected:
    C** objectPtr_;
    refgetter<C,T> rget_;
    refsetter<C,T> rset_;
    T empty_=T();

  };



  template<class C,typename Enum>
  class Implements_EnumMethod_Var: public ABC_Simple_Var<Enum>, public ABCObject<C>
  {
    // ABC_Var interface
  public:
    static std::string ClassName();

    static std::set<std::string> SuperClasses()
    {
      return ABC_Var::SuperClasses()+ClassName();
    }

    virtual std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }

    virtual Implements_EnumMethod_Var<C,Enum>* varCreate() const override
    {
      return new Implements_EnumMethod_Var<C,Enum>;
    }

    virtual Implements_EnumMethod_Var<C,Enum>* varClone() const override
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


    std::deque<Token_New> toTokens() const override
    {
      auto out=Implements_VarId::toTokens();
      out<<"="<<toToken(Category())<<"\n";
      return out;
    }

    bool processTokens(const std::deque<Token_New>& t,std::size_t &pos) override
    {
      if (!Implements_VarId::processTokens(t,pos))
        return false;
      else
        {
          if (t.at(pos).tok()!=Token_New::ASSIGN)
            return false;
          ++pos;
          std::string val{};
          if (!toValue(t,val,pos))
            return false;
          else if (!setCategory(val))
            return false;
          else
            {
              if (t.at(pos).tok()==Token_New::EOL)
                ++pos;
              return true;
            }
        }
    }



    // ABC_Var interface

    Implements_EnumMethod_Var(ABC_Var* parent,
                              std::string id,
                              C** objectPtr,
                              getter<C,Enum> getterMethod,
                              setter<C,Enum> setterMethod,
                              std::string className=ClassName(),
                              const std::string& tip="",
                              const std::string& whatthis=""):
      Implements_VarId(parent,id,className,tip,whatthis),
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
      if ((this->parentVar()!=nullptr)&&(!this->isRootedVariable()))
        {
          auto s=dynamic_cast<Implements_EnumMethod_Var<C,Enum>*>(this->parentVar()->getChildVar(this->id()));
          if (s!=nullptr)
            *this=*s;

        }
    }

    virtual Implements_Simple_Var<std::string>* to_ComplexVar()const  override
    {
      return new Implements_Simple_Var<std::string>(
            nullptr,this->id(),this->Category(),this->myClass(),this->Tip(), this->WhatThis());
    }

    virtual bool loadFromComplexVar(const ABC_Var* var) override
    {
      if ((var!=nullptr)&&(this->id()==var->id()))
        {
          auto o=dynamic_cast<const ABC_Simple_Var<std::string>*>(var);
          if(o!=nullptr)
            {

              setCategory(o->value());
              if (!o->Tip().empty())
                this->setTip(o->Tip());
              if (!o->WhatThis().empty())
                this->setWhatThis(o->WhatThis());
              return true;
            }
          else
            return false;
        }
      else
        return false;
    }
  protected:
    C** objectPtr_;
    getter<C,Enum> get_;
    setter<C,Enum> set_;
    Enum empty_=Enum();
    static std::map<std::string,Enum> strToEnum;
  };



  template<typename Enum>
  class Implements_Categorical: public Implements_Simple_Var<std::string>
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

    Implements_Categorical(ABC_Var* parent, const std::string& idName,Enum i,
                           const std::string& tip="",
                           const std::string & whatthis="");
    Implements_Categorical(ABC_Var* parent, const std::string& idName,
                           const std::string &cat,
                           const std::string& tip="",
                           const std::string & whatthis="");



    virtual const Implements_Categorical* motherClass()const;
    virtual Implements_Categorical* motherClass();


    virtual bool loadFromComplexVar(const ABC_Var*) override;

    virtual Implements_Categorical<Enum> *to_ComplexVar() const override;

    typedef Implements_Categorical<Enum> C;
    virtual void reset() override
    {
      if ((parentVar()!=nullptr)&&(!isRootedVariable()))
        {

          C* r=dynamic_cast<C*>(parentVar()->getChildVar(id()));
          if (r!=nullptr)
            *this=*r;

        }

    }

  private:
    static std::map<std::string,Enum> strToEnum;
    Enum rank_;
  };






  template <class C>
  class Implements_Class_Reflection: public Implements_Complex_Var, public ABCObject<C>
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

    const C* getObject()const override
    {
      return object_;
    }
    void setObject(C** obj) override
    {
      object_=*obj;
    }


    virtual Implements_Class_Reflection<C>* varCreate() const override
    {
      return new Implements_Class_Reflection<C>();
    }

    virtual Implements_Class_Reflection<C>* varClone() const override
    {
      return new Implements_Class_Reflection<C>(*this);
    }

    virtual void reset() override
    {
      if ((parentVar()!=nullptr)&&(!isRootedVariable()))
        {
          auto s=dynamic_cast<Implements_Class_Reflection<C>*>(parentVar()->getChildVar(id()));
          if (s!=nullptr)
            *this=*s;

        }
    }

    template<typename T>
    bool push_backVarPointer(const std::string& name,
                             T C::* value,
                             const std::string& classname="",
                             const std::string& tip="",
                             const std::string & whatthis="");

    template<typename T>
    bool push_backValMethod(const std::string& name,
                            getter<C,T> getmethod,
                            setter<C,T> setmethod,
                            const std::string& classname="",
                            const std::string& tip="",
                            const std::string & whatthis="");

    template<typename Enum>
    bool push_backEnumValMethod(const std::string& name,
                                getter<C,Enum> getmethod,
                                setter<C,Enum> setmethod,
                                const std::string& classname="",
                                const std::string& tip="",
                                const std::string & whatthis="");

    template<typename T>
    bool push_backRefMethod(const std::string& name,
                            refgetter<C,T> rgetmethod,
                            refsetter<C,T> rsetmethod,
                            const std::string& classname="",
                            const std::string& tip="",
                            const std::string & whatthis="");


    Implements_Class_Reflection(
        ABC_Var *parent,
        const std::string& id,
        C* object,
        const std::string className,
        const std::string & tip,
        const std::string& whatthis):
      Implements_VarId(parent,id,className,tip,whatthis),
      Implements_Complex_Var(parent,id,className,tip,whatthis),
      object_(object)
    {}


    Implements_Class_Reflection()=default;

    Implements_Class_Reflection(const Implements_Class_Reflection& other)
      :  Implements_VarId(other),
        Implements_Complex_Var(other),
        object_(other.object_)
    {
      resetChildsObject();


    }

    Implements_Class_Reflection(Implements_Class_Reflection&& other):
      Implements_VarId(other),
      Implements_Complex_Var(std::move(other)),
      object_(std::move(other.object_))

    {
      other.object_=nullptr;
      resetChildsObject();
    }

    Implements_Class_Reflection& operator=(Implements_Class_Reflection&& other)
    {
      if (this!=&other)
        {
          Implements_Complex_Var::operator =(std::move(other));
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

    virtual ABC_Var* to_ComplexVar()const override
    {
      auto out= new Implements_Complex_Var(nullptr,id(),myClass(),Tip(),WhatThis());
      for (std::size_t i=0; i<numChildVars(); ++i)
        {
          auto a=getChildVar(ith_VarName(i));
          auto e=a->to_ComplexVar();
          out->addChildVar(e);
        }
      return out;
    }
    virtual bool loadFromComplexVar(const ABC_Var* source)override
    {
      if (sameFields(source))
        {
          for (std::size_t i=0; i<this->numChildVars(); ++i)
            {
              auto s=source->getChildVar(this->ith_VarName(i));
              if (s!=nullptr)
                {
                  this->getChildVar(ith_VarName(i))->loadFromComplexVar(s);
                }
            }
          return true;
        }
      else
        return false;
    }



  protected:
    virtual void initComplexVar(){}

    virtual void resetChildsObject()
    {
      for (std::size_t i=0; i<numChildVars(); i++)
        {
          ABC_Var* a=this->getChildVar(ith_VarName(i));
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
      private Implements_Class_Reflection<Implements_Simple_Class<T>>
  {
    typedef Implements_Simple_Class<T> C;
    // ABC_Var interface
  public:

    static std::string ClassName()
    {
      return Implements_Simple_Var<T>::ClassName()+"_class";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Var::SuperClasses()+ClassName();
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
    Implements_Simple_Class(ABC_Var* parent,
                            std::string id,
                            std::string measureunits,
                            std::set<std::string> modes,
                            T defaultValue=T(),
                            T minValue=T(),
                            T maxValue=T(),
                            std::string className=ClassName(),
                            std::string tip="",
                            std::string whatthis=""):
      Implements_VarId(parent,id,className,tip,whatthis),
      Implements_Class_Reflection<C>(parent,id,this,className,tip,whatthis),
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

    virtual  Implements_Simple_Var<T>* varTemplate()const  override
    {
      return new Implements_Simple_Var<T>(nullptr,"",defaultValue(),this->id());
    }


    virtual bool isInDomain(const ABC_Var *value) const  override
    {
      auto p=dynamic_cast<const ABC_Simple_Var<T>* > (value);
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


  private:
    std::set<std::string> mode_;
    std::string units_;
    T default_;
    T min_;
    T max_;

  };





  class Implements_Refer_Var:public Implements_VarId
  {
    // ABC_Var interface
  public:

    static std::string ClassName();

    virtual std::string refId()const override;


    Implements_Refer_Var(ABC_Var* parent,
                         const std::string &idName,
                         const std::string& refClass,
                         const std::string &refName,
                         const std::string& tip,
                         const std::string& whatthis);

    Implements_Refer_Var()=default;

  private:
    ABC_Var* refVar() ;

    const ABC_Var* refVar()const ;
    std::string refId_;
    // ABC_Var interface
  public:
    virtual std::deque<Token_New> toTokens() const override;
    virtual bool processTokens(const std::deque<Token_New> &t,std::size_t& pos)override;


    virtual std::string ith_VarName(std::size_t i)const  override;

    virtual const ABC_Var* getChildVar(const std::string& name)const  override;
    virtual ABC_Var* getChildVar(const std::string &name)  override;

    virtual const ABC_Var* getChildVar(const std::string& name,const std::string& kind)const  override;
    virtual ABC_Var* getChildVar(const std::string &name, const std::string &kind)  override;


    virtual bool addChildVar(ABC_Var* var) override;

  };





  class Implements_Complex_Class: public Implements_Complex_Var
  {
  public:

    struct fieldDef{
      std::string superClass; std::string className; std::string tip; std::string whatthis;

    };

    Implements_Complex_Class(ABC_Var *parent,
                             const std::string &id,
                             const std::string &className,
                             const std::string &tip,
                             const std::string &whatthis,
                             const std::map<std::string, fieldDef> m);



    virtual bool isInDomain(const ABC_Var *value) const  override;
    virtual  Implements_Complex_Var *varTemplate()  const override;
    // ABC_Complex_Var interface
  public:
    virtual void push_back(const std::string& idName,
                           const std::string& superclassname,
                           const std::string& classname,
                           const std::string& tip,
                           const std::string& whatthis);


  };


  /*
  class Implements_Categorical;


  template<>
  std::string Implements_Simple_Var<std::map<std::string,int>>::ClassName();


  class Implements_Categorical_Class : public Implements_Simple_Var<std::map<std::string,int>>
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
  std::string Implements_Simple_Var<std::vector<std::string>>::ClassName();

  template<>
  std::string Implements_Simple_Var<std::string>::ClassName();

  template<>
  std::string Implements_Simple_Var<Markov_LA::M_Matrix<double>>::ClassName();



  inline std::ostream& operator<<(std::ostream& os, std::vector<std::string> data )
  {
    for (const auto& s:data)
      {
        os<<s<<"\t";
      }
    return os;
  }

  template<>
  inline bool ABC_Var::getValue(const std::string &name, const ABC_Var  *& value) const
  {
    const ABC_Var* o=getChildVar(name);
    if (o!=nullptr)
      {
        value=o;
        return true;
      }
    else
      return false;
  }


  template<typename T>
  bool ABC_Var::getValue(const std::string &name, T &value) const
  {
    auto a=getChildVar(name);
    const Implements_Simple_Var<T>* o=dynamic_cast<const Implements_Simple_Var<T>*>(a);

    if (o!=nullptr)
      {
        value=o->value();
        return true;
      }
    else
      {
        auto t=a->toTokens();
        Implements_Simple_Var<T> v{};
        std::size_t pos=0;
        if (v.processTokens(t,pos))
          {
            value=v.value();
            return true;
          }
        else
          return false;
      }
  }
  template<typename T>
  bool ABC_Var::push_backVar(const std::string &name,
                             T value,
                             const std::string &classname,
                             const std::string& tip,
                             const std::string & whatthis)
  {
    std::string c=classname;
    if (c.empty())
      c=Implements_Simple_Var<T>::ClassName();
    Implements_Simple_Var<T>* o=new Implements_Simple_Var<T>(this,name,value,c,tip,whatthis);
    return addChildVar(o);

  }



  template<class C> template<typename T>
  bool Implements_Class_Reflection<C>::push_backVarPointer(const std::string &name,
                                                           T C::* value,
                                                           const std::string &classname,
                                                           const std::string& tip,
                                                           const std::string & whatthis)
  {
    std::string c=classname;
    if (c.empty())
      c=Implements_Simple_Var<T>::ClassName();
    Implements_PointerMember_Var<C,T>* o=new Implements_PointerMember_Var<C,T>(
          this,name,&object_,value,c,tip,whatthis);
    return addChildVar(o);

  }


  template<class C> template<typename T>
  bool Implements_Class_Reflection<C>::push_backValMethod(const std::string& name,
                                                          getter<C,T> getmethod,
                                                          setter<C,T> setmethod,
                                                          const std::string& classname,
                                                          const std::string& tip,
                                                          const std::string & whatthis)
  {
    std::string c=classname;
    if (c.empty())
      c=Implements_ValMethod_Var<C,T>::ClassName();
    Implements_ValMethod_Var<C,T>* o=new Implements_ValMethod_Var<C,T>(this,name,&object_,getmethod,setmethod,c,tip,whatthis);
    return addChildVar(o);

  }






  template<class C>  template<typename Enum>
  bool Implements_Class_Reflection<C>::push_backEnumValMethod(const std::string& name,
                                                              getter<C,Enum> getmethod,
                                                              setter<C,Enum> setmethod,
                                                              const std::string& classname,
                                                              const std::string& tip,
                                                              const std::string & whatthis)
  {
    std::string c=classname;
    if (c.empty())
      c=Implements_EnumMethod_Var<C,Enum>::ClassName();
    Implements_EnumMethod_Var<C,Enum>* o=new Implements_EnumMethod_Var<C,Enum>(this,name,&object_,getmethod,setmethod,c,tip,whatthis);
    return addChildVar(o);

  }




  template<class C>template<typename T>
  bool Implements_Class_Reflection<C>::push_backRefMethod(const std::string& name,
                                                          refgetter<C,T> rgetmethod,
                                                          refsetter<C,T> rsetmethod,
                                                          const std::string& classname,
                                                          const std::string& tip,
                                                          const std::string & whatthis)
  {
    std::string c=classname;
    if (c.empty())
      c=Implements_RefMethod_Var<C,T>::ClassName();
    auto o=new Implements_RefMethod_Var<C,T>(this,name,&object_,rgetmethod,rsetmethod,c,tip,whatthis);
    return addChildVar(o);

  }













  template<>
  inline  bool ABC_Var::push_backVar(const std::string &name,
                                     ABC_Var* value,
                                     const std::string &classname,
                                     const std::string& tip,
                                     const std::string & whatthis)

  {
    if (value!=nullptr)
      {
        if (!name.empty())
          value->setId(name);
        if (!classname.empty())
          value->setClass(classname);
        if (!tip.empty())
          value->setTip(tip);
        if (!whatthis.empty())
          value->setWhatThis(whatthis);
        return addChildVar(value);

      }
    else
      return false;
  }

  template<typename T>
  bool ABC_Var::replaceValue(const std::string &name, const T &value)
  {
    ABC_Var*p=getChildVar(name);
    Implements_Simple_Var<T>* o=dynamic_cast<Implements_Simple_Var<T>*>(p);

    if (o!=nullptr)
      {
        o->setValue(value);
        return true;
      }
    else
      return false;
  }



  template<>
  inline  bool ABC_Var::replaceValue(const std::string &name, ABC_Var* const& value)
  {
    if ((value==nullptr)||(value->id()!=name)||(getChildVar(name)==nullptr))
      return false;
    return addChildVar(value);
  }



  template<typename Enum>
  std::set<std::string> Implements_Categorical<Enum>::SuperClasses()
  {
    return Implements_Simple_Var<int>::SuperClasses()+ClassName();
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
    push_backVar(cat);
    updateRank();
  }

  template<typename Enum>
  void Implements_Categorical<Enum>::setRank(Enum i)
  {
    rank_=i;
    updateCat();
  }

  template<typename Enum>
  Implements_Categorical<Enum>::Implements_Categorical(ABC_Var *parent,
                                                       const std::string &idName,
                                                       Enum i,
                                                       const std::string& tip,
                                                       const std::string & whatthis):
    Implements_Simple_Var<std::string>(parent,idName,"",ClassName(),tip,whatthis),
    rank_{i}
  {
    updateCat();
  }


  template<typename Enum>
  Implements_Categorical<Enum>::Implements_Categorical(ABC_Var *parent,
                                                       const std::string &idName,
                                                       const std::string & cat,
                                                       const std::string& tip,
                                                       const std::string & whatthis):
    Implements_Simple_Var<std::string>(parent,idName,cat,ClassName(),tip,whatthis),
    rank_{}
  {
    updateRank();
  }



  template<typename Enum>
  const Implements_Categorical<Enum> *Implements_Categorical<Enum>::motherClass() const
  {
    return dynamic_cast<const Implements_Categorical<Enum>*>(parentVar()->getChildVar(myClass()));
  }


  template<typename Enum>
  Implements_Categorical<Enum> *Implements_Categorical<Enum>::motherClass()
  {
    return dynamic_cast< Implements_Categorical<Enum>*>(parentVar()->getChildVar(myClass()));
  }

  template<typename Enum>
  bool Implements_Categorical<Enum>::loadFromComplexVar(const ABC_Var* )
  {
    return false;
  }

  template<typename Enum>
  Implements_Categorical<Enum> *Implements_Categorical<Enum>::to_ComplexVar()const
  {
    return nullptr;
  }

  template<typename Enum>
  bool ABC_Var::push_back_CategoryItem(const std::string &name, Enum i,
                                       const std::string& tip,
                                       const std::string & whatthis)
  {
    return addChildVar(new Implements_Categorical<Enum>(this,name,i,tip,whatthis));

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


  inline std::deque<Token_New> &operator<<(std::deque<Token_New> &tok1, const std::deque<Token_New> &tok2)
  {
    tok1.insert(tok1.end(),tok2.begin(),tok2.end());
    return tok1;
  }

  inline std::deque<Token_New> &operator<<(std::deque<Token_New> &tok, const std::string &text)
  {
    std::stringstream ss(text);
    Token_New t;
    while (t.get(ss))
      {
        tok.push_back(t);
      }

    return tok;
  }


  inline std::deque<Token_New> &operator<<(std::deque<Token_New> &tok, const char* text)
  {
    std::stringstream ss(text);
    Token_New t;
    while (t.get(ss))
      {
        tok.push_back(t);
      }

    return tok;
  }


  inline std::deque<Token_New> &operator<<(std::deque<Token_New> &tok, double d)
  {
    tok.push_back(Token_New(d));
    return tok;
  }




  template<typename T>
  std::string ABC_Simple_Class<T>::ClassName()
  {
    return Implements_Simple_Var<T>::ClassName()+"_abs_SC";
  }


}

#endif // ABC_VAR_H
