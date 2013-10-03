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
  auto patchNames=cm_->getVarsList(Markov_Mol::ABC_PatchModel::ClassName());

  for (auto name:patchNames)
    {
      add(QString(name.c_str()));
    }
}
QList<QStandardItem*> MacrorPatchsWindow::objectItems(const QString& modelName)
{
  QList<QStandardItem*> list;


  if (cm_->checkVariable(modelName.toStdString(),Markov_Mol::ABC_PatchModel::ClassName()))
  {
      list.append(new QStandardItem(modelName));
      const Markov_Mol::ABC_PatchModel* m=
          dynamic_cast<const Markov_Mol::ABC_PatchModel*>(cm_->getVar(modelName.toStdString()));
      list.append(new QStandardItem(QString(m->myClass().c_str())));
      list.append(new QStandardItem(QString(m->myName().c_str())));
  }

  return list;
}





