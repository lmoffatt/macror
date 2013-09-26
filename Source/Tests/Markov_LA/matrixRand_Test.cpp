
#include "Borrowed/MersenneTwister.h"
#include "Markov_LA/matrixIO.h"

#include "Tests/Markov_LA/Markov_LA_Tests.h"
#include "Tests/AssertPlain.h"
#include "Markov_LA/Matrix.h"
#include "Markov_LA/matrixRand.h"
#include "Markov_LA/matrixRelational.h"
#include <time.h>


namespace Markov_Test
{

namespace Markov_LA_Test
{

void wait ( int miliseconds )
{
  clock_t endwait;
  endwait = clock () + miliseconds * CLOCKS_PER_SEC/1000 ;
  while (clock() < endwait) {}
}
    using namespace Markov_LA;
    template<typename T>
    MultipleTests Markov_LA_Test<T>::Rand_Test()

    {
	MultipleTests result("matrixRand.h",
		      "same seed means same sample");
	M_Matrix<T> rand_sample_0_1=Rand<T>(2,3,0);
	  M_Matrix<T> rand_sample_1_1=Rand<T>(2,3,1);

	  M_Matrix<T> rand_sample_1_2=Rand<T>(2,3,1);

	  M_Matrix<T> rand_sample_2=Rand<T>(2,3,2);


	  result.push_back(EqualValue_Test("Rand(), same seed",rand_sample_1_1,rand_sample_1_2));
	  result.push_back(EqualValue_Test("Rand(), rigth number of rows",nrows(rand_sample_1_1),std::size_t(2)));
	  result.push_back(EqualValue_Test("Rand(), rigth number of cols",ncols(rand_sample_1_1),std::size_t(3)));
	  wait(1);
	  // we have to wait a milisecond at least!;


	  M_Matrix<T> rand_sample_0_2=Rand<T>(2,3,0);

	  result.push_back(UnEqualValue_Test("Rand() different seed,"
					     "different sample",
					     rand_sample_1_1(0,0),rand_sample_2(0,0)));
	  result.push_back(UnEqualValue_Test("Rand() two automatic seeds",
					     rand_sample_0_1(0,0),rand_sample_0_2(0,0)));

	  result.push_back(ElementaryTest("Rand() less than 1",
					  "sample<1",
					  rand_sample_1_1<1.0));

		  result.push_back(ElementaryTest("Rand() more or equal to zero",
						  "sample>=0",
						  rand_sample_1_1>=0.0));

	  Borrowed::MersenneTwister::MTRand TR0;

	  Borrowed::MersenneTwister::MTRand TR1=TR0;

	  rand_sample_1_1=Rand<T>(2,3,TR0);

	  rand_sample_1_2=Rand<T>(2,3,TR1);

	  rand_sample_2=Rand<T>(2,3,TR0);

	  result.push_back(EqualValue_Test(
			       "Rand() initialization by same MTRand",
			       rand_sample_1_1,rand_sample_1_2));
	  result.push_back(UnEqualValue_Test(
			       "Rand() initialization by different MTRand",
			       rand_sample_1_1(0,0),rand_sample_2(0,0)));

	  M_Matrix<T> sample(4,5);
	  result.push_back(EqualValue_Test(
			       "Rand(), same initialization by matrix or size",
			       Rand<T>(sample,34),Rand<T>(4,5,34)));
	  return result;

      }

    template<typename T>
    MultipleTests Markov_LA_Test<T>::NumericRand_Test()

    {
        MultipleTests result("MersenneTwister.h",
                      "same seed means same sample");
        M_Matrix<T> rand_sample_0_1=Rand<T>(2,3,0);
          M_Matrix<T> rand_sample_1_1=Rand<T>(2,3,1);

          M_Matrix<T> rand_sample_1_2=Rand<T>(2,3,1);

          M_Matrix<T> rand_sample_2=Rand<T>(2,3,2);


          result.push_back(EqualValue_Test("Rand(), same seed",rand_sample_1_1,rand_sample_1_2));
          result.push_back(EqualValue_Test("Rand(), rigth number of rows",nrows(rand_sample_1_1),std::size_t(2)));
          result.push_back(EqualValue_Test("Rand(), rigth number of cols",ncols(rand_sample_1_1),std::size_t(3)));
          wait(1);
          // we have to wait a milisecond at least!;


          M_Matrix<T> rand_sample_0_2=Rand<T>(2,3,0);

          result.push_back(UnEqualValue_Test("Rand() different seed,"
                                             "different sample",
                                             rand_sample_1_1(0,0),rand_sample_2(0,0)));
          result.push_back(UnEqualValue_Test("Rand() two automatic seeds",
                                             rand_sample_0_1(0,0),rand_sample_0_2(0,0)));

          result.push_back(ElementaryTest("Rand() less than 1",
                                          "sample<1",
                                          rand_sample_1_1<1.0));

                  result.push_back(ElementaryTest("Rand() more or equal to zero",
                                                  "sample>=0",
                                                  rand_sample_1_1>=0.0));

          Borrowed::MersenneTwister::MTRand TR0;

          Borrowed::MersenneTwister::MTRand TR1=TR0;

          rand_sample_1_1=Rand<T>(2,3,TR0);

          rand_sample_1_2=Rand<T>(2,3,TR1);

          rand_sample_2=Rand<T>(2,3,TR0);

          result.push_back(EqualValue_Test(
                               "Rand() initialization by same MTRand",
                               rand_sample_1_1,rand_sample_1_2));
          result.push_back(UnEqualValue_Test(
                               "Rand() initialization by different MTRand",
                               rand_sample_1_1(0,0),rand_sample_2(0,0)));

          M_Matrix<T> sample(4,5);
          result.push_back(EqualValue_Test(
                               "Rand(), same initialization by matrix or size",
                               Rand<T>(sample,34),Rand<T>(4,5,34)));
          return result;

      }



    template MultipleTests Markov_LA_Test<double>::Rand_Test();
}
}
