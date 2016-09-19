#ifndef PATCHMODEL_H
#define PATCHMODEL_H
#include "Markov_Mol/ABC_PatchModel.h"


namespace Markov_Mol_New
{
  class PatchModel:public ABC_PatchModel

  {
  public:
    ///virtual copy constructors
    virtual PatchModel* clone() const override;

    ///virtual default constructors
    virtual PatchModel* create() const override;


    virtual ~PatchModel();


    virtual Experiment_simulation run
    (const Markov_IO_New::ABC_Experiment& x,
     std::size_t n_replicates,
     double time_step
     , std::size_t num_steps,
     std::mt19937_64 &sto) const override;




    virtual const ABC_Markov_Model& Model()const override;

    virtual double AverageNumberOfChannels()const override;

    virtual std::size_t ChannelsCount()const override;

    virtual const ABC_noise& Noise()const override;
    virtual ABC_noise& Noise() override;


    static std::string ClassName();
    virtual std::string myClass()const override {return ClassName();}


    PatchModel(const ABC_Markov_Model* model,
               std::size_t nChannels,
               const ABC_noise* noise);

    PatchModel();

    PatchModel(const PatchModel& other);
    friend void swap(PatchModel& one, PatchModel& two);


  private:
    ABC_Markov_Model* model_;
    double nChannels_;
    ABC_noise* noise_;
  };


}



}



#endif // PATCHMODEL_H
