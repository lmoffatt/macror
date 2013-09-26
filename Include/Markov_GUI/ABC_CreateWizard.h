#ifndef CREATEWIZARD_H
#define CREATEWIZARD_H
#include <QWizard>
#include <QString>
#include <QSpinBox>
#include <QObject>
#include <QMap>


#include "Markov_GUI/MacrorCommandWindow.h"
#include "Markov_GUI/EditWizardField.h"

class QLabel;
class QComboBox;
class QTableWidget;
class QDialogButtonBox;

class CreateWizard: public QWizard
{
    Q_OBJECT
public:

    static CreateWizard* create(Markov_IO::ClassDescription* claDes,
                                QWidget* parent=0);

    static CreateWizard* create(QString className,
                                Markov_IO::ClassDescription* claDes,
                                QWidget* parent=0);
protected:
    CreateWizard(Markov_IO::ClassDescription* claDes,
                 QWidget* parent=0);
     Markov_IO::ClassDescription* desc;

 };



class CreateQ_Markov_ModelWizard: public CreateWizard
{
    Q_OBJECT
public:
    CreateQ_Markov_ModelWizard(Markov_IO::ClassDescription* claDes,
                 QWidget* parent=0);

 };


class SelectStringWizardPage:public QWizardPage
{
    Q_OBJECT
public:
    SelectStringWizardPage(QStringList* someStrings,QString* selectedString);

    void initializePage();
    bool validatePage();
private slots:
    void setString(int i);

protected:
    QStringList* list_;
    QString* str_;
};



class CreateWizardPage:public QWizardPage
{
    Q_OBJECT
public:
    CreateWizardPage(QList<QString>someFieldNames,Markov_IO::ClassDescription* claDes);
    CreateWizardPage(QList<int>someFieldIndex,Markov_IO::ClassDescription* claDes);

    void initializePage();

protected:
    Markov_IO::ClassDescription* des;
    QList<QString> fieldNames;
    QMap<QString,EditWizardField*> editMap ;
private:
    void init();
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

class CreateQ_Markov_ModelPage1:public CreateWizardPage
{
    Q_OBJECT
public:
    CreateQ_Markov_ModelPage1(Markov_IO::ClassDescription* claDes);

    void initializePage();
    bool isComplete()const;
};

class CreateQ_Markov_ModelPage2:public CreateWizardPage
{
    Q_OBJECT
public:
    CreateQ_Markov_ModelPage2(Markov_IO::ClassDescription* claDes);

    void initializePage();
     bool isComplete()const;

};





#endif // CREATEWIZARD_H
