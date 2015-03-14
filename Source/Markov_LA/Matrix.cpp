/*!
 * @file Matrix.cpp Implementation of Matrix class, friend functions and
                     Relational Operators

 @see Matrix.h

 */
#include "Markov_LA/auxiliarRelational.h"
#include "Markov_LA/ToleranceComparison.h"
#include "Markov_LA/matrixMaxMin.h"
#include "Markov_IO/auxiliarIO.h"
#include "Tests/AssertPlain.h"


namespace Markov_LA
{
  /** @name Default and Copy Constructor, Assignment and Destructor
     */
  //@{


  /*!
    @brief Default constructor
    @post zero columns, zero rows and NULL pointer (no space assigned).
    */
  template<typename T>
  M_Matrix<T>::M_Matrix():
    _nrows(std::size_t(0)),
    _ncols(std::size_t(0)),
    _ncells(std::size_t(0)),
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

    @see  operator=()(const M_Matrix<T>&)
    */
  template<typename T>
  inline
  M_Matrix<T>::M_Matrix(const M_Matrix<T>& sample)
    : _nrows(sample._nrows),
      _ncols(sample._ncols),
      _ncells(sample._ncells),
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
  M_Matrix<T>& M_Matrix<T>::operator=(const M_Matrix<T>& x)
  {
    if (this != &x)
      {
        if ((size(*this) == size(x)))
          // the same size, no need to reallocate memory
          {
            // copy the value of the number of rows and columns and all the data
            _nrows=nrows(x);
            _ncols=ncols(x);
            for (std::size_t i = 0;
                 i < size(*this);
                 ++i)
              (*this)[i] = x[i];
          }
        else
          // we need to do a memory reallocation
          {
            // this technique is recommended for excecptions managment
            M_Matrix<T> tmp(x);
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
  M_Matrix<T>::~M_Matrix()
  {
    //  if (_data>0)
    //	delete [] _data;
  }





  //@}





  /** @name Other Constructors and Assigments
     */
  //@{

  /*!
    Copy constructor with type cast
    @param anOtherKind matrix that is copied
    @post \p *this==x
    */
  template<typename T>
  template<typename T2>
  M_Matrix<T>::M_Matrix(const M_Matrix<T2>& anOtherKind)
    : _nrows(nrows(anOtherKind)),
      _ncols(ncols(anOtherKind)),
      _ncells(size(anOtherKind)),
      //_data(_ncells>0?new T[size(x)]:NULL)
      _data(_ncells)
  {
    for (std::size_t i = 0; i < size(anOtherKind); ++i)
      (*this)[i] = T(anOtherKind[i]);
  }





  /**
     Constructor of defined size, allocates memory, values not initialized.
     @post specified memory is allocated
     @warning values are not initialized
     @see zeros() for initializing to \p T(0)
     @see ones() for initializing to \p T(1)
     @see operator=(T N) for initializing to the arbitrary values N
     */
  template<typename T>
  M_Matrix<T>::M_Matrix(std::size_t nrows_,
                        std::size_t ncols_)
    : _nrows(nrows_),
      _ncols(ncols_),
      _ncells(nrows_*ncols_),
      //_data((_ncells>0)?new T[_ncells]:NULL)
      _data(_ncells)
  {}





  /**
     Constructor with initialized values
     @post (*this)[i]==data[i] for  0<=i< min(size(*this),data.size())
     @post pad remaining values with zeros
    */
  template<typename T>
  M_Matrix<T>::M_Matrix(std::size_t nrows_,
                        std::size_t ncols_,
                        std::vector<T> data):
    _nrows(nrows_),
    _ncols(ncols_),
    _ncells(nrows_*ncols_),
    //   _data(new T[_ncells])
    _data(_ncells)
  {
    ASSERT_EQ(nrows_*ncols_,data.size());

    for (size_t i=0; i<_ncells; ++i)
      _data[i]=data[i];
  }





  /**
    Constructor from a string using the istream shift operator.
    @pre the string has to be formatted in the same way as the I/O operators
    @see operator>>(std::istream&,M_Matrix&)
    @returns if the format of the srting is valid, the translated matrix
    @returns if is invalid, it returns an empty matrix, no exception
    is raised
    */
  template<typename T>
  M_Matrix<T>::M_Matrix(const std::string& s):
    _nrows(0),
    _ncols(0),
    _ncells(0),
    _data(0)
  {
    M_Matrix<T> temp;
    if (Markov_IO::ToValue<M_Matrix<T> >(s,temp))
      *this=temp;
  }






  /**
     Asignment operator to a Matrix of another type S
     @tparam S typename of the elements of the sample matrix
     @pre \p cast T(S) is a valid expression
     @post \p (*this)[i]==T(x[i]) for all \p 0<=i<size(sample)
     @post \p nrows(*this)==nrows(sample) ncols(*this)==nrows(sample)
     @post for some T and S, S((*this)[i])==sample[i] is also true
     @return a reference to itself
    */
  template<typename T>
  template<typename S>
  M_Matrix<T>& M_Matrix<T>::operator= (const M_Matrix<S>& x)
  {
    M_Matrix<T> tmp(x);
    swap(*this, tmp);
    return *this;
  }
  /**
      Instantiation for std::size_t to doubles
    */
  template
  M_Matrix<double>&
  M_Matrix<double>::operator=(const M_Matrix<std::size_t>& x);







  /**
     Asigns a given value to all the elements
     @post \p (*this)[i]=X for all \p 0<=i<size(*this)
     @return a reference to itself
    */
  template<typename T>
  M_Matrix<T>& M_Matrix<T>::operator=(T X)
  {
    for (std::size_t i=0; i<_ncells; ++i) _data[i]=X;
    return *this;
  }


  //@}


  /** @name Member Inspectors and Modifiers of the data in the matrix
     */
  //@{


  /**
    Direct Access to the value of the \a nth element.
    @param n accessed index
    @pre \p n<size(*this)
    @warning run-time error is likely if n>=size(*this)
    \returns a reference to \p (*this->(i,j)) where \p i*ncols()+j==n
    @see operator()(std::size_t,std::size_t) for access using row and
                   colums indexes
    @see operator()[std::size_t]const for constant access
    */
  template<typename T>
  T& M_Matrix<T>::operator[](std::size_t n)
  {
    ASSERT_LESS(n, size(*this));
    return _data[n];
  }





  /**
    Constant Access to the value of the \a nth element.
    @param n accessed index
    @pre \p n<size(*this)
    @warning run-time error is likely if n>=size(*this)
    \returns a constant reference to \p (*this)->(i,j) where \p i* ncols()+j==n
    @see operator()(std::size_t,std::size_t) for access using row and
                   colums indexes
    @see operator()[std::size_t] for changing the value
    */

  template<typename T>
  const T& M_Matrix<T>::operator[](std::size_t n) const
  {
    if (n>=size(*this))
    ASSERT_LESS(n, size(*this));
    return _data[n];
  }





  /**
    Direct access to the value of the \p i row and the \p j column.
    @pre \p i<nrows(*this)
    @pre \p j<ncols(*this)
    @warning run-time error is likely if i*ncols()+j>=size(*this)
    @post \p (*this)(i,j)==(*this)[i*ncols()+j]
    */

  template<typename T>
  T&  M_Matrix<T>::operator() (std::size_t i,std::size_t j)
  {
    if (_nrows<=i)
       ASSERT_LESS(i,_nrows);//number of rows
    if (_ncols<=j)
    ASSERT_LESS(j,_ncols); //number of columns
     return (*this)[i*_ncols+j];
  }





  /**
    Constant access to the value of the \p i row and the \p j column.
    @pre \p i<nrows(*this)
    @pre \p j<ncols(*this)
    @warning run-time error is likely if i*ncols()+j>=size(*this)
    @post \p (*this)(i,j)==(*this)[i*ncols()+j]
    */
  template<typename T>
  const  T&  M_Matrix<T>::operator() (std::size_t i,std::size_t j) const
  {
    ASSERT_LESS(i,_nrows);//number of rows
    ASSERT_LESS(j,_ncols); //number of columns
    return (*this)[i*_ncols+j];
  }


  //@}



  /** @name  Accesing all the values of a Row or Column at once
     */
  //@{

  /**
    Replacement of the ith Row.
    @param iRow the extracted row (0 is the first as always in C)
    @param newValues contains the numbers used to relace iRow
    @param dummy an ignored variable to differentiate from column
    extraction
    @pre iRow is smaller than nrows(*this)
    @pre size(newValues)==ncols(*this)
    @returns *this
    @post if the preconditions are met, the ith row is replaced by
    newValues
    @post newValues is treated as a vector, although is a Matrix. Its
    internal structure (i.e., ncols and nrows) is ignored.
    @post assert the precoditions
    */

  template<typename T>
  M_Matrix<T>&  M_Matrix<T>::operator() (std::size_t iRow,
                                         std::string /*dummy*/,
                                         const M_Matrix<T>& newValues)
  {
    ASSERT_LESS(iRow,nrows(*this));//number of rows
    ASSERT_EQ(size(newValues),ncols(*this)); //number of columns
    for (std::size_t j=0; j<std::min(ncols(*this),size(newValues)); j++)
      this->operator()(iRow,j)=newValues[j];
    return *this;
  }





  /**
    Replacement of the jth Column.
    @param newValues contains the numbers used to relace jth Column
    @pre newValues is treated as a vector, although is a Matrix. Its
    internal structure (i.e., ncols and nrows) is ignored.
    @param jColumn the replaced column (0 is the first as always in C)
    @param dummy an ignored variable to differentiate from column
    extraction
    @pre jColumn is smaller than ncols(*this)
    @pre size(newValues)==nrows(*this)
    \returns *this
    @post if the preconditions are met, the jth Column is replaced by
    newValues
    @post assert the precoditions
    */


  template<typename T>
  M_Matrix<T>&  M_Matrix<T>::operator() (const std::string /*dummy*/,
                                         std::size_t jColumn,
                                         const M_Matrix<T>& newValues)
  {
    ASSERT_LESS(jColumn,ncols(*this));//number of rows
    ASSERT_EQ(size(newValues),nrows(*this)); //number of columns

    for (std::size_t i=0; i<std::min(nrows(*this),size(newValues)); i++)
      this->operator()(i,jColumn)=newValues[i];
    //  assert(ndim>1);
    //  assert(i<n[0]);//number of rows
    //  assert(j<n[1]); //number of columns
    return *this;
  }





  /**
    Copy of the ith Row
    @pre iRow is smaller than nrows(*this)
    @param iRow the extracted row (0 is the first as always in C)
    @param dummy an ignored variable to differentiate from column
    extraction
    \returns a 1-row ncols Matrix with the values of the ith row
    */

  template<typename T>
  M_Matrix<T>  M_Matrix<T>::operator() (std::size_t iRow,
                                        const std::string /*dummy*/
                                        ) const
  {
    ASSERT_LESS(iRow,nrows(*this));
    M_Matrix<T> out(1,ncols(*this));
    for (std::size_t j=0; j<ncols(*this); j++)
      out[j]=this->operator()(iRow,j);
    return out;
  }






  /**
    Copy of the jth Column
    @pre jColumn is smaller than ncols(*this)
    @param jColumn the extracted column (0 is the first as always in C)
    @param dummy is an ignored const string (like "") to differentiate
    from row extraction
    \returns a nrows 1-column Matrix with the values of the jth column
    */

  template<typename T>
  M_Matrix<T>  M_Matrix<T>::operator() (std::string /*dummy*/,
                                        std::size_t jColumn
                                        ) const
  {
    ASSERT_LESS(jColumn,ncols(*this));
    M_Matrix<T> out(nrows(*this),1);
    for (std::size_t i=0; i<nrows(*this); i++)
      out[i]=(*this)(i,jColumn);
    return out;
  }

  //@}


  /** @name template class M_Matrix<T> instantiations
     */
  //@{

  /** Instantation to double
      */
  template class M_Matrix<double>;


  /** Instantation to std::size_t
      */
  template class M_Matrix<std::size_t>;
  //@}


  /** @name template class M_Matrix<T> member instantiations
     */
  //@{

  /** Instantation of typecast std::size_t to double
      */
  template  M_Matrix<double>::M_Matrix(const M_Matrix<std::size_t>&);



  /** Instantation of typecast std::size_t to double
      */
  template  M_Matrix<std::size_t>::M_Matrix(const M_Matrix<double>&);

  //@}


  /** @name Functions friend of M_Matrix<T> inspecting its size
     */
  //@{


  /**
    Get the Number of elements (cells) of the matrix
    @post size(x)=nrows(x)*ncols(x)
    */
  template<typename S>
  size_t size(const M_Matrix<S>& x)
  {
    return x._ncells;
  }




  /**
    Get the Number of rows of the matrix

    */
  template <typename T>
  std::size_t nrows(const M_Matrix<T>& x)
  {return x._nrows;}



  /**
    Get the Number of columns of the matrix
    */
  template <typename T>
  std::size_t ncols(const M_Matrix<T>& x)
  {
    return x._ncols;
  }

  //@}

  //@}


  /** @name Template Instantiations of size Inspectors
     */
  //@{

  /**
     Instantiation for double
    */
  template size_t size(const M_Matrix<double>& x);
  /**
     Instantiation for std::size_t
    */
  template size_t size(const M_Matrix<std::size_t>& x);


  /**
     Instantiation for double
    */
  template
  size_t nrows(const M_Matrix<double>& x);
  /**
     Instantiation for std::size_t
    */
  template
  size_t nrows(const M_Matrix<std::size_t>& x);



  /**
     Instantiation for double
    */
  template
  size_t ncols(const M_Matrix<double>& x);
  /**
     Instantiation for std::size_t
    */
  template
  size_t ncols(const M_Matrix<std::size_t>& x);


  //@}


  /** @name  Friend Swap Operator
     */
  //@{
  /**
 Swap Operator
 @pre both Matrices are of the same type
 @post the Matrices are interchanged
 @remarks it swaps pointers, so it is fast
*/

  template<typename S>
  void swap(M_Matrix<S>& x, M_Matrix<S>& y)
  {
    std::swap(x._nrows, y._nrows);
    std::swap(x._ncols, y._ncols);
    std::swap(x._ncells, y._ncells);
    std::swap(x._data, y._data);
  }

  //@}




  /** @name  Template Instantiation of Friend Swap Operator
     */
  //@{
  /**
     Instantiation for double
    */
  template void swap(M_Matrix<double>& x,
  M_Matrix<double>& y);

  /**
     Instantiation for std::size_t
    */
  template void swap(M_Matrix<std::size_t>& x,
  M_Matrix<std::size_t>& y);

  //@}

  /** @name  Relational operators on M_Matrix<T>
     */
  //@{

  /**
    Matrix Equality Operator
    @returns true only if all the elements are equal
    @remarks it uses the isEqual() operator
    */
  template<typename T>
  bool operator==(const M_Matrix<T>& x,
                  const M_Matrix<T>& y)
  {
    if (std::numeric_limits<T>::is_exact)
      {
        if (size(x) != size(y)) return false;
        for (std::size_t i = 0; i < size(x); ++i)
          if (x[i]!= y[i]) return false;
        return true;
      }
    else
      {
        if (size(x) != size(y)) return false;
        ToleranceComparison<T> tol(
              std::sqrt(std::numeric_limits<T>::epsilon()),
              std::sqrt(std::numeric_limits<T>::epsilon())
              );
        for (std::size_t i = 0; i < size(x); ++i)
          if (!tol.isEqual(x[i] , y[i]))
            return false;
        return true;
      }
  }

  /** UnEqual Operator based on the Equality Operator.
    @see operator==(const M_Matrix<T>&,const M_Matrix<T>&)
    */

  template<typename T>
  bool operator!=(const M_Matrix<T>& x, const M_Matrix<T>& y)
  {
    return !(x == y);
  }


  /** Minor Operator based on a Lexicographic Comparison.
     It uses as keys each one of the elements of the Matrix,
     starting from (*this)[0]
     @returns true if x<y
     @remarks uses the isLess() operator
    */
  template<typename T>
  bool operator<(const M_Matrix<T>& x, const M_Matrix<T>& y)
  {
    ToleranceComparison<T> tol(
          std::numeric_limits<T>::epsilon(),
          std::numeric_limits<T>::epsilon()*norm_inf(x)
          );
    for (size_t i(0); ; ++i)
      {
        if (i >= size(y)) return false;
        if (i >= size(x)) return true;
        if (tol.isLess(y[i],x[i])) return false;
        if (tol.isLess(x[i], y[i])) return true;
      }
  }

  /** Major Operator based on the Minor Operator.
    @see operator<(const M_Matrix<T>&,const M_Matrix<T>&)
    */
  template<typename T>
  bool operator>(const M_Matrix<T>& x, const M_Matrix<T>& y)
  {
    return y < x;
  }

  /** MinorEqual Operator based on the Minor Operator.
    @see operator<(const M_Matrix<T>&,const M_Matrix<T>&)
    */
  template<typename T>
  bool operator<=(const M_Matrix<T>& x, const M_Matrix<T>& y)
  {
    return !(y < x);
  }

  /** MajorEqual Operator based on the Minor Operator.
    @see operator<(const M_Matrix<T>&,const M_Matrix<T>&)
    */

  template<typename T>
  bool operator>=(const M_Matrix<T>& x, const M_Matrix<T>& y)
  {
    return !(x < y);
  }

  //@}



  /**  Double Operator. Converts a one by one matrix to a double.
      Assert that its a one by one matrix.
      @pre  ncols()==nrows()==size()==1
      @return matrix(0,0)
      @return assert that is a one by one matrix
    */
  template<typename T>
  double ToDouble(const M_Matrix<T>& matrix)
  {
    ASSERT_EQ(size(matrix),1);
    return matrix[0];
  }

  template double ToDouble(const M_Matrix<double>& matrix);





  /**
    @name Template Instantiation of Relational Operators on Matrix
     */
  //@{


  /** Instantation to double
    */
  template bool operator ==(const M_Matrix<double>& x,
  const M_Matrix<double>& y);



  /** Instantation to std::size_t
    */
  template bool operator ==(const M_Matrix<std::size_t>& x,
  const M_Matrix<std::size_t>& y);


  /** Instantation to double
    */
  template  bool operator < (const M_Matrix<double>& x,const M_Matrix<double>& y);

                            /** Instantation to std::size_           */


                            template
                            bool operator < (const M_Matrix<std::size_t>& x,
                                            const M_Matrix<std::size_t>& y);


                                            /** Instantation to double
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  */
                                            template
                                            bool operator>(const M_Matrix<double>& x,
                            const M_Matrix<double>& y);


                            /** Instantation to std::size_t
                                                                                                                                                       */
                            template
                           bool operator>(const M_Matrix<std::size_t>& x,
  const M_Matrix<std::size_t>& y);


  /** Instantation to double
    */
  template
  bool operator<=(const M_Matrix<double>& x,
  const M_Matrix<double>& y);


  /** Instantation to std::size_t
    */
  template
  bool operator<=(const M_Matrix<std::size_t>& x,
  const M_Matrix<std::size_t>& y);


  /** Instantation to double
    */
  template
  bool operator>=(const M_Matrix<double>& x,
  const M_Matrix<double>& y);


  /** Instantation to std::size_t
    */
  template
  bool operator>=(const M_Matrix<std::size_t>& x,
  const M_Matrix<std::size_t>& y);


  /** Instantation to double
    */
  template
  bool operator!=(const M_Matrix<double>& x,
  const M_Matrix<double>& y);


  /** Instantation to std::size_t
    */
  template
  bool operator!=(const M_Matrix<std::size_t>& x,
  const M_Matrix<std::size_t>& y);


  //@}
} //namespace Markov_LA


