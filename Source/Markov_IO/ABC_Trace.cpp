#include "Markov_IO/ABC_Trace.h"
#include "Markov_IO/PulsesTrace.h"
#include "Markov_IO/Trace.h"
#include "Markov_LA/auxiliarMath.h"
#include "Markov_IO/ABC_Experiment.h"


namespace Markov_IO_New
{


std::string ABC_trace::ClassName()
{
    return "Trace";
}



Markov_LA::M_Matrix<double>  ABC_trace::t_x()const
{
 std::vector< double > tv;
 std::vector<double> xv;
 (*this)[0];
 x_dt xdt=this->sub_step(0);
 double ts=t()-0.5*dt();
 double xs=xdt.x();
 double te=ts+xdt.dt();

 tv.push_back(ts);
 tv.push_back(te);
 xv.push_back(xs);
 xv.push_back(xs);
 for (std::size_t j=0; j<num_measures(); j++)
 {
     (*this)[j];
     if (j==num_measures())
         te=t();
     te=t()-0.5*dt();
     for (std::size_t i=0; i<num_steps(); i++)
     {
	 x_dt xdt=this->sub_step(i);
	 ts=te;
	 te+=xdt.dt();
	 if(xs!=xdt.x())
	 {
	     xs=xdt.x();
	     tv.push_back(ts);
	     tv.push_back(te);
	     xv.push_back(xs);
	     xv.push_back(xs);
	 }
	 else
	 {
	     tv.back()=te;
	 }
      }

  };

 Markov_LA::M_Matrix<double> tx(tv.size(),2);
 for (std::size_t i=0; i<tv.size(); i++)
 {
     tx(i,0)=tv[i];
     tx(i,1)=xv[i];
 }


 return tx;
}

Markov_LA::M_Matrix<double> ABC_trace::t_y()const
{
    Markov_LA::M_Matrix<double>  ty(this->num_measures()*2,1+num_replicates());
    for (std::size_t i=0; i<num_measures(); i++)
    {
        ty(2*i,0)=(*this)[i].t()-dt()/2;
        ty(2*i+1,0)=t()+dt()/2;
        for (std::size_t j=0;j<num_replicates();j++)
        {
            ty(2*i,j+1)=(*this).replicate(j).y();
            ty(2*i+1,j+1)=(*this).replicate(j).y();
        }
    }
    return ty;
}



Markov_LA::M_Matrix<double> ABC_trace::toTx() const
{
    std::vector<double>ts;
    std::vector<double>xs;
    double t=0;
    double x=(*this)[0].sub_step(0).x();
    ts.push_back(t);
    xs.push_back(x);
    Markov_LA::ToleranceComparison<double> tol;
    for (std::size_t i=0; i<=(*this).num_measures(); i++)
    {
        (*this)[i];
        for (std::size_t j=0; j<(*this).num_steps(); j++)
        {
            if (tol.isEqual(x,(*this).sub_step(j).x()))
            {
                t+=(*this).sub_step(j).dt();
            }
            else
            {
                x=(*this).sub_step(j).x();
                ts.push_back(t);
                xs.push_back(x);
                t+=(*this).sub_step(j).dt();

            }
        }
    }
    ts.push_back(t);
    xs.push_back(x);

    Markov_LA::M_Matrix<double> result(ts.size(),2);
    for (std::size_t i=0; i<ts.size(); i++)
    {
        result(i,0)=ts[i];
        result(i,1)=xs[i];
    }
    return result;

}


Markov_LA::M_Matrix<double> ABC_trace::toTy()const
{
    Markov_LA::M_Matrix<double> result(
                (*this).num_measures()+2,(*this).num_replicates()+1);

    double t=0;
    for (std::size_t i=0;i<(*this).num_measures(); i++)
    {
        result(i,0)=t;
        (*this)[i];
        for (std::size_t j=0;j<(*this).num_replicates(); j++)
        {
           (*this).replicate(j);
           result(i,j+1)=(*this).y();
        }
        t+=(*this).dt();
    }
    std::size_t i=(*this).num_measures();
    (*this)[i];
    result(i,0)=t;
    for (std::size_t j=0;j<(*this).num_replicates(); j++)
    {
       (*this).replicate(j);
       result(i,j+1)=(*this).y();
    }
    t+=(*this).dt();
    result(i+1,0)=t;

    for (std::size_t j=0;j<(*this).num_replicates(); j++)
    {
        (*this).replicate(j);
        result(i+1,j+1)=Markov_LA::NaN();
    }
    return result;
}






ABC_trace::~ABC_trace() {}









}






