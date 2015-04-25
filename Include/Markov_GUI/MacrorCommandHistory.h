#ifndef MACRORCOMMANDHISTORY_H
#define MACRORCOMMANDHISTORY_H
#include <QTreeView>
#include <QString>
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>
#include "Markov_Console/Markov_CommandManager.h"

class MacrorCommandHistory: public QTreeView
{
    Q_OBJECT
public:
    MacrorCommandHistory(Markov_Console::Markov_CommandManagerVar* cm,
                         QWidget* parent=0,const QString& fname="");

public slots:
    void addCommand(const QString& line);
    void newSession();


private:
    void newSession(const QString& title);
    void newSessionNoFileWrite(const QString& title);
    void addCommandNoFileWrite(const QString &line);
    QStandardItemModel* data_;
    QStandardItem *lastSession_;
    Markov_Console::Markov_CommandManagerVar* cm_;
};



#endif // MACRORCOMMANDHISTORY_H
