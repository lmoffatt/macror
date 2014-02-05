#include "Markov_IO/ABC_Operator.h"
#include <fstream>
#include "Markov_IO/AverageExperiment.h"


namespace Markov_IO
{

std::string ABC_Operator::mySuperClass()const
{
    return ClassName();
}

 std::vector<std::string>  ABC_Operator::myParentClasses()const
 {
     return parentClasses();
 }

 std::vector<std::string>  ABC_Operator::myChildClasses()const
 {
     return childClasses();
 }


 bool ABC_Operator::amIAbstract() const
 {
     return true;
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

  std::vector<std::string> ABC_Operator::parentClasses()
 {
     std::vector<std::string> list;
     list.push_back(ABC_Saveable::ClassName());
     return list;

 }
  std::vector<std::string> ABC_Operator::childClasses()
 {

     std::vector<std::string> list;
     list.push_back(AverageExperiment::ClassName());
     return list;


 }

  bool  create(ABC_Operator*& v,const std::string& childClass)
  {
      if (childClass==AverageExperiment::ClassName())
        {
            AverageExperiment* ae;
            ae=new AverageExperiment();
            v=ae;
            return true;
        }
       return false;
  }

  bool LoadFromDescription(ABC_Operator*& v,
               const Markov_IO::ClassDescription& classDesc)
  {

      AverageExperiment* o;
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






