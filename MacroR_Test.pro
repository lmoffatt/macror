#-------------------------------------------------
#
# Project created by QtCreator 2010-10-22T10:21:34
#
#-------------------------------------------------
#  Include  the GUI interfase of MarkovLib

istest = 1


 !include( MacroR.pro ){
       message( "MacroR.pro not found" )
}
 !include( MacroRConsole_Test.pro ){
       message( "MacroRConsole_Test.pro not found" )
}

SOURCES += Source/main_MacroR_Test.cpp
SOURCES -=Source/main_MacroR.cpp
SOURCES -=Source/main_MacroConsole_Test.cpp


HEADERS = $$unique(HEADERS)


SOURCES =  $$unique(SOURCES)

DEFINES = $$unique(DEFINES)

TARGET = MacroR_Test

#message($$SOURCES)



