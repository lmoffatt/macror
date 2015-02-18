#include <QTableView>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <string>
#include <QFileDialog>

#include "Markov_IO/Object.h"
#include "Markov_IO/auxiliarIO.h"

#include "Markov_GUI/ABC_Var_GUI.h"
#include "Markov_GUI/ModelMatrix.h"
#include "Markov_GUI/CreateWizard.h"

#include "Markov_IO/ABC_Saveable.h"
#include "Markov_LA/matrixRelational.h"




namespace Markov_GUI {


  EditField::EditField(QWidget* parent, Markov_IO::ABC_Data *av):
    QWidget(parent),
    var_(av)
  {
  }

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




  EditField* EditField::create(QWidget *parent, Markov_IO::ABC_Data* v)
  {
    if (v==nullptr)
      return nullptr;


    if (v->complyClass(
          Markov_IO::Implements_Simple_Var<Markov_LA::M_Matrix<double> >::ClassName()))
      return new EditFieldMatrixDoubles(parent,v);
    else if (v->complyClass(
               Markov_IO::Implements_Simple_Var<Markov_LA::M_Matrix<std::size_t> >::ClassName()))
      return new EditWizardMatrixSizes(parent,v);
    else if (v->complyClass(
               Markov_IO::Implements_Simple_Var<double >::ClassName()))
      return new EditWizardDouble(parent,v);
    else if (v->complyClass(
               Markov_IO::Implements_Simple_Var<std::size_t >::ClassName()))
      return new EditWizardSize(parent,v);
    else if (v->complyClass(
               Markov_IO::Implements_Simple_Var<bool>::ClassName()))
      return new EditWizardBool(parent,v);
    else if (v->complyClass(
               Markov_IO::Implements_Simple_Var<std::string>::ClassName()))
      return new EditWizardString(parent,v);
    else return nullptr;
  }



  EditFieldMatrixDoubles::EditFieldMatrixDoubles(QWidget* parent,
                                                 Markov_IO::ABC_Data* av):
    EditField(parent ,av),
    v(dynamic_cast<Markov_IO::Implements_Simple_Var<Markov_LA::M_Matrix<double>>*>(var_)),
    table (new QTableView)
  {

    //    const Markov_IO::Object<Markov_LA::M_Matrix<double> > * od;
    //    const Markov_IO::ABC_Object *o=(*desc)[field.toStdString()];

    //    od=dynamic_cast<const Markov_IO::Object<Markov_LA::M_Matrix<double> > * > (o);


    if (v->complyModes("Q_Matrix"))
      {
        columnExpandable=false;
        rowsExpandable=false;
        ModelQMatrix *Qmodel=new ModelQMatrix(&v->refval());
        table->setModel(Qmodel);
        connect(Qmodel,SIGNAL(moveToCell(int,int)),this,SLOT(moveToCell(int,int)));
      }
    else
      {
        table->setModel(new ModelMatrix(&v->refval()));
        columnExpandable=false;
        rowsExpandable=false;
      }
    table->setItemDelegate(new LineEditDelegate);
    QStringList colTitles;
    auto c=v->modes();
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



    QLabel* label=new QLabel(v->id().c_str());
    //    int i=desc->NameIndex(field.toStdString());
    // label->setToolTip(QString(desc->Tip(i).c_str()));
    // label->setWhatsThis(desc->WhatThis(i).c_str());

    label->setToolTip(QString(var_->Tip().c_str()));
    label->setWhatsThis(var_->WhatThis().c_str());



    QVBoxLayout* myLayout=new QVBoxLayout;

    myLayout->addWidget(label);
    /*
    if (!desc->Unit(i).empty())
      {
        QLabel* units=new QLabel(desc->Unit(i).c_str());
        myLayout->addWidget(units);
      }
*/
    if ((v->motherClass()->complyModes("ROW_INDEX"))&&(v->motherClass()->complyModes("COL_INDEX")))

      {
        QHBoxLayout* lay=new QHBoxLayout;


        if (v->motherClass()->complyModes("ROW_INDEX"))
          {
            if  (v->motherClass()->complyModes("COL_INDEX"))
              {
                QSpinBox* numCols=new QSpinBox(this);
                columnExpandable=true;

                numCols->setValue(table->model()->columnCount());
                numCols->setRange(0,1e8);
                connect(numCols,SIGNAL(valueChanged(int)),this,SLOT(resetColumnCount(int)));
                QSpinBox* numRows=new QSpinBox(this);
                rowsExpandable=true;

                numRows->setValue(table->model()->rowCount());
                numRows->setRange(0,1e8);
                connect(numRows,SIGNAL(valueChanged(int)),this,SLOT(resetRowCount(int)));
                QVBoxLayout* indexLayout=new QVBoxLayout;
                indexLayout->addWidget(numCols);
                indexLayout->addWidget(numRows);
                lay->addLayout(indexLayout);

              }
            else
              {
                QSpinBox* numRows=new QSpinBox(this);
                rowsExpandable=true;

                numRows->setValue(table->model()->rowCount());
                numRows->setRange(0,1e8);
                connect(numRows,SIGNAL(valueChanged(int)),this,SLOT(resetRowCount(int)));
                lay->addWidget(numRows);
              }

          }
        else if (v->motherClass()->complyModes("COL_INDEX"))
          {
            QSpinBox* numCols=new QSpinBox(this);
            columnExpandable=true;

            numCols->setValue(table->model()->columnCount());
            numCols->setRange(0,1e8);
            connect(numCols,SIGNAL(valueChanged(int)),this,SLOT(resetColumnCount(int)));
            lay->addWidget(numCols);
          }
        lay->addWidget(table);
        myLayout->addLayout(lay);

      }
    else
      {
        myLayout->addWidget(table);
      }
    setLayout(myLayout);

    connect(table->itemDelegate(),SIGNAL(closeEditor(QWidget*)),this,SLOT(updateValue()));

  }

  void EditFieldMatrixDoubles::resetRowCount(int newRowCount)
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

  void EditFieldMatrixDoubles::resetColumnCount(int newColumnCount)
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


  bool EditFieldMatrixDoubles::isValid()const
  {
    if (var_->motherClass()->complyModes("NOT_ALL_ZERO"))
      {
        if (v->refval()==0.0)
          return false;
      }
    if (var_->motherClass()->complyModes("Q_MATRIX"))
      {
        if (v->refval()==0.0)
          return false;
        for (std::size_t i=0; i < Markov_LA::nrows(v->refval()); i++)
          {
            for (std::size_t j=i+1; j< Markov_LA::nrows(v->refval()); ++j)
              {
                if ((v->refval()(i,j)<0)||(v->refval()(j,i)<0))
                  return false;
                if ((v->refval()(i,j)>0)&&(v->refval()(j,i)==0))
                  return false;
                if ((v->refval()(j,i)>0)&&(v->refval()(i,j)==0))
                  return false;
              }
          }
      }
    return true;
  }



  void EditFieldMatrixDoubles::copy()
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

    // add last element
    selected_text.append(table->model()->data(current).toString());
    selected_text.append(QLatin1Char('\n'));
    qApp->clipboard()->setText(selected_text);
  }

  void EditFieldMatrixDoubles::paste()
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

  void EditFieldMatrixDoubles::updateValue()
  {

    //    Markov_IO::Object<Markov_LA::M_Matrix<double> > od(md_);
    //    desc->ReplaceElement(field.toStdString(),od);
   
    emit valueChanged();
  }


  void EditFieldMatrixDoubles::resetModel()
  {
    //    const Markov_IO::Object<Markov_LA::M_Matrix<double> > * od;
    //    const Markov_IO::ABC_Object *o=(*desc)[field.toStdString()];
    //    od=dynamic_cast<const Markov_IO::Object<Markov_LA::M_Matrix<double> > * > (o);
    //    md_=od->Value();

    var_->reset();


  }


  void EditFieldMatrixDoubles::moveToCell(int i, int j)
  {
    table->setCurrentIndex(table->currentIndex().sibling(i,j));
  }






  EditWizard_Complex_Var::EditWizard_Complex_Var(QWidget* parent,Markov_IO::ABC_Data *av):
    EditField(parent,av),
    cvar_(dynamic_cast<Markov_IO::Implements_Complex_Var*>(av)),
    isvalid(false)
  {
    QLabel* label=new QLabel(cvar_->id().c_str());
    lineEdit=new QLineEdit(QString(cvar_->id().c_str()));
    lineEdit->setReadOnly(true);

    QPushButton* button=new QPushButton("&edit");
    label->setToolTip(cvar_->Tip().c_str());
    lineEdit->setToolTip(cvar_->Tip().c_str());
    label->setWhatsThis(cvar_->WhatThis().c_str());
    lineEdit->setWhatsThis(cvar_->WhatThis().c_str());

    QHBoxLayout* myLayout=new QHBoxLayout;
    myLayout->addWidget(label);
    myLayout->addWidget(lineEdit);
    myLayout->addWidget(button);
    setLayout(myLayout);
    connect(button,SIGNAL(clicked()),this,SLOT(editMe()));

  }


  void EditWizard_Complex_Var::editMe()
  {
    auto v=cvar_->to_ComplexVar();
    EditVariableDialog* c=new EditVariableDialog(this,v);
    if (c->exec()==1)
      {
        cvar_->loadFromComplexVar(v);

        isvalid=true;
        lineEdit->setText(QString(cvar_->id().c_str()));
        update();

        emit valueChanged();
      }


  }
  void EditWizard_Complex_Var::updateValue()
  {

  }

  bool EditWizard_Complex_Var::isValid()const
  {
    return isvalid;
  }


  EditWizardMatrixSizes::EditWizardMatrixSizes(QWidget* parent,Markov_IO::ABC_Data * av):
    EditField(parent,av),
    v(dynamic_cast<Markov_IO::Implements_Simple_Var<Markov_LA::M_Matrix<std::size_t>>*>(av))
  {
    QTableView *table=new QTableView;

    table->setModel(new ModelMatrix(&v->refval()));


    QLabel* label=new QLabel(av->id().c_str());
    QVBoxLayout* myLayout=new QVBoxLayout;

    //    int i=desc->NameIndex(field.toStdString());
    //    label->setToolTip(QString(desc->Tip(i).c_str()));
    //    label->setWhatsThis(desc->WhatThis(i).c_str());

    label->setToolTip(QString(var_->Tip().c_str()));
    label->setWhatsThis(var_->WhatThis().c_str());


    myLayout->addWidget(label);
    //    if (!desc->Unit(i).empty())
    //      {
    //        QLabel* units=new QLabel(desc->Unit(i).c_str());
    //        myLayout->addWidget(units);
    //      }
    QHBoxLayout* tableLayout=new QHBoxLayout;

    tableLayout->addWidget(table);
    tableLayout->addStretch();
    tableLayout->addStretch();
    tableLayout->addStretch();
    myLayout->addLayout(tableLayout);
    myLayout->addStretch();
    myLayout->addStretch();

    setLayout(myLayout);
    connect(table->itemDelegate(),SIGNAL(closeEditor(QWidget*)),this,SLOT(updateValue()));

  }

  void EditWizardMatrixSizes::updateValue()
  {

    //    Markov_IO::Object<Markov_LA::M_Matrix<std::size_t> > od(ms_);
    //    desc->ReplaceElement(field.toStdString(),od);

    emit valueChanged();
  }


  EditWizardDouble::EditWizardDouble(QWidget * parent,Markov_IO::ABC_Data*av):
    EditField(parent,av),
    v(dynamic_cast < Markov_IO::Implements_Simple_Var<double>*>(av))
  {

    //    const Markov_IO::Object<double > * od;
    //    const Markov_IO::ABC_Object *o=(*desc)[field.toStdString()];
    //    od=dynamic_cast<const Markov_IO::Object<double > * > (o);
    //    d_=od->Value();

    lineEdit=new QLineEdit;


    QDoubleValidator* val=new QDoubleValidator;
    val->setDecimals(14);
    lineEdit->setValidator(val);
    lineEdit->setText(QString("%1").arg(d_,0,'g',14));
    lineEdit->setAlignment(Qt::AlignRight);

    QLabel* label=new QLabel(v->id().c_str());

    //    int i=desc->NameIndex(field.toStdString());
    //    QString toolt=QString(desc->Tip(i).c_str());
    //    label->setToolTip(toolt);
    //    label->setWhatsThis(desc->WhatThis(i).c_str());

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

  bool EditWizardDouble::isValid()const
  {
    if (var_->motherClass()->complyModes("NOT_ZERO"))
      {
        if (d_==0)
          return false;

      }
    return true;
  }

  void EditWizardDouble::updateValue()
  {

    QString label=lineEdit->text();
    bool ok;
    d_ =label.toDouble(&ok) ;
    if (ok)
      {
        //        Markov_IO::Object<double> od(d_);
        //        desc->ReplaceElement(field.toStdString(),od);
        v->setValue(d_);
        emit valueChanged();
      }
    lineEdit->updateGeometry();
  }

  EditWizardSize::EditWizardSize(QWidget * parent,Markov_IO::ABC_Data*av):
    EditField(parent,av),
    v(dynamic_cast < Markov_IO::Implements_Simple_Var<std::size_t>*>(av)),
    s_(v->value())
  {

    //    const Markov_IO::Object<std::size_t > * od;
    //    const Markov_IO::ABC_Object *o=(*desc)[field.toStdString()];
    //    od=dynamic_cast<const Markov_IO::Object<std::size_t > * > (o);
    //    s_=od->Value();



    spinBox=new QSpinBox;

    spinBox->setMaximum(v->motherClassType()->maxValue());

    spinBox->setValue(s_);

    spinBox->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);


    QLabel* label=new QLabel(v->id().c_str());
    //    int i=desc->NameIndex(field.toStdString());
    //    label->setToolTip(QString(desc->Tip(i).c_str()));
    //    label->setWhatsThis(desc->WhatThis(i).c_str());

    label->setToolTip(QString(var_->Tip().c_str()));
    label->setWhatsThis(var_->WhatThis().c_str());


    QHBoxLayout* myLayout=new QHBoxLayout;

    myLayout->addWidget(label);
    myLayout->addStretch();
    myLayout->addWidget(spinBox);
    if (!v->motherClassType()->units().empty())
      {
        QLabel* units=new QLabel(v->motherClassType()->units().c_str());
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
    //    Markov_IO::Object<std::size_t> od(s_);
    //    desc->ReplaceElement(field.toStdString(),od);
    v->setValue(s_);

    emit valueChanged();
  }


  EditWizardBool::EditWizardBool(QWidget * parent,Markov_IO::ABC_Data*av):
    EditField(parent,av),
    v(dynamic_cast < Markov_IO::Implements_Simple_Var<bool>*>(av)),
    b_(v->value())
  {

    //    const Markov_IO::Object<bool > * od;
    //    const Markov_IO::ABC_Object *o=(*desc)[field.toStdString()];
    //    od=dynamic_cast<const Markov_IO::Object<bool > * > (o);
    //    b_=od->Value();

    comboBox=new QComboBox;

    comboBox->insertItem(0,tr("false"));
    comboBox->insertItem(1,tr("true"));

    if (b_)
      comboBox->setCurrentIndex(1);
    else
      comboBox->setCurrentIndex(0);

    QLabel* label=new QLabel(v->id().c_str());

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
    v->setValue(b_);

    emit valueChanged();
  }




  EditWizardString::EditWizardString(QWidget * parent,Markov_IO::ABC_Data*av):
    EditField(parent,av),
    v(dynamic_cast < Markov_IO::Implements_Simple_Var<std::string>*>(av))
  {

    //    const Markov_IO::Object<std::string > * od;
    //    const Markov_IO::ABC_Object *o=(*desc)[field.toStdString()];
    //    od=dynamic_cast<const Markov_IO::Object<std::string > * > (o);
    //    str_=od->Value();

    str_=v->value();
    lineEdit=new QLineEdit;


    lineEdit->setText(QString(str_.c_str()));

    lineEdit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

    QLabel* label=new QLabel(v->id().c_str());
    QHBoxLayout* myLayout=new QHBoxLayout;

    //    int i=desc->NameIndex(field.toStdString());
    //    label->setToolTip(QString(desc->Tip(i).c_str()));
    //    label->setWhatsThis(desc->WhatThis(i).c_str());

    label->setToolTip(QString(v->Tip().c_str()));
    label->setWhatsThis(v->WhatThis().c_str());


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
    v->setValue(str_);
    emit valueChanged();

  }




}
