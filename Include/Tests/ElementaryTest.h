#ifndef ELEMENTARYTEST_H
#define ELEMENTARYTEST_H
#include <sstream>

#include "Markov_IO/ABC_Put.h"
#include "Tests/ABC_Test.h"
#include "Markov_LA/Matrix.h"

namespace Markov_Test
{
/**

  */
  class ElementaryTest: public ABC_Test
  {
  public:
      virtual ElementaryTest* clone()const;
      virtual ElementaryTest* create()const;
      virtual std::ostream& put(std::ostream&) const;

      virtual const ElementaryTest& VerboseLevel(bool verboseLevel)const;

      virtual bool result()const;

      virtual std::string functionalityUnderTest()const;
      virtual std::string Rationale()const;

      virtual std::size_t numSubTests() const;
      virtual std::size_t numFailures()const;

      virtual std::size_t numElementayTests() const;
      virtual std::size_t numElementayFailures() const;





      virtual const ABC_Test& operator[](std::size_t i)const;
      virtual ABC_Test& operator[](std::size_t i);


      ElementaryTest(const std::string& functionalityUnderTest,
		 const std::string& Rationale,
		 bool result);
      ElementaryTest();

      ElementaryTest(const ElementaryTest& other);

      ElementaryTest& operator=(const ElementaryTest& other);

      virtual ~ElementaryTest();

      friend void swap(ElementaryTest& one, ElementaryTest& two);


  protected:
      bool result_;
      std::string functionality_;
      std::string rationale_;

  };

  ElementaryTest IsZero_Test(const std::string& functionality,
			  std::size_t count);


  template<class T>
  ElementaryTest UnEqualAddress_Test(const std::string& functionality,T x, T y)
  {
      std::stringstream s;
      s<<&x;
      std::string sxadd=s.str();
      s.str("");
      s<<&y;
      std::string syadd=s.str();


      return ElementaryTest(functionality,sxadd+
			    "\tshould be different from\t"+syadd,
			&x!=&y);
  }
  template<class T>
  ElementaryTest EqualValue_Test(const std::string& functionality,T x, T y)
  {
      std::stringstream s;
      s<<x;
      std::string sx=s.str();
      s.str("");
      s<<y;
      std::string sy=s.str();
      if (sx.find_first_of("\n")!=sx.npos)
	  sx.insert(0,"\n");
      if (sy.find_first_of("\n")!=sy.npos)
	  sy.insert(0,"\n");

      return ElementaryTest(functionality,sx+"  should be equal to  " +sy,x==y);
  }


  template<class T>
  ElementaryTest MinorValue_Test(const std::string& functionality,T x, T y)
  {
      std::stringstream s;
      s<<x;
      std::string sx=s.str();
      s.str("");
      s<<y;
      std::string sy=s.str();
      if (sx.find_first_of("\n")!=sx.npos)
          sx.insert(0,"\n");
      if (sy.find_first_of("\n")!=sy.npos)
          sy.insert(0,"\n");

      return ElementaryTest(functionality,sx+"  should be minor than " +sy,x<y);
  }





  template<class T>
  ElementaryTest UnEqualValue_Test(const std::string& functionality,T x, T y)
  {
      std::stringstream s;
      s<<x;
      std::string sx=s.str();
      s.str("");
      s<<y;
      std::string sy=s.str();
      if (sx.find_first_of("\n")!=sx.npos)
	  sx.insert(0,"\n");
      if (sy.find_first_of("\n")!=sy.npos)
	  sy.insert(0,"\n");

      return ElementaryTest(functionality,sx+"  should be unequal to "+sy,x!=y);
  }






}


#endif // ELEMENTARYTEST_H
