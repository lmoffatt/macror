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




  std::string SimulateCommand::commandName()const
  {
    return "simulate";
  }




  bool SimulateCommand::run(const std::vector<std::string>& InputValue,
                            const std::vector<std::string>& OutputValue)
  {


    std::string patch_in=InputValue[0];
    std::string experiment_in=InputValue[1];
    std::string options_in=InputValue[2];

    std::size_t num_replicates=1;
    if (!InputValue[3].empty())
      num_replicates=std::stoul(InputValue[3]);

    std::string experiment_out=OutputValue[0];

    return run(patch_in,experiment_in,experiment_out,num_replicates,options_in);
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





}


