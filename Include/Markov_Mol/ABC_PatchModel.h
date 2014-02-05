#ifndef ABC_ABC_PatchModel_H
#define ABC_ABC_PatchModel_H

#include "Markov_IO/ABC_Saveable.h"
#include "Markov_IO/ABC_Parametrizable.h"
#include "Markov_IO/ABC_Options.h"
#include "Markov_IO/ABC_Experiment.h"
#include "Markov_Mol/ExperimentSimulation.h"
#include "Markov_Mol/ABC_MarkovModel.h"
#include "Markov_Mol/ABC_Noise.h"
#include "Markov_IO/Parameters.h"

namespace Markov_Mol
{
 using Markov_IO::Parameters;
 using Markov_IO::ClassDescription;
class ABC_PatchModel: public Markov_IO::ABC_Parametrizable

{
public:
    ///virtual copy constructors
    virtual ABC_PatchModel* clone() const=0;

    ///virtual default constructors
    virtual ABC_PatchModel* create() const=0;

    virtual ~ABC_PatchModel();

    virtual int apply_parameters(const Parameters& p)=0;

    /// It returns the parameters of the object
    virtual const Parameters& get_parameters()const=0;

    virtual Experiment_simulation run(const Markov_IO::ABC_Experiment& x,
				      std::size_t n_replicates,
				      const Markov_IO::ABC_Options& opt)=0;




    virtual const ABC_Markov_Model& Model()const=0;


    virtual double AverageNumberOfChannels()const=0;

    virtual std::size_t ChannelsCount()const=0;

    virtual const ABC_noise& Noise()const=0;
    virtual ABC_noise& Noise()=0;

    virtual ClassDescription GetDescription()const=0;

    virtual bool LoadFromDescription(const ClassDescription& classDes)=0;
    //virtual bool LoadFromStringDescription(const ClassDescription& classDes);

    static std::string ClassName();
    static std::vector<std::string> parentClasses();
    static std::vector<std::string> childClasses();
    virtual bool amIAbstract()const;
    virtual std::vector<std::string>  myParentClasses()const;
    virtual std::vector<std::string>  myChildClasses()const;

    virtual std::string myName()const=0;
    virtual std::string myClass()const=0;
    virtual std::string mySuperClass()const;


};
















bool operator==(const ABC_PatchModel& x,const ABC_PatchModel& y);


bool LoadFromDescription(ABC_PatchModel*& x,
			 const Markov_IO::ClassDescription& classDes);
//bool LoadFromStringDescription(ABC_PatchModel*& x,
//			 const Markov_IO::ClassDescription& classDes);


std::istream& operator>> (std::istream& stream,ABC_PatchModel*& model);


bool  create(ABC_PatchModel*& e,const std::string& childClass);

}


#endif // ABC_ABC_PatchModel_H
