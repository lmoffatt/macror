
#include <sstream>
#include "Markov_LA/matrixInit.h"
#include "Tests/Markov_LA/Markov_LA_Tests.h"
#include "Markov_LA/matrixIO.h"
#include "Tests/Markov_LA/Markov_LA_Tests.h"


namespace Markov_Test
{

namespace Markov_LA_Test
{
    using namespace Markov_LA;

    /**
      some common matrices builders
      Ones
      Zeros
      eye
      */


    template<typename T>
    MultipleTests Markov_LATest<T>::Init_Test()const
    {
	MultipleTests result("matrixInit.h",
			     "Test an example for each one");
	M_Matrix<T> expected(2,3);
	    expected(0,0)=T(1);  expected(0,1)=T(1);  expected(0,2)=T(1);
	    expected(1,0)=T(1);  expected(1,1)=T(1);  expected(1,2)=T(1);


	    result.push_back(EqualValue_Test("ones based on size",
					     ones<T>(2,3),expected));

	    result.push_back(EqualValue_Test("ones based on copy",
					     ones<T>(2,3),expected));


	    expected(0,0)=T(0);  expected(0,1)=T(0);  expected(0,2)=T(0);
	    expected(1,0)=T(0);  expected(1,1)=T(0);  expected(1,2)=T(0);
	    result.push_back(EqualValue_Test("zeros based on size",
					     zeros<T>(2,3),expected));

	    result.push_back(EqualValue_Test("zeros based on copy",
					     zeros(expected),expected));


	    expected=zeros<T>(3,3);

	    expected(0,0)=T(1);  expected(0,1)=T(0);  expected(0,2)=T(0);
	    expected(1,0)=T(0);  expected(1,1)=T(1);  expected(1,2)=T(0);
	    expected(2,0)=T(0);  expected(2,1)=T(0);  expected(2,2)=T(1);

	    result.push_back(EqualValue_Test("eye based on size",
					     eye<T>(3),expected));

	    return result;

    }

    template MultipleTests  Markov_LATest<double>::Init_Test()const;
}
}
