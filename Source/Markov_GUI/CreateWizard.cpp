#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QAbstractButton>
#include <QScrollArea>
#include <QComboBox>
#include <QDialog>
#include <QInputDialog>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QMenu>
#include <QRadioButton>
#include <QButtonGroup>

#include "Markov_IO/Object.h"

#include "Markov_LA/Matrix.h"
#include "Markov_LA/matrixRelational.h"

#include "Markov_IO/Object.h"

#include "Markov_GUI/CreateWizard.h"
#include "Markov_GUI/EditWizardField.h"

#include <Markov_Mol/QMarkovModel.h>

#include <Markov_IO/RandomPulses.h>
#include <Markov_IO/SinglePulses.h>
#include <Markov_IO/SinglePulses2.h>
#include "Markov_IO/PulsesProgram.h"
#include "Markov_IO/ExperimentalData.h"

#include "Markov_IO/Experiment.h"
#include "Markov_IO/PulsesTrace.h"
#include "Markov_IO/AverageExperiment.h"



#include "Markov_IO/ABC_IO.h"



#include <Markov_Mol/ExperimentSimulation.h>
#include <Markov_Mol/MarkovSimulator.h>
#include <Markov_Mol/GaussianNoise.h>
#include "Markov_Mol/QMarkovModel.h"
#include "Markov_Mol/PatchModel.h"
#include "Markov_Mol/PatchModelNormalDistribution.h"

#include "Markov_Mol/SimulationOptions.h"



#include <Markov_Console/Markov_Script.h>
#include "Markov_Console/Token.h"


#include "Markov_Bay/YfitLikelihoodEvaluation.h"
#include "Markov_Bay/OptimizationResult.h"
#include "Markov_Bay/SingleOptimizationResult.h"
#include "Markov_Bay/PartialLikelihoodEvaluation.h"
#include "Markov_Bay/LikelihoodEvaluation.h"
#include "Markov_Bay/Optimization_Step_BFGS.h"
#include "Markov_Bay/Optimization_Termination.h"
#include "Markov_Bay/TerminationByThreshold.h"


#include "Markov_Bay/LikelihoodOptions.h"
#include "Markov_Bay/TerminationByThreshold.h"
#include "Markov_Bay/SimpleOptimization.h"


#include "Markov_GUI/CreateWizardPage.h"




CreateWizard::CreateWizard(QString *className,
                            Markov_IO::ClassDescription* claDes,
                           Markov_IO::ABC_Saveable **s,
                            QWidget* parent):
    QWizard(parent),
    desc(claDes),
    sptr(s),
    myClassName(className)
{
    initselect();
}


CreateWizard::CreateWizard(QStringList classNames,
                            QString* className,
                            Markov_IO::ClassDescription* claDes,
                           Markov_IO::ABC_Saveable **s,
                            QWidget* parent):
    QWizard(parent),
    desc(claDes),
    sptr(s),
    myClassName(className)
{

    SelectStringWizardPage* selPage =new SelectStringWizardPage(&classNames,className);
    addPage(selPage);


}


QString CreateWizard::getClassName()const
{
    return *myClassName;
}

void CreateWizard::setClassName(const QString &newClassName)
{
    *myClassName=newClassName;
}




void CreateWizard::initselect()
{
    std::string className=myClassName->toStdString();
    if (className==Markov_Mol::Q_Markov_Model::ClassName())
        init_Q_Markov_Model();
    else if (className==Markov_IO::Pulses_program::ClassName())
        init_Pulses_program();
    else if (className==Markov_IO::Pulses_trace::ClassName())
         init_Pulses_trace();


    else if (className==Markov_IO::Experiment::ClassName())
        init_Experiment();

    else if (className==Markov_IO::Single_Pulses::ClassName())
        init_Single_Pulses();

    else if (className==Markov_IO::Single_Pulses2::ClassName())
        init_Single_Pulses2();

    else if (className==Markov_IO::ExperimentalData::ClassName())
        init_ExperimentData();

    else if (className==Markov_IO::Trace::ClassName())
        init_Trace();

    else if (className==Markov_IO::Random_Pulses::ClassName())
         init_Random_Pulses();

    else if (className==Markov_Mol::Experiment_simulation::ClassName())
         init_Experiment_simulation();

    else if (className==Markov_IO::Experiment_Average::ClassName())
         init_Experiment_Average();


    else if (className==Markov_Bay::LikelihoodEvaluation::ClassName())
         init_LikelihoodEvaluation();

    else if (className==Markov_Bay::OptimizationResult::ClassName())
         init_OptimizationResult();

    else if (className==Markov_Bay::SingleOptimizationResult::ClassName())
         init_SingleOptimizationResult();

    else if (className==Markov_Bay::LikelihoodOptions::ClassName())
    {
        if (desc->ClassName()!=Markov_Bay::LikelihoodOptions::ClassName())
        {

            *desc=Markov_Bay::LikelihoodOptions().GetDescription();
        }

         init_ClassDescription();
    }

    else if (className==Markov_Bay::Markov_Likelihood::Options::ClassName())
    {
        if (desc->ClassName()!=Markov_Bay::Markov_Likelihood::Options::ClassName())
        {

            *desc=Markov_Bay::Markov_Likelihood::Options().GetDescription();
        }

         init_ClassDescription();
    }

    else if (className==Markov_IO::AverageExperiment::Options::ClassName())
    {
        if (desc->ClassName()!=Markov_IO::AverageExperiment::Options::ClassName())
        {

            *desc=Markov_IO::AverageExperiment::Options().GetDescription();
        }

         init_ClassDescription();
    }

    else if (className==Markov_Bay::SimpleOptimization::Options::ClassName())
    {
        if (desc->ClassName()!=Markov_Bay::SimpleOptimization::Options::ClassName())
        {

            *desc=Markov_Bay::SimpleOptimization::Options().GetDescription();
        }

         init_ClassDescription();
    }




    else if (className==Markov_Bay::OptimizationStepBFGS::Options::ClassName())
    {
        if (desc->ClassName()!=Markov_Bay::OptimizationStepBFGS::Options::ClassName())
        {

            *desc=Markov_Bay::OptimizationStepBFGS::Options().GetDescription();
        }

         init_ClassDescription();
    }

    else if (className==Markov_Bay::TerminationByThreshold::Options::ClassName())
      {
          if (desc->ClassName()!=Markov_Bay::TerminationByThreshold::Options::ClassName())
          {

              *desc=Markov_Bay::TerminationByThreshold::Options().GetDescription();
          }

           init_ClassDescription();
      }
    else if (className==Markov_Mol::SimulationOptions::ClassName())
    {
        if (desc->ClassName()!=Markov_Mol::SimulationOptions::ClassName())
        {

            *desc=Markov_Mol::SimulationOptions().GetDescription();
        }

         init_ClassDescription();
    }



    else if (className==Markov_Mol::PatchModel::ClassName())
         init_PatchModel();

    else if (className==Markov_Mol::gaussian_noise::ClassName())
         init_gaussian_noise();

    else if (className==Markov_IO::Parameters::ClassName())
         init_Parameters();

  else
        reject();

}

void CreateWizard::accept()
{
    QWizard::accept();
    std::string className=myClassName->toStdString();

    if (className==Markov_Mol::Q_Markov_Model::ClassName())
        acceptQ_Markov_Model();
    else if (className==Markov_IO::Pulses_program::ClassName())
        accept_Pulses_program();
    else if (className==Markov_IO::Pulses_trace::ClassName())
         accept_Pulses_trace();



    else if (className==Markov_IO::Experiment::ClassName())
        accept_Experiment();

    else if (className==Markov_IO::Single_Pulses::ClassName())
        accept_Single_Pulses();

    else if (className==Markov_IO::Single_Pulses2::ClassName())
        accept_Single_Pulses2();

    else if (className==Markov_IO::Trace::ClassName())
        accept_Trace();

    else if (className==Markov_IO::Random_Pulses::ClassName())
         accept_Random_Pulses();

    else if (className==Markov_IO::ExperimentalData::ClassName())
         accept_ExperimentData();

    else if (className==Markov_Mol::Experiment_simulation::ClassName())
         accept_Experiment_simulation();

    else if (className==Markov_IO::Experiment_Average::ClassName())
         accept_Experiment_Average();


    else if (className==Markov_Bay::LikelihoodEvaluation::ClassName())
         accept_LikelihoodEvaluation();

    else if (className==Markov_Bay::OptimizationResult::ClassName())
         accept_OptimizationResult();

    else if (className==Markov_Bay::SingleOptimizationResult::ClassName())
         accept_SingleOptimizationResult();

    else if (className==Markov_Bay::LikelihoodOptions::ClassName())
      {
          Markov_Bay::LikelihoodOptions* m=new Markov_Bay::LikelihoodOptions;
          m->LoadFromDescription(*desc);
          *sptr=m;

      }
    else if (className==Markov_Mol::SimulationOptions::ClassName())
      {
          Markov_Mol::SimulationOptions* m=new Markov_Mol::SimulationOptions;
          m->LoadFromDescription(*desc);
          *sptr=m;

      }


    else if (className==Markov_Bay::Markov_Likelihood::Options::ClassName())
    {
        Markov_Bay::Markov_Likelihood::Options* m=new Markov_Bay::Markov_Likelihood::Options;
        m->LoadFromDescription(*desc);
        *sptr=m;

    }

    else if (className==Markov_Bay::SimpleOptimization::Options::ClassName())
    {
        Markov_Bay::SimpleOptimization::Options* m=new Markov_Bay::SimpleOptimization::Options;
        m->LoadFromDescription(*desc);
        *sptr=m;

    }


    else if (className==Markov_IO::AverageExperiment::Options::ClassName())
    {
        Markov_IO::AverageExperiment::Options* m=new Markov_IO::AverageExperiment::Options;
        m->LoadFromDescription(*desc);
        *sptr=m;
    }

    else if (className==Markov_Bay::OptimizationStepBFGS::Options::ClassName())
    {
        Markov_Bay::OptimizationStepBFGS::Options* m=new Markov_Bay::OptimizationStepBFGS::Options;
        m->LoadFromDescription(*desc);
        *sptr=m;
    }

    else if (className==Markov_Bay::TerminationByThreshold::Options::ClassName())
{
        Markov_Bay::TerminationByThreshold::Options* m=new Markov_Bay::TerminationByThreshold::Options;
        m->LoadFromDescription(*desc);
        *sptr=m;
    }

    else if (className==Markov_Bay::Markov_Likelihood::Options::ClassName())
      {
              Markov_Bay::Markov_Likelihood::Options* m=new Markov_Bay::Markov_Likelihood::Options;
              m->LoadFromDescription(*desc);
              *sptr=m;
          }


    else if (className==Markov_Mol::PatchModel::ClassName())
         accept_PatchModel();

    else if (className==Markov_Mol::gaussian_noise::ClassName())
         accept_gaussian_noise();

    else if (className==Markov_IO::Parameters::ClassName())
         accept_Parameters();


}


void CreateWizard::init_Q_Markov_Model()
{
    *desc=Markov_Mol::Q_Markov_Model().GetDescription();
    CreateQ_Markov_ModelPage0 *page0=new CreateQ_Markov_ModelPage0(desc);
    CreateWizardPage *page1=
            new CreateWizardPage(QStringList("agonist_vector"),
                                 desc);
    CreateWizardPage *page2=
            new CreateWizardPage(QStringList("unitary_conductance,NOT_ZERO")
                                <<"conductance_vector,NOT_ALL_ZERO",
                                 desc);
    CreateWizardPage *page3=
            new CreateWizardPage(QStringList("Q_matrix,Q_Matrix"),desc);
    addPage(page0);
    addPage(page1);
    addPage(page2);
    addPage(page3);
}

void CreateWizard::init_Pulses_program(){
    *desc=Markov_IO::Pulses_program().GetDescription();
    Create_Pulses_program_Page0 *page0=new Create_Pulses_program_Page0(desc);
    Create_Pulses_program_Page1 *page1=new Create_Pulses_program_Page1(desc);;
    Create_Pulses_program_Page2 *page2=new Create_Pulses_program_Page2(desc);
    addPage(page0);
    addPage(page1);
    addPage(page2);
    }

void CreateWizard::init_Pulses_trace(){

    if (desc->ClassName()!=Markov_IO::Pulses_trace::ClassName())
         *desc=Markov_IO::Pulses_trace().GetDescription();
      Create_Pulses_trace_Page0 *page0=new Create_Pulses_trace_Page0(desc);
      Create_Pulses_trace_Page1 *page1= new Create_Pulses_trace_Page1(desc);
      Create_Pulses_trace_Page2 *page2=new Create_Pulses_trace_Page2(desc);
      addPage(page0);
      addPage(page1);
      addPage(page2);

}




void CreateWizard::init_Trace(){

   if (desc->ClassName()!=Markov_IO::Trace::ClassName())
   {
       Markov_LA::M_Matrix<double> tx(Markov_LA::zeros<double>(1,2));
       Markov_LA::M_Matrix<double> ty(Markov_LA::zeros<double>(1,2));


       *desc=Markov_IO::Trace("",tx,ty,0).GetDescription();
   }
      CreateWizardPage *page0=new CreateWizardPage(
                  QStringList("name")<<"evolution_of_x,ColTitle_0_t,ColTitle_1_x,ROW_INDEX",
                  desc);
      CreateWizardPage *page1=
       new CreateWizardPage(
          QStringList("evolution_of_y,ColTitle_0_t,ColTitle_1_y,ROW_INDEX"),
          desc);
      addPage(page0);
      addPage(page1);

}


void CreateWizard::init_Experiment(){
    if (desc->ClassName()!=Markov_IO::Experiment::ClassName())
         *desc=Markov_IO::Experiment().GetDescription();

      Create_Experiment_Page0 *page0=new Create_Experiment_Page0(desc);
      Create_Experiment_Page1 *page1= new Create_Experiment_Page1(desc);
      addPage(page0);
      addPage(page1);

}
void CreateWizard::init_Single_Pulses(){
    if (desc->ClassName()!=Markov_IO::Single_Pulses::ClassName())
         *desc=Markov_IO::Single_Pulses().GetDescription();

      desc->push_back("number_of_pulse_concentrations",std::size_t(1));
      Create_Single_Pulses_Page0 *page0=new Create_Single_Pulses_Page0(desc);
      Create_Single_Pulses_Page1 *page1= new Create_Single_Pulses_Page1(desc);
      addPage(page0);
      addPage(page1);



}
void CreateWizard::init_Single_Pulses2(){

}
void CreateWizard::init_Random_Pulses(){
    if (desc->ClassName()!=Markov_IO::Random_Pulses::ClassName())
    {

        *desc=Markov_IO::Random_Pulses().GetDescription();
    }
       CreateWizardPage *page0=new CreateWizardPage(
                   QStringList("name")<<
                   "time_of_pulse"<<
                   "minimal_pulse_duration,POSITIVE"<<
                   "maximal_pulse_duration,POSITIVE"<<
                   "minimal_interval,POSITIVE"<<
                   "maximal_interval,POSITIVE",
                   desc);

       CreateWizardPage *page1=new CreateWizardPage(
                   QStringList("is_log_scale")<<
                   "concentrations,COL_INDEX,POSITIVE"<<
                   "trace_duratrion,POSITIVE"<<
                   "trace_interval,POSITIVE"<<
                   "frequency_of_sampling,POSITIVE"<<
                   "exchange_time,NON_NEGATIVE"<<
                   "sub_step_time",
                   desc);

       addPage(page0);
       addPage(page1);

}
void CreateWizard::init_Experiment_simulation(){

}

void CreateWizard::init_ExperimentData(){
    if (desc->ClassName()!=Markov_IO::ExperimentalData::ClassName())
    {

        *desc=Markov_IO::ExperimentalData().GetDescription();
    }
       CreateWizardPage *page0=new CreateWizardPage(
                   QStringList("name")<<
                   "fileName,fileName"<<
                   "fileNameCode"<<
                   "PatchNameCode"<<
                   "GainCode"<<
                   "SamplingFrequencyCode"<<
                   "AgonistCode"<<
                   "time_to_exchange"<<
                   "sub_step_time"<<
                   "time_to_next_trace",
                   desc);




       addPage(page0);

}



void CreateWizard::init_Experiment_Average(){
    if (desc->ClassName()!=Markov_IO::Experiment_Average::ClassName())
    {

        *desc=Markov_IO::Random_Pulses().GetDescription();
    }
       CreateWizardPage *page0=new CreateWizardPage(
                   QStringList("name")<<
                   "time_of_pulse"<<
                   "minimal_pulse_duration,POSITIVE"<<
                   "maximal_pulse_duration,POSITIVE"<<
                   "minimal_interval,POSITIVE"<<
                   "maximal_interval,POSITIVE",
                   desc);

       CreateWizardPage *page1=new CreateWizardPage(
                   QStringList("is_log_scale")<<
                   "concentrations,COL_INDEX,POSITIVE"<<
                   "trace_duratrion,POSITIVE"<<
                   "trace_interval,POSITIVE"<<
                   "frequency_of_sampling,POSITIVE"<<
                   "exchange_time,NON_NEGATIVE"<<
                   "sub_step_time",
                   desc);

       addPage(page0);
       addPage(page1);

}
void CreateWizard::init_LikelihoodEvaluation(){

}
void CreateWizard::init_OptimizationResult(){

}
void CreateWizard::init_SingleOptimizationResult(){

}
void CreateWizard::init_ClassDescription(){
  double numFieldsPerPage=6;

  if (desc->size()<numFieldsPerPage+1)
  {
       CreateWizardPage *page0=new CreateWizardPage(desc);
       addPage(page0);
    }
  else
    {
      QList<int> ilist;
      for (std::size_t i=0; i<desc->size();i++)
        {
          ilist.push_back(i);
          if (std::floor((i+1.0)/numFieldsPerPage)*numFieldsPerPage==i+1.0)
        {
              CreateWizardPage *page0=new CreateWizardPage(ilist,desc);
              addPage(page0);
              ilist.clear();
            }
      }
      CreateWizardPage *page0=new CreateWizardPage(ilist,desc);
      addPage(page0);

    }

}
void CreateWizard::init_PatchModel(){
    if (desc->ClassName()!=Markov_Mol::PatchModel::ClassName())
    {

        *desc=Markov_Mol::PatchModel().GetDescription();
    }
       CreateWizardPage *page0=new CreateWizardPage(
                   QStringList("name")<<
                   "Channel_Model"<<
                   "Number_of_Channels,POSITIVE"<<
                   "Noise",
                   desc);



       addPage(page0);


}
void CreateWizard::init_gaussian_noise(){
    if (desc->ClassName()!=Markov_Mol::gaussian_noise::ClassName())
    {

        *desc=Markov_Mol::gaussian_noise().GetDescription();
    }
       CreateWizardPage *page0=new CreateWizardPage(
                   QStringList("name")<<
                   "standard_deviation,NON_NEGATIVE"<<
                   "frequency_of_sampling,POSITIVE",
                   desc);

              addPage(page0);


}
void CreateWizard::init_Parameters(){

}







void CreateWizard::acceptQ_Markov_Model()
{
    Markov_Mol::Q_Markov_Model* m=new Markov_Mol::Q_Markov_Model;
    m->LoadFromDescription(*desc);
    *sptr=m;
}

void CreateWizard::accept_Pulses_program()
{
    Markov_IO::Pulses_program* m=new Markov_IO::Pulses_program;
    m->LoadFromDescription(*desc);
    *sptr=m;

}




void CreateWizard::accept_Pulses_trace()
{
    Markov_IO::Pulses_trace* m=new Markov_IO::Pulses_trace;
    m->LoadFromDescription(*desc);
    *sptr=m;

}




void CreateWizard::accept_Experiment(){
    Markov_IO::Experiment* m=new Markov_IO::Experiment;
    m->LoadFromDescription(*desc);
    *sptr=m;

}
void CreateWizard::accept_Single_Pulses(){
    Markov_IO::Single_Pulses* m=new Markov_IO::Single_Pulses;
    m->LoadFromDescription(*desc);
    *sptr=m;

}
void CreateWizard::accept_Single_Pulses2(){

}
void CreateWizard::accept_Trace(){
    Markov_IO::Trace* m=new Markov_IO::Trace;
    m->LoadFromDescription(*desc);
    *sptr=m;
}
void CreateWizard::accept_Random_Pulses(){
    Markov_IO::Random_Pulses* m=new Markov_IO::Random_Pulses;
    m->LoadFromDescription(*desc);
    *sptr=m;

}
void CreateWizard::accept_ExperimentData(){
    Markov_IO::ExperimentalData* m=new Markov_IO::ExperimentalData;
    m->LoadFromDescription(*desc);
    *sptr=m;

}
void CreateWizard::accept_Experiment_simulation(){

}
void CreateWizard::accept_Experiment_Average(){

}
void CreateWizard::accept_LikelihoodEvaluation(){

}
void CreateWizard::accept_OptimizationResult(){

}
void CreateWizard::accept_SingleOptimizationResult(){

}
void CreateWizard::accept_LikelihoodOptions(){

}
void CreateWizard::accept_Markov_Likelihood_Options(){

}
void CreateWizard::accept_PatchModel(){
    Markov_Mol::PatchModel* m=new Markov_Mol::PatchModel;
    m->LoadFromDescription(*desc);
    *sptr=m;



}
void CreateWizard::accept_gaussian_noise(){
    Markov_Mol::gaussian_noise* m=new Markov_Mol::gaussian_noise;
    m->LoadFromDescription(*desc);
    *sptr=m;

}
void CreateWizard::accept_Parameters(){

}





















