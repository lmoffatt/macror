#include "Markov_LA/matrixIO.h"

#include "Tests/Markov_LA/Markov_LA_Tests.h"
#include "Tests/AssertPlain.h"
#include "Markov_LA/Matrix.h"
#include "Markov_LA/matrixInit.h"
#include "Markov_LA/matrixProduct.h"

#include "Markov_LA/matrixOperators.h"

namespace Markov_Test
{

namespace Markov_LA_Test
{
    using namespace Markov_LA;

    template<typename T>
    MultipleTests Markov_LA_Test<T>::Product_Test()

    {
	MultipleTests result("matrixProduct.h",
		      "explicit comparison to known case");
	M_Matrix<T> sample(2,3);

	  sample(0,0)=3.4;  sample(0,1)=6;    sample(0,2)=8.9;
	  sample(1,0)=-5; sample(1,1)=6;    sample(1,2)=3.9;

	  M_Matrix<T> other(3,4);
	  other(0,0)=-2.4;  other(0,1)=3;  other(0,2)=4.3; other(0,3)=-3.7;
	  other(1,0)=0;  other(1,1)=0.23;  other(1,2)=6.2; other(1,3)=-5.4;
	  other(2,0)=-3.4; other(2,1)=7.3; other(2,2)=-1.8; other(2,3)=-2.1;

	  M_Matrix<T> expected(2,4);
	  expected(0,0)=-38.42; expected(0,1)= 76.55; expected(0,2)=35.8; expected(0,3)=-63.67;

	  expected(1,0)= -1.26; expected(1,1)= 14.85;expected(1,2)=8.68; expected(1,3)=-22.09;



	  M_Matrix<T> sampleT(3,2);

	  sampleT(0,0)=3.4;  sampleT(1,0)=6;    sampleT(2,0)=8.9;
	  sampleT(0,1)=-5; sampleT(1,1)=6;    sampleT(2,1)=3.9;

	  M_Matrix<T> otherT(4,3);
	  otherT(0,0)=-2.4;  otherT(1,0)=3;
	  otherT(0,1)=0;  otherT(1,1)=0.23;
	  otherT(0,2)=-3.4; otherT(1,2)=7.3;

	  otherT(2,0)=4.3;
	  otherT(3,0)=-3.7;
	   otherT(2,1)=6.2;
	   otherT(3,1)=-5.4;

	    otherT(2,2)=-1.8; otherT(3,2)=-2.1;






	  result.push_back(EqualValue_Test("matrix product,* ",
					   sample*other,expected));
	  result.push_back(EqualValue_Test("TranspMult()",
					   TranspMult(sampleT,other),expected));
	  result.push_back(EqualValue_Test("multTransp()",
					   multTransp(sample,otherT),expected));
		  return result;


      }
    template MultipleTests Markov_LA_Test<double>::Product_Test();
}
}
