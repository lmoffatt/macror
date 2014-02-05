#include "Markov_Bay/SimpleOptimization.h"
#include "Markov_Bay/ABC_Optimization_step.h"
#include "Markov_Bay/ABC_Optimization_termination.h"
#include "Markov_Bay/Optimization_Step_BFGS.h"
#include "Markov_Bay/TerminationByThreshold.h"
#include "Markov_LA/matrixOperators.h"
#include "Markov_LA/matrixMath.h"

namespace Markov_Bay
{

SimpleOptimization* SimpleOptimization::clone() const{
    return new SimpleOptimization(*this);
}

SimpleOptimization* SimpleOptimization::create() const
{
    return new SimpleOptimization();
}

SimpleOptimization::~SimpleOptimization()
{
}

const Markov_IO::ABC_Experiment& SimpleOptimization::experiment()const{
    return ML_.experiment();
}

const SimpleOptimization::Options& SimpleOptimization::getOptions()const{
    return this->O_;
}

bool SimpleOptimization::setOptions(const Markov_IO::ABC_Options &options){
    O_=Options(options);
    maxfeval_=O_.count("Maximum_number_of_evaluations");
    maxiter_=O_.count("Maximum_number_of_iterations");
    return true;

}


SingleOptimizationResult SimpleOptimization::run(const Markov_IO::Parameters& beta)
{
    ABC_OptimizationStep* step;
    ABC_OptimizationTermination* isend;

    if(O_.name("Hessian_update")=="BFGS")
    {
	step=new OptimizationStepBFGS(ML_,beta,O_);
    }
    else return SingleOptimizationResult();

    if (O_.name("Termination_Condition")=="Threshold")
    {
	isend=new TerminationByThreshold(O_);
    }
    else return SingleOptimizationResult();
    Markov_Mol::ABC_PatchModel* startPatch=ML_.patch().clone();
    Markov_Mol::ABC_PatchModel* optimalPatch=ML_.patch().clone();

    startPatch->apply_parameters(beta);

    std::string namePM=ML_.model().myName();

    std::size_t nfeval=0;
    std::size_t niter=0;
    std::string termination;
    if (Markov_LA::isFinite(step->Likelihood().logL()))
      {
    while (! isend->operator ()(step->next())&&
           (nfeval<maxfeval_)&&(niter<maxiter_))
      {
        nfeval+=step->NumEvaluationsInStep();
        niter++;
        std::stringstream ss;
        ss<<nfeval<<"\t "<<step->Likelihood().logL()<<"\t";
        ss<<
             Markov_LA::exp10(
               Markov_LA::Transpose(
                 step->CurrentParameters().
                 transformed_values()))<<"\n";
        io_->put(ss.str());

      }
    termination=isend->Message();

    if (nfeval>=maxfeval_)
	termination+="Maximum number of Likelihood Evaluations exceeded. \n";
    else if (niter>=maxiter_)
        termination+="Maximum number of iterations exceeded. \n";

      }
    else
      termination="Likelihood of start value is not a valid number. \n";
    optimalPatch->apply_parameters(step->CurrentParameters());


    Markov_Mol::PatchModelNormalDistribution pdist(namePM,
						   *optimalPatch,
						   step->moments(),
						   ML_.experiment().num_measures());

    LikelihoodEvaluation LE=step->Likelihood();

    SingleOptimizationResult SOR(namePM,
				 *startPatch,
				 ML_.experiment().myName(),
				 pdist,
				 LE,
				 nfeval,
				 termination);

    delete startPatch;
    delete optimalPatch;
    delete step;
    delete isend;
    std::cout<<SOR;

    return SOR;
}




OptimizationResult SimpleOptimization::run(const Markov_Mol::PatchModelNormalDistribution& betaDist,
                                         std::size_t numStarts)
{
  std::vector<SingleOptimizationResult> runs;

  for (std::size_t i=0; i< numStarts;i++)
    {
      Markov_Mol::ABC_PatchModel* model=betaDist.Sample();
      Markov_IO::Parameters p=model->get_parameters();
      runs.push_back(run(p));
      delete model;
     }

  OptimizationResult result(name_,this->experiment(), betaDist,runs);
  return result;
}



SimpleOptimization::SimpleOptimization(const std::string& name,
				       const Markov_Mol::ABC_PatchModel& P,
				       const Markov_IO::ABC_Experiment& E,
                       const Markov_IO::ABC_Options& O,
                                       Markov_IO::ABC_IO *io):
    name_(name),
    par_(P.get_parameters()),
    ML_(Markov_Likelihood(P,E,O)),
    O_(O),
    maxfeval_(O.count("Maximum_number_of_evaluations")),
    maxiter_(O.count("Maximum_number_of_iterations")),
    io_(io)
{}



SimpleOptimization::SimpleOptimization(const SimpleOptimization& other):
    name_(other.name_),
    ML_(other.ML_),
    O_(other.O_),
    maxfeval_(other.maxfeval_),
    maxiter_(other.maxiter_)
{}


SimpleOptimization::SimpleOptimization():
    name_(),
    ML_(),
    O_(),
    maxfeval_(),
    maxiter_()
{}




SimpleOptimization::Options::Options():
    BaseOptions("Default")
{
    push_back("Hessian_update",std::string("BFGS"));
    push_back("Termination_Condition",std::string("Threshold"));
    push_back("Maximum_number_of_evaluations",std::size_t(3000));
    push_back("Maximum_number_of_iterations",std::size_t(100));
    (*this)+=Markov_Likelihood::Options();
    if (name("Hessian_update")=="BFGS")
	(*this)+=OptimizationStepBFGS::Options();
    if (name("Termination_Condition")=="Threshold")
	(*this)+=TerminationByThreshold::Options();
}

SimpleOptimization::Options::Options(
    const std::string& myname,
    const std::string& HessianUpdate,
    const std::string& Termination,
    std::size_t maxEval,
    std::size_t maxIter,
    const Markov_IO::ABC_Options& likelihoodOptions,
    const Markov_IO::ABC_Options& stepOptions,
    const Markov_IO::ABC_Options& terminationOptions
    ):
    BaseOptions(myname)
{
    push_back("Hessian_update",HessianUpdate);
    push_back("Termination_Condition",Termination);
    push_back("Maximum_number_of_evaluations",maxEval);
    push_back("Maximum_number_of_iterations",maxIter);
    (*this)+=Markov_Likelihood::Options(likelihoodOptions);
    if (name("Hessian_update")=="BFGS")
	(*this)+=OptimizationStepBFGS::Options(stepOptions);
    if (name("Termination_Condition")=="Threshold")
	(*this)+=TerminationByThreshold::Options(terminationOptions);
}

SimpleOptimization::Options::Options(const Markov_IO::ABC_Options& options):
    BaseOptions(options.myName())
{
    push_back("Hessian_update",options.name("Hessian_update"));
    push_back("Termination_Condition",options.name("Termination_Condition"));
    push_back("Maximum_number_of_evaluations",
	      options.count("Maximum_number_of_evaluations"));
    push_back("Maximum_number_of_iterations",
	      options.count("Maximum_number_of_iterations"));
    (*this)+=Markov_Likelihood::Options(options);
    if (name("Hessian_update")=="BFGS")
	(*this)+=OptimizationStepBFGS::Options(options);
    if (name("Termination_Condition")=="Threshold")
	(*this)+=TerminationByThreshold::Options(options);
}

std::string SimpleOptimization::Options::myClass()const
{
    return ClassName();
}

std::string SimpleOptimization::Options::ClassName()
{
    return "Simple_Optimization_Options";
}


SimpleOptimization::Options::Options(const Options& other):
    BaseOptions(other){}
SimpleOptimization::Options&
SimpleOptimization::Options::operator=(
    const SimpleOptimization::Options& other)
{
    if (this!=&other)
    {
	Options tmp(other);
	swap(tmp,*this);
    }
    return *this;
}

void swap(SimpleOptimization::Options& x,SimpleOptimization::Options& y)
{
    Markov_IO::BaseOptions * xp=&x;
    Markov_IO::BaseOptions * yp=&y;
    swap(*xp,*yp);
}

std::ostream& SimpleOptimization::put(std::ostream& s) const
{
    s<<"Name\n"<<name_;
    s<<"Parameters \n"<< par_;
    s<< ML_;
    s<< O_;
    s<<"Maximum number of function evaluations\t"<< maxfeval_<<"\n";
    s<<"Maximum number of iterations \t"<< maxiter_<<"\n";
    return s;
}

 bool SimpleOptimization::operator==(const SimpleOptimization& other)const
{
    if (name_!=other.name_) return false;
    if (!(ML_==other.ML_)) return false;
    if (!(O_==other.O_))return false;
    if (maxfeval_!=other.maxfeval_)return false;
    if (maxiter_!=other.maxiter_) return false;
    return true;

}







}


