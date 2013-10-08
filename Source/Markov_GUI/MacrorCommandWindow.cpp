#include <QTextBlock>
#include <QInputDialog>
#include "Markov_GUI/MacrorCommandWindow.h"
#include "Markov_GUI/MacrorMainWindow.h"

#include "Markov_GUI/MacrorEditWindow.h"
#include "Markov_GUI/MacrorExitWindow.h"
#include "Markov_GUI/MacrorCreateCommand.h"


#include "Markov_Mol/QMarkovModel.h"


#include "Markov_Plot/GraphWindow.h"
#include "Markov_Plot/GraphView.h"

#include "Markov_Plot/XY_PlotData.h"


MacrorCommandWindow::MacrorCommandWindow(MacrorMainWindow *parent ,
                                         Markov_Console::Markov_CommandManager* cm):
  QPlainTextEdit(parent),
  mw_(parent),
  cm_(cm),
  cout_buff_backup(std::cout.rdbuf()),
  cerr_buff_backup(std::cerr.rdbuf())

{
  std::cout.rdbuf(this->cout_string_.rdbuf());
  std::cerr.rdbuf(this->cout_string_.rdbuf());
  cm_->setIO(this);

  cm_->add_command(new MacrorEditCommand(cm_));
  cm_->add_command(new MacrorExitCommand(cm_,mw_));
  cm_->add_command(new MacrorCreateCommand(cm_));
  unsigned windowWidth=35;
  appendPlainText(QString(cm_->wellcomeMessage(windowWidth).c_str()));

  appendPlainText(">>");
  std::stringstream ss;

  connect(this, SIGNAL(blockCountChanged(int)),
          this, SLOT(next_instruction()));


}

MacrorCommandWindow::~MacrorCommandWindow()
{
  std::cout.rdbuf(cout_buff_backup);
  std::cerr.rdbuf(cout_buff_backup);
}

void MacrorCommandWindow::commandLine(const QString& line)
{
  if (!graphCommandLine(line))
    {
      MarkovCommand()->add_tokens(line.toStdString());
      if (MarkovCommand()->next_instruction())
        emit commandLineExecuted(line);
    }
  std::cout.flush();
  appendPlainText(cout_string_.str().c_str());
  cout_string_.str("");
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
  edit(varname);
}



bool MacrorCommandWindow::edit(const QString& varname)
{
  MacrorEditWindow* eW=new MacrorEditWindow(varname,cm_);
  eW->show();

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
  if (textCursor().blockNumber()!=blockCount()-1)
     moveCursor(QTextCursor::End);

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
        moveCursor(QTextCursor::Left,QTextCursor::MoveAnchor);

      }
      break;
     case Qt::Key_Backspace:
      {
        if(textCursor().positionInBlock()>2)
          QPlainTextEdit::keyPressEvent(e);

      }
      break;
    case Qt::Key_Right:
      {
        moveCursor(QTextCursor::Right,QTextCursor::MoveAnchor);

      }
      break;
    case Qt::Key_Up:
      {

        QTextCursor c=textCursor();
        auto p=c.position();
        c.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
        c.removeSelectedText();
        c.movePosition(QTextCursor::StartOfLine,QTextCursor::KeepAnchor);
        c.movePosition(QTextCursor::Right,QTextCursor::KeepAnchor,2);

        QString line=c.selectedText();
        QString tail(cm_->getH().up(line.toStdString()).c_str());
        c.setPosition(p);
        c.insertText(tail);
        c.setPosition(p);
        setTextCursor(c);
      }
      break;

      //    case Qt::Key_Right:
    case Qt::Key_Down:
      {
        QTextCursor c=textCursor();
        auto p=c.position();
        c.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
        c.removeSelectedText();
        c.movePosition(QTextCursor::StartOfLine,QTextCursor::KeepAnchor);
        c.movePosition(QTextCursor::Right,QTextCursor::KeepAnchor,2);

        QString line=c.selectedText();
        QString tail(cm_->getH().down(line.toStdString()).c_str());
        c.setPosition(p);
        c.insertText(tail);
        c.setPosition(p);
        setTextCursor(c);
      }
      break;

    case Qt::Key_Tab:
      {

      }

    break;
    case Qt::Key_PageUp:
    case Qt::Key_PageDown:
      break;
    default:
      QPlainTextEdit::keyPressEvent(e);
    }
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
  QString out=s.c_str();
  emit outputGenerated(out);
}



