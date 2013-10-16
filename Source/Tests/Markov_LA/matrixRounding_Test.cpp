#include "Markov_LA/matrixRounding.h"
#include "Markov_LA/matrixMath.h"
#include "Markov_LA/matrixIO.h"

#include "Tests/Markov_LA/Markov_LA_Tests.h"
#include "Tests/AssertPlain.h"
#include "Markov_LA/matrixMath.h"
#include "Markov_LA/auxiliarMath.h"


namespace Markov_Test
{

namespace Markov_LA_Test
{
    using namespace Markov_LA;

    template<typename T>
    MultipleTests Markov_LATest<T>::Rounding_Test() const
    {
	MultipleTests result("matrixRounding.h",
		      "test each function by an example");
	double eps=std::numeric_limits<T>::epsilon();
	M_Matrix<T> sample(3,3);

	  sample(0,0)=3.4000;  sample(0,1)=6.0000;    sample(0,2)=8.9000;
	  sample(1,0)=-5.0000; sample(1,1)=10*eps;    sample(1,2)=3.9000;
	  sample(2,0)=-2.0000; sample(2,1)=-6.0000;    sample(2,2)=9.5000;

	  M_Matrix<T> Z(2,3);
	  Z(0,0)=0;	    Z(0,1)=eps;	    Z(0,2)=0;
	  Z(1,0)=0;	    Z(1,1)=0;	    Z(1,2)=0;


	  round_to_zero(sample);
	  result.push_back(ElementaryTest("round to zero (matrix)",
					  "test if rounds eps to zero",
					  sample(1,1)==0));

	  result.push_back(ElementaryTest("isfinite(matrix)",
					  "checks for a finite value",
					  isfinite(sample)));

	  sample(1,1)=NaN();
	  result.push_back(ElementaryTest("isfinite(matrix)",
					  "checks it is false for one NaN value"
					  "in the matrix",
					  !(isfinite(sample))));
	  sample(1,1)=infinity();
	  result.push_back(ElementaryTest("isfinite(matrix)",
					  "one element of the matrix is infinite",
					  !(isfinite(sample))));
	  sample(1,1)=9;
	  result.push_back(ElementaryTest("isfinite(matrix)",
					  "the element is now finite",
					  (isfinite(sample))));
	  if (!std::numeric_limits<T>::is_integer)
	  {
	      sample(1,1)=1.0/0.0;
	      result.push_back(ElementaryTest("isfinite(matrix)",
					      "one element is 1./0.0",
					      !(isfinite(sample))));
	      sample(1,1)=-1.0/0.0;
	      result.push_back(ElementaryTest("isfinite(matrix)",
					      "one element is -1.0/0.0",
					      !(isfinite(sample))));
	      sample(1,1)=0.0/0.0;
	      result.push_back(ElementaryTest("isfinite(matrix)",
					      "one element is 0/0",
					      !(isfinite(sample))));
	    }
    return result;

      }
    template MultipleTests Markov_LATest<double>::Rounding_Test()const;

}
}
