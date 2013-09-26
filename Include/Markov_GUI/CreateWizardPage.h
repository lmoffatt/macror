#ifndef CREATEWIZARDPAGE_H
#define CREATEWIZARDPAGE_H
#include <QObject>
#include <QWizardPage>
#include <QList>
#include <QMap>
#include "Markov_GUI/EditWizardField.h"
#include "Markov_IO/ClassDescription.h"


class SelectStringWizardPage:public QWizardPage
{
    Q_OBJECT
public:
    SelectStringWizardPage(QStringList* someStrings,QString* selectedString);

    void initializePage();
    bool validatePage();
    virtual bool isComplete() const;

    int nextId()const;

private slots:
    void setString(int i);

protected:
    QStringList* list_;
    QString* str_;
    int nextId_;
};



class CreateWizardPage:public QWizardPage
{
    Q_OBJECT
public:
    CreateWizardPage(QList<QString>someFieldNames,Markov_IO::ClassDescription* claDes);
    CreateWizardPage(QList<int>someFieldIndex,Markov_IO::ClassDescription* claDes);
    CreateWizardPage(Markov_IO::ClassDescription* claDes);


    void initializePage();

    bool isComplete()const;

protected:
    Markov_IO::ClassDescription* des;
    QList<QString> field_and_modes;
    QMap<QString,EditWizardField*> editMap ;

};





class CreateQ_Markov_ModelPage0:public CreateWizardPage
{
    Q_OBJECT
public:
    CreateQ_Markov_ModelPage0(Markov_IO::ClassDescription* claDes);

    void initializePage();
    bool validatePage();
    bool isComplete()const;
private slots:
    void setNumStates(int);
protected:
    std::size_t numStates;
};



class Create_Pulses_program_Page0:public CreateWizardPage
{
    Q_OBJECT
public:
    Create_Pulses_program_Page0(Markov_IO::ClassDescription* claDes);

    bool isComplete()const;
    bool validatePage();
};



class Create_Pulses_program_Page1:public CreateWizardPage
{
    Q_OBJECT
public:
    Create_Pulses_program_Page1(Markov_IO::ClassDescription* claDes);
    void initializePage();
    bool isComplete()const{return true;}
    bool validatePage(){return true;}
};


class Create_Pulses_program_Page2:public CreateWizardPage
{
    Q_OBJECT
public:
    Create_Pulses_program_Page2(Markov_IO::ClassDescription* claDes);
    bool isComplete()const{return true;}

};



class Create_Pulses_trace_Page0:public CreateWizardPage
{
    Q_OBJECT
public:
    Create_Pulses_trace_Page0(Markov_IO::ClassDescription* claDes);

    bool isComplete()const;
    bool validatePage();
};



class Create_Pulses_trace_Page1:public CreateWizardPage
{
    Q_OBJECT
public:
    Create_Pulses_trace_Page1(Markov_IO::ClassDescription* claDes);

    bool isComplete()const;
};


class Create_Pulses_trace_Page2:public CreateWizardPage
{
    Q_OBJECT
public:
    Create_Pulses_trace_Page2(Markov_IO::ClassDescription* claDes);
    bool isComplete()const;

};




class Create_Single_Pulses_Page0:public CreateWizardPage
{
    Q_OBJECT
public:
    Create_Single_Pulses_Page0(Markov_IO::ClassDescription* claDes);

    bool isComplete()const;
};

class Create_Single_Pulses_Page1:public CreateWizardPage
{
    Q_OBJECT
public:
    Create_Single_Pulses_Page1(Markov_IO::ClassDescription* claDes);

    bool isComplete()const;
 };


class Create_Experiment_Page0:public CreateWizardPage
{
    Q_OBJECT
public:
    Create_Experiment_Page0(Markov_IO::ClassDescription* claDes);

    bool isComplete()const;
    bool validatePage();
};

class Create_Experiment_Page1:public CreateWizardPage
{
    Q_OBJECT
public:
    Create_Experiment_Page1(Markov_IO::ClassDescription* claDes);

    void initializePage();
 };



#endif // CREATEWIZARDPAGE_H
