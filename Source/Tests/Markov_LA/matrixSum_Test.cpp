#include "Markov_LA/matrixSum.h"
#include "Markov_LA/matrixMath.h"
#include "Markov_LA/matrixIO.h"

#include "Tests/Markov_LA/Markov_LA_Tests.h"
#include "Tests/AssertPlain.h"
#include "Markov_LA/matrixMath.h"



namespace Markov_Test
{

namespace Markov_LA_Test
{
    using namespace Markov_LA;

    template<typename T>
    MultipleTests Markov_LA_Test<T>::Sum_Test()
    {
	MultipleTests result("matrixSum.h",
			     "test by examples");
	M_Matrix<T> sample(2,3);

	  sample(0,0)=3.40;  sample(0,1)=6.0;    sample(0,2)=8.90;
	  sample(1,0)=-5.0; sample(1,1)=6.0;    sample(1,2)=3.90;


	M_Matrix<T> sum_each_col(1,3);
	sum_each_col(0,0)=-1.6;  sum_each_col(0,1)=12.0;    sum_each_col(0,2)=12.8;


	result.push_back(ElementaryTest(
			     "sum(matrix,false) sum each col",
			     "compare with known result",
			     (sum(sample,false)==sum_each_col)));

	M_Matrix<T> sum_each_row(2,1);
	sum_each_row(0,0)=18.3;
	sum_each_row(1,0)=4.9;


	result.push_back(ElementaryTest("sum(matrix,true) sum each row",
					"compare with each row summed up",
					(sum(sample,true)==sum_each_row)));

	M_Matrix<T> mean_each_col(1,3);
	mean_each_col(0,0)=-1.6/2.0;
	mean_each_col(0,1)=12.0/2.0;
	mean_each_col(0,2)=12.8/2.0;

	result.push_back(ElementaryTest("mean(matrix,false), mean each col",
					"compare with the actual"
					"mean of each col",
					(mean(sample,false)==mean_each_col)));
//---------------------------------------------------------------
	M_Matrix<T> mean_each_row(2,1);
	mean_each_row(0,0)=18.3/3.0;
	mean_each_row(1,0)=4.9/3.0;



	result.push_back(ElementaryTest("mean(matrix,true) mean each row",
					"compare with mean of each row",
					(mean(sample,true)==mean_each_row)));
//---------------------------------------------------------------

	M_Matrix<T> diff_on_row(2,3);
	diff_on_row(0,0)=3.4;  diff_on_row(0,1)=6.0-3.4;   diff_on_row(0,2)=8.9-6.0;
	diff_on_row(1,0)=-5.0;  diff_on_row(1,1)=6.0+5.0;   diff_on_row(1,2)=3.9-6.0;



	result.push_back(ElementaryTest("diff(sample,true) diff on row",
					"compare with diff on row",
					(diff(sample,true)==diff_on_row)));
//---------------------------------------------------------------
	M_Matrix<T> diff_on_col(2,3);
	diff_on_col(0,0)=3.4;  diff_on_col(0,1)=6.0;   diff_on_col(0,2)=8.9;
	diff_on_col(1,0)=-5.0-3.4;  diff_on_col(1,1)=6.0-6.0;diff_on_col(1,2)=3.9-8.9;


	result.push_back(ElementaryTest("diff(sample,false) diff on col",
					"compare with diff on col",
					(diff(sample,false)==diff_on_col)));
//---------------------------------------------------------------



	M_Matrix<T> sum_on_row(2,3);
	sum_on_row(0,0)=3.4;  sum_on_row(0,1)=6.0+3.4; sum_on_row(0,2)=8.9+6.0+3.4;
	sum_on_row(1,0)=-5.0; sum_on_row(1,1)=6.0-5.0;sum_on_row(1,2)=3.9+6.0-5.0;


	result.push_back(ElementaryTest("cumsum(matrix,true) cumsum on row",
					"compare with sum on row",
					(cumsum(sample,true)==sum_on_row)));
	result.push_back(ElementaryTest(
			     "cumsum is the inverse of diff",
			     "cumsum(diff(matrix,true),true)==matrix",
			     (cumsum(diff(sample,true),true)==sample)));


	M_Matrix<T> sum_on_col(2,3);
	sum_on_col(0,0)=3.4;  sum_on_col(0,1)=6.0;   sum_on_col(0,2)=8.9;
	sum_on_col(1,0)=-5.0+3.4;sum_on_col(1,1)=6.0+6.0;sum_on_col(1,2)=3.9+8.9;


	result.push_back(ElementaryTest("cumsum(matrix,false) on col",
					"compare with calculated cumsum on col"
					,(cumsum(sample,false)==sum_on_col)));
	result.push_back(ElementaryTest(
			     "cumsum is the inverse of diff",
			     "cumsum(diff(matrix,false),false)==matrix",
			     (cumsum(diff(sample,false),false)==sample)));


	T tot=23.2;


	result.push_back(ElementaryTest("totalsum(matrix)",
					"check with calculated result",
					(totalsum(sample)==tot)));
	result.push_back(ElementaryTest("totalmena(matrix)",
					"check with result",
					(totalmean(sample)==tot/6.0)));
	return result;

    }
    template MultipleTests Markov_LA_Test<double>::Sum_Test();
}
}
