#ifndef TRACE_H
#define TRACE_H

#include "Markov_IO/ABC_Trace.h"
#include "Markov_IO/x_step.h"

//#include "boost/shared_ptr.hpp"


namespace Markov_IO
{

class Trace: public ABC_trace

{
public:
    virtual Trace* clone() const;
    ///virtual default constructors
    virtual Trace* create() const;
    virtual ~Trace();

    static std::string ClassName();

    virtual std::string id()const;
    virtual std::string myClass()const;


    /** last measure is the trace interval*/
    virtual const Trace& operator[](std::size_t i)const;
    virtual const Trace& operator++()const;
     virtual std::size_t i_sample()const;


    virtual std::size_t num_measures()const;

    virtual std::size_t num_replicates()const;

    virtual const Trace& replicate(std::size_t i)const;

    virtual double t()const;
    virtual double dt()const;
    //    virtual size_t nsamples()const;
    virtual double x()const;
    virtual double y()const;
    virtual Trace& y(double new_value);

    virtual std::size_t num_steps()const;
    virtual const ABC_measure_point&  sub_step(std::size_t i)const;

    // virtual Trace& set_max_x_trace(double x);

    virtual ClassDescription GetDescription()const;
    virtual ClassDescription GetState()const;

    virtual bool LoadFromDescription(const ClassDescription& classDes);


    Trace(const Trace& other);

    Trace& operator=(const Trace& other);

    Trace(const std::string& traceName,
      const Markov_LA::M_Matrix<double>& tx,
      const Markov_LA::M_Matrix<double>& ty,
          double trace_interval);


    void push_back(const x_step& astep);


    Trace(const ABC_trace& other);

    Trace();

    friend
    void swap(Trace& one, Trace& other);

private:
    Markov_LA::M_Matrix<double> toTx(const ABC_trace& anytrace);
    std::vector<x_step> toXs(const ABC_trace& anytrace);
    Markov_LA::M_Matrix<double> toTy(const ABC_trace& anytrace);

    void init();
    std::string name_;
    Markov_LA::M_Matrix<double>  tx_;

    /** last two times are the end of the trace and the begining of next trace
     in both, y is NaN*/
    Markov_LA::M_Matrix<double> ty_;

    double trace_interval_;
    /**stores x more easily  */
    std::vector<x_step> xs_;

    std::size_t num_measures_;

    mutable std::size_t i_sample_, i_replicate_;


};

/*

class TraceList:public ABC_Descriptible_List
{
public:
    ///virtual copy constructors
    virtual TraceList* clone() const;
    ///virtual default constructors
    virtual TraceList* create() const;


    virtual ClassDescription GetDescription()const;

    virtual bool LoadFromDescription(const ClassDescription& classDes);
    static std::string ClassName();
    virtual std::string myName()const;
    virtual std::string myClass()const;

    TraceList(const std::vector<Trace>& traces);
    TraceList(const TraceList& other);
    TraceList& operator=(const TraceList& other);

    std::vector<Trace>  getList()const;

    TraceList();
    virtual ~TraceList();
private:
    std::vector<Trace> traces_;
};
*/
}
#endif // TRACE_H
