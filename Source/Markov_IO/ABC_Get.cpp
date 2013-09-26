#include "Markov_IO/ABC_Get.h"

namespace Markov_IO
{

std::istream& operator>> (std::istream& s,ABC_Get& F)
{
    std::string str;
    return F.get(str,s);
}

ABC_Get::~ABC_Get(){}
}
