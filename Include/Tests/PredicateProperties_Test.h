#ifndef PREDICATEPROPERTIES_TEST_H
#define PREDICATEPROPERTIES_TEST_H
#include <vector>
#include "Tests/AssertPlain.h"

namespace Markov_Test
{


template<class T,class BinaryPredicate>
class BinaryPredicate_Tests
{
public:
    BinaryPredicate_Tests(const BinaryPredicate_Tests<T,BinaryPredicate>& other):
	    Op_(other.Op_),
	    x_(other.x_){}

    BinaryPredicate_Tests():
	    Op_(),
	    x_(){}

    BinaryPredicate_Tests& operator=(const BinaryPredicate_Tests& other)
				    {
	Op_=other.Op_;
	x_=other.x_;
	return *this;
    }

    BinaryPredicate_Tests(const BinaryPredicate& op, std::vector<T> elements):
	    Op_(op),
	    x_(elements){}

    bool IsAssociative_Test()
    {
	for (std::size_t i=0; i<x_.size();i++)
	{
	    for (std::size_t j=0; j<x_.size();j++)
	    {
		for (std::size_t k=0; k<x_.size();k++)
		{
		    ASSERT_EQ_M(Op_(Op_(x_[i],x_[j]),x_[k]),
				Op_(x_[i],Op_(x_[j],x_[k])),
				Op_<<"  "<<x_[i]<<","<<x_[j]<<","<<x_[k]);
		}
	    }
	}
	return true;
    }

    bool IsSymmetric_Test()
    {
	for (std::size_t i=0; i<x_.size();i++)
	{
	    for (std::size_t j=0; j<x_.size();j++)
	    {
		ASSERT_EQ_M(Op_(x_[i],x_[j]),Op_(x_[j],x_[i]),
			    Op_<<"  "<<x_[i]<<"  "<<x_[j]);
	    }
	}
	return true;
    }

    bool IsAsymmetric_Test()
    {
	for (std::size_t i=0; i<x_.size();i++)
	{
	    for (std::size_t j=0; j<x_.size();j++)
	    {
		if (Op_(x_[i],x_[j]))
		    ASSERT_false_M(Op_(x_[j],x_[i]),Op_<<"  "<<x_[i]<<"  "<<x_[j]);
		}
	}
	return true;
    }

    bool IsTransitive_Test()
    {
	for (std::size_t i=0; i<x_.size();i++)
	{
	    for (std::size_t j=0; j<x_.size();j++)
	    {
		for (std::size_t k=0; k<x_.size();k++)
		{
		    if (Op_(x_[i],x_[j])==Op_(x_[j],x_[k]))
			ASSERT_EQ_M(Op_(x_[i],x_[j]),Op_(x_[i],x_[k]),
				  Op_<<"  "<<x_[i] <<"  "<< x_[j] <<"  "<< x_[k] );
		}
	    }
	}
	return true;
    }
    bool IsReflexive_Test()
    {
	for (std::size_t i=0; i<x_.size();i++)
	{
		ASSERT_TRUE_M(Op_(x_[i],x_[i]),Op_<<"  "<<x_[i]);
	}
	return true;
    }

    bool IsStrict_Test()
    {
	for (std::size_t i=0; i<x_.size();i++)
	{
	    ASSERT_false_M(Op_(x_[i],x_[i]),Op_<<"  "<<x_[i]);
	}
	return true;
    }

    bool IsComplement(const BinaryPredicate& ComplementOp)
    {
	for (std::size_t i=0; i<x_.size();i++)
	{
	    for (std::size_t j=0; j<x_.size();j++)
	    {
		ASSERT_NE_M(Op_(x,y),ComplementOp(x,y),
			    Op_<<"  "<<ComplementOp<<"  "<<x_[i]<<"  "<<x_[j]);
	    }
	}
	return true;
    }

    bool IsConverse(const BinaryPredicate& ConverseOp)
    {
	for (std::size_t i=0; i<x_.size();i++)
	{
	    for (std::size_t j=0; j<x_.size();j++)
	    {

		ASSERT_EQ_M(Op_(x_[j],x_[i]),ConverseOp(x,y),
			    Op_<<"  "<<ConverseOp<<"  "<<x_[i]<<"  "<<x_[j]);

	    }
	}
    }
    bool IsComplement_of_Converse(const BinaryPredicate& ComplementOfConverseOp)
    {
	for (std::size_t i=0; i<x_.size();i++)
	{
	    for (std::size_t j=0; j<x_.size();j++)
	    {
		ASSERT_NE_M(Op_(x_[j],x_[i]),
			    ComplementOfConverseOp(x_[i],x_[j]),
			    Op_<<"  "<<ComplementOfConverseOp<<"  "<<
			    x_[i]<<"  "<<x_[j]);
	    }
	}
	return true;
    }
    bool IsSymmetric_Complement(const BinaryPredicate& symmCompOp)
    {
	for (std::size_t i=0; i<x_.size();i++)
	{
	    for (std::size_t j=0; j<x_.size();j++)
	    {
		ASSERT_NE_M(!Op_(x_[i],x_[j])&&!Op_(x_[j],x_[i]),
			    symmCompOp(x_[i],x_[j]),
			    Op_<<"  "<<symmCompOp<<"  "<<
			    x_[i]<<"  "<<x_[j]);
	    }
	}
	return true;
    }

    bool IsEquivalence_Test()
    {
	if (!(IsReflexive_Test()))
	    return false;
	if (!(IsSymmetric_Test()))
	    return false;
	if (!IsTransitive_Test())
	    return false;
	return true;
    }


    template<class UnaryFunction>
    bool IsKeyFunction_Test(UnaryFunction F)
    {
	for (std::size_t i=0; i<x_.size();i++)
	{
	    for (std::size_t j=0; j<x_.size();j++)
	    {
	       if (Op_(x_[i],x_[j]))
		   ASSERT_EQ(F(x[i]),F(x[j]),
			     F<<"  "<<x[i]<<"  "x[j]);
	   }
	}
	return true;
    }
private:
    BinaryPredicate Op_;
    std::vector<T> x_;
}


}

#endif // PREDICATEPROPERTIES_TEST_H
