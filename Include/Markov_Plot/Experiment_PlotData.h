#ifndef EXPERIMENT_PLOTDATA_H
#define EXPERIMENT_PLOTDATA_H

#include <Markov_Plot/ABC_PlotData.h>
#include <Markov_Plot/plotter.h>

namespace Markov_Plot
{

class Experiment_PlotData : public ABC_PlotData
{
public:
    Experiment_PlotData();
    Experiment_PlotData(Plotter *p);

    Plotter* getPlotter() {return _p;}

private:
    Plotter *_p;
};

}

#endif // EXPERIMENT_PLOTDATA_H
