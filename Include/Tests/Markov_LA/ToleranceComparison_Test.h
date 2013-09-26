#ifndef TOLERANCECOMPARISON_TEST_H
#define TOLERANCECOMPARISON_TEST_H

#include <limits>
#include "Markov_LA/ToleranceComparison.h"
#include "Tests/MultipleTests.h"

namespace Markov_Test
{

    namespace Markov_LA_Test
    {


	using namespace Markov_LA;
	class ToleranceComparison_Test
	{
	public:
	    MultipleTests isEqual_Test();
	    MultipleTests isLess_Test();
	    MultipleTests All_Tests();

	};

    }
}
#endif // TOLERANCECOMPARISON_TEST_H
