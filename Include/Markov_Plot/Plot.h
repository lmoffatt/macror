#ifndef PLOT_H
#define PLOT_H

#include "Forms/plotscreen.h"

#include "Markov_Plot/ABC_PlotData.h"
#include "Markov_Plot/Experiment_PlotData.h"


namespace Markov_Plot
{

class Plot
{
public:

    Plot(Markov_Plot::ABC_PlotData* pd, std::string onfile)
    {
        if(pd->type=="ABC_Experiment")
            PlotExperiment((Markov_Plot::Experiment_PlotData*)pd, onfile);
    }

    Plot(Markov_Plot::ABC_PlotData* pd, QWidget* parent)
    {
        if(pd->type=="ABC_Experiment")
            PlotExperiment((Markov_Plot::Experiment_PlotData*)pd, "", parent);
    }

private:
    void PlotExperiment(Markov_Plot::Experiment_PlotData* pd,
                        std::string onfile,
                        QWidget* parent = NULL)
    {
        if (onfile == "")
        {
            pd->getPlotter()->save("temp.png");
            //show
            PlotScreen* ps = new PlotScreen(parent);
            ps->show();
        }
        else
            pd->getPlotter()->save(onfile);
    }

};

}
#endif // PLOT_H
