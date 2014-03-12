#include "Markov_LA/matrixOperators.h"
#include "Markov_LA/matrixRelational.h"
#include "Markov_LA/matrixSum.h"
#include "Markov_LA/matrixInit.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixProduct.h"
#include "Tests/Markov_Mol/MarkovTransitionRate_Test.h"

#include "Tests/ElementaryTest.h"


namespace Markov_Test
{
namespace Markov_Mol_Test
{
using namespace Markov_LA;
  std::string Markov_Transition_rate_Test::TestName()
  {
    return "Markov_Transition_rate_Test";
  }

 std::string Markov_Transition_rate_Test::myTest()const
 {
   return TestName();
 }
  std::string Markov_Transition_rate_Test::testedClass()const
 {
   return "";
 }



  MultipleTests Markov_Transition_rate_Test::classInvariant()const
{
    MultipleTests results("ClassDescription ",
			  "Class Invariant");
    results.push_back(ABC_Put_Test::classInvariant());

    if (size(this->Qx_->Qrun)>0)
    {
	M_Matrix<double> Diag=diag(diag(Qx_->Qrun));
	M_Matrix<double> Q=Qx_->Qrun-Diag;
	std::size_t k=nrows(Qx_->Qrun);

	MultipleTests pQrun("Qrun",
			    "invariants");
	pQrun.push_back(ElementaryTest(
			    "Qrun",
			    "is a square matrix",
			    nrows(Qx_->Qrun)==ncols(Qx_->Qrun)));

	pQrun.push_back(ElementaryTest(
			    "Qrun",
			    "elements of diagonal are negative",
			    diag(Qx_->Qrun)<0.0));
	pQrun.push_back(ElementaryTest(
			    "Qrun",
			    "elements of out of diagonal are nonnegative",
			    Q>=0.0));

	pQrun.push_back(ElementaryTest(
			    "Qrun",
			    "all rows sum up zero",
			    sum(Qx_->Qrun,true)==zeros<double>(k,1)));
	results.push_back(pQrun);
	MultipleTests pEig("Eigensystem decomposition",
			   "check invariants");
	pEig.push_back(ElementaryTest(
			   "V",
			   "same dimension as Qrun",
			   ((nrows(Qx_->V)==ncols(Qx_->V))&&
			    (nrows(Qx_->V)==nrows(Qx_->Qrun))
			    )));
	pEig.push_back(ElementaryTest(
			   "W",
			   "same dimension as Qrun",
			   ((nrows(Qx_->W)==ncols(Qx_->W))&&
			    (nrows(Qx_->W)==nrows(Qx_->Qrun))
			    )));

	pEig.push_back(ElementaryTest(
			   "W",
			   "is the inverse of V",
			   (Qx_->W*Qx_->V==eye<double>(nrows(Qx_->V))))
		       );
	pEig.push_back(ElementaryTest(
			   "landa",
			   "non positive values",
			   Qx_->landa<=0.0));

	pEig.push_back(ElementaryTest(
			   "Eigendecomposition",
			   "check decomposition ",
			   Qx_->Qrun==
			   Qx_->V*diag(Qx_->landa)*Qx_->W
			   ));
	MultipleTests ppV("Eigenvalue equation",
			  "check each eigenvector");
	for(std::size_t i=0; i<nrows(Qx_->V);++i)
	    ppV.push_back(ElementaryTest(
			      std::to_string(i)+"th vector",
			      std::string("check it \n"
			      "Qrun*V(:,i)\n")+
                              Markov_IO::ToString(Qx_->Qrun * Qx_->V(":",i))+
                              "landa[i]*V(:,i)\n"+
                              Markov_IO::ToString(Qx_->landa[i]*Qx_->V(":",i))+"\n",
                              Qx_->Qrun * Qx_->V(":",i)==
                              Qx_->landa[i] * Qx_->V(":",i)
			      ));
	pEig.push_back(ppV);
	results.push_back(pEig);
	if (size(Qx_->Wg)>0)
	{
	    MultipleTests pWg("Eigenvalue buffers",
			      "confirm identities");
	    M_Matrix<double> G=Qx_->V*Qx_->WgV*Qx_->W;
	    pWg.push_back(ElementaryTest(
			      "WgV",
			      "check recovering g",
			      G-diag(diag(G))==zeros(G)));
	    pWg.push_back(ElementaryTest(
			      "Wg",
			      "check formula",
			      Qx_->Wg==Qx_->W*Transpose(diag(G))));

	    results.push_back(pWg);

	}
	MultipleTests pConst("Constructor",
			     "Recover parameters");
	Markov_Transition_rate copy;

	if (size(Qx_->WgV)>0)
	{
	    copy=Markov_Transition_rate(Qx_->Qrun,
					Qx_->V,
					Qx_->W,
					Qx_->landa,
					Qx_->Wg,
					Qx_->WgV);
	}else
	{
	    copy=Markov_Transition_rate(Qx_->Qrun,
					Qx_->V,
					Qx_->W,
					Qx_->landa);

	}
	pConst.push_back(ElementaryTest("operator==",
					"Recover the whole object",
					copy==*Qx_));
	pConst.push_back(ElementaryTest(
			     "Qrun",
			     "recover value",
			     copy.Qrun==Qx_->Qrun));
	pConst.push_back(ElementaryTest(
			     "V",
			     "recover value",
			     copy.V==Qx_->V));
	pConst.push_back(ElementaryTest(
			     "W",
			     "recover value",
			     copy.W==Qx_->W));
	pConst.push_back(ElementaryTest(
			     "landa",
			     "recover value",
			     copy.landa==Qx_->landa));
	if (size(Qx_->WgV)>0)
	{
	    pConst.push_back(ElementaryTest(
				 "Wg",
				 "recover value",
				 copy.Wg==Qx_->Wg));
	    pConst.push_back(ElementaryTest(
				 "WgV",
				 "recover value",
				 copy.WgV==Qx_->WgV));
	}
	results.push_back(pConst);
	MultipleTests pEmp("Empty shell constructor",
			   "check rigth sizes");
	bool isaveraging=size(Qx_->WgV)>0;

	Markov_Transition_rate empty(k,isaveraging );

	pEmp.push_back(ElementaryTest(
			   "Qrun",
			   "rigth size",
			   (nrows(empty.Qrun)==k)&&
			   (ncols(empty.Qrun)==k)));

	pEmp.push_back(ElementaryTest(
			   "V",
			   "rigth size",
			   (nrows(empty.V)==k)&&
			   (ncols(empty.V)==k)));
	pEmp.push_back(ElementaryTest(
			   "W",
			   "rigth size",
			   (nrows(empty.W)==k)&&
			   (ncols(empty.W)==k)));
	pEmp.push_back(ElementaryTest(
			   "landa",
			   "rigth size",
                           (nrows(empty.landa)==k)&&
                           (ncols(empty.landa)==1)));
	if (isaveraging)
	{
	    pEmp.push_back(ElementaryTest(
			       "Wg",
			       "rigth size",
			       (nrows(empty.Wg)==k)&&
			       (ncols(empty.Wg)==1)));
	    pEmp.push_back(ElementaryTest(
			       "WgV",
			       "rigth size",
			       (nrows(empty.WgV)==k)&&
			       (ncols(empty.WgV)==k)));
	}
	else
	{
	    pEmp.push_back(ElementaryTest(
			       "Wg",
			       "rigth size",
			       (nrows(empty.Wg)==0)&&
			       (ncols(empty.Wg)==0)));
	    pEmp.push_back(ElementaryTest(
			       "WgV",
			       "rigth size",
			       (nrows(empty.WgV)==0)&&
			       (ncols(empty.WgV)==0)));

	}
	results.push_back(pEmp);

	MultipleTests pDefCons("Default constructor",
			       "all sizes are zero");

	Markov_Transition_rate def;
	pDefCons.push_back(ElementaryTest(
			       "Qrun",
			       "rigth size",
			       (nrows(def.Qrun)==0)&&
			       (ncols(def.Qrun)==0)));

	pDefCons.push_back(ElementaryTest(
			       "V",
			       "rigth size",
			       (nrows(def.V)==0)&&
			       (ncols(def.V)==0)));
	pDefCons.push_back(ElementaryTest(
			       "W",
			       "rigth size",
			       (nrows(def.W)==0)&&
			       (ncols(def.W)==0)));
	pDefCons.push_back(ElementaryTest(
			       "landa",
			       "rigth size",
			       (nrows(def.landa)==0)&&
			       (ncols(def.landa)==0)));
	pDefCons.push_back(ElementaryTest(
			       "Wg",
			       "rigth size",
			       (nrows(def.Wg)==0)&&
			       (ncols(def.Wg)==0)));
	pDefCons.push_back(ElementaryTest(
			       "WgV",
			       "rigth size",
			       (nrows(def.WgV)==0)&&
			       (ncols(def.WgV)==0)));
	results.push_back(pDefCons);
    }
    return results;


}

Markov_Transition_rate_Test::
Markov_Transition_rate_Test(const Markov_Transition_rate& sample):
    ABC_Put_Test(sample),
    Qx_(dynamic_cast<const Markov_Transition_rate*>(sample_))
{}

Markov_Transition_rate_Test::~Markov_Transition_rate_Test()
{}

}


}






