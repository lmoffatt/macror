#ifndef BIOPERATORPROPERTIES_TEST_H
#define BIOPERATORPROPERTIES_TEST_H
#include <vector>
#include "Tests/AssertPlain.h"

namespace Markov_Test
{


template<class T,
	class SumOperator,
	class MultiplicationOperator>
class RingProperties_Test
{
public:
    BasicAlgebraProperties_Test(const SumOperator& sum,
				const MultiplicationOperator& mult,
				const T& zeroElement,
				const T& oneElement,
				const std::vector<T> elements):
    sum_(sum),
    mult_(mult),
    zero_(zeroElement),
    one_(oneElement),
    x_(elements)
    {}

    bool hasAnnihilationProperty_Test()
    {
	for (std::size_t i=0; i<x_.size();++i)
	{
	    ASSERT_EQ_M(mult_(x_[i],zero_),zero_,
			mult_<<"  "<<zero_<<"  "<<x[i]);
	    ASSERT_EQ_M(mult_(zero_,x_[i]),zero_,
			mult_<<"  "<<zero_<<"  "<<x[i]);
}
	return true;
    }
    bool IsDistributive_Test()
    {
	for (std::size_t i=0; i<x_.size();++i)
	{
	    for (std::size_t j=0; j<x_.size();++j)
	    {
		for (std::size_t k=0; k<x_.size();++k)
		{
		    ASSERT_EQ_M(mult_(x_[i],sum_(x_[j],x_[k])),
				sum_(mult_(x_[i],x_[j]),mult_(x_[i],x_[k])),
				sum_<<"  "<<mult_<<"  "<<
				x[i]<<"  "<<x[j]<<"  "<<x[k]);

		    ASSERT_EQ_M(mult_(sum_(x_[j],x_[k]),x_[i]),
				sum_(mult_(x_[j],x_[i]),mult_(x_[k],x_[i])),
				sum_<<"  "<<mult_<<"  "<<
				x[i]<<"  "<<x[j]<<"  "<<x[k]);
		}
	    }
	}
	return true;
    }


private:
    SumOperator sum_;
    MultiplicationOperator mult_;
    T& zero_;
    T& one_;
};


}
#endif // BIOPERATORPROPERTIES_TEST_H
