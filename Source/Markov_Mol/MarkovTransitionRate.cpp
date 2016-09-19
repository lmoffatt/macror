#include "Markov_Mol/MarkovTransitionRate.h"
#include "Markov_LA/matrixInit.h"
#include "Markov_LA/matrixIO.h"

namespace Markov_Mol_New
{

using Markov_LA::zeros;

Markov_Transition_rate::~Markov_Transition_rate() {};
/// copy constructors

Markov_Transition_rate* Markov_Transition_rate::clone() const
{
    return new Markov_Transition_rate(*this);
};
/// default constructors
Markov_Transition_rate* Markov_Transition_rate::create() const
{
    return new Markov_Transition_rate();
};

Markov_Transition_rate::Markov_Transition_rate(const Markov_Transition_rate& other):
	Qrun(other.Qrun),
	V(other.V),
	W(other.W),
	landa(other.landa),
	Wg(other.Wg),
	WgV(other.WgV) {};

Markov_Transition_rate::Markov_Transition_rate(const M_Matrix<double>& Qrun_,
		       const M_Matrix<double>& V_,
		       const M_Matrix<double>& W_,
		       const M_Matrix<double>& landa_):
Qrun(Qrun_),
V(V_),
W(W_),
landa(landa_),
Wg(M_Matrix<double>()),
WgV(M_Matrix<double> ()) {};

Markov_Transition_rate::Markov_Transition_rate(const M_Matrix<double>& Qrun_,
		       const M_Matrix<double>& V_,
		       const M_Matrix<double>& W_,
		       const M_Matrix<double>& landa_,
		       const M_Matrix<double>& Wg_,
		       const M_Matrix<double>& WgV_):
Qrun(Qrun_),
V(V_),
W(W_),
landa(landa_),
Wg(Wg_),
WgV(WgV_) {};

Markov_Transition_rate& Markov_Transition_rate::operator=(
	const Markov_Transition_rate& other)
				 {
    if (this!=&other)
    {
	Markov_Transition_rate tmp(other);
	swap(*this, tmp);
    };
    return *this;
};

void swap(Markov_Transition_rate& one, Markov_Transition_rate& other)
{
    swap(one.Qrun,other.Qrun);
    swap(one.V,other.V);
    swap(one.W,other.W);
    swap(one.landa,other.landa);
    swap(one.Wg,other.Wg);
    swap(one.WgV,other.WgV);
};

Markov_Transition_rate::Markov_Transition_rate(std::size_t n, bool is_averaging):
	Qrun(zeros<double>(n,n)),
	V(zeros<double>(n,n)),
	W(zeros<double>(n,n)),
	landa(zeros<double>(n,1)),
	Wg(M_Matrix<double>()),
	WgV(M_Matrix<double>())
{
    if (is_averaging)
    {
	Wg=zeros<double>(n,1);
	WgV=zeros<double>(n,n);
    };
};

Markov_Transition_rate::Markov_Transition_rate():
	Qrun(M_Matrix<double>()),V(M_Matrix<double>()),W(M_Matrix<double>()),
	landa(M_Matrix<double>()),Wg(M_Matrix<double>()),WgV(M_Matrix<double>()) {}

std::ostream& Markov_Transition_rate::put(std::ostream& s) const
{
    s<<"\n Markov_Transition_rate \n";
    s<<Qrun;
    s<<V;
    s<<W;
    s<<landa;
    s<<Wg;
    s<<WgV;
    return s;
};



inline
	std::ostream& operator<< (std::ostream& s,const Markov_Transition_rate& x)
{
    return x.put(s);
}


}





