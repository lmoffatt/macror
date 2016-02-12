#include "Markov_Console/Average_Command.h"
#include "Markov_IO/AverageExperiment.h"
#include "Markov_Console/Markov_CommandManager.h"
#include "Markov_IO/Object.h"
namespace Markov_Console
{
  ///  destructor
  AverageCommand::~AverageCommand(){}





  AverageCommand::AverageCommand(Markov_CommandManager *cm)
    :ABC_Command(cm,
                 "average",{{
                 "experiment_in",Markov_IO::ABC_Experiment::ClassName(),true},{
                 "options_in",Markov_Mol::AverageExperiment::Options::ClassName(),false}},{{
                 "experiment_out",Markov_IO::Object<std::string>::ClassName(),false}})
  {
  }

  /// hint about of the class nature
  std::string AverageCommand::Tip()const
  {
    return "Averages an experiment to speed up calculations";
  }

  /// a short description of the class
  std::string AverageCommand::WhatThis()const
  {
    return "average experiment-alias \n"
        "      Averages  a patch on an experiment\n"

        "simulate patch-alias experiment-alias [option-alias] [simulation-new-alias]\n"
        "Simulates a patch for an experiment using the specified options. The"
        "results are stored in the provided new alias.";
  }




  std::string AverageCommand::commandName()const
  {
    return "average";
  }

  /// runs the command on the command manager and returns true if succeeds
  bool AverageCommand::run(std::deque<Token>& tokenList)
  {
    std::string experiment_in;
    std::string experiment_out;
    std::string options_in;
    std::string name;
    while (!tokenList.empty())

      {
        switch(tokenList.front().get_token())
          {
          case Token::IDENTIFIER:
            name=tokenList.front().Name();
            tokenList.pop_front();
            if (cm_->checkVariable(name,Markov_IO::ABC_Experiment::ClassName()))
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
          default:
            std::string tokenString=tokenList.front().get_tokenString();
            output_.clear();
            errorMessage_="wrong token; expected NAME or NUMBER one number, found : "+
                tokenString;
            return false;
          }



      }


    if (experiment_out.empty())
      experiment_out="myAverage";
    return run(experiment_in,experiment_out,options_in);
  }

  bool AverageCommand::run( const std::string &experiment_in,
                            const std::string &experiment_out,
                            const std::string &options_in)
  {
    bool validExperiment=cm_->checkVariable(experiment_in,
                                            Markov_IO::ABC_Experiment::ClassName());
    bool validOptions=cm_->checkVariable(options_in,
                                         Markov_IO::ABC_Options::ClassName());

    if (!validExperiment)
      {
        output_.clear();
        errorMessage_=" failed to provide an experiment";
        return false;
      }

    Markov_IO::ABC_Experiment* e=dynamic_cast<Markov_IO::ABC_Experiment*>
        (cm_->getVar(experiment_in));
    Markov_IO::ABC_Options* o;

    if (validOptions)
      o=dynamic_cast<Markov_IO::ABC_Options*>(cm_->getVar(options_in));
    else
      o=new Markov_Mol::AverageExperiment::Options();

    Markov_IO::AverageExperiment Avg("",*o);

    Markov_IO::Experiment* avg =new
        Markov_IO::Experiment(Avg.run(*e));

    cm_->delete_var(experiment_out);
    cm_->add_var(experiment_out,avg);

    output_="average  "+experiment_out+ " created succesfully";
    errorMessage_.clear();
    return true;


  }

  AverageCommandVar::AverageCommandVar(Markov_CommandManagerVar *cm)
    :
      ABC_CommandVar(cm
                     ,"average"
                     , ""
                     ,"Averages an experiment to speed up calculations"
                     ,"average experiment-alias \n"
                      "      Averages  a patch on an experiment\n"

                      "simulate patch-alias experiment-alias [option-alias] [simulation-new-alias]\n"
                      "Simulates a patch for an experiment using the specified options. The"
                      "results are stored in the provided new alias."
                     ,1){
    push_backVarRef("experiment_in","",Markov_IO::ABC_Experiment::ClassName()
                    ,"average_this","experiment to be averaged");

    push_backVarRef("options_in","",Markov_Mol::AverageExperiment::Options::ClassName(),"","");

    pushChild(new Markov_IO::Implements_Simple_Value<std::string>(true,"experiment_out",""));

  }



  void AverageCommandVar::run( const std::string &experiment_in,
                              const std::string &experiment_out,
                              const std::string &options_in)
    {
//      bool validExperiment=cm_->checkVariable(experiment_in,
//                                              Markov_IO::ABC_Experiment::ClassName());
//      bool validOptions=cm_->checkVariable(options_in,
//                                           Markov_IO::ABC_Options::ClassName());

//      if (!validExperiment)
//        {
//          output_.clear();
//          errorMessage_=" failed to provide an experiment";
//          return false;
//        }

//      Markov_IO::ABC_Experiment* e=dynamic_cast<Markov_IO::ABC_Experiment*>
//          (cm_->getVar(experiment_in));
//      Markov_IO::ABC_Options* o;

//      if (validOptions)
//        o=dynamic_cast<Markov_IO::ABC_Options*>(cm_->getVar(options_in));
//      else
//        o=new Markov_Mol::AverageExperiment::Options();

//      Markov_IO::AverageExperiment Avg("",*o);

//      Markov_IO::Experiment* avg =new
//          Markov_IO::Experiment(Avg.run(*e));

//      cm_->delete_var(experiment_out);
//      cm_->add_var(experiment_out,avg);

//      output_="average  "+experiment_out+ " created succesfully";
//      errorMessage_.clear();
//      return true;


    }






  /// runs the command on the command manager and returns true if succeeds
   bool AverageCommandVar::processTokens(Markov_IO::Token_Stream &t)
 {
//    std::string experiment_in;
//    std::string experiment_out;
//    std::string options_in;
//    std::string name;
//    while (!tokenList.empty())

//      {
//        switch(tokenList.front().get_token())
//          {
//          case Token::IDENTIFIER:
//            name=tokenList.front().Name();
//            tokenList.pop_front();
//            if (cm_->checkVariable(name,Markov_IO::ABC_Experiment::ClassName()))
//              {
//                if (experiment_in.empty())
//                  {
//                    experiment_in=name;
//                  }
//                else if (experiment_out.empty())
//                  {
//                    experiment_out=name;
//                  }
//                else
//                  {
//                    output_.clear();
//                    errorMessage_=" found three experiments: "+experiment_in+
//                        " ," +experiment_out+" and "+name+ " expected at most 2";
//                    return false;
//                  }
//              }
//            else if(cm_->checkVariable(name,Markov_IO::ABC_Options::ClassName()))
//              {
//                if (options_in.empty())
//                  {
//                    options_in=name;
//                  }
//                else
//                  {
//                    output_.clear();
//                    errorMessage_="expected one options, found two: "+options_in+ " and "+name;
//                    return false;
//                  }
//              }
//            else
//              if (experiment_out.empty())
//                {
//                  experiment_out=name;
//                }
//              else
//                {
//                  output_.clear();
//                  errorMessage_=" found two new names: "+experiment_out+
//                      " and "+name+ " expected one for experiment out";
//                  return false;
//                }

//            break;
//          default:
//            std::string tokenString=tokenList.front().get_tokenString();
//            output_.clear();
//            errorMessage_="wrong token; expected NAME or NUMBER one number, found : "+
//                tokenString;
//            return false;
//          }



//      }


//    if (experiment_out.empty())
//      experiment_out="myAverage";
//    return run(experiment_in,experiment_out,options_in);
  }




}



