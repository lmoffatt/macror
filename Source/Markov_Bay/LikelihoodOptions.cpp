#include "Markov_Bay/LikelihoodOptions.h"

namespace Markov_Bay
{

    LikelihoodOptions::LikelihoodOptions():
	BaseOptions("default")
    {
        push_back("Likelihood_Algorithm",std::string("MacroDR"));
	push_back("averaging",true);
	push_back("zero_guard",true);
	push_back("run_Approximation",false);
	push_back("num_steps",std::size_t(100));
	push_back("num_samples",std::size_t(1000));
    }
    LikelihoodOptions::LikelihoodOptions(const std::string& myname,
                                         const std::string algorithm,
                                         bool isaveraging,
                                         bool zeroGuard,
                                         bool runApproximation,
                                         std::size_t numSteps,
                                         std::size_t numSamples):
      BaseOptions(myname)
    {
      push_back("Likelihood_Algorithm",algorithm);
      push_back("averaging",isaveraging);
      push_back("zero_guard",zeroGuard);
      push_back("run_Approximation",runApproximation);
        push_back("num_steps",numSteps);
        push_back("num_samples",numSamples);
    }

    LikelihoodOptions::LikelihoodOptions(const Markov_IO::ABC_Options& options):
	BaseOptions(options.myName())
    {
        push_back("Likelihood_Algorithm",options.name("Likelihood_Algorithm"));
	push_back("averaging",options.boolean("averaging"));
	push_back("zero_guard",options.boolean("zero_guard"));
	push_back("run_Approximation",options.boolean("run_Approximation"));
	push_back("num_steps",options.count("num_steps"));
	push_back("num_samples",options.count("num_samples"));
    }

    std::string LikelihoodOptions::myClass()const
    {
	return ClassName();
    }

    std::string LikelihoodOptions::ClassName()
    {
	return "Likelihood_Options";
    }

    std::vector<std::string> LikelihoodOptions::parentClasses()
    {
        std::vector<std::string> v;
        v.push_back(Markov_IO::BaseOptions::ClassName());

       return v;

    }

    std::vector<std::string> LikelihoodOptions::childClasses()
    {
        std::vector<std::string> v;
        return v;
    }

     bool LikelihoodOptions::amIAbstract()const
    {
        return false;
    }

     std::vector<std::string>  LikelihoodOptions::myParentClasses()const
    {
        return parentClasses();
    }
     std::vector<std::string>  LikelihoodOptions::myChildClasses()const
    {
        return childClasses();
    }


}
