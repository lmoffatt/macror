#include "Markov_Mol/GaussianNoise.h"
#include "Markov_LA/auxiliarMath.h"
#include "Markov_IO/auxiliarIO.h"

namespace Markov_Mol_New
{



///  Copy Constructor
gaussian_noise* gaussian_noise::clone() const
{
    return new gaussian_noise(*this);
};
///  Default Constructor
gaussian_noise* gaussian_noise::create() const
{
    return new gaussian_noise();
};

/// Default constuctor
gaussian_noise::gaussian_noise():
        s_at_1Hz_d(),std_{},fs_{}{}

gaussian_noise::~gaussian_noise() {}




/*
/// Identifies the kind of noise
std::string gaussian_noise::name()const
{
    return "gaussian noise";
};
*/

/** Constructor
  @param s Standard deviation of the noise
  @param fs Frequency of sampling where the noise is s
  @param sto A pointer to a random number generator
  @post gaussian_noise do not own the random number generator.
*/
gaussian_noise::gaussian_noise(double standard_deviation,
                               double frequency_of_sampling):
    s_at_1Hz_d(standard_deviation/sqrt(frequency_of_sampling))
  ,std_(standard_deviation),fs_(frequency_of_sampling)
 {
 };


/** Copy constructor

*/
gaussian_noise::gaussian_noise(const gaussian_noise& other):
    s_at_1Hz_d(other.s_at_1Hz_d)
  ,std_(other.std_),fs_(other.fs_)
    {
};

/// Assigment Operator
gaussian_noise& gaussian_noise::operator=(const gaussian_noise& other)
			 {

    if (this != &other)
    {
	gaussian_noise tmp(other);
	swap(*this, tmp);
    }
    return *this;
};





/**
  Simulates gaussian noise averaged on a given time interval
  @param dt [s] Time interval of the measurement in seconds
*/
double gaussian_noise::sample(double dt, std::mt19937_64 &sto)const
{
  auto normal=std::normal_distribution<>(0,s_at_1Hz_d/sqrt(dt));
    return normal(sto);
}

/**
  Returns the value of the standard deviation of the noise for a given time
  interval.
  @param dt [s] Time interval of the measurement in seconds

*/
double gaussian_noise::std(double dt)const
{
    return s_at_1Hz_d/sqrt(dt);
};


/**
  Returns the value of the variance of the noise for a given time
  interval.
  @param dt [s] Time interval of the measurement in seconds

*/
double gaussian_noise::var(double dt) const
{
    double var=s_at_1Hz_d*s_at_1Hz_d/dt;
    return var;
}


double gaussian_noise::P(double x,double dt)const
{
    return exp(logP(x,dt));
}

double gaussian_noise::logP(double x,double dt)const
{
    return -0.5*log(2*PI*var(dt))-0.5*(x*x)/var(dt);
}




/// Swap operator.
void swap(gaussian_noise& one,gaussian_noise& two)
{
    std::swap(one.s_at_1Hz_d,two.s_at_1Hz_d);
    std::swap(one.std_,two.std_);
    std::swap(one.fs_,two.fs_);

 }





std::string gaussian_noise::ClassName()
{
    return "gaussian_noise";
}











}


