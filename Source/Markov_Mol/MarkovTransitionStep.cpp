#include "Markov_Mol/MarkovTransitionStep.h"

#include "Markov_LA/matrixInit.h"
#include "Markov_LA/matrixIO.h"
#include "Markov_LA/Matrix.h"

namespace Markov_Mol
{


Markov_Transition_step*  Markov_Transition_step::clone() const
{
    return new Markov_Transition_step(*this);
}
/// default constructors
 Markov_Transition_step* Markov_Transition_step::create() const
{
    return new Markov_Transition_step();
}
 Markov_Transition_step::~Markov_Transition_step() {}


Markov_Transition_step::Markov_Transition_step(std::size_t n,
		       bool is_averaging_,
		       bool varying_,
		       bool two_anchor_):
P(Markov_LA::zeros<double>(n,n)),
gmean_i(Markov_LA::zeros<double>(n,1)),
gtotal_ij(varying_ ? Markov_LA::zeros<double>(n,n): Markov_LA::M_Matrix<double>()),
gmean_ij(two_anchor_ ? Markov_LA::zeros<double>(n,n):Markov_LA::M_Matrix<double>()),

gtotal_sqr_ij(two_anchor_? Markov_LA::zeros<double>(n,n) :Markov_LA::M_Matrix<double>()),
gsqr_i(is_averaging_ ?Markov_LA::zeros<double>(n,1):Markov_LA::M_Matrix<double>()),
gvar_i(is_averaging_ ?Markov_LA::zeros<double>(n,1):Markov_LA::M_Matrix<double>()),
gtotal_var_ij(two_anchor_? Markov_LA::zeros<double>(n,n):Markov_LA::M_Matrix<double>()),
gtotal_var_i(two_anchor_? Markov_LA::zeros<double>(n,1):Markov_LA::M_Matrix<double>()),
gvar_ij(two_anchor_? Markov_LA::zeros<double>(n,n):Markov_LA::M_Matrix<double>())
{}

Markov_Transition_step::Markov_Transition_step():
	P(Markov_LA::M_Matrix<double>()),
	gmean_i(Markov_LA::M_Matrix<double>()),
	gtotal_ij(Markov_LA::M_Matrix<double>()),
	gmean_ij(Markov_LA::M_Matrix<double>()),
	gtotal_sqr_ij(Markov_LA::M_Matrix<double>()),
	gsqr_i(Markov_LA::M_Matrix<double>()),
	gvar_i(Markov_LA::M_Matrix<double>()),
	gtotal_var_ij(Markov_LA::M_Matrix<double>()),
	gtotal_var_i(Markov_LA::M_Matrix<double>()),
	gvar_ij(Markov_LA::M_Matrix<double>()) {}




///copy constructor
Markov_Transition_step::Markov_Transition_step(const Markov_Transition_step& other):
	P(other.P),
	gmean_i(other.gmean_i),
	gtotal_ij(other.gtotal_ij),
	gmean_ij(other.gmean_ij),
	gtotal_sqr_ij(other.gtotal_sqr_ij),
	gsqr_i(other.gsqr_i),
	gvar_i(other.gvar_i),
	gtotal_var_ij(other.gtotal_var_ij),
	gtotal_var_i(other.gtotal_var_i),
	gvar_ij(other.gvar_ij) {}


void swap(Markov_Transition_step& x, Markov_Transition_step& y)
{
    Markov_LA::swap(x.P,y.P);
    Markov_LA::swap(x.gmean_i,y.gmean_i);
    Markov_LA::swap(x.gtotal_ij, y.gtotal_ij);
    Markov_LA::swap(x.gmean_ij,y.gmean_ij);
    Markov_LA::swap(x.gtotal_sqr_ij, y.gtotal_sqr_ij);
    Markov_LA::swap(x.gsqr_i,y.gsqr_i);
    Markov_LA::swap(x.gvar_i, y.gvar_i);
    Markov_LA::swap(x.gtotal_var_ij, y.gtotal_var_ij);
    Markov_LA::swap(x.gtotal_var_i, y.gtotal_var_i);
    Markov_LA::swap(x.gvar_ij, y.gvar_ij);
}

///asignment
Markov_Transition_step& Markov_Transition_step::operator=(
	const Markov_Transition_step& other)
				 {
    if (this!=&other)
    {
	Markov_Transition_step tmp(other);
	swap(*this, tmp);
    }
    return *this;
}

 std::ostream& Markov_Transition_step::put(std::ostream& s) const
{
    s<<"\n Markov_Transition_step \n";
    s<<"P\n"<<P;
    s<<"gmean_i\n"<<gmean_i;
    s<<"gmean_ij\n"<<gmean_ij;
    s<<"gtotal_ij\n"<<gtotal_ij;
    s<<"gvar_i\n"<<gvar_i;
    s<<"gvar_ij\n"<<gvar_ij;
    s<<"gtotal_var_ij\n"<<gtotal_var_ij;
    s<<"gtotal_sqr_ij\n"<<gtotal_sqr_ij;
    s<<"gtotal_var_i\n"<<gtotal_var_i;
    s<<"gsqr_i\n"<<gsqr_i;
    return s;
}

}
