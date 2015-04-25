#include "Markov_GUI/MacrorExperimentsWindow.h"




MacrorExperimentsWindow::MacrorExperimentsWindow(Markov_Console::Markov_CommandManager *cm, QWidget *parent):
    ABC_ObjectsWindow(cm,parent)
    {

    }


void MacrorExperimentsWindow::actualize()
{
    clear();
    auto names=cm_->getVarsList(Markov_IO::ABC_Experiment::ClassName());

    for (auto name:names)
      {
        add(QString(name.c_str()));
      }

}
QList<QStandardItem*> MacrorExperimentsWindow::objectItems(const QString& modelName)
{
    QList<QStandardItem*> list;

    if (cm_->checkVariable(modelName.toStdString(),Markov_IO::ABC_Experiment::ClassName()))
    {
        list.append(new QStandardItem(modelName));
        const Markov_IO::ABC_Experiment* m=
            dynamic_cast<const Markov_IO::ABC_Experiment*>(cm_->getVar(modelName.toStdString()));
        list.append(new QStandardItem(QString(m->myClass().c_str())));
        list.append(new QStandardItem(QString(m->id().c_str())));
    }

    return list;
}






