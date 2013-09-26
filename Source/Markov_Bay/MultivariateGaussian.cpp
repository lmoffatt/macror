#include "Markov_Bay/MultivariateGaussian.h"
#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/auxiliarMath.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixOperators.h"
#include "Markov_LA/matrixCholesky.h"
#include "Markov_LA/matrixInverse.h"
#include "Markov_LA/matrixRand.h"
#include "Markov_LA/matrixMaxMin.h"
#include "Markov_LA/matrixSum.h"
#include "Markov_LA/matrixMath.h"
#include "Markov_LA/matrixRelational.h"
namespace Markov_Bay
{


MultivariateGaussian& MultivariateGaussian::setMoments(
        const Markov_IO::ParametersMoments& parMoments)
{
    mean_=Markov_LA::row_vector(parMoments.transformed_values());
    covinv_=parMoments.transformed_CovInv();
    cho_cov_=Markov_LA::chol(Markov_LA::invSafe(covinv_));
    logDetCov_=log(Markov_LA::diagProduct(cho_cov_));
    return *this;
}


MultivariateGaussian& MultivariateGaussian::set_random_generator(Borrowed::MersenneTwister::MTRand *sto)
{
    this->MTR_=*sto;
    return *this;
}

Borrowed::MersenneTwister::MTRand& MultivariateGaussian::get_random_generator()const
{
    return MTR_;
}


double MultivariateGaussian::P(const Markov_LA::M_Matrix<double>& x)const
{
    return exp(logP(x));
}
double MultivariateGaussian::logP(const Markov_LA::M_Matrix<double>& x)const
{
    if (Markov_LA::size(x)!=Markov_LA::size(mean_))
        return Markov_LA::NaN();
    Markov_LA::M_Matrix<double> d=Markov_LA::row_vector(x)-mean_;
    double chi2=0;

    for (std::size_t i=0;i<Markov_LA::size(mean_);++i)
    {
        chi2+=d[i]*d[i]*covinv_(i,i);
        for (std::size_t j=i+1; j<Markov_LA::size(mean_); ++j)
        {
            chi2+=2*d[i]*d[j]*covinv_(i,j);
        }
    }
    double logL=-0.5*(log(2*PI)+0.5*logDetCov_+chi2);
    //revisar  double logL=-0.5*(log(2*PI)*Markov_LA::size(mean_)+0.5*logDetCov_+chi2);


    return logL;
}


std::size_t MultivariateGaussian::size()const
{
    return Markov_LA::size(this->mean_);
}

Markov_LA::M_Matrix<double> MultivariateGaussian::sample()const
{
    Markov_LA::M_Matrix<double> r;
    if (this->size()>0)
    {
        Markov_LA::M_Matrix<double> z(1, Markov_LA::size(mean_));
        for (std::size_t i=0; i<Markov_LA::size(z); i++)
            z[i]=MTR_.randNorm();
        r=mean_+z*cho_cov_;
    }
    return r;
}

MultivariateGaussian::MultivariateGaussian(const Markov_LA::M_Matrix<double>& mean,
                                           const Markov_LA::M_Matrix<double>& covinv,
                                           long  seed):
    mean_(Markov_LA::row_vector(mean)),
    covinv_(covinv),
    cho_cov_(Markov_LA::chol(Markov_LA::invSafe(covinv_),"upper")),
    logDetCov_(log(Markov_LA::diagProduct(cho_cov_))),
    MTR_(Borrowed::MersenneTwister::seedinit(seed))
{}

MultivariateGaussian::MultivariateGaussian(const Markov_IO::ParametersMoments& parMoments,
                                           long seed):
    mean_(Markov_LA::row_vector(parMoments.transformed_values())),
    covinv_(parMoments.transformed_CovInv()),
    cho_cov_(Markov_LA::chol(Markov_LA::invSafe(covinv_),"upper")),
    logDetCov_(log(Markov_LA::diagProduct(cho_cov_))),
    MTR_(Borrowed::MersenneTwister::seedinit(seed))
{}

MultivariateGaussian::MultivariateGaussian():
    mean_(),
    covinv_(),
    cho_cov_(),
    logDetCov_(),
    MTR_()
{}

MultivariateGaussian::MultivariateGaussian(const MultivariateGaussian& other):
    mean_(other.mean_),
    covinv_(other.covinv_),
    cho_cov_(other.cho_cov_),
    logDetCov_(other.logDetCov_),
    MTR_(other.MTR_)
{}

MultivariateGaussian& MultivariateGaussian::operator=(
        const MultivariateGaussian& other)
{
    if (this!=&other)
    {
        MultivariateGaussian tmp(other);
        swap(tmp,*this);
    }
    return *this;
}
void swap(MultivariateGaussian& one, MultivariateGaussian& other)
{
    swap(one.mean_,other.mean_);
    swap(one.covinv_,other.covinv_);
    swap(one.cho_cov_,other.cho_cov_);
    std::swap(one.logDetCov_,other.logDetCov_);
    Borrowed::MersenneTwister::MTRand tmp(one.MTR_);
    one.MTR_=other.MTR_;
    other.MTR_=tmp;

}

MultivariateGaussian::~MultivariateGaussian(){}


const Markov_LA::M_Matrix<double>& MultivariateGaussian::Mean()const
{
    return mean_;
}
Markov_LA::M_Matrix<double> MultivariateGaussian::Cov()const
{
    return Markov_LA::inv(covinv_);
}

const Markov_LA::M_Matrix<double>& MultivariateGaussian::CovInv()const
{
    return covinv_;
}

}
