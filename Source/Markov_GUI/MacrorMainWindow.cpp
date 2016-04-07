
//#include <QAction>
#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QDockWidget>
#include <QBoxLayout>
#include <QFileDialog>
#include <QToolBar>
#include <QStatusBar>
#include<QInputDialog>

#include "Markov_GUI/MacrorMainWindow.h"
#include "Markov_GUI/DirComboBox.h"
#include "Markov_Plot/PlotCommand.h"


namespace Markov_IO_New {



MacrorMainWindow::MacrorMainWindow(QWidget *parent,
                                   Markov_CommandManagerVar* cm):
    QMainWindow(parent),
    commandWindow(new MacrorCommandWindow(this,cm)),
    commandHistory(new MacrorCommandHistory(cm,parent)),
    modelsWindow(new ABC_ObjectsWindow(cm,Markov_Mol::ABC_Markov_Model::ClassName(),parent)),
    patchsWindow(new ABC_ObjectsWindow(cm,Markov_Mol::ABC_PatchModel::ClassName(),parent)),
    experimentsWindow(new ABC_ObjectsWindow(cm,Markov_IO::ABC_Experiment::ClassName(),parent)),
    //graphWindows(),
    cm_(cm)
{
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createDockWindows();

    setWindowTitle(tr("Macro-R"));
  // include plot later
    //  Markov_Console::ABC_Command* plcmd=new Markov_Plot::PlotCommand(cm,this);
 //   cm->add_command(plcmd);

}





void MacrorMainWindow::setCurrentFile(const QString& fileName)
{
    currentFile=fileName;
    this->setWindowModified(false);
    this->setWindowTitle(QFileInfo(currentFile).fileName()+"[*]   "+"MacroR");
   }



void MacrorMainWindow::open()
{
    QString file = QFileDialog::getOpenFileName(this);
    setCurrentFile(file);

    if (!file.isEmpty())
    {
        commandWindow->addCommandLine(QString("load \"").append(file).append("\""));
    }
    if (commandWindow->lastCommandResult())
        setCurrentFile(file);
}

void MacrorMainWindow::save()
{
   commandWindow->addCommandLine(QString("save \"").append(currentFile).append("\""));
}

void MacrorMainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    commandWindow->addCommandLine(QString("save \"").append(fileName).append("\""));
    if (commandWindow->lastCommandResult())
        setCurrentFile(fileName);

}

void MacrorMainWindow::exportAll()
{
    QString dirname=QFileDialog::getExistingDirectory(this);
    commandWindow->addCommandLine(QString("export \"").append(dirname).append("\""));
}

void MacrorMainWindow::exit()
{
    commandWindow->addCommandLine(QString("exit"));
}



void MacrorMainWindow::edit()
{

}

void MacrorMainWindow::paste()
{

}

void MacrorMainWindow::copy()
{

}

void MacrorMainWindow::about()
{

}

void MacrorMainWindow::newExperiment()
{
    bool ok;
    QString alias = QInputDialog::getText(this, tr("Create a new Experiment"),
                                         tr("alias:"), QLineEdit::Normal,
                                          "myExperiment", &ok);
    if (ok)
    {
        if (alias.isEmpty())
            alias="myExperiment";
       commandWindow->addCommandLine(QString("create Experiment ").append(alias));
    }

}


void MacrorMainWindow::newModel()
{
    bool ok;
    QString alias = QInputDialog::getText(this, tr("Create a new Model"),
                                         tr("alias:"), QLineEdit::Normal,
                                          "myModel", &ok);

    if (ok)
    {
        if (alias.isEmpty())
            alias="myModel";

           commandWindow->addCommandLine(QString("create Model ").append(alias));
    }

}


void MacrorMainWindow::newOption()
{
    bool ok;
    QString alias = QInputDialog::getText(this, tr("Create a new Option"),
                                         tr("alias:"), QLineEdit::Normal,
                                          "myOption", &ok);

    if (ok)
    {
        if (alias.isEmpty())
            alias="myOption";

           commandWindow->addCommandLine(QString("create Options ").append(alias));
    }

}




void MacrorMainWindow::changeDir(QString newDir)
{
  commandWindow->addCommandLine(QString("cd \"").append(newDir).append("\""));
}



void MacrorMainWindow::clear()
{
    commandWindow->addCommandLine(QString("clear all"));

}

void MacrorMainWindow::createActions()
{
    openAction = new QAction(style()->standardIcon(QStyle::SP_DirOpenIcon),
                             tr("&Open File"),
                               this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Opens an existing file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));


    saveAction = new QAction(style()->standardIcon(QStyle::SP_DialogSaveButton),
                             tr("&Saves Everything"),
                               this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Saves all the variables in current file"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));


    saveAsAction = new QAction(style()->standardIcon(QStyle::SP_FileIcon),
                             tr("&Saves As"),
                               this);
    saveAsAction->setShortcuts(QKeySequence::Save);
    saveAsAction->setStatusTip(tr("Saves all the variables in a different file"));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));


    exportAction = new QAction(style()->standardIcon(QStyle::SP_DirLinkIcon),
                             tr("&Export all"),
                               this);
   // exportAction->setShortcuts(QKeySequence::Save);
    exportAction->setStatusTip(tr("Saves each variables in a different file"));
    connect(exportAction, SIGNAL(triggered()), this, SLOT(exportAll()));


    exitAction = new QAction (tr("E&xit"),
                               this);
     exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quits the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(exit()));

    editAction = new QAction (style()->standardIcon(QStyle::SP_DirLinkIcon),
                              tr("E&dit"),
                               this);
     editAction->setShortcut(QKeySequence(Qt::Key_F2));
    editAction->setStatusTip(tr("Edits the selected object"));
    connect(editAction, SIGNAL(triggered()), this, SLOT(edit()));




    copyAction = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
    copyAction->setShortcuts(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAction = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
    pasteAction->setShortcuts(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the application's About box"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));


    editAction = new QAction (style()->standardIcon(QStyle::SP_DirLinkIcon),
                              tr("E&dit"),
                               this);
     editAction->setShortcut(QKeySequence(Qt::Key_F2));
    editAction->setStatusTip(tr("Edits the selected object"));
    connect(editAction, SIGNAL(triggered()), this, SLOT(edit()));

    clearAction = new QAction (style()->standardIcon(QStyle::SP_DialogCancelButton),
                              tr("C&lear all"),
                               this);
    // clearAction->setShortcut(QKeySequence(Qt::Key_F2));
    clearAction->setStatusTip(tr("Removes all the variables"));
    connect(clearAction, SIGNAL(triggered()), this, SLOT(clear()));


    experimentAction = new QAction(tr("Create &Experiment"), this);
    experimentAction->setShortcut(QKeySequence(tr("Ctrl+E")));
    experimentAction->setStatusTip(tr("Creates a new experiment"));
    connect(experimentAction, SIGNAL(triggered()), this, SLOT(newExperiment()));


    modelAction = new QAction(tr("Create &Model"), this);
    modelAction->setShortcut(QKeySequence(tr("Ctrl+M")));
    modelAction->setStatusTip(tr("Creates a new model"));
    connect(modelAction, SIGNAL(triggered()), this, SLOT(newModel()));

    optionAction = new QAction(tr("Create &Option"), this);
    optionAction->setShortcut(QKeySequence(tr("Ctrl+M")));
    optionAction->setStatusTip(tr("Creates a new option"));
    connect(optionAction, SIGNAL(triggered()), this, SLOT(newOption()));


    //    QAction *modelChannelAction;

    //    QAction *modelPatchAction;

    //    QAction *experimentAction;

    //    QAction *optionAction;




//    QAction *whoAction;

//    QAction *clearAction;

//    QAction *simulateAction;

//    QAction *likelihoodAction;

//    QAction *optimizeAction;


//    QAction *scriptAction;





//    QAction *printAction;

//    QAction *aboutAction;
//    QAction *quitAction;


 }

void MacrorMainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(exportAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    //    fileMenu->addAction(printAct);
//    fileMenu->addSeparator();
//    fileMenu->addAction(quitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(editAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addSeparator();
    editMenu->addAction(clearAction);

    dataMenu = menuBar()->addMenu(tr("&Data"));
    dataMenu->addAction(experimentAction);
    dataMenu->addAction(modelAction);
    dataMenu->addAction(optionAction);




    viewMenu = menuBar()->addMenu(tr("&View"));

//    menuBar()->addSeparator();

//    helpMenu = menuBar()->addMenu(tr("&Help"));
//    helpMenu->addAction(aboutAct);
//    helpMenu->addAction(aboutQtAct);
}

void MacrorMainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);
    fileToolBar->addAction(saveAsAction);
    fileToolBar->addAction(exportAction);

    dirToolBar=addToolBar(tr("working dir"));
    addToolBarBreak();
    DirComboBox* dirBox=new DirComboBox(this->commandWindow->getDir(),tr("cd"),this);


     dirToolBar->addWidget(dirBox);
     connect(dirBox,SIGNAL(changeDirectory(QString)),this,SLOT(changeDir(QString)));

     connect(this,SIGNAL(DirHasChanged(QString)),dirBox,SLOT(setDirectory(QString)));

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(editAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addSeparator();
    editToolBar->addAction(clearAction);

    dataToolBar = addToolBar(tr("Data"));
    dataToolBar->addAction(experimentAction);
    dataToolBar->addAction(modelAction);
    dataToolBar->addAction(optionAction);


}

//! [8]
void MacrorMainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}
//! [8]

//! [9]
//void MainWindow::createDockWindows()
//{
////    QDockWidget *dock = new QDockWidget(tr("Customers"), this);
////    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
////    customerList = new QListWidget(dock);
////    customerList->addItems(QStringList()
////            << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
////            << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
////            << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
////            << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
////            << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
////            << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
////    dock->setWidget(customerList);
////    addDockWidget(Qt::RightDockWidgetArea, dock);
////    viewMenu->addAction(dock->toggleViewAction());

////    dock = new QDockWidget(tr("Paragraphs"), this);
////    paragraphsList = new QListWidget(dock);
////    paragraphsList->addItems(QStringList()
////            << "Thank you for your payment which we have received today."
////            << "Your order has been dispatched and should be with you "
////               "within 28 days."
////            << "We have dispatched those items that were in stock. The "
////               "rest of your order will be dispatched once all the "
////               "remaining items have arrived at our warehouse. No "
////               "additional shipping charges will be made."
////            << "You made a small overpayment (less than $5) which we "
////               "will keep on account for you, or return at your request."
////            << "You made a small underpayment (less than $1), but we have "
////               "sent your order anyway. We'll add this underpayment to "
////               "your next bill."
////            << "Unfortunately you did not send enough money. Please remit "
////               "an additional $. Your order will be dispatched as soon as "
////               "the complete amount has been received."
////            << "You made an overpayment (more than $5). Do you wish to "
////               "buy more items, or should we return the excess to you?");
////    dock->setWidget(paragraphsList);
////    addDockWidget(Qt::RightDockWidgetArea, dock);
////    viewMenu->addAction(dock->toggleViewAction());

////    connect(customerList, SIGNAL(currentTextChanged(QString)),
////            this, SLOT(insertCustomer(QString)));
////    connect(paragraphsList, SIGNAL(currentTextChanged(QString)),
////            this, SLOT(addParagraph(QString)));
//}
////! [9]



void MacrorMainWindow::createDockWindows(){
    QDockWidget *dock = new QDockWidget(tr("Command"), this);
    dock->setWidget(commandWindow);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());


    dock = new QDockWidget(tr("History"), this);
    dock->setWidget(commandHistory);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    connect(commandWindow,SIGNAL(commandLineExecuted(QString)),
            commandHistory,SLOT(addCommand(QString)));

    dock = new QDockWidget(tr("Models"), this);
    dock->setWidget(modelsWindow);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    connect(commandWindow,SIGNAL(commandLineExecuted(QString)),
            modelsWindow,SLOT(actualize()));




    dock = new QDockWidget(tr("Patchs"), this);
    dock->setWidget(patchsWindow);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    connect(commandWindow,SIGNAL(commandLineExecuted(QString)),
            patchsWindow,SLOT(actualize()));


    dock = new QDockWidget(tr("Experiments"), this);
    dock->setWidget(experimentsWindow);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    connect(commandWindow,SIGNAL(commandLineExecuted(QString)),
            experimentsWindow,SLOT(actualize()),Qt::DirectConnection);



}


void MacrorMainWindow::createGraph(Markov_Plot::GraphicPage* graph)
{
  //  graph->show();
    if (0)
    {
    QDockWidget *dock = new QDockWidget(tr("Plot"), this);
    dock->setWidget(graph);


    addDockWidget(Qt::RightDockWidgetArea, dock);
    graphWindows.push_back(graph);

    }
    else
   {
        graph->show();
        graph->resize(600,600);

        graphWindows.push_back(graph);

    }

}


}




MacrorMainWindow::MacrorMainWindow(QWidget *parent,
                                   Markov_Console::Markov_CommandManagerVar* cm):
    QMainWindow(parent),
    commandWindow(new MacrorCommandWindow(this,cm)),
    commandHistory(new MacrorCommandHistory(cm,parent)),
    modelsWindow(new ABC_ObjectsWindow(cm,Markov_Mol::ABC_Markov_Model::ClassName(),parent)),
    patchsWindow(new ABC_ObjectsWindow(cm,Markov_Mol::ABC_PatchModel::ClassName(),parent)),
    experimentsWindow(new ABC_ObjectsWindow(cm,Markov_IO::ABC_Experiment::ClassName(),parent)),
    //graphWindows(),
    cm_(cm)
{
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createDockWindows();

    setWindowTitle(tr("Macro-R"));
  // include plot later
    //  Markov_Console::ABC_Command* plcmd=new Markov_Plot::PlotCommand(cm,this);
 //   cm->add_command(plcmd);

}





void MacrorMainWindow::setCurrentFile(const QString& fileName)
{
    currentFile=fileName;
    this->setWindowModified(false);
    this->setWindowTitle(QFileInfo(currentFile).fileName()+"[*]   "+"MacroR");
   }



void MacrorMainWindow::open()
{
    QString file = QFileDialog::getOpenFileName(this);
    setCurrentFile(file);

    if (!file.isEmpty())
    {
        commandWindow->addCommandLine(QString("load \"").append(file).append("\""));
    }
    if (commandWindow->lastCommandResult())
        setCurrentFile(file);
}

void MacrorMainWindow::save()
{
   commandWindow->addCommandLine(QString("save \"").append(currentFile).append("\""));
}

void MacrorMainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    commandWindow->addCommandLine(QString("save \"").append(fileName).append("\""));
    if (commandWindow->lastCommandResult())
        setCurrentFile(fileName);

}

void MacrorMainWindow::exportAll()
{
    QString dirname=QFileDialog::getExistingDirectory(this);
    commandWindow->addCommandLine(QString("export \"").append(dirname).append("\""));
}

void MacrorMainWindow::exit()
{
    commandWindow->addCommandLine(QString("exit"));
}



void MacrorMainWindow::edit()
{

}

void MacrorMainWindow::paste()
{

}

void MacrorMainWindow::copy()
{

}

void MacrorMainWindow::about()
{

}

void MacrorMainWindow::newExperiment()
{
    bool ok;
    QString alias = QInputDialog::getText(this, tr("Create a new Experiment"),
                                         tr("alias:"), QLineEdit::Normal,
                                          "myExperiment", &ok);
    if (ok)
    {
        if (alias.isEmpty())
            alias="myExperiment";
       commandWindow->addCommandLine(QString("create Experiment ").append(alias));
    }

}


void MacrorMainWindow::newModel()
{
    bool ok;
    QString alias = QInputDialog::getText(this, tr("Create a new Model"),
                                         tr("alias:"), QLineEdit::Normal,
                                          "myModel", &ok);

    if (ok)
    {
        if (alias.isEmpty())
            alias="myModel";

           commandWindow->addCommandLine(QString("create Model ").append(alias));
    }

}


void MacrorMainWindow::newOption()
{
    bool ok;
    QString alias = QInputDialog::getText(this, tr("Create a new Option"),
                                         tr("alias:"), QLineEdit::Normal,
                                          "myOption", &ok);

    if (ok)
    {
        if (alias.isEmpty())
            alias="myOption";

           commandWindow->addCommandLine(QString("create Options ").append(alias));
    }

}




void MacrorMainWindow::changeDir(QString newDir)
{
  commandWindow->addCommandLine(QString("cd \"").append(newDir).append("\""));
}



void MacrorMainWindow::clear()
{
    commandWindow->addCommandLine(QString("clear all"));

}

void MacrorMainWindow::createActions()
{
    openAction = new QAction(style()->standardIcon(QStyle::SP_DirOpenIcon),
                             tr("&Open File"),
                               this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Opens an existing file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));


    saveAction = new QAction(style()->standardIcon(QStyle::SP_DialogSaveButton),
                             tr("&Saves Everything"),
                               this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Saves all the variables in current file"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));


    saveAsAction = new QAction(style()->standardIcon(QStyle::SP_FileIcon),
                             tr("&Saves As"),
                               this);
    saveAsAction->setShortcuts(QKeySequence::Save);
    saveAsAction->setStatusTip(tr("Saves all the variables in a different file"));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));


    exportAction = new QAction(style()->standardIcon(QStyle::SP_DirLinkIcon),
                             tr("&Export all"),
                               this);
   // exportAction->setShortcuts(QKeySequence::Save);
    exportAction->setStatusTip(tr("Saves each variables in a different file"));
    connect(exportAction, SIGNAL(triggered()), this, SLOT(exportAll()));


    exitAction = new QAction (tr("E&xit"),
                               this);
     exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quits the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(exit()));

    editAction = new QAction (style()->standardIcon(QStyle::SP_DirLinkIcon),
                              tr("E&dit"),
                               this);
     editAction->setShortcut(QKeySequence(Qt::Key_F2));
    editAction->setStatusTip(tr("Edits the selected object"));
    connect(editAction, SIGNAL(triggered()), this, SLOT(edit()));




    copyAction = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
    copyAction->setShortcuts(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAction = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
    pasteAction->setShortcuts(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the application's About box"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));


    editAction = new QAction (style()->standardIcon(QStyle::SP_DirLinkIcon),
                              tr("E&dit"),
                               this);
     editAction->setShortcut(QKeySequence(Qt::Key_F2));
    editAction->setStatusTip(tr("Edits the selected object"));
    connect(editAction, SIGNAL(triggered()), this, SLOT(edit()));

    clearAction = new QAction (style()->standardIcon(QStyle::SP_DialogCancelButton),
                              tr("C&lear all"),
                               this);
    // clearAction->setShortcut(QKeySequence(Qt::Key_F2));
    clearAction->setStatusTip(tr("Removes all the variables"));
    connect(clearAction, SIGNAL(triggered()), this, SLOT(clear()));


    experimentAction = new QAction(tr("Create &Experiment"), this);
    experimentAction->setShortcut(QKeySequence(tr("Ctrl+E")));
    experimentAction->setStatusTip(tr("Creates a new experiment"));
    connect(experimentAction, SIGNAL(triggered()), this, SLOT(newExperiment()));


    modelAction = new QAction(tr("Create &Model"), this);
    modelAction->setShortcut(QKeySequence(tr("Ctrl+M")));
    modelAction->setStatusTip(tr("Creates a new model"));
    connect(modelAction, SIGNAL(triggered()), this, SLOT(newModel()));

    optionAction = new QAction(tr("Create &Option"), this);
    optionAction->setShortcut(QKeySequence(tr("Ctrl+M")));
    optionAction->setStatusTip(tr("Creates a new option"));
    connect(optionAction, SIGNAL(triggered()), this, SLOT(newOption()));


    //    QAction *modelChannelAction;

    //    QAction *modelPatchAction;

    //    QAction *experimentAction;

    //    QAction *optionAction;




//    QAction *whoAction;

//    QAction *clearAction;

//    QAction *simulateAction;

//    QAction *likelihoodAction;

//    QAction *optimizeAction;


//    QAction *scriptAction;





//    QAction *printAction;

//    QAction *aboutAction;
//    QAction *quitAction;


 }

void MacrorMainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(exportAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    //    fileMenu->addAction(printAct);
//    fileMenu->addSeparator();
//    fileMenu->addAction(quitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(editAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addSeparator();
    editMenu->addAction(clearAction);

    dataMenu = menuBar()->addMenu(tr("&Data"));
    dataMenu->addAction(experimentAction);
    dataMenu->addAction(modelAction);
    dataMenu->addAction(optionAction);




    viewMenu = menuBar()->addMenu(tr("&View"));

//    menuBar()->addSeparator();

//    helpMenu = menuBar()->addMenu(tr("&Help"));
//    helpMenu->addAction(aboutAct);
//    helpMenu->addAction(aboutQtAct);
}

void MacrorMainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);
    fileToolBar->addAction(saveAsAction);
    fileToolBar->addAction(exportAction);

    dirToolBar=addToolBar(tr("working dir"));
    addToolBarBreak();
    DirComboBox* dirBox=new DirComboBox(this->commandWindow->getDir(),tr("cd"),this);


     dirToolBar->addWidget(dirBox);
     connect(dirBox,SIGNAL(changeDirectory(QString)),this,SLOT(changeDir(QString)));

     connect(this,SIGNAL(DirHasChanged(QString)),dirBox,SLOT(setDirectory(QString)));

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(editAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addSeparator();
    editToolBar->addAction(clearAction);

    dataToolBar = addToolBar(tr("Data"));
    dataToolBar->addAction(experimentAction);
    dataToolBar->addAction(modelAction);
    dataToolBar->addAction(optionAction);


}

//! [8]
void MacrorMainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}
//! [8]

//! [9]
//void MainWindow::createDockWindows()
//{
////    QDockWidget *dock = new QDockWidget(tr("Customers"), this);
////    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
////    customerList = new QListWidget(dock);
////    customerList->addItems(QStringList()
////            << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
////            << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
////            << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
////            << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
////            << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
////            << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
////    dock->setWidget(customerList);
////    addDockWidget(Qt::RightDockWidgetArea, dock);
////    viewMenu->addAction(dock->toggleViewAction());

////    dock = new QDockWidget(tr("Paragraphs"), this);
////    paragraphsList = new QListWidget(dock);
////    paragraphsList->addItems(QStringList()
////            << "Thank you for your payment which we have received today."
////            << "Your order has been dispatched and should be with you "
////               "within 28 days."
////            << "We have dispatched those items that were in stock. The "
////               "rest of your order will be dispatched once all the "
////               "remaining items have arrived at our warehouse. No "
////               "additional shipping charges will be made."
////            << "You made a small overpayment (less than $5) which we "
////               "will keep on account for you, or return at your request."
////            << "You made a small underpayment (less than $1), but we have "
////               "sent your order anyway. We'll add this underpayment to "
////               "your next bill."
////            << "Unfortunately you did not send enough money. Please remit "
////               "an additional $. Your order will be dispatched as soon as "
////               "the complete amount has been received."
////            << "You made an overpayment (more than $5). Do you wish to "
////               "buy more items, or should we return the excess to you?");
////    dock->setWidget(paragraphsList);
////    addDockWidget(Qt::RightDockWidgetArea, dock);
////    viewMenu->addAction(dock->toggleViewAction());

////    connect(customerList, SIGNAL(currentTextChanged(QString)),
////            this, SLOT(insertCustomer(QString)));
////    connect(paragraphsList, SIGNAL(currentTextChanged(QString)),
////            this, SLOT(addParagraph(QString)));
//}
////! [9]



void MacrorMainWindow::createDockWindows(){
    QDockWidget *dock = new QDockWidget(tr("Command"), this);
    dock->setWidget(commandWindow);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());


    dock = new QDockWidget(tr("History"), this);
    dock->setWidget(commandHistory);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    connect(commandWindow,SIGNAL(commandLineExecuted(QString)),
            commandHistory,SLOT(addCommand(QString)));

    dock = new QDockWidget(tr("Models"), this);
    dock->setWidget(modelsWindow);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    connect(commandWindow,SIGNAL(commandLineExecuted(QString)),
            modelsWindow,SLOT(actualize()));




    dock = new QDockWidget(tr("Patchs"), this);
    dock->setWidget(patchsWindow);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    connect(commandWindow,SIGNAL(commandLineExecuted(QString)),
            patchsWindow,SLOT(actualize()));


    dock = new QDockWidget(tr("Experiments"), this);
    dock->setWidget(experimentsWindow);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    connect(commandWindow,SIGNAL(commandLineExecuted(QString)),
            experimentsWindow,SLOT(actualize()),Qt::DirectConnection);



}


void MacrorMainWindow::createGraph(Markov_Plot::GraphicPage* graph)
{
  //  graph->show();
    if (0)
    {
    QDockWidget *dock = new QDockWidget(tr("Plot"), this);
    dock->setWidget(graph);


    addDockWidget(Qt::RightDockWidgetArea, dock);
    graphWindows.push_back(graph);

    }
    else
   {
        graph->show();
        graph->resize(600,600);

        graphWindows.push_back(graph);

    }

}





