#include <numeric>
#include <iostream>
#include "Markov_IO/ABC_Var.h"
#include "Markov_Console/ExpressionManager.h"



namespace Markov_IO {

  template<>
  std::string Implements_Simple_Value<std::string>::ClassName()
  {
    return "Simple_name_var";
  }

  template<>
  std::string Implements_Simple_Value<double>::ClassName()
  {
    return "Simple_real_var";
  }

  template<>
  std::string Implements_Simple_Value<int>::ClassName()
  {
    return "Simple_integer_var";
  }

  template<>
  std::string Implements_Simple_Value<bool>::ClassName()
  {
    return "Simple_boolean_var";
  }

  template<>
  std::string Implements_Simple_Value<std::size_t>::ClassName()
  {
    return "Simple_count_var";
  }


  template<>
  std::string Implements_Simple_Value<std::vector<std::string>>::ClassName()
  {
    return "Simple_string_vector_var";
  }

  template<>
  std::string Implements_Simple_Value<std::vector<double>>::ClassName()
  {
    return "Simple_double_vector_var";
  }
  template<>
  std::string Implements_Simple_Value<std::vector<int>>::ClassName()
  {
    return "Simple_int_vector_var";
  }
  template<>
  std::string Implements_Simple_Value<std::vector<std::size_t>>::ClassName()
  {
    return "Simple_count_vector_var";
  }



  template<>
  std::string Implements_Simple_Value<Markov_LA::M_Matrix<double>>::ClassName()
  {
    return "Simple_double_Matrix_var";
  }
  template<>
  std::string Implements_Simple_Value<Markov_LA::M_Matrix<std::size_t>>::ClassName()
  {
    return "Simple_count_Matrix_var";
  }



  template<>
  std::string Implements_Simple_Value<std::map<std::string,std::string>>::ClassName()
  {
    return "Simple_string_string_map";
  }

  template<>
  std::string Implements_Simple_Value<std::map<double,std::string>>::ClassName()
  {
    return "Simple_double_string_map";
  }
  template<>
  std::string Implements_Simple_Value<std::map<int,std::string>>::ClassName()
  {
    return "Simple_int_string_map";
  }
  template<>
  std::string Implements_Simple_Value<std::map<std::size_t,std::string>>::ClassName()
  {
    return "Simple_count_string_map";
  }




  template<>
  std::string Implements_Simple_Value<std::map<std::string,std::size_t>>::ClassName()
  {
    return "Simple_string_count_map";
  }

  template<>
  std::string Implements_Simple_Value<std::map<double,std::size_t>>::ClassName()
  {
    return "Simple_double_count_map";
  }
  template<>
  std::string Implements_Simple_Value<std::map<int,std::size_t>>::ClassName()
  {
    return "Simple_int_count_map";
  }
  template<>
  std::string Implements_Simple_Value<std::map<std::size_t,std::size_t>>::ClassName()
  {
    return "Simple_count_count_map";
  }




  template<>
  std::string Implements_Simple_Value<std::map<std::string,double>>::ClassName()
  {
    return "Simple_string_double_map";
  }

  template<>
  std::string Implements_Simple_Value<std::map<double,double>>::ClassName()
  {
    return "Simple_double_double_map";
  }
  template<>
  std::string Implements_Simple_Value<std::map<int,double>>::ClassName()
  {
    return "Simple_int_double_map";
  }
  template<>
  std::string Implements_Simple_Value<std::map<std::size_t,double>>::ClassName()
  {
    return "Simple_count_double_map";
  }



  template<>
  std::string Implements_Simple_Value<std::map<std::string,int>>::ClassName()
  {
    return "Simple_string_int_map";
  }

  template<>
  std::string Implements_Simple_Value<std::map<double,int>>::ClassName()
  {
    return "Simple_double_int_map";
  }
  template<>
  std::string Implements_Simple_Value<std::map<int,int>>::ClassName()
  {
    return "Simple_int_int_map";
  }
  template<>
  std::string Implements_Simple_Value<std::map<std::size_t,int>>::ClassName()
  {
    return "Simple_count_int_map";
  }











  template<>
  std::string Implements_Simple_Value<std::map<std::string,std::vector<std::string>>>::ClassName()
  {
    return "Simple_string_string_map_of_vectors";
  }

  template<>
  std::string Implements_Simple_Value<std::map<double,std::vector<std::string>>>::ClassName()
  {
    return "Simple_double_string_map_of_vectors";
  }
  template<>
  std::string Implements_Simple_Value<std::map<int,std::vector<std::string>>>::ClassName()
  {
    return "Simple_int_string_map_of_vectors";
  }
  template<>
  std::string Implements_Simple_Value<std::map<std::size_t,std::vector<std::string>>>::ClassName()
  {
    return "Simple_count_string_map_of_vectors";
  }




  template<>
  std::string Implements_Simple_Value<std::map<std::string,std::vector<std::size_t>>>::ClassName()
  {
    return "Simple_string_count_map_of_vectors";
  }

  template<>
  std::string Implements_Simple_Value<std::map<double,std::vector<std::size_t>>>::ClassName()
  {
    return "Simple_double_count_map_of_vectors";
  }
  template<>
  std::string Implements_Simple_Value<std::map<int,std::vector<std::size_t>>>::ClassName()
  {
    return "Simple_int_count_map_of_vectors";
  }
  template<>
  std::string Implements_Simple_Value<std::map<std::size_t,std::vector<std::size_t>>>::ClassName()
  {
    return "Simple_count_count_map_of_vectors";
  }




  template<>
  std::string Implements_Simple_Value<std::map<std::string,std::vector<double>>>::ClassName()
  {
    return "Simple_string_double_map_of_vectors";
  }

  template<>
  std::string Implements_Simple_Value<std::map<double,std::vector<double>>>::ClassName()
  {
    return "Simple_double_double_map_of_vectors";
  }
  template<>
  std::string Implements_Simple_Value<std::map<int,std::vector<double>>>::ClassName()
  {
    return "Simple_int_double_map_of_vectors";
  }
  template<>
  std::string Implements_Simple_Value<std::map<std::size_t,std::vector<double>>>::ClassName()
  {
    return "Simple_count_double_map_of_vectors";
  }



  template<>
  std::string Implements_Simple_Value<std::map<std::string,std::vector<int>>>::ClassName()
  {
    return "Simple_string_int_map_of_vectors";
  }

  template<>
  std::string Implements_Simple_Value<std::map<double,std::vector<int>>>::ClassName()
  {
    return "Simple_double_int_map_of_vectors";
  }
  template<>
  std::string Implements_Simple_Value<std::map<int,std::vector<int>>>::ClassName()
  {
    return "Simple_int_int_map_of_vectors";
  }
  template<>
  std::string Implements_Simple_Value<std::map<std::size_t,std::vector<int>>>::ClassName()
  {
    return "Simple_count_int_map_of_vectors";
  }




  /////SETS
  ///
  template<>
  std::string Implements_Simple_Value<std::map<std::string,std::set<std::string>>>::ClassName()
  {
    return "Simple_string_string_map_of_sets";
  }

  template<>
  std::string Implements_Simple_Value<std::map<double,std::set<std::string>>>::ClassName()
  {
    return "Simple_double_string_map_of_sets";
  }
  template<>
  std::string Implements_Simple_Value<std::map<int,std::set<std::string>>>::ClassName()
  {
    return "Simple_int_string_map_of_sets";
  }
  template<>
  std::string Implements_Simple_Value<std::map<std::size_t,std::set<std::string>>>::ClassName()
  {
    return "Simple_count_string_map_of_sets";
  }




  template<>
  std::string Implements_Simple_Value<std::map<std::string,std::set<std::size_t>>>::ClassName()
  {
    return "Simple_string_count_map_of_sets";
  }

  template<>
  std::string Implements_Simple_Value<std::map<double,std::set<std::size_t>>>::ClassName()
  {
    return "Simple_double_count_map_of_sets";
  }
  template<>
  std::string Implements_Simple_Value<std::map<int,std::set<std::size_t>>>::ClassName()
  {
    return "Simple_int_count_map_of_sets";
  }
  template<>
  std::string Implements_Simple_Value<std::map<std::size_t,std::set<std::size_t>>>::ClassName()
  {
    return "Simple_count_count_map_of_sets";
  }




  template<>
  std::string Implements_Simple_Value<std::map<std::string,std::set<double>>>::ClassName()
  {
    return "Simple_string_double_map_of_sets";
  }

  template<>
  std::string Implements_Simple_Value<std::map<double,std::set<double>>>::ClassName()
  {
    return "Simple_double_double_map_of_sets";
  }
  template<>
  std::string Implements_Simple_Value<std::map<int,std::set<double>>>::ClassName()
  {
    return "Simple_int_double_map_of_sets";
  }
  template<>
  std::string Implements_Simple_Value<std::map<std::size_t,std::set<double>>>::ClassName()
  {
    return "Simple_count_double_map_of_sets";
  }



  template<>
  std::string Implements_Simple_Value<std::map<std::string,std::set<int>>>::ClassName()
  {
    return "Simple_string_int_map_of_sets";
  }

  template<>
  std::string Implements_Simple_Value<std::map<double,std::set<int>>>::ClassName()
  {
    return "Simple_double_int_map_of_sets";
  }
  template<>
  std::string Implements_Simple_Value<std::map<int,std::set<int>>>::ClassName()
  {
    return "Simple_int_int_map_of_sets";
  }
  template<>
  std::string Implements_Simple_Value<std::map<std::size_t,std::set<int>>>::ClassName()
  {
    return "Simple_count_int_map_of_sets";
  }






















  template
  class Implements_Simple_Value<double>;

  template
  class Implements_Simple_Value<std::string>;

  template
  class Implements_Simple_Value<std::vector<std::string>>;

  template
  class Implements_Simple_Value<int>;


  template
  class Implements_Simple_Value<std::size_t>;


  template
  class Implements_Simple_Value<bool>;

  template
  class Implements_Simple_Value<Markov_LA::M_Matrix<double>>;

  template
  class Implements_Simple_Value<Markov_LA::M_Matrix<std::size_t>>;






































  std::string Implements_ValueId::id() const
  {
    return id_;
  }

  void Implements_ValueId::setId(const std::string &IdName)
  {
    id_=IdName;
  }

  std::string Implements_ValueId::Tip() const
  {
    return tip_;
  }

  std::string Implements_ValueId::WhatThis() const
  {
    return whatThis_;
  }

  void Implements_ValueId::setTip(const std::string &tip)
  {
    tip_=tip;
  }

  void Implements_ValueId::setWhatThis(const std::string &whatThis)
  {
    whatThis_=whatThis;
  }

  bool Implements_ValueId::isRootedVariable() const
  {
    if (parentValue()==nullptr)
      return false;
    else   return parentValue()->getChild(id())==this;
  }

  std::size_t Implements_ValueId::numChilds() const
  {
    return 0;
  }

  std::string Implements_ValueId::ith_ChildName(std::size_t ) const
  {
    return{};
  }

  std::string Implements_ValueId::childVar(const std::string &) const
  {
    return {};
  }

  const ABC_Value *Implements_ValueId::getChild(const std::string &) const
  {
    return nullptr;
  }

  ABC_Value *Implements_ValueId::getChild(const std::string &)
  {
    return nullptr;
  }


  void Implements_ValueId::removeChild(const std::string& ) {}

  const ABC_Value *Implements_ValueId::getChild(const std::string &, const std::string &) const
  {
    return nullptr;
  }

  ABC_Value *Implements_ValueId::getChild(const std::string &, const std::string &)
  {
    return nullptr;
  }

  void Implements_ValueId::pushChild(ABC_Value *)
  {
  }



  ABC_Value *Implements_ValueId::parentValue()
  {
    if (isRootedVariable())
      return p_;
    else
      return nullptr;
  }
  const ABC_Value *Implements_ValueId::parentValue() const
  {
    return p_;
  }
  std::string Implements_ValueId::refId() const
  {
    return id();
  }


  ABC_Var *Implements_ValueId::myVarPtr()
  {
    if (parentValue()!=nullptr)
      return parentValue()->getChild(myVar());
    else
      return nullptr;

  }

  const ABC_Value *Implements_ValueId::myVarPtr() const
  {
    if (parentValue()!=nullptr)
      return parentValue()->getChild(myVar());
    else
      return nullptr;

  }


  Implements_ValueId::Implements_ValueId(const std::string &name,
                                         const std::string &className,
                                         const std::string &tip,
                                         const std::string &whatthis)
    :
      id_(ABC_Value::isValidId(name)?name:""),
      var_(ABC_Value::isValidId(className)?className:""),
      p_(nullptr),
      tip_(tip),
      whatThis_(whatthis)
  {
  }

  Implements_ValueId::Implements_ValueId(const ABC_Value &other):
    id_(other.id()),
    var_(other.myVar()),
    p_(const_cast<ABC_Value*>(other.parentValue())),
    tip_(other.Tip()),
    whatThis_(other.WhatThis())
  {}

  void Implements_ValueId::putOut(const std::string &m) const
  {
    if ((parentValue()!=nullptr)&& (parentValue()!=this))
      parentValue()->putOut(m);

  }

  void Implements_ValueId::putErrorOut(const std::string &m) const
  {
    if ((parentValue()!=nullptr)&& (parentValue()!=this))
      parentValue()->putErrorOut(m);

  }



  ABC_Value *Implements_ValueId::to_PlainValue()const
  {
    return nullptr;
  }



  void Implements_ValueId::setParentValue(ABC_Value *par)
  {
    p_=par;
  }

  bool Implements_ValueId::isInDomain(const ABC_Value *value) const
  {
    auto p= parentValue();
    if (p!=nullptr)
      return p->isInDomain(value);
    else
      return false;

  }





  std::string Implements_ValueId::myVar() const
  {
    return var_;
  }

  void Implements_ValueId::setVar(const std::string &varname){
    var_=varname;
  }

  Token_Stream Implements_ValueId::toTokens() const
  {
    Token_Stream out;
    if (!Tip().empty())
      out.getToken()<<"# \""+Tip()+"\" \n";
    if (!WhatThis().empty())
      out.getToken()<<"## \""+WhatThis()+"\" \n";
    out.getToken()<<id()<<":"<<myVar();
    return out;


  }

  /**
Extract tip, whatthis, id and class from stream
@param[in, out] t buffer of unprocessed tokens already extracted from stream
@param[in,out] pos position of the next token to be processed
@param[in,out] s pointer to the stream to be extracted from
@returns DONE if an valid Implements_VarId object was extracted
@returns INTERMEDIATE if the input was valid but not complete
@returns ERROR if an valid Implements_VarId object could not be extracted

@pre expects a token buffer t with a cursor indicating the next token to be processed
@pre parameter s can be nullptr, in which case it only extract from the tokens buffer.
@pre if the pos is out of the token buffer, tokens are read from the stream


@post if successful, current object elements are changed to indicate the read object. Absent tip or whatthis are indicated by an empty string.

@post Buffer will contain all read tokens and postion will indicate +1 of the last successfully read token
@post if unsuccessful, current object is left unchanged
@post no elements are removed from the buffer in neither case, only added.

*/

  bool Implements_ValueId::processTokens(Token_Stream &tok)
  {

    tok.tokenAdvance(3);
    tok.advanceEmptyLines();
    tok.tokenAdvance(3);
    std::string tip;
    std::string whatthis;
    if (tok.toTip(tip)) tok.tokenAdvance(3);
    tok.toWhatThis(whatthis);
    tok.tokenAdvance(3);
    tok.advanceEmptyLines();
    tok.tokenAdvance(3);
    std::string id; std::string myclass;
    if (tok.toIdClass(id,myclass))
      {
        setTip(tip);
        setWhatThis(whatthis);
        setId(id);
        setVar(myclass);
        return true;
      }
    else
      return false;
  }








  std::string Implements_Refer_Var::ClassName()
  {
    return "Refers_Variable";
  }

  std::string Implements_Refer_Var::refId() const
  {
    return refId_;
  }

  ABC_Value *Implements_Refer_Var::refVar()
  {
    if (parentValue()!=nullptr)
      return parentValue()->getChild(refId(),myVar());
    return
        nullptr;
  }

  const ABC_Value *Implements_Refer_Var::refVar() const
  {
    if (parentValue()!=nullptr)
      return parentValue()->getChild(refId(),myVar());
    return
        nullptr;
  }
  ///Constructor for use as Base
  Implements_Refer_Var::Implements_Refer_Var(const std::string& idName,
                                             const std::string &refClass,
                                             const std::string& refName,
                                             const std::string &tip,
                                             const std::string &whatthis):
    Implements_ValueId(idName,refClass,tip,whatthis),
    refId_(refName){

  }




  Token_Stream Implements_Refer_Var::toTokens() const
  {
    auto out=Implements_ValueId::toTokens();
    out.getToken()<<"="<<"*"<<refId()<<"\n";
    return out;
  }

  bool Implements_Refer_Var::processTokens(Token_Stream &t)
  {
    if (!Implements_ValueId::processTokens(t))
      return false;
    else
      {
        t.tokenAdvance(3);
        if ((!t.pos()+3<t.size())
            ||(t.currToken().tok()!=Token_New::ASSIGN)
            ||(t.nextToken(1).tok()!=Token_New::MUL)
            ||(t.nextToken(2).tok()!=Token_New::IDENTIFIER)
            ||(t.nextToken(3).tok()!=Token_New::EOL)
            )
          return false;
        else
          {
            refId_=t.nextToken(2).str();
            t.advance(4);
            return true;
          }
      }
  }

  std::string Implements_Refer_Var::ith_ChildName(std::size_t i) const
  {
    if (refVar()!=nullptr)
      return refVar()->ith_ChildName(i);
    else return {};
  }

  const ABC_Value *Implements_Refer_Var::getChild(const std::string &name) const
  {
    if (refVar()!=nullptr)
      return refVar()->getChild(name);
    else return {};
  }

  ABC_Value *Implements_Refer_Var::getChild(const std::string &name)
  {
    if (refVar()!=nullptr)
      return refVar()->getChild(name);
    else return {};
  }

  const ABC_Value *Implements_Refer_Var::getChild(const std::string &name, const std::string &kind) const
  {
    if (refVar()!=nullptr)
      return refVar()->getChild(name,kind);
    else return {};
  }

  ABC_Value *Implements_Refer_Var::getChild(const std::string &name, const std::string &kind)
  {
    if (refVar()!=nullptr)
      return refVar()->getChild(name,kind);
    else return {};
  }

  void Implements_Refer_Var::pushChild(ABC_Value *var)
  {
    if (refVar()!=nullptr)
      refVar()->pushChild(var);
  }




  Token_Stream Implements_Complex_Value::toTokens() const
  {
    auto out=Implements_ValueId::toTokens();
    out.getToken()<<"begin"<<"\n";
    for (std::size_t i=0; i<numChilds(); i++)
      {
        if (getChild(ith_ChildName(i))!=nullptr)
          out.getToken()<<getChild(ith_ChildName(i))->toTokens();
      }
    out.getToken()<<myVar()<<"end"<<"\n";
    return out;
  }

  bool Implements_Complex_Value::processTokens(Token_Stream &t)
  {

    if (!Implements_ValueId::processTokens(t))
      return false;
    else
      {
        t.tokenAdvance(3);
        if ( (!(t.pos()+1<t.size()))
             ||(t.currToken().tok()!=Token_New::BEGIN)
             ||(t.nextToken(1).tok()!=Token_New::EOL))
          return false;
        else
          {
            t.advance(2);
            while ((t.pos()+1<t.size())&&
                   (!((t.nextToken(0).str()==myVar())&&
                      (t.nextToken(1).tok()==Token_New::END))))
              {
                auto p=getValueFromStream(t);
                if (p==nullptr)
                  return false;
                else
                  {
                    pushChild(p);
                    t.tokenAdvance(2);
                    while (t.currToken().tok()==Token_New::EOL)
                      {
                        ++t;
                        t.tokenAdvance(2);
                      }
                  }

              }
            if ((t.pos()+1>=t.size())||(t.nextToken(1).tok()!=Token_New::END))
              return false;
            t.advance(2);
            return true;
          }
      }

  }

  std::string Implements_Complex_Value::ClassName()
  {
    return "Implements_Complex_Var";
  }

  std::size_t Implements_Complex_Value::numChilds() const
  {
    return ids_.size();
  }

  std::string Implements_Complex_Value::ith_ChildName(std::size_t i) const
  {
    return ids_[i];
  }

  std::string Implements_Complex_Value::childVar(const std::string &idName) const
  {
    auto it=childclss_.find(idName);
    if (it!=childclss_.end())
      return it->second;
    else
      return {};
  }

  const ABC_Value *Implements_Complex_Value::getChild(const std::string &name) const
  {
    auto it=vars_.find(name);
    if (it!=vars_.end())
      return it->second;
    else if (parentValue()!=nullptr)
      return parentValue()->getChild(name);
    else return nullptr;
  }

  void Implements_Complex_Value::removeChild(const std::string &name)
  { if (vars_.erase(name)>0)
      {
        childclss_.erase(name);
        auto i=std::find(ids_.begin(),ids_.end(),name);
        if (i!=ids_.end())
          ids_.erase(i);

      }
  }

  ABC_Value *Implements_Complex_Value::getChild(const std::string &name)
  {
    auto it=vars_.find(name);
    if (it!=vars_.end())
      return it->second;
    else if (parentValue()!=nullptr)
      return parentValue()->getChild(name);
    else return nullptr;
  }

  const ABC_Value *Implements_Complex_Value::getChild(const std::string &name, const std::string &myclass) const
  {
    const ABC_Value* out=getChild(name);
    if ((out!=nullptr)&&(out->complyClass(myclass)))
      return out;
    else
      return nullptr;
  }

  ABC_Value *Implements_Complex_Value::getChild(const std::string &name, const std::string &myclass)
  {
    ABC_Value* out=getChild(name);
    if ((out!=nullptr)&&(out->complyClass(myclass)))
      return out;
    else
      return nullptr;
  }

  void Implements_Complex_Value::pushChild(ABC_Value *var)
  {
    if ((var!=nullptr)&&(ABC_Value::isValidId(var->id())))
      {
        auto it=vars_.find(var->id());
        if (it==vars_.end())
          {
            ids_.push_back(var->id());
            childclss_[var->id()]=var->myVar();
            vars_[var->id()]=var;
            var->setParentValue(this);
          }
        else {
            ABC_Value* o=vars_[var->id()];
            if (o!=var)
              {
                delete o ;
                vars_[var->id()]=var;
                childclss_[var->id()]=var->myVar();
              }
            var->setParentValue(this);
          }
      }
  }





  /// No parent, use as Base Class
  Implements_Complex_Value::Implements_Complex_Value(
      const std::string &id,
      const std::string className,
      const std::string&tip,
      const std::string &whatthis,
      const std::vector<std::pair<std::string,std::string>>& childsNameClass):
    Implements_ValueId(id,className,tip, whatthis),
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

  bool Token_New::oneCharIsEnough(Token_New::Value v)
  {
    switch (v) {
      case EOL:
      case PLUS:
      case MUL:
      case DIV:
      case EXPONENT:
      case COMMA:
      case SEMICOLON:
      case LP:
      case RP:
      case LSB:
      case RSB:
      case LCB:
      case RCB:
      case AND:
      case OR:
      case HASH:
        return true;
        break;
      default:
        return false;
        break;
      }
  }

  ///
  /// \brief Token_New::get
  /// \param stream input stream
  /// \return valid stream if a token was successfully read
  /// \post if successfull, the read token is stored.
  /// \post if fails, previous value is wiped out
  /// \post if the stream is invalid, token value is set to Token_New::END
  ///
  /// whitespaces are skipped
  ///
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
            curr_tok=STRING;

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
            str_.push_back(' ');
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
              str_.push_back(' ');

            }
            catch (...)
            {
              curr_tok=INVALID;
              return stream;
            }

            if (!isdigit(ch))
              stream.putback(ch);
            return stream;
          }
        if (curr_tok==INTEGER)
          try{
            int_=std::stoi(str_);} catch(...){ curr_tok=INVALID;}
        else if (curr_tok==UNSIGNED)
          try{
            size_=std::stoul(str_);
            str_.push_back(' ');
          }
        catch(...){ curr_tok=INVALID;}
        if (!isdigit(ch))
          stream.putback(ch);
        return stream;
      case '"':
        str_.push_back(ch);
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
          {
            curr_tok=STRING;
            str_.push_back(ch);
            str_.push_back(' ');
          }
        return stream;

      default:			// NAME, NAME=, or error
        if (isalpha(ch))
          {
            str_ = ch;
            while (stream.get(ch) && isNameChar(ch))
              str_.push_back(ch);
            str_.push_back(' ');
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
    if (identifier.empty())
      return EMPTY;
    if (identifier.back()==' ')
      identifier.pop_back();
    if ((identifier.front()=='"')||(identifier==".."))
      return STRING;
    else if (isalpha(identifier.front()))
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
        else
          return IDENTIFIER;
      }
    else if (std::isdigit(identifier.front()))
      {
        if (identifier.find_first_not_of("0123456789")!=identifier.npos)
          return UNSIGNED;
        else if  (identifier.find_first_not_of("0123456789.eE+-")!=identifier.npos)
          return REAL;
      }
    else if (std::isdigit(identifier.front()=='-')
             &&(identifier.find_first_not_of("0123456789",1)!=identifier.npos))
      return INTEGER;
    else if (identifier=="\n") return EOL;

    else if (identifier=="+") return PLUS;
    else if (identifier=="-") return MINUS;
    else if (identifier=="*") return MUL;
    else if (identifier=="/") return DIV;
    else if (identifier=="^") return EXPONENT;
    else if (identifier==".") return DOT;
    else if (identifier==":") return COLON;
    else if (identifier==",") return COMMA;
    else if (identifier==";") return SEMICOLON;
    else if (identifier=="=") return ASSIGN;
    else if (identifier=="(") return LP;
    else if (identifier==")") return RP;
    else if (identifier=="[") return LSB;
    else if (identifier=="]") return RSB;
    else if (identifier=="{") return LCB;
    else if (identifier=="}") return RCB;
    else if (identifier=="~") return NOT;
    else if (identifier=="&") return AND;
    else if (identifier=="|") return OR;
    else if (identifier=="<") return LSS;
    else if (identifier==">") return GTR;
    else if (identifier=="#") return HASH;
    else if (identifier=="::") return DCOLON;
    else if (identifier=="<=") return LEQ;
    else if (identifier=="==") return EQ;
    else if (identifier=="~=") return NEQ;
    else if (identifier==">=") return GEQ;
    else return INVALID;


  }

  Token_New::Value Token_New::toToken(char ch)
  {
    switch (ch) {
      case '\n':
      case '+':
      case '-':
      case '*':
      case '/':
      case '^':
      case '.':
      case ':':
      case ',':
      case ';':
      case '=':
      case '(':
      case ')':
      case '[':
      case ']':
      case '{':
      case '}':
      case '~':
      case '&':
      case '|':
      case '>':
      case '<':
        return static_cast<Value>(ch);
        break;
      case '"':
        return STRING;
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        return UNSIGNED;
        break;

      default:
        if (isalpha(ch)||ch=='_')
          return IDENTIFIER;
        else if (isSpaceChar(ch))
          return EMPTY;
        else
          return INVALID;
      }
  }


  ///
  /// \brief Token_New::toString string representation of an operator or keyword Token_New::Value
  /// \param identifier the category of token
  /// \return string representation of the keyword or operator token
  ///  \return empty string otherwise (number, identifier, string,path)
  ///
  std::string Token_New::toString(Token_New::Value identifier)
  {
    switch (identifier) {
      case EMPTY:
      case IDENTIFIER:
      case STRING:
      case INTEGER:
      case UNSIGNED:
      case REAL:
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
      case LCB: return "{";
      case RCB: return "}";
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

      case WHILE:   return  "while ";
      case DO:   return  "do ";
      case IF:   return  "if ";
      case THEN:   return  "then ";
      case BEGIN:   return  "begin ";
      case END:   return  "end ";
      case ELSE:   return  "else ";
      case SWITCH:   return "switch ";
      case CASE:    return "case ";
      }



  }

  char Token_New::popLastChar()
  {
    if (str_.empty())
      return {};
    char r=str_.back();
    str_.pop_back();
    curr_tok=toKeyword(str_);
    switch (curr_tok) {
      case UNSIGNED:
        try {
          size_=std::stoul(str_);

        } catch (...) {
          curr_tok=INVALID;
        }
        break;
      case REAL:
        try {
          number_=std::stod(str_);
        } catch (...) {
          curr_tok=INVALID;
        }
        break;
      case INTEGER:
        try {
          int_=std::stoi(str_);
        } catch (...) {
          curr_tok=INVALID;
        }
        break;
      default:
        break;
      }
    return r;
  }
  bool Token_New::CharIsSuccesfullyFeed(char ch)
  {
    switch (curr_tok) {
      case EMPTY:
        curr_tok=toToken(ch);
        str_.push_back(ch);
        return true;
        break;
      case EOL:
      case PLUS:
      case MUL:
      case DIV:
      case EXPONENT:
      case COMMA:
      case SEMICOLON:
      case LP:
      case RP:
      case LSB:
      case RSB:
      case LCB:
      case RCB:
      case AND:
      case OR:
      case HASH:
      case  DCOLON:
      case  LEQ:
      case  EQ:
      case  NEQ:
      case  GEQ:
      case  WHILE:
      case  DO:
      case  IF:
      case  THEN:
      case  BEGIN:
      case  END:
      case  ELSE:
      case  SWITCH:
      case  CASE:
        return false;

      case COLON:
        if (ch==':')
          {
            curr_tok=DCOLON;
            str_.push_back(ch);
            return true;
          }
        else
          {
            return false;
          }
      case ASSIGN:
        if (ch=='=')
          {
            curr_tok=EQ;
            str_.push_back(ch);
            return true;
          }
        else
          {
            return false;
          }
      case NOT:
        if (ch=='=')
          {
            curr_tok=NEQ;
            str_.push_back(ch);
            return true;
          }
        else
          {
            return false;
          }

      case LSS:
        if (ch=='=')
          {
            curr_tok=LEQ;
            str_.push_back(ch);
            return true;
          }
        else
          {
            return false;
          }

      case GTR:
        if (ch=='=')
          {
            curr_tok=GEQ;
            str_.push_back(ch);
            return true;
          }
        else
          {
            return false;
          }
      case DOT:
        if (ch=='.')
          {
            curr_tok=STRING;
            str_.push_back(ch);
            return true;
          }
        else
          {
            return false;
          }
      case MINUS:
        if (isdigit(ch))
          {
            curr_tok=INTEGER;
            str_.push_back(ch);
            return true;
          }
        else
          {
            return false;
          }
      case UNSIGNED:
        if (isdigit(ch))
          {
            str_.push_back(ch);
            return true;
          }
        else if ((ch=='.')||(ch=='e')||(ch=='E'))
          {
            str_.push_back(ch);
            curr_tok=REAL;
            return true;
          }
        else
          {
            try {
              size_=std::stoul(str_);
            } catch (...) {
              curr_tok=INVALID;
            }
            return false;
          }
      case REAL:
        if (isdigit(ch)||ch=='E'||ch=='e'||ch=='.'
            ||(((ch=='+')||(ch=='-'))&&((str_.back()=='e')||(str_.back()=='E'))))
          {
            str_.push_back(ch);
            return true;
          }
        else
          {
            try {
              number_=std::stod(str_);
            } catch (...) {
              curr_tok=INVALID;
            }
            return false;
          }
      case INTEGER:
        if (isdigit(ch))
          {
            str_.push_back(ch);
            return true;
          }
        else if ((ch=='.')||(ch=='e')||(ch=='E'))
          {
            curr_tok=REAL;
            str_.push_back(ch);
            return true;
          }
        else
          {
            try {
              int_=std::stoi(str_);
            } catch (...) {
              curr_tok=INVALID;
            }
            return false;
          }
      case STRING:
        if (str_.back()!='"')
          {
            str_.push_back(ch);
            return true;
          }
        else
          {
            return false;
          }
      case IDENTIFIER:
        if (str_.back()==' ')
          {
            return false;
          }
        else if (isNameChar(ch)||ch==' ')
          {
            str_.push_back(ch);
            return true;
          }
        else
          {
            return false;
          }
      case INVALID:
        {
          return false;
        }
      }

  }



  Token_New::Token_New():
    curr_tok(EMPTY),
    number_(),
    int_(),
    size_(),
    str_(){}

  Token_New::Token_New(double d):
    curr_tok{REAL},
    number_(d),
    int_{},
    size_{},
    str_{std::to_string(d)}{}

  Token_New::Token_New(int n):
    curr_tok{INTEGER},
    number_{},
    int_{n},
    size_{},
    str_{std::to_string(n)}{}

  Token_New::Token_New(std::size_t s):
    curr_tok{UNSIGNED},
    number_{},
    int_{},
    size_{s},
    str_{std::to_string(s)}{}

  Token_New::Token_New(const std::string& d):
    curr_tok{},
    number_{},
    str_{}{
    std::stringstream ss(d);
    get(ss);
  }

//  Token_New::Token_New(Token_New::Value v):
//    curr_tok{},
//    number_{},
//    str_{}{


//  }

  Token_New::Token_New(char ch):
    curr_tok(toToken(ch)),
    number_(),
    int_(),
    size_(),
    str_()
  {
    if (curr_tok!=STRING&&curr_tok!=EMPTY)
      str_.push_back(ch);
  }






  //*************************************************************************************//



  std::string ABC_Value::toString() const
  {
    std::string out;
    auto t=toTokens();
    for (const Token_New& i:t.getToken())
      {
        out+=i.toString();
      }
    return out;
  }


  /**
Extract an ABC_Var object from stream and it insert in a complex var
@param[in, out]  parent complex ABC_Object where the read object is inserted
@param[in, out] t  buffer that stores unprocessed tokens already extracted from stream
@returns the input stream. If an invalid name is found, it sets the failbit
 of the stream (and  therefore the boolean operator applied
on the stream will return false).

@pre Expects a two words: the class name and the beginLabel(). It admits
commenst after the characters //
@post on success, a goodbit stream, an empty line and the class name in
the parameter className

*/

  ABC_Value *ABC_Value::getValueFromStream(Token_Stream& t)
  {
    auto pos0=t.pos();
    Implements_ValueId n;

    if (!n.processTokens(t))
      return nullptr;
    t.tokenAdvance(5);
    if (!(t.pos()<t.size()))
      return nullptr;
    Token_New to=t.currToken();
    ABC_Value* out=nullptr;
    // we have to find what is out
    // possibilities:  reference, simple_var or complex_var

    if (to.tok()==Token_New::ASSIGN)
      {
        ++t;
        if (!(t.pos()<t.size())) return nullptr;
        to=t.currToken();
        if (to.tok()==Token_New::MUL)
          {  // Implements_Refer_Var

            ++t;
            if (!(t.pos()<t.size())) return nullptr;
            to=t.currToken();
            if (to.tok()!=Token_New::IDENTIFIER)
              return nullptr;
            else
              {
                ++t;
                if (t.currToken().tok()==Token_New::EOL)
                  ++t;

                return new Implements_Refer_Var(n.id(),n.myVar(),t.currToken().str(),n.Tip(),n.WhatThis());

              }
          }
        else
          {
            //Implements_Simple_Value, lets find out of what
            ++t;
            switch (to.tok())
              {
              case Token_New::REAL:
                return new Implements_Simple_Value<double>(n.id(),to.realValue(),n.myVar());
                break;
              case Token_New::INTEGER:
                return new Implements_Simple_Value<int>(n.id(),to.intval(),n.myVar());
                break;
              case Token_New::UNSIGNED:
                return new Implements_Simple_Value<std::size_t>(n.id(),to.count(),n.myVar());
                break;
              case Token_New::IDENTIFIER:
                return new Implements_Simple_Value<std::string>(n.id(),t.currToken().str(),n.myVar());
                break;
              case Token_New::EOL:
                // that means it is a matrix, a vector or a map
                {
                  if (!(t.pos()<t.size()))
                    return nullptr;
                  to=t.currToken();
                  if (to.tok()==Token_New::LSB)  // vector !!
                    {
                      if (!(t.pos()<t.size())) return nullptr;

                      to=t.nextToken(1);

                      switch (to.tok())
                        {
                        case Token_New::REAL:
                          out=new Implements_Simple_Value<std::vector<double>>;
                          break;
                        case Token_New::INTEGER:
                          out=new Implements_Simple_Value<std::vector<int>>;
                          break;
                        case Token_New::UNSIGNED:
                          out=new Implements_Simple_Value<std::vector<std::size_t>>;
                          break;
                        case Token_New::IDENTIFIER:
                          out=new Implements_Simple_Value<std::vector<std::string>>;
                          break;
                        default:
                          return nullptr;
                        }
                    }


                  if (to.tok()==Token_New::LCB)  // set or map !!
                    {

                      if ((t.pos()+3<t.size())&&
                          (t.nextToken(3).tok()==Token_New::COLON)) //map
                        {  // it is a simple key map!!
                          // lets find out the types
                          to=t.nextToken(1);
                          Token_New to2=t.nextToken(3);
                          switch (to.tok())
                            {
                            case Token_New::REAL:
                              switch (to2.tok())
                                {
                                case Token_New::REAL:
                                  out=new  Implements_Simple_Value<std::map<double,double>>;
                                  break;
                                case Token_New::INTEGER:
                                  out=new Implements_Simple_Value<std::map<double,int>>;
                                  break;
                                case Token_New::UNSIGNED:
                                  out=new Implements_Simple_Value<std::map<double,std::size_t>>;
                                  break;
                                case Token_New::IDENTIFIER:
                                  out=new Implements_Simple_Value<std::map<double,std::string>>;
                                  break;
                                case Token_New::EOL:
                                  {
                                    if (!(t.pos()+4<t.size()))
                                      return nullptr;
                                    to2=t.nextToken(4);
                                    auto to3=t.nextToken(5);
                                    if (to2.tok()==Token_New::LSB) //vector
                                      {

                                        switch (to3.tok())
                                          {
                                          case Token_New::REAL:
                                            out=new Implements_Simple_Value<
                                                std::map<double,std::vector<double>>>;
                                            break;
                                          case Token_New::INTEGER:
                                            out=new Implements_Simple_Value<
                                                std::map<double,std::vector<int>>>;
                                            break;
                                          case Token_New::UNSIGNED:
                                            out=new Implements_Simple_Value<
                                                std::map<double,std::vector<std::size_t>>>;
                                            break;
                                          case Token_New::IDENTIFIER:
                                            out=new Implements_Simple_Value<
                                                std::map<double,std::vector<std::string>>>;
                                            break;

                                          default:
                                            return nullptr;
                                          }
                                      }
                                    else if (to2.tok()==Token_New::LCB) //set
                                      {
                                        switch (to3.tok())
                                          {
                                          case Token_New::REAL:
                                            out=new Implements_Simple_Value<
                                                std::map<double,std::set<double>>>;
                                            break;
                                          case Token_New::INTEGER:
                                            out=new Implements_Simple_Value<
                                                std::map<double,std::set<int>>>;
                                            break;
                                          case Token_New::UNSIGNED:
                                            out=new Implements_Simple_Value<
                                                std::map<double,std::set<std::size_t>>>;
                                            break;
                                          case Token_New::IDENTIFIER:
                                            out=new Implements_Simple_Value<
                                                std::map<double,std::set<std::string>>>;
                                            break;

                                          default:
                                            return nullptr;
                                          }
                                      }
                                    else {
                                        return nullptr;
                                      }
                                  }
                                  break;
                                default:
                                  return nullptr;
                                }
                              break;

                            case Token_New::INTEGER:
                              switch (to2.tok())
                                {
                                case Token_New::REAL:
                                  out=new  Implements_Simple_Value<std::map<int,double>>;
                                  break;
                                case Token_New::INTEGER:
                                  out=new Implements_Simple_Value<std::map<int,int>>;
                                  break;
                                case Token_New::UNSIGNED:
                                  out=new Implements_Simple_Value<std::map<int,std::size_t>>;
                                  break;
                                case Token_New::IDENTIFIER:
                                  out=new Implements_Simple_Value<std::map<int,std::string>>;
                                  break;
                                case Token_New::EOL:
                                  {
                                    if (!(t.pos()+4<t.size()))
                                      return nullptr;
                                    to2=t.nextToken(4);
                                    auto to3=t.nextToken(5);

                                    if (to2.tok()==Token_New::LSB) //vector
                                      {

                                        switch (to3.tok())
                                          {
                                          case Token_New::REAL:
                                            out=new Implements_Simple_Value<
                                                std::map<int,std::vector<double>>>;
                                            break;
                                          case Token_New::INTEGER:
                                            out=new Implements_Simple_Value<
                                                std::map<int,std::vector<int>>>;
                                            break;
                                          case Token_New::UNSIGNED:
                                            out=new Implements_Simple_Value<
                                                std::map<int,std::vector<std::size_t>>>;
                                            break;
                                          case Token_New::IDENTIFIER:
                                            out=new Implements_Simple_Value<
                                                std::map<int,std::vector<std::string>>>;
                                            break;

                                          default:
                                            return nullptr;
                                          }
                                      }
                                    else if (to2.tok()==Token_New::LCB) //set
                                      {
                                        switch (to3.tok())
                                          {
                                          case Token_New::REAL:
                                            out=new Implements_Simple_Value<
                                                std::map<int,std::set<double>>>;
                                            break;
                                          case Token_New::INTEGER:
                                            out=new Implements_Simple_Value<
                                                std::map<int,std::set<int>>>;
                                            break;
                                          case Token_New::UNSIGNED:
                                            out=new Implements_Simple_Value<
                                                std::map<int,std::set<std::size_t>>>;
                                            break;
                                          case Token_New::IDENTIFIER:
                                            out=new Implements_Simple_Value<
                                                std::map<int,std::set<std::string>>>;
                                            break;

                                          default:
                                            return nullptr;
                                          }
                                      }
                                  }
                                  break;
                                default:
                                  return nullptr;
                                }
                              break;
                            case Token_New::UNSIGNED:
                              switch (to2.tok())
                                {
                                case Token_New::REAL:
                                  out=new  Implements_Simple_Value<std::map<std::size_t,double>>;
                                  break;
                                case Token_New::INTEGER:
                                  out=new Implements_Simple_Value<std::map<std::size_t,int>>;
                                  break;
                                case Token_New::UNSIGNED:
                                  out=new Implements_Simple_Value<std::map<std::size_t,std::size_t>>;
                                  break;
                                case Token_New::IDENTIFIER:
                                  out=new Implements_Simple_Value<std::map<std::size_t,std::string>>;
                                  break;
                                case Token_New::EOL:
                                  {
                                    if (!(t.pos()+4<t.size()))
                                      return nullptr;
                                    to2=t.nextToken(4);
                                    auto to3=t.nextToken(5);

                                    if (to2.tok()==Token_New::LSB) //vector
                                      {

                                        switch (to3.tok())
                                          {
                                          case Token_New::REAL:
                                            out=new Implements_Simple_Value<
                                                std::map<std::size_t,std::vector<double>>>;
                                            break;
                                          case Token_New::INTEGER:
                                            out=new Implements_Simple_Value<
                                                std::map<std::size_t,std::vector<int>>>;
                                            break;
                                          case Token_New::UNSIGNED:
                                            out=new Implements_Simple_Value<
                                                std::map<std::size_t,std::vector<std::size_t>>>;
                                            break;
                                          case Token_New::IDENTIFIER:
                                            out=new Implements_Simple_Value<
                                                std::map<std::size_t,std::vector<std::string>>>;
                                            break;

                                          default:
                                            return nullptr;
                                          }
                                      }
                                    else if (to2.tok()==Token_New::LCB) //set
                                      {
                                        switch (to3.tok())
                                          {
                                          case Token_New::REAL:
                                            out=new Implements_Simple_Value<
                                                std::map<std::size_t,std::set<double>>>;
                                            break;
                                          case Token_New::INTEGER:
                                            out=new Implements_Simple_Value<
                                                std::map<std::size_t,std::set<int>>>;
                                            break;
                                          case Token_New::UNSIGNED:
                                            out=new Implements_Simple_Value<
                                                std::map<std::size_t,std::set<std::size_t>>>;
                                            break;
                                          case Token_New::IDENTIFIER:
                                            out=new Implements_Simple_Value<
                                                std::map<std::size_t,std::set<std::string>>>;
                                            break;

                                          default:
                                            return nullptr;
                                          }
                                      }

                                    else
                                      return nullptr;
                                  }
                                  break;
                                default:
                                  return nullptr;
                                }
                              break;
                            case Token_New::IDENTIFIER:
                              switch (to2.tok())
                                {
                                case Token_New::REAL:
                                  out=new  Implements_Simple_Value<std::map<std::string,double>>;
                                  break;
                                case Token_New::INTEGER:
                                  out=new Implements_Simple_Value<std::map<std::string,int>>;
                                  break;
                                case Token_New::UNSIGNED:
                                  out=new Implements_Simple_Value<std::map<std::string,std::size_t>>;
                                  break;
                                case Token_New::IDENTIFIER:
                                  out=new Implements_Simple_Value<std::map<std::string,std::string>>;
                                  break;
                                case Token_New::EOL:
                                  {
                                    if (!(t.pos()+4<t.size()))
                                      return nullptr;
                                    to2=t.nextToken(4);
                                    auto to3=t.nextToken(5);

                                    if (to2.tok()==Token_New::LSB) //vector
                                      {

                                        switch (to3.tok())
                                          {
                                          case Token_New::REAL:
                                            out=new Implements_Simple_Value<
                                                std::map<std::string,std::vector<double>>>;
                                            break;
                                          case Token_New::INTEGER:
                                            out=new Implements_Simple_Value<
                                                std::map<std::string,std::vector<int>>>;
                                            break;
                                          case Token_New::UNSIGNED:
                                            out=new Implements_Simple_Value<
                                                std::map<std::string,std::vector<std::size_t>>>;
                                            break;
                                          case Token_New::IDENTIFIER:
                                            out=new Implements_Simple_Value<
                                                std::map<std::string,std::vector<std::string>>>;
                                            break;

                                          default:
                                            return nullptr;
                                          }
                                      }
                                    else if (to2.tok()==Token_New::LCB) //set
                                      {
                                        switch (to3.tok())
                                          {
                                          case Token_New::REAL:
                                            out=new Implements_Simple_Value<
                                                std::map<std::string,std::set<double>>>;
                                            break;
                                          case Token_New::INTEGER:
                                            out=new Implements_Simple_Value<
                                                std::map<std::string,std::set<int>>>;
                                            break;
                                          case Token_New::UNSIGNED:
                                            out=new Implements_Simple_Value<
                                                std::map<std::string,std::set<std::size_t>>>;
                                            break;
                                          case Token_New::IDENTIFIER:
                                            out=new Implements_Simple_Value<
                                                std::map<std::string,std::set<std::string>>>;
                                            break;

                                          default:
                                            return nullptr;
                                          }
                                      }

                                    else
                                      return nullptr;
                                  }
                                  break;
                                default:
                                  return nullptr;
                                }
                              break;

                            default:
                              return nullptr;
                            }
                        }
                      else
                        //set
                        {
                          if (!(t.pos()<t.size())) return nullptr;

                          to=t.nextToken(1);

                          switch (to.tok())
                            {
                            case Token_New::REAL:
                              out=new Implements_Simple_Value<std::vector<double>>;
                              break;
                            case Token_New::INTEGER:
                              out=new Implements_Simple_Value<std::vector<int>>;
                              break;
                            case Token_New::UNSIGNED:
                              out=new Implements_Simple_Value<std::vector<std::size_t>>;
                              break;
                            case Token_New::IDENTIFIER:
                              out=new Implements_Simple_Value<std::vector<std::string>>;
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
                      out=new Implements_Simple_Value<Markov_LA::M_Matrix<double>>;
                      break;
                      //out=new Implements_Simple_Value<Markov_LA::M_Matrix<std::size_t>>;
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
    else if  (t.currToken().tok()==Token_New::BEGIN)
      {
        // Complex_Var
        out=new Implements_Complex_Value;
      }
    else
      return nullptr;
    t.setPos(pos0);
    if (!out->processTokens(t))
      {
        delete out;
        return nullptr;
      }
    else
      {
        return out;
      }

  }










  bool ABC_Value::isValidId(std::string name)
  {
    return Token_New(name).tok()==Token_New::IDENTIFIER;
  }

  std::string ABC_Value::ClassName()
  {
    return "ABC_Var";
  }

  std::set<std::string> ABC_Value::SuperClasses()
  {
    return {ClassName()};
  }



  bool ABC_Value::complyClass(const std::string classname) const
  {
    auto s= mySuperClasses();
    bool ret= s.find(classname)!=s.end();
    return ret;
  }

  void ABC_Value::pushIdChild(const std::string &id, ABC_Value *var)
  {
    var->setId(id);
    pushChild(var);
  }




  Implements_Complex_Class::Implements_Complex_Class(const std::string &id,
                                                     const std::string& className,
                                                     const std::string &tip,
                                                     const std::string &whatthis,
                                                     const std::map<std::string,fieldDef> m):
    Implements_Complex_Value(id,className,tip,whatthis)
  {
    for (const auto& e:m)
      {
        pushChild(new Implements_Refer_Var(e.first,
                                           e.second.superClass,
                                           e.second.className,
                                           e.second.tip,
                                           e.second.whatthis));
      }
  }




  bool Implements_Complex_Class::isInDomain(const ABC_Value *value) const
  {
    if (value==nullptr)
      return false;
    if (value->myVar()!=id())
      return false;
    if (numChilds()!=value->numChilds())
      return false;
    for (std::size_t i=0; i<numChilds(); ++i)
      {
        auto iname=ith_ChildName(i);
        auto valueVar=value->getChild(iname);
        if (valueVar==nullptr)
          return false;
        else if (!getChild(iname)->isInDomain(valueVar))
          return false;
      }
    return true;

  }




  void Implements_Complex_Class::push_back(const std::string &idName,
                                           const std::string &superclassname,
                                           const std::string &classname,
                                           const std::string& tip,
                                           const std::string& whatthis)
  {
    pushChild(new Implements_Refer_Var(idName,superclassname, classname,tip, whatthis));
  }

  /*
  std::string Implements_Categorical_Class::ClassName()
  {
    return "Category_Class";
  }

  std::set<std::string> Implements_Categorical_Class::SuperClasses()
  {
    return Implements_Simple_Value<std::map<std::string,int>>::SuperClasses()+ClassName();
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
    Implements_Simple_Value<std::map<std::string,int>>(parent,categoryName,{},ClassName()),
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
    Implements_Simple_Value<std::map<std::string,int>>(parent,categoryName,categoriesRank,ClassName()),
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
    Implements_Simple_Value<std::map<std::string,int>>(parent,categoryName,{},ClassName()),
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
