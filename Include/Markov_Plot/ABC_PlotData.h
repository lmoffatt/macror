#ifndef ABC_PLOTDATA_H
#define ABC_PLOTDATA_H

#include <string>
#include "Markov_LA/Matrix.h"

namespace Markov_Plot
{

class ABC_PlotData
{
public:
    virtual std::string type()=0;

    virtual const Markov_LA::M_Matrix<double>& x()const=0;
    virtual const Markov_LA::M_Matrix<double>& y()const=0;




};

}

#endif // ABC_PLOTDATA_H
