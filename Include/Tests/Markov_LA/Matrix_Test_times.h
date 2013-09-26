#ifndef MATRIX_TEST_TIMES_H
#define MATRIX_TEST_TIMES_H
#include "Markov_LA/Matrix.h"
#include "Borrowed/MersenneTwister.h"

namespace Markov_Test
{

    namespace Markov_LA_Test
    {

	using namespace Markov_LA;
	template<typename T>
	class Matrix_Test_times
	{
	public:
	    Matrix_Test_times(std::size_t nrows,std::size_t ncols);

	    Matrix_Test_times(std::size_t nrows_and_columns);

	    Matrix_Test_times<T>& operator=(const Matrix_Test_times<T>& other);

	    Matrix_Test_times(const Matrix_Test_times<T>& other);

	    Matrix_Test_times();

	    double Access();
	    double Copy();
	    double Sum();
	    double Product();
	    double Inverse();
	    double Expm();

	private:
	    Borrowed::MersenneTwister::MTRand      TR_;
	    M_Matrix<T>  M_;
	    class Access_binder;
	    class Copy_binder;
	    class Sum_binder;
	    class Product_binder;
	    class Inverse_binder;
	    class Expm_binder;

	};
    };

};
#endif // MATRIX_TEST_TIMES_H
