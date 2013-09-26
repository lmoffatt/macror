#ifndef ABC_OBJECTSWINDOW_H
#define ABC_OBJECTSWINDOW_H


#include <QTableView>
#include <QString>
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>

#include "Markov_Console/Markov_CommandManager.h"
class ABC_ObjectsWindow: public QTableView
{
    Q_OBJECT
public:
    ABC_ObjectsWindow(Markov_Console::Markov_CommandManager* cm,
                       QWidget* parent=0);

    virtual ~ABC_ObjectsWindow(){}
public slots:
    virtual void add(const QString& ObjectName);
    virtual void remove(const QString& ObjectName);

    virtual void clear();
    virtual QList<QStandardItem*> objectItems(const QString& modelName)=0;


private slots:
    virtual void actualize()=0;


protected:
    QStandardItemModel* data_;

    Markov_Console::Markov_CommandManager * cm_;


 };




#endif // ABC_OBJECTSWINDOW_H
