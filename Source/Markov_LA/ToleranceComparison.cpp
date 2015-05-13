/*!
 * @file ToleranceComparison.cpp @brief Implementation of ToleranceComparison methods

 */

#include "Markov_LA/ToleranceComparison.h"

namespace Markov_LA{

/**
  Default Constructor
  @post both AbsoluteTolerance() and RelativeTolerance() are set equal to std::numeric_limits<T>::epsilon()
  @warning Will not compile for classes if std::numeric_limits is not defined
for T
 */
 template<class T>
ToleranceComparison<T>::ToleranceComparison():
	absTol_(std::numeric_limits<T>::epsilon()*10000),
	relTol_(absTol_) {}


/**
 Copy Constructor
 */
template<class T>
ToleranceComparison<T>::ToleranceComparison(const ToleranceComparison& c):
	absTol_(c.absTol_),
	relTol_(c.relTol_){}

/**
  Assigment Operator
 */
template<class T>
ToleranceComparison<T>&
	ToleranceComparison<T>::operator=(const ToleranceComparison& other)
					 {
    absTol_=other.absTol_;
    relTol_=other.relTol_;
    return *this;
}

/**
  Swap Operator on class ToleranceComparison<T>
  */
template<typename S>
void swap(const ToleranceComparison<S>& x,
	  const ToleranceComparison<S>& y)
{
    using std::swap;
    swap(x.absTol_,y.absTol_);
    swap(x.relTol_,y.relTol_);
}


/**
  Builds ToleranceConstructor Functor with custom values for AbsoluteTolerance()
 and RelativeTolerance()
*/

template<class T>
ToleranceComparison<T>::ToleranceComparison(T absoluteTolerance,T relativeTolerance):
	absTol_(absoluteTolerance),
	relTol_(relativeTolerance){}





/**
  Equality Operator
  @returns true if abs(x-y)<=tolerance,   where the \n
@b tolerance=max(AsoluteTolerance(),RelativeToleranace()*max(abs(y),abs(x))

 */

template<class T>
bool ToleranceComparison<T>::isEqual(T x,
				     T y
				     )const
{
    if (x==y) return true;
    else if (x>y)
    {
	if (x>T(0))
	{
	    return (x-y)<=std::max(absTol_,relTol_*x);
	}
	else
	{
	    return (x-y)<=std::max(absTol_,relTol_*(-y));
	}
    }
    else
    {
	if (y>T(0))
	{
	    return (y-x)<=std::max(absTol_,relTol_*y);
	}
	else
	{
	    return (y-x)<=std::max(absTol_,relTol_*(-x));
	}
    }
}

/**
  Less than Operator
  @returns true if x<min(y-tol) where tol=max(absTol,relTol*max(|x|,|y|))
 */

template<class T>
bool ToleranceComparison<T>::isLess(T x, T y)const
{
    T maxdif=std::max(absTol_, relTol_ *
		    std::max(x>0?x:-x, y>0?y:-y));
    //double dif=x-y;
    return (x<y-maxdif);
}

/**
  Greater than Operator
  Based on isLess()
  */
template<class T>
bool ToleranceComparison<T>::isGreater(T x,T y)const
{
    return isLess(y,x);
}

/**
  Accesor to the value of the absolute tolerance, that is the tolerance for the
comparison between values close to zero
@returns a reference to the internal value of the absolute tolerance
  */
template<class T>
T& ToleranceComparison<T>::AbsoluteTolerance()
{
    return absTol_;
}

/**
  Accesor to the value of the relative tolerance, that is the tolerance for the
comparison between values as a fraction of the magnitude of the compared values.
@returns a reference to the internal value of the relative tolerance
*/
template<class T>
T& ToleranceComparison<T>:: RelativeTolerance()
{
    return relTol_;
}


/**
  Returns the value of the absolute tolerance
@returns a constant reference to the internal value of the absolute tolerance
 */
template<class T>
const T& ToleranceComparison<T>::AbsoluteTolerance()const
{
    return absTol_;
}

/**
  Returns the value of the relative tolerance
@returns a constant reference to the internal value of the relative tolerance
 */
template<class T>
const T& ToleranceComparison<T>::RelativeTolerance()const
{
    return relTol_;
}


template class ToleranceComparison<double>;
template class ToleranceComparison<int>;
template class ToleranceComparison<std::size_t>;


}
