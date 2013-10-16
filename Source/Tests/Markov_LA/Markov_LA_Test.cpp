#include "Markov_LA/matrixRand.h"
#include "Tests/Markov_LA/Markov_LA_Tests.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_IO/Object.h"


namespace Markov_Test
{

namespace Markov_LA_Test
{
using namespace Markov_LA;
using Markov_IO::press_any_key_to_continue;



template<typename T>
MultipleTests Markov_LATest<T>::AllTests()const
{
    MultipleTests result("Markov_LA namespace",
		   "test one by one each header");
    result.push_back(Product_Test());
    result.push_back(Expm_Test());
    result.push_back(IO_Test());
    result.push_back(Init_Test());
    result.push_back(Inverse_Test());
    result.push_back(Aritmetic_Test());
    result.push_back(AssigmentOp_Test<std::size_t>());
    result.push_back(Math_Test());
    result.push_back(MaxMin_Test());
    result.push_back(Operators_Test());
    result.push_back(Rand_Test());
    result.push_back(Relational_Test());
    result.push_back(Rounding_Test());
    result.push_back(Sum_Test());
    result.push_back(AuxiliarMath_Test());
    result.push_back(Cholesky_Test());

    Matrix_Test<double> mdTest;
    result.push_back(mdTest.AllTests());

    Matrix_Test<std::size_t> msTest;
    result.push_back(msTest.AllTests());
    ToleranceComparison_Test tTest;
    result.push_back(tTest.AllTests());
    return result;


}

template<typename T>
Markov_LATest<T>::Markov_LATest():
    M_(){}

template<typename T>
Markov_LATest<T>::Markov_LATest(
    const Markov_LATest& other):
    M_(other.M_){}

template<typename T>
Markov_LATest<T>::Markov_LATest(const M_Matrix<T>& sample):
    M_(sample){}

template<typename T>
Markov_LATest<T>::Markov_LATest(std::size_t size):
    M_(Rand<T>(size,size,0)){}

template<typename T>
MultipleTests Markov_LATest<T>::AllTests(Markov_Console::Markov_CommandManager* cm,const std::string varNameTested)
{
  return AllTests();
}
// virtual MultipleTests AllTests()=0;
template<typename T>
 std::string Markov_LATest<T>::TestName(){
  return "Linear_Algebra_Test";
}

template<typename T>
 std::string Markov_LATest<T>::myTest()const{
  return TestName();
}

template<typename T>
 std::string Markov_LATest<T>::testedClass()const{
  return Markov_IO::Object< Markov_LA::M_Matrix<T> >::ClassName();
}




template class Markov_LATest<double>;

/*
MultipleTests Markov_LA_Test<T>::ProductTest();
MultipleTests Markov_LA_Test<T>::Inverse_Test();
MultipleTests Markov_LA_Test<T>::Expm_Test();
MultipleTests Markov_LA_Test<T>::IO_test();
MultipleTests Markov_LA_Test<T>::Init_Test();
MultipleTests Markov_LA_Test<T>::Math_Test();
MultipleTests Markov_LA_Test<T>::MaxMin_Test();
MultipleTests Markov_LA_Test<T>::Rand_Test();
MultipleTests Markov_LA_Test<T>::Relational_Test();
MultipleTests Markov_LA_Test<T>::Rounding_Test();
*/
}
}
