#ifndef MACROSCOPICGAUSSIANDISTRIBUTION_H
#define MACROSCOPICGAUSSIANDISTRIBUTION_H
#include "Markov_LA/Matrix.h"
#include "Markov_LA/matrixRand.h"
#include "Markov_IO/ParametersMoments.h"
#include "Markov_Mol/ABC_Noise.h"
#include "Markov_Bay/MultivariateGaussian.h"



namespace Markov_Bay
{
class MacroscopicGaussianDistribution
{
public:
    MacroscopicGaussianDistribution(const Markov_LA::M_Matrix<double>& Pmean,
                                    const Markov_LA::M_Matrix<double>& Pcov,
                                    double N,
                                    long  seed);

    MacroscopicGaussianDistribution();

    Markov_LA::M_Matrix<double> SampleP()const;
    Markov_LA::M_Matrix<std::size_t> SampleN()const;

    double Pr_P_mean(const Markov_LA::M_Matrix<double> Pmean,
                     double df)const;

    double Chi2_P_mean(const Markov_LA::M_Matrix<double> Pmean)const;

    std::size_t NumVaryingStates()const;

    MacroscopicGaussianDistribution(const MacroscopicGaussianDistribution& other);
    MacroscopicGaussianDistribution& operator=(
            const MacroscopicGaussianDistribution& other);

    friend void swap(MacroscopicGaussianDistribution& one,
                     MacroscopicGaussianDistribution& other);


    static Markov_LA::M_Matrix<double>
    getPcovRedInv(const Markov_LA::M_Matrix<double>& Pcov);

    static std::size_t
    getRank(const Markov_LA::M_Matrix<double>& Pcov);

    ~MacroscopicGaussianDistribution();

private:
    Markov_LA::M_Matrix<double> Pmean_;
    Markov_LA::M_Matrix<double> Pcov_;
    double N_;
    std::size_t rank_;
    Markov_LA::M_Matrix<double> PcovRedInv_;
    MultivariateGaussian gaussian_;

  };


}

#endif // MACROSCOPICGAUSSIANDISTRIBUTION_H
