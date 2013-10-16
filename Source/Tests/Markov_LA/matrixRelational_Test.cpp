#include "Markov_LA/matrixRelational.h"
#include "Tests/Markov_LA/Markov_LA_Tests.h"
#include "Tests/AssertPlain.h"
#include "Markov_LA/matrixIO.h"
#include "Markov_LA/matrixMaxMin.h"

#include <limits>


namespace Markov_Test
{

namespace Markov_LA_Test
{
    using namespace Markov_LA;
    template<typename T>
    MultipleTests Markov_LATest<T>::Relational_Test() const    {
	MultipleTests result("matrixRelational.h",
			     "Checks results at the boundaries ");
	M_Matrix<T> sample(3,3);

	sample(0,0)=3.4000;  sample(0,1)=6.0000;    sample(0,2)=8.9000;
	sample(1,0)=-5.0000; sample(1,1)=6.0000;    sample(1,2)=3.9000;
	sample(2,0)=-2.0000; sample(2,1)=-6.0000;    sample(2,2)=9.5000;

	result.push_back(ElementaryTest("operator <=",
					"checks if a matrix<=max(matrix)",
					sample<=9.5));
	result.push_back(ElementaryTest(
			     "operator <",
			     "checks that it is false that matrix<max(matrix)",
			     !(sample<9.5)));
        T eps=std::numeric_limits<T>::epsilon()*norm_inf(sample)*40;
	result.push_back(ElementaryTest(
			     "operator <",
			     "sample<max(sample)+eps",
			     sample<9.5+eps));
	result.push_back(ElementaryTest(
			     "operator ,=",
			     "it is false that sample<=max(sample)-eps",
			     !(sample<=9.5-eps)));

	result.push_back(ElementaryTest(
			     "opeartor >=",
			     "sample>=min(sample)",
			     sample>=-6.0));
	result.push_back(ElementaryTest(
                             "opeartor >",
			     "It is false that sample>min(sample)",
			     !(sample>-6.0)));
	result.push_back(ElementaryTest(
			     "opearor >",
			     "It is true that sample>min(sample)-eps",
			     sample>-6.0-eps));
	result.push_back(ElementaryTest(
			     "operator >=",
			     "it is false that sample>=min(sample)+eps",
			     !(sample>=-6.0+eps)));

	sample=10;

	result.push_back(ElementaryTest(
			     "operator =(T type) and operator ==" ,
			     "It is true that all the values are equal"
			     "to the assigned value",
			     sample==10.0));
	result.push_back(ElementaryTest(
			     "operator ==",
			     "It is false that all the values are equal"
			     "to the assigned value +eps",
			     !(sample==10.0+eps)));

	sample(1,2)=10.0-eps;
	result.push_back(ElementaryTest("operator ==",
					"detects one value that changed by eps",
					!(sample==10.0)));
	result.push_back(ElementaryTest("operator !=",
					"not all the values are different from 10",
					!(sample!=10.0)));
	result.push_back(ElementaryTest("operator !=",
					"not all the values are different from 10-eps",
					!(sample!=10.0-eps)));
	result.push_back(ElementaryTest("operator !=",
					"all the values are different from 10+eps",
					sample!=10.0+eps));
	return result;

    }
    template MultipleTests Markov_LATest<double>::Relational_Test()const;
}
}
