#include "Markov_LA/matrixMath.h"
#include <cmath>

namespace Markov_LA
{


    /**
     Absolute value of the elements of a Matrix
     @returns a copy
     @post abs(x)[i]==abs(x[i])
     */

    template<typename T>
    M_Matrix<T>  abs(const M_Matrix<T>& x)
    {
	M_Matrix<T> y(x);
	for (std::size_t i=0; i<size(x); ++i)
	    y[i]=std::abs(x[i]);
	return y;
    }


    /**
    Additive Inverse. Returns a copy of the matrix changing the signs of all
    its elements.
    @returns a copy of *this with its values negated
    @post \p (-(x))[i]=-(x[i])
*/
    template<typename T>
    M_Matrix<T> operator-(const M_Matrix<T>& x)
    {
	M_Matrix<T> y(x);
	for (std::size_t i=0; i<size(x); ++i)
	    y[i]=-x[i];
	return y;
    }



    /**
    Natural exponential of the value of the elements of a Matrix
    @returns a copy
    @post  exp(x)[i]==exp(x[i])
    */
    template<typename T>
    M_Matrix<T>  exp(const M_Matrix<T>& x)
    {
	M_Matrix<T> y(x);
	for (std::size_t i=0; i<size(x); ++i)
	    y[i]=std::exp(x[i]);
	return y;
    }


    /**
    Power of ten of the value of the elements of a Matrix
    @returns a copy
    @post  exp10(x)[i]==exp10(x[i])
    */

    template<typename T>
    M_Matrix<T>  exp10(const M_Matrix<T>& x)
    {
	M_Matrix<T> y(x);
	for (std::size_t i=0; i<size(x); ++i)
	    y[i]=std::exp(x[i]*std::log(10));
	return y;
    }


    /**
    Logarithm base ten of the value of the elements of a Matrix
    @returns a copy
    @post  log10(x)[i]==log10(x[i])
    */
    template<typename T>
    M_Matrix<T>  log10(const M_Matrix<T>& x)
    {
	M_Matrix<T> y(x);
	for (std::size_t i=0; i<size(x); ++i)
	    y[i]=std::log10(x[i]);
	return y;
    }

    /**
    Logarithm base e of the value of the elements of a Matrix
    @returns a copy
    @post  log(x)[i]==log(x[i])
    */
    template<typename T>
    M_Matrix<T>  log(const M_Matrix<T>& x)
    {
	M_Matrix<T> y(x);
	for (std::size_t i=0; i<size(x); ++i)
	    y[i]=std::log(x[i]);
	return y;
    }

    /**
    floor the value of the elements of a Matrix
    @returns a copy
    @post  floor(x)[i]==floor(x[i])
    */
    template<typename T>
    M_Matrix<T>  floor(const M_Matrix<T>& x)
    {
        M_Matrix<T> y(x);
        for (std::size_t i=0; i<size(x); ++i)
            y[i]=std::floor(x[i]);
        return y;
    }

    /**
    ceil the value of the elements of a Matrix
    @returns a copy
    @post  floor(x)[i]==floor(x[i])
    */
    template<typename T>
    M_Matrix<T>  ceil(const M_Matrix<T>& x)
    {
        M_Matrix<T> y(x);
        for (std::size_t i=0; i<size(x); ++i)
            y[i]=std::ceil(x[i]);
        return y;
    }




    /**
    Square root of the value of the elements of a Matrix
    @returns a copy
    @post  sqrt(x)[i]==sqrt(x[i])
    */
    template<typename T>
    M_Matrix<T>  sqrt(const M_Matrix<T>& x)
    {
	M_Matrix<T> y(x);
	for (std::size_t i=0; i<size(x); ++i)
	    y[i]=std::sqrt(x[i]);
	return y;
    }









    template
    M_Matrix<double>  abs(const M_Matrix<double>& x);

    template
    M_Matrix<double> operator-(const M_Matrix<double>& x);

    template
    M_Matrix<double>  exp(const M_Matrix<double>& x);


    template
    M_Matrix<double>  exp10(const M_Matrix<double>& x);

    template
    M_Matrix<double>  log10(const M_Matrix<double>& x);

    template
    M_Matrix<double>  log(const M_Matrix<double>& x);

    template
    M_Matrix<double>  floor(const M_Matrix<double>& x);

    template
    M_Matrix<double>  ceil(const M_Matrix<double>& x);


    template
    M_Matrix<double>  sqrt(const M_Matrix<double>& x);

}


