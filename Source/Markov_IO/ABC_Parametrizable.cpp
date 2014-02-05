#include <Markov_IO/ABC_Parametrizable.h>
#include <Markov_Mol/ABC_MarkovModel.h>
#include <Markov_Bay/ABC_ParametricDistributable.h>
#include <Markov_Mol/ABC_PatchModel.h>
#include <Markov_Mol/ABC_Noise.h>
#include <Markov_IO/Parameters.h>



namespace Markov_IO
{

std::string ABC_Parametrizable::myClass()const
{return ClassName();}
std::string ABC_Parametrizable::ClassName()
{
    return "Parametrizable";
}


 bool  create(ABC_Parametrizable*& v,const std::string& childClass)
 {

     Markov_Mol::ABC_Markov_Model* m;
     if (create(m,childClass))
     {
         v=m;
         return true;
     }
     Markov_Mol::ABC_PatchModel* p;
     if (create(p,childClass))
     {
         v=p;
         return true;
     }
     Markov_Bay::ABC_ParametricDistributable* d;
     if (create(d,childClass))
     {
         v=d;
         return true;
     }
     Markov_Mol::ABC_noise* n;
     if (create(n,childClass))
     {
         v=n;
         return true;
     }
     Markov_IO::Parameters* pa;
     if (create(pa,childClass))
     {
         v=pa;
         return true;
     }
     return false;
 }



 bool LoadFromDescription(ABC_Parametrizable*& v,
              const Markov_IO::ClassDescription& classDesc)

 {

     Markov_Mol::ABC_Markov_Model* m;
     if (LoadFromDescription(m,classDesc))
     {
         v=m;
         return true;
     }
     Markov_Mol::ABC_PatchModel* p;
     if (LoadFromDescription(p,classDesc))
     {
         v=p;
         return true;
     }
     Markov_Bay::ABC_ParametricDistributable* d;
     if (LoadFromDescription(d,classDesc))
     {
         v=d;
         return true;
     }
     Markov_Mol::ABC_noise* n;
     if (LoadFromDescription(n,classDesc))
     {
         v=n;
         return true;
     }
     Markov_IO::Parameters* pa;
     if (LoadFromDescription(pa,classDesc))
     {
         v=pa;
         return true;
     }
     return false;
 }




}
