#include "Markov_GUI/MacrorPatchsWindow.h"
#include "Markov_Mol/ABC_PatchModel.h"




MacrorPatchsWindow::MacrorPatchsWindow(
        Markov_Console::Markov_CommandManager *cm,QWidget *parent):
    ABC_ObjectsWindow(cm,parent)
    {

    }


void MacrorPatchsWindow::actualize()
{
    clear();
    for (std::map<std::string, Markov_Mol::ABC_PatchModel*>::iterator it=
         cm_->getPatchs().begin();
         it!=cm_->getPatchs().end();
         ++it)
    {

        std::string name=(*it).first;
        add(QString(name.c_str()));
    }
}
QList<QStandardItem*> MacrorPatchsWindow::objectItems(const QString& modelName)
{
    QList<QStandardItem*> list;

    if (cm_->has_patch(modelName.toStdString()))
    {
        list.append(new QStandardItem(modelName));
        Markov_Mol::ABC_PatchModel* m=cm_->getPatchs()[modelName.toStdString()];
        list.append(new QStandardItem(QString(m->myClass().c_str())));
        list.append(new QStandardItem(QString(m->myName().c_str())));
    }
    return list;
}





