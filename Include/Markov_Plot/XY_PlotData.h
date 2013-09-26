#ifndef XY_PLOTDATA_H
#define XY_PLOTDATA_H
#include "Markov_Plot/ABC_PlotData.h"
//#include <QString>

namespace Markov_Plot
{

class XY_PlotData: public ABC_PlotData
{
public:
    virtual std::string type();

    virtual const Markov_LA::M_Matrix<double>& x()const;
    virtual const Markov_LA::M_Matrix<double>& y()const;

    std::size_t numSeries()const;


    XY_PlotData(const Markov_LA::M_Matrix<double>& x,
                const Markov_LA::M_Matrix<double>& y);

    virtual ~XY_PlotData();

private:
   const Markov_LA::M_Matrix<double>* x_;
   const Markov_LA::M_Matrix<double>* y_;

};

}



#endif // XY_PLOTDATA_H
