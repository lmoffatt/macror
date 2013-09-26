#ifndef REGULARTYPE_TEST_H
#define REGULARTYPE_TEST_H
#include <vector>
#include "Tests/MultipleTests.h"
#include "Tests/ElementaryTest.h"
#include "Markov_IO/auxiliarIO.h"
namespace Markov_Test
{


template<class T>
class RegularType_Test
{
public:
    RegularType_Test(const RegularType_Test<T>& other):
	    x_(other.elements){}


    RegularType_Test(std::vector<T> elements):
	    x_(elements){}


    RegularType_Test<T>& operator=(const RegularType_Test<T>& other)
				  {
	x_=other.x_;
	return *this;
    }

    RegularType_Test():
	    x_(){}





    /**
       Asserts that the Copy Constructor provides variables Equal to the original
       @tparam T class where the test is performed
       @param a singular value where the test is performed
       @invariant different adddress, the copy cannot be the original
       @invariant copy and original are equal
    */
    MultipleTests CopyConstructor_Test()
    {
	MultipleTests result("Copy Constructor",
			     "1. Copy has a new address"
			     "2. Copy is equal to the original");
	for (std::size_t i=0;i<x_.size();++i)
	{
	    T b(x_[i]);
	    result.push_back(UnEqualAddress_Test("Copy has new address",
						 b,x_[i]));
	    result.push_back(EqualValue_Test("Copy holds same value",
						 b,x_[i]));
	}
	return result;
    }

    /**
       Asserts that the Assigment provides variables Equal to the original
       @tparam T class where the test is performed
       @param a singular value where the test is performed
       @invariant different adddress, the copy cannot be the original
       @invariant copy and original are equal
    */
    MultipleTests Assigment_Test()
    {
	MultipleTests result("Assigment_test",
			     "copies have a new address"
			     "and they are equal to original");

	for (std::size_t i=0;i<x_.size();++i)
	{
	    T b=x_[i];
	    result.push_back(UnEqualAddress_Test("Copy has new address",
						 b,x_[i]));
	    result.push_back(EqualValue_Test("Copy holds same value",
						 b,x_[i]));
	}
	return result;
    }

    MultipleTests Swap_Test()
    {
	MultipleTests result("Swap_Test",
			     "values are exchanged");

	for (std::size_t i=0;i<x_.size();++i)
	{
	    for (std::size_t j=0;j<x_.size();++j)
	    {
		T xNew(x_[i]);
		T yNew(x_[j]);
		swap(xNew,yNew);
		result.push_back(EqualValue_Test(
				     "value of first swapped variable"
				     "equal to former second variable",
				     x_[i],
				     yNew));
		result.push_back(EqualValue_Test(
				     "value of second swapped variable"
				     "equal to former frist variable",
				     x_[j],
				     xNew));
	    }
	}
	return result;
    }
    MultipleTests AllTest()
    {
	MultipleTests result("RegularType_Test",
		      "can be copied, swapped and assigned");

	result.push_back(this->CopyConstructor_Test());
	result.push_back(this->Assigment_Test());
	result.push_back(this->Swap_Test());
	return result;

    }

private:
    std::vector<T> x_;

};

}
#endif // REGULARTYPE_TEST_H
