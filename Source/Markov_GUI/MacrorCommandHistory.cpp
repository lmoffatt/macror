#include "Markov_GUI/MacrorCommandHistory.h"



#include <QDate>
#include <QFile>


#include "Markov_IO/auxiliarIO.h"

MacrorCommandHistory::MacrorCommandHistory(Markov_Console::Markov_CommandManagerVar *cm,
        QWidget* parent, const QString& ):
    QTreeView(parent),
    cm_(cm)
{
    data_=new QStandardItemModel(this);
    setModel(data_);
    std::string previousHistory=cm_->getH().history();

    std::stringstream ss(previousHistory);

    std::string line;
    Markov_IO::safeGetline(ss, line);

    newSessionNoFileWrite(line.c_str());

    while (Markov_IO::safeGetline(ss, line))
    {
       if (line.substr(0,3)=="%-- ")
        {
            newSessionNoFileWrite(line.c_str());
        }
        else
        {
            addCommandNoFileWrite(line.c_str());
        }
    }

        newSession();
    setHeaderHidden(true);


}

void MacrorCommandHistory::addCommandNoFileWrite(const QString &line)
{
    lastSession_->appendRow(new QStandardItem(line));



}
void MacrorCommandHistory::addCommand(const QString &line)
{
    addCommandNoFileWrite(line);
    cm_->getH().push_back(line.toStdString());
    //fs_<<line<<"\n";
    //fs_.flush();

}


void MacrorCommandHistory::newSession(){
    newSession(QDateTime::currentDateTime().toString().prepend("%-- ").append(" --%"));

}

void MacrorCommandHistory::newSessionNoFileWrite(const QString& title)
{
    data_->appendRow(new QStandardItem(title));
    lastSession_ = data_->item(data_->rowCount()-1);

}
void MacrorCommandHistory::newSession(const QString& title)
{
    newSessionNoFileWrite(title);
    cm_->getH().push_back(title.toStdString());
   // fs_<<title<<"\n";
   // fs_.flush();

}

