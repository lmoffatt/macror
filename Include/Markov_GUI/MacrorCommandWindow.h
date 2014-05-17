#ifndef MACRORCOMMANDWINDOW_H
#define MACRORCOMMANDWINDOW_H
#include <sstream>
#include <QPlainTextEdit>
#include <QStandardItem>

#include <Markov_Console/Markov_CommandManager.h>


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


class MacrorCommandWindow: public QPlainTextEdit, public Markov_IO::ABC_IO
{
    Q_OBJECT

public:
    MacrorCommandWindow(MacrorMainWindow *parent,
                         Markov_Console::Markov_CommandManager* cm=
            new Markov_Console::Markov_CommandManager());
    ~MacrorCommandWindow();


    /// get a string from the input source
    virtual std::string getline();

    /// put a string to the output source
    virtual void put(const std::string &s);

virtual void putError(const std::string &);


    bool lastCommandResult()const;

    virtual QString getDir()const;
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
    Markov_Console::Markov_CommandManager* cm_;
    int cursorPosition;
    int previous_key;
    QString cmdLine;
    QString cmdWord;
    QString tail;
    QLabel* message;


};


#endif // MACRORCOMMANDWINDOW_H
