#ifndef BASICALGEBRAPROPERTIES_TEST_H
#define BASICALGEBRAPROPERTIES_TEST_H
#include <vector>
#include "Tests/AssertPlain.h"


namespace Markov_Test
{

template<class T, class BinaryOperator, class Transformation>
class BasicAlgebraProperties_Test
{
public:
    BasicAlgebraProperties_Test(const BinaryOperator& Op,
				const std::vector<T> elements,
				const T& identityElement,
				const Transformation& inverse):
    Op_(Op),
    x_(elements),
    e_(identityElement),
    inv_(inverse)
    {}

    bool HasIdentityElement_Test()
    {
	for (std::size_t i=0; i<x_.size();i++)
	{
	    ASSERT_EQ_M(Op_(x_[i],e_),x_[i],Op_<<"  "<<e_<<"  "<<x[i]);
	    ASSERT_EQ_M(Op_(e_,x_[i]),x_[i],Op_<<"  "<<e_<<"  "<<x[i]);
	}
	return true;
    }

    bool HasInverseTransformation_Test()
    {
	for (std::size_t i=0; i<x_.size();i++)
	{
	    ASSERT_EQ_M(Op_(x[i],inv_(x[i])),e_,Op_<<inv_<<x[i]);
	    ASSERT_EQ_M(Op_(inv_(x[i]),x[i]),e_,Op_<<inv_<<x[i]);
	}
	return true;
    }

    bool IsCommutative_Test()
    {
	for (std::size_t i=0; i<x_.size();i++)
	{
	    for (std::size_t j=0; j<x_.size();j++)
	    {
		ASSERT_EQ_M(Op_(x[i],x[j]),Op_(x[j],x[i]),
			    Op_<<"  "<<x[i]<<"  "<<x[j]);
	    }
	}
	return true;
    }

    bool IsAssociative_Test()
    {
	for (std::size_t i=0; i<x_.size();i++)
	{
	    for (std::size_t j=0; j<x_.size();j++)
	    {
		for (std::size_t k=0; k<x_.size();k++)
		{
		    ASSERT_EQ_M(Op_(Op_(x_[i],x_[j]),x_[k]),
			      Op_(x[i],Op_(x[j],x[k])),
			      Op_<<"  "<<x[i]<<"  "<<x[j]<<"  "<<x[k]);
		}
	    }
	}
	return true;
    }

    bool IsMultiplicativeSemigroup_Test(){
	if(!this->HasIdentityElement_Test())
	    return false;
	if(!this->HasInverseTransformation_Test())
	    return false;
	if(!this->IsAssociative_Test())
	    return false;
	if(!this->IsCommutative_Test())
	    return false;
	return true;
    }
private:
    BinaryOperator Op_;
    T e_;
    Transformation inv_;
};


};
#endif // BASICALGEBRAPROPERTIES_TEST_H
