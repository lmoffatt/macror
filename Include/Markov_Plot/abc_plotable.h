#ifndef ABC_PLOTABLE_H
#define ABC_PLOTABLE_H

#include <string>


namespace Markov_Plot
{

/// Abstract base class of objects that can be plotted
class ABC_Plotable
{
public:
    static std::string ClassName();
    virtual std::string myName()const=0;
    virtual std::string myClass()const=0;
    virtual std::string mySuperClass()const;

  //  virtual Experiment_PlotData* Get_PlotData();
};

}

#endif // ABC_PLOTABLE_H
