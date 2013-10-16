#ifndef MATRIX_TEST_H
#define MATRIX_TEST_H


#include <cstdlib>
#include <limits>
#include <vector>
#include "Markov_LA/Matrix.h"
#include "Tests/getTimeMs64.h"

#include "Tests/ElementaryTest.h"
#include "Tests/MultipleTests.h"
#include "Tests/All_Tests.h"
namespace Markov_Test
{

namespace Markov_LA_Test
{
    using namespace Markov_LA;
    template<typename T>
    class Matrix_Test:public All_Tests
    {
    public:

	/// virtual formated output

	Matrix_Test();

        virtual MultipleTests AllTests(Markov_Console::Markov_CommandManager* cm,
                                       const std::string varNameTested);
       // virtual MultipleTests AllTests()=0;
        static std::string TestName();

        virtual std::string myTest()const;

        virtual std::string testedClass()const;




	MultipleTests DefaultConstructor_Test()const;

	MultipleTests EmptyShellConstructor_Test()const;
	MultipleTests RegularType_Test()const;
	MultipleTests StringConstructor_Test()const;
	MultipleTests TypeCastConstructor_Test()const;
	MultipleTests ValueAssigment_Test()const;
	MultipleTests VectorConstructor_Test()const;

	MultipleTests RowCopy_Test()const;
	MultipleTests ColumnCopy_Test()const;
	MultipleTests RowInsert_Test()const;
	MultipleTests ColumnInsert_Test()const;
	MultipleTests AllTests()const;

    };
}
}










#endif // MATRIX_TEST_H
