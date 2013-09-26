#ifndef OPTIMIZATION_STEP_BFGS_H
#define OPTIMIZATION_STEP_BFGS_H
#include "Markov_Bay/ABC_Optimization_step.h"


namespace Markov_Bay
{
class OptimizationStepBFGS: public ABC_OptimizationStep
{
 public:
    virtual OptimizationStepBFGS* clone()const;
    virtual OptimizationStepBFGS* create()const;
    virtual ~OptimizationStepBFGS();

    virtual OptimizationStepBFGS& start(const Markov_IO::Parameters& x0);
    virtual OptimizationStepBFGS& next();

    virtual const Markov_IO::Parameters& CurrentParameters()const;

    virtual const LikelihoodEvaluation& Likelihood()const;

    virtual const Markov_LA::M_Matrix<double>& Score()const;

    virtual const Markov_LA::M_Matrix<double>& HessianInv()const;

    virtual const Markov_LA::M_Matrix<double>& Hessian()const;

    virtual const Markov_LA::M_Matrix<double>& FisherInformation();

    virtual const Markov_LA::M_Matrix<double>& HessianApprox();


    virtual Markov_IO::ParametersMoments moments();

    virtual double LastLogLikelihoodChange()const;

    virtual double ExpectedLogLikelihoodChange()const;

    virtual const Markov_LA::M_Matrix<double>& LastParametersChange()const;

    virtual const Markov_LA::M_Matrix<double>& SearchDirection()const;

    virtual double AdaptiveStepLength()const;

    virtual size_t NumEvaluationsInStep()const;


    OptimizationStepBFGS();
    OptimizationStepBFGS(const OptimizationStepBFGS& other);
    OptimizationStepBFGS& operator=(const OptimizationStepBFGS& other);

    OptimizationStepBFGS(const Markov_Likelihood& markovLikelihood,
			 const Markov_IO::Parameters& beta,
			 const Markov_IO::ABC_Options& Op);

    OptimizationStepBFGS(const Markov_Likelihood& markovLikelihood,
			 const Markov_IO::Parameters& beta,
			 const Markov_LA::M_Matrix<double>& Hinv,
			 double alpha,
			 const Markov_IO::ABC_Options& Op);


    friend void swap(OptimizationStepBFGS& one, OptimizationStepBFGS& other);


    class Options:public Markov_IO::BaseOptions
    {
    public:
	Options();
	Options(const std::string& name,
		std::size_t maxfevalLoop,
		double Wolf_Condition_c1,
		double Wolf_Condition_c2,
		double initial_alpha);
	Options(const Markov_IO::ABC_Options& options);
	virtual std::string myClass()const;
	static std::string ClassName();

    static std::vector<std::string> parentClasses();
    static std::vector<std::string> childClasses();
    virtual bool amIAbstract()const;
    virtual std::vector<std::string>  myParentClasses()const;
    virtual std::vector<std::string>  myChildClasses()const;

    };

private:
    void Hessian_update();
    void complete_step();

    std::string name_;

    Markov_Likelihood ML_;

    Markov_IO::Parameters beta_;

    LikelihoodEvaluation L1_;
    Markov_LA::M_Matrix<double> score0_;
    Markov_LA::M_Matrix<double> Hinv_;
    mutable Markov_LA::M_Matrix<double> H_;
    mutable Markov_LA::M_Matrix<double> FIM_;
    mutable Markov_LA::M_Matrix<double> Happ_;


    Markov_LA::M_Matrix<double> delta_x_;
    Markov_LA::M_Matrix<double> d_;
    LikelihoodEvaluation L0_;
    std::size_t neval_;
    double alpha_;
    double df0_;


    std::size_t maxfevalLoop_;
    double initial_alpha_;
    double Wolf_Condition_c1_;
    double Wolf_Condition_c2_;
 };

}



#endif // OPTIMIZATION_STEP_BFGS_H
