#include <math.h>
#include "Markov_IO/ParametersMoments.h"
#include "Markov_LA/matrixOperators.h"
#include "Markov_LA/matrixMath.h"
#include "Markov_LA/matrixInverse.h"
#include "Markov_LA/matrixInit.h"
#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixAssigmentOp.h"
#include "Markov_LA/matrixAritmetic.h"

namespace Markov_IO
{

namespace
{
std::vector<std::string> operator+(const std::vector<std::string>& name,
				   const std::string& ext){
    std::vector<std::string> name_ext(name);
    for (std::size_t i=0; i<name.size();i++)
	name_ext[i]+=ext;
    return name_ext;
}
std::vector<std::string> operator+(const std::string& ext,
				   const std::vector<std::string>& name){
    std::vector<std::string> ext_name(name.size());
    for (std::size_t i=0; i<name.size();i++)
	ext_name[i]=ext+name[i];
    return ext_name;


}

std::size_t numParFromNumParMoments(std::size_t numPar)
{
    std::size_t k=(sqrt(9+8*numPar)-3)/2;
    if (k*(k+3)/2==numPar)
	return k;
    else return 0;

}


}

ParametersMoments* ParametersMoments::clone()const{
    return new ParametersMoments(*this);

}
ParametersMoments* ParametersMoments::create()const{
    return new ParametersMoments();
}


int ParametersMoments::apply_parameters(const Parameters& p){
    int nusedPar=0;
    if (allmoments_.size()==0)
    {
	std::size_t n=numParFromNumParMoments(p.size());
	if (n==0) return nusedPar;
	Markov_LA::M_Matrix<double> cov_new(n,n);
	Markov_LA::M_Matrix<double> corrcoef(Markov_LA::zeros<double>(n,n));
	Parameters parameters_new;
	for (std::size_t i=0; i<p.size(); i++)
	{
	    std::string npar=p.Name(i);
	    double d=p[i];
	    TRANSFORMATION tr=p.Transform(i);
	    nusedPar++;
	    if (npar.find("Mean_")==0)
	    {
		parameters_new.push_back(npar.substr(5),d,tr);
	    }
	    else if (npar.find("CoefVar_")==0)
	    {
		std::size_t i=parameters_new.Index(npar.substr(8));
		cov_new(i,i)=pow(log10(d+1),2);
	    }
	    else if (npar.find("SD_")==0)
	    {
		std::size_t i=parameters_new.Index(npar.substr(3));
		cov_new(i,i)=pow(d,2);
	    }
	    else if (npar.find("SDFischer_")==0)
	    {
		std::size_t i=parameters_new.Index(npar.substr(3));
		cov_new(i,i)=pow(d,2);
	    }
	    else if (npar.find("SDSquare_")==0)
	    {
		std::size_t i=parameters_new.Index(npar.substr(3));
		cov_new(i,i)=pow(d,2);
	    }
	    else if (npar.find("CorrCoef_")==0)
	    {
		std::size_t npos0=npar.find_first_of('_');
		std::size_t npos1=npar.find_first_of('_',npos0+1);
		std::string name0=npar.substr(npos0+1,npos1-npos0);
		int i=parameters_new.Index(name0);
		while((i<0)&&(npos1!=npar.npos))
		  {
		    npos1=npar.find_first_of('_',npos1+1);
		    name0=npar.substr(npos0+1,npos1-npos0-1);
		    i=parameters_new.Index(name0);
		  }
		std::size_t j=parameters_new.Index(npar.substr(npos1+1));
		corrcoef(i,j)=d;

	    }
	    else return nusedPar;

	}

	for (std::size_t i=0; i<Markov_LA::nrows(corrcoef);i++)
	{
	    for (std::size_t j=0;j<ncols(corrcoef);j++ )
	    {
		if ((corrcoef(i,j)!=0)&&(i!=j))
		{
		    cov_new(i,j)=corrcoef(i,j)*sqrt(cov_new(i,i)*cov_new(j,j));
		}
	    }
	}
	ParametersMoments tmp(parameters_new,cov_new);
	swap(*this, tmp);
	return nusedPar;

    }
    else
    {
	Markov_LA::M_Matrix<double> corrcoef(Markov_LA::zeros(cov_));
	for (std::size_t i=0; i<p.size(); i++)
	{
	    std::string npar=p.Name(i);
	    double d=p[i];
	    if (allmoments_.HasName(npar))
	    {
		allmoments_[npar]=d;
		nusedPar++;
		if (npar.find("Mean_")==0)
		{
		    (*this)[npar.substr(5)]=d;
		}
		else if (npar.find("CoefVar_")==0)
		{
		    std::size_t i=Index(npar.substr(8));
		    cov_(i,i)=pow(log10(d+1),2);
		}
		else if (npar.find("SD_")==0)
		{
		    std::size_t i=Index(npar.substr(3));
		    cov_(i,i)=pow(d,2);
		}
		else if (npar.find("SDFischer_")==0)
		{
		    std::size_t i=Index(npar.substr(3));
		    cov_(i,i)=pow(d,2);
		}
		else if (npar.find("SDSquare_")==0)
		{
		    std::size_t i=Index(npar.substr(3));
		    cov_(i,i)=pow(d,2);
		}
		else if (npar.find("CorrCoef_")==0)
		{
		    std::size_t npos0=npar.find_first_of('_');
		    std::size_t npos1=npar.find_first_of('_',npos0);
		    std::size_t i=Index(npar.substr(npos0+1,npos1-npos0));
		    std::size_t j=Index(npar.substr(npos1+1));
		    corrcoef(i,j)=d;

		}

	    }
	}
	for (std::size_t i=0; i<Markov_LA::nrows(corrcoef);i++)
	    for (std::size_t j=0;j<ncols(corrcoef);j++ )
	    {
		if ((corrcoef(i,j)!=0)&&(i!=j))
		{
		    cov_(i,j)=corrcoef(i,j)*sqrt(cov_(i,i)*cov_(j,j));
		}
	    }
	cov_inv_=Markov_LA::invSafe(cov_);
	return nusedPar;
    }
}
// object inspectors


/// Returns the parameters of the object
const Parameters& ParametersMoments::get_parameters()const
{
    return allmoments_;
}




Markov_LA::M_Matrix<double> ParametersMoments::transformed_Cov()const{
    return cov_;
}
Markov_LA::M_Matrix<double> ParametersMoments::transformed_CovInv()const{
    return cov_inv_;
}



ParametersMoments::ParametersMoments(const Parameters par,
				     const Markov_LA::M_Matrix<double>& cov,
				     const Markov_LA::M_Matrix<double>& covinv):
    Parameters(par),
    cov_inv_(Markov_LA::size(covinv)>0?covinv:Markov_LA::invSafe(cov)),
    cov_(Markov_LA::size(cov)>0?cov:Markov_LA::invSafe(covinv)),
    allmoments_(par.myName()+"_moments")
{

    for (std::size_t i=0; i<size();i++)
    {
	allmoments_.push_back("Mean_"+Name(i),
			      (*this)[i],
			      Transform(i));

	switch (Transform(i))
	{
	case LOG:
	    allmoments_.push_back("CoefVar_"+Name(i),
				  pow(10,sqrt(transformed_Cov()(i,i)))-1.0,
				  Parameters::LINEAR);
	    break;
	case FISHER:
	    allmoments_.push_back("SDFisher_"+Name(i),
				  sqrt(transformed_Cov()(i,i)),
				  Parameters::SQUARE);
	    break;
	case SQUARE:
	    allmoments_.push_back("SDSquare_"+Name(i),
				  sqrt(transformed_Cov()(i,i)),
				  Parameters::SQUARE);
	    break;

	case ERROR:
	case LINEAR:
	default:
	    allmoments_.push_back("SD_"+Name(i),
				  sqrt(transformed_Cov()(i,i)),
				  Parameters::SQUARE);
	}
    }
    for (std::size_t i=0; i<size();i++)
	for (std::size_t j=i+1; j<size();++j)
	    allmoments_.push_back("CorrCoef_"+Name(i)+"_"+Name(j),
				  cov_(i,j)/sqrt(cov_(i,i)*cov_(j,j)),
				  Parameters::FISHER);
    }


ParametersMoments::ParametersMoments():
    Parameters(),
    cov_inv_(),
    cov_(),
    allmoments_(){}

ParametersMoments::ParametersMoments(const ParametersMoments& other):
    Parameters(other),
    cov_inv_(other.cov_inv_),
    cov_(other.cov_),
    allmoments_(other.allmoments_){}

ParametersMoments& ParametersMoments::operator=(const ParametersMoments& other)
{
    if (this!=&other)
    {
	ParametersMoments tmp(other);
	swap(*this,tmp);

    }

    return *this;
}

void swap(ParametersMoments& one, ParametersMoments& other)
{
   Parameters* oneP=&one;
   Parameters* otherP=&other;
   swap(*oneP,*otherP);
   swap(one.cov_inv_,other.cov_inv_);
   swap(one.cov_,other.cov_);
   swap(one.allmoments_,other.allmoments_);
}



ClassDescription ParametersMoments::GetDescription()const
{
    return allmoments_.GetDescription();
}
bool ParametersMoments::LoadFromDescription(const ClassDescription& classDes)
{

    if (allmoments_.LoadFromDescription(classDes))
    {
	apply_parameters(allmoments_);
	return true;
    }
    else
	return false;

}

std::string ParametersMoments::ClassName(){
    return "Parameters_Moments";
}


std::vector<std::string> ParametersMoments::parentClasses()
{
    std::vector<std::string> v;
    v.push_back(Markov_IO::Parameters::ClassName());

   return v;

}

std::vector<std::string> ParametersMoments::childClasses()
{
    std::vector<std::string> v;
    return v;
}

 bool ParametersMoments::amIAbstract()const
{
    return false;
}

 std::vector<std::string>  ParametersMoments::myParentClasses()const
{
    return parentClasses();
}
 std::vector<std::string>  ParametersMoments::myChildClasses()const
{
    return childClasses();
}





std::string ParametersMoments::myName()const{
    return Parameters::myName()+"_Moments";

}
std::string ParametersMoments::myClass()const{
    return ClassName();
}

std::istream& operator>> (std::istream& stream,ParametersMoments*& x)
{
    ClassDescription classDes;
    stream>>classDes;
    if (stream.good())
	if(!x->LoadFromDescription(classDes))
	    stream.setstate(stream.rdstate() | std::ios_base::failbit);
    return stream;
}



//precondition: homologous parameters
 ParametersMoments ParametersMoments::getMoments(const std::vector<ABC_Parametrizable*>& samples)
{
  if (samples.empty())
    return ParametersMoments();
  ABC_Parametrizable* s=samples[0];
  Parameters p=s->get_parameters();
  std::size_t n=p.size();

  Markov_LA::M_Matrix<double> sumx(n,1);
  Markov_LA::M_Matrix<double> sumxx(n,n);

  for (std::size_t i=0; i<samples.size(); ++i)
    {
      p=samples[i]->get_parameters();
      sumx+=p.transformed_values();
      sumxx+=Markov_LA::multTransp(p.transformed_values(),p.transformed_values());
    }
  Markov_LA::M_Matrix<double> mean=sumx/(1.0*samples.size());
  Markov_LA::M_Matrix<double> cov=sumxx/(1.0*samples.size())-Markov_LA::multTransp(mean,mean);
  p.transformed_values(mean);

  ParametersMoments result(p,cov);
  return result;


}

 ParametersMoments ParametersMoments::getMoments(const std::vector<Parameters>& samples)
{
  if (samples.empty())
    return ParametersMoments();
  Parameters p=samples[0];
  std::size_t n=p.size();

  Markov_LA::M_Matrix<double> sumx(n,1);
  Markov_LA::M_Matrix<double> sumxx(n,n);

  for (std::size_t i=0; i<samples.size(); ++i)
    {
      p=samples[i];
      sumx+=p.transformed_values();
      sumxx+=Markov_LA::multTransp(p.transformed_values(),p.transformed_values());
    }
  Markov_LA::M_Matrix<double> mean=sumx/(1.0*samples.size());
  Markov_LA::M_Matrix<double> cov=sumxx/(1.0*samples.size())-Markov_LA::multTransp(mean,mean);
  p.transformed_values(mean);

  ParametersMoments result(p,cov);
  return result;


}




}

