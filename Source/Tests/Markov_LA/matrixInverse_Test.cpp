#include "Markov_LA/matrixIO.h"

#include "Tests/Markov_LA/Markov_LA_Tests.h"
#include "Tests/AssertPlain.h"

#include "Markov_LA/matrixInit.h"
#include "Markov_LA/matrixInverse.h"
#include "Markov_LA/matrixProduct.h"



namespace Markov_Test
{

namespace Markov_LA_Test
{
    using namespace Markov_LA;

    template<typename T>
    MultipleTests Markov_LATest<T>::Inverse_Test() const
    {
	MultipleTests result("matrixInverse.h","test a given example");
	M_Matrix<T> sample(3,3);

	  sample(0,0)=3.4000;  sample(0,1)=6.0000;    sample(0,2)=8.9000;
	  sample(1,0)=-5.0000; sample(1,1)=6.0000;    sample(1,2)=3.9000;
	  sample(2,0)=-2.0000; sample(2,1)=-6.0000;    sample(2,2)=9.5000;

	  M_Matrix<T> expected(3,3);
	  expected(0,0)=9.081051775548929e-002;
	  expected(0,1)=-1.246950393060450e-001;
	  expected(0,2)=-3.388452155055571e-002;

	  expected(1,0)=4.484051685190205e-002;
	  expected(1,1)=5.658715098942803e-002;
	  expected(1,2)=-6.523899882533658e-002;

	  expected(2,0)=4.743833017077800e-002;
	  expected(2,1)=9.487666034155601e-003;
	  expected(2,2)=5.692599620493359e-002;

	  result.push_back(EqualValue_Test("Inverse of a known sample",
					   inv(sample),expected));

	  result.push_back(EqualValue_Test(
			       "Identity test: product by the inverse"
			       " should return identity matrix",
			       sample*inv(sample),eye<T>(3)));
	  return result;


      }
    template MultipleTests Markov_LATest<double>::Inverse_Test()const;
}
}
