#ifndef TOLERANCECOMPARISON_TEST_H
#define TOLERANCECOMPARISON_TEST_H

#include <limits>
#include "Markov_LA/ToleranceComparison.h"
#include "Tests/MultipleTests.h"
#include "Tests/All_Tests.h"

namespace Markov_Test
{

    namespace Markov_LA_Test
    {


	using namespace Markov_LA;
	class ToleranceComparison_Test:public All_Tests
	{
	public:
	  virtual MultipleTests AllTests(Markov_Console::Markov_CommandManager* cm,
					 const std::string varNameTested);
	 // virtual MultipleTests AllTests()=0;
	  static std::string TestName();

	  virtual std::string myTest()const;

	  virtual std::string testedClass()const;

	    MultipleTests isEqual_Test()const;
	    MultipleTests isLess_Test()const;
	    MultipleTests AllTests() const;
	    virtual ~ToleranceComparison_Test(){}

	};

    }
}
#endif // TOLERANCECOMPARISON_TEST_H
