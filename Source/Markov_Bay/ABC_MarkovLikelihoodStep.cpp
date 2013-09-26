
#include "Markov_Bay/ABC_MarkovLikelihoodStep.h"
#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixInverse.h"

#include "Markov_LA/auxiliarMath.h"

namespace Markov_Bay
{

std::ostream& ABC_Markov_Likelihood_step::put(std::ostream& s)const
{
    s<<"\n mean P\n"<<P_mean();
    s<<"\n cov P\n"<<P_cov();
    s<<"\n ymean "<<y_mean()<<"  ystd  "<<y_std()<<"  plogL  "<<plogL()<<"\n";
    return s;
}



}
