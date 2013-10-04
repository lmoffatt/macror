#include "Markov_Console/Markov_CommandManager.h"

#include <Markov_Mol/QMarkovModel.h>

#include <Markov_IO/RandomPulses.h>
#include <Markov_IO/SinglePulses.h>
#include <Markov_IO/SinglePulses2.h>
#include "Markov_IO/PulsesProgram.h"

#include "Markov_IO/Experiment.h"
#include "Markov_IO/PulsesTrace.h"
#include "Markov_IO/ExperimentAverage.h"
#include "Markov_IO/AverageExperiment.h"
#include "Markov_IO/ExperimentalData.h"



#include "Markov_IO/ABC_IO.h"



#include <Markov_Mol/ExperimentSimulation.h>
#include <Markov_Mol/MarkovSimulator.h>
#include <Markov_Mol/GaussianNoise.h>
#include "Markov_Mol/QMarkovModel.h"
#include "Markov_Mol/PatchModel.h"
#include "Markov_Mol/PatchModelNormalDistribution.h"
#include "Markov_Mol/SimulationOptions.h"



#include <Markov_Console/Markov_Script.h>
#include "Markov_Console/Token.h"


#include "Markov_Bay/YfitLikelihoodEvaluation.h"
#include "Markov_Bay/OptimizationResult.h"
#include "Markov_Bay/SingleOptimizationResult.h"
#include "Markov_Bay/PartialLikelihoodEvaluation.h"
#include "Markov_Bay/LikelihoodEvaluation.h"

#include "Markov_Bay/LikelihoodOptions.h"
#include "Markov_Bay/TerminationByThreshold.h"
#include "Markov_Bay/SimpleOptimization.h"






namespace Markov_Console
{
void Markov_CommandManager::LoadTypes()
{
    types[Markov_IO::Pulses_program::ClassName()]=new Markov_IO::Pulses_program;

    types[Markov_IO::Experiment::ClassName()]=new Markov_IO::Experiment;

    types[Markov_IO::Single_Pulses::ClassName()]=new Markov_IO::Single_Pulses;

    types[Markov_IO::Single_Pulses2::ClassName()]=new Markov_IO::Single_Pulses2;

    types[Markov_IO::Trace::ClassName()]=new Markov_IO::Trace;

    types[Markov_IO::Random_Pulses::ClassName()]=new Markov_IO::Random_Pulses;


    types[Markov_IO::Pulses_trace::ClassName()]=new Markov_IO::Pulses_trace;

    types[Markov_IO::ExperimentalData::ClassName()]=new Markov_IO::ExperimentalData;


    types[Markov_Bay::LikelihoodEvaluation::ClassName()]=new Markov_Bay::LikelihoodEvaluation;

    types[Markov_Bay::OptimizationResult::ClassName()]=new Markov_Bay::OptimizationResult;

    types[Markov_Bay::SingleOptimizationResult::ClassName()]=new Markov_Bay::SingleOptimizationResult;

    types[Markov_Bay::PartialLikelihoodEvaluation::ClassName()]=new Markov_Bay::PartialLikelihoodEvaluation;

    types[Markov_Bay::YfitLikelihoodEvaluation::ClassName()]=new Markov_Bay::YfitLikelihoodEvaluation;

    types[Markov_Bay::LikelihoodOptions::ClassName()]=new Markov_Bay::LikelihoodOptions;

    types[Markov_Bay::Markov_Likelihood::Options::ClassName()]=new Markov_Bay::Markov_Likelihood::Options;

    types[Markov_Bay::TerminationByThreshold::Options::ClassName()]=new Markov_Bay::TerminationByThreshold::Options;

    types[Markov_IO::AverageExperiment::Options::ClassName()]=new Markov_IO::AverageExperiment::Options;


    types[Markov_Bay::SimpleOptimization::Options::ClassName()]=new Markov_Bay::SimpleOptimization::Options;

    types[Markov_Mol::SimulationOptions::ClassName()]=new Markov_Mol::SimulationOptions;


    types[Markov_Mol::Q_Markov_Model::ClassName()]=new Markov_Mol::Q_Markov_Model;

    types[Markov_Mol::PatchModel::ClassName()]=new Markov_Mol::PatchModel;

    types[Markov_Mol::gaussian_noise::ClassName()]=new Markov_Mol::gaussian_noise;

    types[Markov_IO::Parameters::ClassName()]=new Markov_Mol::Parameters;


    for (auto it=types.begin(); it!=types.end(); ++it)
    {
        auto sc=it->second->mySuperClass();
        auto c=it->first;
        parent[c]=sc;
        childs[sc].push_back(c);
        autoCmptBySuperClass[sc]=
            Autocomplete({std::string("<")+sc+">"});
        autoCmptByClass[it->second->myClass()]=Autocomplete({std::string("<")+c+">"});

    }

}
}
