#include <QTableView>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <string>
#include <QFileDialog>
#include <QHeaderView>
#include <QDebug>

#include "Markov_IO/Object.h"
#include "Markov_IO/auxiliarIO.h"

#include "Markov_GUI/ABC_Var_GUI.h"
#include "Markov_GUI/ModelMatrix.h"
#include "Markov_GUI/CreateWizard.h"

#include "Markov_IO/ABC_Saveable.h"
#include "Markov_LA/matrixRelational.h"




namespace Markov_GUI {

  EditField::EditField(QWidget* parent):
    QWidget(parent){}

  bool EditField::isValid()const
  {
    return true;
  }

  void EditField::keyPressEvent(QKeyEvent * event)
  {
    if(event->matches(QKeySequence::Copy) )
      {
        copy();
      }
    else if(event->matches(QKeySequence::Paste) )
      {
        paste();
      }
    else
      {
        QWidget::keyPressEvent(event);
      }

  }




  EditField* EditField::create(QWidget *parent, Markov_IO::ABC_Value* v)
  {
    if (v==nullptr)
      return nullptr;
    if (v->complyClass(
          Markov_IO::Implements_Simple_Value<Markov_LA::M_Matrix<double> >::ClassName()))
      return new EditFieldMatrix(parent,v);
    else if (v->complyClass(
               Markov_IO::Implements_Simple_Value<Markov_LA::M_Matrix<std::size_t> >::ClassName()))
      return new EditFieldMatrix(parent,v);
    else if (v->complyClass(
               Markov_IO::Implements_Simple_Value<double >::ClassName()))
      return new EditFieldDouble(parent,v);
    else if (v->complyClass(
               Markov_IO::Implements_Simple_Value<std::size_t >::ClassName()))
      return new EditWizardSize(parent,v);
    else if (v->complyClass(
               Markov_IO::Implements_Simple_Value<bool>::ClassName()))
      return new EditWizardBool(parent,v);
    else if (v->complyClass(
               Markov_IO::Implements_Simple_Value<std::string>::ClassName()))
      return new EditWizardString(parent,v);
    else return nullptr;
  }


  EditFieldMatrix::EditFieldMatrix(QWidget* parent,
                                     Markov_IO::ABC_Value* av):
    EditField(parent ),
    v_(av),
    vard_(dynamic_cast<Markov_IO::Implements_Simple_Value<Markov_LA::M_Matrix<double>>*>(av)),
    vars_(dynamic_cast<Markov_IO::Implements_Simple_Value<Markov_LA::M_Matrix<size_t>>*>(av)),
    table(new QTableView)
  {


    if (av->complyModes("Q_Matrix"))
      {
        columnExpandable=false;
        rowsExpandable=false;
        ModelQMatrix *Qmodel;
        if (vard_)
          Qmodel=new ModelQMatrix(&vard_->refval());
        else if (vars_)
          Qmodel=new ModelQMatrix(&vars_->refval());
        table->setModel(Qmodel);
        connect(Qmodel,SIGNAL(moveToCell(int,int)),this,SLOT(moveToCell(int,int)));
      }
    else
      {
        if (vard_)
          table->setModel(new ModelMatrix(&vard_->refval()));
        else if (vars_)
          table->setModel(new ModelMatrix(&vars_->refval()));
        columnExpandable=false;
        rowsExpandable=false;
      }
    table->setItemDelegate(new LineEditDelegate);
    QStringList colTitles;
    auto   c=av->modes();

    for (std::string e:c)
      {
        if (e.find("ColTitle")!=e.npos)
          colTitles.push_back(e.c_str());
      }
    foreach (QString title,colTitles )
      {
        QStringList ti=title.split("_");
        bool ok;
        int i=ti.at(1).toInt(&ok);
        if (ok)
          table->model()->setHeaderData(i,Qt::Horizontal,ti.at(2));
      }



    QLabel* label=new QLabel(av->id().c_str());

    label->setToolTip(QString(av->Tip().c_str()));
    label->setWhatsThis(av->WhatThis().c_str());



    QGridLayout* myLayout=new QGridLayout;

    myLayout->addWidget(label,0,0,1,2,Qt::AlignLeft);
    /*
    if (!desc->Unit(i).empty())
      {
        QLabel* units=new QLabel(desc->Unit(i).c_str());
        myLayout->addWidget(units);
      }
*/
    auto var=av->myVarPtr();

    if ((var!=nullptr)
        &&(av->myVarPtr()->complyModes("ROW_INDEX"))
        &&(av->myVarPtr()->complyModes("COL_INDEX")))

      {

        if (av->myVarPtr()->complyModes("ROW_INDEX"))
          {
            if  (av->myVarPtr()->complyModes("COL_INDEX"))
              {
                QSpinBox* numCols=new QSpinBox(this);
                columnExpandable=true;

                numCols->setValue(table->model()->columnCount());
                numCols->setRange(0,1e3);
                numCols->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
                connect(numCols,SIGNAL(valueChanged(int)),this,SLOT(resetColumnCount(int)));
                QSpinBox* numRows=new QSpinBox(this);
                rowsExpandable=true;

                numRows->setValue(table->model()->rowCount());
                numRows->setRange(0,1e3);
                numRows->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
                connect(numRows,SIGNAL(valueChanged(int)),this,SLOT(resetRowCount(int)));
                myLayout->addWidget(numCols,1,2,1,2,Qt::AlignCenter);
                myLayout->addWidget(numRows,2,1,1,2,Qt::AlignCenter);

              }
            else
              {
                QSpinBox* numRows=new QSpinBox(this);
                rowsExpandable=true;

                numRows->setValue(table->model()->rowCount());
                numRows->setRange(0,1e3);
                numRows->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
                connect(numRows,SIGNAL(valueChanged(int)),this,SLOT(resetRowCount(int)));
                myLayout->addWidget(numRows,2,1,2,2,Qt::AlignCenter);
              }

          }
        else if (v_->myVarPtr()->complyModes("COL_INDEX"))
          {
            QSpinBox* numCols=new QSpinBox(this);
            columnExpandable=true;

            numCols->setValue(table->model()->columnCount());
            numCols->setRange(0,1e8);
            numCols->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
            connect(numCols,SIGNAL(valueChanged(int)),this,SLOT(resetColumnCount(int)));
            myLayout->addWidget(numCols,1,2,1,2,Qt::AlignCenter);
          }
        table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        table->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
        table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
        table->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);

        table->horizontalHeader()->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
        table->horizontalHeader()->sectionResizeMode(2);
        table->verticalHeader()->sectionResizeMode(2);
        table->verticalHeader()->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

        //      table->resizeColumnsToContents();
        //     table->resizeRowsToContents();

        myLayout->addWidget(table,2,3,
                            std::min(5,table->model()->rowCount()),
                            std::min(5,table->model()->columnCount()));

      }
    else
      {
        table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        table->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
        table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
        table->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);

        table->horizontalHeader()->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
        table->horizontalHeader()->sectionResizeMode(2);
        table->verticalHeader()->sectionResizeMode(2);
        table->verticalHeader()->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

        //  table->resizeColumnsToContents();
        //  table->resizeRowsToContents();
        myLayout->addWidget(table,2,3,
                            std::min(5,table->model()->rowCount()),
                            std::min(5,table->model()->columnCount()));

      }
    setLayout(myLayout);

    connect(table->itemDelegate(),SIGNAL(closeEditor(QWidget*)),this,SLOT(updateValue()));

  }



  void EditFieldMatrix::resetRowCount(int newRowCount)
  {
    int oldRowCount=table->model()->rowCount();
    if (newRowCount>oldRowCount)
      {
        table->model()->insertRows(oldRowCount,newRowCount-oldRowCount);
      }
    else if (newRowCount<oldRowCount)
      {
        table->model()->removeRows(newRowCount,oldRowCount-newRowCount);
      }
  }


  void EditFieldMatrix ::resetColumnCount(int newColumnCount)
  {
    int oldColumnCount=table->model()->columnCount();
    if (newColumnCount>oldColumnCount)
      {
        table->model()->insertColumns(oldColumnCount,newColumnCount-oldColumnCount);
      }
    else if (newColumnCount<oldColumnCount)
      {
        table->model()->removeColumns(newColumnCount,oldColumnCount-newColumnCount);
      }
  }


  int EditFieldMatrix ::nGridColumnsHint() const
  {
    int n=std::min(5,table->model()->columnCount());

    if(v_->myVarPtr()->complyModes("COL_INDEX"))  {++n;}
    return n;

  }


  int EditFieldMatrix ::nGridRowsHint() const
  {
    int n=std::min(5,table->model()->rowCount());
    if(v_->myVarPtr()->complyModes("ROW_INDEX"))  {++n;}
    return n;

  }




  bool EditFieldMatrix::isValid()const
  {
    if (v_!=nullptr)
      {
        if (v_->myVarPtr()->complyModes("NOT_ALL_ZERO"))
          {
            if (((vard_!=nullptr)&&(vard_->refval()==0.0))
                ||((vars_!=nullptr)&&(vard_->refval()==0.0)))
              return false;
          }
        if (v_->myVarPtr()->complyModes("Q_MATRIX"))
          {
            if (((vard_!=nullptr)&&(vard_->refval()==0.0))
                ||((vars_!=nullptr)&&(vard_->refval()==0.0)))
              return false;
            if (vard_!=nullptr)
            for (std::size_t i=0; i < Markov_LA::nrows(vard_->refval()); i++)
              {
                for (std::size_t j=i+1; j< Markov_LA::nrows(vard_->refval()); ++j)
                  {
                    if ((vard_->refval()(i,j)<0)||(vard_->refval()(j,i)<0))
                      return false;
                    if ((vard_->refval()(i,j)>0)&&(vard_->refval()(j,i)==0))
                      return false;
                    if ((vard_->refval()(j,i)>0)&&(vard_->refval()(i,j)==0))
                      return false;
                  }
              }
            else if (vars_!=nullptr)
              for (std::size_t i=0; i < Markov_LA::nrows(vars_->refval()); i++)
                {
                  for (std::size_t j=i+1; j< Markov_LA::nrows(vars_->refval()); ++j)
                    {
                      if ((vars_->refval()(i,j)<0)||(vars_->refval()(j,i)<0))
                        return false;
                      if ((vars_->refval()(i,j)>0)&&(vars_->refval()(j,i)==0))
                        return false;
                      if ((vars_->refval()(j,i)>0)&&(vars_->refval()(i,j)==0))
                        return false;
                    }
                }

          }
        return true;
      }

  }


  void EditFieldMatrix::copy()
  {
    QItemSelectionModel * selection = table->selectionModel();
    QModelIndexList indexes = selection->selectedIndexes();

    if(indexes.size() < 1)
      return;

    // QModelIndex::operator < sorts first by row, then by column.
    // this is what we need
    std::sort(indexes.begin(), indexes.end());

    // You need a pair of indexes to find the row changes
    QModelIndex previous = indexes.first();
    indexes.removeFirst();
    QString selected_text;
    QModelIndex current;
    Q_FOREACH(current, indexes)
      {
        QVariant data = table->model()->data(previous);
        QString text = data.toString();
        // At this point `text` contains the text in one cell
        selected_text.append(text);
        // If you are at the start of the row the row number of the previous index
        // isn't the same.  Text is followed by a row separator, which is a newline.
        if (current.row() != previous.row())
          {
            selected_text.append(QLatin1Char('\n'));
          }
        // Otherwise it's the same row, so append a column separator, which is a tab.
        else
          {
            selected_text.append(QLatin1Char('\t'));
          }
        previous = current;
      }

    // add last element1
    selected_text.append(table->model()->data(current).toString());
    selected_text.append(QLatin1Char('\n'));
    qApp->clipboard()->setText(selected_text);
  }


  void EditFieldMatrix ::paste()
  {
    QString selected_text = qApp->clipboard()->text();
    QStringList cells = selected_text.split(QRegExp(QLatin1String("\\n|\\t")));
    while(!cells.empty() && cells.back().size() == 0)
      {
        cells.pop_back(); // strip empty trailing tokens
      }
    int rows = selected_text.count(QLatin1Char('\n'));
    int cols = cells.size() / rows;
    if(cells.size() % rows != 0)
      {
        // error, uneven number of columns, probably bad data
        QMessageBox::critical(this, tr("Error"),
                              tr("Invalid clipboard data, unable to perform paste operation."));
        return;
      }


    QModelIndex idx=table->currentIndex();
    int icol=idx.column();
    int irow=idx.row();

    int ncol=table->model()->columnCount();
    int nrow=table->model()->rowCount();

    if(cols > ncol-icol)
      {
        if (columnExpandable)
          table->model()->insertColumns(ncol,cols-ncol+icol);
        else
          {
            QMessageBox::warning(this,tr("Warning"),tr("cannot paste all columns, boundaries reached"));
            cols=ncol-icol;
          }
      }

    if(rows > nrow-irow)
      {
        if (rowsExpandable)
          table->model()->insertRows(nrow,rows-nrow+idx.row());
      }
    else
      {
        QMessageBox::warning(this,tr("Warning"),tr("cannot paste all rows, boundaries reached"));
        rows=nrow-irow;
      }

    for(int i=0, icell=0; i < rows; ++i)
      {
        for(int j=0; j < cols; ++j, ++icell)
          {
            bool ok;
            double val=QVariant(cells[icell]).toDouble(&ok);
            if (ok)
              {
                table->model()->setData(idx.sibling(irow+i,icol+j),val);
              }
          }
      }
  }


  void EditFieldMatrix ::updateValue()
  {

    //    Markov_IO::Object<Markov_LA::M_Matrix<double> > od(md_);
    //    desc->ReplaceElement(field.toStdString(),od);

    emit valueChanged();
  }


  void EditFieldMatrix ::resetModel()
  {
    //    const Markov_IO::Object<Markov_LA::M_Matrix<double> > * od;
    //    const Markov_IO::ABC_Object *o=(*desc)[field.toStdString()];
    //    od=dynamic_cast<const Markov_IO::Object<Markov_LA::M_Matrix<double> > * > (o);
    //    md_=od->Value();

    if (vard_!=nullptr)
      vard_->reset();
    else if (vars_!=nullptr)
      vars_->reset();




  }


  void EditFieldMatrix ::moveToCell(int i, int j)
  {
    table->setCurrentIndex(table->currentIndex().sibling(i,j));
  }






  EditField_Complex_Var::EditField_Complex_Var(QWidget* parent,Markov_IO::ABC_Value *av):
    EditField(parent),
    var_(av),
    isvalid(false)
  {
    QLabel* label=new QLabel(var_->id().c_str());
    lineEdit=new QLineEdit(QString(var_->id().c_str()));
    lineEdit->setReadOnly(true);

    QPushButton* button=new QPushButton("&edit");
    label->setToolTip(var_->Tip().c_str());
    lineEdit->setToolTip(var_->Tip().c_str());
    label->setWhatsThis(var_->WhatThis().c_str());
    lineEdit->setWhatsThis(var_->WhatThis().c_str());

    QHBoxLayout* myLayout=new QHBoxLayout;
    myLayout->addWidget(label);
    myLayout->addWidget(lineEdit);
    myLayout->addWidget(button);
    setLayout(myLayout);
    connect(button,SIGNAL(clicked()),this,SLOT(editMe()));

  }


  void EditField_Complex_Var::editMe()
  {
    auto v=var_->to_PlainValue();
    EditVariableDialog* c=new EditVariableDialog(v);
    if (c->exec()==1)
      {

        /// FIXME: replace this with something!!
        //  cvar_->loadFromObjectValue(v);

        isvalid=true;
        lineEdit->setText(QString(var_->id().c_str()));
        update();

        emit valueChanged();
      }


  }
  void EditField_Complex_Var::updateValue()
  {

  }

  bool EditField_Complex_Var::isValid()const
  {
    return isvalid;
  }





  EditFieldDouble::EditFieldDouble(QWidget * parent,Markov_IO::ABC_Value*av):
    EditField(parent),
    var_(dynamic_cast < Markov_IO::Implements_Simple_Value<double>*>(av)),
    d_(var_?var_->value():Markov_LA::NaN())
  {
    lineEdit=new QLineEdit;
    QDoubleValidator* val=new QDoubleValidator;
    val->setDecimals(14);
    lineEdit->setValidator(val);
    lineEdit->setText(QString("%1").arg(d_,0,'g',14));
    lineEdit->setAlignment(Qt::AlignRight);


    QLabel* label=new QLabel(var_->id().c_str());

    label->setToolTip(QString(var_->Tip().c_str()));
    label->setWhatsThis(var_->WhatThis().c_str());

    QHBoxLayout* myLayout=new QHBoxLayout;
    myLayout->addWidget(label);
    myLayout->addStretch();

    myLayout->addWidget(lineEdit);
    //    if (!desc->Unit(i).empty())
    //      {
    //        QLabel* units=new QLabel(desc->Unit(i).c_str());
    //        myLayout->addWidget(units);
    //      }
    //    else
    //      {

    //        myLayout->addStretch();
    //      }
    myLayout->addStretch();

    setLayout(myLayout);
    connect(lineEdit,SIGNAL(textChanged(QString)),this,SLOT(updateValue()));

  }

  bool EditFieldDouble::isValid()const
  {
    if (var_->myVarPtr()->complyModes("NOT_ZERO"))
      {
        if (d_==0)
          return false;

      }
    return true;
  }

  void EditFieldDouble::updateValue()
  {

    QString label=lineEdit->text();
    bool ok;
    d_ =label.toDouble(&ok) ;
    if (ok)
      {
        var_->setValue(d_);
        emit valueChanged();
      }
    lineEdit->updateGeometry();
  }

  EditWizardSize::EditWizardSize(QWidget * parent,Markov_IO::ABC_Value*av):
    EditField(parent),
    var_(dynamic_cast < Markov_IO::Implements_Simple_Value<std::size_t>*>(av)),
    s_(var_!=nullptr ?var_->value():0)
  {

    spinBox=new QSpinBox;

    spinBox->setMaximum(var_->motherClassType()->maxValue());

    spinBox->setValue(s_);

    spinBox->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);


    QLabel* label=new QLabel(var_->id().c_str());

    label->setToolTip(QString(var_->Tip().c_str()));
    label->setWhatsThis(var_->WhatThis().c_str());


    QHBoxLayout* myLayout=new QHBoxLayout;

    myLayout->addWidget(label);
    myLayout->addStretch();
    myLayout->addWidget(spinBox);
    if (!var_->motherClassType()->units().empty())
      {
        QLabel* units=new QLabel(var_->motherClassType()->units().c_str());
        myLayout->addWidget(units);
      }
    else
      {
        myLayout->addStretch();
      }
    myLayout->addStretch();

    setLayout(myLayout);
    connect(spinBox,SIGNAL(editingFinished()),this,SLOT(updateValue()));

  }


  void EditWizardSize::updateValue()
  {
    s_=spinBox->value();
    var_->setValue(s_);

    emit valueChanged();
  }


  EditWizardBool::EditWizardBool(QWidget * parent,Markov_IO::ABC_Value*av):
    EditField(parent),
    var_(dynamic_cast < Markov_IO::Implements_Simple_Value<bool>*>(av)),
    b_((var_!=nullptr) ? var_->value():false)

  {
    comboBox=new QComboBox;

    comboBox->insertItem(0,tr("false"));
    comboBox->insertItem(1,tr("true"));

    if (b_)
      comboBox->setCurrentIndex(1);
    else
      comboBox->setCurrentIndex(0);

    QLabel* label=new QLabel(var_->id().c_str());

    //    int i=desc->NameIndex(field.toStdString());
    //    label->setToolTip(QString(desc->Tip(i).c_str()));
    //    label->setWhatsThis(desc->WhatThis(i).c_str());

    label->setToolTip(QString(var_->Tip().c_str()));
    label->setWhatsThis(var_->WhatThis().c_str());


    QHBoxLayout* myLayout=new QHBoxLayout;

    myLayout->addWidget(label);
    myLayout->addWidget(comboBox);

    setLayout(myLayout);
    connect(comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(updateValue()));

  }

  void EditWizardBool::updateValue()
  {

    if(comboBox->currentIndex()==0)
      b_=false;
    else
      b_=true;
    //    Markov_IO::Object<bool> od(b_);
    //    desc->ReplaceElement(field.toStdString(),od);
    var_->setValue(b_);

    emit valueChanged();
  }




  EditWizardString::EditWizardString(QWidget * parent,Markov_IO::ABC_Value*av):
    EditField(parent),
    var_(dynamic_cast<Markov_IO::Implements_Simple_Value<std::string>*>(av))
  {
    if ((av!=nullptr)&&( av->complyClass(Markov_IO::Implements_Simple_Value<std::string>::ClassName())))

      str_=var_->value();
    lineEdit=new QLineEdit;


    lineEdit->setText(QString(str_.c_str()));

    lineEdit->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    QLabel* label=new QLabel(var_->id().c_str());
    QHBoxLayout* myLayout=new QHBoxLayout;

    //    int i=desc->NameIndex(field.toStdString());
    //    label->setToolTip(QString(desc->Tip(i).c_str()));
    //    label->setWhatsThis(desc->WhatThis(i).c_str());

    label->setToolTip(QString(var_->Tip().c_str()));
    label->setWhatsThis(var_->WhatThis().c_str());


    myLayout->addWidget(label);
    myLayout->addStretch();

    myLayout->addWidget(lineEdit);
    myLayout->addStretch();


    setLayout(myLayout);
    connect(lineEdit,SIGNAL(editingFinished()),this,SLOT(updateValue()));

  }


  bool EditWizardString::isValid()const
  {
    return !str_.empty();
  }

  void EditWizardString::updateValue()
  {
    str_=lineEdit->text().toStdString();
    //desc->ReplaceElement(field.toStdString(),str_);
    var_->setValue(str_);
    emit valueChanged();

  }




}
