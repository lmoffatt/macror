#include <iostream>

#include "Markov_Plot/Experiment_PlotData.h"

namespace Markov_Plot
{

Experiment_PlotData::Experiment_PlotData()
{
    _p = new Plotter();
    type="ABC_Experiment";
}

Experiment_PlotData::Experiment_PlotData(Plotter *p)
{
    _p = p;
    type="ABC_Experiment";
}

}

