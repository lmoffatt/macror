#ifndef MARKOVSIMULATOR_H
#define MARKOVSIMULATOR_H

#include "Markov_IO/ABC_Put.h"
#include "Markov_IO/ABC_Options.h"

#include "Markov_Mol/ExperimentSimulation.h"
#include "Markov_Mol/PatchModel.h"


namespace Markov_Mol
{
class Markov_Simulator: public Markov_IO::ABC_Put
{
public:
    ///virtual copy constructors
    virtual Markov_Simulator* clone()const;
    virtual Markov_Simulator* create()const;
    virtual std::ostream& put(std::ostream& s) const;

    virtual Experiment_simulation run(const Markov_IO::ABC_Experiment& x,
				      std::size_t n_replicates=1);


    virtual const ABC_Markov_Model& model()const;

    virtual double N_channels()const;

    virtual const ABC_noise& noise()const;

    virtual const ABC_PatchModel& Patch()const;

    Markov_Simulator(const ABC_PatchModel& patch,
		     const double time_step,
		     int32_t seed=0);

    Markov_Simulator();

public:
    ABC_PatchModel* patch_;
    double time_step_d;
    mutable Borrowed::MersenneTwister::MTRand sto;
};
}

#endif // MARKOVSIMULATOR_H
