#include "Markov_Bay/Optimization_Step_BFGS.h"
#include "Markov_LA/matrixOperators.h"
#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixAssigmentOp.h"
#include "Markov_LA/matrixOperators.h"
#include "Markov_LA/matrixMath.h"
#include "Markov_LA/matrixMaxMin.h"
#include "Markov_LA/matrixInverse.h"
#include "Markov_LA/ToleranceComparison.h"


namespace Markov_Bay
{
  using Markov_LA::M_Matrix;

  OptimizationStepBFGS* OptimizationStepBFGS::clone()const
  {
    return new OptimizationStepBFGS(*this);
  }
  OptimizationStepBFGS* OptimizationStepBFGS::create()const
  {
    return new OptimizationStepBFGS();
  }

  OptimizationStepBFGS::~OptimizationStepBFGS(){}





  OptimizationStepBFGS& OptimizationStepBFGS::next()
  {
    neval_=0;
    Hessian_update();
    complete_step();
    return *this;
  }


  OptimizationStepBFGS& OptimizationStepBFGS::start(const Markov_IO::Parameters& betaPar)

  {
    // initialize score_, beta_, delta_x_,Hinv_
    neval_=0;

    Markov_IO::Parameters p=betaPar;

    Hinv_=Markov_LA::eye<double>(betaPar.size());
    L1_=ML_.run(betaPar);
    if (Markov_LA::isFinite(L1_.logL()))
      {
        score0_=ML_.score(p);

    neval_+=betaPar.size();
    alpha_=initial_alpha_;
    beta_=betaPar;

    complete_step();
      }
    return *this;
  }


  const Markov_LA::M_Matrix<double>&
  OptimizationStepBFGS::SearchDirection()const
  {
    return d_;
  }

  double OptimizationStepBFGS::AdaptiveStepLength()const
  {
    return alpha_;
  }


  double OptimizationStepBFGS::LastLogLikelihoodChange()const
  {
    return L1_.logL()-L0_.logL();
  }

  double OptimizationStepBFGS::ExpectedLogLikelihoodChange()const
  {
    return df0_;
  }


  const Markov_LA::M_Matrix<double>&
  OptimizationStepBFGS::LastParametersChange()const
  {
    return delta_x_;
  }



  const Markov_IO::Parameters& OptimizationStepBFGS::CurrentParameters()const{
    return beta_;
  }

  Markov_IO::ParametersMoments OptimizationStepBFGS::moments()
  {
    return Markov_IO::ParametersMoments(beta_,
                                        Markov_LA::M_Matrix<double>(),
                                        this->HessianApprox());
  }


  const LikelihoodEvaluation& OptimizationStepBFGS::Likelihood()const{
    return L1_;
  }

  size_t OptimizationStepBFGS::NumEvaluationsInStep()const{
    return neval_;
  }
  const Markov_LA::M_Matrix<double>& OptimizationStepBFGS::Score()const{
    return score0_;
  }

  const Markov_LA::M_Matrix<double>& OptimizationStepBFGS::Hessian()const{
    H_= Markov_LA::invSafe(Hinv_);
    return H_;
  }
  const Markov_LA::M_Matrix<double>& OptimizationStepBFGS::HessianInv()const{
    return Hinv_;
  }

  const Markov_LA::M_Matrix<double>& OptimizationStepBFGS::FisherInformation()
  {
    FIM_=ML_.FisherInformationMatrix(beta_);
    return FIM_;
  }

  const Markov_LA::M_Matrix<double>& OptimizationStepBFGS::HessianApprox()
  {
    Happ_=ML_.HessianAproximationMatrix(beta_);
    return Happ_;
  }



  void OptimizationStepBFGS::complete_step()
  {
    d_=  Hinv_*score0_; //that determine the direction of search.
    df0_=-Markov_LA::TranspMult(score0_,d_)[0];
    double alfa=0;
    double beta=INFINITY;
    std::size_t ifevalLoop=0;
    // this loop look after a value of a that satisfy Wolfe conditions
    double df1;
    LikelihoodEvaluation L1;
    Markov_IO::Parameters beta1(beta_);
    while (true)
      {
        if (!(Markov_LA::isFinite(alpha_)))
          alpha_=initial_alpha_;
        Markov_LA::M_Matrix<double> x01=beta_.transformed_values();
        Markov_LA::M_Matrix<double> x1;
        while(true)
          {
            x1=x01+d_*alpha_;
            beta1.transformed_values(x1);
            L1=ML_.run(beta1);
            neval_++;
            ifevalLoop++;
            if (Markov_LA::isFinite(L1.logL()))
              break;
            else
              alpha_/=10;
          }
        //Armijo rule
        if (((-L1.logL()>-L1_.logL()+df0_*Wolf_Condition_c1_*alpha_)||
             (!Markov_LA::isFinite(L1.logL())))
            &&(ifevalLoop<maxfevalLoop_))
          {
            beta=alpha_;
            alpha_=0.5*(alfa+beta);
          }
        else
          {
            df1=-ML_.score(beta1,d_);
            neval_++;
            ifevalLoop++;
            //curvature conditions
            if ((df1<Wolf_Condition_c2_*df0_)&&ifevalLoop<maxfevalLoop_)
              {
                alfa=alpha_;
                if (beta==INFINITY)
                  {
                    alpha_=2*alfa;
                  }
                else
                  {
                    alpha_=0.5*(alfa+beta);
                  };
              }
            else
              break;
          }
      }

    /** if it is possible, apply a cubic interpolation phase                                                                              */

    double b1=df0_+df1-3*(-L1.logL()+L1_.logL())/alpha_;
    Markov_LA::ToleranceComparison<double> tol;

    if ((b1*b1-df0_*df1)>0)
      {
        double b2=pow((b1*b1-df0_*df1),0.5);
        if (!tol.isEqual((df1-df0_+2*b2),0.0))
          alpha_=alpha_-alpha_*(df1+b2-b1)/(df1-df0_+2*b2);
      }
    Markov_LA::M_Matrix<double> x2=beta_.transformed_values()+d_*alpha_;
    Markov_IO::Parameters beta2(beta_);
    LikelihoodEvaluation L2=ML_.run(beta2.transformed_values(x2));
    neval_++;
    if ((L2.logL()==L2.logL())&&(-L2.logL()<-L1.logL()))
      {
        L0_=L1_;
        L1_=L2;
        delta_x_=beta2.transformed_values()-beta_.transformed_values();
        beta_=beta2;
      }
    else
      {
        L0_=L1_;
        L1_=L1;
        delta_x_=beta1.transformed_values()-beta_.transformed_values();
        beta_=beta1;
      }
  }


  void OptimizationStepBFGS::Hessian_update()
  {
    Markov_LA::M_Matrix<double> old_score=score0_;
    score0_=ML_.score(beta_);
    neval_+=beta_.size();


    Markov_LA::M_Matrix<double> delta_score=-score0_+old_score;

    double s2=(Markov_LA::TranspMult(delta_x_,delta_score))[0];
    if (s2>0)
      {
        using Markov_LA::multTransp;
        using Markov_LA::TranspMult;

        double sigma=pow(s2,0.5);
        Markov_LA::M_Matrix<double> s=delta_x_/sigma;
        Markov_LA::M_Matrix<double> y=delta_score/sigma;
        Markov_LA::M_Matrix<double> ds=s-(Hinv_*y);
        Markov_LA::M_Matrix<double> Hx=multTransp(ds,s);

        Hinv_+=Hx+Transpose(Hx)-multTransp(s,s)*(TranspMult(ds,y))[0] ;

        /**     last formula is from
    http://www.math.washington.edu/~burke/crs/408f/notes/nlp/direction.pdf

    */
      }
  }



  OptimizationStepBFGS::OptimizationStepBFGS():
    ML_(),
    beta_(),
    L1_(),
    score0_(),
    Hinv_(),
    H_(),
    FIM_(),
    Happ_(),
    delta_x_(),
    d_(),
    L0_(),
    neval_(),
    alpha_(),
    df0_(),
    maxfevalLoop_(),
    initial_alpha_(),
    Wolf_Condition_c1_(),
    Wolf_Condition_c2_(){}
  OptimizationStepBFGS::OptimizationStepBFGS(const OptimizationStepBFGS& other):
    ML_(other.ML_),
    beta_(other.beta_),
    L1_(other.L1_),
    score0_(other.score0_),
    Hinv_(other.Hinv_),
    H_(other.H_),
    FIM_(other.FIM_),
    Happ_(other.Happ_),
    delta_x_(other.delta_x_),
    d_(other.d_),
    L0_(other.L0_),
    neval_(other.neval_),
    alpha_(other.alpha_),
    df0_(other.df0_),
    maxfevalLoop_(other.maxfevalLoop_),
    initial_alpha_(other.initial_alpha_),
    Wolf_Condition_c1_(other.Wolf_Condition_c1_),
    Wolf_Condition_c2_(other.Wolf_Condition_c2_){}


  OptimizationStepBFGS::OptimizationStepBFGS(
      const Markov_Likelihood& markovLikelihood,
      const Markov_IO::Parameters& beta,
      const Markov_IO::ABC_Options& O):
    ML_(markovLikelihood),
    beta_(beta),
    L1_(),
    score0_(),
    Hinv_(),
    H_(),
    FIM_(),
    Happ_(),
    delta_x_(),
    d_(),
    L0_(),
    neval_(),
    alpha_(),
    df0_(),
    maxfevalLoop_(O.count("Maximum_evaluations_per_loop")),
    initial_alpha_(O.real("Initial_step_length")),
    Wolf_Condition_c1_(O.real("Wolf_Condition_c1")),
    Wolf_Condition_c2_(O.real("Wolf_Condition_c2"))
  {
    start(beta_);
  }


  OptimizationStepBFGS& OptimizationStepBFGS::operator=(const OptimizationStepBFGS& other)

  {
    if (this!=&other)
      {
        OptimizationStepBFGS tmp(other);
        swap(*this,tmp);
      }
    return *this;

  }

  void swap(OptimizationStepBFGS& one, OptimizationStepBFGS& other)
  {
    swap(one.ML_,other.ML_);
    swap(one.beta_,other.beta_);
    swap(one.L1_,other.L1_);
    swap(one.score0_,other.score0_);
    swap(one.Hinv_,other.Hinv_);
    swap(one.H_,other.H_);
    swap(one.FIM_,other.FIM_);
    swap(one.Happ_,other.Happ_);
    swap(one.delta_x_,other.delta_x_);
    swap(one.d_,other.d_);
    swap(one.L0_,other.L0_);
    std::swap(one.neval_,other.neval_);
    std::swap(one.alpha_,other.alpha_);
    std::swap(one.df0_,other.df0_);
    std::swap(one.maxfevalLoop_,other.maxfevalLoop_);
    std::swap(one.initial_alpha_,other.initial_alpha_);
    std::swap(one.Wolf_Condition_c1_,other.Wolf_Condition_c1_);
    std::swap(one.Wolf_Condition_c2_,other.Wolf_Condition_c2_);


  }





  OptimizationStepBFGS::Options::Options():
    BaseOptions("Deafault")
  {
    push_back("Maximum_evaluations_per_loop",std::size_t(10));
    push_back("Wolf_Condition_c1",0.1);
    push_back("Wolf_Condition_c2",0.5);
    push_back("Initial_step_length",1e-4);
  }

  OptimizationStepBFGS::Options::Options(const std::string& name,
                                         std::size_t maxfevalLoop,
                                         double Wolf_Condition_c1,
                                         double Wolf_Condition_c2,
                                         double initial_alpha):
    BaseOptions(name)
  {
    push_back("Maximum_evaluations_per_loop",maxfevalLoop);
    push_back("Wolf_Condition_c1",Wolf_Condition_c1);
    push_back("Wolf_Condition_c2",Wolf_Condition_c2);
    push_back("Initial_step_length",initial_alpha);

  }

  OptimizationStepBFGS::Options::Options(const Markov_IO::ABC_Options& O):
    BaseOptions(O.myName())
  {
    push_back("Maximum_evaluations_per_loop",O.count("Maximum_evaluations_per_loop"));
    push_back("Wolf_Condition_c1",O.real("Wolf_Condition_c1"));
    push_back("Wolf_Condition_c2",O.real("Wolf_Condition_c2"));
    push_back("Initial_step_length",O.real("Initial_step_length"));

  }
  std::string OptimizationStepBFGS::Options::myClass()const
  {return ClassName();}
  std::string OptimizationStepBFGS::Options::ClassName()
  {return "Optimization_Step_BFGS_Options";}




}



