#include "Markov_LA/matrixMath.h"
#include "Markov_LA/matrixIO.h"

#include "Tests/Markov_LA/Markov_LA_Tests.h"
#include "Tests/AssertPlain.h"
#include "Markov_LA/matrixMath.h"



namespace Markov_Test
{

namespace Markov_LA_Test
{
    using namespace Markov_LA;

    template<typename T>
    MultipleTests Markov_LATest<T>::Math_Test() const

    {
	MultipleTests result("MatrixMath.h",
		      "Compare to known result of examples");

	M_Matrix<T> sample(3,3);

	  sample(0,0)=3.4000;  sample(0,1)=6.0000;    sample(0,2)=8.9000;
	  sample(1,0)=-5.0000; sample(1,1)=6.0000;    sample(1,2)=3.9000;
	  sample(2,0)=-2.0000; sample(2,1)=-6.0000;    sample(2,2)=9.5000;

	  M_Matrix<T> expected(3,3);
	  expected(0,0)=3.4000;  expected(0,1)=6.0000;    expected(0,2)=8.9000;
	  expected(1,0)=5.0000; expected(1,1)=6.0000;    expected(1,2)=3.9000;
	  expected(2,0)=2.0000; expected(2,1)=6.0000;    expected(2,2)=9.5000;


	  result.push_back(EqualValue_Test("absolute value of a matrix, abs()",
					   abs(sample),expected));

	  expected(0,0)=-3.4000;  expected(0,1)=-6.0000; expected(0,2)=-8.9000;
	  expected(1,0)=5.0000; expected(1,1)=-6.0000;  expected(1,2)=-3.9000;
	  expected(2,0)=2.0000; expected(2,1)=6.0000;   expected(2,2)=-9.5000;

	  result.push_back(EqualValue_Test("additive inverse operator -()",
					   -sample, expected));


	  expected(0,0)=2.996410004739701e+001;
	  expected(0,1)=4.034287934927351e+002;
	  expected(0,2)=7.331973539155995e+003;

	  expected(1,0)=6.737946999085467e-003;
	  expected(1,1)=4.034287934927351e+002;
	  expected(1,2)=4.940244910553017e+001;

	  expected(2,0)=1.353352832366127e-001;
	  expected(2,1)=2.478752176666359e-003;
	  expected(2,2)=1.335972682966187e+004;

	  result.push_back(
		      EqualValue_Test("exponential of the members"
				      "of the matrix exp()",
				      exp(sample),expected));



	     expected(0,0)=2.511886431509580e+003;
	     expected(0,1)=1.000000000000000e+006 ;
	     expected(0,2)=7.943282347242822e+008;

	     expected(1,0)=9.999999999999999e-006;
	     expected(1,1)=1.000000000000000e+006;
	     expected(1,2)=7.943282347242814e+003;

	     expected(2,0)=1.000000000000000e-002;
	     expected(2,1)=1.000000000000000e-006;
	     expected(2,2)=3.162277660168379e+009;


	     result.push_back(EqualValue_Test("10^x, exp10()",
					      exp10(sample),expected));

	     expected(0,0)= 5.314789170422551e-001;
	     expected(0,1)=7.781512503836436e-001;
	     expected(0,2)=9.493900066449128e-001;

	     expected(1,0)=6.989700043360188e-001 ;
	     expected(1,1)=7.781512503836436e-001;
	     expected(1,2)=5.910646070264991e-001;

	     expected(2,0)=3.010299956639811e-001;
	     expected(2,1)=7.781512503836436e-001;
	     expected(2,2)=9.777236052888478e-001;

	     result.push_back(EqualValue_Test("logarithm base 10, log10()",
					      log10(abs(sample)),expected));
	     return result;
	 }
    template MultipleTests Markov_LATest<double>::Math_Test()const;
}
}
