#include "Markov_GUI/CreateWizardPage.h"
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QAbstractButton>
#include <QScrollArea>
#include <QComboBox>
#include <QDialog>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QMenu>
#include <QRadioButton>
#include <QButtonGroup>
#include <QDebug>

#include "Markov_IO/Object.h"

#include "Markov_LA/Matrix.h"
#include "Markov_LA/matrixRelational.h"

#include "Markov_IO/Object.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_GUI/CreateWizard.h"
#include "Markov_GUI/EditWizardField.h"

#include <Markov_Mol/QMarkovModel.h>

#include <Markov_IO/RandomPulses.h>
#include <Markov_IO/SinglePulses.h>
#include <Markov_IO/SinglePulses2.h>
#include "Markov_IO/PulsesProgram.h"

#include "Markov_IO/Experiment.h"
#include "Markov_IO/PulsesTrace.h"
#include "Markov_IO/ExperimentAverage.h"



#include "Markov_IO/ABC_IO.h"



#include <Markov_Mol/ExperimentSimulation.h>
#include <Markov_Mol/MarkovSimulator.h>
#include <Markov_Mol/GaussianNoise.h>
#include "Markov_Mol/QMarkovModel.h"
#include "Markov_Mol/PatchModel.h"
#include "Markov_Mol/PatchModelNormalDistribution.h"




#include <Markov_Console/Markov_Script.h>
#include "Markov_Console/Token.h"


#include "Markov_Bay/YfitLikelihoodEvaluation.h"
#include "Markov_Bay/OptimizationResult.h"
#include "Markov_Bay/SingleOptimizationResult.h"
#include "Markov_Bay/PartialLikelihoodEvaluation.h"
#include "Markov_Bay/LikelihoodEvaluation.h"

#include "Markov_Bay/LikelihoodOptions.h"
#include "Markov_Bay/TerminationByThreshold.h"
#include "Markov_Bay/SimpleOptimization.h"

#include "Markov_LA/matrixRelational.h"







SelectStringWizardPage::SelectStringWizardPage(
        QStringList* someStrings,QString* selectedString):
    list_(someStrings),
    str_(selectedString),
    nextId_(1)
{

}

int SelectStringWizardPage::nextId()const
{
    return nextId_;
}



void SelectStringWizardPage::initializePage()
{
    nextId_=wizard()->currentId()+1;
    QButtonGroup *buttonGroup=new QButtonGroup;
    QVBoxLayout *vbox = new QVBoxLayout;
    for (int i=0; i<list_->size(); i++)
    {
        QRadioButton *radio = new QRadioButton(list_->at(i));
        vbox->addWidget(radio);
        buttonGroup->addButton(radio,i);
    }
    setLayout(vbox);
    connect(buttonGroup,SIGNAL(buttonClicked(int)),this,SLOT(setString(int)));
    connect(buttonGroup,SIGNAL(buttonClicked(int)),this,SIGNAL(completeChanged()));


    setCommitPage(true);

}

void SelectStringWizardPage::setString(int i)
{
    *str_=list_->at(i);
}

bool SelectStringWizardPage::isComplete() const
{
    return !(str_->isEmpty());
}


bool SelectStringWizardPage::validatePage()
{
    CreateWizard* w=dynamic_cast<CreateWizard*> (wizard());

    w->setClassName(*str_);
    w->initselect();
    nextId_=w->currentId()+1;
    return true;

}









CreateWizardPage::CreateWizardPage(
        QList<QString>someFieldNames,
        Markov_IO::ClassDescription* claDes):
    des(claDes),
    field_and_modes(someFieldNames),
    editMap()
{
    }


CreateWizardPage::CreateWizardPage(
        QList<int>someFielIndex,
        Markov_IO::ClassDescription* claDes):
    des(claDes),
    field_and_modes(),
    editMap()
{
    for (int i=0; i<someFielIndex.size(); ++i)
    {
        field_and_modes.append(QString(claDes->ElementName(someFielIndex.at(i)).c_str()));

    }

}


CreateWizardPage::CreateWizardPage(
        Markov_IO::ClassDescription* claDes):
    des(claDes),
    field_and_modes(),
    editMap()
{
    for (std::size_t i=0; i<claDes->size(); ++i)
    {
        field_and_modes.append(QString(claDes->ElementName(i).c_str()));

    }

}





void CreateWizardPage::initializePage()
{
   QVBoxLayout *mainLayout=new QVBoxLayout;
   for (int i=0; i<field_and_modes.size(); ++i)
    {
       QStringList modeList=field_and_modes.at(i).split(",");
       QString fieldName=modeList.at(0);
       modeList.removeFirst();
       if (des->HasElementName(fieldName.toStdString()))
        {
            EditWizardField* editField=EditWizardField::create(fieldName,modeList,des);
            if (editField)
            {
                mainLayout->addWidget(editField);
                connect(editField,SIGNAL(valueChanged()),this,SIGNAL(completeChanged()));

                editMap[fieldName]=editField;
            }
        }
    }
    setLayout(mainLayout);
}


bool CreateWizardPage::isComplete()const
{
    for (int i=0;i<field_and_modes.size();++i)
        {
            QString fieldName=field_and_modes.at(i).split(",").at(0);
            EditWizardField* ef=editMap[fieldName];
            if (!(ef->isValid()))
            {
                return false;
            }
        }
    return true;
}


CreateQ_Markov_ModelPage0::CreateQ_Markov_ModelPage0(Markov_IO::ClassDescription* claDes):
    CreateWizardPage(QList<int>()<<0,claDes)
{

}
void CreateQ_Markov_ModelPage0::initializePage()
{
    CreateWizardPage::initializePage();
    QSpinBox *numberStatesBox=new QSpinBox;
    QLabel* statesLabel = new QLabel(tr("&Number of states:"));
    statesLabel->setBuddy(numberStatesBox);
    statesLabel->setToolTip("number of states that are recongizible for the model");
    statesLabel->setWhatsThis("this number is used to build the vectors and matrices "
                              "that define the model");


    QHBoxLayout* hLayout=new QHBoxLayout;
    hLayout->addWidget(statesLabel);
    hLayout->addWidget(numberStatesBox);
    connect(numberStatesBox,SIGNAL(valueChanged(int)),this,SLOT(setNumStates(int)));
    connect(numberStatesBox,SIGNAL(valueChanged(int)),this,SIGNAL(completeChanged()));

    static_cast<QVBoxLayout*>(layout())->addLayout(hLayout);

}

bool CreateQ_Markov_ModelPage0::isComplete() const
{
    if (!CreateWizardPage::isComplete())
        return false;
    bool numStates_gretearThanZero=numStates>0;
    bool name_nonEmpty=!des->ElementValue(0).empty();

    return numStates_gretearThanZero&name_nonEmpty;
  }



bool CreateQ_Markov_ModelPage0::validatePage()
{
  /*  const Markov_IO::ABC_Object* o=(*des)["Q_matrix"];

    const Markov_IO::Object<Markov_LA::M_Matrix<double> > * obj;
    obj=static_cast< const Markov_IO::Object<Markov_LA::M_Matrix<double> >* >(o);
    std::size_t old_numberStates=Markov_LA::ncols(obj->Value());

    std::string name=des->ElementValue(0);
    if (numStates!=old_numberStates)
    {
        *des=Markov_Mol::Q_Markov_Model(name,numStates).GetDescription();
    }
    return true;
*/
}

void CreateQ_Markov_ModelPage0::setNumStates(int numstates)
{
    numStates=numstates;
}







Create_Pulses_program_Page0::Create_Pulses_program_Page0(
        Markov_IO::ClassDescription* claDes):
      CreateWizardPage(
          QStringList("name")<<"number_of_traces"<<"number_of_repetitions",
                       claDes)
  {
  }

bool Create_Pulses_program_Page0::validatePage()
{
   // it just erases what it was there before
    std::string name;
    Markov_IO::ToValue((*des)["name"],name);
    std::size_t numTraces;
    Markov_IO::ToValue((*des)["number_of_traces"],numTraces);

    std::size_t number_of_repetitions;
    Markov_IO::ToValue((*des)["number_of_repetitions"],number_of_repetitions);



    *des=Markov_IO::Pulses_program(
                name,numTraces,number_of_repetitions).GetDescription();

    return true;


}
bool Create_Pulses_program_Page0::isComplete()const{

    bool name_nonEmpty=!des->ElementValue(0).empty();

    std::size_t numTraces;
    Markov_IO::ToValue((*des)["number_of_traces"],numTraces);
    bool numTraces_gretearThanZero=numTraces>0;

    std::size_t number_of_repetitions;
    Markov_IO::ToValue((*des)["number_of_repetitions"],number_of_repetitions);
    bool number_of_repetitions_gretearThanZero=number_of_repetitions>0;


    return numTraces_gretearThanZero &
            name_nonEmpty &
            number_of_repetitions_gretearThanZero;
}


Create_Pulses_program_Page1::
Create_Pulses_program_Page1(Markov_IO::ClassDescription* claDes):
    CreateWizardPage(QStringList(),claDes){}

void Create_Pulses_program_Page1::
initializePage()
{
    QVBoxLayout *mainLayout=new QVBoxLayout;
    std::size_t number_of_traces;
    ToValue((*des)["number_of_traces"],number_of_traces);
    for (std::size_t i=0;i<number_of_traces;++i)
    {
        std::string fieldName="traces_"+Markov_IO::ToString(i);
        QString fieldNameQ(fieldName.c_str());
        QStringList modeList;
        field_and_modes.append(fieldNameQ);
        if (des->HasElementName(fieldName))
        {
            EditWizardField* editField=EditWizardField::create(fieldNameQ,modeList,des);
            if (editField)
            {
                mainLayout->addWidget(editField);
                connect(editField,SIGNAL(valueChanged()),this,SIGNAL(completeChanged()));

                editMap[fieldNameQ]=editField;
            }
        }
    }
    setLayout(mainLayout);

}



Create_Pulses_program_Page2::
Create_Pulses_program_Page2(Markov_IO::ClassDescription* claDes):
    CreateWizardPage(
        QStringList("sequence_of_traces")<<"concentration_of_each_trace",
        claDes){}


Create_Pulses_trace_Page0::
Create_Pulses_trace_Page0(Markov_IO::ClassDescription* claDes):
    CreateWizardPage(
        QStringList("name")<<"number_of_concentration_changes",
        claDes){}




bool Create_Pulses_trace_Page0::isComplete()const
{
    if (!CreateWizardPage::isComplete())
        return false;
    std::size_t number_of_concentration_changes;
    if(!ToValue((*des)["number_of_concentration_changes"],number_of_concentration_changes))
        return false;
    if (number_of_concentration_changes>0)
        return true;
    return false;

}
bool Create_Pulses_trace_Page0::validatePage()
{
    // it just erases what it was there before
    std::string name;
    if (!ToValue((*des)["name"],name))
    return false;

    std::size_t number_of_concentration_changes;
     Markov_IO::ToValue((*des)["number_of_concentration_changes"],number_of_concentration_changes);
     Markov_LA::M_Matrix<double> time_of_each_pulse;
     Markov_IO::ToValue((*des)["time_of_each_concentration_change"],time_of_each_pulse);

     bool toReWrite=number_of_concentration_changes!=Markov_LA::size(time_of_each_pulse);

     if (toReWrite)
     *des=Markov_IO::Pulses_trace(
                 name,number_of_concentration_changes).GetDescription();

     return true;

}

Create_Pulses_trace_Page1::Create_Pulses_trace_Page1(Markov_IO::ClassDescription* claDes):
    CreateWizardPage(
        QStringList("trace_duration")
        <<"time_to_next_trace"
       <<"frequency_of_sampling"
         <<"sub_step_time"
        <<"time_to_exchange",
        claDes){}

bool Create_Pulses_trace_Page1::isComplete()const
{
    double trace_duration;
    if(!ToValue((*des)["trace_duration"],trace_duration))
    return false;

    double time_to_next_trace;
    if(!ToValue((*des)["time_to_next_trace"],time_to_next_trace))
    return false;

    double frequency_of_sampling;
    if(!ToValue((*des)["frequency_of_sampling"],frequency_of_sampling))
    return false;

    double sub_step_time;
    if(!ToValue((*des)["sub_step_time"],sub_step_time))
    return false;

    double time_to_exchange;
    if(!ToValue((*des)["time_to_exchange"],time_to_exchange))
    return false;

    if (!trace_duration>0)
        return false;

    if (!time_to_next_trace>0)
        return false;
    if (!frequency_of_sampling>0)
        return false;
    if (!sub_step_time>0)
        return false;

    if (time_to_exchange<0)
        return false;

    if (frequency_of_sampling*trace_duration<2)
        return false;
    return true;
  }

Create_Pulses_trace_Page2::Create_Pulses_trace_Page2(Markov_IO::ClassDescription* claDes):
    CreateWizardPage(
        QStringList("time_of_each_concentration_change")
        <<"concentration_of_each_change",
        claDes){}

bool Create_Pulses_trace_Page2::isComplete()const
{
    Markov_LA::M_Matrix<double> time_of_each_concentration_change;
    if (!ToValue((*des)["time_of_each_concentration_change"],time_of_each_concentration_change))
    return false;


    Markov_LA::M_Matrix<double> concentration_of_each_pulse;
    if (!ToValue((*des)["concentration_of_each_change"],
         concentration_of_each_pulse))
    return false;


    double trace_duration;
    if(!ToValue((*des)["trace_duration"],trace_duration))
    return false;

    if(! (time_of_each_concentration_change>=0.0))
        return false;
    if(! (time_of_each_concentration_change<=trace_duration))
        return false;
    if(! (concentration_of_each_pulse>=0.0))
        return false;
    return true;

}



Create_Single_Pulses_Page0::
Create_Single_Pulses_Page0(Markov_IO::ClassDescription* claDes):
    CreateWizardPage(
        QStringList("name")
        <<"time_of_pulse"
       <<"pulse_duration"
        <<"control_duration"
       <<"trace_duration",
        claDes){}

bool Create_Single_Pulses_Page0::isComplete()const
{
    std::string name;
    if (!ToValue((*des)["name"],name))
    return false;

    double time_of_pulse;
    if (!ToValue((*des)["time_of_pulse"],time_of_pulse))
    return false;
    bool time_of_pulse_within_limits=(time_of_pulse>=0);


    double pulse_duration;
    if (!ToValue((*des)["pulse_duration"],pulse_duration))
    return false;

    double control_duration;
    if (!ToValue((*des)["control_duration"],control_duration))
    return false;

    double trace_duration;
    if (!ToValue((*des)["trace_duration"],trace_duration))
    return false;



    bool pulse_duration_within_limits=(pulse_duration+time_of_pulse<trace_duration)&&
            (pulse_duration>0);

    bool control_duration_within_limits=(control_duration+time_of_pulse<trace_duration)&&
            (control_duration>0);


return  control_duration_within_limits &&
        pulse_duration_within_limits &&
        time_of_pulse_within_limits;


}


Create_Single_Pulses_Page1::
Create_Single_Pulses_Page1(Markov_IO::ClassDescription* claDes):
    CreateWizardPage(
        QStringList("frequency_of_sampling")
        <<"number_of_pulse_concentrations"
       <<"pulse_concentration"
       <<"control_concentration"
       <<"time_to_exchange"
      <<"trace_interval"
     <<"sub_step_time",
        claDes){}

bool Create_Single_Pulses_Page1::isComplete()const
{

    double trace_duration;
    if (!ToValue((*des)["trace_duration"],trace_duration))
    return false;

    std::size_t number_of_pulse_concentrations;
    if (!ToValue((*des)["number_of_pulse_concentrations"],number_of_pulse_concentrations))
    return false;


    Markov_LA::M_Matrix<double> pulse_concentration;
    if (!ToValue((*des)["pulse_concentration"],pulse_concentration))
    return false;

    if (number_of_pulse_concentrations!= Markov_LA::ncols(pulse_concentration))
    {
        Markov_LA::M_Matrix<double> new_pulse_concentration(1,number_of_pulse_concentrations);
        for (std::size_t i=0; i<number_of_pulse_concentrations;++i)
            if (i<Markov_LA::nrows(pulse_concentration))
                new_pulse_concentration(0,i)=pulse_concentration(0,i);
            else
                new_pulse_concentration(0,i)=0;
        Markov_IO::Object<Markov_LA::M_Matrix<double> > o(new_pulse_concentration);
        des->ReplaceElement("pulse_concentration",o);
        editMap["pulse_concentration"]->resetModel();
        pulse_concentration=new_pulse_concentration;

    }


    bool concetrations_greater_than_zero=pulse_concentration>0.0;

    double control_concentration;
    if (!ToValue((*des)["control_concentration"],control_concentration))
    return false;

    bool control_concentration_positive=control_concentration>0;


    double trace_interval;
    if (!ToValue((*des)["trace_interval"],trace_interval))
    return false;
    bool trace_interval_positive=trace_interval>0;


    double frequency_of_sampling;
    if (!ToValue((*des)["frequency_of_sampling"],frequency_of_sampling))
    return false;
    bool frequency_of_sampling_10x_duration=frequency_of_sampling*trace_duration>10;


    double time_to_exchange;
    if (!ToValue((*des)["time_to_exchange"],time_to_exchange))
    return false;
    bool time_to_exchange_nonNegative=time_to_exchange>=0;


    double sub_step_time;
    if (!ToValue((*des)["sub_step_time"],sub_step_time))
    return false;
    bool sub_step_time_non_less_measure_time=sub_step_time*frequency_of_sampling<=1;


   return   concetrations_greater_than_zero &&
           control_concentration_positive&&
                   trace_interval_positive &&
   time_to_exchange_nonNegative &&
           sub_step_time_non_less_measure_time &&
           frequency_of_sampling_10x_duration;
}


Create_Experiment_Page0::
Create_Experiment_Page0(Markov_IO::ClassDescription* claDes):
    CreateWizardPage(
        QStringList("name")<<"number_of_traces"<<"number_of_repetitions",
                     claDes)
{
}

bool Create_Experiment_Page0::validatePage()
{
   // it just erases what it was there before
    std::string name;
    Markov_IO::ToValue((*des)["name"],name);
    std::size_t numTraces;
    Markov_IO::ToValue((*des)["number_of_traces"],numTraces);


    *des=Markov_IO::Experiment(
                name,
                std::vector<Markov_IO::Trace>(
                    numTraces,Markov_IO::Trace("",Markov_LA::zeros<double>(1,2),
                                     Markov_LA::zeros<double>(1,2),
                    0))
                ).GetDescription();

    return true;


}
bool Create_Experiment_Page0::isComplete()const{

    bool name_nonEmpty=!des->ElementValue(0).empty();

    std::size_t numTraces;
    Markov_IO::ToValue((*des)["number_of_traces"],numTraces);
    bool numTraces_gretearThanZero=numTraces>0;

     return numTraces_gretearThanZero &
            name_nonEmpty;
}


Create_Experiment_Page1::
Create_Experiment_Page1(Markov_IO::ClassDescription* claDes):
    CreateWizardPage(QStringList(),claDes){}

void Create_Experiment_Page1::
initializePage()
{
    QVBoxLayout *mainLayout=new QVBoxLayout;
    std::size_t number_of_traces;
    ToValue((*des)["number_of_traces"],number_of_traces);
    for (std::size_t i=0;i<number_of_traces;++i)
    {
        std::string fieldName="traces_"+Markov_IO::ToString(i);
        QString fieldNameQ(fieldName.c_str());
        QStringList modeList;
        field_and_modes.append(fieldNameQ);
        if (des->HasElementName(fieldName))
        {
            EditWizardField* editField=EditWizardField::create(fieldNameQ,modeList,des);
            if (editField)
            {
                mainLayout->addWidget(editField);
                connect(editField,SIGNAL(valueChanged()),this,SIGNAL(completeChanged()));

                editMap[fieldNameQ]=editField;
            }
        }
    }
    setLayout(mainLayout);

}

