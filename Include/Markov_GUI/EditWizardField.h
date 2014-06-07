#ifndef EDITWIZARDFIELD_H
#define EDITWIZARDFIELD_H
#include <QWidget>
#include <QObject>
#include <QBoxLayout>
#include <QComboBox>

#include "Markov_IO/ClassDescription.h"
#include "Markov_LA/Matrix.h"

class QTableView;
class QLineEdit;
class QSpinBox;

class EditWizardField:public QWidget
{
    Q_OBJECT
public:
    enum Constrain
    {
        NON_ZERO,
        POSITIVE,
        Q_Matrix
    };

    static EditWizardField* create(QString fieldName,
                                   QStringList modeList,
                                   Markov_IO::ClassDescription* cd);

    virtual ~EditWizardField(){}

    virtual void setConstraint(Constrain ){;}
 //   virtual void relieveConstrain(Constrain someContrain){}
    virtual bool isValid()const;



 signals:
    void valueChanged();

 public slots:
    virtual void updateValue()=0;

    virtual void resetModel(){}


protected slots:
    virtual void copy(){}


    virtual void paste(){}

protected:
    virtual void keyPressEvent(QKeyEvent * event);

    EditWizardField(QString fieldName,
                    QStringList modeList,
                    Markov_IO::ClassDescription* cd,
                    QWidget* pw=0 );
    QString field;
    QStringList mode;
    Markov_IO::ClassDescription* desc;

};

class EditWizardMatrixDoubles: public EditWizardField
{
    Q_OBJECT
public:
virtual ~EditWizardMatrixDoubles(){}

    virtual bool isValid()const;
 public slots:
    void updateValue();
    void resetModel();
    friend class EditWizardField;
    void setConstraint(Constrain someConstrain);
    void moveToCell(int i, int j);

    void resetRowCount(int newRowCount);
    void resetColumnCount(int newRowCount);

protected slots:
    virtual void copy();
    virtual void paste();


protected:
    EditWizardMatrixDoubles(QString fieldName,
                            QStringList modeList,
                            Markov_IO::ClassDescription* cd);
    Markov_LA::M_Matrix<double> md_;
    QTableView *table;
    bool rowsExpandable;
    bool columnExpandable;

 };




class EditWizardSaveable: public EditWizardField
{
    Q_OBJECT
public:
virtual ~EditWizardSaveable(){}
    bool isValid()const;
 public slots:
    void editMe();
    void updateValue();
 friend class EditWizardField;
 protected:
    EditWizardSaveable(QString fieldName,
                       QStringList modeList,
                            Markov_IO::ClassDescription* cd);

    Markov_IO::ClassDescription desField;
private:
    bool isvalid;
    QLineEdit *lineEdit;
};

class EditWizardMatrixSizes: public EditWizardField
{
    Q_OBJECT
public:
virtual ~EditWizardMatrixSizes(){}
 public slots:
    void updateValue();
friend class EditWizardField;
protected slots:
    virtual void copy(){}


    virtual void paste(){}

protected:
    EditWizardMatrixSizes(QString fieldName,
                          QStringList modeList,
                            Markov_IO::ClassDescription* cd);
    Markov_LA::M_Matrix<std::size_t> ms_;

 };

class EditWizardDouble: public EditWizardField
{
    Q_OBJECT
public:
virtual ~EditWizardDouble(){}

    bool isValid()const;
 public slots:
    void updateValue();
friend class EditWizardField;

protected:
    EditWizardDouble(QString fieldName,
                     QStringList modeList,
                            Markov_IO::ClassDescription* cd);
    QLineEdit* lineEdit;
    double d_;

 };


class EditWizardSize: public EditWizardField
{
    Q_OBJECT
public:
virtual ~EditWizardSize(){}
protected slots:
    virtual void copy(){}


    virtual void paste(){}

 public slots:
    void updateValue();
friend class EditWizardField;
protected:
    EditWizardSize(QString fieldName,
                   QStringList modeList,
                            Markov_IO::ClassDescription* cd);
    QSpinBox* spinBox;
    std::size_t s_;

 };


class EditWizardBool: public EditWizardField
{
    Q_OBJECT
public:
virtual ~EditWizardBool(){}
protected slots:
    virtual void copy(){}


    virtual void paste(){}

 public slots:
    void updateValue();
friend class EditWizardField;
protected:
    EditWizardBool(QString fieldName,
                   QStringList modeList,
                            Markov_IO::ClassDescription* cd);
    QComboBox* comboBox;
    bool b_;

 };


class EditWizardString: public EditWizardField
{
    Q_OBJECT
public:
virtual ~EditWizardString(){}
    bool isValid()const;

 public slots:
    void updateValue();
friend class EditWizardField;
protected slots:
void browse();
protected:

    EditWizardString(QString fieldName,
                     QStringList modeList,
                            Markov_IO::ClassDescription* cd);
    std::string str_;
    QLineEdit* lineEdit;

 };




#endif // EDITWIZARDFIELD_H
