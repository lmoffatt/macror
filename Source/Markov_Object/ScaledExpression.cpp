#include "Markov_Object/ScaledExpression.h"
#include "Markov_Object/Measurement_Unit.h"
#include "Markov_Object/Environment.h"
#include "Markov_IO/auxiliarIO.h"

namespace Markov_Object {

  std::string ScaledExpression::ClassName()
  {
    return "ScaledExpression";

  }

  std::set<std::string> ScaledExpression::SuperClasses()
  {
    auto out=Abstract_Object::SuperClasses();
    out.insert(ClassName());
    return out;
  }


  ScaledExpression ScaledExpression::dimensionless()
  {
    return ScaledExpression{1.0,ex_.dimensionless()};
  }

  std::set<std::string> ScaledExpression::mySuperClasses() const
  {
    return SuperClasses();
  }

  std::string ScaledExpression::myClass() const
  {
    return ClassName();
  }

  bool ScaledExpression::empty() const
  {
    return ex_.empty() && (scale_==0);
  }

  bool ScaledExpression::isValid() const
  {
    return scale()>0;
  }

  ScaledExpression *ScaledExpression::create() const
  {
    return new ScaledExpression;
  }

  std::string ScaledExpression::ToString() const
  {
    if (!empty())
    return Markov_IO::ToString(scale())+QuantityExpression::mult+ex_.ToString();
    else
      return "";
  }

  std::set<std::string> ScaledExpression::referencedObjects() const
  {
    return {};
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
    ex_+=(other.ex_);
    scale_*=other.scale_;
    return *this;
  }

  ScaledExpression &ScaledExpression::operator*=(int n)
  {
    ex_ *=(n);
    scale_=std::pow(scale_,n);
    return *this;
  }

  bool ScaledExpression::operator<(const ScaledExpression &other) const
  {
    if (ex_<other.ex_)
      return true;
    else if (other.ex_<ex_)
      return false;
    else
      return scale()<other.scale();
  }

  std::map<std::string, int> ScaledExpression::value() const
  {
    return ex_.value();
  }

  ScaledExpression::ScaledExpression(Environment *E):
    Abstract_Object(E),
    scale_(0),
    ex_(E){}

  ScaledExpression::ScaledExpression(double scale, QuantityExpression def):
    Abstract_Object(def.getEnvironment()),
    ex_(def),
    scale_(scale)
  {}

  ScaledExpression::ScaledExpression(Environment *E, double scale, std::string def)
    :
      Abstract_Object(E),
      ex_(E,def),
      scale_(scale)
  {

  }


  ScaledExpression::~ScaledExpression(){}

  ScaledExpression::ScaledExpression(const ScaledExpression &other):
    Abstract_Object(other),
    ex_(other.ex_),
    scale_(other.scale_){}

  ScaledExpression ScaledExpression::baseDefinition()const
  {
    ScaledExpression out(const_cast<Environment*>(getEnvironment()));
    int n0=0,n=0;

    if (getEnvironment()!=nullptr)
      {
        for (auto t:value())
          {
            std::shared_ptr<const Measurement_Unit> mu=getEnvironment()->U(t.first);
            if (mu==nullptr)
              {
                n=0;
                if (!t.first.empty())
                  n=Measurement_Unit::abbrToN(t.first[0]);
                if (n!=0)
                  mu=getEnvironment()->U(t.first.substr(1));
              }
            if (mu==nullptr)
              return ScaledExpression();
            else
              {
                ScaledExpression defq=mu->baseDefinition()*t.second;
                out+=defq;
                n0+=n*t.second;
              }

          }
      }
    double sc=scale()*std::pow(10.0,n0);
    out.setScale(sc);
    return out;
  }

  QuantityExpression ScaledExpression::QuantityDefinition() const
  {
    QuantityExpression out(const_cast<Environment*>(getEnvironment()));
    for (auto t:ex_.value())
      {
        auto mu=getEnvironment()->U(t.first);
        if (mu==nullptr)
          {
            int n=0;
            if (!t.first.empty())
              n=Measurement_Unit::abbrToN(t.first[0]);
            if (n!=0)
              mu=getEnvironment()->U(t.first.substr(1));
          }
        if (mu!=nullptr)
          {
            out+=(mu->getQuantityDefinition())*t.second;
          }

        else
          return {};
      }
    return out;
  }

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
    auto q=ex_.CreateObject(text,cursor);
    if (q==nullptr)
      {
        cursor=cursor0;
        return nullptr;
      }
    else
      {
        ex_=*q;
        delete q;
        return this;
      }

  }

  ScaledExpression::ScaledExpression():
    Abstract_Object(),
    ex_(),
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


#ifdef MACRO_TEST


#include "Tests/MultipleTests.h"
#include "Tests/TESTS.h"
#include "Tests/ElementaryTest.h"

namespace Markov_Test
{
  namespace Markov_Object_Test
  {

    MultipleTests isAbelian(const std::set<std::shared_ptr<ScaledExpression>>& qs)
    {

      MultipleTests o("Test if it is an Abelian group",
                      "true for all the properties");

      MultipleTests closure("test for Closure",
                            "For all a, b in A, the result of the operation a • b is also in A",
      {"ScaledExpression"},
      {"ScaledExpression::invalid()",
       "operator+(ScaledExpression&,ScaledExpression&)"});
      //Closure
      for (auto q:qs)
        {
          for (auto q2:qs)
            {
              closure.push_back(TEST_EQ_xi_xj(q->ToString(),
                                              q2->ToString(),
                                              (*q+*q2).invalid(),
                                              q->invalid()&&q2->invalid()));
            }
        }

      o.push_back(closure);


      MultipleTests associativity("Associativity",
                                  "For all a, b and c in A, the equation (a • b) • c = a • (b • c) holds.",
      {"ScaledExpression"},
      {"operator+(ScaledExpression&,ScaledExpression&)"});


      //Associativity
      for (auto q:qs)
        {
          for (auto q2:qs)
            {
              for (auto q3:qs)
                {
                  associativity.push_back(TEST_EQ_xi_xj_xk(q->ToString(),
                                                           q2->ToString(),
                                                           q3->ToString(),
                                                           ((*q+*q2)+*q3).ToString(),(*q+(*q2+*q3)).ToString()));
                }
            }
        }

      o.push_back(associativity);
      MultipleTests identity("Identity element",
                             "There exists an element e in A, such that for all elements a in A, the equation e • a = a • e = a holds.");

      for (auto q:qs)
        {
          identity.push_back(TEST_EQ_xi(q->ToString(),
                                        (*q).ToString(),
                                        (*q+q->dimensionless()).ToString())
                             );
          identity.push_back(TEST_EQ_xi(q->ToString(),
                                        (*q).ToString(),
                                        (q->dimensionless()+*q).ToString())
                             );
        }
      o.push_back(identity);


      MultipleTests Inverse("Inverse element",
                            "For each a in A, there exists an element b in A such"
                            "that a • b = b • a = e, where e is the identity element.",
      {"ScaledExpression"},
      {"ScaledExpression::dimensionless()",
       "ScaledExpression::operator *=(int)",
       "operator+(ScaledExpression&,ScaledExpression&)"});

      for (auto q:qs)
        {
          Inverse.push_back(TEST_EQ_xi(q->ToString(),
                                       (*q+*q*-1).ToString(),
                                       (q->dimensionless()).ToString()));

          Inverse.push_back(TEST_EQ_xi(q->ToString(),
                                       (*q*(-1)+*q).ToString(),
                                       (q->dimensionless()).ToString()));
        }
      o.push_back(Inverse);


      MultipleTests Commutativity("Commutativity",
                                  "For all a, b in A, a • b = b • a.",
      {"ScaledExpression"},
      {"operator+(ScaledExpression&,ScaledExpression&)"});

      for (auto q:qs)
        {
          for (auto q1:qs)
            {
              Commutativity.push_back(TEST_EQ_xi_xj(q->ToString(),
                                                    q1->ToString(),
                                                    (*q+*q1).ToString(),
                                                    (*q1+*q).ToString()));
            }
        }

      o.push_back(Commutativity);


      return o;

    }




    MultipleTests ScaledExpression_Test::classInvariant() const
    {
      MultipleTests M("Quantity Expression Tests",
                      "interface invariants");

      M.push_back(QuantityExpression_Test::classInvariant());
      M.push_back(isAbelian(se_));

      return M;

    }

    std::set<std::shared_ptr<QuantityExpression> >getset(
        const std::set<std::shared_ptr<ScaledExpression> > &object)
    {
      std::set<std::shared_ptr<QuantityExpression> > out;
      for (std::shared_ptr<ScaledExpression> t:object)
        {
          out.insert(std::make_shared<QuantityExpression>(t->getEnvironment(),t->value()));
        }
      return out;

    }


    ScaledExpression_Test::ScaledExpression_Test
    (const std::set<std::shared_ptr<ScaledExpression> > &object):
      QuantityExpression_Test(getset(object)),
      se_(object){}

  }
}

#endif //MACRO_TEST

