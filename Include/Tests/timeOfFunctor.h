#ifndef TIMEOFFUNCTOR_H
#define TIMEOFFUNCTOR_H

#include "Tests/getTimeMs64.h"
#include <cstddef>

namespace Markov_Test
{

template<class F>
class TimeOfFunctor
{
    F f_;
    double minTime_;
    double goodTime_;
    double maxTime_;
public:
    TimeOfFunctor(F f);
    TimeOfFunctor& maxTime(double x);
    TimeOfFunctor& goodTime(double x);
    TimeOfFunctor& minTime(double x);
    double operator()();
};

template<class F>
TimeOfFunctor<F>& TimeOfFunctor<F>::maxTime(double x)
{
    maxTime_=x;
    return *this;
}

template<class F>
TimeOfFunctor<F>& TimeOfFunctor<F>::minTime(double x)
{
    minTime_=x;
    return *this;
}

template<class F>
TimeOfFunctor<F>& TimeOfFunctor<F>::goodTime(double x)
{
    return goodTime_=x;
    return *this;
}


template<class F>
TimeOfFunctor<F>::TimeOfFunctor(F f):
	f_(f),
	minTime_(5e-3),
	goodTime_(0.3),
	maxTime_(0.1){}

template<class F>
double TimeOfFunctor<F>::operator ()()
{
    int64_t t0=getTimeMs64();
    // we try one
    f_();
    int64_t t1=getTimeMs64();

    double dur=1e-3*(t1-t0);

    if(dur>maxTime_)
       return dur;
    if (dur>minTime_)
    {
	std::size_t n=goodTime_/dur;
	t0=getTimeMs64();
	for (std::size_t i=0;i<n;++i)
	{
	    f_();
	}
	t1=getTimeMs64();
	dur=1e-3*(t1-t0);
	return dur/n;
    }
    std::size_t n=10;
    while (true)
    {
	t0=getTimeMs64();
	for (std::size_t i=0;i<n;i++)
	    f_();
	t1=getTimeMs64();
	dur=1e-3*(t1-t0);
	if (dur>minTime_)
	{
	    std::size_t m=goodTime_/dur*n;
	    t0=getTimeMs64();
	    for (std::size_t i=0;i<m;++i)
	    {
		f_();
	    }
	    t1=getTimeMs64();
	    dur=1e-3*(t1-t0);
	    return dur/m;
	}
	n*=10;
    }
}



}




#endif // TIMEOFFUNCTOR_H
