#ifndef MARKOV_LA_TESTS_H
#define MARKOV_LA_TESTS_H

#include "Tests/Markov_LA/Matrix_Test.h"

#include "Tests/Markov_LA/ToleranceComparison_Test.h"
#include "Tests/All_Tests.h"


namespace Markov_Test
{
namespace Markov_LA_Test
{
    using namespace Markov_LA;

  template<typename T>
    class Markov_LATest: public All_Tests
    {
    public:
        Markov_LATest();
        virtual MultipleTests AllTests(Markov_Console::Markov_CommandManager* cm,
                                       const std::string varNameTested);
       // virtual MultipleTests AllTests()=0;
        static std::string TestName();

        virtual std::string myTest()const;

        virtual std::string testedClass()const;



        Markov_LATest(const Markov_LATest& other);
        Markov_LATest(const M_Matrix<T>& sample);
        Markov_LATest(std::size_t size_t);

	MultipleTests Aritmetic_Test() const;
	template<typename S>
	MultipleTests AssigmentOp_Test() const;
	MultipleTests IO_Test() const;

	MultipleTests Expm_Test()const;
	MultipleTests Inverse_Test()const;
	MultipleTests Init_Test()const;
	MultipleTests Math_Test()const;
	MultipleTests MaxMin_Test()const;
	MultipleTests Operators_Test()const;
	MultipleTests Rand_Test()const;
	MultipleTests NumericRand_Test()const;
	MultipleTests Product_Test() const;
	MultipleTests Relational_Test()const;
	MultipleTests Rounding_Test()const;
	MultipleTests Sum_Test()const;
	MultipleTests AuxiliarMath_Test()const;
	MultipleTests Cholesky_Test()const;


        MultipleTests AllTests() const;
    private:
        M_Matrix<T> M_;
    };
} //end of Markov_LA
}



#endif // MARKOV_LA_TESTS_H
