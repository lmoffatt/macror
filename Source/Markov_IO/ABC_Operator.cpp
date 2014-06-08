#include "Markov_IO/ABC_Operator.h"
#include <fstream>
#include "Markov_IO/AverageExperiment.h"


namespace Markov_IO
{

std::string ABC_Operator::mySuperClass()const
{
    return ClassName();
}

std::string ABC_Operator::ClassName()
{
    return "ABC_Operator";
}



ClassDescription ABC_Operator::GetState()const
{
    return GetDescription();
}

bool ABC_Operator::Save(const std::string& path)
{
    std::ofstream f(path.c_str());
    if(!f) return false;
    f<<this->GetDescription();
    if (!f) return false;
    f.close();
    return true;
}

bool ABC_Operator::Load(const std::string& fileName)
{

    ClassDescription classDes;
    // load the ClassDescription

    std::ifstream f(fileName.c_str());
    if(!f) return false;
    if (!(f>>classDes))
    {
        f.close();
        return false;
    }
    f.close();
    return this->LoadFromDescription(classDes);
}


 bool ABC_Operator::operator ==(const ABC_Operator& other)const
{
    return this->GetDescription()==other.GetDescription();
}


  bool  create(ABC_Operator*& ,const std::string& )
  {
       return false;
  }

  bool LoadFromDescription(ABC_Operator*& ,
               const Markov_IO::ClassDescription& )
  {

      return false;

  }


  ABC_Operator* ABC_Operator::create(const std::string& childClass)
 {
     ABC_Operator* o;
     if (Markov_IO::create(o,childClass))
         return o;
     else
         return 0;
 }





}






