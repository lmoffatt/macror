#include <numeric>
#include "Markov_IO/ABC_Var.h"



namespace Markov_IO {

  template<>
  std::string Implements_Simple_Var<std::string>::ClassName()
  {
    return "Simple_name_var";
  }

  template<>
  std::string Implements_Simple_Var<double>::ClassName()
  {
    return "Simple_real_var";
  }

  template<>
  std::string Implements_Simple_Var<int>::ClassName()
  {
    return "Simple_integer_var";
  }

  template<>
  std::string Implements_Simple_Var<std::size_t>::ClassName()
  {
    return "Simple_unsigned_var";
  }



  template<>
  std::string Implements_Simple_Var<std::vector<std::string>>::ClassName()
  {
    return "Simple_string_vector_var";
  }




  template<typename T>
  std::deque<Token_New> Implements_Simple_Var<T>::toTokens() const
  {
    auto out=Implements_VarId::toTokens();
    out<<"="<<toToken(value())<<"\n";
    return out;
  }

  template<typename T>
  bool Implements_Simple_Var<T>::processTokens(const std::deque<Token_New>& t,
                                               std::size_t &pos)
  {
    if (!Implements_VarId::processTokens(t,pos))
      return false;
    else
      {
        if (t.at(pos).tok()!=Token_New::EQ)
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

  template<typename T>
  std::set<std::string> Implements_Simple_Var<T>::SuperClasses()
  {
    return ABC_Var::SuperClasses()+ClassName();
  }

  template<typename T>
  std::set<std::string> Implements_Simple_Var<T>::mySuperClasses()
  {
    return SuperClasses();
  }

  template<typename T>
  T Implements_Simple_Var<T>::value() const
  {
    return value_;
  }

  template<typename T>
  void Implements_Simple_Var<T>::setValue(T val)
  {
    value_=val;
  }

  template<typename T>
  const Implements_Simple_Class<T> *Implements_Simple_Var<T>::motherClass() const
  {
    if (parentVar()!=nullptr)
      {
        auto p=parentVar()->getVarId(myClass());
        return dynamic_cast<const Implements_Simple_Class<T>*>(p);
      }
    else
      return nullptr;
  }





  template<typename T>
  Implements_Simple_Var<T>::
  Implements_Simple_Var(ABC_Var *parent,
                        std::string id,
                        T val,
                        std::string className):
    Implements_VarId(parent,id,className),
    value_(val){}



  template
  class Implements_Simple_Var<double>;

  template
  class Implements_Simple_Var<std::string>;

  template
  class Implements_Simple_Var<std::vector<std::string>>;

  template
  class Implements_Simple_Var<int>;


  std::string Implements_VarId::id() const
  {
    return id_;
  }

  void Implements_VarId::setId(const std::string &IdName)
  {
    id_=IdName;
  }

  std::size_t Implements_VarId::numChildVars() const
  {
    return 0;
  }

  std::string Implements_VarId::ith_Var(std::size_t i) const
  {
    return{};
  }

  const ABC_Var *Implements_VarId::getVarId(const std::string &name) const
  {
    if (parentVar()!=nullptr)
      return parentVar()->getVarId(name);
    else return nullptr;
  }

  ABC_Var *Implements_VarId::getVarId(const std::string &name)
  {
    if (parentVar()!=nullptr)
      return parentVar()->getVarId(name);
    else return nullptr;
  }

  const ABC_Var *Implements_VarId::getVarId(const std::string &name, const std::string &kind) const
  {
    if (parentVar()!=nullptr)
      return parentVar()->getVarId(name,kind);
    else return nullptr;
  }

  ABC_Var *Implements_VarId::getVarId(const std::string &name, const std::string &kind)
  {
    if (parentVar()!=nullptr)
      return parentVar()->getVarId(name,kind);
    else return nullptr;
  }

  bool Implements_VarId::addVar(ABC_Var *var)
  {
    if (parentVar()!=nullptr)
      return parentVar()->addVar(var);
  }

  ABC_Var *Implements_VarId::parentVar() const
  {
    return p_;
  }

  std::string Implements_VarId::refId() const
  {
    return id();
  }

  ABC_Var *Implements_VarId::refVar()
  {
    return this;
  }

  const ABC_Var *Implements_VarId::refVar() const
  {
    return this;
  }

  ABC_Var *Implements_VarId::motherClass()
  {
    if (parentVar()!=nullptr)
      return parentVar()->getVarId(myClass());
    else
      return nullptr;

  }

  const ABC_Var *Implements_VarId::motherClass() const
  {
    if (parentVar()!=nullptr)
      return parentVar()->getVarId(myClass());
    else
      return nullptr;

  }


  Implements_VarId::Implements_VarId(ABC_Var *parent,
                                     const std::string &name, const std::string className)
    :
      id_(ABC_Var::isValidId(name)?name:""),
      class_(ABC_Var::isValidId(className)?className:""),
      p_(parent){}

  Implements_VarId::Implements_VarId():
    id_{},
    class_{},
    p_(nullptr){}

  void Implements_VarId::setParentVar(ABC_Var *par)
  {
    p_=par;
  }

  bool Implements_VarId::isInDomain(const ABC_Var *value) const
  {
    auto p= motherClass();
    if (p!=nullptr)
      return p->isInDomain(value);
    else
      return false;

  }

  ABC_Var *Implements_VarId::varTemplate() const
  {
    auto p= motherClass();
    if (p!=nullptr)
      return p->varTemplate();
    else
      return nullptr;
  }

  std::string Implements_VarId::myClass() const
  {
    return class_;
  }

  std::deque<Token_New> Implements_VarId::toTokens() const
  {
    return {{id()},{":"},{myClass()}};

  }

  bool Implements_VarId::processTokens(const std::deque<Token_New> &t,
                                       std::size_t &pos)
  {
    if ((!(pos+2<t.size()))
        ||(t.at(pos).tok()!=Token_New::IDENTIFIER)
        ||(t.at(pos+1).tok()!=Token_New::COLON)
        ||(t.at(pos+2).tok()!=Token_New::IDENTIFIER))
      return false;
    else
      {
        id_=t.at(pos).str();
        class_=t.at(pos+2).str();
        pos+=3;
        return true;
      }
  }




  std::string Implements_Refer_Var::refId() const
  {
    return refId_;
  }

  ABC_Var *Implements_Refer_Var::refVar()
  {
    return parentVar()->getVarId(refId(),myClass());
  }

  const ABC_Var *Implements_Refer_Var::refVar() const
  {
    return parentVar()->getVarId(refId(),myClass());
  }

  Implements_Refer_Var::Implements_Refer_Var(ABC_Var *parent,
                                             std::string idName,
                                             std::string refClass,
                                             std::string refName):
    Implements_VarId(parent,idName,refClass),
    refId_(refName){}

  std::deque<Token_New> Implements_Refer_Var::toTokens() const
  {
    auto out=Implements_VarId::toTokens();
    out<<"="<<"*"<<refId()<<"\n";
    return out;
  }

  bool Implements_Refer_Var::processTokens(const std::deque<Token_New> &t, std::size_t &pos)
  {
    if (!Implements_VarId::processTokens(t,pos))
      return false;
    else  if ((!pos+3<t.size())
              ||(t.at(pos).tok()!=Token_New::EQ)
              ||(t.at(pos+1).tok()!=Token_New::MUL)
              ||(t.at(pos+2).tok()!=Token_New::IDENTIFIER)
              ||(t.at(pos+3).tok()!=Token_New::EOL)
              )
      return false;
    else
      {
        refId_=t.at(pos+2).str();
        pos+=4;
        return true;
      }
  }

  bool Implements_Refer_Var::addVar(ABC_Var *var)
  {
    if (refVar()!=nullptr)
      return refVar()->addVar(var);
    else return {};
  }




  std::deque<Token_New> Implements_Complex_Var::toTokens() const
  {
    auto out=Implements_VarId::toTokens();
    out<<"begin"<<"\n";
    for (std::size_t i=0; i<numChildVars(); i++)
      {
        out<<getVarId(ith_Var(i))->toTokens();
      }
    out<<myClass()<<"end"<<"\n";
    return out;
  }

  bool Implements_Complex_Var::processTokens(
      const std::deque<Token_New> &t,
      std::size_t& pos)
  {
    if (!Implements_VarId::processTokens(t,pos))
      return false;
    else
      {
        if ( (!(pos+1<t.size()))
             ||(t.at(pos).tok()!=Token_New::BEGIN)
             ||(t.at(pos+1).tok()!=Token_New::EOL))
          return false;
        else
          {
            pos+=2;
            while ((pos+1<t.size())&&
                   (!((t.at(pos).str()==myClass())&&
                      (t.at(pos+1).tok()==Token_New::END))))
              {
                if (! addVar(getFromTokens(this,t,pos)))
                  return false;
              }
            if ((pos+1<t.size())&&(t.at(pos+1).tok()!=Token_New::END))
              return true;
            else
              return false;
          }
      }

  }

  std::string Implements_Complex_Var::ClassName()
  {
    return "Implements_Complex_Var";
  }

  std::size_t Implements_Complex_Var::numChildVars() const
  {
    return ids_.size();
  }

  std::string Implements_Complex_Var::ith_Var(std::size_t i) const
  {
    return ids_[i];
  }

  const ABC_Var *Implements_Complex_Var::getVarId(const std::string &name) const
  {
    auto it=vars_.find(name);
    if (it!=vars_.end())
      return it->second;
    else if (parentVar()!=nullptr)
      return parentVar()->getVarId(name);
    else return nullptr;
  }

  ABC_Var *Implements_Complex_Var::getVarId(const std::string &name)
  {
    auto it=vars_.find(name);
    if (it!=vars_.end())
      return it->second;
    else if (parentVar()!=nullptr)
      return parentVar()->getVarId(name);
    else return nullptr;
  }

  const ABC_Var *Implements_Complex_Var::getVarId(const std::string &name, const std::string &myclass) const
  {
    const ABC_Var* out=getVarId(name);
    if ((out!=nullptr)&&(out->myClass()==myclass))
      return out;
    else
      return nullptr;
  }

  ABC_Var *Implements_Complex_Var::getVarId(const std::string &name, const std::string &myclass)
  {
    ABC_Var* out=getVarId(name);
    if ((out!=nullptr)&&(out->myClass()==myclass))
      return out;
    else
      return nullptr;
  }

  bool Implements_Complex_Var::addVar(ABC_Var *var)
  {
    if (var==nullptr)
      return false;
    var->setParentVar(this);

    if (std::find (ids_.begin(),ids_.end(),var->id())==ids_.end())
      {
        ids_.push_back(var->id());
        vars_[var->id()]=var;
        return true;
      }
    else
      {
        delete  vars_[var->id()];
        vars_[var->id()]=var;
        return false;
      }
  }




  Implements_Complex_Var::Implements_Complex_Var( ABC_Var *parent,
                                                  const std::string &id,
                                                  const std::string className,
                                                  const std::vector<ABC_Var *> &childs):
    Implements_VarId(parent,id,className),
    ids_(),vars_{}
  {
    for (ABC_Var* v:childs)
      {
        v->setParentVar(this);
        ids_.push_back(v->id());
        vars_[v->id()]=v;
      }
  }

  Implements_Complex_Var::~Implements_Complex_Var()
  {
    for (auto id:vars_)
      delete id.second;
  }


  bool Token_New::isNameChar(char ch)
  {
    const std::string NameChar="abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "1234567890_"; return
        NameChar.find_first_of(ch)!=std::string::npos;

  }

  bool Token_New::isSpaceChar(char ch)
  {
    const std::string spaceChar=" \t"; return
        spaceChar.find_first_of(ch)!=std::string::npos;

  }

  bool Token_New::isRealNumberChar(char ch)
  { const std::string NumberChar="1234567890.eE+-";
    return NumberChar.find_first_of(ch)!=std::string::npos;


  }

  std::string Token_New::toString(double number)
  {
    std::stringstream ss;
    ss<<std::setprecision(std::numeric_limits<double>::digits10)<<number;
    return ss.str();
  }

  std::string Token_New::toString(int number)
  {
    std::stringstream ss;
    ss<<number;
    return ss.str();
  }

  std::string Token_New::toString(std::size_t number)
  {
    std::stringstream ss;
    ss<<number;
    return ss.str();
  }

  std::istream &Token_New::get(std::istream &stream)

  {
    str_.clear();
    int_=0;
    size_=0;
    number_=0;
    char ch;

    do {	// skip whitespace except '\en'
        if(!stream.get(ch))
          {
            curr_tok = END;
            return stream;
          }
      } while (isSpaceChar(ch));

    switch (ch) {
      case '\n':
        str_=ch;
        curr_tok=EOL;
        return stream;
        break;
      case '+':
      case '*':
      case '/':
      case '^':

      case ';':

      case '(':
      case ')':
      case '[':
      case ']':
      case '&':
      case '|':
        str_=ch;
        curr_tok=Value(ch);
        return stream;

      case ':':
        if(!stream.get(ch))
          {
            curr_tok = COLON;
            return stream;
          }
        else if (ch==':')
          {
            str_="::";
            curr_tok=DCOLON;
            return stream;
          }
        else
          {
            str_=":";
            stream.putback(ch);
            curr_tok=COLON;
            return stream;
          }

      case '=':
        if(!stream.get(ch))
          {
            curr_tok = ASSIGN;
            return stream;
          }
        else if (ch=='=')
          {
            str_="==";
            curr_tok=EQ;
            return stream;
          }
        else
          {
            str_="=";
            stream.putback(ch);
            curr_tok=ASSIGN;
            return stream;
          }
      case '~':
        if(!stream.get(ch))
          {
            curr_tok = NOT;
            return stream;
          }
        else if (ch=='=')
          {
            str_="~=";
            curr_tok=NEQ;
            return stream;
          }
        else
          {
            stream.putback(ch);
            str_="~";
            curr_tok=NOT;
            return stream;
          }
      case '<':
        if(!stream.get(ch))
          {
            curr_tok = LSS;
            return stream;
          }
        else if (ch=='=')
          {
            str_="<=";
            curr_tok=LEQ;
            return stream;
          }
        else
          {
            str_="<";
            stream.putback(ch);
            curr_tok=LSS;
            return stream;
          }
      case '>':
        if(!stream.get(ch))
          {
            curr_tok = GTR;
            return stream;
          }
        else if (ch=='=')
          {
            str_=">=";
            curr_tok=GEQ;
            return stream;
          }
        else
          {
            stream.putback(ch);
            str_=">";
            curr_tok=GTR;
            return stream;
          }

      case '.':
        if(!stream.get(ch))
          {
            curr_tok = DOT;
            return stream;
          }
        else if (ch=='.')
          {
            str_="..";
            curr_tok=PATH;

            return stream;
          }
        else
          {
            stream.putback(ch);
            str_=".";
            curr_tok=DOT;
            return stream;
          }
      case '-':
        str_=ch;
        if(!stream.get(ch))
          {
            curr_tok = MINUS;
            return stream;
          }
        else if (!isdigit(ch))
          {
            stream.putback(ch);
            curr_tok=MINUS;
            return stream;
          }

      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        if (str_=="-")
          {
            curr_tok=INTEGER;
            str_+= ch;
          }
        else
          {
            curr_tok=UNSIGNED;
            str_= ch;
          }
        while (stream.get(ch) && std::isdigit(ch))
          str_.push_back(ch);
        if (ch=='.')
          {
            str_.push_back(ch);
            while (stream.get(ch) && std::isdigit(ch))
              str_.push_back(ch);
            if ((ch=='e')||(ch=='E'))
              {
                str_.push_back(ch);
                if ((stream.get(ch)) && ((std::isdigit(ch)||(ch=='-')||(ch=='+'))))
                  str_.push_back(ch);
                while (stream.get(ch) && std::isdigit(ch))
                  str_.push_back(ch);
              }
            curr_tok=REAL;
            try {number_=std::stod(str_);} catch (...){curr_tok=INVALID; return stream;}
            if (!std::isdigit(ch))
              stream.putback(ch);
            return stream;

          }
        else if ((ch=='e')||(ch=='E'))
          {
            str_.push_back(ch);
            if ((stream.get(ch)) && ((std::isdigit(ch)||(ch=='-')||(ch=='+'))))
              str_.push_back(ch);
            while (stream.get(ch) && std::isdigit(ch))
              str_.push_back(ch);
            curr_tok=REAL;
            try{
              number_=std::stod(str_);
            }
            catch (...)
            {
              curr_tok=INVALID;
              return stream;
            }

            if (!std::isdigit(ch))
              stream.putback(ch);
            return stream;
          }
        if (curr_tok==INTEGER)
          try{
            int_=std::stoi(str_);} catch(...){ curr_tok=INVALID;}
        else if (curr_tok==UNSIGNED)
          try{
            size_=std::stoul(str_);}
        catch(...){ curr_tok=INVALID;}
        if (!std::isdigit(ch))
          stream.putback(ch);
        return stream;
      case '"':
        while (stream.get(ch)&& (ch!='"'))
          str_.push_back(ch);
        if (ch!='"')
          {
            //error("missing `""` ");
            curr_tok=STRING;
            stream.setstate(stream.rdstate() | std::ios_base::failbit);
            return stream;
          }
        else
          curr_tok=STRING;
        return stream;

      default:			// NAME, NAME=, or error
        if (isalpha(ch))
          {
            str_ = ch;
            while (stream.get(ch) && isNameChar(ch))
              str_.push_back(ch);
            if (!isNameChar(ch))
              stream.putback(ch);

            curr_tok=toKeyword(str_);
            stream.clear();
            return stream;
          }
        else
          {
            //error("bad token");
            curr_tok=INVALID;
            stream.setstate(stream.rdstate() | std::ios_base::failbit);
            return stream;
          }

      }
  }

  std::string Token_New::str() const
  {
    return str_;
  }

  double Token_New::num() const
  {
    return number_;
  }

  int Token_New::intval() const
  {
    return int_;
  }

  std::size_t Token_New::count() const
  {
    return size_;
  }

  Token_New::Value Token_New::tok() const
  {
    return curr_tok;
  }

  std::string Token_New::toString() const
  {
    if (tok()==REAL)
      return toString(number_);
    else  if (tok()==INTEGER)
      return toString(int_);
    else  if (tok()==UNSIGNED)
      return toString(size_);
    else return str_;
  }

  Token_New::Value Token_New::toKeyword(std::string identifier)
  {

    if(identifier=="do")
      {
        return DO;
      }
    else if(identifier=="then")
      {
        return THEN;
      }
    else if(identifier=="while")
      {
        return WHILE;
      }
    else if(identifier=="if")
      {
        return IF;
      }
    else if(identifier=="else")
      {
        return ELSE;
      }
    else if(identifier=="begin")
      {
        return BEGIN;
      }
    else if(identifier=="end")
      {
        return END;
      }
    else if(identifier=="switch")
      {
        return SWITCH;
      }
    else if(identifier=="case")
      {
        return CASE;
      }


    else return IDENTIFIER;

  }

  std::string Token_New::toString(Token_New::Value identifier)
  {

    if(identifier==DO)
      {
        return "do";
      }
    else if(identifier==THEN)
      {
        return "then";
      }
    else if(identifier==WHILE)
      {
        return "while";
      }
    else if(identifier==IF)
      {
        return "if";
      }
    else if(identifier==ELSE)
      {
        return "else";
      }
    else if(identifier==BEGIN)
      {
        return "begin";
      }
    else if(identifier==END)
      {
        return "end";
      }
    else if(identifier==SWITCH)
      {
        return "switch";
      }
    else if(identifier==CASE)
      {
        return "case";
      }

    else return {};

  }

  Token_New::Token_New(double d):
    curr_tok{REAL},
    number_(d),
    int_{},
    size_{},
    str_{}{}

  Token_New::Token_New(int n):
    curr_tok{INTEGER},
    number_{},
    int_{n},
    size_{},
    str_{}{}

  Token_New::Token_New(std::size_t s):
    curr_tok{UNSIGNED},
    number_{},
    int_{},
    size_{s},
    str_{}{}

  Token_New::Token_New(std::string d):
    curr_tok{},
    number_{},
    str_{}{
    std::stringstream ss(d);
    get(ss);
  }

  Token_New::Token_New(Token_New::Value v):
    curr_tok{v},
    number_{},
    str_{toString(v)}{}

  std::string ABC_Var::toString() const
  {
    std::string out;
    auto t=toTokens();
    for (Token_New i:t)
      {
        out+=i.toString()+" ";
      }
    return out;
  }

  ABC_Var *ABC_Var::getFromTokens(ABC_Var* parent,
                                  const std::deque<Token_New> &t,
                                  std::size_t &pos)
  {
    auto pos0=pos;
    Implements_VarId n;

    if (!n.processTokens(t,pos))
      return nullptr;
    else
      {
        ABC_Var* out;
        if (t.at(pos).tok()==Token_New::EQ)
          {
            ++pos;
            if (t.at(pos).tok()==Token_New::MUL)
              {
                // reference var
                ++pos;
                if (t.at(pos).tok()!=Token_New::IDENTIFIER)
                  return nullptr;
                else
                  return new Implements_Refer_Var(parent,n.id(),n.myClass(),t.at(pos).str());
              }
            else
              {
                //Implements_Simple_Var, lets find out of what
                switch (t.at(pos).tok())
                  {
                  case Token_New::REAL:
                    return new Implements_Simple_Var<double>(parent,n.id(),t.at(pos).num(),n.myClass());
                  case Token_New::INTEGER:
                    return new Implements_Simple_Var<int>(parent,n.id(),t.at(pos).intval(),n.myClass());

                  case Token_New::UNSIGNED:
                    return new Implements_Simple_Var<std::size_t>(parent,n.id(),
                                                                  t.at(pos).count(),n.myClass());

                  case Token_New::IDENTIFIER:
                    return new Implements_Simple_Var<std::string>(parent,n.id(),t.at(pos).str(),n.myClass());

                  case Token_New::EOL:
                    // that means it is a vector or map

                    return nullptr;
                  }

              }
          }
        else if  (t.at(pos).tok()==Token_New::BEGIN)
          {
            // ABC_Complex_Var
            out=new Implements_Complex_Var;
            out->setParentVar(parent);
            if (!out->processTokens(t,pos0))
              return nullptr;
            else return out;
          }

        else
          return nullptr;
      }
  }

  bool ABC_Var::isValidId(std::string name)
  {
    return Token_New(name).tok()==Token_New::IDENTIFIER;
  }

  std::string ABC_Var::ClassName()
  {
    return "ABC_Var";
  }

  std::set<std::string> ABC_Var::SuperClasses()
  {
    return {ClassName()};
  }

  std::set<std::string> ABC_Var::mySuperClasses()
  {
    return SuperClasses();
  }

  std::set<std::string> operator+(std::set<std::string>&& tok1,
                                  std::string &&s)
  {
    tok1.insert(s);
    return tok1;
  }

  std::set<std::string> operator+(std::set<std::string> &&ss1,
                                  std::set<std::string> &&ss2)
  {
    ss1.insert(ss2.begin(),ss2.end());
    return ss1;
  }

  std::deque<Token_New> &operator<<(std::deque<Token_New> &tok1, const std::deque<Token_New> &tok2)
  {
    tok1.insert(tok1.end(),tok2.begin(),tok2.end());
    return tok1;
  }

  std::deque<Token_New> &operator<<(std::deque<Token_New> &tok, const std::string &text)
  {
    std::stringstream ss(text);
    Token_New t;
    while (t.get(ss))
      {
        tok.push_back(t);
      }

    return tok;
  }

  std::deque<Token_New> &operator<<(std::deque<Token_New> &tok, double d)
  {
    tok.push_back(Token_New(d));
    return tok;
  }



  Implements_Complex_Class::Implements_Complex_Class(ABC_Var *parent,
                                                     const std::string &id,
                                                     const std::string className,
                                                     const std::map<std::string, std::pair<std::string,
                                                     std::string> >
                                                     id_superClass_ClassId):
    Implements_Complex_Var(parent,id,className,{})
  {
    for (auto e:id_superClass_ClassId)
      {
        addVar(new Implements_Refer_Var(parentVar(),
                                               e.first,
                                               e.second.first,
                                               e.second.second));
      }
  }




  bool Implements_Complex_Class::isInDomain(const ABC_Var *value) const
  {
    if (value==nullptr)
      return false;
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
        else if (!getVarId(iname)->isInDomain(valueVar))
          return false;
      }
    return true;

  }

  Implements_Complex_Var *Implements_Complex_Class::varTemplate() const
  {
    Implements_Complex_Var* out=  new Implements_Complex_Var(parentVar(),"",id(),{});
    for (std::size_t i=0; i<numChildVars(); i++)
      {
        auto v=getVarId(ith_Var(i))->varTemplate();
        v->setId(ith_Var(i));
        out->addVar(v);
      }
     return out;
  }

  template<typename T>
  std::set<std::string> Implements_Simple_Class<T>::SuperClasses()
  {
    return ABC_Var::SuperClasses()<<ClassName();
  }

  template<typename T>
  std::set<std::string> Implements_Simple_Class<T>::mySuperClasses()
  {
    return SuperClasses();
  }

  template<typename T>
  T Implements_Simple_Class<T>::defaultValue() const
  {
    return dynamic_cast<Implements_Simple_Var<T>*>(getVarId("default"))->value();
  }

  template<typename T>
  T Implements_Simple_Class<T>::minValue() const
  {
    return dynamic_cast<Implements_Simple_Var<T>*>(getVarId("min"))->value();
  }

  template<typename T>
  T Implements_Simple_Class<T>::maxValue() const
  {
    return dynamic_cast<Implements_Simple_Var<T>*>(getVarId("max"))->value();
  }

  template<typename T>
  T Implements_Simple_Class<T>::emptyValue() const
  {
    return T();
  }

  template<typename T>
  T Implements_Simple_Class<T>::unknownValue() const
  {
    std::numeric_limits<T>::quiet_NaN();
  }

  template<typename T>
  void Implements_Simple_Class<T>::setDefaultValue(T val)
  {
    dynamic_cast<Implements_Simple_Var<T>*>(getVarId("default"))->setValue(val);
  }

  template<typename T>
  void Implements_Simple_Class<T>::setminValue(T val)
  {
    dynamic_cast<Implements_Simple_Var<T>*>(getVarId("min"))->setValue(val);
  }

  template<typename T>
  void Implements_Simple_Class<T>::setmaxValue(T val)
  {
    dynamic_cast<Implements_Simple_Var<T>*>(getVarId("max"))->setValue(val);
  }




}
