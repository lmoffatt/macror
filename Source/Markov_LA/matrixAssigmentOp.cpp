/*!
 * @file matrixAssigmentOp.cpp @brief Assigment Operators Implementation

Assigment aritmetic operators on single values or on another Matrix.

 */
#include "Markov_LA/matrixAssigmentOp.h"
#include "Tests/AssertPlain.h"



namespace Markov_LA
{

    /** @name Aritmetic Assigment Operations between a Matrix and a scalar
   (single element)
     */
    //@{
    /**
    Scalar Adition assignment.
    @returns a reference to itself
    @post all the values of the matrix are summed up by the value x
    */

    template<typename T>
    M_Matrix<T>& operator+=(M_Matrix<T>& itself, T x)
    {
	for (size_t i=0; i<size(itself); i++)
	    itself[i]+=x;
	return itself;
    }


    /**
    Scalar Subtraction assignment.
    @returns a reference to itself
    @post all the values of the matrix are sustracted by the value x
    */
    template<typename T>
    M_Matrix<T>& operator-=(M_Matrix<T>& itself, T x)
    {
	for (size_t i=0; i<size(itself); i++)
	    itself[i]-=x;
	return itself;
    }





    /**
    Scalar Multiplication assignment.
    @returns a reference to itself
    @post all the values of the matrix are multiplied by the value x
    */
    template<typename T>
    M_Matrix<T>& operator*=(M_Matrix<T>& itself, T x)
    {
	for (size_t i=0; i<size(itself); i++)
	    itself[i]*=x;
	return itself;
    }


    /**
    Scalar Division assignment.
    @returns a reference to itself
    @post all the values of the matrix are divided by the value x
    */
    template<typename T>
    M_Matrix<T>& operator/=(M_Matrix<T>& itself, T x)
    {
	for (size_t i=0; i<size(itself); i++)
	    itself[i]/=x;
	return itself;
    }

    //@}
    /** @name Aritmetic Assigment Operations between two Matrices
     */
    //@{






    /*!
    Matrix Addition assignment.
    @returns a reference to itself
    @pre  same number of rows and columns
    @post all the values of the matrix are summed up by the corresponing
	  values of the other matrix\n\n
	  assert(nrows(*this)==nrows(other))&& assert(ncols(*this)==ncols(other))

    */
    template<typename T>
    M_Matrix<T>& operator+=(M_Matrix<T>& itself,
			    const M_Matrix<T>& other)
    {
	assert (size(itself)==size(other));
	assert (nrows(itself)==nrows(other));
	for (size_t i=0; i<size(itself); i++)
	    itself[i]+=other[i];
	return itself;
    }

    /*!
     Matrix Subtraction assignment.
     @returns a reference to itself
     @pre  same number of rows and columns
     @post all the values of the matrix are sustracted by the corresponing
	   values of the other matrix\n\n
	   assert(nrows(*this)==nrows(other))&& assert(ncols(*this)==ncols(other))
     */
     template<typename T>
     M_Matrix<T>& operator-=(M_Matrix<T>& itself,
			     const M_Matrix<T>& other)
     {
         ASSERT_EQ(size(itself),size(other));
         ASSERT_EQ(nrows(itself),nrows(other));
	 for (size_t i=0; i<size(itself); i++)
	     itself[i]-=other[i];
	 return itself;
     }

     /*!
     Matrix Addition assignment with typecast.
     @warning will not compile unless typecast T(S) is defined
     @returns a reference to itself
     @pre  same number of rows and columns
     @post all the values of the matrix are summed up by the corresponing
	   values of the other matrix\n\n
	   assert(nrows(*this)==nrows(other))&& assert(ncols(*this)==ncols(other))

     */
     template<typename T,typename S>
     M_Matrix<T>& operator+=(M_Matrix<T>& itself,
			     const M_Matrix<S>& other)
     {
       ASSERT_EQ(size(itself),size(other));
       ASSERT_EQ(nrows(itself),nrows(other));
         for (size_t i=0; i<size(itself); i++)
	     itself[i]+=T(other[i]);
	 return itself;
     }

     /*!
      Matrix Subtraction assignment with typecast.
     @warning will not compile unless typecast T(S) is defined.
      @returns a reference to itself
      @pre  same number of rows and columns
      @post all the values of the matrix are sustracted by the corresponing
	    values of the other matrix\n\n
	    assert(nrows(*this)==nrows(other))&& assert(ncols(*this)==ncols(other))
      */
      template<typename T,typename S>
      M_Matrix<T>& operator-=(M_Matrix<T>& itself,
			      const M_Matrix<S>& other)
      {
        ASSERT_EQ(size(itself),size(other));
        ASSERT_EQ(nrows(itself),nrows(other));
          for (size_t i=0; i<size(itself); i++)
	      itself[i]-=T(other[i]);
	  return itself;
      }




    //@}


    /**
@name Template Instantations of Assigment Aritmetic Operations between a
Matrix and a scalar
 */
    //@{
    template
     M_Matrix <double>& operator+=(M_Matrix <double>& itself,  double x);

     template
     M_Matrix <double>& operator-=(M_Matrix <double>& itself,  double x);

     template
     M_Matrix <double>& operator*=(M_Matrix <double>& itself,  double x);

     template
     M_Matrix <double>& operator/=(M_Matrix <double>& itself,  double x);

     template
      M_Matrix <std::size_t>& operator+=(M_Matrix <std::size_t>& itself,  std::size_t x);

      template
      M_Matrix <std::size_t>& operator-=(M_Matrix <std::size_t>& itself,  std::size_t x);

      template
      M_Matrix <std::size_t>& operator*=(M_Matrix <std::size_t>& itself,  std::size_t x);

      template
      M_Matrix <std::size_t>& operator/=(M_Matrix <std::size_t>& itself,  std::size_t x);


     //@}
    /**
@name Template Instantations of Assigment Aritmetic Operations between two
Matrices
 */
    //@{
     template
     M_Matrix <double>& operator-=(M_Matrix <double>& itself,
				   const M_Matrix <double>& other);

     template
     M_Matrix <double>& operator+=(M_Matrix <double>& itself,
				   const M_Matrix <double>& other);

     template
     M_Matrix <std::size_t>& operator-=(M_Matrix <std::size_t>& itself,
				   const M_Matrix <std::size_t>& other);

     template
     M_Matrix <std::size_t>& operator+=(M_Matrix <std::size_t>& itself,
				   const M_Matrix <std::size_t>& other);

     //@}
    /**
@name Template Instantations of Assigment Aritmetic Operations between two
Matrices with typecast size_t->double
 */
    //@{
     /**
       typecast from std::size_t to double
       */
     template
     M_Matrix <double>& operator-=(M_Matrix <double>& itself,
				   const M_Matrix <std::size_t>& other);

     template
     M_Matrix <double>& operator+=(M_Matrix <double>& itself,
				   const M_Matrix <std::size_t>& other);



     //@}

 }


