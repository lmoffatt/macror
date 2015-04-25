#ifndef MACRORMODELSWINDOW_H
#define MACRORMODELSWINDOW_H

#include "Markov_GUI/ABC_ObjectsWindow.h"
class MacrorModelsWindow: public ABC_ObjectsWindow
{
    Q_OBJECT
public:
    MacrorModelsWindow(Markov_Console::Markov_CommandManager *cm,
                       QWidget* parent=0);

public slots:
    virtual QList<QStandardItem*> objectItems(const QString& modelName);


private slots:
    void actualize();

};








#endif // MACRORMODELSWINDOW_H
