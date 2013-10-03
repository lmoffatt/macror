#include "Markov_Console/SimulateCommand.h"
#include <Markov_IO/auxiliarIO.h>
#include <Markov_Console/Markov_CommandManager.h>
#include "Markov_IO/ABC_Experiment.h"
#include "Markov_IO/Experiment.h"
#include "Markov_Mol/SimulationOptions.h"
#include "Markov_Mol/ABC_PatchModel.h"
#include "Markov_IO/getTimems.h"

namespace Markov_Console
{
  ///  destructor
  SimulateCommand::~SimulateCommand(){}



  SimulateCommand::SimulateCommand(Markov_CommandManager *cm)
  {
    cm_=cm;
  }

  /// hint about of the class nature
  std::string SimulateCommand::Tip()const
  {
    return "Simulates a patch on an experiment";
  }

  /// a short description of the class
  std::string SimulateCommand::WhatThis()const
  {
    return "simulate patch-alias experiment-alias \n"
        "      Simulates a patch on an experiment\n"

        "simulate patch-alias experiment-alias [option-alias] [simulation-new-alias]\n"
        "Simulates a patch for an experiment using the specified options. The"
        "results are stored in the provided new alias.";
  }




  std::string SimulateCommand::commandName()const
  {
    return "simulate";
  }

  /// runs the command on the command manager and returns true if succeeds
  bool SimulateCommand::run(std::deque<Token>& tokenList)
  {
    std::string patch_in;
    std::string experiment_in;
    std::string experiment_out;
    std::size_t num_replicates=0;
    std::string options_in;
    std::string name;
    std::size_t number;
    while (!tokenList.empty())
      {
        switch(tokenList.front().get_token())
          {
          case Token::IDENTIFIER:
            name=tokenList.front().Name();
            tokenList.pop_front();
            if (cm_->checkVariable(name,Markov_Mol::ABC_PatchModel::ClassName()))
              {
                //valid Patch

                if (patch_in.empty())
                  {
                    patch_in=name;
                  }
                else
                  {
                    output_.clear();
                    errorMessage_="expected one patch, found two: "+patch_in+ " and "+name;
                    return false;
                  }
              }
            else if (cm_->checkVariable(name,Markov_IO::ABC_Experiment::ClassName()))
              {
                if (experiment_in.empty())
                  {
                    experiment_in=name;
                  }
                else if (experiment_out.empty())
                  {
                    experiment_out=name;
                  }
                else
                  {
                    output_.clear();
                    errorMessage_=" found three experiments: "+experiment_in+
                        " ," +experiment_out+" and "+name+ " expected at most 2";
                    return false;
                  }
              }
            else if(cm_->checkVariable(name,Markov_IO::ABC_Options::ClassName()))
              {
                if (options_in.empty())
                  {
                    options_in=name;
                  }
                else
                  {
                    output_.clear();
                    errorMessage_="expected one options, found two: "+options_in+ " and "+name;
                    return false;
                  }
              }
            else
              if (experiment_out.empty())
                {
                  experiment_out=name;
                }
              else
                {
                  output_.clear();
                  errorMessage_=" found two new names: "+experiment_out+
                      " and "+name+ " expected one for experiment out";
                  return false;
                }

            break;
          case Token::NUMBER:
            number=tokenList.front().Number();
            tokenList.pop_front();
            if (num_replicates==0)
              {
                num_replicates=number;
              }
            else
              {
                output_.clear();
                errorMessage_="expected one number, found two: "+
                    Markov_IO::ToString(num_replicates)+ " and "+
                    Markov_IO::ToString(number);
                return false;
              }
            break;
          default:
            std::string tokenString=tokenList.front().get_tokenString();
            output_.clear();
            errorMessage_="wrong token; expected NAME or NUMBER one number, found : "+
                tokenString;
            return false;
          }



      }


    if (experiment_out.empty())
      experiment_out="mySimulation";
    if (num_replicates==0)
      num_replicates=1;
    return run(patch_in,experiment_in,experiment_out,num_replicates,options_in);
  }


  std::vector<std::string> SimulateCommand::
  complete(const std::string& hint,const std::deque<Token>& tokenList)const
  {
    std::string patch_in;
    std::string experiment_in;
    std::size_t num_replicates=0;
    std::string options_in;
    std::string experiment_out;
    std::string name;
    std::size_t number;


    if (tokenList.empty())
      return {"Bug:","\t absent command"};
    else if (tokenList.front().Name()!=this->commandName())
      return {"Bug:","\t erroneous command"};
    else if (tokenList.size()==1)
      return cm_->complete(hint,Markov_Mol::ABC_PatchModel::ClassName());
    else
      {
        patch_in=tokenList[1].Name();
        if (! (cm_->checkVariable(patch_in,Markov_Mol::ABC_PatchModel::ClassName())))
          return {"Error: ","\t patch expected"};
        else if (tokenList.size()==2)
          return cm_->complete(hint,Markov_IO::ABC_Experiment::ClassName());
        else
          {
            experiment_in=tokenList[2].Name();
            if (! (cm_->checkVariable(experiment_in,Markov_Mol::ABC_Experiment::ClassName())))
              return {"Error: ","\t experiment expected"};
            else if (tokenList.size()==3)
              {
                return  cm_->complete(hint,Markov_Mol::SimulationOptions::ClassName());
              }
            else
              {
                return {"Mandatory fields filled ",
                    "\t optional fields: number of replictes and alias for simulation"};

              }
          }
      }
  }



  bool SimulateCommand::run(const std::string &patch_in,
                            const std::string &experiment_in,
                            const std::string &experiment_out,
                            std::size_t num_replicates,
                            const std::string &options_in)
  {
    int64_t tini=Markov_IO::getTimeMs();
    bool validExperiment=cm_->checkVariable(experiment_in,
                                            Markov_IO::ABC_Experiment::ClassName());
    bool validPatch=cm_->checkVariable(patch_in,
                                       Markov_Mol::ABC_PatchModel::ClassName());
    bool validOptions=cm_->checkVariable(options_in,
                                         Markov_IO::ABC_Options::ClassName());

    if (!validPatch )
      {
        output_.clear();
        if (validExperiment)
          {
            errorMessage_=" failed to provide a patchmodel";
            return false;
          }
        else
          {
            errorMessage_=" failed to provide a patchmodel and an experiment";
            return false;

          }
      }
    if (!validExperiment)
      {
        output_.clear();
        errorMessage_=" failed to provide an experiment";
        return false;
      }

    Markov_IO::ABC_Experiment* e=dynamic_cast<Markov_IO::ABC_Experiment*>(cm_->getVar(experiment_in));
    Markov_Mol::ABC_PatchModel* p=dynamic_cast<Markov_Mol::ABC_PatchModel*>(cm_->getVar(patch_in));
    Markov_IO::ABC_Options* o;

    if (validOptions)
      o=dynamic_cast<Markov_IO::ABC_Options*>(cm_->getVar(options_in));
    else
      o=new Markov_Mol::SimulationOptions();

    Markov_IO::Experiment* sim =new
        Markov_IO::Experiment(p->run(*e,num_replicates,*o));

    cm_->delete_var(experiment_out);
    cm_->add_var(experiment_out,sim);

    int64_t tend=Markov_IO::getTimeMs();
    std::size_t telap=tend-tini;
    std::string timestr=Markov_IO::ToString(telap);

    output_="simulation "+experiment_out+ " created succesfully in "+timestr+"ms";
    errorMessage_.clear();
    return true;


  }





}


