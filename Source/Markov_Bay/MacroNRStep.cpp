
#include "Markov_Bay/MacroNRStep.h"

#include "Markov_Mol/QMarkovModel.h"

#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixRelational.h"
#include "Markov_LA/matrixOperators.h"

#include "Markov_LA/auxiliarMath.h"

namespace Markov_Bay
{

Macro_NR_step* Macro_NR_step::clone()const
{
    return new Macro_NR_step(*this);
}

Macro_NR_step* Macro_NR_step::create()const
{
    return new Macro_NR_step();
}


std::string Macro_NR_step::myClass()const
{
    return ClassName();
}
std::string Macro_NR_step::ClassName()
{
    return "Macro_NR_step";
}






Macro_NR_step::Macro_NR_step(const Macro_NR_step& other):
  Implements_VarId(other),
  ABC_Markov_Likelihood_step(other) ,
    model_A(other.model_A->clone()),
    Q_dt(other.Q_dt),
    P_mean_M(other.P_mean_M),
    P_cov_M(other.P_cov_M),
     y_d(other.y_d),
    y_mean_d(other.y_mean_d),
    y_var_d(other.y_var_d),
    y_std_d(other.y_std_d),
    plogL_d(other.plogL_d),
    eplogL_d(other.eplogL_d),
    chi2_d(other.chi2_d),
    isaveraging_b(other.isaveraging_b){}







const  Markov_LA::M_Matrix<double>& Macro_NR_step::P_mean()const
{
    return P_mean_M;
}
const Markov_LA::M_Matrix<double>& Macro_NR_step::P_cov()const
{
    return P_cov_M;
}
double Macro_NR_step::y_mean()const
{
    return y_mean_d;
}
double Macro_NR_step::y()const
{
    return y_d;
}
double Macro_NR_step::y_var()const
{
    return y_var_d;
}
double Macro_NR_step::y_std()const
{
    return y_std_d;
}
double Macro_NR_step::plogL()const
{
    return plogL_d;
}
double Macro_NR_step::eplogL()const
{
    return eplogL_d;
}
double Macro_NR_step::N_channels()const
{
    return model_A->AverageNumberOfChannels();
}
const Markov_Mol::ABC_PatchModel& Macro_NR_step::patch()const
{
    return *model_A;
}

const Markov_Mol::ABC_Markov_Model& Macro_NR_step::model()const
{
    return model_A->Model();
}

const Markov_Mol::ABC_noise& Macro_NR_step::noise()const
{
    return model_A->Noise();
}
void Macro_NR_step::apply_parameters(const Markov_IO::Parameters& beta)
{
    model_A->apply_parameters(beta);
 }
const Markov_IO::Parameters& Macro_NR_step::get_parameters()const
{
    return model_A->get_parameters();
}

Macro_NR_step::Macro_NR_step(ABC_Data *e,
                             const std::string& id,
                             const Markov_Mol::ABC_PatchModel& P,
                             bool is_averaging,
                             const std::string& tip,
                             const std::string& whatthis):
  ABC_Markov_Likelihood_step(e,id,ClassName(),tip,whatthis),
    model_A(P.clone()),
    Q_dt(),
    P_mean_M(Markov_LA::M_Matrix<double>(1,P.Model().k())),
    P_cov_M(Markov_LA::M_Matrix<double>(P.Model().k(),P.Model().k())),
    y_d(Markov_LA::NaN()),
    y_mean_d(Markov_LA::NaN()),
    y_var_d(Markov_LA::NaN()),
    y_std_d(Markov_LA::NaN()),

    plogL_d(Markov_LA::NaN()),
    eplogL_d(Markov_LA::NaN()),
    chi2_d(Markov_LA::NaN()),

    isaveraging_b(is_averaging)
{
}

Macro_NR_step::Macro_NR_step():
    model_A(0),
    Q_dt(),
    P_mean_M(),
    P_cov_M(),
    isaveraging_b(false)
{}

Macro_NR_step::~Macro_NR_step()
{
    delete model_A;
}

Macro_NR_step& Macro_NR_step::start(double x)
{
    P_mean_M=model().Peq(x);
    P_cov_M=diag(P_mean_M)-TranspMult(P_mean_M,P_mean_M);
    return *this;
}

Macro_NR_step& Macro_NR_step::run(const Markov_IO::ABC_measure_step& Y)
{
    Q_dt=this->model().Q_step(Y,isaveraging_b);
    Markov_LA::M_Matrix<double> gS(TranspMult(Q_dt.gmean_i,P_cov_M));// product of S and g, used several places
    y_d=Y.y();
    if (Markov_LA::isNaN(Y.y()))
    {
	plogL_d=Markov_LA::NaN();
	chi2_d=Markov_LA::NaN();
    }
    else
    {
	y_mean_d=(P_mean_M*Q_dt.gmean_i)[0]*model_A->AverageNumberOfChannels();

	if (isaveraging_b)
	{
	    y_var_d=model_A->Noise().var(Y.dt())+
		    ((gS*Q_dt.gmean_i)[0]+(P_mean_M*Q_dt.gvar_i)[0])*
		    model_A->AverageNumberOfChannels();
	}
	else
	{
	    y_var_d=model_A->Noise().var(Y.dt())+
		    ((gS*Q_dt.gmean_i)[0])*model_A->AverageNumberOfChannels();
	};

	y_std_d=sqrt(y_var_d);

	double dy=y_mean_d-Y.y();

	chi2_d=dy*dy/y_var_d;

	plogL_d=-0.5*log(2*PI*y_var_d)-0.5*chi2_d;

	eplogL_d=-0.5*(1+log(2*PI*y_var_d));


    }

    P_cov_M=diag(P_mean_M)-TranspMult(P_mean_M,P_mean_M);

    P_mean_M = P_mean_M*Q_dt.P;

    return *this;
}

}

