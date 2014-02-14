#include "Tests/ElementaryTest.h"
#include "Markov_IO/auxiliarIO.h"

namespace Markov_Test
{
  ElementaryTest* ElementaryTest::clone()const
  {
    return new ElementaryTest(*this);
  }
  ElementaryTest* ElementaryTest::create()const
  {
    return new ElementaryTest();
  }
  std::ostream& ElementaryTest::put(std::ostream& s) const
  {
    s<<"-----    \n";
    s<<"Functionality under test:  \t"<<functionalityUnderTest()<<"\n";
    s<<"Test rationale:            \t "<<Rationale()<<"\n";
    s<<"Result:                    \t";
    if (result())
      s<<"Passed. \n";
    else
      {
        s<<"Failed. \n";
      }


    return s;
  }


  bool ElementaryTest::result()const
  {
    return result_;
  }

  std::string ElementaryTest::functionalityUnderTest()const
  {
    return functionality_;
  }
  std::string ElementaryTest::Rationale()const
  {
    if (rationale_.size()<40)
      return rationale_;
    else
      {
        std::string s;
        auto n=rationale_.find("==");
        auto n0=rationale_.find("[",0);
        auto n2=rationale_.find("[",n);
        auto d=rationale_.find("\n",n);

        if (d!=rationale_.npos)
          {
            s+="\n        "+rationale_.substr(0,n0)+"\n";
            s+=rationale_.substr(n0,n-n0);

            s+="\n        "+rationale_.substr(n,n2-n)+"\n";
            s+=rationale_.substr(n2)+"\n";
          }
        else
          {
            s+="\n        "+rationale_.substr(0,n+2)+"\n";
            s+="        "+rationale_.substr(n+2)+"\n";
          }
        return s;
      }
  }
  const ElementaryTest& ElementaryTest::VerboseLevel(bool verboseLevel) const
  {
    return *this;
  }

  ElementaryTest::ElementaryTest(const std::string& Name,
                                 const std::string& Expected,
                                 bool Result):
    result_(Result),
    functionality_(Name),
    rationale_(Expected){}


  ElementaryTest::ElementaryTest():
    result_(false),
    functionality_(),
    rationale_(){}


  ElementaryTest::ElementaryTest(const ElementaryTest& other):
    result_(other.result_),
    functionality_(other.functionality_),
    rationale_(other.rationale_){}


  ElementaryTest& ElementaryTest::operator=(const ElementaryTest& other)
  {
    if (this!=&other)
      {
        ElementaryTest tmp(other);
        swap(tmp,*this);

      }
    return *this;
  }

  ElementaryTest::~ElementaryTest(){}

  void swap(ElementaryTest& one, ElementaryTest& two)
  {
    std::swap(one.functionality_,two.functionality_);
    std::swap(one.rationale_,two.rationale_);
    std::swap(one.result_,two.result_);
  }

  std::size_t ElementaryTest::numSubTests() const
  {
    return 1;
  }
  std::size_t ElementaryTest::numFailures()const
  {
    if (result())
      return 0;
    else
      return 1;
  }

  const ABC_Test& ElementaryTest::operator[](std::size_t i)const
  {

    return *this;
  }

  ABC_Test& ElementaryTest::operator[](std::size_t i)
  {

    return *this;
  }



  ElementaryTest IsZero_Test(const std::string& functionality,
                             std::size_t count)
  {
    ElementaryTest result(functionality,
                          Markov_IO::ToString(count)+" should be zero",
                          count==0);
    return result;

  }


  std::size_t ElementaryTest::numElementayTests() const
  {
    return 1;
  }

  std::size_t ElementaryTest::numElementayFailures() const
  {
    if (result_)
      return 0;
    else
      return 1;
  }


}



