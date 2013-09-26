#ifndef MARKOV_LA_TESTS_H
#define MARKOV_LA_TESTS_H

#include "Tests/Markov_LA/Matrix_Test.h"
#include "Tests/Markov_LA/ToleranceComparison_Test.h"


namespace Markov_Test
{
namespace Markov_LA_Test
{
    using namespace Markov_LA;
    template<typename T>
    class Markov_LA_Test
    {
    public:
	Markov_LA_Test();
	Markov_LA_Test(const Markov_LA_Test& other);
	Markov_LA_Test(const M_Matrix<T>& sample);
	Markov_LA_Test(std::size_t size_t);

	MultipleTests Aritmetic_Test();
	template<typename S>
	MultipleTests AssigmentOp_Test();
	MultipleTests Expm_Test();
	MultipleTests IO_Test();
	MultipleTests Inverse_Test();
	MultipleTests Init_Test();
	MultipleTests Math_Test();
	MultipleTests MaxMin_Test();
	MultipleTests Operators_Test();
	MultipleTests Rand_Test();
        MultipleTests NumericRand_Test();
	MultipleTests Product_Test();
	MultipleTests Relational_Test();
	MultipleTests Rounding_Test();
	MultipleTests Sum_Test();
        MultipleTests AuxiliarMath_Test();
        MultipleTests Cholesky_Test();


	MultipleTests All_Tests();
    private:
	M_Matrix<T> M_;
    };
} //end of Markov_LA
}



#endif // MARKOV_LA_TESTS_H
