#ifndef MACRORCOMMANDWINDOW_H
#define MACRORCOMMANDWINDOW_H
#include <sstream>
#include <QPlainTextEdit>
#include <QStandardItem>

#include <Markov_Console/Markov_CommandManager.h>
#include "Markov_Console/ExpressionManager.h"





class QLabel;

namespace Markov_IO_New {

class MacrorMainWindow;

inline Key QKey2Key(QKeyEvent * e)
{

Key k=static_cast<Key>(e->key());

if ((k>=Key_A)&&(k<=Key_Z))
  return static_cast<Key>(e->text().toStdString()[0]);
else
  return k;
}



/**

    MacrorCommandWindow is the class behind the command window

MacrorCommandWindow centralize the processing of all the command text inputs
entered into the command window.
It delegates console commands to Markov_Console::Markov_CommandManager and it implements
itsel all the GUI commands. Some native console commands are reimplemented here without
deriving Markov_CommandManager but by catching them before Markov_CommandManager do that.

*/


class MacrorCommandWindow: public QPlainTextEdit, public ABC_IO
{
  Q_OBJECT

public:
  MacrorCommandWindow(MacrorMainWindow *parent,
                      Markov_CommandManagerVar* cm=
      new Markov_CommandManagerVar());
  ~MacrorCommandWindow();



  /// put a string to the output source
  virtual void put(const std::string &s) override;

  virtual void putError(const std::string &) override;

  virtual void showMessage(const std::string &m) override;

  std::string spacer()const override;


  bool lastCommandResult()const;

  virtual QString getDir()const;

  virtual std::string getItemFromList(const std::string &title, const std::vector<std::string> &list, bool &ok, std::size_t current) override;

  virtual std::string
  getItemFromSeveralLists(const std::string& title,
                          const std::map<std::string,std::vector<std::string> >& list,
                          bool &ok,
                          std::size_t current) override;

  virtual void erase_from_cursor_forward(std::string s) override;
  virtual void erase_from_cursor_backward(std::string s) override;

  virtual void move_cursor(int n) override;

  virtual void cleanToEndLine() override;

  virtual void move_end() override;

  virtual void move_home()override{}

  virtual bool isLineBegin()const override;
protected:



  Markov_CommandManagerVar* MarkovCommand();
  const Markov_CommandManagerVar* MarkovCommand()const;
  virtual void	keyPressEvent ( QKeyEvent * e ) override;


public slots:
  virtual void commandLine(const QString& line);

  virtual void addCommandLine(const QString& line);

  virtual void next_instruction();




signals:
  void commandLineExecuted(const QString& line);
  void outputGenerated(const QString& output);



private:
  bool graphCommandLine(const QString& line);

  bool plot(const QString& line);

  bool modelChannel(const QString& line);

  bool modelPatch(const QString& line);

  bool edit(const QString& varname);

  MacrorMainWindow* mw_;
  Markov_CommandManagerVar* cm_;
  QLabel* message;



protected:
  virtual std::string chooseFromList(const std::vector<std::string> list) const{}

  // ABC_IO interface
public:
  virtual void putNewLine() override;
  virtual void freshLine() override;
  virtual bool isLineEnd() const override;
  virtual std::string currentLine() const override;
  virtual char pop_next_char() override;
  virtual void backErase() override;
  virtual void putTail(const std::string &text) override;
  virtual std::string getTail() override;
};


}



class MacrorMainWindow;

inline Markov_IO::Key QKeyToKey(QKeyEvent * e)
{

Markov_IO::Key k=static_cast<Markov_IO::Key>(e->key());

if ((k>=Markov_IO::Key_A)&&(k<=Markov_IO::Key_Z))
  return static_cast<Markov_IO::Key>(e->text().toStdString()[0]);
else
  return k;
}



/**

    MacrorCommandWindow is the class behind the command window

MacrorCommandWindow centralize the processing of all the command text inputs
entered into the command window.
It delegates console commands to Markov_Console::Markov_CommandManager and it implements
itsel all the GUI commands. Some native console commands are reimplemented here without
deriving Markov_CommandManager but by catching them before Markov_CommandManager do that.

*/


class MacrorCommandWindow: public QPlainTextEdit, public Markov_IO::ABC_IO
{
  Q_OBJECT

public:
  MacrorCommandWindow(MacrorMainWindow *parent,
                      Markov_Console::Markov_CommandManagerVar* cm=
      new Markov_Console::Markov_CommandManagerVar());
  ~MacrorCommandWindow();



  /// put a string to the output source
  virtual void put(const std::string &s) ;

  virtual void putError(const std::string &);

  virtual void showMessage(const std::string &m);

  std::string spacer()const override;


  bool lastCommandResult()const;

  virtual QString getDir()const;

  virtual std::string getItemFromList(const std::string &title, const std::vector<std::string> &list, bool &ok, std::size_t current);

  virtual std::string
  getItemFromSeveralLists(const std::string& title,
                          const std::map<std::string,std::vector<std::string> >& list,
                          bool &ok,
                          std::size_t current);

  virtual void erase_from_cursor_forward(std::string s) override;
  virtual void erase_from_cursor_backward(std::string s) override;

  virtual void move_cursor(int n) override;

  virtual void cleanToEndLine() override;

  virtual void move_end() override;

  virtual void move_home()override{}

  virtual bool isLineBegin()const override;
protected:



  Markov_Console::Markov_CommandManagerVar* MarkovCommand();
  const Markov_Console::Markov_CommandManagerVar* MarkovCommand()const;
  virtual void	keyPressEvent ( QKeyEvent * e );


public slots:
  virtual void commandLine(const QString& line);

  virtual void addCommandLine(const QString& line);

  virtual void next_instruction();




signals:
  void commandLineExecuted(const QString& line);
  void outputGenerated(const QString& output);



private:
  bool graphCommandLine(const QString& line);

  bool plot(const QString& line);

  bool modelChannel(const QString& line);

  bool modelPatch(const QString& line);

  bool edit(const QString& varname);

  MacrorMainWindow* mw_;
  Markov_Console::Markov_CommandManagerVar* cm_;
  QLabel* message;



protected:
  virtual std::string chooseFromList(const std::vector<std::string> list) const{}

  // ABC_IO interface
public:
  virtual void putNewLine() override;
  virtual void freshLine() override;
  virtual bool isLineEnd() const override;
  virtual std::string currentLine() const override;
  virtual char pop_next_char() override;
  virtual void backErase() override;
  virtual void putTail(const std::string &text) override;
  virtual std::string getTail() override;
};






#endif // MACRORCOMMANDWINDOW_H
