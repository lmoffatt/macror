#include "Markov_IO/x_step.h"
#include "Tests/AssertPlain.h"
namespace Markov_IO
{


x_step*  x_step::clone() const
{
    return new x_step(*this);
}

/// default constructors
 x_step* x_step::create() const
{ return new x_step();}
 x_step::~x_step() {}
//     size_t nsamples()const;
 double x_step::dt()const
{
    return xdt_.dt();
}
 double x_step::x()const
{
    return xdt_.x();
}
 double x_step::y()const
{return y_;}

 std::size_t x_step::num_steps()const
{return num_steps_;}

 const x_dt&  x_step::sub_step(std::size_t i)const
{
   ASSERT_LESS(i,num_steps());
    if (num_steps_>1)
	return sub_step_[i];
    else
	return xdt_;
}

 std::ostream& x_step::put(std::ostream& s) const
{
    for (std::size_t i=0; i<num_steps(); i++)
    {
	s<<"("<<i<<")"<<sub_step(i).dt()<<"  "<<x()<<"  "<<y()<<"\t";
    };
    s<<"\n";
    return s;
}

x_step::x_step(const ABC_measure_step& xs):
	num_steps_(0),
	xdt_(xs),
	y_(xs.y()),
	sub_step_()
{
    x_dt xdt=xs.sub_step(0);
    for (std::size_t i=1; i<xs.num_steps();i++)
    {
	if (!xdt.tolComp().isEqual(xdt.x(),xs.sub_step(i).x()))
	{
	    sub_step_.push_back(xdt);
	    xdt=xs.sub_step(i);
	}
	else
	{
	    xdt.dt(xdt.dt()+xs.sub_step(i).dt());
	}
    }
    sub_step_.push_back(xdt);
    num_steps_=sub_step_.size();
}


x_step& x_step::operator+=(const ABC_measure_step& xs)
		  {
    // load the first sub-interval of the added step
    x_dt xdt=xs.sub_step(0);

    // if the last interval of previous step has the same x, drop it and sum to xdt
    if (xdt_.tolComp().isEqual(sub_step_.back().x(),xdt.x()))
    {
	xdt+=sub_step_.back();
	sub_step_.pop_back();
    }


    for (std::size_t i=1; i<xs.num_steps();i++)
    {

	if (!xdt.tolComp().isEqual(xdt.x(),xs.sub_step(i).x()))
	    // if x changes, insert previous interval
	{
	    sub_step_.push_back(xdt);
	    xdt=xs.sub_step(i);
	}
	else
	    //  x does not change, sum the sub-interval
	{
	    xdt+=xs.sub_step(i);
	}
    }
    // add the last sub-interval
    sub_step_.push_back(xdt);
    // update the number of sub-intervals
    num_steps_=sub_step_.size();

    // update dt, x and y
    y_=y_*dt()+xs.y()*xs.dt();
    xdt_.x(xdt_.x()*xdt_.dt()+xs.dt()*xs.x());
    xdt_.dt(dt()+xs.dt());
    xdt_.x(xdt_.x()/xdt_.dt());
    y_/=xdt_.dt();
    return *this;
}



x_step::x_step(const x_step& other):
	num_steps_(other.num_steps_),
	xdt_(other.xdt_),
	y_(other.y_),
	sub_step_(other.sub_step_){}

x_step& x_step::operator=(const x_step& other){
    if (this!=&other)
    {
	num_steps_=other.num_steps_;
	xdt_=other.xdt_;
	sub_step_=other.sub_step_;
	y_=other.y_;
    }
    return *this;
}

x_step& x_step::y(double newy)
{
    y_=newy;
    return *this;
}

x_step::x_step():
    num_steps_(0),
    xdt_(0.0,0.0),
    y_(0.0),
    sub_step_()
{}


x_step& x_step::push_back(double dtv, double xv, double yv)
{

    if (!sub_step_.empty()&&
            sub_step_.back().tolComp().isEqual(sub_step_.back().x(),xv))
    {
        sub_step_.back().dt(sub_step_.back().dt()+dtv);

    }
    else
    {
        sub_step_.push_back(x_dt(dtv,xv));
        num_steps_++;
    }
    y_=y()*dt()+yv*dtv;
    double xs=x()*dt()+xv*dtv;
    double dts=dt()+dtv;
    xdt_.dt(dts);
    xdt_.x(xs/dts);
    y_=y_/xdt_.dt();

    return *this;
}

x_step::x_step(double dt, double x, double y):
    num_steps_(1),
    xdt_(x_dt(dt,x)),
    y_(y),
    sub_step_(1,x_dt(dt,x))
{}


}
