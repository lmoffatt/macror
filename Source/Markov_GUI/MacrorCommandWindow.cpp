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


#include "Markov_Plot/GraphicPage.h"
#include "Markov_Plot/GraphView.h"

#include "Markov_Plot/XY_PlotData.h"

#include <iostream>

MacrorCommandWindow::MacrorCommandWindow(MacrorMainWindow *parent ,
                                         Markov_Console::Markov_CommandManagerVar *cm):
  QPlainTextEdit(parent),
  mw_(parent),
  cm_(cm),
  message(new QLabel(this))
{
  cm_->setIO(this);

  //TODO: add them later
//  cm_->add_command(new MacrorEditCommand(cm_));
//  cm_->add_command(new MacrorExitCommand(cm_,mw_));
//  cm_->add_command(new MacrorCreateCommand(cm_));
//  cm_->add_command(new Markov_GUI::CdCommandGUI(cm_,mw_));
  unsigned windowWidth=35;
  put(cm_->getProgram().wellcomeMessage(windowWidth));

  put(">>");

  //  connect(this, SIGNAL(blockCountChanged(int)),
  //          this, SLOT(next_instruction()));


}

MacrorCommandWindow::~MacrorCommandWindow()
{
}

void MacrorCommandWindow::commandLine(const QString& line)
{
//  if (!graphCommandLine(line))
//    {
//      MarkovCommand()->add_tokens(line.toStdString());
//      if (MarkovCommand()->next_instruction())
//        emit commandLineExecuted(line);
//    }
}

void MacrorCommandWindow::addCommandLine(const QString& line)
{
//  MarkovCommand()->add_tokens(line.toStdString());

//  moveCursor(QTextCursor::End);
//  insertPlainText(line);

//  cmdLine=line;

//  textCursor().movePosition(QTextCursor::EndOfLine);

//  textCursor().insertText("\n");

//  commandLine(cmdLine);
//  put(">>");
////  cm_->clear_tokens();
//  cmdLine.clear();
//  cmdWord.clear();
//  tail.clear();
//  cm_->getH().reset();
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
//  if (MarkovCommand()->checkVariable(line.toStdString(),Markov_IO::ABC_Experiment::ClassName()))
//    {
//      Markov_IO::ABC_Experiment* e=dynamic_cast<Markov_IO::ABC_Experiment*>(
//            MarkovCommand()->getVar(line.toStdString()));
//      Markov_Plot::GraphicPage* g=Markov_Plot::plot(0,MarkovCommand(),e->id(),*e);
//      mw_->createGraph(g);


//      return true;

//    }
//  else return false;
}

// TODO: replace with ABC_Var logic
bool MacrorCommandWindow::modelChannel(const QString& varname)
{
  /*
  Markov_Mol::Q_Markov_Model* p=new Markov_Mol::Q_Markov_Model();
  cm_->delete_var(varname.toStdString());
  cm_->add_var(varname.toStdString(),p);
  return edit(varname);
  */
}



bool MacrorCommandWindow::edit(const QString& varname)
{
  //MacrorEditWindow* eW=new MacrorEditWindow(varname,cm_);
  //eW->show();
  //BUG: does not make sense to return a boolean since it does not return nothing
  return true;
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

Markov_Console::Markov_CommandManagerVar *MacrorCommandWindow::MarkovCommand()
{
  return cm_;
}

QString MacrorCommandWindow::getDir()const
{
  return QString(MarkovCommand()->getDir().c_str());
}

std::string MacrorCommandWindow::getItemFromList(const std::string &title, const std::vector<std::string> &list, bool &ok, std::size_t current)
{
 return Markov_GUI::MyInputDialog::getItem(this,title,list,&ok,current);

}

std::string MacrorCommandWindow::getItemFromSeveralLists(const std::string &title, const std::map<std::string, std::vector<std::string> > &list, bool &ok, std::size_t current)
{
  return Markov_GUI::MyInputDialog::getItem(this,title,list.begin()->second,&ok,current);

}

void MacrorCommandWindow::erase_from_cursor(int n)
{
  QTextCursor c=textCursor();
  c.setPosition(c.position()+n,QTextCursor::KeepAnchor);
  c.removeSelectedText();
   setTextCursor(c);
   repaint();
 }

void MacrorCommandWindow::move_cursor(int n)
{

  if (n>0)
    {
  for (int i=0; i<n; ++i)
    moveCursor(QTextCursor::Right,QTextCursor::MoveAnchor);
    }
  else
    {
      for (int i=0; i<-n; ++i)
      moveCursor(QTextCursor::Left,QTextCursor::MoveAnchor);
    }
  repaint();
}

void MacrorCommandWindow::cleanLastLine()
{
  moveCursor(QTextCursor::End);
}

void MacrorCommandWindow::move_end()
{
  moveCursor(QTextCursor::End);
}


const Markov_Console::Markov_CommandManagerVar*
MacrorCommandWindow::MarkovCommand()const
{
  return cm_;
}

bool MacrorCommandWindow::lastCommandResult()const
{
//  return MarkovCommand()->lastCommandResult();
}

void	MacrorCommandWindow::keyPressEvent ( QKeyEvent * e )
{

  Markov_IO::Key k=QKeyToKey(e);
  cm_->KeyEvent(k);

}




///// get a string from the input source
//std::string MacrorCommandWindow::getline()
//{

//  QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
//                                       tr("User name:"));

//  return text.toStdString();
//}

/// put a string to the output source
void MacrorCommandWindow::put(const std::string& s)
{
  QString qs(s.c_str());
  insertPlainText(qs);
  std::size_t n=qs.size();
  move_cursor(n);
  repaint();
}

/// insert a string to the output source
void MacrorCommandWindow::insertText(const std::string& s)
{
  QString qs(s.c_str());
  insertPlainText(qs);
  repaint();
}



/// put a string to the output source
void MacrorCommandWindow::putError(const std::string& s)
{
  QString qs(s.c_str());
  std::size_t n=qs.size();
  textCursor().insertHtml("<font color=\"Red\">"+qs+"</font><br>");
  move_cursor(n);
  repaint();
}


/// insert a string to the output source
void MacrorCommandWindow::insertErrorText(const std::string& s)
{
  QString qs(s.c_str());
  textCursor().insertHtml("<font color=\"Red\">"+qs+"</font><br>");
  repaint();
}



void MacrorCommandWindow::showMessage(const std::string &m)
{
  message->setText(m.c_str());
  message->setBuddy(this);
  message->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  message->move(cursorRect().center().operator +=(QPoint(+10,-10)));
  message->show();
repaint();
}


