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

  class ABC_Complex_Var;

  class ABC_Environment_Var;



  class Token_New
  {
  public:
    static bool isNameChar(char ch);
    static bool isSpaceChar(char ch);
    static std::string toString(double number)
    {
      std::stringstream ss;
      ss<<std::setprecision(std::numeric_limits<double>::digits10)<<number;
      return ss.str();
    }
    enum Value {
      IDENTIFIER,
      STRING,
      PATH,
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

    std::string str()const
    {
      return str_;
    }

    double num()const
    {
      return number_;
    }

    Value tok()const
    {
      return curr_tok;
    }

    std::string toString()const
    {
      if (tok()==NUMBER)
        return toString(number_);
      else
        return str_;
    }


    static Value toKeyword(std::string identifier);
    static std::string toString(Value identifier);



    Token_New()=default;

    Token_New(double d):
      curr_tok{NUMBER},
      number_(d),
      str_{}{}

    Token_New(std::string d):
      curr_tok{},
      number_{},
      str_{}{
      std::stringstream ss(d);
      get(ss);
    }
    Token_New(Value v):
      curr_tok{v},
      number_{},
      str_{toString(v)}{}

  private:
    Value curr_tok;
    double number_;
    std::string str_;
  };


  inline std::deque<Token_New>& operator<<(std::deque<Token_New>& tok1, const std::deque<Token_New>& tok2)
  {
    tok1.insert(tok1.end(),tok2.begin(),tok2.end());
    return tok1;
  }

  inline std::deque<Token_New>& operator<<(std::deque<Token_New>& tok, const std::string& text)
  {
    std::stringstream ss(text);
    Token_New t;
    while (t.get(ss))
      {
        tok.push_back(t);
      }

    return tok;
  }
  inline std::deque<Token_New>& operator<<(std::deque<Token_New>& tok, double d)
  {
    tok.push_back(Token_New(d));
    return tok;
  }

  template<typename T>
  std::deque<Token_New>& operator<<(std::deque<Token_New>& tok, std::vector<T> v)
  {
    for (T e:v)
      tok.push_back(Token_New(e));
    return tok;
  }


  class ABC_Var
  {
  public:


    static ABC_Var* getFromTokens(ABC_Complex_Var* parent,
        const std::deque<Token_New>& tokensList,
        std::size_t& pos);


    static bool isValidId(std::string name)
    {
      return Token_New(name).tok()==Token_New::IDENTIFIER;
    }

    virtual std::string id()const=0;
    virtual std::string refId()const=0;

    virtual const ABC_Var* refVar()const=0;
    virtual ABC_Var* refVar()=0;

    virtual std::string myClass()const=0;

    virtual std::deque<Token_New> toTokens()const=0;

    virtual std::size_t processTokens(const std::deque<Token_New>& tokenList,
                                      std::size_t pos)=0;


    virtual std::string toString()const;

    virtual std::size_t numChildVars()const=0;

    virtual ABC_Complex_Var* parentVar()const =0;

    virtual void setParent(ABC_Complex_Var* par)=0;

    virtual ABC_Var* clone()const=0;

    virtual ~ABC_Var(){}

  };


  class ABC_Complex_Var:virtual public ABC_Var
  {
  public:

    virtual std::string ith_Var(std::size_t i)const=0;

    virtual const ABC_Var* getVarId(const std::string& name)const=0;
    virtual ABC_Var* getVarId(const std::string &name)=0;

    virtual const ABC_Var* getVarId(const std::string& name,const std::string& kind)const=0;
    virtual ABC_Var* getVarId(const std::string &name, const std::string &kind) =0;

    virtual bool addVar(ABC_Var* var)=0;

    virtual const ABC_Environment_Var* getEnvironment()const=0;
    virtual ABC_Environment_Var* getEnvironment()=0;

    virtual ABC_Complex_Var* clone()const=0;

    virtual ~ABC_Complex_Var(){}
  };




  class ABC_Environment_Var:virtual public ABC_Complex_Var
  {
  public:
    virtual std::size_t numClasses()const=0;
    virtual  std::string classId(std::size_t i)const=0;
    virtual  const ABC_Var* getClassId(std::string name)const=0;
    virtual   ABC_Var* getClassId(std::string name)=0;

    virtual bool addClass(ABC_Var* var,const std::string& className="")=0;

    virtual ABC_Environment_Var* clone()const=0;

  };

  
  class Implements_VarId: virtual public ABC_Var
  { // ABC_Var interface
  public:
    virtual std::string myClass() const override
    {
      return class_;
    }
  public:
    virtual std::deque<Token_New> toTokens() const override;
    virtual std::size_t processTokens(const std::deque<Token_New> &t,
                                      std::size_t pos) override;

    virtual std::string id()const override;
    virtual std::size_t numChildVars() const override;
    virtual ABC_Complex_Var *parentVar()const override;

    virtual std::string refId()const override;

    virtual ABC_Var* refVar() override;

    virtual const ABC_Var* refVar() const override;

    Implements_VarId(ABC_Complex_Var* parent,
                     const std::string& name,
                     const std::string className);

    Implements_VarId();

    virtual void setParent(ABC_Complex_Var *par)override;

    virtual Implements_VarId* clone()const
    {
      return new Implements_VarId(nullptr,"",myClass());
    }

    virtual ~Implements_VarId(){}
  protected:

    std::string id_;
    std::string class_;
    ABC_Complex_Var* p_;


    // ABC_Var interface
  };



  template<typename T>
  class Implements_Simple_Var: public Implements_VarId
  {
    // ABC_Var interface
  public:
    static std::string ClassName();

    T value()const;

    void setValue(T val);


    static std::size_t toValue(const std::deque<Token_New> &tok,
                               T &val,
                               std::size_t i=0);

    static std::deque<Token_New> toToken(const T& val);


    // ABC_Var interface
  public:
    virtual std::deque<Token_New> toTokens() const override;

    virtual std::size_t processTokens(const std::deque<Token_New>& tokenList,
                                      std::size_t pos)override;


    Implements_Simple_Var(ABC_Complex_Var* parent,
                          std::string id,
                          T val,
                          std::string className=ClassName());

    Implements_Simple_Var()=default;



    virtual Implements_Simple_Var* clone()const
    {
      return new Implements_Simple_Var(nullptr,"",{},myClass());
    }

    virtual ~Implements_Simple_Var(){}

  private:
    T value_;

  };



  class Implements_Refer_Var:public Implements_VarId
  {
    // ABC_Var interface
  public:

    static std::string ClassName()
    {
      return "Refers_Variable";
    }

    virtual std::string refId()const;
    virtual ABC_Var* refVar();

    virtual const ABC_Var* refVar()const ;


    Implements_Refer_Var(ABC_Complex_Var* parent,
                         std::string idName,
                         std::string refClass,
                         std::string refName);

    Implements_Refer_Var()=default;

    virtual Implements_Refer_Var* clone()const
    {
      return new Implements_Refer_Var(nullptr,"",myClass(),"");
    }

  private:
    std::string refId_;
    // ABC_Var interface
  public:
    virtual std::deque<Token_New> toTokens() const;
    virtual std::size_t processTokens(const std::deque<Token_New> &t,
                                      std::size_t pos)override;
  };


  class Implements_Complex_Var:virtual public ABC_Complex_Var, public Implements_VarId
  {

    // ABC_Var interface
  public:

    static std::string ClassName()
    {
      return "Complex_Var";
    }

    virtual std::size_t numChildVars() const;

    // ABC_Complex_Var interface
  public:

    virtual std::string ith_Var(std::size_t i) const
    {
      return ids_[i];
    }



    virtual const ABC_Var* getVarId(const std::string& name)const override
    {
      auto it=vars_.find(name);
      if (it!=vars_.end())
        return it->second;
      else
        return nullptr;
    }

    virtual  ABC_Var* getVarId(const std::string& name)override
    {
      auto it=vars_.find(name);
      if (it!=vars_.end())
        return it->second;
      else
        return nullptr;
    }

    virtual const ABC_Var* getVarId(const std::string& name,
                                    const std::string &myclass)const override
    {
      const ABC_Var* out=getVarId(name);
      if ((out!=nullptr)&&(out->myClass()==myclass))
        return out;
      else
        return nullptr;
    }
    virtual ABC_Var* getVarId(const std::string& name, const std::string &myclass) override
    {
      ABC_Var* out=getVarId(name);
      if ((out!=nullptr)&&(out->myClass()==myclass))
        return out;
      else
        return nullptr;
    }


    virtual bool addVar(ABC_Var *var);

    virtual const ABC_Environment_Var* getEnvironment()const;

    virtual  ABC_Environment_Var* getEnvironment();


    Implements_Complex_Var(ABC_Complex_Var* parent,
                           const std::string& id,
                           const std::string className,
                           const std::vector<ABC_Var*>& childs);

    Implements_Complex_Var(){}

    virtual ~Implements_Complex_Var();

    virtual Implements_Complex_Var* clone() const
    {
      Implements_Complex_Var* out=new Implements_Complex_Var(nullptr,"",myClass(),{});
       return makingClone(out);
    }

  protected:
    virtual Implements_Complex_Var* makingClone(Implements_Complex_Var* out)const
    {
      out->ids_=ids_;
      for (std::pair<std::string,ABC_Var*> e:vars_)
        {
           out->vars_[e.first]=e.second->clone();
        }
      return out;
    }

    std::vector<std::string> ids_;
    std::map<std::string,ABC_Var*> vars_;


    // ABC_Var interface
  public:
    virtual std::deque<Token_New> toTokens() const;
    virtual std::size_t processTokens(const std::deque<Token_New> &tokenList,
                                      std::size_t pos);
  };

  class Categorical_Options: public Implements_Simple_Var<std::vector<std::string> >
  {
    // ABC_Var interface
  public:
    static std::string ClassName()
    {
      return "Categorical_Options";
    }

    virtual std::string toString()  const;

    Categorical_Options(ABC_Complex_Var* parent,
                        std::string id,
                        const std::vector<std::string>& options):
      Implements_Simple_Var<std::vector<std::string> >(parent,id,options)
    {}

    Categorical_Options()=default;

    virtual ~Categorical_Options(){}


  };



  class Categorical_Data: public Implements_Simple_Var<std::string>
  {
    // ABC_Var interface
  public:
    static std::string ClassName()
    {
      return "Categorical_Data";
    }


    Categorical_Data(ABC_Complex_Var* parent,
                     std::string categoricalClass,
                     std::string id):
      Implements_Simple_Var<std::string>(parent,id,id){}

    Categorical_Data();

    virtual ~Categorical_Data(){}


  };

  class Implement_Environment_Var:public ABC_Environment_Var, public Implements_Complex_Var
  {
  public:
    virtual std::size_t numClasses()const
    {
      return idsClass_.size();
    }
    virtual  std::string classId(std::size_t i)const
    {
      return idsClass_[i];
    }
    virtual  const ABC_Var* getClassId(std::string name)const
    {
     auto it=classKinds_.find(name);
     if(it!=classKinds_.end())
       return it->second;
     else return nullptr;
    }
    virtual   ABC_Var* getClassId(std::string name)
    {
      auto it=classKinds_.find(name);
      if(it!=classKinds_.end())
        return it->second;
      else return nullptr;

    }
    virtual bool addClass(ABC_Var* var,const std::string& className="")
    {
      if (var==nullptr)
          return false;
      std::string cl=className;
      if (cl.empty())
          cl=var->myClass();
       var->setParent(this);

        if (std::find (idsClass_.begin(),idsClass_.end(),cl)==idsClass_.end())
          {
            idsClass_.push_back(cl);
            classKinds_[cl]=var;
            return true;
          }
        else
          {
            delete  classKinds_[cl];
            classKinds_[cl]=var;
            return false;
          }
      }

     Implement_Environment_Var()=default;
     Implement_Environment_Var(ABC_Environment_Var* parent,
                            const std::string& name,
                            const std::string classN):
       Implements_Complex_Var(parent,name,classN,{}),
       idsClass_{},classKinds_{}{}

    virtual const Implement_Environment_Var* getEnvironment()const
    {
      return this;
    }

    virtual Implement_Environment_Var* clone()const
     {
       Implement_Environment_Var* e=new Implement_Environment_Var(0,"",myClass());
       return makingClone(e);
     }

     virtual ~Implement_Environment_Var()
     {
       for (std::pair<std::string,ABC_Var*> e:classKinds_)
         {
            delete e.second;
         }

     }

  protected:
     virtual Implement_Environment_Var* makingClone(Implement_Environment_Var* out)const
     {
       Implements_Complex_Var::makingClone(out);
       out->idsClass_=idsClass_;
       for (std::pair<std::string,ABC_Var*> e:classKinds_)
         {
            out->classKinds_[e.first]=e.second->clone();
         }
       return out;
     }

    std::vector<std::string> idsClass_;
    std::map<std::string,ABC_Var*> classKinds_;


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
