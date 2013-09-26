#ifndef ABC_PROBABILITY_TEST_H
#define ABC_PROBABILITY_TEST_H
#include "Tests/ABC_Test.h"

namespace Markov_Test
{

class ABC_Probability_Test: public ABC_Test
{
public:
    virtual ABC_Probability_Test* clone()const=0;
    virtual ABC_Probability_Test* create()const=0;
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

    virtual ~ABC_Probability_Test();

    /**
      Number of sub tests of present test
      */
    virtual std::size_t numSubTests() const=0;
    /**
      Number of subtests that have failed
      */
    virtual std::size_t numFailures()const=0;

    /**
      returns a particular subtest
      */
    virtual const ABC_Probability_Test& operator[](std::size_t i)const =0;
    virtual  ABC_Probability_Test& operator[](std::size_t i) =0;

    virtual const ABC_Probability_Test& VerboseLevel(bool verboselevel)const=0;


    virtual void compute();






};

}


#endif // ABC_PROBABILITY_TEST_H
