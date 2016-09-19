#include "Markov_IO/Pulse.h"
#include <cmath>
namespace Markov_IO_New
{

double pulse_profile(double x)
{
    if (x<-3)
	return 0;
    else if (x<3)
	return 0.5+0.5*erf(x);
    else return 1;
}

double Pulse(double t, double pulse_duration, double exchange_time)
{
    double y=pulse_profile(t/exchange_time/2)-pulse_profile((t-pulse_duration)/exchange_time/2);
    return y;
}

}




