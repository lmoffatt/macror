#include <numeric>
#include "Markov_IO/ABC_Var.h"



namespace Markov_IO {

  std::string ABC_Var::alfaChars()
  {
    return "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  }

  std::string ABC_Var::alfaNumChars()
  {
    return alfaChars()+"_0123456789";
  }

  std::string ABC_Var::spaceChars()
  {
    return "\t ";
  }

  std::string ABC_Var::numChars()
  {
    return "0123456789";
  }

  std::string ABC_Var::numRChars()
  {
    return "0123456789.eE+-";
  }

  bool ABC_Var::isValidId(const std::string &idC)
  {
    if (alfaChars().find_first_not_of(idC[0])!=alfaChars().npos)
      return false;
    if (idC.find_first_not_of(alfaNumChars())!=idC.npos)
      return false;
    else
      return true;

  }

  std::string ABC_Var::getId(const std::string &text, std::size_t &pos)
  {
    std::size_t pos0=text.find_first_not_of(spaceChars(),pos);
    if (alfaChars().find(text[pos0])==alfaChars().npos)
      {
        std::string error="invalid starting char for identifier: "+text[pos];
        throw std::logic_error(error);
      }
    pos=text.find_first_not_of(alfaNumChars(),pos0);
    return text.substr(pos0,pos-pos0);
  }




  template<>
  std::string Implements_Simple_Var<double>::ClassName()
  {
    return "Simple_real_var";
  }


  template<typename T>
  std::string Implements_Simple_Var<T>::toString() const
  {
    std::stringstream ss;
    ss<<Implements_VarId::id()<<" : "<<this->myKindId()<<" = ";
    ss<<std::setprecision(std::numeric_limits<double>::digits10)<<value()<"\n";
    return ss.str();
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

  /*
template<typename T>
ABC_Var *Implements_Simple_Var<T>::create() const
{
  return new Implements_Simple_Var<T>;
}
*/
  template<typename T>
  Implements_Simple_Var<T>::
  Implements_Simple_Var(ABC_Complex_Var *parent,
                        std::string id,
                        T val,
                        std::string kindName):
    Implements_VarId(parent,kindName,id),
    value_(val){}

  template<typename T>
  Implements_Simple_Var<T>::Implements_Simple_Var():
    Implements_VarId(),
    value_{}{}


  template
  class Implements_Simple_Var<double>;


  std::string ABC_Complex_Var::BeginLabel() const
  {
    return "Begin "+myKindId();
  }

  std::string ABC_Complex_Var::EndLabel() const
  {
    return "End "+myKindId();
  }

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
                                     const std::string &kindName,
                                     const std::string &name)
    :
      kind_(isValidId(kindName)?kindName:""),
      id_(ABC_Var::isValidId(name)?name:""),
      p_(parent)
  {
  }

  Implements_VarId::Implements_VarId():
    kind_{},
    id_{},
    p_(nullptr){}

  void Implements_VarId::setParent(ABC_Complex_Var *par)
  {
    p_=par;
  }

  std::string Implements_Refer_Var::RefLabel() const
  {
    return std::string("Refers ")+ myKindId();
  }


  std::string Implements_Refer_Var::toString() const
  {
    std::stringstream ss;
    ss<<id()<<" : ";
    ss<<RefLabel();
    if (!refId().empty())
      ss<<"="<<refId();
    ss<<"\n";
    return ss.str();

  }

  std::string Implements_Refer_Var::refId() const
  {
    return refId_;
  }

  ABC_Var *Implements_Refer_Var::refVar()
  {
    return parentVar()->getVarId(refId(),myKindId());
  }

  const ABC_Var *Implements_Refer_Var::refVar() const
  {
    return parentVar()->getVarId(refId(),myKindId());
  }

  Implements_Refer_Var::Implements_Refer_Var(ABC_Complex_Var *parent, std::string idName, std::string refKind, std::string refName):
    Implements_VarId(parent,refKind,idName),
    refId_(refName){}

  std::string Implements_Complex_Var::toString() const
  {
    std::stringstream ss;
    ss<<id()<<" : ";
    ss<<BeginLabel()<<"\n";
    for (std::size_t i=0; i<numChildVars(); i++)
      {
        ss<<getVarId(ith_Var(i))->toString();
      }
    ss<<EndLabel()<<"\n";
    return ss.str();
  }

  std::size_t Implements_Complex_Var::numChildVars() const
  {
    return ids_.size();
  }

  bool Implements_Complex_Var::addVar(ABC_Var *var)
  {
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


  ABC_Environment_Var *Implements_Complex_Var::getEnvironment() const
  {
    return Implements_VarId::parentVar()->getEnvironment();
  }

  Implements_Complex_Var::Implements_Complex_Var(ABC_Complex_Var *parent,
                                                 const std::string& kindId,
                                                 const std::string &id,
                                                 const std::vector<ABC_Var *> &childs):
    Implements_VarId(parent,kindId,id),
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
    identifier_.clear();
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
        curr_tok=Value(ch);
        return stream;

      case '=':
        stream.get(ch);
        if (ch=='=')
          {
            curr_tok=EQ;
            return stream;
          }
        else
          {
            stream.putback(ch);
            curr_tok=ASSIGN;
            return stream;
          }
      case '~':
        stream.get(ch);
        if (ch=='=')
          {
            curr_tok=NEQ;
            return stream;
          }
        else
          {
            stream.putback(ch);
            curr_tok=NOT;
            return stream;
          }
      case '<':
        stream.get(ch);
        if (ch=='=')
          {
            curr_tok=LEQ;
            return stream;
          }
        else
          {
            stream.putback(ch);
            curr_tok=LSS;
            return stream;
          }
      case '>':
        stream.get(ch);
        if (ch=='=')
          {
            curr_tok=GEQ;
            return stream;
          }
        else
          {
            stream.putback(ch);
            curr_tok=GTR;
            return stream;
          }

      case '.':
        stream.get(ch);
        if (ch=='.')
          {
            identifier_="..";
            curr_tok=PATH;

            return stream;
          }
        else
          {
            stream.putback(ch);
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
          identifier_.push_back(ch);
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
            identifier_ = ch;
            while (stream.get(ch) && isNameChar(ch))
              identifier_.push_back(ch);
            if (!isNameChar(ch))
              stream.putback(ch);

            curr_tok=toKeyword(identifier_);
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


  /*
ABC_Var *ABC_Var::getFromString(const std::string& text, std::size_t &pos)

{
  std::size_t pos0=pos;
  std::string idN=getId(text,pos);
  ABC_Var* out=nullptr;

  if (idN.empty())
  return nullptr;

  pos=text.find_first_not_of(spaceChars(),pos);

  if (!(text.size()>pos ))
    return false;

  // colon or equal?

  std::size_t pos1=pos;
  if (text[pos]!='=')
    {
     // we know it is a simple var
     pos=text.find_first_not_of(spaceChars(),pos);
     char f=text[pos];
     if (alfaChars().find(f)!=alfaChars().npos)
       { // it is not a number

       }
     else if ((f=='-')||(f=='+')||(numChars().find(f)!=numChars().npos))
       {// it is a number
         pos=text.find_first_of(spaceChars(),pos1);
         std::string numC=text.substr(pos1,pos-pos1);
         if (numC.find_first_not_of(numRChars())!=numC.npos)
           {
             std::string error="invalid number: "+numC;
             throw std::logic_error(error);
           }
         // it is a scalar or a vector or matrix?
         // check the next thing
         std::size_t posn=text.find_first_not_of(spaceChars(),pos);
         char fn=text[posn];
         if (alfaChars().find(fn)!=alfaChars().npos)
                { // it is not a number

                }


         if (numC.find('.')!=numC.npos)
           {
             // not an integer



           }



         if (f=='-')  // signed


       }



    }
    return false;
  pos++;

  // check the class begin

 std::string beginN=getId(text,pos);
 std::string classN=getId(text,pos);








  pos=text.find_first_not_of(spaceChars(),pos);
  pos1=pos;
  pos=text.find_first_not_of(numRChars(),pos);
  std::string num=text.substr(pos1,pos-pos1);
  double d;
  try
  {
    d=std::stod(num);
  }
  catch (std::invalid_argument)
  {
    pos=pos0;
    return false;
  }
  // if we got here, we have id and value rights
  id_=idN;
  real_=d;
  return true;
}

*/




}
