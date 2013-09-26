#include <string>
#include "Markov_IO/auxiliarIO.h"
#include "Markov_Console/OptimizeCommand.h"
#include "Markov_Bay/MarkovLikelihood.h"
#include "Markov_Console/Markov_CommandManager.h"
#include "Markov_Bay/SimpleOptimization.h"
#include "Markov_Bay/SingleOptimizationResult.h"
#include "Markov_Bay/OptimizationResult.h"
#include "Markov_LA/matrixAritmetic.h"





namespace Markov_Console
{
  ///  destructor
  OptimizeCommand::~OptimizeCommand(){}



  OptimizeCommand::OptimizeCommand(Markov_CommandManager *cm)
  {
    cm_=cm;
  }

  /// hint about of the class nature
  std::string OptimizeCommand::Tip()const
  {
    return "Calculates the likelihood of patch on an experiment";
  }

  /// a short description of the class
  std::string OptimizeCommand::WhatThis()const
  {
    return "simulate patch-alias experiment-alias \n"
        "      Simulates a patch on an experiment\n"

        "simulate patch-alias experiment-alias [option-alias] [simulation-new-alias]\n"
        "Simulates a patch for an experiment using the specified options. The"
        "results are stored in the provided new alias.";
  }




  std::string OptimizeCommand::commandName()const
  {
    return "optimize";
  }

  /// runs the command on the command manager and returns true if succeeds
  bool OptimizeCommand::run(std::deque<Token>& tokenList)
  {
    std::string parameters_in;
    std::string patch_in;
    std::string experiment_in;
    std::string options_in;
    std::string results_out;
    std::string name;
    bool zeroIter=false;
    double randomRadius=0;
    std::size_t numStarts=0;
    while (!tokenList.empty())
      {
        switch(tokenList.front().get_token())
          {
          case Token::IDENTIFIER:
            {
              name=tokenList.front().Name();
              tokenList.pop_front();
              if ((name=="noiter")||(name=="NoIter")||(name=="NOITER")||(name=="noIter"))
                {
                  zeroIter=true;
                }
              else if (cm_->checkVariable(name,Markov_IO::Parameters::ClassName()))
                {
                  //valid Patch

                  if (parameters_in.empty())
                    {
                      parameters_in=name;
                    }
                  else
                    {
                      output_.clear();
                      errorMessage_="expected one parameter, found two: "+parameters_in+
                          " and "+name;
                      return false;
                    }
                }
              else if (cm_->checkVariable(name,Markov_Mol::ABC_PatchModel::ClassName()))
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
                if (results_out.empty())
                  {
                    results_out=name;
                  }
                else
                  {
                    output_.clear();
                    errorMessage_=" found two new names: "+results_out+
                        " and "+name+ " expected one for results_out";
                    return false;
                  }

            }
            break;
          case Token::NUMBER:
            {
              double n=tokenList.front().Number();
              tokenList.pop_front();

              if (randomRadius==0)
                {
                  if (n>0)
                    {
                      randomRadius=n;
                    }
                  else
                    {
                      output_.clear();
                      errorMessage_=" randomRadius has to be positive, you give "+Markov_IO::ToString(n);
                      return false;
                    }
                }
              else
                {
                  if (n>0 && (floor(n)==n))
                    {
                      numStarts=n;

                    }
                  else
                    {
                      output_.clear();
                      errorMessage_=" number of starts has to be positive entire, you give "+Markov_IO::ToString(n);
                      return false;

                    }
                }
            }
            break;
          default:
            {
              std::string tokenString=tokenList.front().get_tokenString();
              output_.clear();
              errorMessage_="wrong token; expected NAME or NUMBER one number, found : "+
                  tokenString;
              return false;
            }
          }

      }


    if (results_out.empty())
      results_out="myOptimization";

    return run(parameters_in,patch_in,experiment_in,options_in,results_out,zeroIter,randomRadius,numStarts);
  }

  bool OptimizeCommand::run(const std::string& parameters_in,
                            const std::string& patch_in,
                            const std::string& experiment_in,
                            const std::string& options_in,
                            const std::string& results_out,
                            bool zeroIter,
                            double randomRadius,
                            std::size_t numStarts){
    bool validParameter=cm_->checkVariable(parameters_in,
                                           Markov_IO::Parameters::ClassName());
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

    Markov_IO::ABC_Experiment* e=cm_->getExperiments()[experiment_in];
    Markov_Mol::ABC_PatchModel* p=cm_->getPatchs()[patch_in];
    Markov_IO::ABC_Options* o;
    Markov_IO::Parameters* par;

    if (validOptions)
      o=cm_->getOptions()[options_in];
    else
      o=new Markov_Bay::SimpleOptimization::Options();

    if (zeroIter)
      o->set("Maximum_number_of_iterations",std::size_t(0));

    if(validParameter)
      {
        par=cm_->getParameters()[parameters_in];
        p->apply_parameters(*par);

      }
    else
      {
        par=new Markov_IO::Parameters(p->get_parameters());
      }
    Markov_Bay::SimpleOptimization Opt("esta",
                                       *p,
                                       *e,
                                       *o,
                                       cm_->getIO());

    if (randomRadius==0)
      {


        cm_->getIO()->put(" hola!, Start Optimization...\n");

        Markov_Bay::SingleOptimizationResult* myresult=
            new Markov_Bay::SingleOptimizationResult(Opt.run(*par));


        cm_->delete_var(results_out);
        cm_->getVars()[results_out]=myresult;
        cm_->getResults()[results_out]=myresult;
        std::stringstream ss;
        ss<<*myresult;
        output_=ss.str();
        errorMessage_.clear();
        return true;
      }
    else  // random optimization

      {
        Markov_LA::M_Matrix<double> cov=0.01*randomRadius*randomRadius*Markov_LA::eye<double>(par->size());
        Markov_IO::ParametersMoments pm(*par,cov);
        Markov_Mol::PatchModelNormalDistribution prior("prior",
                                                       *p,
                                                       pm,
                                                       e->num_measures());

        cm_->getIO()->put("¡hola!, Start Optimization...\n");

        if (zeroIter||(numStarts<=1))
          {

            Markov_Mol::ABC_PatchModel* pa=prior.Sample();
            Markov_Bay::SingleOptimizationResult* myresult=
                new Markov_Bay::SingleOptimizationResult(Opt.run(pa->get_parameters()));

            delete pa;
            cm_->delete_var(results_out);
            cm_->getVars()[results_out]=myresult;
            cm_->getResults()[results_out]=myresult;
            std::stringstream ss;
            ss<<*myresult;
            output_=ss.str();
            errorMessage_.clear();
            return true;

          }
        else
          {
            Markov_Bay::OptimizationResult* myresult=
                new Markov_Bay::OptimizationResult(Opt.run(prior,numStarts));


            cm_->delete_var(results_out);
            cm_->getVars()[results_out]=myresult;
            cm_->getResults()[results_out]=myresult;
            std::stringstream ss;
            ss<<*myresult;
            output_=ss.str();
            errorMessage_.clear();
            return true;
          }
      }



  }





}


