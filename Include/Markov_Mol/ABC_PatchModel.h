#ifndef ABC_ABC_PatchModel_H
#define ABC_ABC_PatchModel_H

#include "Markov_IO/ABC_Options.h"
#include "Markov_IO/ABC_Experiment.h"
#include "Markov_Mol/ExperimentSimulation.h"
#include "Markov_Mol/ABC_MarkovModel.h"
#include "Markov_Mol/ABC_Noise.h"

#include <random>
namespace Markov_Mol_New
{




class ABC_PatchModel
{
public:
    ///virtual copy constructors
    virtual ABC_PatchModel* clone() const=0;

    ///virtual default constructors
    virtual ABC_PatchModel* create() const=0;

    virtual ~ABC_PatchModel();


    virtual Experiment_simulation run(const Markov_IO_New::ABC_Experiment& x,
				      std::size_t n_replicates,
				      double time_step
				      , std::size_t num_steps,
			     std::mt19937_64& mtrand)const =0;




    virtual const ABC_Markov_Model& Model()const=0;


    virtual double AverageNumberOfChannels()const=0;

    virtual std::size_t ChannelsCount()const=0;

    virtual const ABC_noise& Noise()const=0;
    virtual ABC_noise& Noise()=0;


    static std::string ClassName();
    virtual std::string myClass()const=0;



};
















bool operator==(const ABC_PatchModel& x,const ABC_PatchModel& y);



bool  create(ABC_PatchModel*& e,const std::string& childClass);

}




#endif // ABC_ABC_PatchModel_H
