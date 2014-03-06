#include "Markov_Object/ScaledExpression.h"

namespace Markov_Object {

  std::string ScaledExpression::ClassName()
  {
    return "ScaledExpression";

  }

  std::set<std::string> ScaledExpression::SuperClasses()
  {
    auto out=QuantityExpression::SuperClasses();
    out.insert(ClassName());
    return out;
  }

  Class_info ScaledExpression::classInfo()
  {
    return {ClassName(),
            SuperClasses(),
            true,
            false,
            false};

  }

  Class_info ScaledExpression::myClassInfo() const
  {
    return myClassInfo();
  }

  std::string ScaledExpression::myClass() const
  {
    return ClassName();
  }

  bool ScaledExpression::empty() const
  {
    return QuantityExpression::empty() && (scale_==0);
  }

  bool ScaledExpression::invalid() const
  {
    return QuantityExpression::invalid()||(
          !empty()&&(QuantityExpression::empty()|| (scale_==0)));
  }

  ScaledExpression *ScaledExpression::create() const
  {
    return new ScaledExpression;
  }

  std::string ScaledExpression::ToString() const
  {
    return std::to_string(scale())+mult+QuantityExpression::ToString();
  }

  ScaledExpression *ScaledExpression::CreateObject(const std::string &text, std::size_t &cursor) const
  {
    auto tmp=create();
    auto out=tmp->ToObject(text,cursor);
    if (out==nullptr)
      delete tmp;
    return out;
  }

  double ScaledExpression::scale() const
  {
    return scale_;
  }

  void ScaledExpression::setScale(double newScale)
  {
    scale_=newScale;
  }



  ScaledExpression &ScaledExpression::operator+=(const ScaledExpression &other)
  {
    QuantityExpression::operator +=(other);
    scale_*=other.scale_;
    return *this;
  }

  ScaledExpression &ScaledExpression::operator*=(int n)
  {
    QuantityExpression::operator *=(n);
    scale_=std::pow(scale_,n);
    return *this;
  }

  bool ScaledExpression::operator<(const ScaledExpression &other) const
  {
    if (QuantityExpression::operator <(other))
      return true;
    else if (!other.QuantityExpression::operator<(*this))
      return false;
    else
      return scale()<other.scale();
  }

  ScaledExpression::ScaledExpression(double scale, QuantityExpression def):
    QuantityExpression(def),
    scale_(scale)
  {}

  ScaledExpression::~ScaledExpression(){}

  ScaledExpression::ScaledExpression(const ScaledExpression &other):
    QuantityExpression(other),
    scale_(other.scale_){}

  ScaledExpression *ScaledExpression::ToObject(const std::string &text, std::size_t &cursor)
  {
    std::size_t cursor0=cursor;
    std::size_t n;
    try
    {
      scale_=std::stod(text.substr(cursor),&n);
    }
    catch (...)
    {
      return nullptr;
    }
    cursor+=n;
    auto q=QuantityExpression::ToObject(text,cursor);
    if (q==nullptr)
      {
        cursor=cursor0;
        return nullptr;
      }
    else
      return this;

  }

  ScaledExpression::ScaledExpression():
    QuantityExpression(),
    scale_(0){}

  ScaledExpression operator*(const ScaledExpression &one, int n)
  {
    ScaledExpression out(one);
    return out*=n;
  }

  ScaledExpression operator+(const ScaledExpression &one, const ScaledExpression &other)
  {
    ScaledExpression out(one);
    return out+=other;
  }




















}
