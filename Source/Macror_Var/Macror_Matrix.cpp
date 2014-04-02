#include "Tests/AssertPlain.h"

#include "Macror_Var/Macror_Matrix.h"

namespace Macror_Var
{
  /** @name Default and Copy Constructor, Assignment and Destructor
     */
  //@{


  /*!
    @brief Default constructor
    @post zero columns, zero rows and NULL pointer (no space assigned).
    */
  template<typename T>
  Matrix<T>::Matrix():
    _nrows(std::size_t(0)),
    _ncols(std::size_t(0)),
    _data(0) {}






  /**
    Regular Copy Constructor.
    It creates an independent object whose structure and values are equal
    to the sample object.

    @param sample matrix whose structure and values are copied

    @post  the created object owns its resources, it can alter its values without
           affecting the sample object. Subsequent operations on the
           original object do not affect the duplicate either. That is,
           this!=&other.\n\n

    @post  the creted object is equal to the sample\n
           that is the ::operator==() aplied on *this and sample returns true\n\n

    @see  operator=()(const Matrix<T>&)
    */
  template<typename T>
  inline
  Matrix<T>::Matrix(const Matrix<T>& sample)
    : _nrows(sample._nrows),
      _ncols(sample._ncols),
      //   _data(_ncells>0?new T[size(x)]:0)
      _data(sample._data)
  {
    /*  for (std::size_t i = 0; i < size(sample); ++i)
      (*this)[i] = sample[i];
 */
  }








  /**
     Regular Asignment operator
     @post \p (*this)[i]=sample[i] for all \p 0<=i<size(*this)
     @post memory is reallocated to fit
            the number of rows and columns of the sample
     @return a reference to itself
    */
  template<typename T>
  Matrix<T>& Matrix<T>::operator=(const Matrix<T>& x)
  {
    if (this != &x)
      {
        if (size() == x.size())
          // the same size, no need to reallocate memory
          {
            // copy the value of the number of rows and columns and all the data
            _nrows=nrows();
            _ncols=ncols();
            for (std::size_t i = 0; i < size(); ++i)
              _data[i] = x._data[i];
          }
        else
          // we need to do a memory reallocation
          {
            // this technique is recommended for excecptions managment
            Matrix<T> tmp(x);
            swap(*this, tmp);
          }
      };
    return *this;
  }






  /**
     Destructor, it deallocate the internal pointer.
     @post memory deallocated
    */
  template<typename T>
  Matrix<T>::~Matrix()
  {
    //  if (_data>0)
    //	delete [] _data;
  }





  //@}





  /** @name Other Constructors and Assigments
     */
  //@{







  /**
     Constructor of defined size, allocates memory, values not initialized.
     @post specified memory is allocated
     @warning values are not initialized
     @see zeros() for initializing to \p T(0)
     @see ones() for initializing to \p T(1)
     @see operator=(T N) for initializing to the arbitrary values N
     */
  template<typename T>
  Matrix<T>::Matrix(std::size_t nrows_,
                        std::size_t ncols_)
    : _nrows(nrows_),
      _ncols(ncols_),
      //_data((_ncells>0)?new T[_ncells]:NULL)
      _data(nrows_*ncols_,0)
  {}





  /**
     Constructor with initialized values
     @post (*this)[i]==data[i] for  0<=i< min(size(*this),data.size())
     @post pad remaining values with zeros
    */
  template<typename T>
  Matrix<T>::Matrix(std::size_t nrows_,
                        std::size_t ncols_,
                        std::vector<T> data):
    _nrows(nrows_),
    _ncols(ncols_),
    //   _data(new T[_ncells])
    _data(data)
  {
    ASSERT_EQ(_nrows*_ncols,data.size());
  }





  /**
    Constructor from a string using the istream shift operator.
    @pre the string has to be formatted in the same way as the I/O operators
    @see operator>>(std::istream&,Matrix&)
    @returns if the format of the srting is valid, the translated matrix
    @returns if is invalid, it returns an empty matrix, no exception
    is raised
    */
  /*template<typename T>
  Matrix<T>::Matrix(const std::string& s):
    _nrows(0),
    _ncols(0),
    _data(0)
  {
    Matrix<T> temp;
    if (Markov_IO::ToValue<Matrix<T> >(s,temp))
      *this=temp;
  }

*/










  /**
     Asigns a given value to all the elements
     @post \p (*this)[i]=X for all \p 0<=i<size(*this)
     @return a reference to itself
    */
  template<typename T>
  Matrix<T>& Matrix<T>::operator=(T X)
  {
    for (std::size_t i=0; i<size(); ++i) _data[i]=X;
    return *this;
  }


  //@}


  /** @name Member Inspectors and Modifiers of the data in the matrix
     */
  //@{







  /**
    Direct access to the value of the \p i row and the \p j column.
    @pre \p i<nrows(*this)
    @pre \p j<ncols(*this)
    @warning run-time error is likely if i*ncols()+j>=size(*this)
    @post \p (*this)(i,j)==(*this)[i*ncols()+j]
    */

  template<typename T>
  T&  Matrix<T>::operator() (std::size_t i,std::size_t j)
  {
    if (_nrows<=i)
       ASSERT_LESS(i,_nrows);//number of rows
    if (_ncols<=j)
    ASSERT_LESS(j,_ncols); //number of columns
     return _data[i*_ncols+j];
  }





  /**
    Constant access to the value of the \p i row and the \p j column.
    @pre \p i<nrows(*this)
    @pre \p j<ncols(*this)
    @warning run-time error is likely if i*ncols()+j>=size(*this)
    @post \p (*this)(i,j)==(*this)[i*ncols()+j]
    */
  template<typename T>
  const  T&  Matrix<T>::operator() (std::size_t i,std::size_t j) const
  {
    ASSERT_LESS(i,_nrows);//number of rows
    ASSERT_LESS(j,_ncols); //number of columns
    return _data[i*_ncols+j];
  }


  //@}






  /** @name template class Matrix<T> instantiations
     */
  //@{

  /** Instantation to double
      */
  template class Matrix<double>;


  /** Instantation to std::size_t
      */
  template class Matrix<std::size_t>;
  //@}

}
