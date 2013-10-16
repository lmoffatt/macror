#ifndef ABC_TEST_H
#define ABC_TEST_H
#include "Markov_IO/ABC_Put.h"

namespace Markov_Test
{





  class ABC_Test: public Markov_IO::ABC_Put
  {
  public:
      virtual ABC_Test* clone()const=0;
      virtual ABC_Test* create()const=0;
      virtual std::ostream& put(std::ostream&) const=0;


      virtual bool result()const=0;

      /**
       Name of the functionality (i.e, class or method or postcondition)
       under test
      */
      virtual std::string functionalityUnderTest()const=0;

      /**
	Rationale of the test.
	*/
      virtual std::string Rationale()const=0;





      virtual ~ABC_Test();

      /**
	Number of sub tests of present test
	*/
      virtual std::size_t numSubTests() const=0;

      /**
        Number of elementary tests of present test
        */
      virtual std::size_t numElementayTests() const=0;




      /**
	Number of subtests that have failed
	*/
      virtual std::size_t numFailures()const=0;


      /**
        Number of elementary tests that have failed
        */
      virtual std::size_t numElementayFailures() const=0;



      /**
	returns a particular subtest
	*/
      virtual const ABC_Test& operator[](std::size_t i)const =0;
      virtual  ABC_Test& operator[](std::size_t i) =0;

      virtual const ABC_Test& VerboseLevel(bool verboselevel)const=0;

  };
}



#endif // ABC_TEST_H
