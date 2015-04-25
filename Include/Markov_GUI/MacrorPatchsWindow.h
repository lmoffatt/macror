#ifndef MACRORPATCHSWINDOW_H
#define MACRORPATCHSWINDOW_H



#include "Markov_GUI/ABC_ObjectsWindow.h"
class MacrorPatchsWindow: public ABC_ObjectsWindow
{
    Q_OBJECT
public:
    MacrorPatchsWindow(Markov_Console::Markov_CommandManager *cm,
                       QWidget* parent=0);

public slots:
    virtual QList<QStandardItem*> objectItems(const QString& modelName);


private slots:
    void actualize();

};





#endif // MACRORPATCHSWINDOW_H
