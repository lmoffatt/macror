#include "Tests/Markov_IO/ABC_Parametrizable_Test.h"
#include "Tests/ElementaryTest.h"
#include "Markov_IO/Parameters.h"
#include "Markov_Console/Markov_CommandManagerTest.h"
namespace Markov_Test
{

namespace Markov_IO_Test
{

using namespace Markov_IO;

   std::string ABC_Parametrizable_Test::testedClass()const
  {
    return ABC_Saveable::ClassName();
  }


   ABC_Parametrizable_Test::ABC_Parametrizable_Test(){}


  std::string ABC_Parametrizable_Test::TestName()
  {
    return "Parametrizable_Test";
  }

   std::string ABC_Parametrizable_Test::myTest()const
  {
    return TestName();
  }

   MultipleTests ABC_Parametrizable_Test::AllTests(Markov_Console::Markov_CommandManager* cm,
                                                   const std::string varNameTested)
   {
     {
       ABC_Saveable* p;
       if (!cm->checkVariable(varNameTested,ABC_Parametrizable::ClassName()))
         return MultipleTests();
       else
         {
           p=cm->getVar(varNameTested);
           this->sample_=p;
           this->saveable_=p;
           this->param_=dynamic_cast<ABC_Parametrizable*>(p);
           return classInvariant();
         }
     }


   }



MultipleTests ABC_Parametrizable_Test::classInvariant()const
{
    MultipleTests result("class ABC_Parametrizable",
			 "check the invariants for the specified object");

    result.push_back(ABC_Saveable_Test::classInvariant());


    ABC_Parametrizable* copy=param_->clone();

    Parameters par=param_->get_parameters();


    MultipleTests pGP("get_parameters()",
		      "function invariants");

    pGP.push_back(ElementaryTest(
		      "clone()",
		      "cloned object returns the same Parameters",
		      par==(copy->get_parameters())));

    int usedPar=copy->apply_parameters(par);


    pGP.push_back(ElementaryTest(
		      "apply_paramers()",
		      "appy_parameters() applies all the parameters",
		      usedPar==par.size()));
    pGP.push_back(ElementaryTest(
		      "apply_parameters()",
		      "apply_parameters returns the original object",
		      *copy==*param_));
    // change in any parameter results in a different object

    result.push_back(pGP);
    MultipleTests pAp("apply_parameters()",
		      "alter individual parameters");

    MultipleTests pGPGP("get_parameters()",
			"should recover alter parameters");

    MultipleTests pApAp("apply_parameters()",
			"recover altered object");



    for (std::size_t i=0; i<par.size(); i++)
    {
	ABC_Parametrizable* cp;
	cp=param_->clone();

	Parameters p=param_->get_parameters();
	p[i]=par[i]*1.1;
	copy->apply_parameters(p);
	pAp.push_back(ElementaryTest(
			  par.Name(i),
			  "multiplied by 1.1, should recover other object",
			  !(*copy==*param_)));
	Parameters p2=copy->get_parameters();
	pGPGP.push_back(ElementaryTest(
			    par.Name(i),
			    "recover modified parameter",
			    (p2==p)));

	cp->apply_parameters(p2);
	pApAp.push_back(ElementaryTest(
			    par.Name(i),
			    "object should change back",
			    (*copy==*cp)));
	delete cp;
    }
    result.push_back(pAp);
    result.push_back(pGPGP);
    result.push_back(pApAp);
    return result;


}



ABC_Parametrizable_Test::
ABC_Parametrizable_Test(const ABC_Parametrizable& parametrizable):
    ABC_Saveable_Test(parametrizable),
    param_(dynamic_cast<const ABC_Parametrizable*>(saveable_))
{}

ABC_Parametrizable_Test::~ABC_Parametrizable_Test(){}

}

}


