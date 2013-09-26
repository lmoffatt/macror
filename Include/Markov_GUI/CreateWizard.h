#ifndef CREATEWIZARD_H
#define CREATEWIZARD_H
#include <QWizard>
#include <QString>
#include <QSpinBox>
#include <QObject>
#include <QMap>

#include <string>

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


    CreateWizard(QString* className,
                 Markov_IO::ClassDescription* claDes,
                 Markov_IO::ABC_Saveable** s,
                 QWidget* parent=0);

    CreateWizard(QStringList classNames,
                 QString* className,
                 Markov_IO::ClassDescription* claDes,
                 Markov_IO::ABC_Saveable** s,
                 QWidget* parent=0);

    void accept();
    QString getClassName()const;
    void setClassName(const QString& newClassName);

protected:
    Markov_IO::ClassDescription* desc;
    Markov_IO::ABC_Saveable** sptr;
    QString* myClassName;
private:
    friend class SelectStringWizardPage;
    void initselect();

    void init_Q_Markov_Model();
    void init_Pulses_program();
    void init_Pulses_trace();


    void init_Trace();


    void init_Experiment();
    void init_Single_Pulses();
    void init_Single_Pulses2();
    void init_Random_Pulses();
    void init_ExperimentData();
    void init_Experiment_simulation();
    void init_Experiment_Average();
    void init_LikelihoodEvaluation();
    void init_OptimizationResult();
    void init_SingleOptimizationResult();
    void init_ClassDescription();
    void init_PatchModel();
    void init_gaussian_noise();
    void init_Parameters();





    void acceptQ_Markov_Model();
    void accept_Pulses_program();
    void accept_Pulses_trace();

    void accept_Trace();
    void accept_Experiment();
    void accept_Single_Pulses();
    void accept_Single_Pulses2();
    void accept_Random_Pulses();
    void accept_ExperimentData();
    void accept_Experiment_simulation();
    void accept_Experiment_Average();
    void accept_LikelihoodEvaluation();
    void accept_OptimizationResult();
    void accept_SingleOptimizationResult();
    void accept_LikelihoodOptions();
    void accept_Markov_Likelihood_Options();
    void accept_PatchModel();
    void accept_gaussian_noise();
    void accept_Parameters();



};







#endif // CREATEWIZARD_H
