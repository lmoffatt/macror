#include "Tests/Markov_LA/Matrix_Test.h"
#include "Markov_LA/matrixIO.h"
#include "Tests/AssertPlain.h"
#include "Tests/RegularType_Test.h"

namespace Markov_Test
{

namespace Markov_LA_Test
{
    using namespace Markov_LA;

    template<typename T>
    Matrix_Test<T>::Matrix_Test(){}




    template<typename T>
    MultipleTests Matrix_Test<T>:: DefaultConstructor_Test()const
    {
	MultipleTests tests(
		    "",
		    "test ");
	M_Matrix<T> A;
	tests.push_back(IsZero_Test("size()",size(A)));
	tests.push_back(IsZero_Test("ncols()",ncols(A)));
	tests.push_back(IsZero_Test("nrows()",nrows(A)));
	return tests;
     }

    template<typename T>
    MultipleTests Matrix_Test<T>::EmptyShellConstructor_Test() const
    {

	MultipleTests result("Empty-Shell Constructor",
		      "It should have the specified size");
	std::size_t n=5;
	std::size_t m=3;
	// int64_t start=GetTimeMs64();
	M_Matrix<T> B(n,m);

	result.push_back(EqualValue_Test("right number of cells",
					 n*m,
					 size(B)));
	result.push_back(EqualValue_Test("right number of rows",
					 n,
					 nrows(B)));
	result.push_back(EqualValue_Test("right number of columns",
					 m,
					 ncols(B)));

	for (std::size_t i=0;i<n;i++)
	    for (std::size_t j=0; j<m; j++)
		B(i,j)=i*m+j;


	for (std::size_t i=0;i<n;i++)
	    for (std::size_t j=0; j<m; j++)
		result.push_back(EqualValue_Test(
				     "values written and recovered",
				     double(i*m+j),double(B(i,j))));

	for (std::size_t n=0;n<size(B);n++)
	    B[n]=B[n]*B[n];
	for (std::size_t n=0;n<size(B);n++)
	    result.push_back(EqualValue_Test(
				 "value written and recovered",
				 double(n*n),double(B[n])));

	return result;

    }


    template<typename T>
    MultipleTests Matrix_Test<T>::RegularType_Test() const
    {

	M_Matrix<T> B(2,3);
	B(0,0)=0.1;	    B(0,1)=4.2;	    B(0,2)=2;
	B(1,0)=3.4;	    B(1,1)=5;	    B(1,2)=6;

	M_Matrix<T> A(3,3);
	if (std::numeric_limits<T>::is_signed)
	{
	    A(0,0)=3.4000;  A(0,1)=6.0000;    A(0,2)=8.9000;
	    A(1,0)=-5.0000; A(1,1)=6.0000;    A(1,2)=3.9000;
	    A(2,0)=-2.0000; A(2,1)=-6.0000;    A(2,2)=9.5000;
	}
	else
	{
	    A(0,0)=3.4000;  A(0,1)=6.0000;    A(0,2)=8.9000;
	    A(1,0)=5.0000; A(1,1)=6.0000;    A(1,2)=3.9000;
	    A(2,0)=2.0000; A(2,1)=6.0000;    A(2,2)=9.5000;

	}
	std::vector<M_Matrix<T> > x;
	x.push_back(B);
	x.push_back(A);


	Markov_Test::RegularType_Test<Markov_LA::M_Matrix<T> >  regTest(x);
	return regTest.AllTest();
    }

    template<typename T>
    MultipleTests Matrix_Test<T>:: StringConstructor_Test() const
    {
	MultipleTests result("Test constructor based on string",
			     "Valid matrix from string");
	std::string s;
	if (!std::numeric_limits<T>::is_exact)
	    s=" 0.1  4  2  \n  3.4  5  6 \n" ;
	else
	    s=" 0  4  2  \n  3  5  6 \n" ;

	M_Matrix<T> A(s);

	M_Matrix<T> B(2,3);
	B(0,0)=0.1;
	B(0,1)=4;
	B(0,2)=2;
	B(1,0)=3.4;
	B(1,1)=5;
	B(1,2)=6;

	result.push_back(EqualValue_Test("Direct comparison", B,A));

	return result;
    }
    template<typename T>
    MultipleTests Matrix_Test<T>:: TypeCastConstructor_Test() const
    {
	MultipleTests result("Test constructor based on typecast on std::size_t",
			     "Should be equal");

	M_Matrix<std::size_t> a(" 0  4  2  \n  3  5  6 \n" );
	M_Matrix<T> A(a);
	M_Matrix<T> B(" 0  4  2  \n  3  5  6 \n" );

	result.push_back(EqualValue_Test("Equal",B,A));
	return result;

    }
    template<typename T>
    MultipleTests Matrix_Test<T>:: ValueAssigment_Test() const
    {
	MultipleTests result("Test assigment to a value",
			     "All cell equal to the value");
	M_Matrix<T> B(" 0  4  2  \n  3  5  6 \n" );

	B=4.3;

	for (std::size_t n=0;n<size(B);n++)
	    result.push_back(EqualValue_Test("Equal to assigned value",
					     T(4.3),B[n]));
	return result;

    }
    template<typename T>
    MultipleTests Matrix_Test<T>:: VectorConstructor_Test() const
    {
	MultipleTests result("Constructor based on vector",
			     "rigth values");
	std::vector<T> datav(6);
	datav[0]=0.1;
	datav[1]=4;
	datav[2]=2;
	datav[3]=3.4;
	datav[4]=5;
	datav[5]=6;

	M_Matrix<T> B(2,3);
	B(0,0)=0.1;
	B(0,1)=4;
	B(0,2)=2;
	B(1,0)=3.4;
	B(1,1)=5;
	B(1,2)=6;



	M_Matrix<T>  x(3,2,datav);

	result.push_back(EqualValue_Test("test matrix right",B,x));
	return result;

    }

    template<typename T>
    MultipleTests Matrix_Test<T>:: RowCopy_Test() const
    {
	MultipleTests result("Row copy being tested",
		      "example test");
	M_Matrix<T> B(2,3);
	B(0,0)=0.1;	    B(0,1)=4;	    B(0,2)=2;
	B(1,0)=3.4;	    B(1,1)=5;	    B(1,2)=6;

	M_Matrix<T> expected(1,3);
	expected(0,0)=3.4;	    expected(0,1)=5;	    expected(0,2)=6;

	M_Matrix<T> actual=B(1,":");

	result.push_back(EqualValue_Test("example",expected,actual));
	return result;
    }

    template<typename T>
    MultipleTests Matrix_Test<T>:: ColumnCopy_Test() const
    {
	MultipleTests result("Column copy being tested",
		      "Columns are copied right");
	M_Matrix<T> B(2,3);
	B(0,0)=0.1;	    B(0,1)=4.2;	    B(0,2)=2;
	B(1,0)=3.4;	    B(1,1)=5;	    B(1,2)=6;

	M_Matrix<T> expected(2,1);
	expected(0,0)=4.2;
	expected(1,0)=5;

	M_Matrix<T> actual=B(":",1);

	result.push_back(EqualValue_Test("test column copy",
					 expected,
					 actual));
	return result;

    }

    template<typename T>
    MultipleTests Matrix_Test<T>:: RowInsert_Test() const
    {
	MultipleTests result("Row insert being tested",
			     "rigth insertion in example");
	M_Matrix<T> B(2,3);
	B(0,0)=0.1;	    B(0,1)=4;	    B(0,2)=2;
	B(1,0)=3.4;	    B(1,1)=5;	    B(1,2)=6;

	M_Matrix<T> inserted(1,3);
	inserted(0,0)=2.4;	    inserted(0,1)=3;	    inserted(0,2)=45;

	M_Matrix<T> expected(2,3);
	expected(0,0)=0.1;	    expected(0,1)=4;	    expected(0,2)=2;
	expected(1,0)=2.4;	    expected(1,1)=3;	    expected(1,2)=45;
	M_Matrix<T> actual=B(1,":",inserted);

	result.push_back(EqualValue_Test("Inserted row is right",
					 expected, actual));
	return result;
    }

    template<typename T>
    MultipleTests Matrix_Test<T>:: ColumnInsert_Test() const
    {
	MultipleTests result("Column insert",
		      "Right insertion in example");
	M_Matrix<T> B(2,3);
	B(0,0)=0.1;	    B(0,1)=4;	    B(0,2)=2;
	B(1,0)=3.4;	    B(1,1)=5;	    B(1,2)=6;

	M_Matrix<T> inserted(2,1);
	inserted(0,0)=2.4;
	inserted(1,0)=3;

	M_Matrix<T> expected(2,3);
	expected(0,0)=0.1;	    expected(0,1)=4;	    expected(0,2)=2.4;
	expected(1,0)=3.4;	    expected(1,1)=5;	    expected(1,2)=3;
	M_Matrix<T> actual=B(":",2,inserted);
	result.push_back(EqualValue_Test("Expected insertion",
					 expected,actual));
	return result;
    }

    template<typename T>
MultipleTests Matrix_Test<T>::AllTests(Markov_Console::Markov_CommandManager* cm,
                                   const std::string varNameTested){

  return AllTests();

}
   // virtual MultipleTests AllTests()=0;

    template<typename T>
     std::string Matrix_Test<T>::TestName()
     {
       return "Matrix_Test";
     }

    template<typename T>
     std::string Matrix_Test<T>::myTest()const
     {
       return TestName();
     }

    template<typename T>
     std::string Matrix_Test<T>::testedClass()const
     {
       return "";
     }




    template<typename T>
    MultipleTests Matrix_Test<T>::AllTests() const
    {
	MultipleTests result("M_Matrix class",
			     "All test are right");
	result.push_back(DefaultConstructor_Test());
	result.push_back(EmptyShellConstructor_Test());
	result.push_back(RegularType_Test());
	result.push_back(StringConstructor_Test());
	result.push_back(ValueAssigment_Test());
	result.push_back(VectorConstructor_Test());
	result.push_back(RowCopy_Test());
	result.push_back(ColumnCopy_Test());
	result.push_back(RowInsert_Test());
	return result;
    }

    template class Matrix_Test<double>;
    template class Matrix_Test<std::size_t>;


}

}

