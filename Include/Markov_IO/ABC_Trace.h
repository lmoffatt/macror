#ifndef ABC_TRACE_H
#define ABC_TRACE_H
#include <cstddef> //std::size_t
#include <iostream>

#include "Markov_IO/ABC_MeasureStep.h"

#include "Markov_LA/Matrix.h"

namespace Markov_IO_New
{

class ABC_trace: public ABC_measure_step
{
public:
    virtual ABC_trace* clone() const=0;
    ///virtual default constructors
    virtual ABC_trace* create() const=0;
    virtual ~ABC_trace();

    static std::string ClassName();
    virtual std::string myClass()const=0;


    /** last measure is the trace interval*/
    virtual const ABC_trace& operator[](std::size_t i)const=0;
    virtual const ABC_trace& operator++()const=0;

    virtual std::size_t i_sample()const=0;

    virtual std::size_t num_measures()const=0;

    virtual std::size_t num_replicates()const=0;

    virtual const ABC_trace& replicate(std::size_t i)const=0;

    virtual double t()const=0;
    virtual double dt()const=0;
    //    virtual size_t nsamples()const=0;
    virtual double x()const=0;
    virtual double y()const=0;

    virtual
    Markov_LA::M_Matrix<double> t_x()const;

    virtual Markov_LA::M_Matrix<double> t_y()const;


    virtual Markov_LA::M_Matrix<double> toTx()const;
    virtual Markov_LA::M_Matrix<double> toTy()const;


    virtual std::size_t num_steps()const=0;
    virtual const ABC_measure_point&  sub_step(std::size_t i)const=0;

    // virtual ABC_trace& set_max_x_trace(double x)=0;

};



}




#endif // ABC_TRACE_H
