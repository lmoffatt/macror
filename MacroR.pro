#-------------------------------------------------
#
# Project created by QtCreator 2010-10-22T10:21:34
#
#-------------------------------------------------
#  Include  the GUI interfase of MarkovLib

#message(ENTER MACROR CONFIG ES $$CONFIG)

!macroR{
CONFIG+=macroR
message(MacroR.pro here)
 !include( MacroRConsole.pro ){
       message( "MacroRConsole.pro not found" )
}

DEFINES+=MACRO_GUI

QT+= core gui
QT += widgets

CONFIG -= console
CONFIG +=qt


TARGET = MacroR

TEMPLATE = app

HEADERS += \
    Include/Markov_Remote/Markov_Remote.h \
    Include/Markov_Plot/ABC_PlotData.h \
    Include/Markov_GUI/MacrorMainWindow.h \
    Include/Markov_GUI/MacrorCommandWindow.h \
    Include/Markov_GUI/MacrorCommandHistory.h \
    Include/Markov_GUI/ABC_ObjectsWindow.h \
    Include/Markov_Plot/GraphWindow.h \
    Include/Markov_Plot/Scale.h \
    Include/Markov_Plot/XY_PlotData.h \
    Include/Markov_Plot/XY_Plot.h \
    Include/Markov_GUI/qdebugstream.h \
    Include/Markov_GUI/MacrorEditWindow.h \
    Include/Markov_GUI/EditWidgetMatrixDoubles.h \
    Include/Markov_GUI/EditWidgetField.h \
    Include/Markov_GUI/CreateQModelWizard.h \
    Include/Markov_GUI/MacrorCreateCommand.h \
    Include/Markov_GUI/MacrorExitWindow.h \
    Include/Markov_GUI/DirComboBox.h \
    Include/Markov_GUI/CreateWizard.h \
    Include/Markov_GUI/ModelMatrix.h \
    Include/Markov_GUI/EditWizardField.h \
    Include/Markov_GUI/CreateWizardPage.h \
    Include/Markov_Plot/GraphView.h \
    Include/Markov_GUI/CreateWizardField.h

SOURCES -=Source/main_MacroConsole.cpp

SOURCES += \
    Source/main_MacroR.cpp \
  #  Source/Markov_Console/Markov_CommandManagerGui.cpp  \
    Source/Markov_GUI/ABC_Var_GUI.cpp\
    Source/Markov_GUI/MacrorMainWindow.cpp \
    Source/Markov_GUI/MacrorCommandWindow.cpp \
    Source/Markov_GUI/MacrorCommandHistory.cpp \
    Source/Markov_GUI/ABC_ObjectsWindow.cpp \
    Source/Markov_Plot/GraphWindow.cpp \
    Source/Markov_Plot/Scale.cpp \
    Source/Markov_Plot/XY_PlotData.cpp \
    Source/Markov_Plot/XY_Plot.cpp \
    Source/Markov_GUI/MacrorEditWindow.cpp \
    Source/Markov_GUI/EditWidgetMatrixDoubles.cpp \
    Source/Markov_GUI/EditWidgetField.cpp \
    Source/Markov_GUI/CreateQModelWizard.cpp \
    Source/Markov_GUI/MacrorCreateCommand.cpp \
    Source/Markov_GUI/MacrorExitWindow.cpp \
    Source/Markov_GUI/EditWizardField.cpp\
    Source/Markov_GUI/DirComboBox.cpp \
    Source/Markov_GUI/CreateWizard.cpp \
    Source/Markov_GUI/ModelMatrix.cpp \
    Source/Markov_GUI/CreateWizardPage.cpp \
    Source/Markov_Plot/GraphView.cpp

RESOURCES     = MacroR.qrc


HEADERS = $$unique(HEADERS)

SOURCES =  $$unique(SOURCES)

#message($$CONFIG)
#message($$TEMPLATE)
#message($$QT)

message ("MacroR ends here")

}

HEADERS += \
    Include/Markov_Plot/PlotCommand.h \
    Include/Markov_GUI/CdCommandGUI.h \
    Include/Markov_GUI/MyInputDialog.h \
    Include/Markov_GUI/ABC_Var_GUI.h \
    Include/Markov_Plot/GraphicPage.h

SOURCES += \
    Source/Markov_Plot/PlotCommand.cpp \
    Source/Markov_GUI/CdCommandGUI.cpp \
    Source/Markov_GUI/MyInputDialog.cpp \
    Source/Markov_Plot/GraphicPage.cpp
