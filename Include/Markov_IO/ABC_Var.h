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


  inline std::deque<Token_New>& operator<<(std::deque<Token_New>& tok1,
                                           const std::deque<Token_New>& tok2)
  {
    tok1.insert(tok1.end(),tok2.begin(),tok2.end());
    return tok1;
  }

  inline std::deque<Token_New>& operator<<(std::deque<Token_New>& tok,
                                           const std::string& text)
  {
    std::stringstream ss(text);
    Token_New t;
    while (t.get(ss))
      {
        tok.push_back(t);
      }

    return tok;
  }
  inline std::deque<Token_New>& operator<<(std::deque<Token_New>& tok,
                                           double d)
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

  std::set<std::string> operator+(std::set<std::string>&& tok1,
                                  std::string &&s);


  std::set<std::string> operator+(std::set<std::string> &&ss1,
                                  std::set<std::string> &&ss2);


  class ABC_Class;

  class ABC_Var
  {
  public:


    static ABC_Var* getFromTokens(ABC_Complex_Var* parent,
                                  const std::deque<Token_New>& tokensList,
                                  std::size_t& pos);


    static bool isValidId(std::string name);

    static std::string ClassName()
    {
      return "ABC_Var";
    }

    static std::set<std::string> SuperClasses()
    {
      return {ClassName()};
    }


    virtual std::string id()const=0;
    virtual void setId(const std::string& idName)=0;
    virtual std::string refId()const=0;

    virtual const ABC_Var* refVar()const=0;
    virtual ABC_Var* refVar()=0;



    virtual std::string myClass()const=0;

    virtual std::set<std::string> mySuperClasses()
    {
      return SuperClasses();
    }

    virtual const ABC_Class* motherClass()const=0;

    virtual std::deque<Token_New> toTokens()const=0;

    virtual bool processTokens(const std::deque<Token_New>& tokenList,
                               std::size_t& pos)=0;


    virtual std::string toString()const;

    virtual std::size_t numChildVars()const=0;

    virtual ABC_Complex_Var* parentVar()const =0;

    virtual void setParentVar(ABC_Complex_Var* par)=0;

    virtual ~ABC_Var(){}
    virtual bool isInDomain(const ABC_Var* value)const=0;
    virtual ABC_Var* varTemplate()const=0;

  };


  class ABC_Class: virtual public ABC_Var
  {
  public:
    static std::string ClassName()
    {
      return "ABC_Class";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Var::SuperClasses()+ClassName();
    }

    virtual std::set<std::string> mySuperClasses() override
    {
      return SuperClasses();
    }

  };




  class ABC_Complex_Var:virtual public ABC_Var
  {
  public:
    static std::string ClassName()
    {
      return "ABC_Complex_Var";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Var::SuperClasses()+ClassName();
    }
    virtual std::set<std::string> mySuperClasses() override
    {
      return SuperClasses();
    }


    virtual std::string ith_Var(std::size_t i)const=0;

    virtual const ABC_Var* getVarId(const std::string& name)const=0;
    virtual ABC_Var* getVarId(const std::string &name)=0;

    virtual const ABC_Var* getVarId(const std::string& name,const std::string& kind)const=0;
    virtual ABC_Var* getVarId(const std::string &name, const std::string &kind) =0;

    virtual bool addVar(ABC_Var* var)=0;

    virtual const ABC_Environment_Var* getEnvironment()const=0;
    virtual ABC_Environment_Var* getEnvironment()=0;

    virtual ~ABC_Complex_Var(){}

  };


  class ABC_Environment_Var: virtual public ABC_Complex_Var
  {
  public:

    static std::string ClassName()
    {
      return "ABC_Environment_Var";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Class::SuperClasses()+ABC_Complex_Var::SuperClasses()+ClassName();
    }


    virtual std::set<std::string> mySuperClasses() override
    {
      return SuperClasses();
    }

    virtual std::size_t numChildClass()const=0;

    virtual std::string ith_Class(std::size_t i)const=0;

    virtual const ABC_Class* getClassId(const std::string& name)const=0;

    virtual ABC_Class* getClassId(const std::string &name)=0;


    virtual bool addClass(ABC_Class* var)=0;

    virtual ~ABC_Environment_Var(){}
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
    virtual bool processTokens(const std::deque<Token_New> &t,
                               std::size_t& pos) override;

    virtual std::string id()const override;
    virtual void setId(const std::string& IdName)override;
    virtual std::size_t numChildVars() const override;
    virtual ABC_Complex_Var *parentVar()const override;

    virtual std::string refId()const override;

    virtual ABC_Var* refVar() override;

    virtual const ABC_Var* refVar() const override;

    virtual const ABC_Class* motherClass()const
    {
      if ((parentVar()!=nullptr)&&(parentVar()->getEnvironment()!=nullptr))
        return parentVar()->getEnvironment()->getClassId(myClass());
      else
        return nullptr;

    }

    Implements_VarId(ABC_Complex_Var* parent,
                     const std::string& name,
                     const std::string className);

    Implements_VarId();

    virtual void setParentVar(ABC_Complex_Var *par)override;
    virtual bool isInDomain(const ABC_Var* value)const
    {
      auto p= motherClass();
      if (p!=nullptr)
        return p->isInDomain(value);
      else
        return false;

    }
    virtual ABC_Var* varTemplate()const
    {
      auto p= motherClass();
      if (p!=nullptr)
        return p->varTemplate();
      else
        return nullptr;

    }

    virtual ~Implements_VarId(){}
  protected:

    std::string id_;
    std::string class_;
    ABC_Complex_Var* p_;
  };

  class Implements_ClassId: virtual public ABC_Class,public Implements_VarId
  {
  public:
    virtual std::deque<Token_New> toTokens() const override;
    virtual bool processTokens(const std::deque<Token_New> &t,
                               std::size_t& pos) override;


    Implements_ClassId(ABC_Complex_Var* parent,
                       const std::string& name,
                       const std::string className):
      Implements_VarId(parent,name,className){}

    Implements_ClassId():
      Implements_VarId(){}

    virtual ~Implements_ClassId(){}
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

    T value()const;
    void setValue(T val);


    // ABC_Var interface
  public:

    virtual const Implements_Simple_Class<T>* motherClass()const
    {
      if ((parentVar()!=nullptr)&&(parentVar()->getEnvironment()!=nullptr))
        {
          auto p=parentVar()->getEnvironment()->getClassId(myClass());
          return dynamic_cast<const Implements_Simple_Class<T>*>(p);
        }
      else
        return nullptr;
    }

    virtual std::deque<Token_New> toTokens() const override;

    virtual bool processTokens(const std::deque<Token_New>& tokenList,
                               std::size_t& pos)override;


    Implements_Simple_Var(ABC_Complex_Var* parent,
                          std::string id,
                          T val,
                          std::string className=ClassName());

    Implements_Simple_Var()=default;



    virtual ~Implements_Simple_Var(){}

  private:
    T value_;


  };



  template<typename T>
  class Implements_Simple_Class: public Implements_ClassId
  {
    // ABC_Var interface
  public:
    static std::string ClassName();

    static std::set<std::string> SuperClasses()
    {
      return ABC_Class::SuperClasses()<<ClassName();
    }

    virtual std::set<std::string> mySuperClasses()
    {
      return SuperClasses();
    }


    T defaultValue()const
    {
      return default_;
    }
    T minValue()const
    {
      return min_;
    }
    T maxValue()const
    {
      return max_;
    }
    T emptyValue()const
    {
      return T();
    }
    T unknownValue()const
    {
      std::numeric_limits<T>::quiet_NaN();
    }

    void setDefaultValue(T val)
    {
      default_=val;
    }

    void setminValue(T val)
    {
      min_=val;
    }

    void setmaxValue(T val)
    {
      max_=val;
    }


    virtual bool toValue(const std::deque<Token_New> &tok,
                         T &val,
                         std::size_t& i=0)const;

    virtual std::deque<Token_New> toToken(const T& val)const;


    virtual std::deque<Token_New> toTokens() const override
    {
      auto out=Implements_ClassId::toTokens();

      out<<"\n"<<"default"<<"="<<toToken(defaultValue());
      if (minValue()!=emptyValue())

        out<<"\n"<<"min"<<"="<<toToken(minValue());
      if (maxValue()!=emptyValue())

        out<<"\n"<<"max"<<"="<<toToken(defaultValue());
      out<<"\n";
      return out;
    }

    virtual bool processTokens(const std::deque<Token_New>& t,
                               std::size_t& pos)override
    {
      if (!Implements_ClassId::processTokens(t,pos))
        return false;

      else if ((!pos+2<t.size())
               ||(t.at(pos).tok()!=Token_New::EOL)
               ||(t.at(pos+1).str()!="default")
               ||(t.at(pos+2).tok()!=Token_New::EQ))
        return false;
      else
        {
          pos+=3;
          T val;
          if (!toValue(t,val,pos))
            return false;
          else
            {
              default_=val;
              if ((pos+2<t.size())
                  &&(t.at(pos).tok()==Token_New::EOL)
                  &&(t.at(pos+1).str()=="min")
                  &&(t.at(pos+2).tok()==Token_New::EQ))
                {
                  pos+=3;
                  T valmin;
                  if (!toValue(t,valmin,pos))
                    return false;
                  else
                    min_=valmin;

                }
              if ((pos+2<t.size())
                  &&(t.at(pos).tok()==Token_New::EOL)
                  &&(t.at(pos+1).str()=="max")
                  &&(t.at(pos+2).tok()==Token_New::EQ))
                {
                  pos+=3;
                  T valmax;
                  if (!toValue(t,valmax,pos))
                    return false;
                  else
                    max_=valmax;
                }
              if ((pos<t.size())
                  &&(t.at(pos).tok()==Token_New::EOL))
                {
                  ++pos;
                }
              return true;
            }
        }

    }


    Implements_Simple_Class(ABC_Complex_Var* parent,
                            std::string id,
                            T defaultValue=T(),
                            T minValue=T(),
                            T maxValue=T(),
                            std::string className=ClassName()):
      Implements_VarId(parent,id,className),
      default_(defaultValue), min_(minValue),max_(maxValue){}


    Implements_Simple_Class():
      Implements_VarId(0,ClassName(),ClassName()),
      default_{}, min_{},max_{}{}


    virtual ~Implements_Simple_Class(){}
    virtual Implements_Simple_Var<T>* varTemplate()const
    {
      return new Implements_Simple_Var<T>(this,"",defaultValue(),id());
    }

    virtual bool isInDomain(const ABC_Var *value) const
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


    Implements_Refer_Var(ABC_Complex_Var* parent,
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



  };


  class Implements_Complex_Var:virtual public ABC_Complex_Var, public Implements_VarId
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

    virtual const ABC_Environment_Var* getEnvironment()const override;

    virtual  ABC_Environment_Var* getEnvironment() override;


    Implements_Complex_Var(ABC_Complex_Var *parent,
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


  class Implements_Complex_Class: public Implements_Complex_Var
  {
  public:

    Implements_Complex_Class(ABC_Complex_Var *parent,
                             const std::string& id,
                             const std::string className,
                             const std::map<std::string, std::pair<std::string,std::string>>
                             id_superClass_ClassId):
      Implements_Complex_Var(parent,id,className,toRefVec(parent,id_superClass_ClassId)){}

    virtual bool isInDomain(const ABC_Complex_Var *value) const
    {
      if (value->myClass()!=id())
        return false;
      if (numChildVars()!=value->numChildVars())
        return false;
      for (std::size_t i=0; i<numChildVars(); ++i)
        {
          auto iname=ith_Var(i);
          auto valueVar=value->getVarId(iname);
          if (valueVar==nullptr)
            return false;
          else if (!getVarId(iname)->refVar()->isInDomain(valueVar))
            return false;
        }
      return true;

    }
    virtual Implements_Complex_Var *varTemplate() const
    {
      return new Implements_Complex_Var(parentVar(),"",id(),getChildVars());
    }
  protected:
    std::vector<ABC_Var*> getChildVars()const
    {
      std::vector<ABC_Var*> out;
      for (std::size_t i=0; i<numChildVars(); i++)
        {
          auto v=getVarId(ith_Var(i))->refVar()->varTemplate();
          v->setId(ith_Var(i));
          out.push_back(v);
        }
      return out;

    }
    static std::vector<ABC_Var*> toRefVec
    (ABC_Complex_Var *parent,
     const std::map<std::string,std::pair<std::string,std::string>>& id_superClass_ClassId)
    {
      std::vector<ABC_Var*> out;
      for (auto e:id_superClass_ClassId)
        {
          out.push_back(new Implements_Refer_Var(parent,
                                                 e.first,
                                                 e.second.first,
                                                 e.second.second));
        }
      return out;
    }

    // ABC_Complex_Var interface
  public:
    virtual std::string ith_Var(std::size_t i) const;
    virtual bool addVar(ABC_Var *var);


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





    Categorical_Options(ABC_Complex_Var* parent,
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


    Categorical_Data(ABC_Complex_Var* parent,
                     std::string categoricalData,
                     int ind,
                     std::string catclass):
      Implements_Simple_Var<int>(parent,categoricalData,ind,catclass){}

    Categorical_Data()=default;

    virtual ~Categorical_Data(){}


  };

  class Implement_Environment_Var:public ABC_Environment_Var,
      public Implements_Complex_Var
  {
  public:

    static std::string ClassName()
    {
      return   "Implement_Complex_Class";
    }

    virtual std::size_t numChildClass()const override
    {
      return idsClass_.size();
    }
    virtual  std::string ith_Class(std::size_t i)const override
    {
      return idsClass_[i];
    }
    virtual  const ABC_Class* getClassId(const std::string& name)const override
    {
      auto it=classKinds_.find(name);
      if(it!=classKinds_.end())
        return it->second;
      else return nullptr;
    }
    virtual   ABC_Class* getClassId(const std::string& name) override
    {
      auto it=classKinds_.find(name);
      if(it!=classKinds_.end())
        return it->second;
      else return nullptr;

    }
    virtual bool addClass(ABC_Class* var) override
    {
      if (var==nullptr)
        return false;
      var->setParentVar(this);

      if (std::find (idsClass_.begin(),idsClass_.end(),var->id())==idsClass_.end())
        {
          idsClass_.push_back(var->id());
          classKinds_[var->id()]=var;
          return true;
        }
      else
        {
          delete  classKinds_[var->id()];
          classKinds_[var->id()]=var;
          return false;
        }
    }

    Implement_Environment_Var():
      Implements_Complex_Var(this,"",ClassName(),{}){}


    Implement_Environment_Var(ABC_Environment_Var* parent,
                              const std::string& name,
                              const std::string classN):
      Implements_Complex_Var(parent,name,classN,{}),
      idsClass_{},classKinds_{}{}

    virtual  Implement_Environment_Var* getEnvironment()const override
    {
      return const_cast<Implement_Environment_Var*>(this);
    }

    virtual ~Implement_Environment_Var()
    {
      for (std::pair<std::string,ABC_Var*> e:classKinds_)
        {
          delete e.second;
        }

    }



  protected:


    std::vector<std::string> idsClass_;
    std::map<std::string,ABC_Class*> classKinds_;
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
