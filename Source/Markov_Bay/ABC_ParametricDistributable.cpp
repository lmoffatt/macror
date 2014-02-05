#include "Markov_Bay/ABC_ParametricDistributable.h"
#include "Markov_Bay/ABC_Distribution.h"

namespace Markov_Bay
{



ABC_ParametricDistributable::~ABC_ParametricDistributable(){}


std::string ABC_ParametricDistributable::myClass()const
{return ClassName();}
std::string ABC_ParametricDistributable::ClassName()
{return "Parametric_Distributable";}


 bool  create(ABC_ParametricDistributable*& v,const std::string& childClass)
 {
     ABC_Distribution* d;
     if (create(d,childClass))
     {
         v=d;
         return true;
     }
     return false;
 }


 bool LoadFromDescription(ABC_ParametricDistributable*& v,
              const Markov_IO::ClassDescription& classDesc)
 {
     ABC_Distribution* d;
     if (LoadFromDescription(d,classDesc))
     {
         v=d;
         return true;
     }
     return false;

 }


}
