#include "Markov_IO/x_dt.h"

namespace Markov_IO
{

x_dt* x_dt::clone() const
{
    return new x_dt(*this);
}
/// default constructors
 x_dt* x_dt::create() const
{
    return new x_dt();
}
 x_dt::~x_dt() {}

 double x_dt::dt()const
{
    return dt_d;
}
/*   std::size_t nsamples()const
       {
	   return ns_u;
       }*/
 x_dt& x_dt::dt(double dt_)
{
    dt_d=dt_;
    return *this;
}
 double x_dt::x()const
{
    return x_d;
}

 x_dt& x_dt::x(double x_)
{
    x_d=x_;
    return *this;
}


double x_dt::y() const
{
    return 0;
}

const Markov_LA::ToleranceComparison<double>& x_dt::tolComp()const
{
    return tolComp_;
}
Markov_LA::ToleranceComparison<double>& x_dt::tolComp()
{
    return tolComp_;
}

x_dt::x_dt(const ABC_measure_point& m):dt_d(m.dt()),x_d(m.x()),	tolComp_(std::numeric_limits<double>::epsilon(),
                                                                         std::numeric_limits<double>::epsilon())
 {}

x_dt::x_dt(double dt_,double x_,double absTol,double relTol):
	dt_d(dt_),
	x_d(x_),
	tolComp_(absTol,relTol) {}

x_dt::x_dt(double dt_,double x_):
	dt_d(dt_),
	x_d(x_),
	tolComp_(std::numeric_limits<double>::epsilon(),
		 std::numeric_limits<double>::epsilon())
{}



x_dt& x_dt::operator+=(const ABC_measure_point& m){
    if (!tolComp().isEqual(x_d,m.x()))
    {
	x_d=x_d*dt_d+m.dt()*m.x();
	dt_d+=m.dt();
	x_d/=dt_d;
    }
    else
    {
	dt_d+=m.dt();
    };
    return *this;
}

x_dt::x_dt(const x_dt& other):
	dt_d(other.dt_d),
	x_d(other.x_d),
	tolComp_(other.tolComp_){}

x_dt::x_dt():
    dt_d(),
    x_d(),
    tolComp_(std::numeric_limits<double>::epsilon(),
         std::numeric_limits<double>::epsilon())
{}

x_dt&  x_dt::operator=(const x_dt& other)
		{
    if (this!=&other)
    {
	dt_d=other.dt_d;
	x_d=other.x_d;
	tolComp_=other.tolComp_;
    };
    return *this;
}


bool operator==(const x_dt& x, const x_dt& y)
{
    if (!x.tolComp().isEqual(x.x(),y.x())) return false;
    if (!x.tolComp().isEqual(x.dt(),y.dt())) return false;
    if (!x.tolComp().isEqual(x.y(),y.y())) return false;
    return true;
}


bool operator<(const x_dt& x, const x_dt& y)
{
    if (x.dt()<y.dt()) return true;
    if (y.dt()<x.dt()) return false;
    if (x.x()<y.x()) return true;
    if (y.x()<x.x()) return false;
    if (x.y()<y.y()) return true;
    return false;
}


}
