#ifndef MACRORMAINWINDOW_H
#define MACRORMAINWINDOW_H


#include <QObject>
#include <QMainWindow>
#include <QTextEdit>
#include <QList>

#include "Markov_GUI/MacrorCommandWindow.h"
#include "Markov_GUI/MacrorCommandHistory.h"
#include"Markov_GUI/ABC_ObjectsWindow.h"


#include "Markov_IO/Implements_ComplexVar_New.h"


#include <iostream>

class ToolBar;
class QMenu;
class QSignalMapper;
class QString;


namespace Markov_IO_New {





  template<typename...Args>
  class myTuple
  {
  public:
    myTuple(Args...a):t(a...){}


    template<std::size_t D>
    void print_imp1(){}

    template<std::size_t D, std::size_t I, std::size_t...Is>
    void print_imp1()
    {
      std::cerr<<std::get<I>(t)<<"  tuple"<<I<<" ";
      print_imp1<D, Is...>();
    }

      template<std::size_t...Is>
      void print_imp0(std::index_sequence<Is...>)
        {
           print_imp1<0,Is...>();
      }

      void print()
      {
         print_imp0(std::index_sequence_for<Args...>());
      }

      std::tuple<Args...>t;
  };



  class MacrorMainWindow : public QMainWindow
  {
      Q_OBJECT


  public:

      MacrorMainWindow(QWidget *parent = 0,
                       Markov_CommandManagerVar* cm=
          new Markov_CommandManagerVar());


      virtual ~MacrorMainWindow()
      {
        delete cm_;
      }

  signals:
      void DirHasChanged(QString newDir);


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


      void setCurrentFile(const QString& fileName) ;



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

      ABC_ObjectsWindow * modelsWindow;

      ABC_ObjectsWindow * patchsWindow;
      ABC_ObjectsWindow * experimentsWindow;


      Markov_CommandManagerVar* cm_;





  };




}







#endif // MACRORMAINWINDOW_H
