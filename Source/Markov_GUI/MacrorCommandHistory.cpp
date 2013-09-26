#include "Markov_GUI/MacrorCommandHistory.h"
#include <QDate>
#include <QFile>

MacrorCommandHistory::MacrorCommandHistory(
    Markov_Console::Markov_CommandManager* cm,
    QWidget* parent,const QString& fname):
    QTreeView(parent),
    cm_(cm)
{
    data_=new QStandardItemModel(this);
    setModel(data_);
    f_.setFileName(fname);
    if (fname.isEmpty()||!(f_.open(QIODevice::ReadWrite|QIODevice::Text)))
    {
            f_.setFileName("commandHistory.txt");
            f_.open(QIODevice::ReadWrite|QIODevice::Text);
    }
    fs_.setDevice(&f_);

         while (!fs_.atEnd()) {
             QString line = fs_.readLine();
             if (line.startsWith("%-- "))
             {
                 newSessionNoFileWrite(line);
             }
             else
             {
                 addCommandNoFileWrite(line);
             }
         }

         f_.close();
         f_.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append);
         fs_.setDevice(&f_);

         newSession();
         setHeaderHidden(true);


}

void MacrorCommandHistory::addCommandNoFileWrite(const QString &line)
{
    lastSession_->appendRow(new QStandardItem(line));
    cm_->getH().push_back(line.toStdString());



}
void MacrorCommandHistory::addCommand(const QString &line)
{
    addCommandNoFileWrite(line);
    fs_<<line<<"\n";
    fs_.flush();

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
    fs_<<title<<"\n";
    fs_.flush();

}

