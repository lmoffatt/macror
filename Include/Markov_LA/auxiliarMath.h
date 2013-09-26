/*!
 * @file auxiliarMath.h @brief Numerics Infinity and NaN functions, no Matrix here

 */

#ifndef AUXILIARMATH_H
#define AUXILIARMATH_H

#include <limits>
#include <vector>

#include "Markov_LA/Matrix.h"

#define PI 3.1415926535897932384626433832795


namespace Markov_LA
{


 double infinity();

double NaN();

bool isNaN(double x);

template<typename T>
bool isFinite(T x);

//double exp10(double x);

double erfinv(double P);


double NormalPdf(double x, double mean, double s);
double NormalPdf(double x);


double NormalCdf(double x, double mean, double s);
double NormalCdf(double x);

double NormalCdfInv(double p, double mean, double s);
double NormalCdfInv(double p);

double MultinomialPdf(const M_Matrix<std::size_t>& x,const  M_Matrix<double>& P);

double LogMultinomialPdf(const M_Matrix<std::size_t>& x, const M_Matrix<double>& P);


double ChiSqrCdf(double x, double k);
double ChiSqrPdf(double x, double k);

double GammaFunction(double x);

double LogGammaFunction(double x);


double GammaRegularized(double a, double z, std::size_t n=8);

double LogGammaRegularized(double a, double z, std::size_t n=8);


double floorSafe(double x);
double ceilSafe(double x);


}


#endif // AUXILIARMATH_H
