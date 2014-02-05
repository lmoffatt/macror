#include "Markov_IO/Options.h"
#include "Markov_IO/auxiliarIO.h"
#include <Markov_Bay/LikelihoodOptions.h>
#include <Markov_Bay/MarkovLikelihood.h>
#include <Markov_Bay/Optimization_Step_BFGS.h>
#include <Markov_Bay/SimpleOptimization.h>
#include <Markov_Bay/TerminationByThreshold.h>
#include <Markov_Mol/SimulationOptions.h>
#include "Markov_IO/AverageExperiment.h"





namespace Markov_IO
{
BaseOptions* BaseOptions::clone() const
{
    return new BaseOptions(*this);
}
/// default constructors

BaseOptions* BaseOptions::create() const
{
    return new BaseOptions();
}



std::vector<std::string> BaseOptions::parentClasses()
{
    std::vector<std::string> v;
    v.push_back(Markov_IO::ABC_Options::ClassName());

   return v;

}

std::vector<std::string> BaseOptions::childClasses()
{
    std::vector<std::string> v;
    v.push_back(Markov_Bay::LikelihoodOptions::ClassName());
    v.push_back(Markov_Bay::Markov_Likelihood::Options::ClassName());
    v.push_back(Markov_Bay::OptimizationStepBFGS::Options::ClassName());
    v.push_back(Markov_Bay::SimpleOptimization::Options::ClassName());
    v.push_back(Markov_Bay::TerminationByThreshold::Options::ClassName());
    v.push_back(Markov_Mol::SimulationOptions::ClassName());
   return v;
}

 bool BaseOptions::amIAbstract()const
{
    return false;
}

 std::vector<std::string>  BaseOptions::myParentClasses()const
{
    return parentClasses();
}
 std::vector<std::string>  BaseOptions::myChildClasses()const
{
    return childClasses();
}



ClassDescription BaseOptions::GetDescription()const
{
    ClassDescription desc(myClass(),mySuperClass());

    desc.push_back("name",name_);

    for (std::map<std::string,bool>::const_iterator it=booleans_.begin();
	 it!=booleans_.end();++it)
    {
        std::string tip;
        std::string whathis;
        if (tips_.find(it->first)!=tips_.end())
            tip=tips_.find(it->first)->second;
        else
            tip="";
        if (whatThis_.find(it->first)!=whatThis_.end())
            whathis=whatThis_.find(it->first)->second;
        else
            whathis="";
        desc.push_back(it->first,it->second,tip,whathis);
    }
    for (std::map<std::string,std::size_t>::const_iterator it=counts_.begin();
	 it!=counts_.end();++it)
    {
        std::string tip;
        std::string whathis;
        if (tips_.find(it->first)!=tips_.end())
            tip=tips_.find(it->first)->second;
        else
            tip="";
        if (whatThis_.find(it->first)!=whatThis_.end())
            whathis=whatThis_.find(it->first)->second;
        else
            whathis="";
        desc.push_back(it->first,it->second,tip,whathis);
    }
    for (std::map<std::string,double>::const_iterator it=reals_.begin();
	 it!=reals_.end();++it)
    {
        std::string tip;
        std::string whathis;
        if (tips_.find(it->first)!=tips_.end())
            tip=tips_.find(it->first)->second;
        else
            tip="";
        if (whatThis_.find(it->first)!=whatThis_.end())
            whathis=whatThis_.find(it->first)->second;
        else
            whathis="";
        desc.push_back(it->first,it->second,tip,whathis);
    }
    for (std::map<std::string,std::string>::const_iterator it=names_.begin();
	 it!=names_.end();++it)
    {
        std::string tip;
        std::string whathis;
        if (tips_.find(it->first)!=tips_.end())
            tip=tips_.find(it->first)->second;
        else
            tip="";
        if (whatThis_.find(it->first)!=whatThis_.end())
            whathis=whatThis_.find(it->first)->second;
        else
            whathis="";
        desc.push_back(it->first,it->second,tip,whathis);
    }
    return desc;
}
bool BaseOptions::LoadFromDescription(const ClassDescription& classDes){
    if (classDes.ClassName()!=myClass())
	return false;
    std::string name;
    if (!ToValue(classDes["name"],name))
	return false;
    for (std::map<std::string,bool>::iterator it=booleans_.begin();
	 it!=booleans_.end();++it)
	if (!ToValue(classDes[it->first],it->second))
	    return false;
    for (std::map<std::string,std::size_t>::iterator it=counts_.begin();
	 it!=counts_.end();++it)
	if (!ToValue(classDes[it->first],it->second))
	    return false;
    for (std::map<std::string,double>::iterator it=reals_.begin();
	 it!=reals_.end();++it)
	if (!ToValue(classDes[it->first],it->second))
	    return false;
    for (std::map<std::string,std::string>::iterator it=names_.begin();
	 it!=names_.end();++it)
	if (!ToValue(classDes[it->first],it->second))
	    return false;
    name_=name;
    return true;
}

void BaseOptions::push_back(const std::string& option,bool abool)
{
    booleans_[option]=abool;
 }
void BaseOptions::push_back(const std::string& option,std::size_t acount)
{ counts_[option]=acount;}
void BaseOptions::push_back(const std::string& option,double areal)
{ reals_[option]=areal;}
void BaseOptions::push_back(const std::string& option,const std::string& astring)
{ names_[option]=astring;}

void BaseOptions::push_back(const std::string& option,bool abool,const std::string& tip, const std::string& whatThis)
{
    booleans_[option]=abool;
    tips_[option]=tip;
    whatThis_[option]=whatThis;
 }
void BaseOptions::push_back(const std::string& option,std::size_t acount,const std::string& tip, const std::string& whatThis)
{ counts_[option]=acount;
    tips_[option]=tip;
    whatThis_[option]=whatThis;
}
void BaseOptions::push_back(const std::string& option,double areal,const std::string& tip, const std::string& whatThis)
{ reals_[option]=areal; tips_[option]=tip;
    whatThis_[option]=whatThis;
 }
void BaseOptions::push_back(const std::string& option,const std::string& astring,const std::string& tip, const std::string& whatThis)
{ names_[option]=astring; tips_[option]=tip;
    whatThis_[option]=whatThis;
 }


std::string BaseOptions::ClassName()
{return "options";}
 std::string BaseOptions::myName()const
{return name_;}
 std::string BaseOptions::myClass()const
{return ClassName();}




 bool BaseOptions::boolean(const std::string& option)const
{
    if (booleans_.find(option)!=booleans_.end())
	return booleans_.find(option)->second;
    else return false;
};
  std::size_t BaseOptions::count(const std::string& option)const
{
    if (counts_.find(option)!=counts_.end())
	return counts_.find(option)->second;
    else return 0;
};
 double  BaseOptions::real(const std::string& option)const
{
    if (reals_.find(option)!=reals_.end())
	return reals_.find(option)->second;
    else return 0.0;
};
 std::string BaseOptions::name(const std::string& option)const
{
    if (names_.find(option)!=names_.end())
	return names_.find(option)->second;
    else return "";
};

  bool BaseOptions::set(const std::string& option,bool abool)
{
    if (booleans_.find(option)!=booleans_.end())
    {
	booleans_[option]=abool;
	return true;
    }
    else return false;
}

  bool BaseOptions::set(const std::string& option,std::size_t acount)
{
    if (counts_.find(option)!=counts_.end())
    {    counts_[option]=acount;
	return true;
    }
    else return false;
}


  bool BaseOptions::set(const std::string& option,double areal)
{
    if (reals_.find(option)!=reals_.end())
    {
	reals_[option]=areal;
	return true;
    }
    else return false;
}

  bool BaseOptions::set(const std::string& option,std::string astring)
{
    if (names_.find(option)!=names_.end())
    {
	names_[option]=astring;
	return true;
    }
    else return false;
}


  BaseOptions& BaseOptions::operator+=(const BaseOptions& other)
  {
      name_=name_+"_"+other.name_;
      booleans_.insert(other.booleans_.begin(),other.booleans_.end());
      counts_.insert(other.counts_.begin(),other.counts_.end());
      reals_.insert(other.reals_.begin(),other.reals_.end());
      names_.insert(other.names_.begin(),other.names_.end());
      return *this;
  }





  BaseOptions::BaseOptions(const BaseOptions& other):
      name_(other.name_),
      booleans_(other.booleans_),
      counts_(other.counts_),
      reals_(other.reals_),
      names_(other.names_)
  {}


  BaseOptions& BaseOptions::operator=(const BaseOptions& other)
  {
      if (this!=&other)
      {
	  BaseOptions tmp(*this);
	  swap(tmp,*this);
      }
      return *this;
  }

  void swap(BaseOptions& one,BaseOptions& other)
  {
  std::swap(one.name_,other.name_);
  std::swap(one.booleans_,other.booleans_);
  std::swap(one.counts_,other.counts_);
  std::swap(one.reals_,other.reals_);
  std::swap(one.names_,other.names_);
    }




  BaseOptions::BaseOptions(const std::string& name):
	name_(name),
	booleans_(),
	counts_(),
	reals_(),
	names_()
    {}

    BaseOptions::BaseOptions():
	name_(),
	booleans_(),
	counts_(),
	reals_(),
	names_()
    {}


    BaseOptions::~BaseOptions(){}




    bool LoadFromDescription(BaseOptions*& e,
                 const ClassDescription& classDes)
    {
        if (create(e,classDes.ClassName()))
            return e->LoadFromDescription(classDes);
        else return false;
    }


    bool  create(BaseOptions*& e,const std::string& childClass)
    {
        if (childClass==Markov_Bay::LikelihoodOptions::ClassName())
        {
            e=new Markov_Bay::LikelihoodOptions;
            return true;
        }
        else if (childClass==Markov_Bay::Markov_Likelihood::Options::ClassName())
        {
            e=new Markov_Bay::Markov_Likelihood::Options;
            return true;
        }
        else if (childClass==Markov_IO::AverageExperiment::Options::ClassName())
        {
            e=new Markov_IO::AverageExperiment::Options;
            return true;
        }
        else if (childClass==Markov_Bay::OptimizationStepBFGS::Options::ClassName())
        {
            e=new Markov_Bay::OptimizationStepBFGS::Options;
            return true;
        }
        else if (childClass==Markov_Bay::SimpleOptimization::Options::ClassName())
        {
            e=new Markov_Bay::SimpleOptimization::Options;
            return true;
        }
        else if (childClass==Markov_Bay::TerminationByThreshold::Options::ClassName())
        {
            e=new Markov_Bay::TerminationByThreshold::Options;
            return true;
        }
        else if (childClass==Markov_Mol::SimulationOptions::ClassName())
        {
            e=new Markov_Mol::SimulationOptions;
            return true;
        }
        else if (childClass==BaseOptions::ClassName())
        {
            e=new BaseOptions;
            return true;
        }
        else
            return false;
    }

    std::istream& operator>> (std::istream& stream,BaseOptions*& x)
    {
        ClassDescription classDes;
        stream>>classDes;
        if (stream.good())
        if(!LoadFromDescription(x,classDes))
            stream.setstate(stream.rdstate() | std::ios_base::failbit);
        return stream;
    }






    }



