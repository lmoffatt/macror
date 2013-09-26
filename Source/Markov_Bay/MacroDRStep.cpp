#include "Markov_Bay/MacroDRStep.h"

#include "Markov_Mol/QMarkovModel.h"

#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixRelational.h"
#include "Markov_LA/matrixOperators.h"

#include "Markov_LA/auxiliarMath.h"

namespace Markov_Bay
{

Macro_DR_step* Macro_DR_step::clone()const
{
    return new Macro_DR_step(*this);
}

Macro_DR_step* Macro_DR_step::create()const
{
    return new Macro_DR_step();
}

std::string Macro_DR_step::myClass()const
{
    return ClassName();
}
std::string Macro_DR_step::ClassName()
{
    return "Macro_DR_step";
}



const  Markov_LA::M_Matrix<double>& Macro_DR_step::P_mean()const
{
    return P_mean_M;
}
const Markov_LA::M_Matrix<double>& Macro_DR_step::P_cov()const
{
    return P_cov_M;
}
double Macro_DR_step::y()const
{
    return y_d;
};
double Macro_DR_step::y_mean()const
{
    return y_mean_d;
};
double Macro_DR_step::y_var()const
{
    return y_var_d;
};
double Macro_DR_step::y_std()const
{
    return y_std_d;
};


double Macro_DR_step::plogL()const
{
    return plogL_d;
}
double Macro_DR_step::eplogL()const
{
    return eplogL_d;
};


double Macro_DR_step::N_channels()const
{
    return model_A->AverageNumberOfChannels();
};

const Markov_Mol::ABC_Markov_Model& Macro_DR_step::model()const
{
    return model_A->Model();
};


const Markov_Mol::ABC_PatchModel& Macro_DR_step::patch()const
{
    return *model_A;
}


const Markov_Mol::ABC_noise& Macro_DR_step::noise()const
{
    return model_A->Noise();
}

void Macro_DR_step::apply_parameters(const Markov_IO::Parameters& beta)
{
    model_A->apply_parameters(beta);
 }

const Markov_IO::Parameters& Macro_DR_step::get_parameters()const
{
    return model_A->get_parameters();
}


Macro_DR_step& Macro_DR_step::start(double x)
{
    P_mean_M=model().Peq(x);
    P_cov_M=diag(P_mean_M)-TranspMult(P_mean_M,P_mean_M);
    return *this;
}



Macro_DR_step& Macro_DR_step::run(const Markov_IO::ABC_measure_step& Y)
{
  double dt=Y.dt();
  double x=Y.x();
  double y=Y.y();


    Q_dt=this->model().Q_step(Y,true,true);
    Markov_LA::M_Matrix<double> Sm=P_cov_M-diag(P_mean_M);

    Markov_LA::M_Matrix<double> sSm=TranspMult(Q_dt.gtotal_var_i,Sm);
    Markov_LA::M_Matrix<double> gSm=TranspMult(Q_dt.gmean_i,Sm);

    double sms=0;
    double smg=0;
    double gmg=0;
    std::size_t k_u=model().k();
    for (std::size_t i=0; i<k_u; i++)
        for (std::size_t j=0; j<k_u; j++)
        {
            sms+=Q_dt.gvar_ij(i,j)*P_mean_M[i]*Q_dt.gtotal_var_ij(i,j);
            smg+=Q_dt.gvar_ij(i,j)*P_mean_M[i]*Q_dt.gtotal_ij(i,j);
            gmg+=Q_dt.gmean_ij(i,j)*P_mean_M[i]*Q_dt.gtotal_ij(i,j);
        };

    double gSg=(gSm*Q_dt.gmean_i)[0]+gmg;
    double sSg=(sSm*Q_dt.gmean_i)[0]+smg;
    double sSs=(sSm*Q_dt.gtotal_var_i)[0]+sms;


    Markov_LA::M_Matrix<double> gS=gSm*Q_dt.P+P_mean_M*Q_dt.gtotal_ij;
    Markov_LA::M_Matrix<double> sS=sSm*Q_dt.P+P_mean_M*Q_dt.gtotal_var_ij;
    double N=model_A->AverageNumberOfChannels();
    double sA2=N*(P_mean_M*Q_dt.gtotal_var_i)[0]+model_A->Noise().var(Y.dt());
    double sB4=2*sA2*sA2-N*sSs;

    y_var_d=sA2+N*gSg+(N*N*sSg*sSg)/std::abs(sB4);
    //sometimes sB4 might be negative, when P_cov_M is greter than one.

    if (y_var_d<0)
    {
        std::cerr<<" \n******** y_var_d negative!!!!!***********\n";
        std::cerr<<"\n sA2+N*gSg+(N*N*sSg*sSg)/sB4 \n";
        std::cerr<<"\n sA2=  "<<sA2;
        std::cerr<<"\n gSg ="<<gSg;
        std::cerr<<"\n sB4=2*sA2*sA2-N*sSs  sB4 = "<<sB4<<"\n";

        std::cerr<<*this;
        std::cerr<<this->model();
        //press_any_key_to_continue();
    }

    y_std_d=std::sqrt(y_var_d);

    y_mean_d=N*(P_mean_M*Q_dt.gmean_i)[0]-sA2/sB4*sSg;

    // product of S and g, used several places
    y_d=Y.y();

    if (Markov_LA::isNaN(y_d))
    {
        plogL_d=Markov_LA::NaN();
        chi2_d=Markov_LA::NaN();
        P_cov_M=TranspMult(Q_dt.P,(P_cov_M-diag(P_mean_M))*Q_dt.P);
        P_mean_M = P_mean_M*Q_dt.P;
        P_cov_M+=diag(P_mean_M);

    }
    else
    {
        Markov_LA::M_Matrix<double> m=P_mean_M*Q_dt.P;
        double dy=y_d-y_mean_d;
        m+=sS*(N*sSg/sB4*(Y.y()-y_mean_d)/y_var_d-sA2/sB4)
                +gS*((Y.y()-y_mean_d)/y_var_d);
        if (p_zero_guard_b&&(!(m>=0.0)))
        {
            double summ=0;
            for (std::size_t i=0;i<size(m);i++)
            {
                if (m[i]<0)
                    m[i]=0;
                else if (m[i]>1)
                    m[i]=1;
                summ+=m[i];
            }
            m/=summ;
        }
        chi2_d=dy*dy/y_var_d;

        if (y_var_d>0)
          plogL_d=-0.5*log(2*PI*y_var_d)-0.5*chi2_d;
        else
          plogL_d=Markov_LA::infinity();

        eplogL_d=-0.5*(1+log(2*PI*y_var_d));

        P_cov_M=TranspMult(Q_dt.P,Sm)*Q_dt.P+diag(P_mean_M*Q_dt.P)-
                TranspMult(gS,gS)*(N/y_var_d)-
                (TranspMult(sS,gS)+TranspMult(gS,sS))*(N*N*sSg/y_var_d/sB4)+
                TranspMult(sS,sS)*(N/sB4-N/y_var_d*N*N*sSg*sSg/sB4/sB4);

        if (p_zero_guard_b&&(!(diag(P_cov_M)>=0.0)||!(diag(P_cov_M)<=1.0)))
        {
            for (std::size_t i=0;i<Markov_LA::ncols(P_cov_M);i++)
            {
                if (P_cov_M(i,i)<0.0)
                    P_cov_M(i,i)=abs(P_cov_M(i,i));
                else if (P_cov_M(i,i)>1.0)
                    P_cov_M(i,i)=1.0;
            }
        }


        P_mean_M=m;
    }
    return *this;

}

Macro_DR_step::Macro_DR_step(const Markov_Mol::ABC_PatchModel& P,
                             bool p_zero_guard):
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


    p_zero_guard_b(p_zero_guard)
{
 }

Macro_DR_step::Macro_DR_step(const Macro_DR_step& other):
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
        p_zero_guard_b(other.p_zero_guard_b)
{}


Macro_DR_step::Macro_DR_step() {}

Macro_DR_step::~Macro_DR_step()
{
    delete model_A;
}
}
