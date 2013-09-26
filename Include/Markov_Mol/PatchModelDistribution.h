#ifndef PATCHMODELDISTRIBUTION_H
#define PATCHMODELDISTRIBUTION_H

#include "Markov_IO/ABC_Saveable.h"
#include "Markov_Bay/NormalDistributed.h"



#include "Markov_Mol/PatchModel.h"
#include "Markov_Mol/ABC_Noise.h"



namespace Markov_Mol
{
 using Markov_IO::ParametersMoments;
 using Markov_IO::ClassDescription;


class ABC_Distribution:public Markov_IO::ABC_Saveable
{
public:
    virtual std::string mySuperClass()const;
    static std::string ClassName();
};



class PatchModelDistribution:
	public ABC_Distribution,
	public Markov_Bay::NormalDistributed

{
public:
    ///virtual copy constructors
    virtual PatchModelDistribution* clone() const;

    ///virtual default constructors
    virtual PatchModelDistribution* create() const;


    virtual ~PatchModelDistribution();

    virtual PatchModel* Sample()const;

    virtual PatchModel* Mean()const;

    virtual ClassDescription GetDescription()const;

    virtual bool LoadFromDescription(const ClassDescription& classDes);

    static std::string ClassName();
    virtual std::string myName()const;
    virtual std::string myClass()const;

    PatchModelDistribution();

    PatchModelDistribution(const std::string& name,
			   const ABC_PatchModel& patch,
			   const Markov_IO::ParametersMoments& paramMoments,
			   std::size_t nsamples);

    PatchModelDistribution(const PatchModelDistribution& other);

    PatchModelDistribution& operator=(const PatchModelDistribution& other);



    friend void swap(PatchModelDistribution& one, PatchModelDistribution& other);

private:
    std::vector<Markov_IO::ParametersMoments> parMoments_vec;
    std::string name_;
    std::size_t nsamples_;

   };

}


#endif // PATCHMODELDISTRIBUTION_H
