/*!
 * @file auxiliarRelational.h @brief Generalization of relational operators

Template generalization of relational operators for any Type with epsilon check

 */
#ifndef AUXILIARRELATIONAL_H
#define AUXILIARRELATIONAL_H
#include <limits>
#include <cmath>
#include <vector>
#include "Markov_LA/ToleranceComparison.h"


template<typename T>
bool operator<(const std::vector<T>& x, T f);

template<typename T>
bool operator>(const std::vector<T>& x, T f);

template<typename T>
bool operator>=(const std::vector<T>& x, T f);

template<typename T>
bool operator<=(const std::vector<T>& x, T f);

template<typename T>
bool operator==(const std::vector<T>& x, T f);

template<typename T>
bool operator!=(const std::vector<T>& x, T f);

bool all_true(bool* has_it, std::size_t n);

template<class T>
inline bool operator!=(const T& x,const T& y);

template<class T>
inline bool operator>(const T& x,const T& y);

template<class T>
inline bool operator<=(const T& x,const T& y);

template<class T>
inline bool operator>=(const T& x,const T& y);

/**
@name Relational operators between a container and a value
@returns true if all the elements of the container follow the tested relation
@returns false if \b any of the elements fails to follow the tested relation
@warning therefore, these relational operators do not have the same logical
content i.e, that if it is false that V>x does not mean that it is true that
      V<=x
  */

//{@


/**
  Every element of the vector is less than a given value
  @returns true if every element of the vector is less than the value
  @returns false if any element of the vector is greater or equal to the value
*/

template<typename T>
bool operator<(const std::vector<T>& x, T f){
    Markov_LA::ToleranceComparison<T> tol;
    for (size_t i=0;i<x.size(); ++i)
    {
        if (! tol.isLess(x[i], f))
            return false;
    }
    return true;
}

/**
  Every element of the vector is greater than a given value
  @returns true if every element of the vector is greater than the value
  @returns false if any element of the vector is less than or equal to the value
*/

template<typename T>
bool operator>(const std::vector<T>& x, T f)
{
    Markov_LA::ToleranceComparison<T> tol;
    for (size_t i=0;i<x.size(); ++i)
    {
        if (!tol.isGreater(x[i],f)) return false;
    }
    return true;
}

/**
  Every element of the vector is greater than or equal to a given value
  @returns true if every element of the vector is greater than or equal to the value
  @returns false if any element of the vector is less than the value
*/
template<typename T>
bool operator>=(const std::vector<T>& x, T f){
    Markov_LA::ToleranceComparison<T> tol;
    for (size_t i=0;i<x.size(); ++i)
    {
        if (tol.isLess(x[i],f)) return false;
    }
    return true;
}

/**
  Every element of the vector is less than or equal to a given value
  @returns true if every element of the vector is less than or equal to the value
  @returns false if any element of the vector is greater than value
*/
template<typename T>
bool operator<=(const std::vector<T>& x, T f){
    Markov_LA::ToleranceComparison<T> tol;
    for (size_t i=0;i<x.size(); ++i)
    {
        if (tol.isGreater(x[i],f)) return false;
    }
    return true;
}

/**
  Every element of the vector is equal to a given value
  @returns true if every element of the vector is  equal to the value
  @returns false if any element of the vector is greater than or less than the
  value
*/
template<typename T>
bool operator==(const std::vector<T>& x, T f){
    Markov_LA::ToleranceComparison<T> tol;
    for (size_t i=0;i<x.size(); ++i)
    {
        if (!tol.isEqual(x[i],f)) return false;
    }
    return true;
}

/**
  Every element of the vector is not equal to a given value
  @returns true if every element of the vector is greater of less than the value
  @returns false if any element of the vector is equal to the
  value
  example if (v!=0) it is safe to divide by each one of the values of v.
  @warning the thrichotomy law does not apply, since the fact that neither of
the values of a vector are equal to the tested value does not means that all of
them are greater than it or less than it.
*/
template<typename T>
bool operator!=(const std::vector<T>& x, T f){
    Markov_LA::ToleranceComparison<T> tol;
    for (size_t i=0;i<x.size(); ++i)
    {
        if (!tol.isEqual(x[i],f)) return false;
    }
    return true;
}

//@}


/**
  Checks if an array of boolean has all its values true
 @todo replace by a std::vector<bool>
 */
inline bool all_true(bool* has_it, size_t n)
{
    for (size_t i=1; i<n; i++) // cero is class_name
        if (!has_it[i]) return false;
    return true;
}





/**
  @name Derived Relation operators on elements.

  After defining operator<(T x, T y) it is possible to derive the rest of the Relational
 operators applied to the same class.

  */


//{@

template<class T>
inline bool operator!=(const T& x,const T& y)
{
    return !(x==y);
}

template<class T>
inline bool operator>(const T& x,const T& y)
{
    return (y<x);
}

template<class T>
inline bool operator<=(const T& x,const T& y)
{
    return !(y<x);
}

template<class T>
inline bool operator>=(const T& x,const T& y)
{
    return !(x<y);
}

#endif // AUXILIARRELATIONAL_H
