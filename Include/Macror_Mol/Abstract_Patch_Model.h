#ifndef ABSTRACT_PATCH_MODEL_H
#define ABSTRACT_PATCH_MODEL_H

namespace MacroR_Mol {
  class Abstract_Patch_Model
  {

  public:

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

      virtual std::string myName()const=0;
      virtual std::string myClass()const=0;
      virtual std::string mySuperClass()const;


  };



}

#endif // ABSTRACT_PATCH_MODEL_H
