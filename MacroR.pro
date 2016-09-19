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
    Include/Markov_Plot/XY_PlotData.h \
    Include/Markov_GUI/qdebugstream.h \
    Include/Markov_GUI/DirComboBox.h

SOURCES -=Source/main_MacroConsole.cpp

SOURCES += \
    Source/main_MacroR.cpp \
  #  Source/Markov_Console/Markov_CommandManagerGui.cpp  \
    Source/Markov_GUI/MacrorMainWindow.cpp \
    Source/Markov_GUI/MacrorCommandWindow.cpp \
    Source/Markov_GUI/MacrorCommandHistory.cpp \
    Source/Markov_GUI/ABC_ObjectsWindow.cpp \
    Source/Markov_GUI/DirComboBox.cpp

RESOURCES     = MacroR.qrc


HEADERS = $$unique(HEADERS)

SOURCES =  $$unique(SOURCES)

#message($$CONFIG)
#message($$TEMPLATE)
#message($$QT)

message ("MacroR ends here")

}

HEADERS += \
    Include/Markov_GUI/MyInputDialog.h

SOURCES += \
    Source/Markov_GUI/MyInputDialog.cpp
