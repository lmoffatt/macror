#ifndef CREATEQMODELWIZARD_H
#define CREATEQMODELWIZARD_H
#include <QWizard>
#include <QString>
#include <QSpinBox>
#include <QObject>

#include "Markov_GUI/MacrorCommandWindow.h"


class QLineEdit;
class QTableWidget;

class CreateQModelWizard:public QWizard
{
    Q_OBJECT
public:

    CreateQModelWizard(QString name, Markov_Console::Markov_CommandManager* command);

    void setAgonistVector(Markov_LA::M_Matrix<std::size_t> * a);
    void setConductanceVector(Markov_LA::M_Matrix<double> * g);
    void setQMatrix(const Markov_LA::M_Matrix<double> &Q);



 void  accept();
private:
   QString alias;

   Markov_Console::Markov_CommandManager*  cm_;

   Markov_LA::M_Matrix<std::size_t>* a_;
   Markov_LA::M_Matrix<double>* g_;
   Markov_LA::M_Matrix<double> Q_;


};

class CreateQModelPage0:public QWizardPage
{
    Q_OBJECT
public:
    CreateQModelPage0(QWidget *parent=0);
    bool validatePage();



signals:
    void numberOfStates(int n);


private:
    QLineEdit* nameEdit;
    QSpinBox *numberStates;


};

class CreateQModelPage1:public QWizardPage
{
    Q_OBJECT
public:
    CreateQModelPage1(QWidget *parent=0);
   void initializePage();
   bool validatePage();



public slots:
    void setNumberStates(int n);
    void aca();

protected:
    virtual CreateQModelWizard* wizard();

private:
    QTableWidget* agonistVector;
    QDoubleSpinBox* gammaSB;
    QTableWidget *conductanceVector;
    Markov_LA::M_Matrix<double> g;
    Markov_LA::M_Matrix<std::size_t> a;




};


class CreateQModelPage2:public QWizardPage
{
    Q_OBJECT
public:
    CreateQModelPage2(QWidget *parent=0);
   void initializePage();
   bool validatePage();


protected:
    virtual CreateQModelWizard* wizard();

protected slots:
   void setKij(int i, int j);
   void updateDiag(int i);
private:
    QTableWidget* QMatrixTable;
    Markov_LA::M_Matrix<double> Q;
 };



#endif // CREATEQMODELWIZARD_H
