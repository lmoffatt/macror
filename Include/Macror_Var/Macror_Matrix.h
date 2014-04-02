#ifndef MACROR_MATRIX_H
#define MACROR_MATRIX_H
#include <string>
#include <vector>

namespace Macror_Var {


  /*!
  *  @brief A Matrix of elements of type \p T (usually double or std::size_t).
  *
  *  It allocates and deallocates memory with object construction and destruction.
  *  It is a Regular type (has Equallity operator, total ordering and copying and
      assigment)

  *
     @invariant Input and output warrantied within to give a valid element
                for indexes smaller than its number of elempements \n
                \p \b operator[]( std::size_t i ) succeeds returing a \b \p T&
                for all \p \b i in \p \b 0<=i< \p \b size()  \n\n

     @invariant Input and output warrantied to give a valid element when the row
                index i and the column idexes j are smaller than the number of
                rows and indexes of the matrix \n
                \p \b operator()( std::size_t i, std::size_t j ) succeeds returing
                a \p \b T& for all \p \b i in  \p \b 0<=i< \p \b nrows() and all
                \p \b j in  \p \b 0<=j< \p \b ncols()\n\n

     @invariant The number of elements is equal to the number of rows multiplied
                by the number of columns\n
                \p\b size() == \p \b nrows() * \p \b ncols() \n\n

     @invariant Equationally complete \n
                T b(a); assert(a==b);and T a; a=b; assert(a==b);

                Strictly ordered\n
                Equality operator a global non-friend function
                Copy Constructor and Assigment on the same object are

     @warning   Does not rise exceptions, undefined behavior \p \b of operator[]()
                and operator()() for indexes out of range  \n\n

  **/
      template<typename T>
      class Matrix
      {
      public:

          Matrix();  //default constructor

          Matrix (const Matrix<T> & sample);
          Matrix (Matrix<T> && sample);

          Matrix<T>& operator=(const Matrix<T>& x);

          ~Matrix();

          Matrix(std::size_t nrows_,std::size_t ncols_);

          Matrix(std::size_t nrows_,std::size_t ncols_, std::vector<T> data);

          explicit Matrix(const std::string& s);

          template <typename S>
           Matrix& operator=(const Matrix<S>& sample);

          Matrix<T>& operator=(T X);

          template<typename S>
          friend void swap(Matrix<S>& x, Matrix<S>& y);

          size_t size()const
          {
            return nrows()*ncols();
          }

          size_t nrows()const
          {
            return _nrows;
          }

          size_t ncols()const
          {
            return _ncols;
          }

          T&  operator() (std::size_t i,std::size_t j);

          const  T&  operator() (std::size_t i,std::size_t j) const;

          friend void swap(Matrix<T> one,Matrix<T>two)
          {
            std::swap(one._ncols,two._ncols);
            std::swap(one._nrows,two._nrows);
            std::swap(one._data,two._data);
          }


      private:
          std::size_t          _nrows;    /**< number of rows */
          std::size_t          _ncols;    /**< number of columns */

          /** internal data
            @remarks can be a pointer or a vector
            @remarks now is a vector for debugging purposes
            */
  //	T                      *_data; /**< pointer to the data  */
          std::vector<T>        _data;

      };


      /*
      Matrix Equality Operator
      */
      template<typename T>
      bool operator==(const Matrix<T>& x,
                      const Matrix<T>& y);



      /*
       Minor Operator based on a Lexicographic Comparison.
      */
      template<typename T>
      bool operator<(const Matrix<T>& x, const Matrix<T>& y);


      /** Major Operator based on the Minor Operator.
      */
      template<typename T>
      bool operator>(const Matrix<T>& x, const Matrix<T>& y);


      /** MinorEqual Operator based on the Minor Operator.
      */
      template<typename T>
      bool operator<=(const Matrix<T>& x, const Matrix<T>& y);

      /** MajorEqual Operator based on the Minor Operator.
      */
      template<typename T>
      bool operator>=(const Matrix<T>& x, const Matrix<T>& y);


      /** UnEqual Operator based on the Equality Operator.
      */

      template<typename T>
      bool operator!=(const Matrix<T>& x, const Matrix<T>& y);

      template<typename T>
      std::istream& operator>> (std::istream& s, Matrix<T>& A);

      template<typename T>
      std::ostream& operator<< (std::ostream& s,const Matrix<T>& A);


  }//namespace Markov_LA

#endif // MACROR_MATRIX_H
