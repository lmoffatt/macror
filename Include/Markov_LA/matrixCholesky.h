#ifndef MATRIXCHOLESKY_H
#define MATRIXCHOLESKY_H
#include "Markov_LA/Matrix.h"

namespace Markov_LA
{
M_Matrix<double> chol(const M_Matrix<double>& x,const std::string& kind="lower");



}



#endif // MATRIXCHOLESKY_H
