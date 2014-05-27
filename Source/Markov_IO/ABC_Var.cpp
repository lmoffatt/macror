#include <numeric>
#include "Markov_IO/ABC_Var.h"



namespace Markov_IO {

  template<>
  std::string Implements_Simple_Var<double>::ClassName()
  {
    return "Simple_real_var";
  }




  template<typename T>
  std::deque<Token_New> Implements_Simple_Var<T>::toTokens() const
  {
    auto out=Implements_VarId::toTokens();
    out<<value()<<"\n";
    return out;
  }

  template<typename T>
  std::size_t Implements_Simple_Var<T>::
  processTokens(const std::deque<Token_New>& t,
                std::size_t pos)
  {
    auto p=Implements_VarId::processTokens(t,pos);
    if (p<pos+3)
      return pos;
    else
      {

        T val;
        p=toValue(t,val,p);
        if (p==pos+3)
          return p;
        else
          {
            value_=val;
            return p;
          }
      }
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


  template<>
  std::size_t Implements_Simple_Var<double>::toValue(const std::deque<Token_New> &tok,
                                                     double &val,
                                                     std::size_t i)
  {
    if (tok.at(i).tok()!=Token_New::NUMBER)
      return i;
    else
      {
        val=tok.at(i).num();
        return i+1;
      }
  }

  template<>
  std::size_t Implements_Simple_Var<std::vector<std::string>>::
  toValue(const std::deque<Token_New> &tok,
          std::vector<std::string> &val,
          std::size_t i)
  {
    if (tok.at(i).tok()!=Token_New::IDENTIFIER)
      return i;
    else
      {
        while ((i<tok.size())&&(tok.at(i).tok()!=Token_New::IDENTIFIER))
          {
            val.push_back(tok.at(i).str());
            ++i;
          }
        return i;
      }
  }

  template<>
  std::deque<Token_New> Implements_Simple_Var<double>::toToken(const double& val)
  {
    return {{val}};
  }



  template<typename T>
  Implements_Simple_Var<T>::
  Implements_Simple_Var(ABC_Complex_Var *parent,
                        std::string id,
                        T val,
                        std::string className):
    Implements_VarId(parent,id,className),
    value_(val){}



  template
  class Implements_Simple_Var<double>;




  std::string Implements_VarId::id() const
  {
    return id_;
  }

  std::size_t Implements_VarId::numChildVars() const
  {
    return 0;
  }

  ABC_Complex_Var *Implements_VarId::parentVar() const
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


  Implements_VarId::Implements_VarId(ABC_Complex_Var *parent,
                                     const std::string &name, const std::string className)
    :
      id_(ABC_Var::isValidId(name)?name:""),
      class_(ABC_Var::isValidId(className)?className:""),
      p_(parent){}

  Implements_VarId::Implements_VarId():
    id_{},
    class_{},
    p_(nullptr){}

  void Implements_VarId::setParent(ABC_Complex_Var *par)
  {
    p_=par;
  }

  std::deque<Token_New> Implements_VarId::toTokens() const
  {
    return {{id()},{":"},{myClass()}};

  }

  std::size_t Implements_VarId::processTokens(const std::deque<Token_New> &t,
                                              std::size_t pos)
  {
    if ((!pos+2<t.size())
        ||(t.at(pos).tok()!=Token_New::IDENTIFIER)
        ||(t.at(pos+1).tok()!=Token_New::COLON)
        ||(t.at(pos+2).tok()!=Token_New::IDENTIFIER))
      return pos;
    else
      {
        id_=t.at(pos).str();
        class_=t.at(pos+2).str();
        return pos+3;
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

  Implements_Refer_Var::Implements_Refer_Var(ABC_Complex_Var *parent,
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

  std::size_t Implements_Refer_Var::processTokens(const std::deque<Token_New> &t, std::size_t pos)
  {
    auto p=Implements_VarId::processTokens(t,pos);
    if (p<pos+3)
      return pos;
    else  if ((!pos+6<t.size())
              ||(t.at(pos+3).tok()!=Token_New::EQ)
              ||(t.at(pos+4).tok()!=Token_New::MUL)
              ||(t.at(pos+5).tok()!=Token_New::IDENTIFIER)
              ||(t.at(pos+6).tok()!=Token_New::EOL)
              )
      return pos;
    else
      {
        id_=t.at(pos).str();
        class_=t.at(pos+2).str();
        refId_=t.at(pos+5).str();
        return pos+7;
      }
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

  std::size_t Implements_Complex_Var::processTokens(
      const std::deque<Token_New> &t,
      std::size_t pos)
  {
    auto p=Implements_VarId::processTokens(t,pos);
    if (p<pos+3)
      return pos;
    else
      {
        if ( (!pos+4<t.size())
             ||(t.at(pos+3).tok()!=Token_New::BEGIN)
             ||(t.at(pos+4).tok()!=Token_New::EOL))
          return pos;
        else
          {
            std::size_t p=pos+5;
            while ((p+1<t.size())&&
                   (!(t.at(p).str()==myClass())&&
                    (t.at(p+1).tok()==Token_New::END)))
              {
                if (! addVar(getFromTokens(this,t,p)))
                  return pos;
              }
            if (t.at(p+1).tok()!=Token_New::END)
              return pos;
            else
              return p+2;
          }
      }

  }

  std::size_t Implements_Complex_Var::numChildVars() const
  {
    return ids_.size();
  }

  bool Implements_Complex_Var::addVar(ABC_Var *var)
  {
    if (var==nullptr)
      return false;
    var->setParent(this);

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


  const ABC_Environment_Var *Implements_Complex_Var::getEnvironment() const
  {
    return parentVar()->getEnvironment();
  }

  ABC_Environment_Var *Implements_Complex_Var::getEnvironment()
  {
    return parentVar()->getEnvironment();
  }


  Implements_Complex_Var::Implements_Complex_Var(ABC_Complex_Var *parent,
                                                 const std::string &id,
                                                 const std::string className,
                                                 const std::vector<ABC_Var *> &childs):
    Implements_VarId(parent,id,className),
    ids_(),vars_{}
  {
    for (ABC_Var* v:childs)
      {
        v->setParent(this);
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

  std::istream &Token_New::get(std::istream &stream)

  {
    str_.clear();
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
      case '-':
      case '*':
      case '/':
      case '^':

      case ':':
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

      case '=':
        stream.get(ch);
        if (ch=='=')
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
        stream.get(ch);
        if (ch=='=')
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
        stream.get(ch);
        if (ch=='=')
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
        stream.get(ch);
        if (ch=='=')
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
        stream.get(ch);
        if (ch=='.')
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

      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        stream.putback(ch);
        stream >> number_;
        curr_tok=NUMBER;
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

  ABC_Var *ABC_Var::getFromTokens(ABC_Complex_Var* parent,
                         const std::deque<Token_New> &t,
                         std::size_t &pos)
  {
    Implements_VarId n;
    auto p=n.processTokens(t,pos);
    if (p==pos+3)
      {
        ABC_Var* out=parent->getEnvironment()->getClassId(n.myClass())->clone();
        auto pos0=pos;
        pos=out->processTokens(t,pos0);
        if (pos>pos0)
          return out;
        else
          return nullptr;
      }
    else
      return nullptr;

  }
}
