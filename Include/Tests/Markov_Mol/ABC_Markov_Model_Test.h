#ifndef ABC_MARKOV_MODEL_TEST_H
#define ABC_MARKOV_MODEL_TEST_H
#include "Tests/MultipleTests.h"
#include "Tests/Markov_IO/ABC_Parametrizable_Test.h"
#include "Markov_Mol/ABC_MarkovModel.h"

namespace Markov_Test
{


namespace Markov_Mol_Test
{
using Markov_LA::M_Matrix;

using namespace Markov_Mol;


class ABC_Markov_Model_Test: public Markov_IO_Test::ABC_Parametrizable_Test
{
public:
    /**
      Test invariants of apply_parameters and get_parameters

      */
    virtual MultipleTests AllTests();

    virtual MultipleTests classInvariant()const;



    virtual MultipleTests startInvariant(double agonist_concentration,
		   std::size_t Nchannels,
		   Borrowed::MersenneTwister::MTRand& sto)const;


    virtual MultipleTests PeqInvariant(double agonist_concentration)const;



    virtual MultipleTests runInvariant(const Markov_IO::ABC_measure_point& xdt,
					Markov_state& markovState,
					std::size_t n_steps,
					Borrowed::MersenneTwister::MTRand& sto);


    virtual MultipleTests Q_dtInvariant (const Markov_IO::ABC_measure_point& xdt,
				bool is_averaging,
				bool varyingx,
                                bool two_anchor,
                                std::size_t numSteps);

     virtual MultipleTests Q_xInvariant (double agonist_concentrarion,
					bool isavergaing);



    virtual MultipleTests Q_stepInvariant(const Markov_IO::ABC_measure_step& ,
                                          bool is_averaging,
                                          bool two_anchor,
                                          std::size_t numSteps)const;




    virtual Markov_Transition_step Q_dtRun(const Markov_IO::ABC_measure_point& xdt,
					   std::size_t numSteps);


    virtual Markov_Transition_step Q_stepRun(const Markov_IO::ABC_measure_step& xdt,
					   std::size_t numSteps)const;



    ABC_Markov_Model_Test(const ABC_Markov_Model& model);

    virtual ~ABC_Markov_Model_Test();

private:
    const ABC_Markov_Model* model_;

   };
}
}

#endif // ABC_MARKOV_MODEL_TEST_H
