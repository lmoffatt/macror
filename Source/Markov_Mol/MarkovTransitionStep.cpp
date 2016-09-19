#include "Markov_Mol/MarkovTransitionStep.h"

#include "Markov_LA/matrixInit.h"
#include "Markov_LA/matrixIO.h"
#include "Markov_LA/Matrix.h"

namespace Markov_Mol_New
{


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




// std::ostream& Markov_Transition_step::put(std::ostream& s) const
//{
//    s<<"\n Markov_Transition_step \n";
//    s<<"P\n"<<P;
//    s<<"gmean_i\n"<<gmean_i;
//    s<<"gmean_ij\n"<<gmean_ij;
//    s<<"gtotal_ij\n"<<gtotal_ij;
//    s<<"gvar_i\n"<<gvar_i;
//    s<<"gvar_ij\n"<<gvar_ij;
//    s<<"gtotal_var_ij\n"<<gtotal_var_ij;
//    s<<"gtotal_sqr_ij\n"<<gtotal_sqr_ij;
//    s<<"gtotal_var_i\n"<<gtotal_var_i;
//    s<<"gsqr_i\n"<<gsqr_i;
//    return s;
//}

}



