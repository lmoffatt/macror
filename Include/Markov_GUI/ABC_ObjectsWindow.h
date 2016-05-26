#ifndef ABC_OBJECTSWINDOW_H
#define ABC_OBJECTSWINDOW_H


#include <QTableView>
#include <QString>
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>

#include "Markov_Console/Markov_CommandManager.h"

namespace Markov_IO_New {
class ABC_ObjectsWindow: public QTableView
{
  Q_OBJECT
public:
  ABC_ObjectsWindow(Markov_CommandManagerVar *cm,
                    const std::string& objectclass,
                    QWidget* parent=0);



  virtual ~ABC_ObjectsWindow(){}
public slots:
  virtual void add(const QString& ObjectName);
  virtual void remove(const QString& ObjectName);

  virtual void clear();
  virtual QList<QStandardItem*> objectItems(const QString& modelName)
  {
    QList<QStandardItem*> list;


    std::string whyNot;

    auto m=cm_->idToValue(modelName.toStdString(),objectClass_,&whyNot,"");
    if (m!=nullptr)
    {
        list.append(new QStandardItem(modelName));
        list.append(new QStandardItem(QString(m->myType().c_str())));
      //  auto superclasses=m->mySuperClasses();
     //   for (std::string sc:superclasses)
       // list.append(new QStandardItem(QString(sc.c_str())));
    }

    return list;

  }


private slots:
  virtual void actualize()
  {
    clear();
    auto names=cm_->getIdsOfVarType(objectClass_,false);

    for (auto name:names)
      {
        add(QString(name.c_str()));
      }
  }


protected:
  QStandardItemModel* data_;

  Markov_CommandManagerVar * cm_;

  std::string objectClass_;


};
}

class ABC_ObjectsWindow: public QTableView
{
  Q_OBJECT
public:
  ABC_ObjectsWindow(Markov_Console::Markov_CommandManagerVar *cm,
                    const std::string& objectclass,
                    QWidget* parent=0);



  virtual ~ABC_ObjectsWindow(){}
public slots:
  virtual void add(const QString& ObjectName);
  virtual void remove(const QString& ObjectName);

  virtual void clear();
  virtual QList<QStandardItem*> objectItems(const QString& modelName)
  {
    QList<QStandardItem*> list;

    auto m=cm_->idToValue(modelName.toStdString(),objectClass_);
    if (m!=nullptr)
    {
        list.append(new QStandardItem(modelName));
        list.append(new QStandardItem(QString(m->myClass().c_str())));
        auto superclasses=m->mySuperClasses();
        for (std::string sc:superclasses)
        list.append(new QStandardItem(QString(sc.c_str())));
    }

    return list;

  }


private slots:
  virtual void actualize()
  {
    clear();
    auto names=cm_->getListComplying(objectClass_);

    for (auto name:names)
      {
        add(QString(name.c_str()));
      }
  }


protected:
  QStandardItemModel* data_;

  Markov_Console::Markov_CommandManagerVar * cm_;

  std::string objectClass_;


};


#endif // ABC_OBJECTSWINDOW_H
