#include "Markov_Mol/MarkovStateExt.h"
#include "Markov_LA/matrixInit.h"
#include "Markov_LA/matrixIO.h"


namespace Markov_Mol
{


using Markov_LA::M_Matrix;
using Markov_LA::zeros;



Markov_state_ext* Markov_state_ext::clone() const
{
    return new Markov_state_ext(*this);
};
/// default constructors
 Markov_state_ext* Markov_state_ext::create() const
{
    return new Markov_state_ext();
};

 Markov_state_ext::~Markov_state_ext() {};

Markov_state_ext::Markov_state_ext(const Markov_state_ext& other):
	N(other.N),
	N_mean(other.N_mean),
	N_std(other.N_std),
	ymean(other.ymean),
	ystd(other.ystd),
	P(other.P),
	N_sqr(other.N_sqr),
	ysqr(other.ysqr)
{};

Markov_state_ext::Markov_state_ext(std::size_t n):
	N(zeros<size_t>(1,n)),
	N_mean(zeros<double>(1,n)),
	N_std(zeros<double>(1,n)),
	ymean(),
	ystd(),
	P(zeros<double>(1,n)),
	N_sqr(zeros<double>(1,n)),
	ysqr() {};

Markov_state_ext::Markov_state_ext():
	N(),
	N_mean(),
	N_std(),
	ymean(),
	ystd(),
	P(),
	N_sqr(),
	ysqr() {};

///asignment
Markov_state_ext& Markov_state_ext::operator=(const Markov_state_ext& other)
			   {
    if (this!=&other)
    {
	N=other.N;
	N_mean=other.N_mean;
	N_std=other.N_std;
	ymean=other.ymean;
	ystd=other.ystd;
	P=other.P;
	N_sqr=other.N_sqr;
	ysqr=other.ysqr;
    };
    return *this;
};
 std::ostream& Markov_state_ext::put(std::ostream& s) const
{
    s<<"\n Markov_state \n";
    s<<N<<N_mean<<"\n  +/- "<<N_std;
    s<<ymean<<" +/- "<<ystd<<"\n";
    s<<"P\n"<<P;
    return s;
};

}
