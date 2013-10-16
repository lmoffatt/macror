#include "Markov_LA/matrixIO.h"
#include "Tests/Markov_LA/Markov_LA_Tests.h"
#include "Tests/Markov_LA/Markov_LA_Tests.h"
#include "Tests/AssertPlain.h"

#include <sstream>


namespace Markov_Test
{

namespace Markov_LA_Test
{
    using namespace Markov_LA;

    /**
      Input and Output to streams Operators tests.

      The elements of the matrix have to be separated by spaces,
      the rows by new lines.

      It checks the Insert Operator comparing it to a gold string.
      It checks the Extract Operator using the same string and comparing it
      to the original Matrix.
      */


    template<typename T>
     MultipleTests Markov_LATest<T>::IO_Test() const
    {
	/**
	  Test the Matrix Insert Operator
	*/
	MultipleTests result("matrixIO.h",
		      "we should be able to recover exactly what we insert");

	//No particular meaning just any matrix
	// it includes integers, zero and negative values
	M_Matrix<T> sample(2,3);
	if (std::numeric_limits<T>::is_signed)
	{
	    sample(0,0)=T(0.1);
	    sample(0,1)=T(4.576587643);
	    sample(0,2)=T(-2);
	    sample(1,0)=T(-3.47667301);
	    sample(1,1)=T(0);
	    sample(1,2)=T(6.9783275928e45);
	}
	else
	{
	    sample(0,0)=T(0.1);
	    sample(0,1)=T(4.576587643);
	    sample(0,2)=T(2);
	    sample(1,0)=T(3.47667301);
	    sample(1,1)=T(0);
	    sample(1,2)=T(6.9783275928e45);
	}
	std::stringstream ss;
	ss.precision(std::numeric_limits<T>::digits10);
	ss<<sample;
	M_Matrix<T> read;
	ss>>read;

	result.push_back(EqualValue_Test("Original matrix recovered unaltered",
					 sample,read));
	return result;
    }

   template MultipleTests Markov_LATest<double>::IO_Test()const;
   template MultipleTests Markov_LATest<std::size_t>::IO_Test()const;

}
}

