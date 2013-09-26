#include "Markov_LA/matrixExp.h"
#include "Markov_LA/matrixIO.h"

#include "Tests/Markov_LA/Markov_LA_Tests.h"
#include "Tests/AssertPlain.h"


namespace Markov_Test
{

namespace Markov_LA_Test
{
    using namespace Markov_LA;

    template<typename T>
    MultipleTests Markov_LA_Test<T>::Expm_Test()
    {
	MultipleTests result("matrixExp.h",
		       "comparison with an known example");
	M_Matrix<T> sample(3,3);

	  sample(0,0)=3.4000;  sample(0,1)=6.0000;    sample(0,2)=8.9000;
	  sample(1,0)=-5.0000; sample(1,1)=6.0000;    sample(1,2)=3.9000;
	  sample(2,0)=-2.0000; sample(2,1)=-6.0000;    sample(2,2)=9.5000;


	  M_Matrix<T> expected(3,3);
	  expected(0,0)=3869.02108695026;
	  expected(0,1)=-8533.83552544082;
	  expected(0,2)=9271.30977183703;

	  expected(1,0)=-1463.00865856083;
	  expected(1,1)=3046.69301830354;
	  expected(1,2)=-3251.70560237156;

	  expected(2,0)=3697.14719493202;
	  expected(2,1)=-8188.97332418967;
	  expected(2,2)=8676.12947719926;

	  M_Matrix<T> d=expm(sample);
	  result.push_back(EqualValue_Test("expm(sample)==expected",
			       expm(sample),expected));
	  return result;
   }

    template MultipleTests Markov_LA_Test<double>::Expm_Test();
}

}


