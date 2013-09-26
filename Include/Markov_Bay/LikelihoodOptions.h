#ifndef LIKELIHOODOPTIONS_H
#define LIKELIHOODOPTIONS_H
#include "Markov_IO/Options.h"

namespace Markov_Bay
{

class LikelihoodOptions:public Markov_IO::BaseOptions
{
public:
    LikelihoodOptions();
    LikelihoodOptions(const std::string& myname,
		      const std::string algorithm,
		      bool isaveraging,
		      bool zeroGuard,
		      bool runApproximation=false,
		      std::size_t numSteps=100,
		      std::size_t numSamples=1000);
    LikelihoodOptions(const Markov_IO::ABC_Options& options);
    virtual std::string myClass()const;
    static std::string ClassName();

    static std::vector<std::string> parentClasses();
    static std::vector<std::string> childClasses();
    virtual bool amIAbstract()const;
    virtual std::vector<std::string>  myParentClasses()const;
    virtual std::vector<std::string>  myChildClasses()const;



};


}

#endif // LIKELIHOODOPTIONS_H
