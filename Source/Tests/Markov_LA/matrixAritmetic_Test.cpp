#include "Tests/Markov_LA/Markov_LA_Tests.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixIO.h"


#include "Tests/AssertPlain.h"


namespace Markov_Test
{

namespace Markov_LA_Test
{
    using namespace Markov_LA;
    /**
      It tests all the aritmetic functions on matrixs declared in the file
matrixAritmetic.h
those are:
       matrix Op matrix with Op= +, -, elemDiv and elemMult

       matrix Op element and

       element Op matrix  with Op= +, -, *, /

      */



    template<typename T>
    MultipleTests Markov_LA_Test<T>::Aritmetic_Test()
    {
	MultipleTests result("matrixAritmetic.h",
			     "test examples");

	M_Matrix<T> B(2,3);
	B(0,0)=0.1;             B(0,1)=4.5;	    B(0,2)=2;
	B(1,0)=3.4; 	    B(1,1)=5;	    B(1,2)=6;

	M_Matrix<T> C(2,3);
	C(0,0)=0.2;	    C(0,1)=9.0;	    C(0,2)=4;
	C(1,0)=6.8;	    C(1,1)=10;	    C(1,2)=12;

	M_Matrix<T> All2(2,3);
	All2(0,0)=2;	    All2(0,1)=2;	    All2(0,2)=2;
	All2(1,0)=2;	    All2(1,1)=2;	    All2(1,2)=2;

	M_Matrix<T> Z(2,3);
	Z(0,0)=0;	    Z(0,1)=0;	    Z(0,2)=0;
	Z(1,0)=0;	    Z(1,1)=0;	    Z(1,2)=0;



	result.push_back(EqualValue_Test("operator + on matrix",B+B,C));
	result.push_back(EqualValue_Test("operator - on matrix",C-B,B));

	result.push_back(EqualValue_Test("elemDiv",elemDiv(C,All2),B));
	result.push_back(EqualValue_Test("elemenDiv",elemDiv(C,B),All2));

	result.push_back(EqualValue_Test("elemMult",elemMult(B,All2),C));
	result.push_back(EqualValue_Test("elemMult",elemMult(All2,B),C));

	result.push_back(EqualValue_Test("operator -",B-B,Z));


	T a=2;
	result.push_back(EqualValue_Test("operator *(sclar)",B*a,C));

	T b;
	if (std::numeric_limits<T>::is_signed)
	    b=-23.6795236;
	else
	    b=23.6795236;

	result.push_back(EqualValue_Test("commutative product by scalar",B*b,b*B));

	M_Matrix<T> D(2,3);
	D(0,0)=T(0.2)*b;	    D(0,1)=T(9.0)*b;	    D(0,2)=T(4)*b;
	D(1,0)=T(6.8)*b;	    D(1,1)=T(10)*b;	    D(1,2)=T(12)*b;

	M_Matrix<T> E(2,3);
	E(0,0)=b/T(0.2);	    E(0,1)=b/T(9.0);	    E(0,2)=b/T(4);
	E(1,0)=b/T(6.8);	    E(1,1)=b/T(10);	    E(1,2)=b/T(12);

	M_Matrix<T> F(2,3);
	F(0,0)=T(0.2)+b;	    F(0,1)=T(9.0)+b;	    F(0,2)=T(4)+b;
	F(1,0)=T(6.8)+b;	    F(1,1)=T(10)+b;	    F(1,2)=T(12)+b;


	result.push_back(EqualValue_Test("operator * (scalar)",C*b,D));

	result.push_back(EqualValue_Test("operator / scalar",C,D/b));

	result.push_back(EqualValue_Test("operator /(scalar,matrix)",b/C,E));

	result.push_back(EqualValue_Test("operator + (scalar)",C+b,F));
	result.push_back(EqualValue_Test("operator -(scalar)",F-b,C));

    return result;


    }


    template MultipleTests Markov_LA_Test<double>::Aritmetic_Test();
}
}
