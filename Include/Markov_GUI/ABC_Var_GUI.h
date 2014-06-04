#ifndef ABC_VAR_GUI_H
#define ABC_VAR_GUI_H
#include <QWidget>
#include <QObject>
#include <QBoxLayout>
#include <QComboBox>

#include "Markov_IO/ClassDescription.h"
#include "Markov_IO/ABC_Var.h"
#include "Markov_LA/Matrix.h"

class QTableView;
class QLineEdit;
class QSpinBox;



namespace Markov_IO {

  inline bool toValue(const std::deque<Token_New> &tok, QString &val, std::size_t &i)
  {
    if (!(i<tok.size())) return false;
    if (tok.at(i).tok()!=Token_New::IDENTIFIER)
      return false;
    else
      {
        val=tok.at(i).str().c_str();
        ++i;
        return true;
      }
  }

  inline std::deque<Token_New>& operator<<(std::deque<Token_New>& tok,
                                           const QString& text)
  {
    std::stringstream ss(text.toStdString());
    Token_New t;
    while (t.get(ss))
      {
        tok.push_back(t);
      }

    return tok;
  }


  template
  class Implements_Simple_Var<QString>;
  template<>
  inline std::string Implements_Simple_Var<QString>::ClassName()
  {
    return "QString";
  }

}


namespace Markov_GUI {





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
                                   Markov_IO::ClassDescription* cd,
                                   Markov_IO::ABC_Var* av);

    virtual ~EditWizardField(){}

    virtual void setConstraint(Constrain someConstrain){someConstrain;}
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
                    Markov_IO::ABC_Var* av,
                    QWidget* pw=0 );
    QString field;
    QStringList mode;
    Markov_IO::ClassDescription* desc;
    Markov_IO::ABC_Var* var_;

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
                            Markov_IO::ClassDescription* cd,
                            Markov_IO::ABC_Var *av);
    Markov_LA::M_Matrix<double> md_;
    QTableView *table;
    bool rowsExpandable;
    bool columnExpandable;

  };




  class EditWizard_Complex_Var: public EditWizardField
  {
    Q_OBJECT
  public:
    virtual ~EditWizard_Complex_Var(){}
    bool isValid()const;
  public slots:
    void editMe();
    void updateValue();
    friend class EditWizardField;
  protected:
    EditWizard_Complex_Var(QString fieldName,
                       QStringList modeList,
                       Markov_IO::ClassDescription* cd,
                           Markov_IO::ABC_Var *av);

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
                          Markov_IO::ClassDescription* cd, Markov_IO::ABC_Var *av);
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
                     Markov_IO::ClassDescription* cd, Markov_IO::ABC_Var *av);
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
                   Markov_IO::ClassDescription* cd, Markov_IO::ABC_Var *av);
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
                   Markov_IO::ClassDescription* cd, Markov_IO::ABC_Var *av);
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
                     Markov_IO::ClassDescription* cd,
                     Markov_IO::ABC_Var* av);
    std::string str_;
    QLineEdit* lineEdit;

  };





}
#endif // ABC_VAR_GUI_H
