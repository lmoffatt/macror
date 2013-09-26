#include "Tests/Markov_LA/Matrix_Test_times.h"
#include "Markov_LA/matrixRand.h"
#include "Tests/timeOfFunctor.h"
#include "Markov_LA/matrixInverse.h"
#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixExp.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixOperators.h"


namespace Markov_Test
{

namespace Markov_LA_Test
{
    using namespace Markov_LA;
    using Borrowed::MersenneTwister::seedinit;
    template<typename T>
    Matrix_Test_times<T>::Matrix_Test_times(std::size_t nrows,std::size_t ncols):
	    TR_((seedinit(0))),
	    M_(Rand<T>(nrows,ncols,TR_))
    {}

    template<typename T>
    Matrix_Test_times<T>::Matrix_Test_times(std::size_t nrows_and_columns):
	    TR_((seedinit(0))),
	    M_(Rand<T>(nrows_and_columns,nrows_and_columns,TR_))
    {}


    template<typename T>
    Matrix_Test_times<T>&
	    Matrix_Test_times<T>::operator=(
		    const Matrix_Test_times<T>& other)
    {
	TR_=other.TR_;
	M_=other.M_;
	return *this;
    }

    template<typename T>
    Matrix_Test_times<T>::Matrix_Test_times(const Matrix_Test_times<T>& other):
	    TR_(other.TR_),
	    M_(other.M_)
    {}

    template<typename T>
    Matrix_Test_times<T>::Matrix_Test_times():
	    TR_(),
	    M_()
    {}






    template<typename T>
    double Matrix_Test_times<T>::Access()
    {
	Access_binder b(*this);
	TimeOfFunctor<Access_binder > time(b);
	return time();
    }


    template<typename T>
    double Matrix_Test_times<T>::Copy()
    {
	Copy_binder b(*this);
	TimeOfFunctor<Copy_binder > time(b);
	return time();
    }


    template<typename T>
    double Matrix_Test_times<T>::Sum()
    {
	Sum_binder b(*this);
	TimeOfFunctor<Sum_binder > time(b);
	return time();
    }

    template<typename T>
    double Matrix_Test_times<T>::Product()
    {
	Product_binder b(*this);
	TimeOfFunctor<Product_binder > time(b);
	return time();
    }

    template<typename T>
    double Matrix_Test_times<T>::Inverse()
    {
	if (ncols(M_)!=nrows(M_))
	    return 0;
	Inverse_binder b(*this);
	TimeOfFunctor<Inverse_binder > time(b);
	return time();
    }

    template<typename T>
    double Matrix_Test_times<T>::Expm()
    {
	if (ncols(M_)!=nrows(M_))
	    return 0;
	Expm_binder b(*this);
	TimeOfFunctor<Expm_binder > time(b);
	return time();
    }





    template<typename T>
    class Matrix_Test_times<T>::Access_binder
    {
    public:
	void operator()();
	Access_binder(Matrix_Test_times<T>& outer);
    private:
	Matrix_Test_times<T>&  outer_;
	std::size_t i_,j_;
	T result_;
    };





    template<typename T>
    class Matrix_Test_times<T>::Copy_binder
    {
    public:
	void operator()();
	Copy_binder(Matrix_Test_times<T>& outer);
    private:
	Matrix_Test_times<T>&  outer_;
	M_Matrix<T> result_;
    };


    template<typename T>
    class Matrix_Test_times<T>::Sum_binder
    {
    public:
	void operator()();
	Sum_binder(Matrix_Test_times<T>& outer);
    private:
	Matrix_Test_times<T>&  outer_;
	M_Matrix<T> other_;
	M_Matrix<T> result_;
    };








    template<typename T>
    class Matrix_Test_times<T>::Product_binder
    {
    public:
	void operator()();
	Product_binder(Matrix_Test_times<T>& outer);
    private:
	Matrix_Test_times<T>&  outer_;
	M_Matrix<T> transp_;
	M_Matrix<T> result_;

    };



    template<typename T>
    class Matrix_Test_times<T>::Inverse_binder
    {
    public:
	void operator()();
	Inverse_binder(Matrix_Test_times<T>& outer);
    private:
	Matrix_Test_times<T>&  outer_;
	M_Matrix<T> result_;

    };




    template<typename T>
    class Matrix_Test_times<T>::Expm_binder
    {
    public:
	void operator()();
	Expm_binder(Matrix_Test_times<T>& outer);
    private:
	Matrix_Test_times<T>&  outer_;
	M_Matrix<T> result_;

    };






    template<typename T>
    Matrix_Test_times<T>::Access_binder::Access_binder(
	     Matrix_Test_times<T>& outer):
	    outer_(outer),
	    i_(outer.TR_.randInt(nrows(outer.M_))),
	    j_(outer.TR_.randInt(ncols(outer.M_))),
	    result_()
    {};

    template<typename T>
    void Matrix_Test_times<T>::Access_binder::operator ()()
    {
	result_=outer_.M_(i_,j_);
    }




    template<typename T>
    Matrix_Test_times<T>::Copy_binder::Copy_binder(
	     Matrix_Test_times<T>& outer):
	    outer_(outer),
	    result_()
    {};

    template<typename T>
    void Matrix_Test_times<T>::Copy_binder::operator ()()
    {
	result_=outer_.M_;
    }



    template<typename T>
    Matrix_Test_times<T>::Sum_binder::Sum_binder(
	     Matrix_Test_times<T>& outer):
	    outer_(outer),
	    other_(Rand(outer_.M_,0)),
	    result_()
    {};

    template<typename T>
    void Matrix_Test_times<T>::Sum_binder::operator ()()
    {
	result_=outer_.M_+other_;
    }


    template<typename T>
    Matrix_Test_times<T>::Product_binder::Product_binder(
	     Matrix_Test_times<T>& outer):
	    outer_(outer),
	    transp_(Rand(Transpose(outer_.M_),0)),
	    result_()
    {};

    template<typename T>
    void Matrix_Test_times<T>::Product_binder::operator ()()
    {
	result_=outer_.M_*transp_;
    }



    template<typename T>
    Matrix_Test_times<T>::Inverse_binder::Inverse_binder(
	     Matrix_Test_times<T>& outer):
	    outer_(outer),
	    result_()
    {};

    template<typename T>
    void Matrix_Test_times<T>::Inverse_binder::operator ()()
    {
	result_=inv(outer_.M_);
    }



    template<typename T>
    Matrix_Test_times<T>::Expm_binder::Expm_binder(
	     Matrix_Test_times<T>& outer):
	    outer_(outer),
	    result_()
    {};

    template<typename T>
    void Matrix_Test_times<T>::Expm_binder::operator ()()
    {
	result_=expm(outer_.M_);
    }










    template class Matrix_Test_times<double>;

}
}
