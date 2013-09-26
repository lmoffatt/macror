#include <cmath>
#include "Markov_LA/matrixSum.h"
#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixMath.h"
#include "Markov_LA/auxiliarMath.h"

#include "Markov_Bay/G_Test.h"

namespace Markov_Bay
{
using namespace Markov_LA;

    double G_Test::G()const
    {
        return G_;
    }

    double G_Test::p()const
    {
        return p_;

    }


    const std::map<double,std::size_t>& G_Test::count()const
    {
        return count_;
    }

    const std::map<double,double>& G_Test::pdf()const
    {
        return pdf_;
    }

    G_Test::G_Test(const Markov_LA::M_Matrix<std::size_t>& N,
                   const Markov_LA::M_Matrix<double>& P):
        Nt_(Markov_LA::totalsum(N)),
        count_(),
        pdf_(),
        G_(0),
        df_(0),
        p_()
    {
        for(std::size_t i=0; i<Markov_LA::size(N);i++)
        {
            count_[double(i)]=N[i];
            pdf_[double(i)]=P[i];
        }
        Compute();

    }

    G_Test::G_Test(const G_Test& other):
        Nt_(other.Nt_),
        count_(other.count_),
        pdf_(other.pdf_),
        G_(other.G_),
        df_(other.df_),
        p_(other.p_)
        {}

    G_Test::G_Test(){}

    G_Test& G_Test::operator=(const G_Test& other)
    {
	if (this!=&other)
	{
	    G_Test tmp(other);
	    swap(*this,tmp);

	}
	return *this;
    }
    std::size_t G_Test::df()const
    {
        return df_;
    }


    void swap(G_Test& one, G_Test& other)
    {
        std::swap(one.Nt_,other.Nt_);
        std::swap(one.count_,other.count_);
        std::swap(one.pdf_,other.pdf_);
        std::swap(one.G_,other.G_);
        std::swap(one.df_,other.df_);
        std::swap(one.p_,other.p_);
   }


    G_Test::G_Test(const Markov_LA::M_Matrix<double>& sample,
                  const std::map<double,double>& pdf):
        Nt_(Markov_LA::size(sample)),
        count_(),
        pdf_(pdf),
        G_(0),
        df_(0),
        p_()
    {

        for (std::map<double,double>::const_iterator it=pdf_.begin();
             it!=pdf_.end();
             ++it)
        {
            count_[it->first]=0;
        }

        for (std::size_t i=0; i<size(sample);++i)

        {
            double sam=sample[i];
            double cat=count_.upper_bound(sample[i])->first;
            count_.upper_bound(sample[i])->second++;
        }
        Compute();

      }


    void G_Test::Compute()
    {
        G_=0;
        df_=0;
        for(std::map<double,std::size_t>::const_iterator it=count_.begin();
            it!=count_.end();
            ++it)
        {
            if (it->second>0)
            {
                std::size_t Ni=it->second;
                double Ei=pdf_.find(it->first)->second*Nt_;
                G_+=Ni*std::log(Ni/Ei);
                df_++;
            }
        }
        G_*=2;
        p_=1.-ChiSqrCdf(G_,df_);

    }

    G_Test::~G_Test(){}

}


