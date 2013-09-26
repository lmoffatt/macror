#ifndef MARKOV_COMMANDMANAGERGUI_H
#define MARKOV_COMMANDMANAGERGUI_H

#include <QDialog>

#include <Markov_Mol/QMarkovModel.h>
#include <Markov_IO/RandomPulses.h>
#include <Markov_IO/SinglePulses.h>
#include <Markov_IO/filemanager.h>
#include <Markov_Mol/ExperimentSimulation.h>
#include <Markov_Mol/MarkovSimulator.h>
#include <Markov_Mol/GaussianNoise.h>

#include <map>
#include <vector>

#include <string>
#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <algorithm>

#include <Markov_Console/Markov_CommandManager.h>
//#include <Markov_Plot/Plot.h>
#include <QList>
#include <QStandardItem>


namespace Markov_Console
{
class Markov_CommandManagerGui : public Markov_CommandManager
{

protected:
    void plot(const std::string& aexperiment);
    void plot_save(const std::string& aexperiment, std::string file);
    void show_help();
    virtual void model_channel(const std::string &varname);


public:
    Markov_CommandManagerGui();
    bool next_instruction();
    QList<QStandardItem*> modelItems(const QString& modelName);


};

}

#endif // MARKOV_COMMANDMANAGERGUI_H
