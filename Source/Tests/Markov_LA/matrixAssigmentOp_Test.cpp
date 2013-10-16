#include "Markov_LA/matrixAssigmentOp.h"
#include "Markov_LA/matrixIO.h"
#include "Tests/Markov_LA/Markov_LA_Tests.h"
#include "Tests/AssertPlain.h"



namespace Markov_Test
{

namespace Markov_LA_Test
{
    using namespace Markov_LA;


/**
  @file matrixAssigmentOp_Test.h @brief test assigment operator global functions
  declared in the header file matrixAssigmentOp.h

   functions are
   matrix Op= matrix     with Op= _+ or -
   matrix Op=element    with Op = +,-, * and /

   also

   explicit convesion
   Matrix<T> (+/-)= Matrix<S>

   */

    template <typename T>
    template<typename S>
     MultipleTests Markov_LATest<T>::AssigmentOp_Test()  const  {

	MultipleTests result("matrixAssigmentOp.h",
			     "test against known cases");
	M_Matrix<T> sample(2,3);
	sample(0,0)=0.1;             sample(0,1)=4.5;	    sample(0,2)=2;
	sample(1,0)=3.4; 	    sample(1,1)=5;	    sample(1,2)=6;

	M_Matrix<T> expected(2,3);
	expected(0,0)=0.2;	    expected(0,1)=9.0;	    expected(0,2)=4;
	expected(1,0)=6.8;	    expected(1,1)=10;	    expected(1,2)=12;

	M_Matrix<T> All2(2,3);
	All2(0,0)=2;	    All2(0,1)=2;	    All2(0,2)=2;
	All2(1,0)=2;	    All2(1,1)=2;	    All2(1,2)=2;

	M_Matrix<T> Z(2,3);
	Z(0,0)=0;	    Z(0,1)=0;	    Z(0,2)=0;
	Z(1,0)=0;	    Z(1,1)=0;	    Z(1,2)=0;

	M_Matrix<T> original=sample;
	sample+=original;
	result.push_back(EqualValue_Test("operator +=",sample,expected));
	sample-=original;
	result.push_back(EqualValue_Test("operator -=",sample,original));
	sample-=original;
	result.push_back(EqualValue_Test("operator -= is inverse of operator+=",
					 sample,Z));

	sample+=original;

	M_Matrix<S> sample_S(2,3);
	sample_S(0,0)=S(4.5);   sample_S(0,1)=S(7.3);    sample_S(0,2)=S(8.2);
	sample_S(1,0)=S(3.11);  sample_S(1,1)=S(0.6);     sample_S(1,2)=S(5);

	expected(0,0)=0.1+S(4.5);expected(0,1)=4.5+S(7.3);expected(0,2)=2+S(8.2);
	expected(1,0)=3.4+S(3.11);expected(1,1)=5+S(0.6); expected(1,2)=6+S(5);

	sample+=sample_S;

	result.push_back(EqualValue_Test("operator +=(type cast)",
					 sample,expected));

	sample-=sample_S;

	result.push_back(EqualValue_Test("operator -=(type cast)",
					 sample,original));

	T a=2.54;

	expected(0,0)=0.1+a;    expected(0,1)=4.5+a;	expected(0,2)=2+a;
	expected(1,0)=3.4+a; 	expected(1,1)=5+a;	expected(1,2)=6+a;


	sample+=a;

	result.push_back(EqualValue_Test("operator +=(scalar)",
					 sample,expected));

	sample-=a;
	result.push_back(EqualValue_Test("operator -=(scalar)",
					 sample,original));


	expected(0,0)=0.1*a;    expected(0,1)=4.5*a;	expected(0,2)=2*a;
	expected(1,0)=3.4*a; 	expected(1,1)=5*a;	expected(1,2)=6*a;


	sample*=a;

	result.push_back(EqualValue_Test("operator *=(scalar)",
					 sample,expected));

	sample/=a;
	result.push_back(EqualValue_Test("operator /=(scalar)",
					 sample,original));
	return result;
    }

    template  MultipleTests Markov_LATest<double>::AssigmentOp_Test<std::size_t>()const;
 }

}
