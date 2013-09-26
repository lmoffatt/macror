#include "Tests/Markov_LA/Markov_LA_Tests.h"
#include "Tests/ElementaryTest.h"
#include "Markov_LA/matrixCholesky.h"
#include "Markov_LA/matrixOperators.h"
#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixIO.h"

namespace Markov_Test
{

namespace Markov_LA_Test
{
using namespace Markov_LA;
using namespace Markov_IO;

template<typename T>
MultipleTests Markov_LA_Test<T>::Cholesky_Test()
{

    MultipleTests result("matrixCholesky.h","test a given example");

    M_Matrix<T> sample(3,3);
    sample(0,0)=3.4000;  sample(0,1)=6.0000;    sample(0,2)=8.9000;
    sample(1,0)=-5.0000; sample(1,1)=6.0000;    sample(1,2)=3.9000;
    sample(2,0)=-2.0000; sample(2,1)=-6.0000;    sample(2,2)=9.5000;

    M_Matrix<T> expected(3,3);
    expected(0,0)=11.259218445345130;
    expected(0,1)= 4.770313344635852;
    expected(0,2)= 3.708072651993052;

    expected(1,0)=0;
    expected(1,1)=7.311231810987058 ;
    expected(1,2)=-0.908009570248526;

    expected(2,0)=0;
    expected(2,1)=0;
    expected(2,2)=10.755264563360509;

    result.push_back(EqualValue_Test("cholesky a known sample",
                                     chol(sample*Transpose(sample),"U"),expected));

    result.push_back(EqualValue_Test("cholesky a known sample",
                                     chol(sample*Transpose(sample))*
                                     Transpose(chol(sample*Transpose(sample))),
                                     sample*Transpose(sample)));




    return result;


}

template MultipleTests Markov_LA_Test<double>::Cholesky_Test();

}
}

