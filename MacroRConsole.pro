#-------------------------------------------------
#
# Project created by QtCreator 2010-10-22T10:21:34
#
#-------------------------------------------------
# No GUI, only Console, no dependency on Qt, nor on
# other graphic libraries (i.e, no Markov_Plot)

#message(ENTER MACROCONSOLE CONFIG ES $$CONFIG)

!macroRConsole{
CONFIG +=macroRConsole
#message ("MacroRConsole here")
TARGET = MacroRConsole

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++14

QMAKE_CXXFLAGS_RELEASE += -std=c++14 #-lpthread
QMAKE_CXXFLAGS_DEBUG += -std=c++14 #-lpthread
QMAKE_CXXFLAGS += -std=c++14 #-lpthread


INCLUDEPATH = Include \
            Include/Borrowed

DEPENDPATH= Include \
            Include/Borrowed



GITVERFILENAME = versionNumber
UNCOMMITEDFILENAME=uncommited

GITVERPATH = $${OUT_PWD}/$$GITVERFILENAME
UNCOMMITEDPATH = $${OUT_PWD}/$$UNCOMMITEDFILENAME
path=$$system_path($$GITVERPATH)
uncommitedpath=$$system_path($$UNCOMMITEDPATH)
# stores the hash number in the versionNumber filei
win32{

    # if you installed git in th e safe way this is the suggested directory
    GITCALL='"\Program Files (x86)\Git\bin\git.exe"'
    HASH = $$system(call $$GITCALL rev-parse --short HEAD)
    DATE=$$system(call $$GITCALL show -s --format="%ci" HEAD)
    UNCOMMITED=$$system(call $$GITCALL status --porcelain)
    HASH_DATE=$$HASH  $$DATE
    write_file($$path,HASH_DATE)
    write_file($$uncommitedpath,UNCOMMITED)


} else {

    HASH=$$system(git rev-parse --short HEAD)
    DATE=$$system(git show -s --format="%ci" HEAD)
    UNCOMMITED=$$system(git status --porcelain)

    HASH_DATE=$$HASH  $$DATE

    write_file($$path,HASH_DATE)
    write_file($$uncommitedpath,UNCOMMITED)

}

# defines a Macro containing the name of the versionNumber file

DEFINES+='GIT_VER_PATH=$${GITVERFILENAME}'
DEFINES+='UNCOMMITED_PATH=$${UNCOMMITEDFILENAME}'


CONFIG(debug, debug|release) {

} else {
  DEFINES += NDEBUG
}

#QMAKE_CXXFLAGS_DEBUG += -pg
#QMAKE_LFLAGS_DEBUG += -pg

#unix:!macx {
#QMAKE_CXX = g++-4.8
#}

QMAKE_CXXFLAGS_RELEASE += -fopenmp
QMAKE_LFLAGS_RELEASE += -fopenmp

QMAKE_CXXFLAGS_DEBUG += -fopenmp
QMAKE_LFLAGS_DEBUG += -fopenmp



#QMAKE_CXXFLAGS_RELEASE -=-O2

#QMAKE_CXXFLAGS_RELEASE +=-O3


HEADERS += \
#    Include/Markov_Bay/MarkovOptim.h \
    Include/Markov_Bay/MarkovLikelihood.h \
    Include/Markov_Bay/MacroRStep.h \
    Include/Markov_Bay/MacroNRStep.h \
    Include/Markov_Bay/MacroDRStep.h \
    Include/Markov_Bay/ABC_MarkovLikelihoodStep.h \
    Include/Markov_Console/Markov_console.h \
    Include/Markov_Console/Markov_CommandManager.h \
    Include/Markov_IO/x_step.h \
    Include/Markov_IO/x_dt.h \
    Include/Markov_IO/SinglePulses2.h \
    Include/Markov_IO/SinglePulses.h \
    Include/Markov_IO/RandomPulses.h \
    Include/Markov_IO/PulsesTrace.h \
    Include/Markov_IO/PulsesProgram.h \
    Include/Markov_IO/Pulse.h \
    Include/Markov_IO/FileDir.h \
    Include/Markov_IO/ExperimentAverage.h \
    Include/Markov_IO/auxiliarIO.h \
    Include/Markov_IO/ABC_Trace.h \
    Include/Markov_IO/ABC_MeasureStep.h \
    Include/Markov_IO/ABC_MeasurePoint.h \
    Include/Markov_IO/ABC_Experiment.h \
    Include/Markov_LA/ToleranceComparison.h \
    Include/Markov_LA/matrixSum.h \
    Include/Markov_LA/matrixRounding.h \
    Include/Markov_LA/matrixRelational.h \
    Include/Markov_LA/matrixRand.h \
    Include/Markov_LA/matrixProduct.h \
    Include/Markov_LA/matrixOperators.h \
    Include/Markov_LA/matrixMaxMin.h \
    Include/Markov_LA/matrixMath.h \
    Include/Markov_LA/matrixIO.h \
    Include/Markov_LA/matrixInverse.h \
    Include/Markov_LA/matrixInit.h \
    Include/Markov_LA/matrixExp.h \
    Include/Markov_LA/matrixAssigmentOp.h \
    Include/Markov_LA/matrixAritmetic.h \
    Include/Markov_LA/Matrix.h \
    Include/Markov_LA/Markov_LA_doxygen.h \
    Include/Markov_LA/auxiliarRelational.h \
    Include/Markov_LA/auxiliarMath.h \
    Include/Markov_Mol/QMarkovModel.h \
    Include/Markov_Mol/QAux.h \
    Include/Markov_Mol/MarkovTransitionStep.h \
    Include/Markov_Mol/MarkovTransitionRate.h \
    Include/Markov_Mol/MarkovStateExt.h \
    Include/Markov_Mol/MarkovState.h \
    Include/Markov_Mol/GaussianNoise.h \
    Include/Markov_Mol/ExperimentSimulation.h \
    Include/Markov_Mol/BufferedFunction.h \
    Include/Markov_Mol/ABC_Noise.h \
    Include/Markov_Mol/ABC_MarkovModel.h \
    Include/Markov_Console/Markov_console.h \
    Include/Markov_doxygen/A0_MacroRDoxy.h \
    Include/Markov_doxygen/A100_UserGuideDoxy.h \
    Include/Markov_doxygen/A10_UseCasesDoxy.h \
    Include/Markov_doxygen/A11_InstalationDoxy.h \
    Include/Markov_doxygen/A12_HandsOnDoxy.h \
    Include/Markov_doxygen/A13_ConsoleVsGuiDoxy.h \
    Include/Markov_doxygen/A14_AbcOfKineticFittingDoxy.h \
    Include/Markov_doxygen/A15_KineticModelsTaskDoxy.h \
    Include/Markov_doxygen/A16_RecordingsTaskDoxy.h \
    Include/Markov_doxygen/A17_SimulationsTaskDoxy.h \
    Include/Markov_doxygen/A18_MaximumLikelihoodEstimationRTask.h \
    Include/Markov_doxygen/A19_ModelsSearchTaskDoxy.h \
    Include/Markov_doxygen/A1A_RemoteControlDoxy.h \
    Include/Markov_doxygen/A1B_GraphicRepresentationDoxy.h \
    Include/Markov_doxygen/A1C_FAQDoxy.h \
    Include/Markov_doxygen/A1D_TroubleshootingDoxy.h \
    Include/Markov_doxygen/A1E_GlossaryDoxy.h\
    Include/Markov_doxygen/A2_TheoryDoxy.h \
    Include/Markov_doxygen/A3_ReferenceManualDoxy.h \
    Include/Markov_doxygen/A4_DevelopersGuideDoxy.h \
    Include/Markov_IO/ABC_Options.h \
    Include/Markov_Mol/PatchModel.h \
 #   Include/Markov_Bay/ABC_ParametricDistributable.h \
 #   Include/Markov_Bay/NormalDistributed.h \
 #   Include/Markov_doxygen/ABC_DescriptibleRegular.h \
    Include/Markov_Mol/ABC_PatchModel.h \
    Include/Markov_IO/Experiment.h \
    Include/Markov_IO/Trace.h \
    Include/Markov_Bay/LikelihoodEvaluation.h \
#    Include/Markov_Bay/PartialLikelihoodEvaluation.h \
#    Include/Markov_Bay/YfitLikelihoodEvaluation.h \
    Include/Markov_Bay/LikelihoodOptions.h \
    Include/Markov_Bay/ABC_Result.h \
    Include/Markov_Console/Help_File.h \
#    Include/Markov_Bay/MarkovOptimization.h \
#    Include/Markov_Bay/OptimizationResult.h \
#    Include/Markov_Bay/MultivariateGaussian.h \
    Include/Markov_LA/matrixCholesky.h \
#    Include/Markov_Bay/SimpleOptimization.h \
#    Include/Markov_Bay/SingleOptimizationResult.h \
#    Include/Markov_Bay/ABC_Optimization_step.h \
#    Include/Markov_Bay/ABC_Optimization_termination.h \
#    Include/Markov_Bay/Optimization_Step_BFGS.h \
#    Include/Markov_Bay/Optimization_Termination.h \
#    Include/Markov_Bay/TerminationByThreshold.h \
#    Include/Markov_Bay/ABC_Distribution.h \
#    Include/Markov_Bay/G_Test.h \
#    Include/Markov_LA/ContinuedFraction.h \
#    Include/Markov_Bay/RandomDistribution_Test.h \
#    Include/Markov_Bay/MacroAproxStep.h \
#    Include/Markov_Bay/MacroscopicGaussianDistribution.h \
    Include/Markov_IO/ABC_IO.h \
    Include/Markov_IO/ExperimentalData.h \
    Include/Markov_Console/ImportCommand.h \
    Include/Markov_IO/ABFFile.h \
    Include/Markov_IO/ABF1_Headers.h \
    Include/Markov_IO/ABF2_Headers.h \
 #   Include/Markov_Bay/OptimizationDistributionResults.h \
    Include/Markov_Console/CommandHistory.h


SOURCES += \
    Source/Markov_IO/FunctionCommand.cpp \
    Source/Markov_IO/Token_New.cpp \
    Source/Markov_IO/buildByToken.cpp\
    Source/Markov_Mol/PatchModel.cpp \
    Source/Markov_IO/auxiliarIO.cpp \
    Source/Markov_Bay/MarkovLikelihood.cpp \
#    Source/Markov_Bay/Markov_Bay.cpp \
    Source/Markov_Bay/MacroRStep.cpp \
    Source/Markov_Bay/MacroNRStep.cpp \
    Source/Markov_Bay/MacroDRStep.cpp \
    Source/Markov_Bay/ABC_MarkovLikelihoodStep.cpp \
    Source/Markov_Console/Markov_console.cpp \
    Source/Markov_Console/Markov_CommandManager.cpp \
    Source/Markov_IO/x_step.cpp \
    Source/Markov_IO/x_dt.cpp \
    Source/Markov_IO/SinglePulses2.cpp \
    Source/Markov_IO/SinglePulses.cpp \
    Source/Markov_IO/RandomPulses.cpp \
    Source/Markov_IO/PulsesTrace.cpp \
    Source/Markov_IO/PulsesProgram.cpp \
    Source/Markov_IO/Pulse.cpp \
    Source/Markov_IO/FileDir.cpp \
    Source/Markov_IO/ExperimentAverage.cpp \
    Source/Markov_IO/ABC_Trace.cpp \
    Source/Markov_IO/ABC_MeasureStep.cpp \
    Source/Markov_IO/ABC_Experiment.cpp \
    Source/Markov_LA/ToleranceComparison.cpp \
    Source/Markov_LA/matrixSum.cpp \
    Source/Markov_LA/matrixRounding.cpp \
    Source/Markov_LA/matrixRelational.cpp \
    Source/Markov_LA/matrixRand.cpp \
    Source/Markov_LA/matrixProductLapack.cpp \
    Source/Markov_LA/matrixProduct.cpp \
    Source/Markov_LA/matrixOperators.cpp \
    Source/Markov_LA/matrixMaxMin.cpp \
    Source/Markov_LA/matrixMath.cpp \
    Source/Markov_LA/matrixIO.cpp \
    Source/Markov_LA/matrixInit.cpp \
    Source/Markov_LA/matrixExp.cpp \
    Source/Markov_LA/matrixAssigmentOp.cpp \
    Source/Markov_LA/matrixAritmetic.cpp \
    Source/Markov_LA/Matrix.cpp \
    Source/Markov_LA/matrixInverse.cpp \
    Source/Markov_LA/auxiliarRelational.cpp \
    Source/Markov_LA/auxiliarMath.cpp \
    Source/Markov_Mol/QMarkovModel.cpp \
    Source/Markov_Mol/QAux.cpp \
    Source/Markov_Mol/MarkovTransitionStep.cpp \
    Source/Markov_Mol/MarkovTransitionRate.cpp \
    Source/Markov_Mol/MarkovStateExt.cpp \
    Source/Markov_Mol/MarkovState.cpp \
    Source/Markov_Mol/GaussianNoise.cpp \
    Source/Markov_Mol/ExperimentSimulation.cpp \
    Source/Markov_Mol/BufferedFunction.cpp \
    Source/Markov_Mol/ABC_Noise.cpp \
    Source/Markov_Mol/ABC_MarkovModel.cpp \
    Source/main_MacroConsole.cpp \
    Source/Markov_IO/ABC_Options.cpp \
    Source/Markov_Mol/ABC_PatchModel.cpp \
    Source/Markov_IO/Trace.cpp \
    Source/Markov_IO/Experiment.cpp \
    Source/Markov_Bay/LikelihoodEvaluation.cpp \
#    Source/Markov_Bay/PartialLikelihoodEvaluation.cpp \
#    Source/Markov_Bay/YfitLikelihoodEvaluation.cpp \
 #   Source/Markov_Bay/LikelihoodOptions.cpp \
 #   Source/Markov_Bay/ABC_Result.cpp \
 #   Source/Markov_Bay/ABC_ParametricDistributable.cpp \
 #   Source/Markov_Bay/NormalDistributed.cpp \
    Source/Markov_LA/matrixCholesky.cpp \
#    Source/Markov_Bay/MultivariateGaussian.cpp \
#    Source/Markov_Bay/OptimizationResult.cpp \
#    Source/Markov_Bay/SingleOptimizationResult.cpp \
#    Source/Markov_Bay/SimpleOptimization.cpp \
#    Source/Markov_Bay/Optimization_Step_BFGS.cpp \
#    Source/Markov_Bay/ABC_Optimization_step.cpp \
#    Source/Markov_Bay/ABC_Optimization_termination.cpp \
#    Source/Markov_Bay/Optimization_Termination.cpp \
#    Source/Markov_Bay/TerminationByThreshold.cpp \
#    Source/Markov_Bay/ABC_Distribution.cpp \
#    Source/Markov_Bay/G_Test.cpp \
    Source/Markov_LA/ContinuedFraction.cpp \
#    Source/Markov_Bay/MacroAproxStep.cpp \
#    Source/Markov_Bay/MacroscopicGaussianDistribution.cpp \
    Source/Markov_IO/ExperimentalData.cpp \
    Source/Markov_IO/ABFFile.cpp \
    Source/Markov_IO/ABF1_Headers.cpp \
    Source/Markov_Console/CommandHistory.cpp
win32{
    LIBS += -L$$PWD/lib -lcygblas \
            -L$$PWD/lib -lcyglapack
} else {
    LIBS +=  -lblas  -llapack
#-lgfortran
}

HEADERS = $$unique(HEADERS)
SOURCES =  $$unique(SOURCES)

OTHER_FILES += \
    help_files/wellcome.txt \
    help_files/save.txt \
    help_files/model.txt \
    help_files/load.txt \
    help_files/introduction.txt \
    help_files/help.txt \
    help_files/export.txt \
    help_files/experiment.txt \
    help_files/edit.txt \
    help_files/commands.txt \
    help_files/commands_long.txt \
    help_files/help_long.txt \
    help_files/load_long.txt \
    help_files/dir.txt \
    help_files/cd.txt \
    help_files/who.txt \
    help_files/clear.txt \
    help_files/simulate.txt \
    help_files/likelihood.txt \
    help_files/optimize.txt \
    help_files/options_simulate.txt \
    help_files/model_patch.txt \
    help_files/model_channel.txt \
    help_files/option.txt \
    help_files/option_simulate.txt \
    help_files/option_likelihood.txt \
    help_files/option_optimize.txt \
    help_files/simulate.txt \
    help_files/optimize.txt \
    help_files/likelihood.txt


win32{
    for (f, OTHER_FILES){
        FS=$$system_path($$f)
        FT = $$system_path($${OUT_PWD}/$$f)
        DN=$$dirname(FT)
        !exists($$DN):system(mkdir $$system_path($$DN))
        system(copy $$FS  $$FT)
    }
} else{
    for (f, OTHER_FILES){
        FS=$$system_path($$f)
        FT = $${OUT_PWD}/$$f
        DN=$$dirname(FT)
        !exists($$DN):system(mkdir $$system_path($$DN))
        system(cp $$FS  $$FT)
    }
}


# defines a Macro containing the name of the directory to find the help files
HELPPATH = $${OUT_PWD}/help_files

DEFINES+='HELP_PATH=$${HELPPATH}'



message ("MacroRConsole end here")

}

HEADERS += \
    Include/Markov_IO/ABFExperiment.h \
    Include/Markov_Console/MacorCoreApplication.h \
    Include/Markov_Console/ExpressionManager.h \
    Include/Markov_IO/Token_New.h \
    Include/Markov_IO/buildByToken.h \
    Include/Markov_IO/Var.h \
    Include/Markov_IO/Cls.h \
    Include/Markov_IO/Implements_ComplexVar_New.h \
    Include/Markov_IO/buildByTokenTempl.h \
    Include/Markov_IO/myTypes.h \
    Include/Markov_IO/Implements_path.h \
    Include/Markov_IO/FileLoadSave.h \
    Include/Markov_IO/VarTempl.h \
    Include/Markov_IO/myTypesExperiment.h \
    Include/Markov_IO/mp_Function.h \
    Include/Markov_IO/FunctionCommand.h \
    Include/Markov_IO/StructureEnv.h \
    Include/Markov_IO/Closure.h \
    Include/Markov_IO/Closure_type.h \
    Include/Markov_IO/buildClosureByToken.h \
    Include/Markov_IO/Implements_Closures.h \
    Include/Markov_IO/StructureEnv_templ.h \
    Include/Markov_IO/Implements_Closures_templ.h \
    Include/Markov_IO/buildClosureByToken_Templ.h \
    Include/Markov_Bay/Distributions.h \
    Include/Markov_Console/ScriptManager.h \
    Include/Markov_Bay/myTypes_Bayesian.h

SOURCES += \
    Source/Markov_Console/ExpressionManager.cpp \
    Source/Markov_IO/Var.cpp \
    Source/Markov_IO/Implements_ComplexVar_New.cpp \
    Source/Markov_IO/myTypes.cpp \
    Source/Markov_IO/Implements_path.cpp \
    Source/Markov_IO/FileLoadSave.cpp \
    Source/Markov_IO/myTypesExperiment.cpp \
    Source/Markov_IO/StructureEnv.cpp \
    Source/Markov_IO/buildClosureByToken.cpp \
    Source/Markov_IO/Implements_Closures.cpp \
    Source/Markov_Console/ScriptManager.cpp

OTHER_FILES += \
    help_files/plan_aheadd.txt

DISTFILES +=




