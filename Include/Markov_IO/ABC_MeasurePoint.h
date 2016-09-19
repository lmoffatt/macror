#ifndef ABC_MEASUREPOINT_H
#define ABC_MEASUREPOINT_H

#include <iostream>


namespace Markov_IO_New
{

class ABC_measure_point
{
public:

    virtual ~ABC_measure_point(){}

    //    virtual size_t nsamples()const=0;
    virtual double dt()const=0;
    virtual double x()const=0;
    virtual double y()const=0;

};
}







#endif // ABC_MEASUREPOINT_H
