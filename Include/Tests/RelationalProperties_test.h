#ifndef RELATIONALPROPERTIES_TEST_H
#define RELATIONALPROPERTIES_TEST_H
#include <vector>
#include "Tests/AssertPlain.h"

namespace Markov_Test
{


template<class T>
class RelationalProperties_test
{
    RelationalProperties_test(const std::vector<T> elements):
	    x_(elements){}

    bool IrreflexiveTest()
    {
	for (std::size_t i=0; i<x_.size();i++)
	{    for (std::size_t j=0; j<x_.size();j++)
	    {
		if (x_[i]==x_[j])
		{
		    ASSERT_FALSE_M(x_[i]<x_[j], x_[i]<<"  "<<x_[j ]);
		}
	    }
	}
	return true;
    }

    bool TransitiveTest()
    {
	for (std::size_t i=0; i<x_.size();i++)
	{
	    for (std::size_t j=0; j<x_.size();j++)
	    {
		for (std::size_t k=0; k<x_.size();k++)
		{
		    if((x_[i]<x_[j])&&(x_[j]<x_[k]))
		    {
			ASSERT_TRUE_M(x_[i]<x_[k],
				 x_[i]<<"  "<<x_[j]<<"  "<<x_[k]);
		    }
		}
	    }
	}
	return true;
    }

    bool AntiSymmetryTest()
    {
	for (std::size_t i=0; i<x_.size();i++)
	{
	    for (std::size_t j=0; j<x_.size();j++)
	    {
		if (x_[i]<x_[j])
		{
		    ASSERT_TRUE_M(x_[j]>x_[i],
				  x_[i]<<"   "<< x_[j] );
		}
	    }
	}
	return true;
    }

    bool TrichotomyTest()
    {
	for (std::size_t i=0; i<x_.size();i++)
	{
	    for (std::size_t j=0; j<x_.size();j++)
	    {
		if (x_[i]<x_[j])
		{
		    ASSERT_FALSE_M(x_[i]==x_[j],
				   x_[i]<<"  "<<x_[j]);
		    ASSERT_FALSE_M(x_[i]>x_[j],
				   x_[i]<<"  "<<x_[j]);
		}
		else
		{
		    if(x_[i]>x_[j])
		    {
			ASSERT_FALSE(x_[i]==x_[j],
				     x_[i]<<" "<<x_[j]);
		    }
		    else
		    {
			ASSERT_TRUE(x_[i]==x_[j],
				    x_[i]<<"  "<<x_[j]);
		    }
		}
	    }
	}
	return true;
    }
	private:
    std::vector<T> x_;

}



}





#endif // RELATIONALPROPERTIES_TEST_H
