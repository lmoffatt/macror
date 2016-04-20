/*!
 * @file Matrix.h


 */

#ifndef MARKOV_MATRIX_H
#define MARKOV_MATRIX_H


#include <limits> // for std::numeric_limits
#include <cstddef> //  for std::size_t
#include <ostream>
#include <istream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cassert>

#include <iterator>     // std::iterator, std::input_iterator_tag


namespace Markov_LA
{

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
    class M_Matrix
    {
    public:

      class MyConstIterator;
      class MyIterator : public std::iterator<std::input_iterator_tag, T>
      {
        std::size_t i_;
        std::size_t j_;
        M_Matrix<T>& m;
      public:
        friend class MyConstIterator;
        std::size_t iRow()const{return i_;}
        std::size_t jCol()const{return j_;}

        MyIterator(M_Matrix<T>& x) :m(x),i_(0),j_(0) {}
        MyIterator(M_Matrix<T>& x, std::size_t i, std::size_t j) :m(x),i_(i),j_(j) {}

        MyIterator(MyIterator& mit) : m(mit.m),i_(mit.i_),j_(mit.j_) {}
        MyIterator& operator++()
        {
          ++j_;
          if (j_>=ncols(m))
            {
              j_=0;
              ++i_;
            }
          return *this;}
        MyIterator operator++(int)
        {MyIterator tmp(*this); operator++(); return tmp;}
        bool operator==(const MyIterator& rhs)
        {
          if (i_!=rhs.i_)
            return false;
          else if (j_!=rhs.j_)
            return false;
          else return true;
          }
        bool operator!=(const MyIterator& rhs) {return ! (*this==rhs);}
        T& operator*() {return m(i_,j_);}
        const T& operator*() const {return m(i_,j_);}
      };


      class MyConstIterator : public std::iterator<std::input_iterator_tag, T>
      {
        std::size_t i_;
        std::size_t j_;
        const M_Matrix<T>& m;
      public:
        std::size_t iRow()const{return i_;}
        std::size_t jCol()const{return j_;}

        MyConstIterator(const M_Matrix<T>& x) :m(x),i_(0),j_(0) {}
        MyConstIterator(const M_Matrix<T>& x, std::size_t i, std::size_t j) :m(x),i_(i),j_(j) {}

        MyConstIterator(const MyConstIterator& mit) : m(mit.m),i_(mit.i_),j_(mit.j_) {}
        MyConstIterator(const MyIterator& mit) : m(mit.m),i_(mit.i_),j_(mit.j_) {}
        MyConstIterator& operator++()
        {
          ++j_;
          if (j_>=ncols(m))
            {
              j_=0;
              ++i_;
            }
          return *this;}
        MyConstIterator operator++(int)
        {MyConstIterator tmp(*this); operator++(); return tmp;}
        bool operator==(const MyConstIterator& rhs)
        {
          if (i_!=rhs.i_)
            return false;
          else if (j_!=rhs.j_)
            return false;
          else return true;
          }
        bool operator!=(const MyConstIterator& rhs) {return ! (*this==rhs);}
        const T& operator*() const {return m(i_,j_);}
      };



      typedef  MyIterator iterator;
      typedef  MyConstIterator const_iterator;


      iterator begin()
      {
        MyIterator out(*this);
        return out;
      }

      iterator end()
      {
        MyIterator out(*this,0,nrows(*this));
        return out;
      }

      const_iterator begin()const
      {
        MyConstIterator out(*this);
        return out;
      }

      const_iterator end() const
      {
        MyConstIterator out(*this,0,nrows(*this));
        return out;
      }


	M_Matrix();  //default constructor


	M_Matrix (const M_Matrix<T> & sample);

	M_Matrix<T>& operator=(const M_Matrix<T>& x);

	~M_Matrix();

	template < typename T2>
		M_Matrix (const M_Matrix<T2> & anOtherKind);

	M_Matrix(std::size_t nrows_,std::size_t ncols_);

	M_Matrix(std::size_t nrows_,std::size_t ncols_, std::vector<T> data);

	explicit M_Matrix(const std::string& s);

	template <typename S>
		M_Matrix& operator=(const M_Matrix<S>& sample);

	M_Matrix<T>& operator=(T X);

	template<typename S>
	friend void swap(M_Matrix<S>& x, M_Matrix<S>& y);

	template<typename S>
	friend size_t size(const M_Matrix<S>& x);

	template<typename S>
	friend size_t nrows(const M_Matrix<S>& x);

	template<typename S>
	friend size_t ncols(const M_Matrix<S>& x);

	T& operator[](std::size_t n);

	const T& operator[](std::size_t n) const;

	T&  operator() (std::size_t i,std::size_t j);

	const  T&  operator() (std::size_t i,std::size_t j) const;

	M_Matrix<T>&  operator() (std::size_t i,
				  const std::string /*dummy*/,
				  const M_Matrix<T>& newValues);

	M_Matrix<T>&  operator() (const std::string /*dummy*/,
				  std::size_t jColumn,
				  const M_Matrix<T>& newValues);

	M_Matrix<T>  operator() (std::size_t iRow,
				 std::string /*dummy*/) const;


	M_Matrix<T>  operator() (std::string /*dummy*/,
				 std::size_t jColumn) const;

        void clear()
        {
          _nrows=0;
          _ncols=0;
          _ncells=0;
          _data.clear();
        }


    private:
	std::size_t          _nrows;    /**< number of rows */
	std::size_t          _ncols;    /**< number of columns */
	std::size_t          _ncells;   /**< _nows*_ncells  */

	/** internal data
	  @remarks can be a pointer or a vector
	  @remarks now is a vector for debugging purposes
	  */
//	T                      *_data; /**< pointer to the data  */
	std::vector<T>        _data;

    };

    template<typename T>
    double ToDouble(const M_Matrix<T>& matrix);



    template<typename S>
    size_t size(const M_Matrix<S>& x);

    template<typename S>
    size_t nrows(const M_Matrix<S>& x);

    template<typename S>
    size_t ncols(const M_Matrix<S>& x);

    template<typename S>
    size_t size(const M_Matrix<S>& x);

    /*
    Matrix Equality Operator
    */
    template<typename T>
    bool operator==(const M_Matrix<T>& x,
		    const M_Matrix<T>& y);



    /*
     Minor Operator based on a Lexicographic Comparison.
    */
    template<typename T>
    bool operator<(const M_Matrix<T>& x, const M_Matrix<T>& y);


    /** Major Operator based on the Minor Operator.
    */
    template<typename T>
    bool operator>(const M_Matrix<T>& x, const M_Matrix<T>& y);


    /** MinorEqual Operator based on the Minor Operator.
    */
    template<typename T>
    bool operator<=(const M_Matrix<T>& x, const M_Matrix<T>& y);

    /** MajorEqual Operator based on the Minor Operator.
    */
    template<typename T>
    bool operator>=(const M_Matrix<T>& x, const M_Matrix<T>& y);


    /** UnEqual Operator based on the Equality Operator.
    */

    template<typename T>
    bool operator!=(const M_Matrix<T>& x, const M_Matrix<T>& y);



}//namespace Markov_LA


#endif // MARKOV_MATRIX_H
