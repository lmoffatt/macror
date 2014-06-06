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

#include <limits>
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


  inline std::deque<Token_New>& operator<<(std::deque<Token_New>& tok1,
                                           const std::deque<Token_New>& tok2);

  inline std::deque<Token_New>& operator<<(std::deque<Token_New>& tok,
                                           const std::string& text);

  inline std::deque<Token_New>& operator<<(std::deque<Token_New>& tok,
                                           const char* text);


  inline std::deque<Token_New>& operator<<(std::deque<Token_New>& tok,
                                           double d);

  template<typename T>
  std::deque<Token_New>& operator<<(std::deque<Token_New>& tok, std::vector<T> v)
  {
    tok<<"\n[";
    for (T e:v)
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
    for (std::pair<K,T> e:m)
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

  inline bool toValue(const std::deque<Token_New> &tok,double &val,std::size_t& i);


  inline bool toValue(const std::deque<Token_New> &tok,
                      int &val,
                      std::size_t& i);

  inline bool toValue(const std::deque<Token_New> &tok,
                      std::size_t &val,
                      std::size_t& i);


  inline bool toValue(const std::deque<Token_New> &tok,
                      std::string &val,
                      std::size_t& i);


  inline bool toValue(const std::deque<Token_New> &tok,
                      bool &val,
                      std::size_t& i);


  template<typename T>
  inline bool toValue(const std::deque<Token_New> &tok,
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
            while (toValue(tok,val,i))
              {
                ++i;
                icol++;
                v.push_back(val);
              }
            // we consider as candidates all the things until there is and end of line
            if (ncols==0)
              ncols=icol;
            else if (ncols!=icol)
              return false;
            icol=0;
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

    virtual std::set<std::string> mySuperClasses();

    virtual const ABC_Var* motherClass()const=0;

    virtual ABC_Var* motherClass()=0;


    virtual std::deque<Token_New> toTokens()const=0;

    virtual bool processTokens(const std::deque<Token_New>& tokenList,
                               std::size_t& pos)=0;


    virtual std::string toString()const;

    virtual std::size_t numChildVars()const=0;

    virtual ABC_Var* parentVar()=0;
    virtual const ABC_Var* parentVar()const =0;

    virtual void setParentVar(ABC_Var* par)=0;

    virtual std::string ith_Var(std::size_t i)const=0;

    virtual const ABC_Var* getChildVar(const std::string& name)const=0;
    virtual ABC_Var* getChildVar(const std::string &name)=0;

    virtual const ABC_Var* getChildVar(const std::string& name,const std::string& kind)const=0;
    virtual ABC_Var* getChildVar(const std::string &name, const std::string &kind) =0;

    virtual bool addChildVar(ABC_Var* var)=0;

    virtual ~ABC_Var(){}
    virtual bool isInDomain(const ABC_Var* value)const=0;

    virtual ABC_Var* varTemplate()const=0;

    virtual bool load_from_ABC_Var(const ABC_Var* source)=0;
    virtual ABC_Var* get_ABC_Var() const =0;

    template<typename T>
    bool getValue(const std::string& name, T& value)const;

    template<typename T>
    bool push_backVar(const std::string& name,
                  T value,
                  const std::string& classname="",
                  const std::string& tip="",
                  const std::string & whatthis="");


    template<typename T>
    bool replaceValue(const std::string& name, const T& value);

    template<typename Enum>
    bool push_back_CategoryItem(const std::string & name, Enum i);
  };



  class Implements_VarId: virtual public ABC_Var
  { // ABC_Var interface
  public:

    virtual Implements_VarId* varCreate()const override
    {
      return new Implements_VarId;
    }

    virtual Implements_VarId* varClone() const override
    {
      return new Implements_VarId(*this);
    }
    virtual std::string myClass() const override;
    virtual void setClass(const std::string& classname)override;

    virtual std::deque<Token_New> toTokens() const override;
    virtual bool processTokens(const std::deque<Token_New> &t,
                               std::size_t& pos) override;
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
    virtual std::string ith_Var(std::size_t i) const override;
    virtual const ABC_Var* getChildVar(const std::string& name)const override;
    virtual ABC_Var* getChildVar(const std::string &name) override;
    virtual const ABC_Var* getChildVar(const std::string& name,const std::string& kind)const  override;
    virtual ABC_Var* getChildVar(const std::string &name, const std::string &kind) override;
    virtual bool addChildVar(ABC_Var *var) override;
    virtual std::string refId()const override;
    virtual ABC_Var* motherClass() override;
    virtual const ABC_Var* motherClass() const  override;
    virtual void setParentVar(ABC_Var *par)override;
    virtual bool isInDomain(const ABC_Var* value)const override;
    virtual ABC_Var* varTemplate()const  override;
    Implements_VarId(ABC_Var* parent,
                     const std::string& name,
                     const std::string& className,
                     const std::string &tip,
                     const std::string &whatthis);
    Implements_VarId();
    Implements_VarId(const Implements_VarId& other)=default;
    Implements_VarId& operator=(const Implements_VarId& other)=default;

    Implements_VarId(Implements_VarId&& other)=default;
    Implements_VarId& operator=(Implements_VarId&& other)=default;

    virtual ~Implements_VarId(){}

    virtual bool load_from_ABC_Var(const ABC_Var* source)override;
    virtual ABC_Var* get_ABC_Var() const override;


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
  class Implements_Simple_Var: public Implements_VarId
  {
    // ABC_Var interface
  public:
    static std::string ClassName();

    static std::set<std::string> SuperClasses()
    {
      return ABC_Var::SuperClasses()+ClassName();
    }

    virtual std::set<std::string> mySuperClasses()
    {
      return SuperClasses();
    }

    virtual Implements_Simple_Var<T>* varCreate() const override
    {
      return new Implements_Simple_Var<T>;
    }

    virtual Implements_Simple_Var<T>* varClone() const override
    {
      return new Implements_Simple_Var<T>(*this);
    }



    const ABC_Var *motherClass() const override
    {
      if (parentVar()!=nullptr)
        {
          auto p=parentVar()->getChildVar(myClass());
          return dynamic_cast<const Implements_Simple_Class<T>*>(p);
        }
      else
        return nullptr;
    }

    T value()const
    {
      return value_;
    }

    void setValue(T val)
    {
      value_=val;
    }
    const T& refval()const
    {
      return value_;
    }
    T& refval()
    {
      return value_;
    }

    std::deque<Token_New> toTokens() const
    {
      auto out=Implements_VarId::toTokens();
      out<<"="<<toToken(value())<<"\n";
      return out;
    }

    bool processTokens(const std::deque<Token_New>& t,
                       std::size_t &pos)
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
              value_=val;
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



    Implements_Simple_Var():
      Implements_VarId(),
      value_{}{}


    Implements_Simple_Var(const Implements_Simple_Var<T>& other)=default;
    Implements_Simple_Var(Implements_Simple_Var<T>&& other)=default;

    Implements_Simple_Var& operator=(const Implements_Simple_Var<T>& other)=default;
    Implements_Simple_Var& operator=(Implements_Simple_Var<T>&& other)=default;

    virtual ~Implements_Simple_Var(){}

    virtual Implements_Simple_Var<T>* get_ABC_Var()const  override
    {
        return varClone();
    }

    virtual bool load_from_ABC_Var(const ABC_Var* source) override
    {
     return false;
    }
  private:
    T value_;
  };


  class Implements_Complex_Var:virtual public ABC_Var, public Implements_VarId
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

    virtual std::size_t numChildVars() const override;
    virtual std::string ith_Var(std::size_t i) const override;
    virtual const ABC_Var* getChildVar(const std::string& name)const override;
    virtual  ABC_Var* getChildVar(const std::string& name)override;
    virtual const ABC_Var* getChildVar(const std::string& name,
                                    const std::string &myclass)const override;
    virtual ABC_Var* getChildVar(const std::string& name, const std::string &myclass) override;
    virtual bool addChildVar(ABC_Var *var) override;
    Implements_Complex_Var(ABC_Var *parent,
                           const std::string& id,
                           const std::string className,
                           const std::string & tip,
                           const std::string& whatthis);

    Implements_Complex_Var(){}


    Implements_Complex_Var(const Implements_Complex_Var& other)
      :
        Implements_VarId(other),
        ids_(other.ids_),
        vars_(other.vars_)
    {
      for (std::pair<std::string,ABC_Var*> it:vars_)
        {
          it.second=it.second->varClone();
        }
    }

    Implements_Complex_Var(Implements_Complex_Var&& other)=default;
    Implements_Complex_Var& operator=(Implements_Complex_Var&& other)=default;


    Implements_Complex_Var& operator=(const Implements_Complex_Var& other)
    {
      if (&other!=this)
        {
          *this=Implements_Complex_Var(other);
        }
      return *this;
      }



    virtual ~Implements_Complex_Var();

    virtual std::deque<Token_New> toTokens() const override;

    virtual bool processTokens(const std::deque<Token_New> &tokenList,
                               std::size_t &pos) override;



    virtual ABC_Var* get_ABC_Var()const override
    {
      return varClone();
    }
    virtual bool load_from_ABC_Var(const ABC_Var* source)override
    {
          return true;
    }

  protected:
    std::vector<std::string> ids_;
    std::map<std::string,ABC_Var*> vars_;

  };


  template<typename T>
  class Implements_Simple_Class: public Implements_Complex_Var
  {
    // ABC_Var interface
  public:
    static std::string ClassName();

    static std::set<std::string> SuperClasses();

    virtual std::set<std::string> mySuperClasses()override;


    T defaultValue()const;
    T minValue()const;
    T maxValue()const;
    T emptyValue()const;
    T unknownValue()const;

    void setDefaultValue(T val);
    void setminValue(T val);
    void setmaxValue(T val);


    Implements_Simple_Class(ABC_Var* parent,
                            std::string id,
                            T defaultValue=T(),
                            T minValue=T(),
                            T maxValue=T(),
                            std::string className=ClassName());


    Implements_Simple_Class();


    virtual ~Implements_Simple_Class(){}
    virtual  Implements_Simple_Var<T>* varTemplate()const  override;

    virtual bool isInDomain(const ABC_Var *value) const  override;


  private:

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
    virtual bool processTokens(const std::deque<Token_New> &t,
                               std::size_t& pos)override;


    virtual std::string ith_Var(std::size_t i)const  override;

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
  template<typename Enum>
  class Implements_Categorical: public Implements_Simple_Var<std::string>
  {
  public:
    static std::string ClassName();

    static std::set<std::string> SuperClasses();

    virtual std::set<std::string> mySuperClasses()override;


    // ABC_Var interface
  public:
    std::string Category()const;

    Enum Rank()const;

    void updateCat();
    void updateRank();

    void setCategory(const std::string& cat);

    void setRank(Enum i);

    Implements_Categorical(ABC_Var* parent, const std::string& idName,Enum i);
    Implements_Categorical(ABC_Var* parent, const std::string& idName, const std::string &cat);



    virtual const Implements_Categorical* motherClass()const;
    virtual Implements_Categorical* motherClass();


    virtual bool load_from_ABC_Var(const ABC_Var* source) override;

    virtual Implements_Categorical<Enum> *get_ABC_Var() const override;

  private:
    static std::map<std::string,Enum> strToEnum;
    Enum rank_;
  };



  template<>
  std::string Implements_Simple_Var<std::vector<std::string>>::ClassName();

  template<>
  std::string Implements_Simple_Var<std::string>::ClassName();

  template<>
  std::string Implements_Simple_Var<Markov_LA::M_Matrix<double>>::ClassName();



  inline std::ostream& operator<<(std::ostream& os, std::vector<std::string> data )
  {
    for (std::string s:data)
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
    const Implements_Simple_Var<T>* o=dynamic_cast<const Implements_Simple_Var<T>*>(getChildVar(name));

    if (o!=nullptr)
      {
        value=o->value();
        return true;
      }
    else
      return false;
  }


  template<typename T>
  bool ABC_Var::push_backVar(const std::string &name, T value,
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
  std::string Implements_Categorical<Enum>::ClassName()
  {
    return "Category";
  }

  template<typename Enum>
  std::set<std::string> Implements_Categorical<Enum>::SuperClasses()
  {
    return Implements_Simple_Var<int>::SuperClasses()+ClassName();
  }

  template<typename Enum>
  std::set<std::string> Implements_Categorical<Enum>::mySuperClasses()
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
    for (std::pair<std::string,Enum> p:strToEnum)
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
                                                 Enum i):
    Implements_Simple_Var<std::string>(parent,idName,"",ClassName()),
    rank_{i}
  {
    updateCat();
  }


  template<typename Enum>
  Implements_Categorical<Enum>::Implements_Categorical(ABC_Var *parent,
                                                 const std::string &idName,
                                                 const std::string & cat):
    Implements_Simple_Var<std::string>(parent,idName,cat,ClassName()),
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
  bool Implements_Categorical<Enum>::load_from_ABC_Var(const ABC_Var* source)
  {
   }

  template<typename Enum>
  Implements_Categorical<Enum> *Implements_Categorical<Enum>::get_ABC_Var()const
  {
   }

  template<typename Enum>
  bool ABC_Var::push_back_CategoryItem(const std::string &name, Enum i)
  {
    return addChildVar(new Implements_Categorical<Enum>(this,name,i));

  }




}

#endif // ABC_VAR_H
