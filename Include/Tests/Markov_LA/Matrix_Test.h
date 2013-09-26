#ifndef MATRIX_TEST_H
#define MATRIX_TEST_H


#include <cstdlib>
#include <limits>
#include <vector>
#include "Markov_LA/Matrix.h"
#include "Tests/getTimeMs64.h"

#include "Tests/ElementaryTest.h"
#include "Tests/MultipleTests.h"
namespace Markov_Test
{

namespace Markov_LA_Test
{
    using namespace Markov_LA;
    template<typename T>
    class Matrix_Test//:public ::ABC_Test
    {
    public:

	/// virtual formated output

	Matrix_Test();

	MultipleTests DefaultConstructor_Test();

	MultipleTests EmptyShellConstructor_Test();
	MultipleTests RegularType_Test();
	MultipleTests StringConstructor_Test();
	MultipleTests TypeCastConstructor_Test();
	MultipleTests ValueAssigment_Test();
	MultipleTests VectorConstructor_Test();

	MultipleTests RowCopy_Test();
	MultipleTests ColumnCopy_Test();
	MultipleTests RowInsert_Test();
	MultipleTests ColumnInsert_Test();
	MultipleTests All_Tests();
    };
}
}










#endif // MATRIX_TEST_H
