#ifndef LIKELIHOODOPTIONS_H
#define LIKELIHOODOPTIONS_H

#include <string>
namespace Markov_Bay_New
{

class LikelihoodOptions
{
public:
    LikelihoodOptions();
    LikelihoodOptions(const std::string& myname,
                      const std::string& algorithm,
		      bool isaveraging,
		      bool zeroGuard,
		      bool runApproximation=false,
		      std::size_t numSteps=100,
		      std::size_t numSamples=1000);
    virtual std::string myClass()const;
    static std::string ClassName();




};


}

#endif // LIKELIHOODOPTIONS_H
