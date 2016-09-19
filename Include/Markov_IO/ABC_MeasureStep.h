#ifndef ABC_MEASURESTEP_H
#define ABC_MEASURESTEP_H
#include <cstddef> //size_t
#include <iostream>

#include "Markov_IO/ABC_MeasurePoint.h"
namespace Markov_IO_New
{

class ABC_measure_step: public ABC_measure_point
{
public:
    virtual ABC_measure_step* clone() const=0;
    ///virtual default constructors
    virtual ABC_measure_step* create() const=0;
    virtual ~ABC_measure_step();
//    virtual size_t nsamples()const=0;
    virtual double dt()const=0;
    virtual double x()const=0;
    virtual double y()const=0;

    virtual std::size_t num_steps()const=0;
    virtual const ABC_measure_point&  sub_step(std::size_t i)const=0;

  std::ostream& printSelf(std::ostream& s)const;
    virtual std::ostream& put(std::ostream& s) const;
};
}













#endif // ABC_MEASURESTEP_H
