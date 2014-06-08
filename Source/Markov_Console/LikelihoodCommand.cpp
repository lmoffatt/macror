#include <string>
#include "Markov_IO/auxiliarIO.h"
#include "Markov_Console/LikelihoodCommand.h"
#include "Markov_Bay/MarkovLikelihood.h"
#include "Markov_Console/Markov_CommandManager.h"
#include "Markov_IO/Object.h"


namespace Markov_Console
{
  ///  destructor
  LikelihoodCommand::~LikelihoodCommand(){}



  LikelihoodCommand::LikelihoodCommand(Markov_CommandManager *cm):
    ABC_Command(cm,
                "likelihood",{{
                "patch_in",Markov_Mol::ABC_PatchModel::ClassName(),true},{
                "experiment_in",Markov_IO::ABC_Experiment::ClassName(),true},{
                "options_in",Markov_Bay::Markov_Likelihood::Options::ClassName(),false}},{{
                "likelihood_out",Markov_IO::Object<std::string>::ClassName(),false}})

  {
  }


  /// hint about of the class nature
  std::string LikelihoodCommand::Tip()const
  {
    return "Calculates the likelihood of patch on an experiment";
  }

  /// a short description of the class
  std::string LikelihoodCommand::WhatThis()const
  {
    return "simulate patch-alias experiment-alias \n"
        "      Simulates a patch on an experiment\n"

        "simulate patch-alias experiment-alias [option-alias] [simulation-new-alias]\n"
        "Simulates a patch for an experiment using the specified options. The"
        "results are stored in the provided new alias.";
  }




  std::string LikelihoodCommand::commandName()const
  {
    return "likelihood";
  }

  /// runs the command on the command manager and returns true if succeeds
  bool LikelihoodCommand::run(std::deque<Token>& tokenList)
  {
    std::string patch_in;
    std::string experiment_in;
    std::string options_in;
    std::string likelihood_out;
    std::string name;
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
                else
                  {
                    output_.clear();
                    errorMessage_=" found two experiments: "+experiment_in+
                        " and "+name+ " expected one";
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
              if (likelihood_out.empty())
                {
                  likelihood_out=name;
                }
              else
                {
                  output_.clear();
                  errorMessage_=" found two new names: "+likelihood_out+
                      " and "+name+ " expected one for likelihood_out";
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


    if (likelihood_out.empty())
      likelihood_out="myLikelihood";
    return run(patch_in,experiment_in,options_in,likelihood_out);
  }






  bool LikelihoodCommand::run(const std::string& patch_in,
                              const std::string& experiment_in,
                              const std::string& options_in,
                              const std::string& likelihood_out)
  {
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

//    Markov_IO::ABC_Experiment* e=dynamic_cast<Markov_IO::ABC_Experiment*>(cm_->getVar(experiment_in));
//    Markov_Mol::ABC_PatchModel* p=dynamic_cast<Markov_Mol::ABC_PatchModel*>(cm_->getVar(patch_in));
    Markov_IO::ABC_Options* o;

    if (validOptions)
      o=dynamic_cast<Markov_IO::ABC_Options*>(cm_->getVar(options_in));
    else
      o=new Markov_Bay::Markov_Likelihood::Options();

    Markov_Bay::Markov_Likelihood ml(cm_,patch_in,experiment_in,*o);


    if (!o->boolean("show_partialLikelihood"))
      {
        Markov_Bay::LikelihoodEvaluation* lik =new
            Markov_Bay::LikelihoodEvaluation(ml.run());

        cm_->add_var(likelihood_out,lik);
        std::stringstream ss;
        ss<<*lik;
        output_=ss.str();
        errorMessage_.clear();
        return true;

      }
    else
      if (!o->boolean("show_predictedValue"))
        {                 Markov_Bay::PartialLikelihoodEvaluation* lik =new
              Markov_Bay::PartialLikelihoodEvaluation(ml.run(std::string("dummy")));

          cm_->add_var(likelihood_out,lik);
          std::stringstream ss;
          ss<<*lik;
          output_=ss.str();
          errorMessage_.clear();
          return true;


        }
      else
        {
          Markov_Bay::YfitLikelihoodEvaluation* lik =new
              Markov_Bay::YfitLikelihoodEvaluation(ml.run(std::string("dummy"),
                                                          std::string("dummy")));

          cm_->add_var(likelihood_out,lik);
          std::stringstream ss;
          ss<<*lik;
          output_=ss.str();
          errorMessage_.clear();
          return true;
        }


}

  }


