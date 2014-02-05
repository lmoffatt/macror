#ifndef NORMALDISTRIBUTED_H

#define NORMALDISTRIBUTED_H

#include "Markov_LA/Matrix.h"

#include "Markov_Bay/ABC_ParametricDistributable.h"
#include "Markov_Bay/ABC_Distribution.h"

#include "Markov_Bay/MultivariateGaussian.h"

namespace Markov_Bay
{
class NormalDistributed: public ABC_Distribution
{
public:
    ///virtual copy constructors
    virtual NormalDistributed* clone() const;
    ///virtual default constructors
    virtual NormalDistributed* create() const;

    virtual ~NormalDistributed();

    //virtual std::ostream& put(std::ostream&) const=0;

    /// Apply the matching parameters
    virtual int apply_parameters(const Markov_IO::Parameters& p);
    // object inspectors

    /// Apply the matching parameters
    virtual int apply_parameters_moments(const Markov_IO::ParametersMoments& p);

    virtual const Markov_IO::Parameters& get_parameters()const;

    /// Returns the parameters of the object
    virtual const Markov_IO::ParametersMoments& get_parameters_moments()const;

    /*    /// It returns a name for the object that identifies its architecture
	virtual std::string name()const=0; */


    virtual std::string myName()const;
    virtual std::string myClass()const;
    static std::string ClassName();

    virtual Markov_IO::ClassDescription GetDescription()const;

    virtual bool LoadFromDescription(const Markov_IO::ClassDescription &classDes);

    virtual Markov_IO::ABC_Parametrizable* Sample()const;

    virtual Markov_IO::ABC_Parametrizable* Mean()const;

    virtual Markov_IO::ABC_Parametrizable* Mode()const;


    virtual double Probability(const Markov_IO::ABC_Parametrizable& sample)const;

    virtual double Density(const Markov_IO::ABC_Parametrizable& sample)const;


    NormalDistributed(const Markov_IO::ABC_Parametrizable& sample,
		      const Markov_IO::ParametersMoments& parMoments);


    //precondition: all samples have equivalent Parameters
    static NormalDistributed meanDistribution(const std::vector<ABC_Parametrizable *> &samples);


    NormalDistributed();

    NormalDistributed(const NormalDistributed& other);

    NormalDistributed& operator=(const NormalDistributed& other);

    friend void swap(NormalDistributed& one, NormalDistributed& other);


private:
    Markov_IO::ABC_Parametrizable* sample_;

    Markov_IO::ParametersMoments parMoments_;

    MultivariateGaussian gaussian_;

   };
}




#endif // NORMALDISTRIBUTED_H
