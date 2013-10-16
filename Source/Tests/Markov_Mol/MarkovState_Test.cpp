#include "Markov_LA/matrixOperators.h"
#include "Markov_LA/matrixRelational.h"
#include "Markov_LA/matrixSum.h"
#include "Markov_LA/matrixInit.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixProduct.h"
#include "Tests/Markov_Mol/MarkovState_Test.h"
#include <cmath>

#include "Tests/ElementaryTest.h"


namespace Markov_Test
{
namespace Markov_Mol_Test
{
using namespace Markov_LA;
  std::string Markov_state_Test::TestName()
  {
    return "Markov_Transition_step_Test";
  }

 std::string Markov_state_Test::myTest()const
 {
   return TestName();
 }

  std::string Markov_state_Test::testedClass()const
 {
   return "";
 }


MultipleTests Markov_state_Test::classInvariant()const
{
    MultipleTests results("ClassDescription ",
			  "Class Invariant");
    results.push_back(ABC_Put_Test::classInvariant());

    if (size(this->S_->N())>0)
    {
	MultipleTests pN("N()",
		      "invariants");
	pN.push_back(ElementaryTest(
			 "row column",
			 "ncols==1; nrows>=1",
			 (ncols(S_->N())==1)&&
			 (nrows(S_->N())>=1)));

	pN.push_back(ElementaryTest(
			 "P()",
			 "same size",
			 (ncols(S_->P())==1)&&
			 (nrows(S_->P())==nrows(S_->N()))));

	MultipleTests pP("P()",
			 "is probability");

	pP.push_back(ElementaryTest(
			 "P()",
			 "between zero and one",
			 (S_->P()>=0.0)&&
			 (S_->P()<=1.0)));

	pP.push_back(ElementaryTest(
			 "P()",
			 "sum up zero",
                         std::abs(totalsum(S_->P())-1.0)<
                         std::numeric_limits<double>::epsilon()*100));


       results.push_back(pP);

	MultipleTests pAccess("N() P() ymean()",
			      "  store modifications");

	Markov_state copy(*S_);

	M_Matrix<size_t> Nc=S_->N();

	Nc[0]+=1;
	copy.N()=Nc;

	pAccess.push_back(ElementaryTest(
			      "N()",
			      "recover modification",
			      copy.N()==Nc));

	M_Matrix<double> Pc=S_->P();

	std::size_t Ntc=totalsum(Nc);
	for (std::size_t i=0; i<nrows(Nc); i++)
	    Pc[0]=double(Nc[i])/double(Ntc);

	copy.P()=Pc;


	pAccess.push_back(ElementaryTest(
			      "P()",
			      "recover modification",
			      copy.P()==Pc));

	double ymeanc=S_->ymean();
	ymeanc*=1.1;

	copy.ymean()=ymeanc;
	pAccess.push_back(ElementaryTest(
			      "ymean()",
			      "recover modification",
			      copy.ymean()==ymeanc));

	results.push_back(pAccess);
	}
    return results;


}

Markov_state_Test::
Markov_state_Test(const Markov_state& sample):
    ABC_Put_Test(sample),
    S_(dynamic_cast<const Markov_state*>(sample_))
{}

Markov_state_Test::~Markov_state_Test()
{}

}


}





