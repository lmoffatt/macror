#include "Markov_GUI/MacrorModelsWindow.h"




MacrorModelsWindow::MacrorModelsWindow(
        Markov_Console::Markov_CommandManager *cm,QWidget *parent):
    ABC_ObjectsWindow(cm,parent)
    {

    }


void MacrorModelsWindow::actualize()
{
    clear();
    for (std::map<std::string, const Markov_Mol::ABC_Markov_Model*>::iterator it=
         cm_->getModelsConst().begin();
         it!=cm_->getModelsConst().end();
         ++it)
    {

        std::string name=(*it).first;
        add(QString(name.c_str()));
    }
}
QList<QStandardItem*> MacrorModelsWindow::objectItems(const QString& modelName)
{
    QList<QStandardItem*> list;

    if (cm_->has_modelConst(modelName.toStdString()))
    {
        list.append(new QStandardItem(modelName));
        const Markov_Mol::ABC_Markov_Model* m=cm_->getModelsConst()[modelName.toStdString()];
        list.append(new QStandardItem(QString(m->myClass().c_str())));
        list.append(new QStandardItem(QString(m->myName().c_str())));
    }
    return list;
}




