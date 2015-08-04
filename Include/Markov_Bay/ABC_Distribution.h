#ifndef ABC_DISTRIBUTION_H
#define ABC_DISTRIBUTION_H

#include "Markov_Bay/ABC_ParametricDistributable.h"


namespace Markov_Bay
{

class ABC_Distribution:public  ABC_ParametricDistributable
{
public:
    virtual std::string mySuperClass()const override;
    static std::string ClassName();

    virtual ~ABC_Distribution();
};



bool LoadFromDescription(ABC_Distribution*& distribution,
			 const Markov_IO::ClassDescription& classDes);

std::istream& operator>> (std::istream& stream,ABC_Distribution*& distribution);

bool  create(ABC_Distribution*& d,const std::string& childClass);

}

#endif // ABC_DISTRIBUTION_H
