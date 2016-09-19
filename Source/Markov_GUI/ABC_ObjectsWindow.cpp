#include "Markov_GUI/ABC_ObjectsWindow.h"

namespace Markov_IO_New {




ABC_ObjectsWindow::ABC_ObjectsWindow(Markov_CommandManagerVar *cm,
                                     const std::string &objectclass,
                                     QWidget *parent):
  QTableView(parent),
  data_{},
  cm_(cm),
  objectClass_(objectclass)

{
  data_=new QStandardItemModel(this);
  setModel(data_);

}

void ABC_ObjectsWindow::add(const QString &modelName)
{
  QList<QStandardItem*> res=data_->findItems(modelName);
  QList<QStandardItem*> items=objectItems(modelName);
  if(res.isEmpty())
    data_->appendRow(items);
  else
    {
      int i=res.last()->row();
      for (int j=1; j<data_->columnCount();++j)
        {
          data_->item(i,j)->setData(items.at(j)->data());
        }
      while (!items.isEmpty())
        delete items.takeFirst();

    }
}

void ABC_ObjectsWindow::remove(const QString &modelName)
{
  QList<QStandardItem*> res=data_->findItems(modelName);
  if(!res.isEmpty())
    {
      int i=res.last()->row();
      data_->removeRow(i);
    }
}


void ABC_ObjectsWindow::clear()
{
  data_->clear();
}


}



