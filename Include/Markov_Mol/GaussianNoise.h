#ifndef GAUSSIANNOISE_H
#define GAUSSIANNOISE_H

#include "Markov_Mol/ABC_Noise.h"


namespace Markov_Mol
{

using Markov_IO::ClassDescription;

class gaussian_noise: public ABC_noise
{
public:
    virtual gaussian_noise* clone() const;
    virtual gaussian_noise* create() const;

    gaussian_noise(const gaussian_noise& other);
    gaussian_noise& operator=(const gaussian_noise& other);
    friend void swap(gaussian_noise& one,gaussian_noise& two);

    gaussian_noise();
    ~gaussian_noise();

    std::string Path()const;

    gaussian_noise(const std::string& name,
		   double standard_deviation,
		   double frequency_of_sampling,
		   Borrowed::MersenneTwister::MTRand* sto);


//    std::ostream& put(std::ostream& s) const;
//    virtual std::istream& get(std::string& line,std::istream& is);

    virtual int apply_parameters(const Parameters& p);
    virtual const Parameters& get_parameters()const;

    virtual const gaussian_noise& set_random_generator(
            Borrowed::MersenneTwister::MTRand* sto)const;


    virtual double sample(double dt)const;
    virtual double std(double dt)const;
    virtual double var(double dt) const;
    virtual double P(double x,double dt)const;
    virtual double logP(double x,double dt)const;




    virtual ClassDescription GetDescription()const;

    virtual bool LoadFromDescription(const ClassDescription& classDes);


    static std::string ClassName();

    virtual std::string id()const;
    virtual std::string myClass()const;


private:
    std::string name_;
    void buildParameters();
    double s_at_1Hz_d;
    mutable Borrowed::MersenneTwister::MTRand * sto_Sto;//not owned!!
    Parameters parameters_Map;


};

void swap(gaussian_noise& one,gaussian_noise& two);
}
#endif // GAUSSIANNOISE_H
