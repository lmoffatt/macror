#include "Markov_IO/Parameters.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_LA/auxiliarMath.h"
#include "Markov_IO/ParametersMoments.h"
#include "Markov_LA/auxiliarRelational.h"
#include <math.h>
namespace Markov_IO
{
using Markov_LA::M_Matrix;

namespace
{
std::vector<double> vectorize(const Markov_LA::M_Matrix<double>& x)
{
    std::vector<double> v(size(x));
    for (std::size_t i=0; i<size(x);++i)
	v[i]=x[i];
    return v;

}
}

ClassDescription Parameters::GetDescription()const
{
    ClassDescription desc(myClass(),mySuperClass());

    desc.push_back("name",name_);

    for (std::size_t i=0; i<this->values_vec.size(); ++i)
    {
	desc.push_back(name_vec[i],values_vec[i]);
	desc.push_back(name_vec[i]+"_transformation",
		       TransfLabel[trans_vec[i]]);
    }

    return desc;
}
bool Parameters::LoadFromDescription(const ClassDescription& classDes)
{
    if (classDes.ClassName()!=myClass())
	return false;
    std::string name;
    Parameters tmp(*this);
    if (!ToValue(classDes["name"],tmp.name_))
	return false;
    if (size()==0)
    {
	for (std::size_t i=0; i<classDes.size(); ++i)
	{
	    std::string elementName=classDes.ElementName(i);
	    if ((elementName!="name")&&
		    (elementName.find("transformation")==elementName.npos))
	    {
		std::string valueString;
		if (!ToValue(classDes[elementName],valueString))
		    return false;
		double value;
		if (!ToValue(valueString,value))
		    return false;
		std::string transfLabel;
		if (!ToValue(classDes[elementName+"_transformation"],
			     transfLabel))
		    return false;
		TRANSFORMATION transformation;
		if (LabelTransf.find(transfLabel)!=LabelTransf.end())
		    transformation=(*LabelTransf.find(transfLabel)).second;
		else
		    return false;
		tmp.push_back(elementName,value,transformation);
	    }
	}
    }
    else
    {
	for (std::size_t i=0; i<name_vec.size(); ++i)
	{
	    std::string valueString;
	    if (!ToValue(classDes[name_vec[i]],valueString))
		return false;
	    double value;
	    if (!ToValue(valueString,value))
		return false;

	    std::string transfLabel;
	    if (!ToValue(classDes[name_vec[i]+"_transformation"],
			 transfLabel))
		return false;
	    TRANSFORMATION transformation;
	    if (LabelTransf.find(transfLabel)!=LabelTransf.end())
		transformation=(*LabelTransf.find(transfLabel)).second;
	    else
		return false;
	    tmp.push_back(name_vec[i],value,transformation);

	}
    }
    swap(*this,tmp);
    return true;


}

const std::string Parameters::TransfLabel []=
{"LINEAR","LOG","SQUARE","FISHER","ERROR"};

std::string Parameters::ClassName()
{
    return "Parameters";
}

std::string Parameters::myName()const
{return name_;
}
std::string Parameters::myClass()const
{
    return ClassName();
}

std::string Parameters::mySuperClass()const
{
    return ClassName();
}


std::map<std::string, Parameters::TRANSFORMATION> Parameters::LabelTransf=Parameters::create_LabelTransf();

std::map<std::string, Parameters::TRANSFORMATION> Parameters::create_LabelTransf()
{
    std::map<std::string, TRANSFORMATION> m;
    for (std::size_t i=0; i<ERROR; i++)
	m[TransfLabel[i]]=TRANSFORMATION(i);
    return m;
}







Parameters* Parameters::clone() const
{
    return new Parameters(*this);
}
/// default constructors

Parameters* Parameters::create() const
{
    return new Parameters();
}

/// Apply the matching parameters
int Parameters::apply_parameters(const Parameters& p)
{
    int numPar=0;

    for (std::size_t i=0; i<p.size(); ++i)
    {
	if (this->HasName(p.Name(i)))
	{
	    (*this)[p.Name(i)]=p[i];
	    numPar++;
	}
    }
    return numPar++;
}
// object inspectors


/// Returns the parameters of the object
const Parameters& Parameters::get_parameters()const
{
    return *this;
}




Parameters::~Parameters() {}



Parameters::Parameters(const std::string& name,
		       const std::vector<std::string>& names,
		       const Markov_LA::M_Matrix<double>& values,
		       const std::vector<Parameters::TRANSFORMATION> transf
		       ):
    name_(name),
    values_vec(vectorize(values)),
    name_vec(names),
    name_map(name_map_build(names)),
    trans_vec(transf.size()>0?transf :
			      std::vector<TRANSFORMATION>(names.size(),LOG))

{}

Parameters::Parameters(const Parameters&other):
    name_(other.name_),
    values_vec(other.values_vec),
    name_vec(other.name_vec),
    name_map(other.name_map),
    trans_vec(other.trans_vec)
{}

Parameters::Parameters():
    name_(),
    values_vec(),
    name_vec(),
    name_map(),
    trans_vec(){}

Parameters::Parameters(const std::string& name):
    name_(name),
    values_vec(),
    name_vec(),
    name_map(),
    trans_vec()

{}




Parameters& Parameters::operator=(const Parameters& other)
{
    if (this!=&other)
    {
	Parameters tmp(other);
	swap(tmp,*this);
    };
    return *this;
}

void swap(Parameters& one, Parameters& two)
{

    std::swap(one.name_,two.name_);
    std::swap(one.values_vec,two.values_vec);
    std::swap(one.name_vec,two.name_vec);
    std::swap(one.name_map,two.name_map);
    std::swap(one.trans_vec,two.trans_vec);
}



Markov_LA::M_Matrix<double> Parameters::transformed_values()const
{
    Markov_LA::M_Matrix<double> v(values_vec.size(),1);
    for (std::size_t i=0;i<values_vec.size();++i)
	switch (this->trans_vec[i])
	{
	case LOG:
	    v[i]=log10(values_vec[i]);
	    break;
	case FISHER:
	    v[i]=0.5*log((1+values_vec[i])/(1-values_vec[i]));
	case SQUARE:
	    v[i]=values_vec[i]*values_vec[i];
	case LINEAR:
	case ERROR:
	default:
	    v[i]=values_vec[i];
	    break;
	}
    return v;
}

Parameters& Parameters::transformed_values(const Markov_LA::M_Matrix<double>& new_values)
{

    for (std::size_t i=0;i<values_vec.size();++i)
	switch (this->trans_vec[i])
	{
	case LOG:
	    values_vec[i]=pow(10,new_values[i]);
	    break;
	case FISHER:
	    values_vec[i]=(exp(2*new_values[i])-1)/(exp(2*new_values[i])+1);
	    break;
	case SQUARE:
	    values_vec[i]=sqrt(new_values[i]);
	    break;

	case LINEAR:
	case ERROR:
	default:
	    values_vec[i]=new_values[i];
	    break;
	}
    return *this;
}





/***
*   It access the value of the named parameter.
*   @pre \p the parameter already exists, otherwise error
*   @warning  NO NAME CHECKING!!!
*   @return  (*this)[name]
*/
double& Parameters::operator[](std::string s /**<  name of the parameter*/)
{
    return values_vec[name_map[s]];
}

const double& Parameters::operator[](std::string s /**<  name of the parameter*/) const
{

    return values_vec[(*name_map.find(s)).second];

}


double & Parameters::operator[] (std::size_t i /**<  index of the parameter*/ )
{
    return values_vec[i];
}

const double& Parameters::operator[]  (std::size_t i)const
{
    return values_vec[i];
}

std::string Parameters::Name(std::size_t i) const
{
    return name_vec[i];
}



int Parameters::Index(const std::string& name) const
{
    std::map<std::string,std::size_t>::const_iterator it=name_map.find(name);
    if (it!=name_map.end())
	return it->second;
    else
	return -1;
}

bool Parameters::push_back(std::string s, double x, TRANSFORMATION tr)
{
    if (HasName(s))
    {
	(*this)[s]=x;
	Transform(s,tr);
	return true;
    }
    else
    {
	values_vec.push_back(x);
	name_vec.push_back(s);
	trans_vec.push_back(tr);
	name_map[s]=values_vec.size()-1;
	return false;
    }
}


Parameters& Parameters::Erase(std::string s)
{
    if (HasName(s))
    {
	values_vec.erase(values_vec.begin()+name_map[s]);
	name_vec.erase(name_vec.begin()+name_map[s]);
	trans_vec.erase(trans_vec.begin()+name_map[s]);
	name_map.erase(s);
    };
    return *this;
}



bool Parameters::HasName(std::string s) const
{
    return  (this->name_map.find(s)!=name_map.end());
}


std::size_t Parameters::size()const
{
    return values_vec.size();
}


Parameters& Parameters::operator+=(const Parameters& other)
{
    for (std::size_t i=0; i<other.size(); ++i)
    {
	if (!HasName(other.Name(i)))
	    push_back(other.Name(i),other[i],other.Transform(i));
    }
    return *this;
}


std::map<std::string, std::size_t>
name_map_build(const std::vector<std::string>& names)
{
    std::map<std::string, std::size_t> m;
    for (std::size_t i=0; i<names.size();++i)
	m[names[i]]=i;
    return m;
}

std::istream& operator>> (std::istream& stream,Parameters*& x)
{
    ClassDescription classDes;
    stream>>classDes;
    if (stream.good())
	if(!LoadFromDescription(x,classDes))
	    stream.setstate(stream.rdstate() | std::ios_base::failbit);
    return stream;
}


bool Parameters::isValid()const
{
  for (std::size_t i=0; i<values_vec.size(); i++)
    {
      if (!Markov_LA::isFinite(values_vec[i]))
        return false;
    }
  return true;
}


Parameters::TRANSFORMATION Parameters::Transform(std::string s)const
{
    return trans_vec[(*name_map.find(s)).second];
}
Parameters& Parameters::Transform(std::string s,Parameters::TRANSFORMATION tr)
{
    trans_vec[name_map[s]]=tr;
    return *this;
}

Parameters::TRANSFORMATION Parameters::Transform(std::size_t i)const
{
    return trans_vec[i];
}
Parameters& Parameters::Transform(std::size_t i,Parameters::TRANSFORMATION tr)
{
    trans_vec[i]=tr;
    return *this;
}





bool  create(Parameters*& par,const std::string& childClass)

{
    if (childClass==Parameters::ClassName())
    {
	Parameters* p;
	p=new Parameters();
	par=p;
	return true;
    }
    else  if (childClass==ParametersMoments::ClassName())
    {
	ParametersMoments* p;
	p=new ParametersMoments();
	par=p;
	return true;
    }

    else
	return false;

}




bool LoadFromDescription(Parameters*& parameters,
			 const Markov_IO::ClassDescription& classDes)
{
    if (create(parameters,classDes.ClassName()))
	return parameters->LoadFromDescription(classDes);
    return false;
}


// two Parameters are the same if they have the same set of Names,
// the same set of values and the same set of scales
// however they can differ in the order of the names
bool operator==(const Parameters& one, const Parameters& two)
{
    if (one.size()!=two.size())
	return false;
    for (std::size_t i=0; i<one.size(); i++)
    {
	// the order of the parameters is not considered in the equality
	// operator
	if (!two.HasName(one.Name(i)))
	    return false;
	if (two[one.Name(i)]!=one[i])
	    return false;
	if (two.Transform(one.Name(i))!=one.Transform(i))
	    return false;
    }
    return true;

}


}



