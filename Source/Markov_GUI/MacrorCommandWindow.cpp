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

namespace Markov_IO_New {




  MacrorCommandWindow::MacrorCommandWindow(MacrorMainWindow *parent ,
                                           Markov_CommandManagerVar *cm):
    QPlainTextEdit(parent),
    mw_(parent),
    cm_(cm),
    message()
  {
    cm_->setIO(this);

    //TODO: add them later
    //  cm_->add_command(new MacrorEditCommand(cm_));
    //  cm_->add_command(new MacrorExitCommand(cm_,mw_));
    //  cm_->add_command(new MacrorCreateCommand(cm_));
    //  cm_->add_command(new Markov_GUI::CdCommandGUI(cm_,mw_));
    unsigned windowWidth=35;
    put(cm_->getProgram().wellcomeMessage(windowWidth));

    freshLine();
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

  Markov_CommandManagerVar *MacrorCommandWindow::MarkovCommand()
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

  void MacrorCommandWindow::erase_from_cursor_forward(std::string s)
  {
    QString qs(s.c_str());
    QTextCursor c=textCursor();
    c.setPosition(c.position()+qs.size(),QTextCursor::KeepAnchor);
    c.removeSelectedText();
    setTextCursor(c);
    repaint();
  }
  void MacrorCommandWindow::erase_from_cursor_backward(std::string s)
  {
    QString qs(s.c_str());
    QTextCursor c=textCursor();
    c.setPosition(c.position()-qs.size(),QTextCursor::KeepAnchor);
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

  void MacrorCommandWindow::cleanToEndLine()
  {
    auto c=textCursor();
    c.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
    c.removeSelectedText();
    setTextCursor(c);
    repaint();
  }

  void MacrorCommandWindow::move_end()
  {
    moveCursor(QTextCursor::End);
  }

  bool MacrorCommandWindow::isLineBegin() const
  {
    auto pos= textCursor().positionInBlock();
    return pos==cm_->getProgram().spacer().size();

  }


  const Markov_CommandManagerVar*
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

    Key k=QKey2Key(e);
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
    if (s.find_first_not_of(" ")==s.npos)
      {
        textCursor().insertText(s.c_str());

      }
    else
      {
        QString qs(s.c_str());
        qs.replace('\n',"<br>");
        qs.prepend("<font color=\"Black\">").append("</font>");
        //std::size_t n=qs.size();
        textCursor().insertHtml(qs);
        //move_cursor(n);
      }
    repaint();
  }





  /// put a string to the output source
  void MacrorCommandWindow::putError(const std::string& s)
  {
    auto c=textCursor();
    QString qs(s.c_str());
    qs.replace('\n',"<br>");

    //std::size_t n=qs.size();
    textCursor().insertHtml("<font color=\"Red\">"+qs+"</font>");
    //move_cursor(n);
    setTextCursor(c);
    repaint();
  }



  void MacrorCommandWindow::showMessage(const std::string &m)
  {

    QString text(m.c_str());
    if (message==nullptr)
      message= new QLabel(this);
    message->setText(text);

    message->setBuddy(this);
    message->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    message->setStyleSheet("QLabel { background-color : black; color : white; }");
    message->move(cursorRect().topLeft().operator +=(QPoint(10,-10-message->height())));
    message->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    //message->setScaledContents(true);
    //message->setSizePolicy(Ignored);
    message->show();
    repaint();
  }

  std::string MacrorCommandWindow::spacer() const
  {
    return cm_->getProgram().spacer();
  }





  void MacrorCommandWindow::putNewLine()
  {
    auto c=textCursor();
    c.movePosition(QTextCursor::EndOfLine,QTextCursor::MoveAnchor);
    c.insertText("\n");
    setTextCursor(c);
    repaint();
  }

  void MacrorCommandWindow::freshLine()
  {
    putNewLine();
    put(cm_->getProgram().spacer().c_str());
    repaint();

  }

  bool MacrorCommandWindow::isLineEnd() const
  {
    return textCursor().atEnd();

  }

  std::string MacrorCommandWindow::currentLine() const
  {
    if (isLineBegin())
      return "";
    else
      {
        auto c=textCursor();
        c.movePosition(QTextCursor::StartOfBlock,QTextCursor::KeepAnchor);
        std::string lastBlock=c.selectedText().toStdString();
        if (lastBlock.substr(0,2)==cm_->getProgram().spacer())
          lastBlock.erase(0,2);
        return lastBlock;
      }
  }

  char MacrorCommandWindow::pop_next_char()
  {
    auto c= textCursor();
    c.movePosition(QTextCursor::Right,QTextCursor::KeepAnchor);
    auto s=c.selectedText();
    c.removeSelectedText();
    return s.toStdString()[0];

  }

  void MacrorCommandWindow::backErase()
  {
    if (!isLineEnd())
      {
        auto c=textCursor();
        c.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
        c.removeSelectedText();
        setTextCursor(c);
      }
    textCursor().deletePreviousChar();
    repaint();
  }

  void MacrorCommandWindow::putTail(const std::string &text)
  {
    if (!isLineEnd())
      {
        auto c=textCursor();
        c.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
        c.removeSelectedText();
        setTextCursor(c);
      }
    auto c2=textCursor();
    auto p=c2.position();
    c2.insertText(text.c_str());

    c2.setPosition(p);
    setTextCursor(c2);
    repaint();
  }

  std::string MacrorCommandWindow::getTail()
  {
    auto c=textCursor();
    c.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
    return c.selectedText().toStdString();
  }

}






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

  freshLine();
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

void MacrorCommandWindow::erase_from_cursor_forward(std::string s)
{
  QString qs(s.c_str());
  QTextCursor c=textCursor();
  c.setPosition(c.position()+qs.size(),QTextCursor::KeepAnchor);
  c.removeSelectedText();
  setTextCursor(c);
  repaint();
}
void MacrorCommandWindow::erase_from_cursor_backward(std::string s)
{
  QString qs(s.c_str());
  QTextCursor c=textCursor();
  c.setPosition(c.position()-qs.size(),QTextCursor::KeepAnchor);
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

void MacrorCommandWindow::cleanToEndLine()
{
  auto c=textCursor();
  c.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
  c.removeSelectedText();
  setTextCursor(c);
  repaint();
}

void MacrorCommandWindow::move_end()
{
  moveCursor(QTextCursor::End);
}

bool MacrorCommandWindow::isLineBegin() const
{
  auto pos= textCursor().positionInBlock();
  return pos==cm_->getProgram().spacer().size();

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
  if (s.find_first_not_of(" ")==s.npos)
    {
      textCursor().insertText(s.c_str());

    }
  else
    {
      QString qs(s.c_str());
      qs.replace('\n',"<br>");
      qs.prepend("<font color=\"Black\">").append("</font>");
      //std::size_t n=qs.size();
      textCursor().insertHtml(qs);
      //move_cursor(n);
    }
  repaint();
}





/// put a string to the output source
void MacrorCommandWindow::putError(const std::string& s)
{
  auto c=textCursor();
  QString qs(s.c_str());
  qs.replace('\n',"<br>");

  //std::size_t n=qs.size();
  textCursor().insertHtml("<font color=\"Red\">"+qs+"</font>");
  //move_cursor(n);
  setTextCursor(c);
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

std::string MacrorCommandWindow::spacer() const
{
  return cm_->getProgram().spacer();
}





void MacrorCommandWindow::putNewLine()
{
  auto c=textCursor();
  c.movePosition(QTextCursor::EndOfLine,QTextCursor::MoveAnchor);
  c.insertText("\n");
  setTextCursor(c);
  repaint();
}

void MacrorCommandWindow::freshLine()
{
  putNewLine();
  put(cm_->getProgram().spacer().c_str());
  repaint();

}

bool MacrorCommandWindow::isLineEnd() const
{
  return textCursor().atEnd();

}

std::string MacrorCommandWindow::currentLine() const
{
  if (isLineBegin())
    return "";
  else
    {
      auto c=textCursor();
      c.movePosition(QTextCursor::StartOfBlock,QTextCursor::KeepAnchor);
      std::string lastBlock=c.selectedText().toStdString();
      if (lastBlock.substr(0,2)==cm_->getProgram().spacer())
        lastBlock.erase(0,2);
      return lastBlock;
    }
}

char MacrorCommandWindow::pop_next_char()
{
  auto c= textCursor();
  c.movePosition(QTextCursor::Right,QTextCursor::KeepAnchor);
  auto s=c.selectedText();
  c.removeSelectedText();
  return s.toStdString()[0];

}

void MacrorCommandWindow::backErase()
{
  if (!isLineEnd())
    {
      auto c=textCursor();
      c.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
      c.removeSelectedText();
      setTextCursor(c);
    }
  textCursor().deletePreviousChar();
  repaint();
}

void MacrorCommandWindow::putTail(const std::string &text)
{
  if (!isLineEnd())
    {
      auto c=textCursor();
      c.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
      c.removeSelectedText();
      setTextCursor(c);
    }
  auto c2=textCursor();
  auto p=c2.position();
  c2.insertText(text.c_str());

  c2.setPosition(p);
  setTextCursor(c2);
  repaint();
}

std::string MacrorCommandWindow::getTail()
{
  auto c=textCursor();
  c.movePosition(QTextCursor::EndOfLine,QTextCursor::KeepAnchor);
  return c.selectedText().toStdString();
}

