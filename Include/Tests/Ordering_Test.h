#ifndef ORDERING_TEST_H
#define ORDERING_TEST_H

#include "Tests/PredicateProperties_Test.h"

namespace Markov_Test
{
template<class T, class EqualityPredicate, class OrderPredicate>
class OrderingProperties_test
{
public:
    OrderingProperties_test(const EqualityPredicate& isEqual,
			    const OrderPredicate& isThisOrder):
    isEqual_(isEqual),
    isThisOrder_(isThisOrder),
    isEqualTest_(isEqual),
    isThisOrderTest_(isThisOrder){}


    bool isTrichotomy_Test(const T& a,const T& b)
    {
	if (isEqual_(a,b))
	    return (!isThisOrder_(a,b)&&!isThisOrder_(b,a));
	else if (isThisOrder_(a,b))
	    return !isThisOrder_(b,a);
	else
	    return isThisOrder_(b,a);
    }

    bool isTotalOrdering_Test(const T& a,const T& b,const T& c)
    {
	if (! isEqualTest_.IsEquivalence_Test(a,b,c))
	    return false;
	if (! isThisOrderTest_.IsTransitive_Test(a,b,c))
	    return false;
	if (!(isTrichotomy_Test(a,b)&&isTrichotomy_Test(b,c)))
	    return false;
	return true;
    }




private:
    EqualityPredicate isEqual_;
    OrderPredicate isThisOrder_;
    BinaryPredicate_Tests isEqualTest_;
    BinaryPredicate_Tests isThisOrderTest_;
};

};
#endif // ORDERING_TEST_H
