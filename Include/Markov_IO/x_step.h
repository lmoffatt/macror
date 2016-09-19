#ifndef X_STEP_H
#define X_STEP_H


#include <vector>

#include "Markov_IO/ABC_MeasureStep.h"

#include "Markov_IO/x_dt.h"

namespace Markov_IO_New
{

/**
  it models a measurement step, i.e., a step where there could be changes in the agonist concentration but from where only an average of the current is analyzed. the likelihood algorithms will take into account all the changes in agonist concentration and they will compare to a single measurment of the current, ie., there will be a single P (probability changes) and gmean and gvar (mean and variance of the conductance).

  we will provide two constructors for constant and variable agonist during the interval

  the constructor will lump together intervals with the same agonist concentration*/


class x_step: public ABC_measure_step
{
public:
    virtual x_step* clone() const;
    ///virtual default constructors
    virtual x_step* create() const;


    virtual ~x_step();
    //    virtual size_t nsamples()const;


    virtual double dt()const;

    virtual double x()const;

    virtual double y()const;

    virtual x_step& y(double newy);

    virtual std::size_t num_steps()const;

    virtual x_step& push_back(double dt, double x, double y=0);

    virtual const x_dt&  sub_step(std::size_t i)const;

    virtual std::ostream& put(std::ostream& s) const;

    x_step(const ABC_measure_step& xs);

    x_step& operator+=(const ABC_measure_step& xs);

    x_step(const x_step& other);

    x_step& operator=(const x_step& other);

    x_step(double dt, double x, double y=0);

    x_step();


private:
    std::size_t num_steps_;
    x_dt xdt_;
    double y_;
    std::vector<x_dt> sub_step_;

};

}






#endif // X_STEP_H
