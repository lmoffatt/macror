#ifndef CONTINUEDFRACTION_H
#define CONTINUEDFRACTION_H
#include "Markov_LA/Matrix.h"

namespace Markov_LA
{

class ContinuedFraction
{
public:
    ContinuedFraction(const std::vector<double>& a,
                      const std::vector<double>& b);

    ContinuedFraction(const ContinuedFraction& other);

    ContinuedFraction();

    ContinuedFraction& operator=(const ContinuedFraction& other);

    friend void swap(ContinuedFraction& one, ContinuedFraction& two);

    double operator()()const;

    ~ContinuedFraction();


private:
    std::vector<double> a_;
    std::vector<double> b_;
    mutable double value_;

};
}


#endif // CONTINUEDFRACTION_H
