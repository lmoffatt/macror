#include "Markov_LA/matrixOperators.h"
#include "Markov_LA/matrixRelational.h"
#include "Markov_LA/matrixSum.h"
#include "Markov_LA/matrixInit.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixProduct.h"
#include "Tests/Markov_Mol/MarkovTransitionStep_Test.h"

#include "Tests/ElementaryTest.h"


namespace Markov_Test
{
namespace Markov_Mol_Test
{
using namespace Markov_LA;
MultipleTests Markov_Transition_step_Test::classInvariant()const
{
    MultipleTests results("MarkovTransition_step ",
			  "Class Invariant");
    results.push_back(ABC_Put_Test::classInvariant());

    results.push_back(RightSize());
    results.push_back(EmptyShellConstructor());


    MultipleTests pP("P",
		     "invariants");

    pP.push_back(ElementaryTest(
		     "Is Probability",
		     "values between zero and one",
		     (Qstep_->P>=0.0)&&
		     (Qstep_->P<=1.0)));

    pP.push_back(ElementaryTest(
		     "Is Probability",
		     "sum up one",
                     sum(Qstep_->P,true)==ones<double>(k_,1)));
    results.push_back(pP);

    if (two_anchor_)
{
    MultipleTests pGmean("gmean_ij",
			 "invariants");

    pGmean.push_back(ElementaryTest(
			 "gtotal_ij",
			 "elemMult(gmean_ij,P)==gtotal_ij",
			 elemMult(Qstep_->gmean_ij,Qstep_->P)==
			 Qstep_->gtotal_ij));

    pGmean.push_back(ElementaryTest(
			 "gmean_i",
                         "sum(gtotal_ij,true)==gmean_i\n"
                         "sum(gtotal_ij,true)\n"+
                         Markov_IO::ToString(
                             sum(Qstep_->gtotal_ij,true))+
                         "\ngmean_i\n"+
                         Markov_IO::ToString(
                             Qstep_->gmean_i)+"\n",
                         sum(Qstep_->gtotal_ij,true)==
			 Qstep_->gmean_i));

    results.push_back(pGmean);

    MultipleTests pGsqr("gsqr_i",
			"invariants");
    MultipleTests pGvar("gsqr_i",
			"invariants");

    pGsqr.push_back(ElementaryTest(
			 "gtotal_sqr_ij",
			 "sum(gtotal_sqr_ij)==gtotal_sqr_ij",
			 sum(Qstep_->gtotal_sqr_ij,true)==
			 Qstep_->gsqr_i));

    results.push_back(pGsqr);


    pGvar.push_back(ElementaryTest(
			 "gvar_ij",
			 "gvar_ij==elemDiv(gtotal_sqr_ij,P)-"
                         "elemMult(gmean_ij*gmean_ij"
                        "\ngvar_ij\n"+
                        Markov_IO::ToString(Qstep_->gvar_ij)+
                        "\nelemDiv(Qstep_->gtotal_sqr_ij,Qstep_->P)-"
                        "elemMult(Qstep_->gmean_ij,Qstep_->gmean_ij)))\n"+
                         Markov_IO::ToString(
                            elemDivSafe(Qstep_->gtotal_sqr_ij,Qstep_->P)-
                            elemMult(Qstep_->gmean_ij,Qstep_->gmean_ij)),
			 Qstep_->gvar_ij==
                         elemDivSafe(Qstep_->gtotal_sqr_ij,Qstep_->P)-
			 elemMult(Qstep_->gmean_ij,Qstep_->gmean_ij)));

    results.push_back(pGvar);

}
    return results;


}

Markov_Transition_step_Test::
Markov_Transition_step_Test(const Markov_Transition_step& sample):
    ABC_Put_Test(sample),
    Qstep_(dynamic_cast<const Markov_Transition_step*>(sample_)),
    k_(nrows(Qstep_->P)),
    is_averaging_(size(Qstep_->gsqr_i)>0),
    varying_(nrows(Qstep_->gtotal_ij)>0),
    two_anchor_(size(Qstep_->gmean_ij)>0)
{}

Markov_Transition_step_Test::~Markov_Transition_step_Test()
{}


MultipleTests Markov_Transition_step_Test::RightSize()const
{
MultipleTests results("Right size",
                   "check all the values");



results.push_back(ElementaryTest(
                   "P",
                   "k x k",
                   ncols(Qstep_->P)==k_));

results.push_back(ElementaryTest(
                   "gmean_i",
                   "k x 1",
                   (nrows(Qstep_->gmean_i)==k_)&&
                   (ncols(Qstep_->gmean_i)==1)));

if (varying_)
{
    results.push_back(ElementaryTest(
                       "gtotal_ij",
                       "k x k",
                       (nrows(Qstep_->gtotal_ij)==k_)&&
                       (ncols(Qstep_->gtotal_ij)==k_)));
}
else
{
    results.push_back(ElementaryTest(
                       "gtotal_ij",
                       "k x k",
                       (nrows(Qstep_->gtotal_ij)==0)&&
                       (ncols(Qstep_->gtotal_ij)==0)));

}
if (two_anchor_)
{
    results.push_back(ElementaryTest(
                       "gmean_ij",
                       "k x k",
                       (nrows(Qstep_->gmean_ij)==k_)&&
                       (ncols(Qstep_->gmean_ij)==k_)));
    results.push_back(ElementaryTest(
                       "gtotal_sqr_ij",
                       "k x k",
                       (nrows(Qstep_->gtotal_sqr_ij)==k_)&&
                       (ncols(Qstep_->gtotal_sqr_ij)==k_)));
    results.push_back(ElementaryTest(
                       "gtotal_var_ij",
                       "k x k",
                       (nrows(Qstep_->gtotal_var_ij)==k_)&&
                       (ncols(Qstep_->gtotal_var_ij)==k_)));
    results.push_back(ElementaryTest(
                       "gtotal_var_i",
                       "k x 1",
                       (nrows(Qstep_->gtotal_var_i)==k_)&&
                       (ncols(Qstep_->gtotal_var_i)==1)));

    results.push_back(ElementaryTest(
                       "gvar_ij",
                       "k x k",
                       (nrows(Qstep_->gvar_ij)==k_)&&
                       (ncols(Qstep_->gvar_ij)==k_)));

}
else
{
    results.push_back(ElementaryTest(
                       "gmean_ij",
                       "empty",
                       (nrows(Qstep_->gmean_ij)==0)&&
                       (ncols(Qstep_->gmean_ij)==0)));
    results.push_back(ElementaryTest(
                       "gtotal_sqr_ij",
                       "empty",
                       (nrows(Qstep_->gtotal_sqr_ij)==0)&&
                       (ncols(Qstep_->gtotal_sqr_ij)==0)));
    results.push_back(ElementaryTest(
                       "gtotal_var_ij",
                       "empty",
                       (nrows(Qstep_->gtotal_var_ij)==0)&&
                       (ncols(Qstep_->gtotal_var_ij)==0)));
    results.push_back(ElementaryTest(
                       "gtotal_var_i",
                       "empty",
                       (nrows(Qstep_->gtotal_var_i)==0)&&
                       (ncols(Qstep_->gtotal_var_i)==0)));

    results.push_back(ElementaryTest(
                       "gvar_ij",
                       "empty",
                       (nrows(Qstep_->gvar_ij)==0)&&
                       (ncols(Qstep_->gvar_ij)==0)));

}


if (is_averaging_)
{
    results.push_back(ElementaryTest(
                       "gsqr_i",
                       "k x 1",
                       (nrows(Qstep_->gsqr_i)==k_)&&
                       (ncols(Qstep_->gsqr_i)==1)));

    results.push_back(ElementaryTest(
                       "gvar_i",
                       "k x 1",
                       (nrows(Qstep_->gvar_i)==k_)&&
                       (ncols(Qstep_->gvar_i)==1)));
}
else
{
    results.push_back(ElementaryTest(
                       "gsqr_i",
                       "empty",
                       (nrows(Qstep_->gsqr_i)==0)&&
                       (ncols(Qstep_->gsqr_i)==0)));

    results.push_back(ElementaryTest(
                       "gvar_i",
                       "empty",
                       (nrows(Qstep_->gvar_i)==0)&&
                       (ncols(Qstep_->gvar_i)==0)));

}

return results;


}



MultipleTests Markov_Transition_step_Test::EmptyShellConstructor()const

{
MultipleTests results("Empty Shell Constructor",
                  "check right size");
Markov_Transition_step empty(k_,
                       is_averaging_,
                       varying_,
                       two_anchor_);

results.push_back(ElementaryTest(
                   "P",
                   "k x k",
                   ncols(empty.P)==k_));

results.push_back(ElementaryTest(
                   "gmean_i",
                   "k x 1",
                   (nrows(empty.gmean_i)==k_)&&
                   (ncols(empty.gmean_i)==1)));



if (varying_)
{
    results.push_back(ElementaryTest(
                       "gtotal_ij",
                       "k x k",
                       (nrows(empty.gtotal_ij)==k_)&&
                       (ncols(empty.gtotal_ij)==k_)));
}
else
{
    results.push_back(ElementaryTest(
                       "gtotal_ij",
                       "k x k",
                       (nrows(empty.gtotal_ij)==0)&&
                       (ncols(empty.gtotal_ij)==0)));

}
if (two_anchor_)
{
    results.push_back(ElementaryTest(
                       "gmean_ij",
                       "k x k",
                       (nrows(empty.gmean_ij)==k_)&&
                       (ncols(empty.gmean_ij)==k_)));
    results.push_back(ElementaryTest(
                       "gtotal_sqr_ij",
                       "k x k",
                       (nrows(empty.gtotal_sqr_ij)==k_)&&
                       (ncols(empty.gtotal_sqr_ij)==k_)));
    results.push_back(ElementaryTest(
                       "gtotal_var_ij",
                       "k x k",
                       (nrows(empty.gtotal_var_ij)==k_)&&
                       (ncols(empty.gtotal_var_ij)==k_)));
    results.push_back(ElementaryTest(
                       "gtotal_var_i",
                       "k x 1",
                       (nrows(empty.gtotal_var_i)==k_)&&
                       (ncols(empty.gtotal_var_i)==1)));

    results.push_back(ElementaryTest(
                       "gvar_ij",
                       "k x k",
                       (nrows(empty.gvar_ij)==k_)&&
                       (ncols(empty.gvar_ij)==k_)));

}
else
{
    results.push_back(ElementaryTest(
                       "gmean_ij",
                       "empty",
                       (nrows(empty.gmean_ij)==0)&&
                       (ncols(empty.gmean_ij)==0)));
    results.push_back(ElementaryTest(
                       "gtotal_sqr_ij",
                       "empty",
                       (nrows(empty.gtotal_sqr_ij)==0)&&
                       (ncols(empty.gtotal_sqr_ij)==0)));
    results.push_back(ElementaryTest(
                       "gtotal_var_ij",
                       "empty",
                       (nrows(empty.gtotal_var_ij)==0)&&
                       (ncols(empty.gtotal_var_ij)==0)));
    results.push_back(ElementaryTest(
                       "gtotal_var_i",
                       "empty",
                       (nrows(empty.gtotal_var_i)==0)&&
                       (ncols(empty.gtotal_var_i)==0)));

    results.push_back(ElementaryTest(
                       "gvar_ij",
                       "empty",
                       (nrows(empty.gvar_ij)==0)&&
                       (ncols(empty.gvar_ij)==0)));

}

if (is_averaging_)
{
    results.push_back(ElementaryTest(
                       "gsqr_i",
                       "k x 1",
                       (nrows(empty.gsqr_i)==k_)&&
                       (ncols(empty.gsqr_i)==1)));

    results.push_back(ElementaryTest(
                       "gvar_i",
                       "k x 1",
                       (nrows(empty.gvar_i)==k_)&&
                       (ncols(empty.gvar_i)==1)));
}
else
{
    results.push_back(ElementaryTest(
                       "gsqr_i",
                       "empty",
                       (nrows(empty.gsqr_i)==0)&&
                       (ncols(empty.gsqr_i)==0)));

    results.push_back(ElementaryTest(
                       "gvar_i",
                       "empty",
                       (nrows(empty.gvar_i)==0)&&
                       (ncols(empty.gvar_i)==0)));

}
return results;
}




}


}




