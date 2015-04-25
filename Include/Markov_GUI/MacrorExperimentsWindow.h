#ifndef MACROREXPERIMENTSWINDOW_H
#define MACROREXPERIMENTSWINDOW_H


#include "Markov_GUI/ABC_ObjectsWindow.h"
class MacrorExperimentsWindow: public ABC_ObjectsWindow
{
    Q_OBJECT
public:
    MacrorExperimentsWindow(Markov_Console::Markov_CommandManager *cm,
                       QWidget* parent=0);

public slots:
    virtual QList<QStandardItem*> objectItems(const QString& modelName);


private slots:
    void actualize();

};







#endif // MACROREXPERIMENTSWINDOW_H
