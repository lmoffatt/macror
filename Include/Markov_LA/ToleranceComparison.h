/*!
 * @file ToleranceComparison.h @brief Interfase of class ToleranceComparison

 */


#ifndef TOLERANCECOMPARISON_H
#define TOLERANCECOMPARISON_H
#include <limits>
#include <cmath>
#include <algorithm>


namespace Markov_LA
{




/*!
  Relational operators with customizable tolerance, recommended for real
floating numbers. The tolerance is taken as the maximum between an absolute
tolerance value and the multiplication of a relative tolerance by the absolute
value of the compared values

  @tparam T typename of the values to be compared (they model a real number,
but also integers can be compared for completitude)

  @invariant Follows the Trichotomy Law: one and only one of {isLess(),
isEqual() and isGreter()} is true for any pair of values

*/



template<class T>
class ToleranceComparison
{
public:
    ToleranceComparison();
    ~ToleranceComparison(){}
    ToleranceComparison(const ToleranceComparison& c);
    ToleranceComparison& operator=(const ToleranceComparison& other);

    template<typename S>
    friend void swap(const ToleranceComparison<S>& x,
		     const ToleranceComparison<S>& y);


    ToleranceComparison(T absoluteTolerance,T relativeTolerance);

    bool isEqual(T x,T y)const;

    bool isLess(T x, T y)const;

    bool isGreater(T x,T y)const;

    T& AbsoluteTolerance();
    T& RelativeTolerance();
    const T& AbsoluteTolerance()const;
    const T& RelativeTolerance()const;

private:
    T absTol_;/**< Absolute Tolerance */
    T relTol_; /**< Relative Tolerance */
};


};
#endif // TOLERANCECOMPARISON_H
