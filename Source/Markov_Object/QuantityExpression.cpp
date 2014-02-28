#include "Markov_Object/QuantityExpression.h"
#include "Markov_Object/Quantity.h"



namespace Markov_Object {
  std::string QuantityExpression::legal(){
    return std::string(allowed)+mult+pow+numeric+div;
  }

  std::map<std::string, int> QuantityExpression::getDefinition(const std::string &defs)
  {
    std::size_t n=0;
    return getDefinition(defs,n);
  }

  std::string QuantityExpression::getName(const std::string text,std::size_t& cursor)
  {
    Abstract_Named_Object::skipSpaces(text,cursor);


    auto start=text.find_first_of(allowed,cursor);
    cursor=text.find_first_not_of(allowed,start);

    std::string current=text.substr(start,cursor-start);
    return current;
  }
  std::string QuantityExpression::getName(const std::string text)
  {
    std::size_t n=0; return getName(text,n);
  }


  std::map<std::string, int> QuantityExpression::getDefinition(const std::string &defs, std::size_t &cursor)
  {
    std::size_t cursor0=cursor;

    std::map<std::string,int> out;
    Abstract_Named_Object::skipSpaces(defs,cursor);

    auto final=defs.find_first_of(separator,cursor);

    std::string candidate=defs.substr(cursor,final-cursor);
    auto nfin=candidate.find_first_not_of(legal());

    bool validformat=!candidate.empty()&&(nfin==candidate.npos);
    std::size_t pos=0;
    if(validformat)
      {
        while (pos<=candidate.size())
          {

            std::string current=getName(candidate,pos);
            if (current.empty())
              break;

            char op;
            if (pos==candidate.npos)
              op=0;
            else
              op=candidate[pos];
            int exponent=1;
            if (op==pow)
              {
                ++pos;
                std::size_t npos=0;
                if (pos>=candidate.size())
                  {
                    validformat=false;
                    break;
                  }
                try
                {
                  exponent=std::stoi(candidate.substr(pos),&npos);
                }
                catch (std::exception& e)
                {
                  validformat=false;
                  break;
                }
                pos+=npos;
                while (pos<candidate.size()-1&&candidate[pos]==' ')
                  ++pos;
                op=candidate[pos];
              }
            if ((op==mult)||
                (op==div)||
                (op==0)||
                (std::string(separator).find(op)!=std::string::npos))
              {
                if (out.find(current)!=out.end())
                  {
                    if (op==div)
                    out[current]-=exponent;
                    else
                      out[current]+=exponent;

                  }
                else
                  {
                    out[current]=exponent;
                  }
                if ((op!=mult)&&(op!=div))
                  break;
              }
            else
              {
                validformat=false;
                break;
              }
          }
      }

    if (validformat)
      {
        cursor=final;
        return out;
      }
    else
      {
        cursor=cursor0;
        return std::map<std::string,int>();
      }
  }


  QuantityExpression &QuantityExpression::operator+=(const QuantityExpression &other)
  {
    for (auto t:other.expr_)
      {
        if (expr_.find(t.first)!=expr_.end())
          expr_[t.first]+=t.second;
        else
          expr_[t.first]=t.second;
      }
    return *this;
  }

  QuantityExpression &QuantityExpression::operator*=(int n)
  {
    for (auto t:expr_)
      {
        expr_[t.first]*=n;
      }
    return *this;
  }

  QuantityExpression QuantityExpression::dimensionless()
  {
    return QuantityExpression();
  }



  bool QuantityExpression::operator<(const QuantityExpression &other)
  {
    auto it=expr_.begin();
    auto itOther=other.expr_.begin();
    while ((it->first==itOther->first)&&(it!=expr_.end())&&(itOther!=other.expr_.end()))
      {
        ++it; ++itOther;
      }
    return it->first<itOther->first;
  }


  bool QuantityExpression::invalid() const
  {
    for (auto t:expr_)
      {
        if ((t.first.empty())|| (t.first!=getName(t.first)))
          return true;
      }
   return false;

  }


  QuantityExpression *QuantityExpression::create() const
  {
    return new QuantityExpression;
  }

  const QuantityExpression *QuantityExpression::dynamicCast(const Abstract_Object*o) const
  {
    return dynamic_cast<const QuantityExpression*>(o);
  }

  std::string QuantityExpression::ToString() const
  {
    std::string o;
    auto m=expr_.begin();
    while ((m!=expr_.end())&&(m->second==0)) ++m;
    auto m0=m;
    for (m;m!=expr_.end();++m)
      {
        if (m->second!=0)
          {
            if (m!=m0)
              o+=mult;
            o+=m->first;
            if (m->second!=1)
              {
                o+=pow+std::to_string(m->second);
              }
          }

      }
    return o;
  }


  QuantityExpression::QuantityExpression():
    Abstract_Object(),
    expr_(){}

  std::map<std::string, int> QuantityExpression::value() const
  {
    return expr_;
  }



  QuantityExpression::QuantityExpression(std::map<std::string, int> expression):
    Abstract_Object(),
    expr_(expression){}

  bool QuantityExpression::ToObject(const std::string &text, std::size_t &cursor)
  {
    auto def=getDefinition(text,cursor);
    if (def.find("")!=def.end())
      return false;
    expr_=def;
    return true;
  }

  QuantityExpression *QuantityExpression::dynamicCast(Abstract_Object*o) const
  {
    return dynamic_cast<QuantityExpression*>(o);
  }

  bool QuantityExpression::empty() const
  {
    return expr_.empty();
  }


  std::string QuantityExpression::myClass() const
  {
    return ClassName();
  }

  Class_info QuantityExpression::myClassInfo() const
  {
    return classInfo();
  }

  std::set<std::string> QuantityExpression::SuperClasses()
  {
    auto out=Abstract_Object::SuperClasses();
    out.insert(ClassName());
    return out;
  }

  Class_info QuantityExpression::classInfo()
  {
    return {ClassName(),
            SuperClasses(),
            true,
            false,
            false};

  }

  std::string QuantityExpression::ClassName()
  {
    return "QuantityExpression";
  }

  QuantityExpression operator*(const QuantityExpression &one, int n)
  {
    QuantityExpression out(one);
    return out*=n;
  }

  QuantityExpression operator+(const QuantityExpression &one, const QuantityExpression &other)
  {
    QuantityExpression out(one);
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

    MultipleTests isAbelian(const std::set<const QuantityExpression*>& qs)
    {

      MultipleTests o("Test if it is an Abelian group",
                      "true for all the properties");

      MultipleTests closure("test for Closure",
                            "For all a, b in A, the result of the operation a • b is also in A");
      //Closure
      for (const QuantityExpression* q:qs)
        {
          for (const QuantityExpression* q2:qs)
            {
              closure.push_back(TEST_EQ_xi_xj(q->ToString(),
                                              q2->ToString(),
                                              (*q+*q2).invalid(),
                                              q->invalid()&&q2->invalid()));
            }
        }

      o.push_back(closure);


      MultipleTests associativity("Associativity",
                                  "For all a, b and c in A, the equation (a • b) • c = a • (b • c) holds.");

      //Associativity
      for (const QuantityExpression* q:qs)
        {
          for (const QuantityExpression* q2:qs)
            {
              for (const QuantityExpression* q3:qs)
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

      for (const QuantityExpression* q:qs)
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
                            "that a • b = b • a = e, where e is the identity element.");

      for (const QuantityExpression* q:qs)
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
                                  "For all a, b in A, a • b = b • a.");
      for (const QuantityExpression* q:qs)
        {
          for (const QuantityExpression* q1:qs)
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




    MultipleTests QuantityExpression_Test::classInvariant() const
    {
      MultipleTests M("Quantity Expression Tests",
                      "interface invariants");

      M.push_back(Abstract_Object_Test::classInvariant());
      M.push_back(isAbelian(qe_));

      return M;

    }


    QuantityExpression_Test::QuantityExpression_Test
    (const std::set<const QuantityExpression *> &object):
      Abstract_Object_Test({object.begin(),object.end()}),
      qe_(object){}







  }
}

#endif //MACRO_TEST
