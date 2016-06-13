#ifndef ABC_NOISE_H
#define ABC_NOISE_H

#include "Borrowed/MersenneTwister.h"

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

    virtual const ABC_noise& set_random_generator(
            Borrowed::MersenneTwister::MTRand* sto)const=0;

    virtual double sample(double dt)const=0;

    virtual double std(double dt)const =0;

    virtual double var(double dt) const=0;

        virtual double P(double x,double dt)const=0;

        virtual double logP(double x,double dt)const=0;

        static std::string ClassName();





};


    /**
      Equality operator for ABC_Noise
      @post If the models are equal, so do all their regular functions.
      */
    bool operator==(const ABC_noise& x,const ABC_noise& y);





}


#include "Markov_IO/ABC_Saveable.h"
#include "Markov_IO/ABC_Parametrizable.h"
#include "Markov_IO/Parameters.h"
#include "Borrowed/MersenneTwister.h"

namespace Markov_Mol{

    using Markov_IO::Parameters;

    class ABC_noise:  public Markov_IO::ABC_Parametrizable
{
public:
    ///virtual copy constructors
    virtual ABC_noise* clone() const=0;

    ///virtual default constructors
    virtual ABC_noise* create() const=0;


    virtual ~ABC_noise()=0;

    virtual int apply_parameters(const Parameters& p)=0;

    /// It returns the parameters of the object
    virtual const Parameters& get_parameters()const=0;

    virtual const ABC_noise& set_random_generator(
            Borrowed::MersenneTwister::MTRand* sto)const=0;

    virtual double sample(double dt)const=0;

    virtual double std(double dt)const =0;

    virtual double var(double dt) const=0;

        virtual double P(double x,double dt)const=0;

        virtual double logP(double x,double dt)const=0;

        static std::string ClassName();

    virtual std::string mySuperClass()const;




};

    bool LoadFromDescription(ABC_noise*& noise,
                             const Markov_IO::ClassDescription& classDes);
    //bool LoadFromStringDescription(ABC_noise*& noise,
    //                         const Markov_IO::ClassDescription& classDes);

    /**
      Equality operator for ABC_Noise
      @post If the models are equal, so do all their regular functions.
      */
    bool operator==(const ABC_noise& x,const ABC_noise& y);



    std::istream& operator>> (std::istream& stream,ABC_noise*& noise);

    bool  create(ABC_noise*& e,const std::string& childClass);


}


#endif // ABC_NOISE_H
