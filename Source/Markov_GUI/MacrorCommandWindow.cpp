#include <QTextBlock>
#include <QInputDialog>

#include <QLabel>
#include <QString>

#include "Markov_Console/Autocomplete.h"
#include "Markov_GUI/MacrorCommandWindow.h"
#include "Markov_GUI/MacrorMainWindow.h"

#include "Markov_GUI/MacrorEditWindow.h"
#include "Markov_GUI/MacrorExitWindow.h"
#include "Markov_GUI/MacrorCreateCommand.h"
#include "Markov_GUI/CdCommandGUI.h"

#include "Markov_GUI/MyInputDialog.h"

#include "Markov_Mol/QMarkovModel.h"


#include "Markov_Plot/GraphWindow.h"
#include "Markov_Plot/GraphView.h"

#include "Markov_Plot/XY_PlotData.h"


MacrorCommandWindow::MacrorCommandWindow(MacrorMainWindow *parent ,
                                         Markov_Console::Markov_CommandManager* cm):
  QPlainTextEdit(parent),
  mw_(parent),
  cm_(cm),
  message(nullptr)
{
  cm_->setIO(this);

  cm_->add_command(new MacrorEditCommand(cm_));
  cm_->add_command(new MacrorExitCommand(cm_,mw_));
  cm_->add_command(new MacrorCreateCommand(cm_));
  cm_->add_command(new Markov_GUI::CdCommandGUI(cm_,mw_));
  unsigned windowWidth=35;
  *this<<cm_->wellcomeMessage(windowWidth);

  *this<<">>";

  //  connect(this, SIGNAL(blockCountChanged(int)),
  //          this, SLOT(next_instruction()));


}

MacrorCommandWindow::~MacrorCommandWindow()
{
}

void MacrorCommandWindow::commandLine(const QString& line)
{
  if (!graphCommandLine(line))
    {
      MarkovCommand()->add_tokens(line.toStdString());
      if (MarkovCommand()->next_instruction())
        emit commandLineExecuted(line);
    }
}

void MacrorCommandWindow::addCommandLine(const QString& line)
{
  insertPlainText(line);
  appendPlainText("");
  this->update();

}



bool MacrorCommandWindow::graphCommandLine(const QString& line)
{
  if (line.startsWith("plot "))
    {
      if (plot(line.mid(5)))
        emit commandLineExecuted(line);
      return true;
    }
  else if (line.startsWith("edit "))
    {
      if (edit(line.mid(5)))
        emit commandLineExecuted(line);
      return true;

    }
  return false;

}

bool MacrorCommandWindow::plot(const QString& line)
{
  if (MarkovCommand()->checkVariable(line.toStdString(),Markov_IO::ABC_Experiment::ClassName()))
    {
      Markov_IO::ABC_Experiment* e=dynamic_cast<Markov_IO::ABC_Experiment*>(
            MarkovCommand()->getVar(line.toStdString()));
      Markov_Plot::GraphWindow* g=Markov_Plot::plot(0,*e);
      mw_->createGraph(g);


      return true;

    }
  else return false;
}

bool MacrorCommandWindow::modelChannel(const QString& varname)
{
  Markov_Mol::Q_Markov_Model* p=new Markov_Mol::Q_Markov_Model();
  cm_->delete_var(varname.toStdString());
  cm_->add_var(varname.toStdString(),p);
  return edit(varname);
}



bool MacrorCommandWindow::edit(const QString& varname)
{
  MacrorEditWindow* eW=new MacrorEditWindow(varname,cm_);
  eW->show();
  //BUG: does not make sense it does not return nothing
}


void MacrorCommandWindow::next_instruction()
{

  QString line=document()->lastBlock().previous().text();
  line.remove(0,2);
  disconnect(this, SIGNAL(blockCountChanged(int)),
             this, SLOT(next_instruction()));
  commandLine(line);

  appendPlainText(">>");
  connect(this, SIGNAL(blockCountChanged(int)),
          this, SLOT(next_instruction()));
  connect(this, SIGNAL(outputGenerated(QString)),
          this,SLOT(appendPlainText(QString)));

  connect(this, SIGNAL(blockCountChanged(int)),
          this,SLOT(repaint()));


}

Markov_Console::Markov_CommandManager* MacrorCommandWindow::MarkovCommand()
{
  return cm_;
}

QString MacrorCommandWindow::getDir()const
{
  return QString(MarkovCommand()->getDir().c_str());
}


const Markov_Console::Markov_CommandManager*
MacrorCommandWindow::MarkovCommand()const
{
  return cm_;
}

bool MacrorCommandWindow::lastCommandResult()const
{
  return MarkovCommand()->lastCommandResult();
}

void	MacrorCommandWindow::keyPressEvent ( QKeyEvent * e )
{
  if (message !=nullptr)  // message indicates a cue to the operator like a missing parameter
    message->close();
  if (textCursor().blockNumber()!=blockCount()-1)
    moveCursor(QTextCursor::End);
  QTextCursor c=textCursor();
  auto p=c.position();
  QString line;

  switch(e->key())
    {
    case Qt::Key_Home:
      {
        moveCursor(QTextCursor::StartOfBlock);
        moveCursor(QTextCursor::Right,QTextCursor::MoveAnchor);
        moveCursor(QTextCursor::Right,QTextCursor::MoveAnchor);
        break;
      }
    case Qt::Key_Left:
      {
        if(textCursor().positionInBlock()>2)
          {
            moveCursor(QTextCursor::Left,QTextCursor::MoveAnchor);
            tail.prepend(cmdWord[0]);
            cmdWord.chop(1);

          }

      }
      break;
    case Qt::Key_Backspace:
      {
        if(textCursor().positionInBlock()>2)
          {
            QPlainTextEdit::keyPressEvent(e);
            tail.clear();
            if (!cmdWord.isEmpty())
              cmdWord.chop(1);
            else
              cmdLine.chop(1);
          }

      }
      break;
    case Qt::Key_Right:
      {
        moveCursor(QTextCursor::Right,QTextCursor::MoveAnchor);
        if (!tail.isEmpty())
          {
            cmdWord.append(tail[0]);
            tail.remove(0,1);
          }
      }
      break;
    case Qt::Key_Up:
      {
        tail=cm_->getH().up((cmdLine+cmdWord).toStdString()).c_str();

        c.setPosition(p);
        c.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
        c.removeSelectedText();
        c.insertText(tail);
        c.setPosition(p);
        setTextCursor(c);
      }
      break;

      //    case Qt::Key_Right:
    case Qt::Key_Down:
      {

        tail=cm_->getH().down((cmdLine+cmdWord).toStdString()).c_str();
        c.setPosition(p);
        c.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
        c.removeSelectedText();
        c.insertText(tail);
        c.setPosition(p);
        setTextCursor(c);
      }
      break;

    case Qt::Key_Tab:
      {
        c.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
        c.removeSelectedText();
        setTextCursor(c);


        std::vector<std::string> res=
            cm_->complete(cmdWord.toStdString());

        if ((res.size()==1)&&(res.front()[0]!='<')&&(res.front()[0]!='['))
          {
            tail=
                Markov_Console::Autocomplete::suggestedCharacters(
                  res,cmdWord.toStdString()).c_str();
            c.movePosition(QTextCursor::EndOfLine);
            c.insertText(tail);
            setTextCursor(c);
            cmdWord+=tail;
            tail.clear();

           }
        else if(res.size()>0)
          {
            if (previous_key==Qt::Key_Tab)
              {

                tail=Markov_Console::Autocomplete::suggestedCharacters(res,cmdWord.toStdString()).c_str();
                auto pp=c.position();
                c.insertText(tail);
                setTextCursor(c);
                cmdWord+=tail;
                tail.clear();

                QStringList list;
                QString field;
                for (auto item:res)
                  {
                    if ((item.front()=='<')||(item.front()=='['))
                      field=QString(item.substr(1,item.size()-2).c_str());
                    else
                      list<<QString(item.c_str());
                  }
                if (list.size()>0)
                  {
                    bool ok;
                    QString fieldselect = Markov_GUI::MyInputDialog::getItem(this,cmdLine,list,&ok,0);
                    std::stringstream ss(fieldselect.toStdString());
                    Markov_Console::Token tok;
                    tok.get(ss);
                    ss.get();
                    if (ss)
                      {
                        fieldselect.prepend('"');
                        fieldselect.append('"');
                      }
                    if (ok && !fieldselect.isEmpty())
                      {
                        c.setPosition(c.position()-cmdWord.size(),QTextCursor::KeepAnchor);
                        c.removeSelectedText();
                        setTextCursor(c);
                        c.insertText(fieldselect);
                        setTextCursor(c);

                        cmdWord=fieldselect;
                      }
                  }
                else
                  {
                    QString field;
                    for (std::size_t i=0;i<res.size()-1; i++)
                      {
                        if ((res[i].front()=='<')||(res[i].front()=='['))
                          field+=QString(res[i].c_str())+QString(",");

                      }
                    field+=res.back().c_str();
                    message=new QLabel(field,this);
                    message->setBuddy(this);
                    message->setFrameStyle(QFrame::Panel | QFrame::Sunken);
                    message->move(cursorRect().center().operator +=(QPoint(+10,-10)));

                    message->show();

                  }
              }
          }

      }

      break;
    case Qt::Key_PageUp:
    case Qt::Key_PageDown:
      break;
    case Qt::Key_Space:
      {
        QTextCursor c=textCursor();
        c.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
        c.removeSelectedText();
        QString err=cm_->add_single_token(cmdWord.toStdString()).c_str();
        if (!err.toStdString().empty())
          {
            c.insertText("\n");
            setTextCursor(c);
            putError(err.toStdString());
            cmdWord.clear();
            c.insertText(">>"+cmdLine);
            setTextCursor(c);
          }
        else
          {
            cmdLine+=cmdWord+" ";
            c.insertText(" ");
            setTextCursor(c);
            cmdWord.clear();

          }
      }
      break;
    default:
      {
        QString s=e->text();
        if (s=="\r")
          {
            cmdLine+=cmdWord+tail;
            c.movePosition(QTextCursor::EndOfLine);

            c.insertText("\n");
            setTextCursor(c);

            commandLine(cmdLine);
            put(">>");
            cm_->clear_tokens();
            cmdLine.clear();
            cmdWord.clear();
            tail.clear();
            cm_->getH().reset();

          }
        else
          {
            cmdWord+=s;
            c.insertText(s);
            setTextCursor(c);

          }
      }

    }
  previous_key=e->key();
}


/// get a string from the input source
std::string MacrorCommandWindow::getline()
{

  QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                       tr("User name:"));

  return text.toStdString();
}

/// put a string to the output source
void MacrorCommandWindow::put(const std::string& s)
{
  insertPlainText(s.c_str());
  moveCursor(QTextCursor::End);
}

/// put a string to the output source
void MacrorCommandWindow::putError(const std::string& s)
{
  textCursor().insertHtml("<font color=\"Red\">"+QString(s.c_str())+"</font><br>");
  moveCursor(QTextCursor::End);

}


