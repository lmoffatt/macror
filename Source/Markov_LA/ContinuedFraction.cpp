#include "Markov_LA/ContinuedFraction.h"

namespace Markov_LA
{

   ContinuedFraction::ContinuedFraction(const std::vector<double>& a,
                      const std::vector<double>& b):
       a_(a),
       b_(b),
       value_(0)
   {}

    ContinuedFraction::ContinuedFraction(const ContinuedFraction& other):
	a_(other.a_),
	b_(other.b_),
	value_(other.value_)
    {}

    ContinuedFraction::ContinuedFraction():
	a_(),
	b_(),
	value_(0){}

    ContinuedFraction& ContinuedFraction::operator=(const ContinuedFraction& other)
    {
	if (this!=&other)
	{
	    ContinuedFraction tmp(other);
	    swap(*this,tmp);
	}
	return *this;
    }

    void swap(ContinuedFraction& one, ContinuedFraction& two)
    {
	std::swap(one.a_,two.a_);
	std::swap(one.b_,two.b_);
	std::swap(one.value_,two.value_);
    }



    double ContinuedFraction::operator()()const
    {
	if (value_==0)
	{
	    value_=1;
	    for (std::size_t i=b_.size(); i>0;i--)
	    {
                value_=a_[i-1]/value_+b_[i-1];
	    }
	}
	return value_;
    }

ContinuedFraction::~ContinuedFraction(){}
}


