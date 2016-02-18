#include <numeric>
#include <iostream>
#include "Markov_IO/ABC_Var.h"
#include "Markov_Console/ExpressionManager.h"



namespace Markov_IO {




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
  std::string Implements_Simple_Value<std::set<std::string>>::ClassName()
  {
    return "Simple_string_set_var";
  }

  template<>
  std::string Implements_Simple_Value<std::set<double>>::ClassName()
  {
    return "Simple_double_set_var";
  }
  template<>
  std::string Implements_Simple_Value<std::set<int>>::ClassName()
  {
    return "Simple_int_set_var";
  }
  template<>
  std::string Implements_Simple_Value<std::set<std::size_t>>::ClassName()
  {
    return "Simple_count_set_var";
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
  std::string Implements_Simple_Value<Markov_LA::M_Matrix<int>>::ClassName()
  {
    return "Simple_int_Matrix_var";
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
    else   return parentValue()->idToValue(id())==this;
  }

  std::size_t Implements_ValueId::numChilds() const
  {
    return 0;
  }

  std::string Implements_ValueId::ith_ChildName(std::size_t ) const
  {
    return{};
  }



  const ABC_Value *Implements_ValueId::idToValue(const std::string & idName) const
  {
    if (parentValue()!=nullptr)
      return parentValue()->idToValue(idName);
    else return nullptr;
  }

  ABC_Value *Implements_ValueId::idToValue(const std::string &)
  {
    return nullptr;
  }


  void Implements_ValueId::removeChild(const std::string& ) {}

  const ABC_Value *Implements_ValueId::idToValue(const std::string &idName, const std::string &varName) const
  {
    if (parentValue()!=nullptr)
      return parentValue()->idToValue(idName,varName);
    else return nullptr;
  }

  ABC_Value *Implements_ValueId::idToValue(const std::string & , const std::string & )
  {
    return nullptr;
  }

  void Implements_ValueId::pushChild(ABC_Value *)
  {
  }



  bool Implements_ValueId::isMyParent(const ABC_Value* aParent) const
  {
    if (p_==nullptr)
      return false;
    else if (aParent==p_)
       return true;
    else
      return p_->isMyParent(aParent);

  }
  const ABC_Value *Implements_ValueId::parentValue() const
  {
    return p_;
  }
  std::string Implements_ValueId::refId() const
  {
    return id();
  }


  ABC_Var *Implements_ValueId::myVarPtr(ABC_Value* parent)
  {
    if (isMyParent(parent))
      return parent->idToValue(myVar());
    else
      return nullptr;

  }

  const ABC_Value *Implements_ValueId::myVarPtr() const
  {
    if (parentValue()!=nullptr)
      return parentValue()->idToValue(myVar());
    else
      return nullptr;

  }

  bool Implements_ValueId::complyModes(const std::string m) const
  {
    if ((parentValue()!=nullptr)
        &&(parentValue()->idToValue(myVar())!=nullptr))
      {
        auto const mo=parentValue()->idToValue(myVar())->modes();
        if(mo.find(m)!=mo.end())
          return true;
        else
          return false;
      }
    else return false;
  }

  std::set<std::string> Implements_ValueId::modes() const
  {

    return {};
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

  Implements_ValueId::~Implements_ValueId(){}

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

  ABC_Value *Implements_ValueId::to_PlainValue(const ABC_Measure *) const
  {
    return nullptr;
  }

  ABC_Value *Implements_ValueId::toMeasure(const ABC_Value *) const
  {
    return nullptr;
  }

  ABC_Var *Implements_ValueId::toSameVar(const ABC_Value *) const
  {
    return nullptr;
  }

  ABC_Value *Implements_ValueId::toPlainMeasure() const
  {
    return nullptr;
  }

  ABC_Var *Implements_ValueId::toPlainSameVar() const
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





  ABC_Value *Implements_ValueId::create() const
  {
    return new Implements_ValueId;
  }

  Implements_ValueId *Implements_ValueId::clone() const
  {
    return new Implements_ValueId(*this);
  }

  void Implements_ValueId::reset()
  {
    if ((parentValue()!=nullptr)&&(!isRootedVariable()))
      {
        auto s=dynamic_cast<const Implements_ValueId*>(parentValue()->idToValue(id()));
        if (s!=nullptr)
          *this=*s;

      }

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
    std::string tip;
    std::string whatthis;
    if (tok.toTip(tip))
      {
        tok.tokenAdvance(3);
      }
    tok.toWhatThis(whatthis);
    tok.tokenAdvance(3);
    tok.advanceEmptyLines();
    tok.tokenAdvance(3);
    std::string id; std::string myclass;
    bool out=tok.toIdClass(id,myclass);
    if (out)
      {
        setTip(tip);
        setWhatThis(whatthis);
        setId(id);
        setVar(myclass);
      }
    return out;
  }






  std::string Implements_Refer_Var::ClassName()
  {
    return "Refers_Variable";
  }

  std::string Implements_Refer_Var::refId() const
  {
    return refId_;
  }

  void Implements_Refer_Var::setRefId(const std::string &ref_id)
  {
    refId_=ref_id;
  }



  const ABC_Value *Implements_Refer_Var::refVar() const
  {
    if (parentValue()!=nullptr)
      return parentValue()->idToValue(refId(),myVar());
    else
      return nullptr;
  }

  Implements_Refer_Var *Implements_Refer_Var::clone() const
  {
    return new Implements_Refer_Var(*this);
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

  Implements_Refer_Var::Implements_Refer_Var(const Implements_ValueId &id):
    Implements_ValueId(id.id(),id.myVar(),id.Tip(),id.WhatThis()),
    refId_(){

  }






  Token_Stream Implements_Refer_Var::toTokens() const
  {
    auto out=Implements_ValueId::toTokens();
    out.getToken()<<"="<<"*"<<refId()<<"\n";
    return out;
  }

  bool Implements_Refer_Var::processTokens(Token_Stream &t)
  {
    bool out=Implements_ValueId::processTokens(t);
    if (!out)
      return out;
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

  const ABC_Value *Implements_Refer_Var::idToValue(const std::string &name) const
  {
    if (refVar()!=nullptr)
      return refVar()->idToValue(name);
    else return nullptr;
  }

  ABC_Value *Implements_Refer_Var::idToValue(const std::string &)
  {
     return nullptr;
  }

  const ABC_Value *Implements_Refer_Var::idToValue(const std::string &name, const std::string &kind) const
  {
    if (refVar()!=nullptr)
      return refVar()->idToValue(name,kind);
    else return nullptr;
  }

  ABC_Value *Implements_Refer_Var::idToValue(const std::string &name, const std::string &kind)
  {
     return nullptr;
  }

  void Implements_Refer_Var::pushChild(ABC_Value *)
  {

  }




  Token_Stream Implements_Complex_Value::toTokens() const
  {
    auto out=Implements_ValueId::toTokens();
    out.getToken()<<"begin"<<"\n";
    for (std::size_t i=0; i<numChilds(); i++)
      {
        if (idToValue(ith_ChildName(i))!=nullptr)
          out.getToken()<<idToValue(ith_ChildName(i))->toTokens();
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

  ABC_Value *Implements_Complex_Value::toPlainMeasure() const
  {
    return nullptr;
  }

  ABC_Var *Implements_Complex_Value::toPlainSameVar() const
  {
    return nullptr;
  }

  ABC_Value *Implements_Complex_Value::to_PlainValue() const
  {
    return new Implements_Complex_Value(*this);
  }

  void Implements_Complex_Value::cloneChids()
  {
    for (auto& it:vars_)
      {
        if (it.second!=nullptr)
          {
            ABC_Value* n=it.second->clone();

            it.second=n;
          }
      }
  }

  void Implements_Complex_Value::resetChildsParent()
  {
    for (auto& it:vars_)
      {
        if (it.second!=nullptr)
          {
            it.second->setParentValue(this);
          }
      }
  }

  std::string Implements_Complex_Value::ClassName()
  {
    return "Implements_Complex_Var";
  }

  Implements_Complex_Value *Implements_Complex_Value::create() const
  {
    return new Implements_Complex_Value;
  }

  Implements_Complex_Value *Implements_Complex_Value::clone() const
  {
    return new Implements_Complex_Value(*this);
  }

  void Implements_Complex_Value::reset()
  {
    if ((parentValue()!=nullptr)&&(!isRootedVariable()))
      {
        auto s=dynamic_cast<const Implements_Complex_Value*>(parentValue()->idToValue(id()));
        if (s!=nullptr)
          *this=*s;

      }

  }

  std::size_t Implements_Complex_Value::numChilds() const
  {
    return ids_.size();
  }

  std::string Implements_Complex_Value::ith_ChildName(std::size_t i) const
  {
    return ids_[i];
  }



  const ABC_Value *Implements_Complex_Value::idToValue(const std::string &name) const
  {
    auto it=vars_.find(name);
    if (it!=vars_.end())
      return it->second;
    else if (parentValue()!=nullptr)
      return parentValue()->idToValue(name);
    else return nullptr;
  }

  ABC_Value *Implements_Complex_Value::popLastChild()
  {
    if (!ids_.empty())
      {
        std::string lastChild=ids_.back();
        ABC_Value* out=idToValue(lastChild);
        removeChild(lastChild);
        return out;
      }
    else
      return nullptr;
  }

  std::vector<std::string> Implements_Complex_Value::getChildList(const std::string &className) const
  {
    if (className.empty())
      return ids_;
    else
      {
        std::vector<std::string> out;
        for (std::string s:ids_)
          {
            auto it=vars_.find(s);
            if (it!=vars_.end())
              {
                ABC_Value* v=it->second;
                if (v->complyClass(className))
                  out.push_back(s);
              }
          }
        return out;
      }
  }

  void Implements_Complex_Value::removeChild(const std::string &name)
  { if (vars_.erase(name)>0)
      {
        auto i=std::find(ids_.begin(),ids_.end(),name);
        if (i!=ids_.end())
          ids_.erase(i);

      }
  }

  ABC_Value *Implements_Complex_Value::idToValue(const std::string &name)
  {
    auto it=vars_.find(name);
    if (it!=vars_.end())
      return it->second;
    else return nullptr;
  }

  const ABC_Value *Implements_Complex_Value::idToValue(const std::string &name, const std::string &myclass) const
  {
    const ABC_Value* out=idToValue(name);
    if ((out!=nullptr)&&(out->complyClass(myclass)))
      return out;
    else
      return nullptr;
  }

  ABC_Value *Implements_Complex_Value::idToValue(const std::string &name, const std::string &myclass)
  {
    ABC_Value* out=idToValue(name);
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
            vars_[var->id()]=var;
            var->setParentValue(this);
          }
        else {
            ABC_Value* o=vars_[var->id()];
            if (o!=var)
              {
                delete o ;
                vars_[var->id()]=var;
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
    ids_(),vars_{}
  {
    for (auto& e:childsNameClass)
      {
        ids_.push_back(e.first);
      }
  }

  Implements_Complex_Value::Implements_Complex_Value(const ABC_Value &other):
    Implements_ValueId(other)
  {

    for (std::size_t i=0; i<other.numChilds(); ++i)
      {
        std::string name=other.ith_ChildName(i);
        auto o=other.idToValue(name);
        if (o!=nullptr)
          pushChild(o->clone());
      }
  }

  Implements_Complex_Value::Implements_Complex_Value(const Implements_Complex_Value &other)
    :
      Implements_ValueId(other),
      ids_(other.ids_),
      vars_(other.vars_)
  {
    cloneChids();
    resetChildsParent();
  }

  Implements_Complex_Value::Implements_Complex_Value(Implements_Complex_Value &&other):
    Implements_ValueId(std::move(other)),
    ids_(std::move(other.ids_)),
    vars_(std::move(other.vars_))
  {
    resetChildsParent();
  }

  Implements_Complex_Value &Implements_Complex_Value::operator=(Implements_Complex_Value &&other)
  {
    if (this!=&other)
      {
        privateDelete();
        Implements_ValueId::operator =(std::move(other));
        ids_=std::move(other.ids_);
        vars_=std::move(other.vars_);
        resetChildsParent();
      }
    return *this;
  }

  Implements_Complex_Value &Implements_Complex_Value::operator=(const Implements_Complex_Value &other)
  {
    if (this!=&other)
      {
        *this=Implements_Complex_Value(other);
        resetChildsParent();

      }
    return *this;
  }

  void Implements_Complex_Value::privateDelete()
  {
    for (auto& id:vars_)
      {
        auto o=id.second;
        delete o;
      }
  }

  Implements_Complex_Value::~Implements_Complex_Value(){
    privateDelete();
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

  std::ostream &ABC_Value::put(std::ostream &s) const
  {
    s<<toString();
    return s;
  }

  ABC_Value *ABC_Value::toIndicatedVar(const ABC_Value *source) const
  {
    if (source->myVar()==id())
      return toMeasure(source);
    else if (source->myVar()==myClass())
      return toSameVar(source);
    else return nullptr;
  }

  ABC_Measure *ABC_Value::getMeasureFromValue(ABC_Value *v)
  {
    if (v)
      {
        auto m=idToValue(v->myVar());
        if (m)
          return m->toIndicatedVar(v);
        else
          return nullptr;
      }
    else
      return nullptr;
  }

  bool ABC_Value::has_child(const std::string &name) const
  {
    return idToValue(name)!=nullptr;
  }

  std::vector<std::string> ABC_Value::getChildList() const
  {
    std::vector<std::string> out(numChilds());
    for (std::size_t i=0; i<numChilds(); i++)
      out[i]=ith_ChildName(i);
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

  ABC_Value::~ABC_Value(){}

  std::string ABC_Value::myClass() const
  {
    return ClassName();
  }

  std::set<std::string> ABC_Value::mySuperClasses() const
  {
    return {ClassName()};
  }













  bool ABC_Value::isValidId(std::string name)
  {
    return Token_New(name).tok()==Token_New::IDENTIFIER;
  }

  std::__cxx11::string ABC_Value::nextId(const std::__cxx11::string &idTemplate)
  {
    auto n=getVersionNumber(idTemplate);

    if (n!=std::string::npos)
      {
        ++n;
        return idTemplate.substr(0,idTemplate.find_last_of('_')+1)+std::to_string(n);
      }
    else
      return idTemplate+"_0";
  }

  std::size_t ABC_Value::getVersionNumber(const std::__cxx11::string &id)
  {
    std::stringstream ss(id.substr(id.find_last_of('_')));
    std::size_t n;
    if (ss>>n)
      return n;
    else
      return std::string::npos;
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

  bool ABC_Value::complyVar(const std::string &var, std::string *errormessage) const
  {
    if (myVar()==var)
      {
        if (errormessage!=nullptr)
          *errormessage=id()+"is defined as a"+var+" var";
        return true;
      }
    else if (complyClass(var))
      {
        if (errormessage!=nullptr)
          *errormessage=id()+" complies to "+var+" class";
        return true;
      }
    else if ((idToValue(var)!=nullptr))
      {
        if (idToValue(var)->isValueOfThisVar(this))
          {
            if (errormessage!=nullptr)
              *errormessage=id()+ " follows "+var+" requirements";
            return true;
          }
        else
          {
            if (errormessage!=nullptr)
              *errormessage=id()+ " does not follow "+var+" requirements";
            return false;

          }
      }
    else
      {
        if (errormessage!=nullptr)
          *errormessage=var+" is not defined as a Variable";
         return false;
      }
  }

  void ABC_Value::pushIdChild(const std::string &id, ABC_Value *var)
  {
    var->setId(id);
    pushChild(var);
  }






  Implements_Complex_Class
  ::Implements_Complex_Class(const std::string &id,
                             const std::string& className,
                             const std::string &tip,
                             const std::string &whatthis,
                             const std::map<std::string,fieldDef> m):
    Implements_Complex_Value(id,className,tip,whatthis)
  {
    for (const auto& e:m)
      {
        pushChild(new Implements_Refer_Var(e.first
                                           ,e.second.superClass
                                           ,{}
                                           ,e.second.tip
                                           ,e.second.whatthis));
        if (e.second.isMandatory)
          isMandatory_.insert(e.first);
      }
  }




  bool Implements_Complex_Class::isInDomain(const ABC_Value *value) const
  {
    if (value==nullptr)
      return false;
    if (value->myVar()!=id())
      return false;
    if (numMandatoryChilds()>value->numChilds())
      return false;
    for (std::size_t i=0; i<numChilds(); ++i)
      {
        auto iname=ith_ChildName(i);
        auto valueVar=value->idToValue(iname);
        if (valueVar==nullptr)
          {
            if (isMandatory(iname))
              return false;
          }
        else if (!idToValue(iname)->isInDomain(valueVar))
          return false;
      }
    return true;

  }




  void Implements_Complex_Class::push_back(const std::string &idName,
                                           const std::string &classname,
                                           const std::string& tip,
                                           const std::string& whatthis,
                                           bool mandatory)
  {
    pushChild(new Implements_Refer_Var(idName, classname,{},tip, whatthis));
    if (mandatory)
      isMandatory_.insert(idName);
  }

  bool Implements_Complex_Class::isMandatory(const std::string id) const
  {
    return isMandatory_.find(id)!=isMandatory_.end();
  }

  std::size_t Implements_Complex_Class::numMandatoryChilds() const
  {
    return  isMandatory_.size();
  }

  std::string ABC_Base::ClassName()
  {
    return "ABC_Base";
  }

  std::set<std::string> ABC_Base::SuperClasses()
  {
    return {ClassName()};
  }

  std::string ABC_Base::myClass() const
  {
    return ClassName();
  }

  std::set<std::string> ABC_Base::mySuperClasses() const
  {
    return SuperClasses();
  }

  std::ostream &operator<<(std::ostream &os, std::vector<std::string> data)
  {
    for (const auto& s:data)
      {
        os<<s<<"\t";
      }
    return os;
  }

  bool Implements_New_Identifier_Class::isInDomain(const ABC_Value *value) const
  {
    const ABC_Simple_Value<std::string>* o=dynamic_cast<const ABC_Simple_Value<std::string>*>(value);

    if (o!=nullptr)
      {
        return cm_->idToValue(o->value())==nullptr;
      }
    else
      {
        return false;
      }
  }

  bool Implements_New_Identifier_Class::checkValue(const std::__cxx11::string &val, std::__cxx11::string *error_message) const
  {
     if (!isValidId(val))

       {
         *error_message="not a valid id";
         return false;
       }
     else if(cm_->idToValue(val)!=nullptr)
           {
             *error_message="existant id";
         return false;
           }
     else
       return true;
  }

  std::set<std::__cxx11::string> Implements_New_Identifier_Class::alternativeValues(Markov_Console::Markov_CommandManagerVar *cm) const
  {
    auto s=cm->getIdList(identifierType())->idSet();

    std::set<std::string> out;
    if (cm->idToValue(defaultValue())==nullptr)
      out.insert(defaultValue());

    for (std::string e:s)
      {
        std::string id_0=nextId(e);
        while (cm->idToValue(id_0)!=nullptr)
          id_0=nextId(id_0);
        out.insert(id_0);
      }
    return out;

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
