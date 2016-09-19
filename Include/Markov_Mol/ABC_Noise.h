#ifndef ABC_NOISE_H
#define ABC_NOISE_H

#include <random>

namespace Markov_Mol_New
{


    class ABC_noise
    {
public:
    ///virtual copy constructors
    virtual ABC_noise* clone() const=0;

    ///virtual default constructors
    virtual ABC_noise* create() const=0;


    virtual ~ABC_noise();

    virtual double sample(double dt,std::mt19937_64& sto)const=0;

    virtual double std(double dt)const =0;

    virtual double var(double dt) const=0;

        virtual double P(double x,double dt)const=0;

        virtual double logP(double x,double dt)const=0;

        static std::string ClassName();
        virtual std::string myClass()const=0;





};


    /**
      Equality operator for ABC_Noise
      @post If the models are equal, so do all their regular functions.
      */
    bool operator==(const ABC_noise& x,const ABC_noise& y);





}




#endif // ABC_NOISE_H
