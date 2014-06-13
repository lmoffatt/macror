#include <numeric>
#include <iostream>
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
  std::string Implements_Simple_Var<bool>::ClassName()
  {
    return "Simple_boolean_var";
  }

  template<>
  std::string Implements_Simple_Var<std::size_t>::ClassName()
  {
    return "Simple_count_var";
  }


  template<>
  std::string Implements_Simple_Var<std::vector<std::string>>::ClassName()
  {
    return "Simple_string_vector_var";
  }

  template<>
  std::string Implements_Simple_Var<std::vector<double>>::ClassName()
  {
    return "Simple_double_vector_var";
  }
  template<>
  std::string Implements_Simple_Var<std::vector<int>>::ClassName()
  {
    return "Simple_int_vector_var";
  }
  template<>
  std::string Implements_Simple_Var<std::vector<std::size_t>>::ClassName()
  {
    return "Simple_count_vector_var";
  }



  template<>
  std::string Implements_Simple_Var<Markov_LA::M_Matrix<double>>::ClassName()
  {
    return "Simple_double_Matrix_var";
  }
  template<>
  std::string Implements_Simple_Var<Markov_LA::M_Matrix<std::size_t>>::ClassName()
  {
    return "Simple_count_Matrix_var";
  }



  template<>
  std::string Implements_Simple_Var<std::map<std::string,std::string>>::ClassName()
  {
    return "Simple_string_string_map";
  }

  template<>
  std::string Implements_Simple_Var<std::map<double,std::string>>::ClassName()
  {
    return "Simple_double_string_map";
  }
  template<>
  std::string Implements_Simple_Var<std::map<int,std::string>>::ClassName()
  {
    return "Simple_int_string_map";
  }
  template<>
  std::string Implements_Simple_Var<std::map<std::size_t,std::string>>::ClassName()
  {
    return "Simple_count_string_map";
  }




  template<>
  std::string Implements_Simple_Var<std::map<std::string,std::size_t>>::ClassName()
  {
    return "Simple_string_count_map";
  }

  template<>
  std::string Implements_Simple_Var<std::map<double,std::size_t>>::ClassName()
  {
    return "Simple_double_count_map";
  }
  template<>
  std::string Implements_Simple_Var<std::map<int,std::size_t>>::ClassName()
  {
    return "Simple_int_count_map";
  }
  template<>
  std::string Implements_Simple_Var<std::map<std::size_t,std::size_t>>::ClassName()
  {
    return "Simple_count_count_map";
  }




  template<>
  std::string Implements_Simple_Var<std::map<std::string,double>>::ClassName()
  {
    return "Simple_string_double_map";
  }

  template<>
  std::string Implements_Simple_Var<std::map<double,double>>::ClassName()
  {
    return "Simple_double_double_map";
  }
  template<>
  std::string Implements_Simple_Var<std::map<int,double>>::ClassName()
  {
    return "Simple_int_double_map";
  }
  template<>
  std::string Implements_Simple_Var<std::map<std::size_t,double>>::ClassName()
  {
    return "Simple_count_double_map";
  }



  template<>
  std::string Implements_Simple_Var<std::map<std::string,int>>::ClassName()
  {
    return "Simple_string_int_map";
  }

  template<>
  std::string Implements_Simple_Var<std::map<double,int>>::ClassName()
  {
    return "Simple_double_int_map";
  }
  template<>
  std::string Implements_Simple_Var<std::map<int,int>>::ClassName()
  {
    return "Simple_int_int_map";
  }
  template<>
  std::string Implements_Simple_Var<std::map<std::size_t,int>>::ClassName()
  {
    return "Simple_count_int_map";
  }











  template<>
  std::string Implements_Simple_Var<std::map<std::string,std::vector<std::string>>>::ClassName()
  {
    return "Simple_string_string_map_of_vectors";
  }

  template<>
  std::string Implements_Simple_Var<std::map<double,std::vector<std::string>>>::ClassName()
  {
    return "Simple_double_string_map_of_vectors";
  }
  template<>
  std::string Implements_Simple_Var<std::map<int,std::vector<std::string>>>::ClassName()
  {
    return "Simple_int_string_map_of_vectors";
  }
  template<>
  std::string Implements_Simple_Var<std::map<std::size_t,std::vector<std::string>>>::ClassName()
  {
    return "Simple_count_string_map_of_vectors";
  }




  template<>
  std::string Implements_Simple_Var<std::map<std::string,std::vector<std::size_t>>>::ClassName()
  {
    return "Simple_string_count_map_of_vectors";
  }

  template<>
  std::string Implements_Simple_Var<std::map<double,std::vector<std::size_t>>>::ClassName()
  {
    return "Simple_double_count_map_of_vectors";
  }
  template<>
  std::string Implements_Simple_Var<std::map<int,std::vector<std::size_t>>>::ClassName()
  {
    return "Simple_int_count_map_of_vectors";
  }
  template<>
  std::string Implements_Simple_Var<std::map<std::size_t,std::vector<std::size_t>>>::ClassName()
  {
    return "Simple_count_count_map_of_vectors";
  }




  template<>
  std::string Implements_Simple_Var<std::map<std::string,std::vector<double>>>::ClassName()
  {
    return "Simple_string_double_map_of_vectors";
  }

  template<>
  std::string Implements_Simple_Var<std::map<double,std::vector<double>>>::ClassName()
  {
    return "Simple_double_double_map_of_vectors";
  }
  template<>
  std::string Implements_Simple_Var<std::map<int,std::vector<double>>>::ClassName()
  {
    return "Simple_int_double_map_of_vectors";
  }
  template<>
  std::string Implements_Simple_Var<std::map<std::size_t,std::vector<double>>>::ClassName()
  {
    return "Simple_count_double_map_of_vectors";
  }



  template<>
  std::string Implements_Simple_Var<std::map<std::string,std::vector<int>>>::ClassName()
  {
    return "Simple_string_int_map_of_vectors";
  }

  template<>
  std::string Implements_Simple_Var<std::map<double,std::vector<int>>>::ClassName()
  {
    return "Simple_double_int_map_of_vectors";
  }
  template<>
  std::string Implements_Simple_Var<std::map<int,std::vector<int>>>::ClassName()
  {
    return "Simple_int_int_map_of_vectors";
  }
  template<>
  std::string Implements_Simple_Var<std::map<std::size_t,std::vector<int>>>::ClassName()
  {
    return "Simple_count_int_map_of_vectors";
  }


















  template
  class Implements_Simple_Var<double>;

  template
  class Implements_Simple_Var<std::string>;

  template
  class Implements_Simple_Var<std::vector<std::string>>;

  template
  class Implements_Simple_Var<int>;


  template
  class Implements_Simple_Var<std::size_t>;


  template
  class Implements_Simple_Var<bool>;

  template
  class Implements_Simple_Var<Markov_LA::M_Matrix<double>>;

  template
  class Implements_Simple_Var<Markov_LA::M_Matrix<std::size_t>>;






































  std::string Implements_VarId::id() const
  {
    return id_;
  }

  void Implements_VarId::setId(const std::string &IdName)
  {
    id_=IdName;
  }

  std::string Implements_VarId::Tip() const
  {
    return tip_;
  }

  std::string Implements_VarId::WhatThis() const
  {
    return whatThis_;
  }

  void Implements_VarId::setTip(const std::string &tip)
  {
    tip_=tip;
  }

  void Implements_VarId::setWhatThis(const std::string &whatThis)
  {
    whatThis_=whatThis;
  }

  bool Implements_VarId::isRootedVariable() const
  {
    if (parentVar()==nullptr)
      return false;
    else   return parentVar()->getChildVar(id())==this;
  }

  std::size_t Implements_VarId::numChildVars() const
  {
    return 0;
  }

  std::string Implements_VarId::ith_VarName(std::size_t ) const
  {
    return{};
  }

  std::string Implements_VarId::childClass(const std::string &) const
  {
    return {};
  }

  const ABC_Var *Implements_VarId::getChildVar(const std::string &) const
  {
    return nullptr;
  }

  ABC_Var *Implements_VarId::getChildVar(const std::string &)
  {
    return nullptr;
  }

  const ABC_Var *Implements_VarId::getChildVar(const std::string &, const std::string &) const
  {
    return nullptr;
  }

  ABC_Var *Implements_VarId::getChildVar(const std::string &, const std::string &)
  {
    return nullptr;
  }

  bool Implements_VarId::addChildVar(ABC_Var *)
  {
    return false;
  }

  ABC_Var *Implements_VarId::parentVar()
  {
    if (isRootedVariable())
      return p_;
    else
      return nullptr;
  }
  const ABC_Var *Implements_VarId::parentVar() const
  {
    return p_;
  }
  std::string Implements_VarId::refId() const
  {
    return id();
  }


  ABC_Var *Implements_VarId::motherClass()
  {
    if (parentVar()!=nullptr)
      return parentVar()->getChildVar(myClass());
    else
      return nullptr;

  }

  const ABC_Var *Implements_VarId::motherClass() const
  {
    if (parentVar()!=nullptr)
      return parentVar()->getChildVar(myClass());
    else
      return nullptr;

  }


  Implements_VarId::Implements_VarId(ABC_Var *parent,
                                     const std::string &name,
                                     const std::string &className,
                                     const std::string &tip,
                                     const std::string &whatthis)
    :
      id_(ABC_Var::isValidId(name)?name:""),
      class_(ABC_Var::isValidId(className)?className:""),
      p_(parent),
      tip_(tip),
      whatThis_(whatthis){}

  Implements_VarId::Implements_VarId(const ABC_Var &other):
    id_(other.id()),
    class_(other.myClass()),
    p_(const_cast<ABC_Var*>(other.parentVar())),
    tip_(other.Tip()),
    whatThis_(other.WhatThis())
  {}


  bool Implements_VarId::loadFromComplexVar(const ABC_Var* )
  {
    return false;

  }

  ABC_Var *Implements_VarId::to_ComplexVar()const
  {
    return nullptr;
  }



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

  ABC_Var *Implements_VarId::varTemplate()const
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

  void Implements_VarId::setClass(const std::string &classname){
    class_=classname;
  }

  std::deque<Token_New> Implements_VarId::toTokens() const
  {
    std::deque<Token_New> out;
    if (!Tip().empty())
      out<<"# \""+Tip()+"\"";
    if (!WhatThis().empty())
      out<<"## \""+WhatThis()+"\"";
    if (!(Tip().empty()&&WhatThis().empty()))
      out<<"\n";
    out<<id()<<":"<<myClass();
    return out;


  }

  bool Implements_VarId::processTokens(const std::deque<Token_New> &t,
                                       std::size_t &pos)
  {
    while ((pos<t.size())&&(t.at(pos).tok()==Token_New::EOL))
      ++pos;
    if ((pos+1<t.size())&&
        (t.at(pos).tok()==Token_New::HASH)&&
        (t.at(pos+1).tok()==Token_New::STRING)) // tip is present
      {
        ++pos;
        setTip(t.at(pos).str());
        ++pos;
      }
    if ((pos+2<t.size())
        &&(t.at(pos).tok()==Token_New::HASH)
        &&(t.at(pos+1).tok()==Token_New::HASH)
        &&(t.at(pos+2).tok()==Token_New::STRING))
      {
        pos+=2;
        setWhatThis(t.at(pos).str());
        ++pos;
      }
    while ((pos<t.size())&&(t.at(pos).tok()==Token_New::EOL))
      ++pos;
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




  std::string Implements_Refer_Var::ClassName()
  {
    return "Refers_Variable";
  }

  std::string Implements_Refer_Var::refId() const
  {
    return refId_;
  }

  ABC_Var *Implements_Refer_Var::refVar()
  {
    if (parentVar()!=nullptr)
      return parentVar()->getChildVar(refId(),myClass());
    return
        nullptr;
  }

  const ABC_Var *Implements_Refer_Var::refVar() const
  {
    if (parentVar()!=nullptr)
      return parentVar()->getChildVar(refId(),myClass());
    return
        nullptr;
  }

  Implements_Refer_Var::Implements_Refer_Var(ABC_Var *parent,
                                             const std::string& idName,
                                             const std::string &refClass,
                                             const std::string& refName,
                                             const std::string &tip,
                                             const std::string &whatthis):
    Implements_VarId(parent,idName,refClass,tip,whatthis),
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
              ||(t.at(pos).tok()!=Token_New::ASSIGN)
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

  std::string Implements_Refer_Var::ith_VarName(std::size_t i) const
  {
    if (refVar()!=nullptr)
      return refVar()->ith_VarName(i);
    else return {};
  }

  const ABC_Var *Implements_Refer_Var::getChildVar(const std::string &name) const
  {
    if (refVar()!=nullptr)
      return refVar()->getChildVar(name);
    else return {};
  }

  ABC_Var *Implements_Refer_Var::getChildVar(const std::string &name)
  {
    if (refVar()!=nullptr)
      return refVar()->getChildVar(name);
    else return {};
  }

  const ABC_Var *Implements_Refer_Var::getChildVar(const std::string &name, const std::string &kind) const
  {
    if (refVar()!=nullptr)
      return refVar()->getChildVar(name,kind);
    else return {};
  }

  ABC_Var *Implements_Refer_Var::getChildVar(const std::string &name, const std::string &kind)
  {
    if (refVar()!=nullptr)
      return refVar()->getChildVar(name,kind);
    else return {};
  }

  bool Implements_Refer_Var::addChildVar(ABC_Var *var)
  {
    if (refVar()!=nullptr)
      return refVar()->addChildVar(var);
    else return {};
  }




  std::deque<Token_New> Implements_Complex_Var::toTokens() const
  {
    auto out=Implements_VarId::toTokens();
    out<<"begin"<<"\n";
    for (std::size_t i=0; i<numChildVars(); i++)
      {
        if (getChildVar(ith_VarName(i))!=nullptr)
          out<<getChildVar(ith_VarName(i))->toTokens();
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
                if (! addChildVar(getFromTokens(this,t,pos)))
                  return false;
              }
            if ((pos+1>=t.size())||(t.at(pos+1).tok()!=Token_New::END))

              return false;
            pos+=2;
            return true;
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

  std::string Implements_Complex_Var::ith_VarName(std::size_t i) const
  {
    return ids_[i];
  }

  std::string Implements_Complex_Var::childClass(const std::string &idName) const
  {
    auto it=childclss_.find(idName);
    if (it!=childclss_.end())
      return it->second;
    else
      return {};
  }

  const ABC_Var *Implements_Complex_Var::getChildVar(const std::string &name) const
  {
    auto it=vars_.find(name);
    if (it!=vars_.end())
      return it->second;
    else if (parentVar()!=nullptr)
      return parentVar()->getChildVar(name);
    else return nullptr;
  }

  ABC_Var *Implements_Complex_Var::getChildVar(const std::string &name)
  {
    auto it=vars_.find(name);
    if (it!=vars_.end())
      return it->second;
    else if (parentVar()!=nullptr)
      return parentVar()->getChildVar(name);
    else return nullptr;
  }

  const ABC_Var *Implements_Complex_Var::getChildVar(const std::string &name, const std::string &myclass) const
  {
    const ABC_Var* out=getChildVar(name);
    if ((out!=nullptr)&&(out->complyClass(myclass)))
      return out;
    else
      return nullptr;
  }

  ABC_Var *Implements_Complex_Var::getChildVar(const std::string &name, const std::string &myclass)
  {
    ABC_Var* out=getChildVar(name);
    if ((out!=nullptr)&&(out->complyClass(myclass)))
      return out;
    else
      return nullptr;
  }

  bool Implements_Complex_Var::addChildVar(ABC_Var *var)
  {
    if (var==nullptr)
      return false;

    auto it=vars_.find(var->id());
    if (it==vars_.end())
      {
        ids_.push_back(var->id());
        childclss_[var->id()]=var->myClass();
        vars_[var->id()]=var;
        var->setParentVar(this);
        return true;
      }
    else {
        auto n=var->id();
        ABC_Var* o=vars_[var->id()];
        if (o!=var)
          {delete o ;
            vars_[var->id()]=var;
          }
        var->setParentVar(this);
        return true;
      }
  }




  Implements_Complex_Var::Implements_Complex_Var(
      ABC_Var *parent,
      const std::string &id,
      const std::string className,
      const std::string&tip,
      const std::string &whatthis,
      const std::vector<std::pair<std::string,std::string>>& childsNameClass):
    Implements_VarId(parent,id,className,tip, whatthis),
    ids_(),childclss_{},vars_{}
  {
    for (auto& e:childsNameClass)
      {
        ids_.push_back(e.first);
        childclss_[e.first]=e.second;
      }
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

      case '#':
        str_=ch;
        curr_tok=HASH;
        return stream;
      case ':':
        if(!stream.get(ch))
          {
            str_=ch;
            curr_tok = COLON;
            stream.clear();
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
            str_="=";
            curr_tok = ASSIGN;
            stream.clear();
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
            stream.clear();
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
            stream.clear();
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
            stream.clear();
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
            stream.clear();
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
            stream.clear();
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
            std::stringstream ss(str_);
            ss>>number_;
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

  double Token_New::realValue() const
  {
    switch (curr_tok) {
      case UNSIGNED:
        return size_;
      case INTEGER:
        return int_;
      case REAL:
        return number_;
      default:
        return {};
      } }

  int Token_New::intval() const
  {
    switch (curr_tok) {
      case UNSIGNED:
        return size_;
      case INTEGER:
        return int_;
      case REAL:
        return number_;
      default:
        return {};
      }
  }


  std::size_t Token_New::count() const
  {
    switch (curr_tok) {
      case UNSIGNED:
        return size_;
      case INTEGER:
        return int_;
      case REAL:
        return number_;
      default:
        return {};
      }
  }

  Token_New::Value Token_New::tok() const
  {
    return curr_tok;
  }

  std::string Token_New::toString() const
  {
    if (tok()==REAL)
      return toString(number_)+" ";
    else  if (tok()==INTEGER)
      return toString(int_)+" ";
    else  if (tok()==UNSIGNED)
      return toString(size_)+" ";
    else if (tok()==IDENTIFIER)
      return str_+" ";
    else if (tok()==STRING)
      return "\""+str_+"\" ";
    else return toString(tok());
  }

  bool Token_New::isReal() const
  {
    return (tok()==REAL)||(tok()==INTEGER)||(tok()==UNSIGNED);
  }

  bool Token_New::isInteger() const
  {
    if ((tok()==INTEGER)||(tok()==UNSIGNED))
      return true;
    else if (tok()==REAL){
        if (number_-floor(number_)==0)
          return true;
        else return false;}
    else return false;
  }

  bool Token_New::isCount() const
  {
    if (tok()==UNSIGNED)
      return true;
    else if ((tok()==INTEGER)){
        if (int_>=0) return true;
        else return false;}
    else if (tok()==REAL){
        if ((number_>=0)&&(number_-floor(number_)==0))
          return true;
        else return false;}
    else return false;

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
    switch (identifier) {
      case IDENTIFIER:
      case STRING:
      case PATH:
      case INTEGER:
      case UNSIGNED:
      case REAL:
      case NUMBER:
      case INVALID:
        return{};
      case EOL: return "\n";
      case PLUS: return "+";
      case MINUS: return "-";
      case MUL:   return "*";
      case DIV:   return "/";
      case EXPONENT:   return "^";
      case DOT:   return ".";
      case COLON:   return ":";
      case COMMA:   return ",";
      case SEMICOLON:   return ";";
      case ASSIGN:   return  "=";
      case LP:   return "(" ;
      case RP:   return  ")";
      case LSB:   return  "[";
      case RSB:   return  "]";
      case NOT:   return  "~";
      case AND:   return  "&";
      case OR:   return  "|";
      case LSS:   return  "<";
      case GTR:   return  ">";
      case HASH:   return "#";
      case DCOLON:  return  "::";
      case LEQ:   return  "<=";
      case EQ:   return  "==";
      case NEQ:   return  "~=";
      case GEQ:   return  ">=";

      case WHILE:   return  "while";
      case DO:   return  "do";
      case IF:   return  "if";
      case THEN:   return  "then";
      case BEGIN:   return  "begin";
      case END:   return  "end";
      case ELSE:   return  "else";
      case SWITCH:   return "switch";
      case CASE:    return "case";

      default: return {};

      }



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
    for (const Token_New& i:t)
      {
        out+=i.toString();
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
    ABC_Var* out=nullptr;
    if (!(pos<t.size())) return nullptr;
    Token_New to=t.at(pos);
    if (to.tok()==Token_New::ASSIGN)
      {
        ++pos;
        if (!(pos<t.size())) return nullptr;
        to=t.at(pos);
        if (to.tok()==Token_New::MUL)
          {  // reference var

            ++pos;
            if (!(pos<t.size())) return nullptr;
            to=t.at(pos);
            if (to.tok()!=Token_New::IDENTIFIER)
              return nullptr;
            else
              return new Implements_Refer_Var(
                    parent,n.id(),n.myClass(),t.at(pos).str(),n.Tip(),n.WhatThis());
          }
        else
          {
            //Implements_Simple_Var, lets find out of what
            switch (to.tok())
              {
              case Token_New::REAL:
                out= new Implements_Simple_Var<double>(parent,n.id(),to.realValue(),n.myClass());
                break;
              case Token_New::INTEGER:
                out= new Implements_Simple_Var<int>(parent,n.id(),to.intval(),n.myClass());
                break;
              case Token_New::UNSIGNED:
                out= new Implements_Simple_Var<std::size_t>(parent,n.id(),to.count(),n.myClass());
                break;
              case Token_New::IDENTIFIER:
                out= new Implements_Simple_Var<std::string>(parent,n.id(),t.at(pos).str(),n.myClass());
                break;
              case Token_New::EOL:
                // that means it is a matrix, a vector or a map
                {
                  ++pos;
                  if (!(pos<t.size())) return nullptr;
                  to=t.at(pos);
                  if (to.tok()==Token_New::LSB)  // vector or map !!
                    {
                      if ((pos+3<t.size())&&(t.at(pos+2).tok()==Token_New::COLON)) //map
                        {  // it is a simple key map!!
                          // lets find out the types
                          to=t.at(pos+1);
                          Token_New to2=t.at(pos+3);
                          switch (to.tok())
                            {
                            case Token_New::REAL:
                              switch (to2.tok())
                                {
                                case Token_New::REAL:
                                  out=new Implements_Simple_Var<std::map<double,double>>;
                                  break;
                                case Token_New::INTEGER:
                                  out=new Implements_Simple_Var<std::map<double,int>>;
                                  break;
                                case Token_New::UNSIGNED:
                                  out=new Implements_Simple_Var<std::map<double,std::size_t>>;
                                  break;
                                case Token_New::IDENTIFIER:
                                  out=new Implements_Simple_Var<std::map<double,std::string>>;
                                  break;
                                case Token_New::EOL:
                                  if (!(pos+4<t.size()))
                                    return nullptr;
                                  to2=t.at(pos+4);
                                  switch (to2.tok())
                                    {
                                    case Token_New::REAL:
                                      out=new Implements_Simple_Var<std::map<double,std::vector<double>>>;
                                      break;
                                    case Token_New::INTEGER:
                                      out=new Implements_Simple_Var<std::map<double,std::vector<int>>>;
                                      break;
                                    case Token_New::UNSIGNED:
                                      out=new Implements_Simple_Var<std::map<double,
                                          std::vector<std::size_t>>>;
                                      break;
                                    case Token_New::IDENTIFIER:
                                      out=new Implements_Simple_Var<std::map<double,
                                          std::vector<std::string>>>;
                                      break;
                                    default:
                                      return nullptr;
                                    }
                                default:
                                  return nullptr;
                                }
                              break;

                            case Token_New::INTEGER:
                              switch (to2.tok())
                                {
                                case Token_New::REAL:
                                  out=new Implements_Simple_Var<std::map<int,double>>;
                                  break;
                                case Token_New::INTEGER:
                                  out=new Implements_Simple_Var<std::map<int,int>>;
                                  break;
                                case Token_New::UNSIGNED:
                                  out=new Implements_Simple_Var<std::map<int,std::size_t>>;
                                  break;
                                case Token_New::IDENTIFIER:
                                  out=new Implements_Simple_Var<std::map<int,std::string>>;
                                  break;
                                case Token_New::EOL:
                                  if (!(pos+4<t.size()))
                                    return nullptr;
                                  to2=t.at(pos+4);
                                  switch (to2.tok())
                                    {
                                    case Token_New::REAL:
                                      out=new Implements_Simple_Var<std::map<int,std::vector<double>>>;
                                      break;
                                    case Token_New::INTEGER:
                                      out=new Implements_Simple_Var<std::map<int,std::vector<int>>>;
                                      break;
                                    case Token_New::UNSIGNED:
                                      out=new Implements_Simple_Var<std::map<int,
                                          std::vector<std::size_t>>>;
                                      break;
                                    case Token_New::IDENTIFIER:
                                      out=new Implements_Simple_Var<std::map<int,
                                          std::vector<std::string>>>;
                                      break;
                                    default:
                                      return nullptr;
                                    }
                                default:
                                  return nullptr;
                                }
                              break;
                            case Token_New::UNSIGNED:
                              switch (to2.tok())
                                {
                                case Token_New::REAL:
                                  out=new Implements_Simple_Var<std::map<std::size_t,double>>;
                                  break;
                                case Token_New::INTEGER:
                                  out=new Implements_Simple_Var<std::map<std::size_t,int>>;
                                  break;
                                case Token_New::UNSIGNED:
                                  out=new Implements_Simple_Var<std::map<std::size_t,std::size_t>>;
                                  break;
                                case Token_New::IDENTIFIER:
                                  out=new Implements_Simple_Var<std::map<std::size_t,std::string>>;
                                  break;
                                case Token_New::EOL:
                                  switch (to2.tok())
                                    {
                                    case Token_New::REAL:
                                      out=new Implements_Simple_Var<std::map<std::size_t
                                          ,std::vector<double>>>;
                                      break;
                                    case Token_New::INTEGER:
                                      out=new Implements_Simple_Var<std::map<std::size_t,
                                          std::vector<int>>>;
                                      break;
                                    case Token_New::UNSIGNED:
                                      out=new Implements_Simple_Var<std::map<std::size_t,
                                          std::vector<std::size_t>>>;
                                      break;
                                    case Token_New::IDENTIFIER:
                                      out=new Implements_Simple_Var<std::map<std::size_t,
                                          std::vector<std::string>>>;
                                      break;
                                    default:
                                      return nullptr;
                                    }
                                default:
                                  return nullptr;
                                }
                              break;
                            case Token_New::IDENTIFIER:
                              switch (to2.tok())
                                {
                                case Token_New::REAL:
                                  out=new Implements_Simple_Var<std::map<std::string,double>>;
                                  break;
                                case Token_New::INTEGER:
                                  out=new Implements_Simple_Var<std::map<std::string,int>>;
                                  break;
                                case Token_New::UNSIGNED:
                                  out=new Implements_Simple_Var<std::map<std::string,std::size_t>>;
                                  break;
                                case Token_New::IDENTIFIER:
                                  out=new Implements_Simple_Var<std::map<std::string,std::string>>;
                                  break;
                                case Token_New::EOL:
                                  switch (to2.tok())
                                    {
                                    case Token_New::REAL:
                                      out=new Implements_Simple_Var<std::map<std::string
                                          ,std::vector<double>>>;
                                      break;
                                    case Token_New::INTEGER:
                                      out=new Implements_Simple_Var<std::map<std::string,
                                          std::vector<int>>>;
                                      break;
                                    case Token_New::UNSIGNED:
                                      out=new Implements_Simple_Var<std::map<std::string,
                                          std::vector<std::size_t>>>;
                                      break;
                                    case Token_New::IDENTIFIER:
                                      out=new Implements_Simple_Var<std::map<std::string,
                                          std::vector<std::string>>>;
                                      break;
                                    default:
                                      return nullptr;
                                    }
                                default:
                                  return nullptr;
                                }
                              break;
                            default:
                              return nullptr;
                            }
                        }
                      else   //vector
                        {
                          if (!(pos<t.size())) return nullptr;

                          to=t.at(pos+1);

                          switch (to.tok())
                            {
                            case Token_New::REAL:
                              out=new Implements_Simple_Var<std::vector<double>>;
                              break;
                            case Token_New::INTEGER:
                              out=new Implements_Simple_Var<std::vector<int>>;
                              break;
                            case Token_New::UNSIGNED:
                              out=new Implements_Simple_Var<std::vector<std::size_t>>;
                              break;
                            case Token_New::IDENTIFIER:
                              out=new Implements_Simple_Var<std::vector<std::string>>;
                              break;
                            default:
                              return nullptr;
                            }
                        }

                    }
                  else switch (to.tok()) // matrix
                    {
                    case Token_New::REAL:
                    case Token_New::INTEGER:
                    case Token_New::UNSIGNED:
                      out=new Implements_Simple_Var<Markov_LA::M_Matrix<double>>;
                      break;
                      //out=new Implements_Simple_Var<Markov_LA::M_Matrix<std::size_t>>;
                      //break;
                    default:
                      return nullptr;
                    }
                }
              default:
                break;
              }
          }
      }
    else if  (t.at(pos).tok()==Token_New::BEGIN)
      {
        // ABC_Complex_Var
        out=new Implements_Complex_Var;
      }
    else
      return nullptr;
    out->setParentVar(parent);
    pos=pos0;
    if (!out->processTokens(t,pos))
      return nullptr;
    else
      return out;

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

  std::set<std::string> ABC_Var::mySuperClasses()const
  {
    return SuperClasses();
  }

  bool ABC_Var::complyClass(const std::string classname) const
  {
    auto s= mySuperClasses()+myClass();
    return s.find(classname)!=s.end();

  }




  Implements_Complex_Class::Implements_Complex_Class(ABC_Var *parent,
                                                     const std::string &id,
                                                     const std::string& className,
                                                     const std::string &tip,
                                                     const std::string &whatthis,
                                                     const std::map<std::string,fieldDef> m):
    Implements_Complex_Var(parent,id,className,tip,whatthis)
  {
    for (const auto& e:m)
      {
        addChildVar(new Implements_Refer_Var(parentVar(),
                                             e.first,
                                             e.second.superClass,
                                             e.second.className,
                                             e.second.tip,
                                             e.second.whatthis));
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
        auto iname=ith_VarName(i);
        auto valueVar=value->getChildVar(iname);
        if (valueVar==nullptr)
          return false;
        else if (!getChildVar(iname)->isInDomain(valueVar))
          return false;
      }
    return true;

  }

  Implements_Complex_Var *Implements_Complex_Class::varTemplate() const
  {
    Implements_Complex_Var* out=  new Implements_Complex_Var(nullptr,"",id(),"","");
    for (std::size_t i=0; i<numChildVars(); i++)
      {
        auto v=getChildVar(ith_VarName(i))->varTemplate();
        v->setId(ith_VarName(i));
        out->addChildVar(v);
      }

    return out;
  }


  void Implements_Complex_Class::push_back(const std::string &idName, const std::string &superclassname, const std::string &classname, const std::string& tip, const std::string& whatthis)
  {
    addChildVar(new Implements_Refer_Var(parentVar(),idName,superclassname, classname,tip, whatthis));
  }



  bool toValue(const std::deque<Token_New> &tok, double &val, std::size_t &i)
  {
    if (!(i<tok.size())) return false;
    Token_New t=tok.at(i);
    if (!t.isReal())
      return false;
    else
      {
        val=t.realValue();
        ++i;
        return true;
      }
  }

  bool toValue(const std::deque<Token_New> &tok, int &val, std::size_t &i)
  {
    if (!(i<tok.size())) return false;
    Token_New t=tok.at(i);
    if (!t.isInteger())
      return false;
    else
      {
        val=t.intval();
        ++i;
        return true;
      }
  }

  bool toValue(const std::deque<Token_New> &tok, std::size_t &val, std::size_t &i)
  {
    if (!(i<tok.size())) return false;
    Token_New t=tok.at(i);
    if (t.isCount())
      {
        val=t.count();
        ++i;
        return true;
      }
    else
      return false;
  }

  bool toValue(const std::deque<Token_New> &tok, std::string &val, std::size_t &i)
  {
    if (!(i<tok.size())) return false;
    if (tok.at(i).tok()!=Token_New::IDENTIFIER)
      return false;
    else
      {
        val=tok.at(i).str();
        ++i;
        return true;
      }
  }


  bool toValue(const std::deque<Token_New> &tok, bool &val, std::size_t &i)
  {
    if (!(i<tok.size())) return false;
    if (tok.at(i).tok()==Token_New::IDENTIFIER)
      {
        std::string s=tok.at(i).str();
        if ((s=="false")||(s=="FALSE"))
          {
            val=false;
            ++i;
            return true;
          }
        else if ((s=="true")||(s=="TRUE"))
          {
            val=true;
            ++i;
            return true;
          }
        else return false;
      }
    else if (tok.at(i).isCount())
      {
        if (tok.at(i).count()==0)
          {
            val=false;
            ++i;
            return true;
          }
        else if(tok.at(i).count()==1)
          {
            val=true;
            ++i;
            return true;
          }
        else
          return false;
      }
    else
      return false;
  }



  /*
  std::string Implements_Categorical_Class::ClassName()
  {
    return "Category_Class";
  }

  std::set<std::string> Implements_Categorical_Class::SuperClasses()
  {
    return Implements_Simple_Var<std::map<std::string,int>>::SuperClasses()+ClassName();
  }

  std::set<std::string> Implements_Categorical_Class::mySuperClasses()
  {
    return SuperClasses();
  }

  std::string Implements_Categorical_Class::Category(int i) const
  {
    auto it=revMap_.find(i);
    if (it!=revMap_.end())
      return it->second;
    else
      return {};
  }

  int Implements_Categorical_Class::Rank(const std::string name) const
  {
    auto it=refval().find(name);
    if (it!=refval().end())
      return it->second;
    else
      return {};
  }

  std::string Implements_Categorical_Class::defaultCategory() const
  {
    return default_;
  }

  Implements_Categorical_Class::Implements_Categorical_Class(ABC_Var *parent,
                                                             const std::string &categoryName,
                                                             std::vector<std::string> categoriesList,
                                                             const std::string& defaultCategoryName):
    Implements_Simple_Var<std::map<std::string,int>>(parent,categoryName,{},ClassName()),
    default_(defaultCategoryName)
  {
    for (std::size_t i=0; i<categoriesList.size(); ++i)
      {
        this->refval()[categoriesList[i]]=i;
        revMap_[i]=categoriesList[i];
      }
  }

  Implements_Categorical_Class::Implements_Categorical_Class(ABC_Var *parent,
                                                             const std::string &categoryName,
                                                             std::map<std::string, int> categoriesRank,
                                                             const std::string& defaultCategoryName):
    Implements_Simple_Var<std::map<std::string,int>>(parent,categoryName,categoriesRank,ClassName()),
    default_(defaultCategoryName)
  {
    for (std::pair<std::string,int> e:value())
      {
        revMap_[e.second]=e.first;
      }
  }

  Implements_Categorical_Class::Implements_Categorical_Class(ABC_Var *parent,
                                                             const std::string &categoryName,
                                                             std::map<int,std::string> RankCategories,
                                                             const std::string& defaultCategoryName):
    Implements_Simple_Var<std::map<std::string,int>>(parent,categoryName,{},ClassName()),
    default_(defaultCategoryName),
    revMap_{RankCategories}
  {
    for (std::pair<int,std::string> e:revMap_)
      {
        refval()[e.second]=e.first;
      }
  }

  bool Implements_Categorical_Class::isInDomain(const ABC_Var *value) const
  {
    if (value->myClass()!=id())
      return false;
    const Implements_Categorical* p=dynamic_cast<const Implements_Categorical*>(value);
    if (p!=nullptr)
      return refval().find(p->Category())!=refval().end();
    else
      return nullptr;
  }

  ABC_Var *Implements_Categorical_Class::varTemplate() const
  {
    return new Implements_Categorical(nullptr,"",defaultCategory(),id());
  }

*/





}
