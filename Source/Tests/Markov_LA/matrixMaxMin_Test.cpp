#include "Markov_LA/matrixMaxMin.h"
#include "Markov_LA/matrixMath.h"
#include "Markov_LA/matrixIO.h"
#include "Tests/Markov_LA/Markov_LA_Tests.h"
#include "Tests/AssertPlain.h"



namespace Markov_Test
{

namespace Markov_LA_Test
{
    using namespace Markov_LA;
    template<typename T>
    MultipleTests Markov_LATest<T>::MaxMin_Test() const
    {
	MultipleTests result("matrixMaxMin.h",
		      "comparison to known result");
	M_Matrix<T> sample(3,3);

	  sample(0,0)=3.4000;  sample(0,1)=6.0000;    sample(0,2)=8.9000;
	  sample(1,0)=-5.0000; sample(1,1)=6.0000;    sample(1,2)=3.9000;
	  sample(2,0)=-2.0000; sample(2,1)=-6.0000;    sample(2,2)=9.5000;

	result.push_back(EqualValue_Test("maxAbs()",maxAbs(sample),9.5));
	result.push_back(EqualValue_Test("minAbs()",minAbs(sample),2.0));
	result.push_back(EqualValue_Test("max",max(sample),9.5));
	result.push_back(EqualValue_Test("min",min(sample),-6.0));

	result.push_back(EqualValue_Test("norm_inf",norm_inf(sample),18.3));
	 result.push_back(EqualValue_Test("norm",norm(sample),
					  18.254588464273851));
	 return result;

      }

    template MultipleTests Markov_LATest<double>::MaxMin_Test()const;
}
}
