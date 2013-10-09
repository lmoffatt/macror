#ifndef MACRORMAINWINDOW_H
#define MACRORMAINWINDOW_H


#include <QObject>
#include <QMainWindow>
#include <QTextEdit>
#include <QList>

#include "Markov_GUI/MacrorCommandWindow.h"
#include "Markov_GUI/MacrorCommandHistory.h"
#include "Markov_GUI/MacrorModelsWindow.h"
#include "Markov_GUI/MacrorPatchsWindow.h"
#include "Markov_GUI/MacrorExperimentsWindow.h"

#include "Markov_Plot/GraphWindow.h"
#include "Markov_Plot/GraphView.h"





class ToolBar;
class QMenu;
class QSignalMapper;
class QString;

class MacrorMainWindow : public QMainWindow
{
    Q_OBJECT


public:

    MacrorMainWindow(QWidget *parent = 0,
                     Markov_Console::Markov_CommandManager* cm=
        new Markov_Console::Markov_CommandManager());

    void createGraph(Markov_Plot::GraphWindow *graph);


private slots:
    void open();
    void save();
    void saveAs();
    void exportAll();
    void exit();

    void copy();
    void edit();
    void paste();
    void about();

    void clear();

    void newExperiment();

    void newModel();

    void newOption();

    //void newOptions();


    void changeDir(QString newDir);

    void setCurrentFile(const QString& fileName);



private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockWindows();


    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *dataMenu;
    QMenu *modelMenu;
    QMenu *analyzeMenu;

    QMenu *windowMenu;
    QMenu *helpMenu;

    QToolBar *fileToolBar;
    QToolBar *dirToolBar;

    QToolBar *editToolBar;
    QToolBar *dataToolBar;
    QToolBar *modelToolBar;
    QToolBar *analyzeToolBar;



    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;

    QAction *exportAction;

    QAction *exitAction;

    QAction *editAction;

    QAction *copyAction;
    QAction *pasteAction;



    QAction *changeDirAction;
    QAction *whoAction;

    QAction *modelChannelAction;

    QAction *modelPatchAction;

    QAction *clearAction;

    QAction *simulateAction;

    QAction *likelihoodAction;

    QAction *optimizeAction;


    QAction *experimentAction;

    QAction *modelAction;

    QAction *optionAction;

    QAction *scriptAction;

    QString currentFile;






    QAction *printAction;

    QAction *aboutAction;
    QAction *quitAction;


    MacrorCommandWindow *commandWindow;

    MacrorCommandHistory *commandHistory;

    MacrorModelsWindow * modelsWindow;

    MacrorPatchsWindow * patchsWindow;
    MacrorExperimentsWindow * experimentsWindow;

    QList<Markov_Plot::GraphWindow*> graphWindows;






};



#endif // MACRORMAINWINDOW_H
