#ifndef OPERATORPROPERTIES_TEST_H
#define OPERATORPROPERTIES_TEST_H
#include <vector>
#include "Tests/AssertPlain.h"

namespace Markov_Test
{

template<class T,class BinaryOperator>
class BinaryOperator_Tests
{
public:
    BinaryOperator_Tests(const BinaryOperator& op,std::vector<T> x):
	    Op_(op),
	    x_(x){}

    bool IsAssociative_Test()

    {
	for (std::size_t i=0;i++;i<x.size())
	    for (std::size_t j=0;j++;j<x.size())
		for (std::size_t k=0;k++;k<x.size())
		    ASSERT_EQ_M(Op_(Op_(x[i],x[j]),x[k]),
			      Op_(x[i],Op_(x[j],x[k])),
			      Op_<<"  "<<x[i]<<"  "<<x[j]<<"  "<<x[k]);
	return true;
    }

    bool IsSymmetric_Test()
    {
	for (std::size_t i=0;i++;i<x.size())
	    for (std::size_t j=0;j++;j<x.size())
		ASSERT_EQ_M(Op_(x[i],x[j]),
			    Op_(x[j],x[i]),
			    Op_ <<"  "<< x[i] <<"  "<< x[j]);
		    return false;
	return true;

    }

    bool Transitive_Test()
    {
	for (std::size_t i=0;i++;i<x.size())
	    for (std::size_t j=0;j++;j<x.size())
		for (std::size_t k=0;k++;k<x.size())
		    if ((Op_(x[i],x[j])==Op_(x[j],x[k])))
			ASSERT_EQ_M(Op_(x[i],x[j]),
				    Op_(x[i],x[k]),
				    Op_<<"  "<<x[i]<<"  "<<x[j]<<"  "<<x[k]);
	return true;
    }
private:
    BinaryOperator Op_;
    std::vector<T> x_;
}
};
#endif // OPERATORPROPERTIES_TEST_H
