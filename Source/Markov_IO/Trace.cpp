#include "Markov_IO/Trace.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_LA/auxiliarMath.h"
#include "Tests/AssertPlain.h"



namespace Markov_IO_New
{


Trace* Trace::clone() const
{
    return new Trace(*this);
}
/// default constructors
Trace* Trace::create() const
{
    return new Trace();
}
Trace::~Trace()
{

}

std::string Trace::ClassName()
{
    return "Simple_Trace";
}








/** last measure is the trace interval*/
const Trace& Trace::operator[](std::size_t i)const
{
  ASSERT_LEQ(i,num_measures());
  i_sample_=i;
    return *this;
}



const Trace& Trace::operator++()const
{
  ASSERT_LESS(i_sample(),num_measures());

    i_sample_++;
    return *this;
}

std::size_t Trace::i_sample()const
{
    return i_sample_;
}



std::size_t Trace::num_measures()const
{
    return num_measures_;
}

std::size_t Trace::num_replicates()const
{
    return ncols(this->ty_)-1;
}

const Trace& Trace::replicate(std::size_t i)const
{
  ASSERT_LESS(i,num_replicates());
    i_replicate_=i;
    return *this;
}





double Trace::t()const
{
    return (ty_(i_sample()+1,0)+ty_(i_sample(),0))/2;
}
double Trace::dt()const
{
    return xs_[i_sample_].dt();
}

//     size_t nsamples()const=0;
double Trace::x()const
{
    return xs_[i_sample_].x();
}

double Trace::y()const
{
    return ty_(i_sample_,1+i_replicate_);
}
Trace& Trace::y(double new_value)
{
    ty_(i_sample_,1+i_replicate_)=new_value;
    return *this;
}

std::size_t Trace::num_steps()const
{
    return xs_[i_sample_].num_steps();
}
const ABC_measure_point&  Trace::sub_step(std::size_t i)const
{
    ASSERT_LESS(i,num_steps());
    return xs_[i_sample_].sub_step(i);
}


//  Trace& set_max_x_trace(double x)=0;


Trace::Trace(const Trace& other):
    name_(other.name_),
    tx_(other.tx_),
    ty_(other.ty_),
    trace_interval_(other.trace_interval_),
    xs_(other.xs_),
    num_measures_(other.num_measures_),
    i_sample_(other.i_sample_),
    i_replicate_(other.i_replicate_)
     {}

Trace& Trace::operator=(const Trace& other)
{
    if(this!=&other)
    {
        Trace tmp(other);
        swap(tmp,*this);
    }
    return *this;
}

Trace::Trace():
    name_(),
    tx_(Markov_LA::M_Matrix<double>("0  0")),
    ty_(Markov_LA::M_Matrix<double>("0  0")),
     trace_interval_(),
     xs_(),
     num_measures_(0),
  i_sample_(),
  i_replicate_()
    {}

void swap(Trace& one, Trace& other)
{
    std::swap(one.name_,other.name_);
    swap(one.tx_,other.tx_);
    swap(one.ty_,other.ty_);
    std::swap(one.xs_,other.xs_);
    std::swap(one.num_measures_,other.num_measures_);

    std::swap(one.trace_interval_,other.trace_interval_);
    std::swap(one.i_sample_,other.i_sample_);
    std::swap(one.i_replicate_,other.i_replicate_);


}

Trace::Trace(const Markov_LA::M_Matrix<double>& tx,
             const Markov_LA::M_Matrix<double>& ty,
             double trace_interval):
    tx_(tx),
    ty_(ty),
    trace_interval_(trace_interval),
    xs_(),
    num_measures_(0),
    i_sample_(0),
    i_replicate_(0)
{
    init();
    (*this)[0];
}


Trace::Trace(const ABC_trace& other):
    tx_(other.toTx()),
    ty_(other.toTy()),
    trace_interval_(other.operator [](other.num_measures()).dt()),
    xs_(),
    num_measures_(0),
    i_sample_(0),
    i_replicate_(0)
    {
    init();
    (*this)[0];
   }





void Trace::init()
{
    //adds a fake last x change and an initial zero x if necessary

    xs_.clear();
    std::size_t nChangesX=Markov_LA::nrows(tx_);
    std::size_t nty0=Markov_LA::nrows(ty_);
    std::size_t nty=nty0;

    // process so the last two rows are nan, one for the last dt
    // the other for the interval

    while (Markov_LA::isNaN(ty_(nty-1,1)))
        nty--;
    num_measures_=nty;

    if (nty0!=nty+2)
    {
        Markov_LA::M_Matrix<double> ty(num_measures_+2,2);
        for (std::size_t i=0; i<num_measures_; i++)
        {
            ty(i,0)=ty_(i,0);
            ty(i,1)=ty_(i,1);
        }
        if (nty0==nty)
        {
            ty(num_measures_,0)=2*ty(num_measures_-1,0)-ty(num_measures_-2,0);
            ty(num_measures_,1)=Markov_LA::NaN();
        }
        else
        {
            ty(num_measures_,0)=ty_(num_measures_,0);
            ty(num_measures_,1)=ty_(num_measures_,1);

        }
        ty(num_measures_+1,0)=ty(num_measures_,0)+trace_interval_;
        ty(num_measures_+1,1)=Markov_LA::NaN();
        ty_=ty;
    }

    bool addLast=ty_(num_measures_,0)>=tx_(nChangesX-1,0);
    bool addFirst=tx_(0,0)>0;
    Markov_LA::M_Matrix<double> tx;
    if (addFirst)
    {
        nChangesX++;
        if (addLast)
        {
            nChangesX++;
            tx=Markov_LA::M_Matrix<double> (nChangesX,2);
            tx(0,1)=0;
            tx(0,0)=0;
            for (std::size_t i=1; i<nChangesX-1; ++i)
            {
                tx(i,0)=tx_(i-1,0);
                tx(i,1)=tx_(i-1,1);
            }
            tx(nChangesX-1,0)=2*ty_(num_measures_,0)-ty_(num_measures_-1,0);
            tx(nChangesX-1,1)=tx(nChangesX-2,1);

        }
        else
        {
            Markov_LA::M_Matrix<double> tx(nChangesX,2);
            tx(0,1)=0;
            tx(0,0)=0;
            for (std::size_t i=1; i<nChangesX; ++i)
            {
                tx(i,0)=tx_(i-1,0);
                tx(i,1)=tx_(i-1,1);
            }
        }
        tx_=tx;

    }
    if (addLast)
    {
        nChangesX++;
        Markov_LA::M_Matrix<double> tx(nChangesX,2);
        for (std::size_t i=1; i<nChangesX-1; ++i)
        {
            tx(i,0)=tx_(i,0);
            tx(i,1)=tx_(i,1);
        }
        tx(nChangesX-1,0)=ty_(num_measures_+1,0);
        tx(nChangesX-1,1)=tx(nChangesX-2,1);
        tx_=tx;
    }
    std::size_t i0x=0;
    std::size_t i1x=0;
    Markov_LA::ToleranceComparison<double> tol;
    for (std::size_t i=0; i<=num_measures_; i++)
    {

        while (tol.isLess(tx_(i0x+1,0),ty_(i,0)))
        {
            i0x++;
        }
        while (i1x+1<Markov_LA::nrows(tx_)&& tol.isLess(tx_(i1x+1,0),ty_(i+1,0)))
        {
            i1x++;
        }
        if (i1x==i0x)
        {
            double x=tx_(i0x,1);
            double dt=ty_(i+1,0)-ty_(i,0);
            x_step        xs=x_step(dt,x);
            xs_.push_back(xs);
        }
        else
        {
            double x=tx_(i0x,1);
            double dt=tx_(i0x+1,0)-ty_(i,0);
            x_step xs;
            if (tol.isLess(0.0,dt))
                  xs=x_step(dt,x);
            for (std::size_t ix=i0x+1; ix<i1x; ix++)
            {
                dt=tx_(ix+1,0)-tx_(ix,0);
                x=tx_(ix,1);
                xs.push_back(dt,x);
            }
            dt=ty_(i+1,0)-tx_(i1x,0);
            x=tx_(i1x,1);
            xs.push_back(dt,x);
            xs_.push_back(xs);

        }

    }
    i_sample_=0;
}





}







