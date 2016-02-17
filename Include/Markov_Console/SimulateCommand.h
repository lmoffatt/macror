#ifndef SIMULATECOMMAND_H
#define SIMULATECOMMAND_H
#include <Markov_Console/ABC_Command.h>


namespace Markov_Console
{

  class SimulateCommandVar:public ABC_CommandVar
  {
  public:
      class SimulationId:public  Markov_IO::Implements_New_Identifier_Class
     {
     public:
       static std::string ClassName(){return "SimulationId";}
       static std::string defaultIdentifier(){return "mySimulation";}

       SimulationId(Markov_CommandManagerVar* cm);


     };
     class NumberOfRepetitions: public Markov_IO::Implements_Simple_Class<std::size_t>
     {
     public:
       static std::string ClassName(){return "NumberOfRepetitions";}

     NumberOfRepetitions(Markov_CommandManagerVar* cm);

     private:
     Markov_CommandManagerVar* cm_;
     };

      /// virtual destructor
      virtual ~SimulateCommandVar(){}

      SimulateCommandVar(Markov_CommandManagerVar* cm);


      static std::string ClassName(){return "simulate";}
      std::string myClass()const {return ClassName();}


      static std::string PatchIn(){ return "Patch_In";}

      static std::string ExperimentIn(){ return "Experiment_In";}
      static std::string ExperimentOut(){ return "Experiment_Out";}
      static std::string NumReplicates(){ return "Num_Replicates";}
      static std::string OptionsIn(){return "Options_In";}



      // ABC_Put interface
  public:
      virtual SimulateCommandVar *clone() const override;

      // ABC_CommandVar interface
  public:
      virtual bool run(ABC_CommandVar *v) const override;

  private:
      bool run(const std::string& patch_in,
                       const std::string& experiment_in,
                       const std::string& experiment_out,
                       std::size_t num_replicates,
                       const std::string& options_in);

  };


  class SimulateCommand:public ABC_Command
{
public:
    /// virtual destructor
    virtual ~SimulateCommand();

    SimulateCommand(Markov_CommandManager* cm);


    virtual std::string commandName()const;


    virtual bool run(const std::vector<std::string>& InputValue,
                     const std::vector<std::string>& OutputValue);


    virtual bool run(const std::string& patch_in,
                     const std::string& experiment_in,
                     const std::string& experiment_out,
                     std::size_t num_replicates,
                     const std::string& options_in);

};


}

#endif // SIMULATECOMMAND_H
