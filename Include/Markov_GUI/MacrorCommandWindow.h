#ifndef MACRORCOMMANDWINDOW_H
#define MACRORCOMMANDWINDOW_H
#include <sstream>
#include <QPlainTextEdit>
#include <QStandardItem>

#include <Markov_Console/Markov_CommandManager.h>
#include "Markov_Console/ExpressionManager.h"

class QLabel;


class MacrorMainWindow;






/**

    MacrorCommandWindow is the class behind the command window

MacrorCommandWindow centralize the processing of all the command text inputs
entered into the command window.
It delegates console commands to Markov_Console::Markov_CommandManager and it implements
itsel all the GUI commands. Some native console commands are reimplemented here without
deriving Markov_CommandManager but by catching them before Markov_CommandManager do that.

*/


class MacrorCommandWindow: public QPlainTextEdit, public Markov_IO::ABC_IO,
    public Markov_Console::ExpressionView
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


  bool lastCommandResult()const;

  virtual QString getDir()const;

  virtual std::string getItemFromList(const std::string &title, const std::vector<std::string> &list, bool &ok, std::size_t current);

  virtual std::string
  getItemFromSeveralLists(const std::string& title,
                          const std::map<std::string,std::vector<std::string> >& list,
                          bool &ok,
                          std::size_t current);

  virtual void erase_from_cursor(int n);

  virtual void move_cursor(int n);

  virtual void cleanLastLine();

  virtual void move_end();

  virtual void move_home();
protected:



  Markov_Console::Markov_CommandManager* MarkovCommand();
  const Markov_Console::Markov_CommandManager* MarkovCommand()const;
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
  int cursorPosition;
  int previous_key;
  QString cmdLine;
  QString cmdWord;
  QString tail;
  QLabel* message;

  // Temporary interface
public:
  virtual bool isEmpty() const;
  virtual bool isValid() const;
  virtual bool isCompleted() const;
  virtual bool hasExecuted() const;
  virtual std::string currentError() const;

  // ExpressionView interface
public:
  virtual void update();

protected:
  virtual std::string chooseFromList(const std::vector<std::string> list) const;
};


#endif // MACRORCOMMANDWINDOW_H
