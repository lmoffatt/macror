#include "Markov_Plot/XY_PlotData.h"
#include <QString>
namespace Markov_Plot
{
     std::string XY_PlotData::type()
{return "XY_Data";}


     const Markov_LA::M_Matrix<double>& XY_PlotData::x()const
     {
         return *x_;
     }
     const Markov_LA::M_Matrix<double>& XY_PlotData::y()const
     {
         return *y_;
     }

     XY_PlotData::XY_PlotData(const Markov_LA::M_Matrix<double>& x,
                 const Markov_LA::M_Matrix<double>& y):
         x_(&x),
         y_(&y)
     {}


     XY_PlotData::~XY_PlotData()
     {
         delete x_;
         delete y_;
     }

}

