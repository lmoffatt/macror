
/*!
 * @file matrixAritmetic.cpp @brief Implementation of aritmetic Operators.
   Aritmetic operators,addition, subtraction, multiplication or division,
  applied between 1. Each element of the matrix and a scalar. Or 2. Between
  homologous positions in the matrix.

 */



#include "Markov_LA/Matrix.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixAssigmentOp.h"
#include "Tests/AssertPlain.h"
#include "Markov_LA/matrixIO.h"




namespace Markov_LA
{

    /** @name Aritmetic operation between a Matrix and a scalar (single element)
     */
    //@{

    /**
    Scalar Addition.
    @returns a copy of the matrix with its values summed by x
    */
    template<typename T>
    M_Matrix<T> operator+(const M_Matrix<T>& x,T t)
    {    // we build the M_Matrix result
	M_Matrix<T> z(x);
	z+=t;
	return z;
    }

    /**
    Scalar Addition reverse order.
    */
    template<typename T>
    M_Matrix<T> operator+(T t,const M_Matrix<T>& x)
    {
	return x+t;
    }

    /**
    Scalar Subtraction.
    @returns a copy of the matrix with its values substracted by x
    */
    template<typename T>
    M_Matrix<T> operator-(const M_Matrix<T>& x,T t)
    {    // we build the M_Matrix result
	M_Matrix<T> z(x);
	z-=t;
	return z;
    };

    /**
    Scalar Subtraction reverse order.
    */
    template<typename T>
    M_Matrix<T> operator-(T t,const M_Matrix<T>& x)
    {
	return x-t;
    }

    /**
    Scalar Multiplication.
    @returns a copy of the matrix with its values multiplied by the value x
    */
    template<typename T>
    M_Matrix<T> operator*(const M_Matrix<T>& x,T t)
    {    // we build the M_Matrix result
	M_Matrix<T> z(x);
	z*=t;
	return z;
    }

    /**
    Scalar Multiplication reverse order.
    */
    template<typename T>
    M_Matrix<T> operator*(T t,const M_Matrix<T>& x)
    {
	return x*t;
    }


    /**
    Scalar Division.
    @returns a copy of the matrix with its values divided by x
    @returns a matrix of real numbers
*/
    template<typename T>
    M_Matrix<double> operator/(const M_Matrix<T>& x,T t)
    {    // we build the M_Matrix result
	M_Matrix<double> z(x);
	z/=double(t);
	return z;
    };

  /**
    Division by inhomogeneus types

    */

    template<typename T,typename S>
    M_Matrix<double> operator/(const M_Matrix<T>& x,S t)
    {    // we build the M_Matrix result
	M_Matrix<double> z(x);
	z/=double(t);
	return z;
    };









    /**
    Scalar Division reverse order.
    */
    template<typename T>
    M_Matrix<double> operator/(T t,const M_Matrix<T>& x)
    {
	M_Matrix<double> out(nrows(x),ncols(x));
	for (std::size_t i=0;i<size(x);i++)
	    out[i]=double(t)/double(x[i]);

	return out;
    }


    //@}


    /**
@name Template Instantations of Aritmetic Operations between a Matrix and a
scalar
 */
    //@{
    template M_Matrix<double> operator+(double t,const M_Matrix<double>& x);

    template M_Matrix<double> operator-(double t,const M_Matrix<double>& x);

    template M_Matrix<double> operator*(double t,const M_Matrix<double>& x);

    template M_Matrix<double> operator/(double t,const M_Matrix<double>& x);




    template M_Matrix<double> operator+(const M_Matrix<double>& x,double t);

    template M_Matrix<double> operator-(const M_Matrix<double>& x,double t);

    template M_Matrix<double> operator*(const M_Matrix<double>& x,double t);

    template M_Matrix<double> operator/(const M_Matrix<double>& x,double t);




    template M_Matrix<std::size_t> operator+(const M_Matrix<std::size_t>& x,
					     std::size_t t);

    template M_Matrix<std::size_t> operator-(const M_Matrix<std::size_t>& x,
					     std::size_t t);

    template M_Matrix<std::size_t> operator*(const M_Matrix<std::size_t>& x,
					     std::size_t t);



    template M_Matrix<double> operator/(const M_Matrix<double>& x,
					std::size_t t);



    template M_Matrix<double> operator/(const M_Matrix<std::size_t>& x,
					std::size_t t);






    //@}


    /**
@name Aritmetic operations applied between two Matrices
 */
    //@{

    /**
Matrix sum, element wise.
@pre \p nrows(x)==ncols(y) ncols(x)==ncols(y)
@return z, where nrows(z)=rows(x), ncols(z)=ncols(y) and z(i,j)= sum
on k of x(i,k)*y(k,j)
@warning it \c assert the preconditions
*/
    template<typename T>
    M_Matrix<T> operator+(const M_Matrix<T>& x,const M_Matrix<T>& y)
    {
	assert(size(x)==size(y));
	assert(nrows(x)==nrows(y));
	M_Matrix<T> z(x);
	for (size_t i=0; i<nrows(z); i++)
	    for (size_t j=0; j<ncols(z); j++)
		z(i,j)+=y(i,j);
	return z;
    }

    /**
Matrix sustraction, element wise.
@pre \p nrows(x)==ncols(y) ncols(x)==ncols(y)
@return z, where nrows(z)=rows(x), ncols(z)=ncols(y) and
z(i,j)= sum on k of x(i,k)*y(k,j)
@warning it \c assert the preconditions
*/
    template<typename T>
    M_Matrix<T> operator-(const M_Matrix<T>& x,const M_Matrix<T>& y)
    {
        if(size(x)!=size(y))
            assert(false);
        if (nrows(x)!=nrows(y))
            assert(false);
	M_Matrix<T> z(nrows(x),ncols(x));
	for (size_t i=0; i<size(z); i++)
	    // for (size_t j=0; j<ncols(z); j++)
	    z[i]=x[i]-y[i];
	return z;
    }




    /**
Multiplication of the elements of two matrices.
 @pre \p nrows(x)==ncols(y) ncols(x)==ncols(y)
 @return z, where nrows(z)=rows(x), ncols(z)=ncols(y)
and z(i,j)= sum on k of x(i,k)*y(k,j)
 @warning it \c assert the preconditions
*/
    template<typename T>
    M_Matrix<T> elemMult(const M_Matrix<T>& x,const M_Matrix<T>& y)
    {
	assert(size(x)==size(y));
	assert(nrows(x)==nrows(y));
	M_Matrix<T> z(x);
	for (size_t i=0; i<nrows(z); i++)
	    for (size_t j=0; j<ncols(z); j++)
		z(i,j)*=y(i,j);
	return z;
    }

    /**
Division of the elements of two matrices.
 @pre \p nrows(x)==ncols(y) ncols(x)==ncols(y)
 @return z, where nrows(z)=rows(x), ncols(z)=ncols(y)
and z(i,j)= sum on k of x(i,k)*y(k,j)
 @warning it \c assert the preconditions
*/
    template<typename T,typename S>
    M_Matrix<double> elemDiv(const M_Matrix<T>& x,const M_Matrix<S>& y)
    {
	assert(size(x)==size(y));
	assert(nrows(x)==nrows(y));
	M_Matrix<double> z(x);
	for (size_t i=0; i<nrows(z); i++)
	    for (size_t j=0; j<ncols(z); j++)
		z(i,j)/=double(y(i,j));
	return z;
    }

    /**
Safe Division of the elements of two matrices.
 @pre \p nrows(x)==ncols(y) ncols(x)==ncols(y)
 @return z, where nrows(z)=rows(x), ncols(z)=ncols(y)
and z(i,j)= sum on k of x(i,k)*y(k,j)
 @warning it \c assert the preconditions
*/
    template<typename T,typename S>
    M_Matrix<double> elemDivSafe(const M_Matrix<T>& x,const M_Matrix<S>& y)
    {
        assert(size(x)==size(y));
        assert(nrows(x)==nrows(y));
        M_Matrix<double> z(x);
        for (size_t i=0; i<nrows(z); i++)
            for (size_t j=0; j<ncols(z); j++)
                if (y(i,j)!=0)
                    z(i,j)/=double(y(i,j));
                else
                    z(i,j)=0;
        return z;
    }
    // @}


    /**
@name Template Instantations of Aritmetic Operations between two Matrices
 */
    //@{
    template M_Matrix<double> operator+(const M_Matrix<double>& x,
					const M_Matrix<double>& y);

    template M_Matrix<double> operator-(const M_Matrix<double>& x,
					const M_Matrix<double>& y);


    template M_Matrix<double> elemMult(const M_Matrix<double>& x,
					const M_Matrix<double>& y);

    template M_Matrix<std::size_t> elemMult(const M_Matrix<std::size_t>& x,
					const M_Matrix<std::size_t>& y);


    template M_Matrix<double> elemDiv(const M_Matrix<double>& x,
					const M_Matrix<double>& y);

    template M_Matrix<double> elemDiv(const M_Matrix<std::size_t>& x,
					const M_Matrix<std::size_t>& y);



    template M_Matrix<double> elemDiv(const M_Matrix<std::size_t>& x,
					const M_Matrix<double>& y);

    template M_Matrix<double> elemDiv(const M_Matrix<double>& x,
					const M_Matrix<std::size_t>& y);


    template M_Matrix<double> elemDivSafe(const M_Matrix<double>& x,
                                        const M_Matrix<double>& y);

    template M_Matrix<double> elemDivSafe(const M_Matrix<std::size_t>& x,
                                        const M_Matrix<std::size_t>& y);



    template M_Matrix<double> elemDivSafe(const M_Matrix<std::size_t>& x,
                                        const M_Matrix<double>& y);

    template M_Matrix<double> elemDivSafe(const M_Matrix<double>& x,
                                        const M_Matrix<std::size_t>& y);






    //@}




} //end of namespace Markov_LA
