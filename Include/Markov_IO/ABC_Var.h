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

    double num()const;

    int  intval()const;

    std::size_t count()const;

    Value tok()const;

    std::string toString()const;


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
  inline bool toValue(const std::deque<Token_New> &tok,
                      T &val,
                      std::size_t& i=0);

  template<typename T>
  inline std::deque<Token_New> toToken(const T& val)
  {
    std::deque<Token_New> out;
    out<<val;
    return out;
  }


  template<typename T>
  std::deque<Token_New>& operator<<(std::deque<Token_New>& tok, std::vector<T> v)
  {
    for (T e:v)
      tok.push_back(Token_New(e));
    return tok;
  }

  template<>
  inline bool toValue(const std::deque<Token_New> &tok,double &val,
               std::size_t& i)
  {
    if (tok.at(i).tok()!=Token_New::REAL)
      return false;
    else
      {
        val=tok.at(i).num();
        ++i;
        return true;
      }
  }


  template<>
  inline bool toValue(const std::deque<Token_New> &tok,
               int &val,
               std::size_t& i)
  {
    if (tok.at(i).tok()!=Token_New::INTEGER)
      return false;
    else
      {
        val=tok.at(i).num();
        ++i;
        return true;
      }
  }

  template<>
  inline bool toValue(const std::deque<Token_New> &tok,
               std::size_t &val,
               std::size_t& i)
  {
    if (tok.at(i).tok()!=Token_New::UNSIGNED)
      return false;
    else
      {
        val=tok.at(i).num();
        ++i;
        return true;
      }
  }


  template<>
  inline bool toValue(const std::deque<Token_New> &tok,
               std::string &val,
               std::size_t& i)
  {
    if (tok.at(i).tok()!=Token_New::IDENTIFIER)
      return false;
    else
      {
        val=tok.at(i).str();
        ++i;
        return true;
      }
  }


  template<>
  inline bool toValue(const std::deque<Token_New> &tok,
          std::vector<std::string> &val,
          std::size_t& i)
  {
    if (tok.at(i).tok()!=Token_New::IDENTIFIER)
      return false;
    else
      {
        while ((i<tok.size())&&(tok.at(i).tok()==Token_New::IDENTIFIER))
          {
            val.push_back(tok.at(i).str());
            ++i;
          }

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

    virtual ABC_Var* parentVar()const =0;

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
    virtual ABC_Var *parentVar()const override;
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
    virtual ABC_Var* varTemplate()const override;
    Implements_VarId(ABC_Var* parent,
                     const std::string& name,
                     const std::string className);
    Implements_VarId();
    virtual ~Implements_VarId(){}
  protected:
    std::string id_;
    std::string class_;
    ABC_Var* p_;
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

    T value()const;
    void setValue(T val);


    // ABC_Var interface
  public:
    // we need a mother class that knows our template type!
    virtual const Implements_Simple_Class<T>* motherClass()const override;

    virtual std::deque<Token_New> toTokens() const override;

    virtual bool processTokens(const std::deque<Token_New>& tokenList,
                               std::size_t& pos)override;

    Implements_Simple_Var(ABC_Var* parent,
                          std::string id,
                          T val,
                          std::string className=ClassName());

    Implements_Simple_Var()=default;
    virtual ~Implements_Simple_Var(){}

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
                           const std::vector<ABC_Var*>& childs);

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
                            std::string className=ClassName()):
      Implements_Complex_Var(parent,id,className,{})
    {
      addVar(new Implements_Simple_Var<T>(this,"default",defaultValue));
      addVar(new Implements_Simple_Var<T>(this,"min",minValue));
      addVar(new Implements_Simple_Var<T>(this,"max",maxValue));

    }


    Implements_Simple_Class():
      Implements_VarId(0,ClassName(),ClassName()),
      default_{}, min_{},max_{}{}


    virtual ~Implements_Simple_Class(){}
    virtual Implements_Simple_Var<T>* varTemplate()const  override
    {
      return new Implements_Simple_Var<T>(this,"",defaultValue(),id());
    }

    virtual bool isInDomain(const ABC_Var *value) const  override
    {
      Implements_Simple_Var<T>* p=dynamic_cast<Implements_Simple_Var<T>* > (value);
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

    T default_;
    T min_;
    T max_;
  };





  class Implements_Refer_Var:public Implements_VarId
  {
    // ABC_Var interface
  public:

    static std::string ClassName()
    {
      return "Refers_Variable";
    }

    virtual std::string refId()const override;
    virtual ABC_Var* refVar() override;

    virtual const ABC_Var* refVar()const override;


    Implements_Refer_Var(ABC_Var* parent,
                         std::string idName,
                         std::string refClass,
                         std::string refName);

    Implements_Refer_Var()=default;

  private:
    std::string refId_;
    // ABC_Var interface
  public:
    virtual std::deque<Token_New> toTokens() const override;
    virtual bool processTokens(const std::deque<Token_New> &t,
                               std::size_t& pos)override;


    virtual std::string ith_Var(std::size_t i)const  override
    {
      if (refVar()!=nullptr)
        return refVar()->ith_Var(i);
      else return {};
    }

    virtual const ABC_Var* getVarId(const std::string& name)const  override
    {
      if (refVar()!=nullptr)
        return refVar()->getVarId(name);
      else return {};
    }
    virtual ABC_Var* getVarId(const std::string &name)  override
    {
      if (refVar()!=nullptr)
        return refVar()->getVarId(name);
      else return {};
    }

    virtual const ABC_Var* getVarId(const std::string& name,const std::string& kind)const  override
    {
      if (refVar()!=nullptr)
        return refVar()->getVarId(name,kind);
      else return {};
    }
    virtual ABC_Var* getVarId(const std::string &name, const std::string &kind)  override
    {
      if (refVar()!=nullptr)
        return refVar()->getVarId(name,kind);
      else return {};
    }


    virtual bool addVar(ABC_Var* var) override;




  };





  class Implements_Complex_Class: public Implements_Complex_Var
  {
  public:

    Implements_Complex_Class(ABC_Var *parent,
                             const std::string& id,
                             const std::string className,
                             const std::map<std::string, std::pair<std::string,std::string>>
                             id_superClass_ClassId);

    virtual bool isInDomain(const ABC_Var *value) const  override;
    virtual Implements_Complex_Var *varTemplate() const override;
  protected:
    std::vector<ABC_Var*> getChildVars()const;

    // ABC_Complex_Var interface
  public:
    virtual void push_back(const std::string& idName,
                           const std::string& superclassname,
                           const std::string& classname)
    {
      addVar(new Implements_Refer_Var(parentVar(),idName,superclassname, classname));
    }


  };




  class Implements_Categorical : virtual public ABC_Var, public Implements_VarId
  {




  };


  template<>
  std::string Implements_Simple_Var<std::vector<std::string>>::ClassName();

  class Categorical_Options: public Implements_Simple_Var<std::vector<std::string> >
  {
    // ABC_Var interface
  public:
    static std::string ClassName()
    {
      return "Categorical_Options";
    }





    Categorical_Options(ABC_Var* parent,
                        std::string id,
                        const std::vector<std::string>& options):
      Implements_Simple_Var<std::vector<std::string> >(parent,id,options)
    {}

    Categorical_Options()=default;

    virtual ~Categorical_Options(){}



  };


  template<>
  std::string Implements_Simple_Var<std::string>::ClassName();


  class Categorical_Data: public Implements_Simple_Var<int>
  {
    // ABC_Var interface
  public:
    static std::string ClassName()
    {
      return "Categorical_Data";
    }


    Categorical_Data(ABC_Var* parent,
                     std::string categoricalData,
                     int ind,
                     std::string catclass):
      Implements_Simple_Var<int>(parent,categoricalData,ind,catclass){}

    Categorical_Data()=default;

    virtual ~Categorical_Data(){}


  };


  inline std::ostream& operator<<(std::ostream& os, std::vector<std::string> data )
  {
    for (std::string s:data)
      {
        os<<s<<"\t";
      }
    return os;
  }





}

#endif // ABC_VAR_H
