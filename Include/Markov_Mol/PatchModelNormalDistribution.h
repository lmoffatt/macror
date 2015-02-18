#ifndef PATCHMODELNORMALDISTRIBUTION_H
#define PATCHMODELNORMALDISTRIBUTION_H

#include "Markov_IO/ABC_Saveable.h"
#include "Markov_Bay/NormalDistributed.h"



#include "Markov_Mol/PatchModel.h"
#include "Markov_Mol/ABC_Noise.h"
#include "Markov_Bay/ABC_Distribution.h"


namespace Markov_Mol
{
 using Markov_IO::ParametersMoments;
 using Markov_IO::ClassDescription;


class PatchModelNormalDistribution:
	public Markov_Bay::NormalDistributed

{
public:
    ///virtual copy constructors
    virtual PatchModelNormalDistribution* clone() const;

    ///virtual default constructors
    virtual PatchModelNormalDistribution* create() const;


    virtual ~PatchModelNormalDistribution();

    virtual PatchModel* Sample()const;

    virtual PatchModel* Mean()const;

    virtual ClassDescription GetDescription()const;

    virtual bool LoadFromDescription(const ClassDescription& classDes);

    static std::string ClassName();
    virtual std::string id()const;
    virtual std::string myClass()const;

    PatchModelNormalDistribution();

    PatchModelNormalDistribution(const std::string& name,
			   const ABC_PatchModel& patch,
			   const Markov_IO::ParametersMoments& paramMoments,
			   std::size_t nsamples);





    PatchModelNormalDistribution(const PatchModelNormalDistribution& other);

    PatchModelNormalDistribution& operator=(const PatchModelNormalDistribution& other);


    std::size_t nSamples()const;




    friend void swap(PatchModelNormalDistribution& one, PatchModelNormalDistribution& other);

private:
    std::string name_;
    std::size_t nsamples_;

   };

}



#endif // PATCHMODELNORMALDISTRIBUTION_H
