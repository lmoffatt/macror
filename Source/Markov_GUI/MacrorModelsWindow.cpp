#include "Markov_GUI/MacrorModelsWindow.h"
#include "Markov_Mol/ABC_PatchModel.h"




MacrorModelsWindow::MacrorModelsWindow(
        Markov_Console::Markov_CommandManager *cm,QWidget *parent):
    ABC_ObjectsWindow(cm,parent)
    {

    }


void MacrorModelsWindow::actualize()
{
    clear();
    auto modelNames=cm_->getVarsList(Markov_Mol::ABC_Markov_Model::ClassName());
    auto patchNames=cm_->getVarsList(Markov_Mol::ABC_PatchModel::ClassName());

    for (auto name: modelNames)
    {

        add(QString(name.c_str()));
    }
    for (auto name:patchNames)
      {
        add(QString(name.c_str())+".model");
      }
}
QList<QStandardItem*> MacrorModelsWindow::objectItems(const QString& modelName)
{
    QList<QStandardItem*> list;

    // is a model within a patch?
    int n=std::string(".model").size();
    if (modelName.right(n)==".model")
      {
        std::string patchName=modelName.left(modelName.size()-n).toStdString();
        if (cm_->checkVariable(patchName,Markov_Mol::ABC_PatchModel::ClassName()))
          {
            list.append(new QStandardItem(modelName));
            const Markov_Mol::ABC_PatchModel* m=
                dynamic_cast<const Markov_Mol::ABC_PatchModel*>(cm_->getVar(patchName));
            list.append(new QStandardItem(QString(m->Model().myClass().c_str())));
            list.append(new QStandardItem(QString(m->Model().id().c_str())));

          }
      }


    if (cm_->checkVariable(modelName.toStdString(),Markov_Mol::ABC_Markov_Model::ClassName()))
    {
        list.append(new QStandardItem(modelName));
        const Markov_Mol::ABC_Markov_Model* m=
            dynamic_cast<const Markov_Mol::ABC_Markov_Model*>(cm_->getVar(modelName.toStdString()));
        list.append(new QStandardItem(QString(m->myClass().c_str())));
        list.append(new QStandardItem(QString(m->id().c_str())));
    }
    return list;
}




