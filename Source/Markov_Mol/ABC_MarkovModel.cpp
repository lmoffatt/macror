#include "Markov_Mol/ABC_MarkovModel.h"
#include "Markov_Mol/QMarkovModel.h"


namespace Markov_Mol
{

std::string num_channels_label()
{
    return "Number_of_channels";
}



std::string ABC_Markov_Model::mySuperClass()const
{
    return ClassName();
}

std::string ABC_Markov_Model::ClassName()
{
    return "Channel_Model";
}



std::vector<std::string> ABC_Markov_Model::parentClasses()
{
    std::vector<std::string> v;
    v.push_back(Markov_IO::ABC_Parametrizable::ClassName());

   return v;

}

std::vector<std::string> ABC_Markov_Model::childClasses()
{
    std::vector<std::string> v;
    v.push_back(Markov_Mol::Q_Markov_Model::ClassName());

    return v;
}

 bool ABC_Markov_Model::amIAbstract()const
{
    return true;
}

 std::vector<std::string>  ABC_Markov_Model::myParentClasses()const
{
    return parentClasses();
}
 std::vector<std::string>  ABC_Markov_Model::myChildClasses()const
{
    return childClasses();
}




inline bool operator==(const ABC_Markov_Model& x,
		       const ABC_Markov_Model& y)
{
    if (!(x.k()==y.k())) return false;
    if (!((x.Q0()==y.Q0()))) return false;
    if (!((x.Q1()==y.Q1()))) return false;
    if (!(x.g()==y.g())) return false;
    return true;
}


bool  create(ABC_Markov_Model*& model,const std::string& childClass)

{
    if (childClass==Q_Markov_Model::ClassName())
   {
       Q_Markov_Model* m;
       m=new Q_Markov_Model();
       model=m;
       return true;
   }
	return false;

}

bool LoadFromDescription(ABC_Markov_Model*& model,
                         const Markov_IO::ClassDescription& classDes)
{
    if (create(model,classDes.ClassName()))
        return model->LoadFromDescription(classDes);
    return false;
}

bool LoadFromStringDescription(ABC_Markov_Model*& model,
                         const Markov_IO::ClassDescription& classDes)
{
    if (create(model,classDes.ClassName()))
        return model->LoadFromStringDescription(classDes);
    return false;
}



std::istream& operator>> (std::istream& stream,ABC_Markov_Model*& x)
{
    ClassDescription classDes;
    stream>>classDes;
    if (stream.good())
	if(!LoadFromDescription(x,classDes))
	    stream.setstate(stream.rdstate() | std::ios_base::failbit);
    return stream;
}






}
