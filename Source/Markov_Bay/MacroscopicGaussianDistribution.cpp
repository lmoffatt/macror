#include "Markov_Bay/MacroscopicGaussianDistribution.h"
#include "Markov_LA/matrixSum.h"
#include "Markov_LA/matrixInverse.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/auxiliarMath.h"


namespace Markov_Bay
{
std::size_t MacroscopicGaussianDistribution::getRank(const Markov_LA::M_Matrix<double>& Pcov)
{
    std::size_t rank=0;
    for (std::size_t i=0; i<Markov_LA::nrows(Pcov); ++i)
        if  (Pcov(i,i)>0)
            rank++;
    return rank;
}

Markov_LA::M_Matrix<double>
MacroscopicGaussianDistribution::getPcovRedInv(const Markov_LA::M_Matrix<double>& Pcov)
{
    // first find out the rank of PcovInv
    std::size_t rank=getRank(Pcov);
    if (rank>0)
    {
        Markov_LA::M_Matrix<double> inverse(rank-1,rank-1);
        std::size_t ii=0;
        std::size_t i=0;
        while(ii<rank-1)
        {
            if (Pcov(i,i)>0)
            {
                std::size_t jj=0;
                std::size_t j=0;
                while(jj<rank-1)
                {
                    if (Pcov(j,j)>0)
                    {
                        inverse(ii,jj)=Pcov(i,j);
                        jj++;
                    }
                    j++;
                }
                ii++;
            }
            i++;
        }
        inverse=Markov_LA::inv(inverse);
        return inverse;
    }
    else
    {
        Markov_LA::M_Matrix<double> inverse;
        return inverse;
    }
}





MacroscopicGaussianDistribution::
MacroscopicGaussianDistribution(const Markov_LA::M_Matrix<double>& Pmean,
                                const Markov_LA::M_Matrix<double>& Pcov,
                                double N,
                                long  seed):
    Pmean_(Pmean),
    Pcov_(Pcov),
    N_(N),
    rank_(getRank(Pcov)),
    PcovRedInv_(getPcovRedInv(Pcov)),
    gaussian_()
{
    if (rank_>0)
    {
        gaussian_=MultivariateGaussian(Markov_LA::zeros<double>(1,rank_-1),
                                       PcovRedInv_,seed);
    }

}


Markov_LA::M_Matrix<double>
MacroscopicGaussianDistribution::SampleP()const
{
    Markov_LA::M_Matrix<double> P(Pmean_);
    Markov_LA::M_Matrix<double> tmp=gaussian_.sample()/std::sqrt(double(N_));
    if (rank_>0)
    {
        std::size_t k=ncols(Pmean_);
        std::size_t ii=0;
        std::size_t ilast;
        for (std::size_t i=0;i<k;i++)
        {
            if (Pcov_(i,i)>std::sqrt(std::numeric_limits<double>::epsilon()))
            {
                if(ii<rank_-1)
                {
                    P(0,i)=std::max(0.0,std::min(1.0,Pmean_(0,i)+tmp(0,ii)));
                    ii++;
                }
                else
                {
                    P(0,i)=0;
                    ilast=i;
                }
            }
        }
        double Psum=Markov_LA::totalsum(P);
        if (Psum>1)
        {
           P=P/Psum;
        }
        else
        {
            P(0,ilast)=1.-Psum;
        }

    }
    if(std::abs(totalsum(P)-1)>=1e-12)
        assert (false);
    return P;
}

Markov_LA::M_Matrix<std::size_t>
MacroscopicGaussianDistribution::SampleN()const
{
    std::size_t k=ncols(Pmean_);
    Markov_LA::M_Matrix<std::size_t> result(1,k);

    Markov_LA::M_Matrix<double> P=SampleP();
    std::size_t Ns=N_;
    double dN=N_-Ns;
    if (dN>gaussian_.get_random_generator().rand())
        Ns++;
    double P_left=1.0;
    std::size_t N_left=Ns;
    for (std::size_t i=0; i<k-1; ++i)
    {
        if (P(0,i)<=0)
        {
            P(0,i)=0;
            result(0,i)=0;
        }
        else if (P(0,i)>1.0)
        {
            result(0,i)=Ns;
            N_left=0;
        }
        else
        {
            std::size_t Ni=P(0,i)/P_left*N_left;

            double dN=P(0,i)/P_left*N_left-Ni;
            if (dN>gaussian_.get_random_generator().rand())
                Ni++;
            P_left-=P(0,i);
            N_left-=Ni;
            result(0,i)=Ni;
        }
    }
    result(0,k-1)=N_left;
    return result;

}

MacroscopicGaussianDistribution::
MacroscopicGaussianDistribution(const MacroscopicGaussianDistribution& other):
    Pmean_(other.Pmean_),
    Pcov_(other.Pcov_),
    N_(other.N_),
    rank_(other.rank_),
    PcovRedInv_(other.PcovRedInv_),
    gaussian_(other.gaussian_){}

MacroscopicGaussianDistribution&
MacroscopicGaussianDistribution::operator=(
        const MacroscopicGaussianDistribution& other)
{
    if (this!=&other)
    {
        MacroscopicGaussianDistribution tmp(other);
        swap(*this,tmp);
    }
    return *this;
}

void swap(MacroscopicGaussianDistribution& one,
          MacroscopicGaussianDistribution& other)
{
    swap(one.Pmean_,other.Pmean_);
    swap(one.Pcov_,other.Pcov_);
    std::swap(one.N_,other.N_);
    std::swap(one.rank_,other.rank_);
    swap(one.PcovRedInv_,other.PcovRedInv_);
    swap(one.gaussian_,other.gaussian_);
}

double MacroscopicGaussianDistribution::
Chi2_P_mean(const Markov_LA::M_Matrix<double> Pmean)const
{
    if (Markov_LA::ncols(Pmean)!=Markov_LA::ncols(Pmean_))
        return 0.0;
    std::size_t ii=0;
    std::size_t i=0;
    if (rank_==0)
    {
        if (Pmean==Pmean_) return 1;
        else return 0;
    }
    else
    {
        Markov_LA::M_Matrix<double> Pdiff(1,rank_-1);
        while (ii<rank_-1)
        {
            if (Pcov_(i,i)>std::sqrt(std::numeric_limits<double>::epsilon()))
            {
                Pdiff(0,ii)=Pmean(0,i)-Pmean_(0,i);
                ii++;
            }
            else
            {
                if (std::abs(Pmean(0,i)-Pmean_(0,i))>
                        std::sqrt(std::numeric_limits<double>::epsilon()))
                    return 0.0;
            }
            i++;
        }
        double chi2=Markov_LA::ToDouble(Pdiff*Markov_LA::multTransp(PcovRedInv_,Pdiff))*
                N_;
        return chi2;
    }
}


double MacroscopicGaussianDistribution::
Pr_P_mean(const Markov_LA::M_Matrix<double> Pmean,
                 double df)const
{
    double p=Markov_LA::ChiSqrCdf(Chi2_P_mean(Pmean)*df,NumVaryingStates()-1);

    return 1.-p;
}


std::size_t MacroscopicGaussianDistribution::NumVaryingStates()const
{
    return rank_;
}


MacroscopicGaussianDistribution::MacroscopicGaussianDistribution(){}

MacroscopicGaussianDistribution::~MacroscopicGaussianDistribution(){}

}

