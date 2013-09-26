#include "Markov_Bay/OptimizationResult.h"
#include "Markov_IO/auxiliarIO.h"

namespace Markov_Bay
{

  /// copy constructors
  OptimizationResult* OptimizationResult::clone() const{
    return new OptimizationResult(*this);
  }
  /// default constructors
  OptimizationResult* OptimizationResult::create() const{
    return new OptimizationResult();
  }



  Markov_IO::ClassDescription OptimizationResult::GetDescription()const
  {
    Markov_IO::ClassDescription desc(myClass(),mySuperClass());;
    desc.push_back("name",myName());
    desc.push_back("Experiment",Experiment());
    desc.push_back("Prior_Distribution",Prior());

    desc.push_back("number_of_optimizations",optRuns_.size());


    if (optRuns_.size()==0)
      {
        desc.push_back("optimization_0",SingleOptimizationResult());

      }
    else
      {
      for (std::size_t i=0;i<optRuns_.size();++i)
        {
          desc.push_back("optimization_"+Markov_IO::ToString(i),optRuns_[i]);

        }
    }
    desc.push_back("Posterior_Distribution", Posterior());
    desc.push_back("Maximum_Likelihood", MaximumLikelihood());

    desc.push_back("Ratio_reaching_maximum",Reach_ML_ratio());

    desc.push_back("Optimizations_reaching_maximum",Reach_ML_indexes());

    desc.push_back("Posterior_Mean_Distribution", PosteriorMean());



    return desc;
  }


  Markov_LA::M_Matrix<std::size_t> OptimizationResult::Reach_ML_indexes()const
  {
    return Markov_LA::M_Matrix<std::size_t>(1,reachMaxLik_.size(),reachMaxLik_);
  }

  double OptimizationResult::Reach_ML_ratio()const
  {
    return 1.0*reachMaxLik_.size()/optRuns_.size();
  }

  bool OptimizationResult::LoadFromDescription(const Markov_IO::ClassDescription& classDes)
  {
    if (classDes.ClassName()!=myClass())
      {
        return false;
      }
    std::string name;
    if (!ToValue(classDes["name"],name))
      return false;

    Markov_IO::ABC_Experiment* experiment;
    if (!ToValue(classDes["Experiment"],experiment))
      return false;




    Markov_Mol::PatchModelNormalDistribution *Prior_Distribution;
    if (!Markov_IO::ToValue(classDes["Prior_Distribution"],Prior_Distribution))
      return false;


    std::vector<SingleOptimizationResult> vector_of_optimizations;
    std::size_t number_of_optimizations;

    if (!ToValue(classDes["number_of_optimizations"],number_of_optimizations))
      return false;


    for (std::size_t i=0;i<number_of_optimizations;++i)
      {
        SingleOptimizationResult* opt;
        if (!Markov_IO::ToValue(classDes["optimization_"+Markov_IO::ToString(i)],opt))
          return false;
        vector_of_optimizations.push_back(*opt);
        delete opt;
      }



    *this=OptimizationResult(name,
                             *experiment,
                             *Prior_Distribution,
                             vector_of_optimizations);

    return true;
  }


  OptimizationResult::~OptimizationResult()
  {

  }


  std::string OptimizationResult::ClassName(){
    return "Optimization_Result";
  }

  std::vector<std::string> OptimizationResult::parentClasses()
  {
    std::vector<std::string> v;
    v.push_back(Markov_Bay::ABC_Result::ClassName());

    return v;

  }

  std::vector<std::string> OptimizationResult::childClasses()
  {
    std::vector<std::string> v;
    return v;
  }

  bool OptimizationResult::amIAbstract()const
  {
    return false;
  }

  std::vector<std::string>  OptimizationResult::myParentClasses()const
  {
    return parentClasses();
  }
  std::vector<std::string>  OptimizationResult::myChildClasses()const
  {
    return childClasses();
  }




  std::string OptimizationResult::myName()const{
    return name_;
  }
  std::string OptimizationResult::myClass()const{
    return ClassName();
  }

  const Markov_Mol::PatchModelNormalDistribution& OptimizationResult::Posterior()const{
    return this->posteriorModeDist_;
  }

  const Markov_Mol::PatchModelNormalDistribution& OptimizationResult::PosteriorMean()const{
    return this->posteriorMeanDist_;
  }



  const Markov_Mol::PatchModelNormalDistribution& OptimizationResult::Prior()const
  {
    return this->priorPatchDist_;
  }

  const Markov_IO::ABC_Experiment& OptimizationResult::Experiment()const
  {
    return *E_;
  }




  const LikelihoodEvaluation& OptimizationResult::MaximumLikelihood()const
  {
    return this->maxLik_;
  }






  OptimizationResult::OptimizationResult(const OptimizationResult& other):
    name_(other.name_),
    E_(other.E_),
    priorPatchDist_(other.priorPatchDist_),
    optRuns_(other.optRuns_),
    resLogL_(other.resLogL_),
    maxLik_(other.maxLik_),
    reachMaxLik_(other.reachMaxLik_),
    posteriorModeDist_(other.posteriorModeDist_),
    posteriorMeanDist_(other.posteriorMeanDist_)

  {}
  OptimizationResult::OptimizationResult():
    name_(),
    E_(0),
    priorPatchDist_(),
    optRuns_(),
    resLogL_(),
    maxLik_(),
    posteriorModeDist_(),
    posteriorMeanDist_(),
    reachMaxLik_()
  {}
  OptimizationResult::OptimizationResult(const std::string& name,
                                         const Markov_IO::ABC_Experiment& experiment,
                                         const Markov_Mol::PatchModelNormalDistribution& priorD,
                                         std::vector<SingleOptimizationResult> optRuns,
                                         double resLogL):
    name_(name),
    E_(&experiment),
    priorPatchDist_(priorD),
    optRuns_(optRuns),
    resLogL_(resLogL),
    maxLik_(),
    reachMaxLik_(),
    posteriorModeDist_(),
    posteriorMeanDist_()
  {
    calc();
  }

  void OptimizationResult::calc()
  {
    if (optRuns_.empty())
      return;
    SingleOptimizationResult r=optRuns_[0];
    maxLik_=r.MaximumLikelihood();
    std::vector<std::size_t> reachMaxL;

    std::size_t iML=0;
    // find the optimizations close to the maximumlikelihood
    for (std::size_t i=0; i<optRuns_.size(); i++)
      {

        if (maxLik_.logL()<optRuns_[i].MaximumLikelihood().logL()+resLogL_)
          {
            if(maxLik_.logL()<optRuns_[i].MaximumLikelihood().logL()-resLogL_)
              {
                iML=i;
                maxLik_=optRuns_[i].MaximumLikelihood();
                reachMaxL.clear();
                reachMaxL.push_back(i);
              }
            else if(maxLik_.logL()<optRuns_[i].MaximumLikelihood().logL())

              {
                iML=i;
                maxLik_=optRuns_[i].MaximumLikelihood();
                reachMaxL.push_back(i);
              }
            else
              reachMaxL.push_back(i);
          }
      }
    // find the mode

    posteriorModeDist_=optRuns_[iML].Result();


    reachMaxLik_.clear();

    // be sure that all the optimizations are at most at a distance of resLogL_
    for (std::size_t i=0; i<reachMaxL.size(); i++)
      {
        if (maxLik_.logL()<optRuns_[reachMaxL[i]].MaximumLikelihood().logL()+resLogL_)
          {
            reachMaxLik_.push_back(reachMaxL[i]);
          }
      }

    // now get the mean posterior
    // first get a vector with the models
    std::vector<Markov_IO::Parameters> bestModels;
    for (std::size_t i=0; i<reachMaxLik_.size(); i++)
          {
        r=optRuns_[reachMaxLik_[i]];
        bestModels.push_back(r.Result().Mean()->get_parameters());
          }
    Markov_IO::ParametersMoments moments=Markov_IO::ParametersMoments::getMoments(bestModels);

    std::size_t nsamples=posteriorModeDist_.nSamples();

    posteriorMeanDist_=Markov_Mol::PatchModelNormalDistribution("mean_"+name_,
                                                                *this->Prior().Mean(),
                                                                moments,
                                                                nsamples);

  }


  OptimizationResult& OptimizationResult::operator=(
      const OptimizationResult& other)
  {
    if (this!=&other)
      {
        OptimizationResult tmp(other);
        swap(*this,tmp);
      }
    return *this;
  }

  void swap(OptimizationResult& one,OptimizationResult& other){
    std::swap(one.name_,other.name_);
    std::swap(one.E_,other.E_);
    std::swap(one.optRuns_,other.optRuns_);
    swap(one.priorPatchDist_,other.priorPatchDist_);
    swap(one.maxLik_,other.maxLik_);
    swap(one.posteriorModeDist_,other.posteriorModeDist_);
    swap(one.posteriorMeanDist_,other.posteriorMeanDist_);
    std::swap(one.reachMaxLik_,other.reachMaxLik_);
  }


  std::istream& operator>> (std::istream& stream,OptimizationResult*& x)
  {
      Markov_IO::ClassDescription classDes;
      stream>>classDes;
      if (stream.good())
          if(!x->LoadFromDescription(classDes))
              stream.setstate(stream.rdstate() | std::ios_base::failbit);
      return stream;
  }



}



