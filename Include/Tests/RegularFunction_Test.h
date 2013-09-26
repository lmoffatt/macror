#ifndef REGULARFUNCTION_TEST_H
#define REGULARFUNCTION_TEST_H


namespace Markov_Test
{



/**
   Asserts that modifying a Copy of an object do not alter the original
   @tparam T models a regular type
   @tparam UnaryOperation Operation from T->T
   @param a sample object under test
   @param Op operation under test: it alter the class T
*/
template<>
void CopiesAreIndependent_Test()
{
    T b(a);
    T c(b);
    b=Op(b);
    if (b!=a)
	ASSERT_EQ_M(c,a,b);
}

}
#endif // REGULARFUNCTION_TEST_H
