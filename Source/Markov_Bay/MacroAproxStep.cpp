#include "Markov_Bay/MacroAproxStep.h"


#include "Markov_Mol/QMarkovModel.h"


#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixRelational.h"
#include "Markov_LA/matrixOperators.h"
#include "Markov_LA/matrixInverse.h"
#include "Markov_LA/matrixSum.h"

#include "Markov_LA/auxiliarMath.h"

#include "Markov_Bay/MacroscopicGaussianDistribution.h"

namespace Markov_Bay
{
using namespace Markov_LA;

Macro_Aprox_step* Macro_Aprox_step::clone()const
{
    return new Macro_Aprox_step(*this);
}

Macro_Aprox_step* Macro_Aprox_step::create()const
{
    return new Macro_Aprox_step();
}

std::string Macro_Aprox_step::myClass()const
{
    return ClassName();
}
std::string Macro_Aprox_step::ClassName()
{
    return "Macro_Aprox_step";
}




const  M_Matrix<double>& Macro_Aprox_step::P_mean()const
{
    return P_mean_M;
}
const M_Matrix<double>& Macro_Aprox_step::P_cov()const
{
    return P_cov_M;
}
double Macro_Aprox_step::y()const
{
    return y_d;
}
double Macro_Aprox_step::y_mean()const
{
    return y_mean_d;
}
double Macro_Aprox_step::y_var()const
{
    return y_var_d;
}
double Macro_Aprox_step::y_std()const
{
    return y_std_d;
}


double Macro_Aprox_step::plogL()const
{
    return plogL_d;
}
double Macro_Aprox_step::eplogL()const
{
    return eplogL_d;
}


double Macro_Aprox_step::N_channels()const
{
    return model_A->AverageNumberOfChannels();
}

const Markov_Mol::ABC_Markov_Model& Macro_Aprox_step::model()const
{
    return model_A->Model();
}


const Markov_Mol::ABC_PatchModel& Macro_Aprox_step::patch()const
{
    return *model_A;
}


const Markov_Mol::ABC_noise& Macro_Aprox_step::noise()const
{
    return model_A->Noise();
}

void Macro_Aprox_step::apply_parameters(const Markov_IO::Parameters& beta)
{
    model_A->apply_parameters(beta);
}

const Markov_IO::Parameters& Macro_Aprox_step::get_parameters()const
{
    return model_A->get_parameters();
}


Macro_Aprox_step& Macro_Aprox_step::start(double x)
{
    step_->start(x);

    P_mean_M=model().Peq(x);
    P_cov_M=diag(P_mean_M)-TranspMult(P_mean_M,P_mean_M);
    return *this;
}

Macro_Aprox_step& Macro_Aprox_step::run(const Markov_IO::ABC_measure_step& Y)
{

    double sumLikelihood=0;
    double sumSqrLikelihood=0;
    double sumy=0;
    double sumy2=0;
    M_Matrix<double> sumPmean=zeros(P_mean());
    M_Matrix<double> sumPcov=zeros(P_cov());
    M_Matrix<double> sumPmeanPrior=zeros(P_mean());
    M_Matrix<double> sumPcovPrior=zeros(P_cov());
    double maxLogL;
    df_=0;
    y_d=Y.y();

    for (std::size_t n=0; n<NumSamples_;n++)
    {
        M_Matrix<std::size_t> N=D_.SampleN();

        Markov_Mol::Markov_state S(N,0.0);

        S=model().run(Y,S,NumSteps_,sto_);

        double logL=noise().logP(y_d-S.ymean(),Y.dt());
        if (n==0)
            maxLogL=logL;
        if (maxLogL<logL)
        {
            double factor=exp(maxLogL-logL);
            maxLogL=logL;
            sumLikelihood*=factor;
            sumSqrLikelihood*=factor*factor;
            sumPmean*=factor;
            sumPcov*=factor;
        }
        double Likelihood=exp(logL-maxLogL);
        sumLikelihood+=Likelihood;
        sumSqrLikelihood+=Likelihood*Likelihood;
        df_=sumLikelihood*sumLikelihood/sumSqrLikelihood;
        sumy+=S.ymean();
        sumy2+=S.ymean()*S.ymean();
        M_Matrix<double>
                P=S.N()/totalsum(S.N());
        sumPmean+=P*Likelihood;
        sumPcov+=TranspMult(P,P)*Likelihood;
        sumPmeanPrior+=P;
        sumPcovPrior+=TranspMult(P,P);
      //  if (floor(n/100)-1.*n/100==0.0)
      //      std::cout<<n<<" ";

    } ;
    y_mean_d=sumy/NumSamples_;
    double nois=noise().var(Y.dt());
    y_var_d=sumy2/NumSamples_-y_mean_d*y_mean_d+nois;
    y_std_d=std::sqrt(y_var_d);

    sumPmeanPrior/=double(NumSamples_);
    sumPcovPrior/=double(NumSamples_);


    plogL_d=log(sumLikelihood/NumSamples_)+maxLogL;
    double dy=y_d-y_mean_d;

    double ratio=nois/y_var_d*NumSamples_;
    double ratio2=dy/y_std_d;


    double chi2=dy*dy/y_var_d;

    double plogL=-0.5*log(2*PI*y_var_d)-0.5*chi2;

    P_mean_prior_M=P_mean_M;
    P_mean_M=sumPmean/sumLikelihood;
    P_cov_prior_M=P_cov_M;
    P_cov_M=sumPcov/sumLikelihood-TranspMult(P_mean_M,P_mean_M);
    P_cov_M=P_cov_M*N_channels();
    eplogL_d=-0.5*(1+log(2*PI*y_var_d));

    D_=MacroscopicGaussianDistribution(P_mean(),
                                       P_cov(),
                                       N_channels(),
                                       0);
    step_->run(Y);
    D_step_=MacroscopicGaussianDistribution(step_->P_mean(),
                                       step_->P_cov(),
                                       step_->N_channels(),
                                       0);


    return *this;
}

Macro_Aprox_step::Macro_Aprox_step(const ABC_Markov_Likelihood_step& step,
                                   std::size_t numSamples,
                                   std::size_t numSteps,
                                   std::size_t seed):
    step_(step.clone()),
    model_A(step.patch().clone()),
    Q_dt(),
    D_(step.P_mean(),step.P_cov(),step.patch().AverageNumberOfChannels(),seed),
    D_step_(D_),
    P_mean_M(step.P_mean()),
    P_cov_M(step.P_cov()),
    P_mean_prior_M(),
    P_cov_prior_M(),

    y_d(std::numeric_limits<double>::quiet_NaN()),
    y_mean_d(std::numeric_limits<double>::quiet_NaN()),
    y_var_d(std::numeric_limits<double>::quiet_NaN()),
    y_std_d(std::numeric_limits<double>::quiet_NaN()),

    plogL_d(std::numeric_limits<double>::quiet_NaN()),
    eplogL_d(std::numeric_limits<double>::quiet_NaN()),
    NumSamples_(numSamples),
    NumSteps_(numSteps),
    sto_(Borrowed::MersenneTwister::seedinit(seed))



{
}


Macro_Aprox_step::Macro_Aprox_step(const Macro_Aprox_step& other):
    step_(other.step_->clone()),
    model_A(other.model_A->clone()),
    Q_dt(other.Q_dt),
    D_(other.D_),
    D_step_(other.D_step_),
    P_mean_M(other.P_mean_M),
    P_cov_M(other.P_cov_M),
    P_mean_prior_M(other.P_mean_prior_M),
    P_cov_prior_M(other.P_cov_prior_M),
    y_d(other.y_d),
    y_mean_d(other.y_mean_d),
    y_var_d(other.y_var_d),
    y_std_d(other.y_std_d),
    plogL_d(other.plogL_d),
    eplogL_d(other.eplogL_d),
    NumSamples_(other.NumSamples_),
    NumSteps_(other.NumSteps_),
    sto_(other.sto_)
{}


Macro_Aprox_step::Macro_Aprox_step() {}

Macro_Aprox_step::~Macro_Aprox_step()
{
    delete model_A;
    delete step_;
}

double Macro_Aprox_step::Pr_P_mean()const
{
    double p=D_step_.Pr_P_mean(P_mean(),df_);
    return p;
}

double Macro_Aprox_step::Chi2_P_mean()const
{
    double chi=D_step_.Chi2_P_mean(P_mean())*df_;
    return chi;
}



double Macro_Aprox_step::Chi2_P_cov(std::size_t i,
                                  std::size_t j)const
{
    double chi2;
    if (i==j)
        chi2=P_cov()(i,i)/step_->P_cov()(i,i) *df_;
    else
        chi2=df_*(P_cov()(i,i)+P_cov()(j,j)+2.0*P_cov()(i,j))/
                (step_->P_cov()(i,i)+step_->P_cov()(j,j)+
                 2.0*step_->P_cov()(i,j));
    return chi2;

}


double Macro_Aprox_step::Pr_P_cov(std::size_t i,
                                  std::size_t j)const
{
    double chi2=Chi2_P_cov(i,j);
    double p=Markov_LA::ChiSqrCdf(chi2,df_-1);
    return 1.-p;

}



double Macro_Aprox_step::Chi2_y_var()const
{
    double chi2=y_var()/step_->y_var()*NumSamples_;
    return chi2;

}

double Macro_Aprox_step::Pr_y_var()const
{
    double chi2=Chi2_y_var();
    double p=Markov_LA::ChiSqrCdf(chi2,NumSamples_);
    return 1-p;

}


double Macro_Aprox_step::Chi2_y_mean()const
{
    double chi2=std::pow(step_->y_mean()-y_mean(),2)/
            step_->y_var()*std::sqrt(NumSamples_);
    return chi2;
}

double Macro_Aprox_step::Pr_y_mean()const
{
    double chi2=Chi2_y_mean();
    double p=Markov_LA::ChiSqrCdf(chi2,1);
    return 1.-p;
}


double Macro_Aprox_step::Chi2_pLogL()const
{
    double chi2=std::sqrt(NumSamples_)*0.5*std::pow(step_->plogL()-plogL(),2);
    return chi2;
}

double Macro_Aprox_step::Pr_pLogL()const
{
    double chi2=Chi2_pLogL();
    double p=Markov_LA::ChiSqrCdf(chi2,1);
    return 1.-p;
}




const ABC_Markov_Likelihood_step& Macro_Aprox_step::TestedStep()const
{
    return *step_;
}

 double Macro_Aprox_step::NumSamples()const
{
    return NumSamples_;
}
 double Macro_Aprox_step::df()const
{
    return df_;
}

 std::size_t Macro_Aprox_step::NumVaryingStates()const
{
     return D_step_.NumVaryingStates();
}
}
