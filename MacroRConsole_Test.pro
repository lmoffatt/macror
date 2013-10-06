#-------------------------------------------------
#
# Project created by QtCreator 2010-10-22T10:21:34
#
#-------------------------------------------------
# No GUI, only Console with their TESTS, no dependency on Qt, nor on
# other graphic libraries (i.e, no Markov_Plot)


#message(ENTER MACROCONSOLETEST CONFIG ES $$CONFIG)

!macroRConsole_Test{

CONFIG +=macroRConsole_Test

message (" macroRConsole_Test here")

!include( MacroRConsole.pro ) {
     message( "MacroRConsole.pro not found" )
}

DEFINES+=MACRO_TEST

TARGET = MacroConsole_Test

HEADERS += \
    Include/Tests/timeOfFunctor.h \
    Include/Tests/RelationalProperties_test.h \
    Include/Tests/RegularType_Test.h \
    Include/Tests/RegularFunction_Test.h \
    Include/Tests/PredicateProperties_Test.h \
    Include/Tests/Ordering_Test.h \
    Include/Tests/OperatorProperties_Test.h \
    Include/Tests/getTimeMs64.h \
    Include/Tests/BiOperatorProperties_Test.h \
    Include/Tests/BasicAlgebraProperties_Test.h \
    Include/Tests/Assigment_Test.h \
    Include/Tests/AssertVerbose.h \
    Include/Tests/AssertPlain.h \
    Include/Tests/Markov_LA/ToleranceComparison_Test.h \
    Include/Tests/Markov_LA/Matrix_Test_times.h \
    Include/Tests/Markov_LA/Matrix_Test.h \
    Include/Tests/Markov_LA/Markov_LA_Tests.h \
    Include/Tests/Markov_Mol/MarkovTransitionRate_Test.h \
    Include/Tests/Markov_Mol/Markov_Mol_Tests.h \
    Include/Tests/ABC_Test.h \
    Include/Tests/ElementaryTest.h \
    Include/Tests/MultipleTests.h\
    Include/Markov_Console/Markov_CommandManagerTest.h \
    Include/Tests/Markov_IO/ABC_Parametrizable_Test.h \
    Include/Tests/Markov_IO/ABC_Put_Test.h \
    Include/Tests/Markov_IO/ClassDescription_Test.h \
    Include/Tests/Markov_Mol/QMarkovModel_Test.h \
    Include/Tests/Markov_Mol/ABC_Markov_Model_Test.h \
    Include/Tests/Markov_Mol/MarkovTransitionStep_Test.h \
    Include/Tests/Markov_Mol/MarkovState_Test.h \
    Include/Tests/ABC_Probability_Test.h \
    Include/Tests/Markov_Bay/ABC_Markov_Likelihood_step_Test.h \
    Include/Tests/Markov_Bay/SimpleOptimization_Test.h \
    Include/Tests/Markov_Bay/Markov_Bay_Test.h \
    Include/Tests/RandomTester.h \
    Include/Tests/MersenneTwister_Test.h \
    Include/Tests/Markov_Bay/MultivariateGaussian_Test.h


SOURCES -= Source/main_MacroConsole.cpp



SOURCES += \
    Source/Markov_Console/Markov_CommandManagerTest.cpp \
    Source/Tests/Markov_LA/matrixMath_Test.cpp \
    Source/Tests/Markov_LA/matrixIO_Test.cpp \
    Source/Tests/Markov_LA/matrixInverse_Test.cpp \
    Source/Tests/Markov_LA/matrixInit_Test.cpp \
    Source/Tests/Markov_LA/matrixExp_Test.cpp \
    Source/Tests/Markov_LA/matrixAssigmentOp_Test.cpp \
    Source/Tests/Markov_LA/matrixAritmetic_Test.cpp \
    Source/Tests/Markov_LA/Matrix_Test_times.cpp \
    Source/Tests/Markov_LA/Matrix_Test.cpp \
    Source/Tests/Markov_LA/Markov_LA_Test.cpp \
    Source/main_MacroConsole_Test.cpp \
    Source/Tests/ABC_Test.cpp\
    Source/Tests/MultipleTests.cpp \
    Source/Tests/ElementaryTest.cpp \
    Source/Tests/Markov_IO/ABC_Parametrizable_Test.cpp \
    Source/Tests/Markov_IO/ABC_Put_Test.cpp \
    Source/Tests/Markov_IO/ClassDescription_Test.cpp \
    Source/Tests/Markov_Mol/ABC_Markov_Model_Test.cpp \
    Source/Tests/Markov_Mol/MarkovTransitionRate_Test.cpp \
    Source/Tests/Markov_Mol/MarkovTransitionStep_Test.cpp \
    Source/Tests/Markov_Mol/MarkovState_Test.cpp \
    Source/Tests/Markov_Bay/ABC_Markov_Likelihood_step_Test.cpp \
    Source/Tests/Markov_Bay/SimpleOptimization_Test.cpp \
    Source/Tests/Markov_Mol/Markov_Mol_Tests.cpp \
    Source/Tests/Markov_Bay/Markov_Bay_Test.cpp \
    Source/Tests/Markov_LA/auxiliarMath_Test.cpp \
    Source/Tests/Markov_LA/matrixCholesky_Test.cpp \
    Source/Tests/MersenneTwister_Test.cpp \
    Source/Tests/Markov_Bay/MultivariateGaussian_Test.cpp \
    Source/Tests/Markov_LA/ToleranceComparison_Test.cpp \
    Source/Tests/Markov_LA/matrixSum_Test.cpp \
    Source/Tests/Markov_LA/matrixRounding_Test.cpp \
    Source/Tests/Markov_LA/matrixRelational_Test.cpp \
    Source/Tests/Markov_LA/matrixRand_Test.cpp \
    Source/Tests/Markov_LA/matrixProduct_Test.cpp \
    Source/Tests/Markov_LA/matrixOperators_Test.cpp \
    Source/Tests/Markov_LA/matrixMaxMin_Test.cpp \
    Source/Tests/Markov_LA/matrixMath_Test.cpp \
    Source/Tests/Markov_LA/matrixIO_Test.cpp \
    Source/Tests/Markov_LA/matrixInverse_Test.cpp \
    Source/Tests/Markov_LA/matrixInit_Test.cpp \
    Source/Tests/Markov_LA/matrixExp_Test.cpp \
    Source/Tests/Markov_LA/matrixCholesky_Test.cpp \
    Source/Tests/Markov_LA/matrixAssigmentOp_Test.cpp \
    Source/Tests/Markov_LA/matrixAritmetic_Test.cpp \
    Source/Tests/Markov_LA/Matrix_Test_times.cpp \
    Source/Tests/Markov_LA/Matrix_Test.cpp \
    Source/Tests/Markov_LA/Markov_LA_Test.cpp \
    Source/Tests/Markov_LA/auxiliarMath_Test.cpp


HEADERS = $$unique(HEADERS)

SOURCES =  $$unique(SOURCES)

message (" MacroRConsole_Test here")

}

HEADERS += \
    Include/Markov_Console/TestCommand.h

SOURCES += \
    Source/Markov_Console/TestCommand.cpp
