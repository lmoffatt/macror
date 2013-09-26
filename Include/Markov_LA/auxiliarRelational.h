/*!
 * @file auxiliarRelational.h @brief Generalization of relational operators

Template generalization of relational operators for any Type with epsilon check

 */
#ifndef AUXILIARRELATIONAL_H
#define AUXILIARRELATIONAL_H
#include <limits>
#include <cmath>
#include <vector>

namespace Markov_LA
{

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

}
#endif // AUXILIARRELATIONAL_H
