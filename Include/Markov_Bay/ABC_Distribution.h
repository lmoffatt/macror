#ifndef ABC_DISTRIBUTION_H
#define ABC_DISTRIBUTION_H

#include "Markov_Bay/ABC_ParametricDistributable.h"


namespace Markov_Bay_New
{

class ABC_Distribution:public  ABC_ParametricDistributable
{
public:
    virtual std::string mySuperClass()const override;
    static std::string ClassName();

    virtual ~ABC_Distribution();
};



}

#endif // ABC_DISTRIBUTION_H
