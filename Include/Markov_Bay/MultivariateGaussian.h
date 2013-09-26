#ifndef MULTIVARIATEGAUSSIAN_H
#define MULTIVARIATEGAUSSIAN_H
#include "Markov_LA/Matrix.h"
#include "Markov_LA/matrixRand.h"
#include "Markov_IO/ParametersMoments.h"
#include "Markov_Mol/ABC_Noise.h"

namespace Markov_Bay
{

class MultivariateGaussian
{
public:
    MultivariateGaussian(const Markov_LA::M_Matrix<double>& mean,
			 const Markov_LA::M_Matrix<double>& covinv,
			 long  seed);

    MultivariateGaussian(const Markov_IO::ParametersMoments& parMoments,
			 long seed=0);


    MultivariateGaussian& setMoments(const Markov_IO::ParametersMoments& parMoments);

    MultivariateGaussian();

    MultivariateGaussian& set_random_generator(Borrowed::MersenneTwister::MTRand *sto);

    Borrowed::MersenneTwister::MTRand& get_random_generator()const;

    std::size_t size()const;

    double logP(const Markov_LA::M_Matrix<double>& x)const;
    double P(const Markov_LA::M_Matrix<double>& x)const;

    Markov_LA::M_Matrix<double> sample()const;


    const Markov_LA::M_Matrix<double>& Mean()const;
     Markov_LA::M_Matrix<double> Cov()const;
    const Markov_LA::M_Matrix<double>& CovInv()const;


    MultivariateGaussian(const MultivariateGaussian& other);
    MultivariateGaussian& operator=(const MultivariateGaussian& other);

    friend void swap(MultivariateGaussian& one, MultivariateGaussian& other);

    ~MultivariateGaussian();

private:
    Markov_LA::M_Matrix<double> mean_;
    Markov_LA::M_Matrix<double> covinv_;
    Markov_LA::M_Matrix<double> cho_cov_;
    double logDetCov_;
    mutable Borrowed::MersenneTwister::MTRand MTR_;
};


}
#endif // MULTIVARIATEGAUSSIAN_H
