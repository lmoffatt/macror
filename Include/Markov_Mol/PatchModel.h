#ifndef PATCHMODEL_H
#define PATCHMODEL_H
#include "Markov_Mol/ABC_PatchModel.h"


namespace Markov_Mol
{
 class PatchModel:public ABC_PatchModel

{
public:
    ///virtual copy constructors
    virtual PatchModel* clone() const;

    ///virtual default constructors
    virtual PatchModel* create() const;


    virtual ~PatchModel();

    virtual int apply_parameters(const Parameters& p);

    /// It returns the parameters of the object
    virtual const Parameters& get_parameters()const;

    virtual Experiment_simulation run(const Markov_IO::ABC_Experiment& x,
				      std::size_t n_replicates,
				      const Markov_IO::ABC_Options& opt);




    virtual const ABC_Markov_Model& Model()const;

     virtual double AverageNumberOfChannels()const;

     virtual std::size_t ChannelsCount()const;

    virtual const ABC_noise& Noise()const;
    virtual ABC_noise& Noise();

    virtual ClassDescription GetDescription()const;

    virtual bool LoadFromDescription(const ClassDescription& classDes);
    //virtual bool LoadFromStringDescription(const ClassDescription& classDes);

     static std::string ClassName();

     virtual std::string myName()const;
    virtual std::string myClass()const;

    PatchModel(const std::string& name,
	const ABC_Markov_Model& model,
	       std::size_t nChannels,
	       const ABC_noise& noise,
	       const Borrowed::MersenneTwister::MTRand& mtrand);

    PatchModel();

    PatchModel(const PatchModel& other);
    friend void swap(PatchModel& one, PatchModel& two);


private:
    std::string name_;
    Markov_IO::Parameters BuildParameters()const;
    ABC_Markov_Model* model_;
    double nChannels_;
    ABC_noise* noise_;
    mutable Markov_IO::Parameters parameters_;
    Borrowed::MersenneTwister::MTRand sto;
  };


}

#endif // PATCHMODEL_H
