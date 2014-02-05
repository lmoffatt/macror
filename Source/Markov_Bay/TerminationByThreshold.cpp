#include "Markov_Bay/TerminationByThreshold.h"
#include "Markov_LA/matrixMaxMin.h"


namespace Markov_Bay
{
TerminationByThreshold* TerminationByThreshold::clone()const{
    return new TerminationByThreshold(*this);

}
TerminationByThreshold* TerminationByThreshold::create()const{
    return new TerminationByThreshold();
}

TerminationByThreshold::~TerminationByThreshold(){}

std::ostream& TerminationByThreshold::put(std::ostream & s) const{return s;}


bool TerminationByThreshold::operator()(const ABC_OptimizationStep& step)
{
    termination_.clear();
    if (std::abs(Markov_LA::norm_inf(step.SearchDirection()))<resolution_in_x_)
    {
	termination_+="Search Direction is less than the Parameters Resolution.\n";
    };
    if (std::abs(step.ExpectedLogLikelihoodChange())<resolution_in_LogL_)
    {
	termination_+="The Expected reduction in LogLikelihood is less than"
		"the LogLikelihood resolution. \n";
    };
    if(std::abs(step.AdaptiveStepLength())<resolution_in_step_)
    {
	termination_+="The Step Length is less than its resolution.\n";
    };
    if (Markov_LA::norm_inf(step.Score())<resolution_in_gradient_)
    {
	termination_+="Gradient is less than its resolution. \n";
    };
    if (termination_.empty())
	return false;
    else
	return true;
}



std::string TerminationByThreshold::Message()const
{
    return termination_;
}


TerminationByThreshold::TerminationByThreshold()
{
    Options o;
    TerminationByThreshold tmp(o);
    swap(tmp,*this);
}



TerminationByThreshold::TerminationByThreshold(const Markov_IO::ABC_Options& O):
    resolution_in_LogL_(O.real("resolution_in_LogL")),
    resolution_in_x_(O.real("resolution_in_x")),
    resolution_in_step_(O.real("resolution_in_step")),
    resolution_in_gradient_(O.real("resolution_in_gradient")),
    termination_("")
{}

TerminationByThreshold::TerminationByThreshold(const TerminationByThreshold& other):
    resolution_in_LogL_(other.resolution_in_LogL_),
    resolution_in_x_(other.resolution_in_x_),
    resolution_in_step_(other.resolution_in_step_),
    resolution_in_gradient_(other.resolution_in_gradient_),
    termination_(other.termination_)
{}
TerminationByThreshold& TerminationByThreshold::operator =(const TerminationByThreshold& other)
{
    if (this!=&other)
    {
	TerminationByThreshold tmp(other);
	swap(*this,tmp);
    }
    return *this;
}
 void swap(TerminationByThreshold& one, TerminationByThreshold& other)
{
     std::swap(one.termination_,other.termination_);
     std::swap(one.resolution_in_x_,other.resolution_in_x_);
     std::swap(one.resolution_in_LogL_,other.resolution_in_LogL_);
     std::swap(one.resolution_in_step_,other.resolution_in_step_);
     std::swap(one.resolution_in_gradient_,other.resolution_in_gradient_);
    }





TerminationByThreshold::Options::Options():
    BaseOptions("DefaultTermination")
{
    push_back("resolution_in_LogL",1e-7);
    push_back("resolution_in_x",1e-12);
    push_back("resolution_in_step",1e-14);
    push_back("resolution_in_gradient",1e-5);

}
TerminationByThreshold::Options::Options(const std::string& name,
					  double resolution_in_x,
					  double resolution_in_LogL,
					  double resolution_in_step,
					  double resolution_in_gradient):
    BaseOptions(name)
{
    push_back("resolution_in_LogL",resolution_in_LogL);
    push_back("resolution_in_x",resolution_in_x);
    push_back("resolution_in_step",resolution_in_step);
    push_back("resolution_in_gradient",resolution_in_gradient);
}

TerminationByThreshold::Options::Options(const Markov_IO::ABC_Options& O):
    BaseOptions(O.myName())
{
    push_back("resolution_in_LogL",
	      O.real("resolution_in_LogL"));
    push_back("resolution_in_x",
	      O.real("resolution_in_x"));
    push_back("resolution_in_step",
	      O.real("resolution_in_step"));
    push_back("resolution_in_gradient",
	      O.real("resolution_in_gradient"));
}
 std::string TerminationByThreshold::Options::myClass()const
{
    return ClassName();
}

 std::string TerminationByThreshold::Options::ClassName()
 {
     return "Optimization_Termination_Options";
 }



}

