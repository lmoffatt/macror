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
        for(std::size_t j=0; i<Markov_LA::ncols(m); ++j)
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


    virtual std::string id()const=0;
    virtual void setId(const std::string& idName)=0;

    virtual std::string Tip()const=0;
    virtual std::string WhatThis()const=0;
    virtual void setTip(const std::string& tip)=0;
    virtual void setWhatThis(const std::string& whatThis)=0;

    virtual std::string refId()const=0;

    virtual const ABC_Var* refVar()const=0;
    virtual ABC_Var* refVar()=0;

    virtual std::string myClass()const=0;

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

    virtual const ABC_Var* getVarId(const std::string& name)const=0;
    virtual ABC_Var* getVarId(const std::string &name)=0;

    virtual const ABC_Var* getVarId(const std::string& name,const std::string& kind)const=0;
    virtual ABC_Var* getVarId(const std::string &name, const std::string &kind) =0;

    virtual bool addVar(ABC_Var* var)=0;

    virtual ~ABC_Var(){}
    virtual bool isInDomain(const ABC_Var* value)const=0;

    virtual ABC_Var* varTemplate()const=0;

    virtual bool unload_ABC_Var()=0;
    virtual ABC_Var* load_ABC_Var() =0;

    template<typename T>
    bool getValue(const std::string& name, T& value)const;

    template<typename T>
    bool setValue(const std::string& name, const T& value);

    bool getCategory(const std::string& name, int& i)const;
    bool setCategory(const std::string &name, const std::string& categ);


  };



  class Implements_VarId: virtual public ABC_Var
  { // ABC_Var interface
  public:
    virtual std::string myClass() const override;
    virtual std::deque<Token_New> toTokens() const override;
    virtual bool processTokens(const std::deque<Token_New> &t,
                               std::size_t& pos) override;
    virtual std::string id()const override;
    virtual void setId(const std::string& IdName)override;

    virtual std::string Tip()const override;
    virtual std::string WhatThis()const override;
    virtual void setTip(const std::string& tip)override;
    virtual void setWhatThis(const std::string& whatThis)override;

    virtual ABC_Var *parentVar() override;
    virtual const ABC_Var *parentVar() const override;
    virtual std::size_t numChildVars() const override;
    virtual std::string ith_Var(std::size_t i) const override;
    virtual const ABC_Var* getVarId(const std::string& name)const override;
    virtual ABC_Var* getVarId(const std::string &name) override;
    virtual const ABC_Var* getVarId(const std::string& name,const std::string& kind)const  override;
    virtual ABC_Var* getVarId(const std::string &name, const std::string &kind) override;
    virtual bool addVar(ABC_Var *var) override;
    virtual std::string refId()const override;
    virtual ABC_Var* refVar() override;
    virtual const ABC_Var* refVar() const override;
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
    virtual ~Implements_VarId(){}

    virtual bool unload_ABC_Var()override;
    virtual ABC_Var* load_ABC_Var()override;


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
    static std::set<std::string> SuperClasses();

    virtual std::set<std::string> mySuperClasses()  override;

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


    // ABC_Var interface
  public:
    // we need a mother class that knows our template type!
    virtual const ABC_Var* motherClass()const override;

    virtual std::deque<Token_New> toTokens() const override;

    virtual bool processTokens(const std::deque<Token_New>& tokenList,
                               std::size_t& pos)override;

    Implements_Simple_Var(ABC_Var* parent,
                          std::string id,
                          T val,
                          std::string className=ClassName(),
                          const std::string& tip="",
                          const std::string& whatthis="");

    Implements_Simple_Var()=default;
    virtual ~Implements_Simple_Var(){}

    virtual Implements_Simple_Var<T>* load_ABC_Var()  override;

  private:
    T value_;
  };


  class Implements_Complex_Var:virtual public ABC_Var, public Implements_VarId
  {

    // ABC_Var interface
  public:

    static std::string ClassName();

    virtual std::size_t numChildVars() const override;
    virtual std::string ith_Var(std::size_t i) const override;
    virtual const ABC_Var* getVarId(const std::string& name)const override;
    virtual  ABC_Var* getVarId(const std::string& name)override;
    virtual const ABC_Var* getVarId(const std::string& name,
                                    const std::string &myclass)const override;
    virtual ABC_Var* getVarId(const std::string& name, const std::string &myclass) override;
    virtual bool addVar(ABC_Var *var) override;
    Implements_Complex_Var(ABC_Var *parent,
                           const std::string& id,
                           const std::string className,
                           const std::vector<ABC_Var*>& childs,
                           const std::string & tip,
                           const std::string& whatthis);

    Implements_Complex_Var(){}

    virtual ~Implements_Complex_Var();

    virtual std::deque<Token_New> toTokens() const override;

    virtual bool processTokens(const std::deque<Token_New> &tokenList,
                               std::size_t &pos) override;



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
    virtual ABC_Var* refVar() override;

    virtual const ABC_Var* refVar()const override;


    Implements_Refer_Var(ABC_Var* parent,
                         const std::string &idName,
                         const std::string& refClass,
                         const std::string &refName, const std::string& tip,const std::string& whatthis);

    Implements_Refer_Var()=default;

  private:
    std::string refId_;
    // ABC_Var interface
  public:
    virtual std::deque<Token_New> toTokens() const override;
    virtual bool processTokens(const std::deque<Token_New> &t,
                               std::size_t& pos)override;


    virtual std::string ith_Var(std::size_t i)const  override;

    virtual const ABC_Var* getVarId(const std::string& name)const  override;
    virtual ABC_Var* getVarId(const std::string &name)  override;

    virtual const ABC_Var* getVarId(const std::string& name,const std::string& kind)const  override;
    virtual ABC_Var* getVarId(const std::string &name, const std::string &kind)  override;


    virtual bool addVar(ABC_Var* var) override;

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

  class Implements_Categorical : public Implements_Simple_Var<std::string>
  {
public:
    static std::string ClassName();

    static std::set<std::string> SuperClasses();

    virtual std::set<std::string> mySuperClasses()override;


    // ABC_Var interface
  public:
    std::string Category()const;

    int Rank()const;

    void updateCat();
    void updateRank();

    void setCategory(const std::string& cat);

    void setRank(int i);

    Implements_Categorical(ABC_Var* parent, const std::string& idName,int i, const std::string& categoryClass);
    Implements_Categorical(ABC_Var* parent, const std::string& idName, const std::string &cat, const std::string& categoryClass);

    virtual const Implements_Categorical_Class* motherClass()const;
    virtual Implements_Categorical_Class* motherClass();


  private:
    int rank_;
  };



  template<>
  std::string Implements_Simple_Var<std::vector<std::string>>::ClassName();

  template<>
  std::string Implements_Simple_Var<std::string>::ClassName();




  inline std::ostream& operator<<(std::ostream& os, std::vector<std::string> data )
  {
    for (std::string s:data)
      {
        os<<s<<"\t";
      }
    return os;
  }

  template<>
  bool ABC_Var::getValue(const std::string &name, ABC_Var*& value) const
  {
    const ABC_Var* o=getVarId(name);
    if (o!=nullptr)
      {
        value=o->value();
        return true;
      }
    else
      return false;
   }


  template<typename T>
  bool ABC_Var::getValue(const std::string &name, T &value) const
  {
    const Implements_Simple_Var<T>* o=dynamic_cast<const Implements_Simple_Var<T>*>(getVarId(name));

    if (o!=nullptr)
      {
        value=o->value();
        return true;
      }
    else
      return false;
   }

  template<>
  bool ABC_Var::setValue(const std::string &name, const ABC_Var* &value)
  {
    ABC_Var* o=getVarId(name);

    if (o!=nullptr)
      {
        o->setValue(value);
        return true;
      }
    else
      return false;
   }

  template<typename T>
  bool ABC_Var::setValue(const std::string &name, const T &value)
  {
    Implements_Simple_Var<T>* o=dynamic_cast<Implements_Simple_Var<T>*>(getVarId(name));

    if (o!=nullptr)
      {
        o->setValue(value);
        return true;
      }
    else
      return false;
   }




}

#endif // ABC_VAR_H
