#include "Markov_Console/Markov_CommandManagerTest.h"
#include "Tests/Markov_LA/Markov_LA_Tests.h"
#include "Tests/Markov_Mol/Markov_Mol_Tests.h"
#include "Tests/Markov_Bay/Markov_Bay_Test.h"
#include "Tests/MersenneTwister_Test.h"

namespace Markov_Console
{

Markov_CommandManagerTest::Markov_CommandManagerTest():
    Markov_CommandManager()
{
 }


void Markov_CommandManagerTest::test(const std::string& testedEntity,
				     const std::string& mode)
{
    Markov_Test::MultipleTests testResult;
    if (testedEntity=="MarkovLA")
    {
	Markov_Test::Markov_LA_Test::Markov_LA_Test<double> LAtest;
        testResult=LAtest.All_Tests();
     }
    else if (testedEntity=="MarkovMol")
    {
        Markov_Mol::ABC_PatchModel* p=patchs.begin()->second;
        if (p)
        {
            Markov_Test::Markov_Mol_Test::Markov_Mol_Test Moltest(p->Model());
            testResult=Moltest.All_Tests();
        }
    }
    else if (testedEntity=="MarkovBay")
    {
        Markov_Mol::ABC_PatchModel* p=patchs.begin()->second;
        if (p)
        {
            Markov_Test::Markov_Bay_Test::Markov_Bay_Test Baytest(*p);
            testResult=Baytest.All_Tests();
        }
    }
    else if (testedEntity=="Random")
    {
        Markov_Test::MersenneTwister_Test::MersenneTwister_Test MTT(0);
        testResult=MTT.AllTests();

    }
    if (mode=="verbose")
        testResult.VerboseLevel(true);
    else
        testResult.VerboseLevel(0);
    std::cerr<<testResult;

    std::ofstream f;
    f.open("test.txt");
    f<<testResult;
    f.close();

}


bool Markov_CommandManagerTest::next_instruction()
{
    if (tokens.size()==0) return false;

    switch (tokens[0].get_token())
    {
    case Token::IDENTIFIER:
	if (tokens[0].Name()=="test")
	{
	    if (tokens.size()<2)
		missing_parameter();
	    else if (tokens.size()<3)
		test(tokens[1].Name());
	    else
		test(tokens[1].Name(),tokens[2].Name());
	}
    default:
	break;
    }

    // Else try with all other commands
    return Markov_CommandManager::next_instruction();
}

}


