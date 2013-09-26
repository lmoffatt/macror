#include "Markov_GUI/MacrorExperimentsWindow.h"




MacrorExperimentsWindow::MacrorExperimentsWindow(
        Markov_Console::Markov_CommandManager *cm,QWidget *parent):
    ABC_ObjectsWindow(cm,parent)
    {

    }


void MacrorExperimentsWindow::actualize()
{
    clear();
    for (std::map<std::string, Markov_Mol::ABC_Experiment*>::iterator it=
         cm_->getExperiments().begin();
         it!=cm_->getExperiments().end();
         ++it)
    {

        std::string name=(*it).first;
        add(QString(name.c_str()));
    }
}
QList<QStandardItem*> MacrorExperimentsWindow::objectItems(const QString& modelName)
{
    QList<QStandardItem*> list;

    if (cm_->has_experiment(modelName.toStdString()))
    {
        list.append(new QStandardItem(modelName));
        Markov_IO::ABC_Experiment* m=cm_->getExperiments()[modelName.toStdString()];
        list.append(new QStandardItem(QString(m->myClass().c_str())));
        list.append(new QStandardItem(QString(m->myName().c_str())));
    }
    return list;
}






