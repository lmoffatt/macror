#ifndef ABC_VAR_GUI_H
#define ABC_VAR_GUI_H
#include <QWidget>
#include <QObject>
#include <QBoxLayout>
#include <QComboBox>
#include <QDialog>


//#include "Markov_IO/ClassDescription.h"
#include "Markov_IO/ABC_Var.h"
#include "Markov_LA/Matrix.h"

class QTableView;
class QLineEdit;
class QSpinBox;



namespace Markov_IO {

  inline bool toValue( Token_Buffer &tok,
                      QString &val)
  {
    tok.tokenAdvance(1);
    if (!(tok.pos()<tok.size())) return false;
    if (tok.currToken().tok()!=Token_New::IDENTIFIER)
      return false;
    else
      {
        val=tok.currToken().str().c_str();
        ++tok;
        return true;
      }
  }

  inline Token_Buffer& operator<<(Token_Buffer& tok,
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

  template<>
  inline std::string Implements_Simple_Value<QString>::ClassName()
  {
    return "QString";
  }

  template
  class Implements_Simple_Value<QString>;





}


namespace Markov_GUI {





  class EditField:public QWidget
  {
    Q_OBJECT
  public:

    static EditField* create(QWidget *parent, Markov_IO::ABC_Value* v);

    virtual ~EditField(){}

    virtual bool isValid()const;

    virtual int nGridColumnsHint()const
    {
      return 1;
    }
    virtual int nGridRowsHint()const
    {
      return 1;
    }


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

    EditField(QWidget* parent,Markov_IO::ABC_Value* av);
    Markov_IO::ABC_Value* var_;
  };

  class EditFieldMatrixDoubles: public EditField
  {
    Q_OBJECT
  public:
    virtual ~EditFieldMatrixDoubles(){}

    virtual bool isValid()const;
  public slots:
    void updateValue();
    void resetModel();
    friend class EditField;
     void moveToCell(int i, int j);

    void resetRowCount(int newRowCount);
    void resetColumnCount(int newRowCount);

    virtual int nGridColumnsHint()const;
    virtual int nGridRowsHint()const;


  protected slots:
    virtual void copy();
    virtual void paste();


  protected:
    EditFieldMatrixDoubles(QWidget* parent,Markov_IO::ABC_Value *av);
    Markov_IO::Implements_Simple_Value<Markov_LA::M_Matrix<double>>* v;
    QTableView *table;
    bool rowsExpandable;
    bool columnExpandable;

  };




  class EditWizard_Complex_Var: public EditField
  {
    Q_OBJECT
  public:
    virtual ~EditWizard_Complex_Var(){}
    bool isValid()const;
  public slots:
    void editMe();
    void updateValue();
    friend class EditField;
  protected:
    EditWizard_Complex_Var(QWidget* parent,Markov_IO::ABC_Value *av);
  private:
    Markov_IO::Implements_Complex_Value* cvar_;

    bool isvalid;
    QLineEdit *lineEdit;
  };

  class EditWizardMatrixSizes: public EditField
  {
    Q_OBJECT
  public:
    virtual ~EditWizardMatrixSizes(){}
    int nGridColumnsHint() const;
    int nGridRowsHint() const;
  public slots:
    void updateValue();
    friend class EditField;
  protected slots:
    virtual void copy(){}


    virtual void paste(){}

  protected:
    EditWizardMatrixSizes(QWidget* parent,Markov_IO::ABC_Value *av);
    Markov_IO::Implements_Simple_Value<Markov_LA::M_Matrix<std::size_t>>* v;
    QTableView *table;
  };

  class EditWizardDouble: public EditField
  {
    Q_OBJECT
  public:
    virtual ~EditWizardDouble(){}

    bool isValid()const;
  public slots:
    void updateValue();
    friend class EditField;

  protected:
    EditWizardDouble(QWidget* parent,Markov_IO::ABC_Value *av);
    Markov_IO::Implements_Simple_Value<double>* v;
    QLineEdit* lineEdit;
    double d_;

  };


  class EditWizardSize: public EditField
  {
    Q_OBJECT
  public:
    virtual ~EditWizardSize(){}
  protected slots:
    virtual void copy(){}


    virtual void paste(){}

  public slots:
    void updateValue();
    friend class EditField;
  protected:
    EditWizardSize(QWidget* parent,Markov_IO::ABC_Value *av);
    Markov_IO::Implements_Simple_Value<std::size_t>* v;
    QSpinBox* spinBox;
    std::size_t s_;

  };


  class EditWizardBool: public EditField
  {
    Q_OBJECT
  public:
    virtual ~EditWizardBool(){}
  protected slots:
    virtual void copy(){}


    virtual void paste(){}

  public slots:
    void updateValue();
    friend class EditField;
  protected:
    EditWizardBool(QWidget* parent,Markov_IO::ABC_Value *av);
    Markov_IO::Implements_Simple_Value<bool>* v;
    QComboBox* comboBox;
    bool b_;

  };


  class EditWizardString: public EditField
  {
    Q_OBJECT
  public:
    virtual ~EditWizardString(){}
    bool isValid()const;

  public slots:
    void updateValue();
    friend class EditField;
  protected:

    EditWizardString(QWidget* parent,Markov_IO::ABC_Value *av);
    Markov_IO::Implements_Simple_Value<std::string>* v;
    std::string str_;
    QLineEdit* lineEdit;

  };



  class  EditVariableDialog: public QDialog
  {
  public:
    EditVariableDialog(QWidget*parent,
                       Markov_IO::ABC_Value* var):
    QDialog(parent),
      v_(var)
    {


      QGridLayout* fieldsLayout=new QGridLayout;

      int row=0;

      for (std::size_t i=0; i<var->numChilds(); i++)
        {
          Markov_IO::ABC_Value * v=var->getChild(var->ith_ChildName(i));
          EditField* f=EditField::create(this,v);
          fieldsLayout->addWidget(f,row,1,f->nGridRowsHint()+1,f->nGridColumnsHint());
          row+=f->nGridRowsHint()+1;

        }

      this->setLayout(fieldsLayout);

    }

   private:
    Markov_IO::ABC_Value* v_;

  };






}
#endif // ABC_VAR_GUI_H
