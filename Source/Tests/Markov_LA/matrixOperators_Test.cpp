#include "Markov_LA/matrixIO.h"

#include "Tests/Markov_LA/Markov_LA_Tests.h"
#include "Tests/AssertPlain.h"
#include "Markov_LA/Matrix.h"
#include "Markov_LA/matrixInit.h"
#include "Markov_LA/matrixOperators.h"



namespace Markov_Test
{

namespace Markov_LA_Test
{
    using namespace Markov_LA;
    template<typename T>
    MultipleTests Markov_LATest<T>::Operators_Test()const
    {
	M_Matrix<T> sample(2,3);
	MultipleTests result("matrixOperators.h",
			     "test case examples");

	  sample(0,0)=3.4;  sample(0,1)=6.0000;    sample(0,2)=8.9000;
	  sample(1,0)=-5; sample(1,1)=6.0000;    sample(1,2)=3.9000;

	  M_Matrix<T> expected(3,2);
	  expected(0,0)=3.4;  expected(0,1)=-5;
	  expected(1,0)=6;  expected(1,1)=6;
	  expected(2,0)=8.9; expected(2,1)=3.9;

	  result.push_back(EqualValue_Test("Transpose()",
					   Transpose(sample),expected));

	  expected=M_Matrix<T>(1,2);
	  expected(0,0)=3.4;  expected(0,1)=6;


	  result.push_back(EqualValue_Test("diag",
					   diag(sample),expected));

	  expected=M_Matrix<T>(2,2);
	  expected(0,0)=3.4;  expected(0,1)=0;
	  expected(1,0)=0;  expected(1,1)=6;

	  result.push_back(EqualValue_Test("diag(diag()",
					   diag(diag(sample)),expected));

	  return result;

      }
    template MultipleTests Markov_LATest<double>::Operators_Test()const;
}
}
