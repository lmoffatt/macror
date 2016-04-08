#ifndef X_DT_H
#define X_DT_H

#include "Markov_IO/ABC_MeasurePoint.h"

#include "Markov_LA/ToleranceComparison.h"

namespace Markov_IO_New
{

class x_dt:public ABC_measure_point
{
public:

    virtual ~x_dt();

    virtual double dt()const;
    /*   std::size_t nsamples()const
       {
	   return ns_u;
       }*/


    virtual x_dt& dt(double dt_);

    virtual double x()const;

    virtual x_dt& x(double x_);

    double y() const;

    const Markov_LA::ToleranceComparison<double>& tolComp()const;

    Markov_LA::ToleranceComparison<double>& tolComp();

    x_dt(const ABC_measure_point& m);

    x_dt(double dt_,double x_,double absTol,double relTol);


    x_dt(double dt_,double x_);

    x_dt& operator+=(const ABC_measure_point& m);



    x_dt(const x_dt& other)=default;

    x_dt(x_dt&& other)=default;

    x_dt();

    x_dt&  operator=(const x_dt& other)=default;
    x_dt&  operator=(x_dt&& other)=default;

private:
    double dt_d;
    double x_d;
    Markov_LA::ToleranceComparison<double> tolComp_;
    // std::size_t ns_u;
};


bool operator==(const x_dt& x, const x_dt& y);

bool operator<(const x_dt& x, const x_dt& y);
}

#include "Markov_IO/ABC_MeasurePoint.h"

#include "Markov_LA/ToleranceComparison.h"

namespace Markov_IO
{

class x_dt:public ABC_measure_point
{
public:
    virtual x_dt* clone() const;

    virtual x_dt* create() const;

    virtual ~x_dt();

    virtual double dt()const;
    /*   std::size_t nsamples()const
       {
           return ns_u;
       }*/


    virtual x_dt& dt(double dt_);

    virtual double x()const;

    virtual x_dt& x(double x_);

    double y() const;

    const Markov_LA::ToleranceComparison<double>& tolComp()const;

    Markov_LA::ToleranceComparison<double>& tolComp();

    x_dt(const ABC_measure_point& m);

    x_dt(double dt_,double x_,double absTol,double relTol);


    x_dt(double dt_,double x_);

    x_dt& operator+=(const ABC_measure_point& m);



    x_dt(const x_dt& other)=default;

    x_dt(x_dt&& other)=default;

    x_dt();

    x_dt&  operator=(const x_dt& other)=default;
    x_dt&  operator=(x_dt&& other)=default;

private:
    double dt_d;
    double x_d;
    Markov_LA::ToleranceComparison<double> tolComp_;
    // std::size_t ns_u;
};


bool operator==(const x_dt& x, const x_dt& y);

bool operator<(const x_dt& x, const x_dt& y);
}


#endif // X_DT_H
