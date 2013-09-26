#ifndef ABC_PLOT_H
#define ABC_PLOT_H
#include <vector>

#include <QGraphicsScene>


class ABC_Plot
{
    ABC_Plot(std::vector<double> x, std::vector<double> y);



 private:
    std::vector<double> x_,y_;


};


#endif // ABC_PLOT_H
