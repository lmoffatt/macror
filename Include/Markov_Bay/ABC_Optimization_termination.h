#ifndef ABC_OPTIMIZATION_TERMINATION_H
#define ABC_OPTIMIZATION_TERMINATION_H
#include "Markov_Bay/ABC_Optimization_step.h"

namespace Markov_Bay_New
{
class ABC_OptimizationTermination
{
 public:
	virtual ABC_OptimizationTermination* clone()const=0;
	virtual ABC_OptimizationTermination* create()const=0;

    virtual ~ABC_OptimizationTermination();
    virtual std::string Message()const=0;

    virtual bool operator()(const ABC_OptimizationStep& step)=0;

 };

}


#endif // ABC_OPTIMIZATION_TERMINATION_H
