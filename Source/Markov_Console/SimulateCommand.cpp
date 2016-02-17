#include "Markov_Console/SimulateCommand.h"
#include <Markov_IO/auxiliarIO.h>
#include <Markov_Console/Markov_CommandManager.h>
#include "Markov_IO/ABC_Experiment.h"
#include "Markov_IO/Experiment.h"
#include "Markov_Mol/SimulationOptions.h"
#include "Markov_Mol/ABC_PatchModel.h"
#include "Markov_IO/getTimems.h"
#include "Markov_IO/Object.h"

namespace Markov_Console
{
  ///  destructor
  SimulateCommand::~SimulateCommand(){}



  SimulateCommand::SimulateCommand(Markov_CommandManager *cm):
    ABC_Command(
      cm,
      "simulate",{
      "patch_in",
      "experiment_in",
      "num_replicates",
      "options_in"},{
      Markov_Mol::ABC_PatchModel::ClassName(),
      Markov_IO::ABC_Experiment::ClassName(),
      Markov_IO::Object<std::size_t>::ClassName(),
      Markov_IO::ABC_Options::ClassName()},  {
      true,true,false,false},{
      "experiment_out"},  {
      Markov_IO::Object<std::string>::ClassName()},{
      false}
      )
  {}

  SimulateCommandVar::SimulateCommandVar(Markov_CommandManagerVar *cm):
    ABC_CommandVar(cm
                   ,ClassName()
                   ,""
                   ,"simulates an experiment"
                   ,ClassName()+" command\n"
                    " simulates \n"
                   ,0)
  {
     pushChild(new Markov_IO::Implements_Refer_Var(PatchIn(),
                                                   Markov_Mol::ABC_PatchModel::ClassName(),"",
                                                   "patch model in"
                                                   ,"the patch that is to be modeled"));

     pushChild(new Markov_IO::Implements_Refer_Var(ExperimentIn(),
                                                   Markov_Mol::ABC_Experiment::ClassName(),"",
                                                   "experiment in"
                                                   ,"the experiment that is to be modeled"));

     pushChild(new Markov_IO::Implements_Simple_Value<std::string>(true,
                                                                   ExperimentOut()
                                                                   ,SimulationId::ClassName()
                                                                   ,"unique identifier for simulation"
                                                                   ,"an identifier for the subject"));
     pushChild(new Markov_IO::Implements_Simple_Value<std::size_t>(true,
                                                                   NumReplicates()
                                                                   ,HelpSubject::ClassName()
                                                                   ,"subject to be clarified"
                                                                   ,"an identifier for the subject"));
  }

  SimulateCommandVar *SimulateCommandVar::clone() const
  {
    return new SimulateCommandVar(*this);
  }




  std::string SimulateCommand::commandName()const
  {
    return "simulate";
  }

  bool SimulateCommand::run(const std::vector<std::__cxx11::string> &InputValue, const std::vector<std::__cxx11::string> &OutputValue)
  {

  }

  bool SimulateCommand::run(const std::string &patch_in,
                            const std::string &experiment_in,
                            const std::string &experiment_out,
                            std::size_t num_replicates,
                            const std::string &options_in)
  {
    int64_t tini=Markov_IO::getTimeMs();

    bool validOptions=cm_->checkVariable(options_in,
                                         Markov_IO::ABC_Options::ClassName());


    Markov_IO::ABC_Experiment* e=dynamic_cast<Markov_IO::ABC_Experiment*>(cm_->getVar(experiment_in));
    Markov_Mol::ABC_PatchModel* p=dynamic_cast<Markov_Mol::ABC_PatchModel*>(cm_->getVar(patch_in));
    Markov_IO::ABC_Options* o;

    if (validOptions)
      o=dynamic_cast<Markov_IO::ABC_Options*>(cm_->getVar(options_in));
    else
      o=new Markov_Mol::SimulationOptions();

    Markov_IO::Experiment* sim =new
        Markov_IO::Experiment(p->run(*e,num_replicates,*o));

    getCommandManager()->delete_var(experiment_out);
    getCommandManager()->add_var(experiment_out,sim);

    int64_t tend=Markov_IO::getTimeMs();
    std::size_t telap=tend-tini;
    std::string timestr=Markov_IO::ToString(telap);

    output_="simulation "+experiment_out+ " created succesfully in "+timestr+"ms";
    errorMessage_.clear();
    return true;


  }





  bool SimulateCommandVar::run(const std::string &patch_in,
                            const std::string &experiment_in,
                            const std::string &experiment_out,
                            std::size_t num_replicates,
                            const std::string &options_in)
  {
    int64_t tini=Markov_IO::getTimeMs();



    Markov_IO::ABC_Experiment* e=dynamic_cast<Markov_IO::ABC_Experiment*>(cm_->getVar(experiment_in));
    Markov_Mol::ABC_PatchModel* p=dynamic_cast<Markov_Mol::ABC_PatchModel*>(cm_->getVar(patch_in));
    Markov_IO::ABC_Options*   o=dynamic_cast<Markov_IO::ABC_Options*>(cm_->getVar(options_in));
    if (o==nullptr)
      o=new Markov_Mol::SimulationOptions();

    Markov_IO::Experiment* sim =new
        Markov_IO::Experiment(p->run(*e,num_replicates,*o));

    getCommandManager()->removeChild(experiment_out);
    //getCommandManager()->pushIdChild(experiment_out,sim);

    int64_t tend=Markov_IO::getTimeMs();
    std::size_t telap=tend-tini;
    std::string timestr=Markov_IO::ToString(telap);

    getCommandManager()->getIO()->put("simulation "+experiment_out+ " created succesfully in "+timestr+"ms");
    return true;


  }

  bool SimulateCommandVar::run(ABC_CommandVar *v) const
  {



  }

  SimulateCommandVar::SimulationId::SimulationId(Markov_CommandManagerVar *cm):
    Implements_New_Identifier_Class(ClassName()
                                    ,Markov_IO::ABC_Experiment::ClassName()
                                    ,defaultIdentifier()
                                    ,cm
                                    ,"Simulation identifier"
                                    ,"an unique identifier for a particular simulation"){}

  SimulateCommandVar::NumberOfRepetitions::NumberOfRepetitions(Markov_CommandManagerVar *cm):
    Implements_Simple_Class<std::size_t>(ClassName()
                                         ,"repetitions"
                                         ,{}
                                         ,1
                                         ,1
                                         ,1e6
                                         ,""
                                         ,"number of simulations replica"
                                         ,"repetitions of the simulation with different random nubmers")
  ,
  cm_(cm){
  }





}


