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


  EditWizardField::EditWizardField(QString fieldName,
                                   QStringList modeList,
                                   Markov_IO::ClassDescription* cd,
                                   Markov_IO::ABC_Var *av,
                                   QWidget *pw):
    QWidget(pw),
    field(fieldName),
    mode(modeList),
    desc(cd),
    var_(av)
  {
  }

  bool EditWizardField::isValid()const
  {
    return true;
  }






  void EditWizardField::keyPressEvent(QKeyEvent * event)
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




  EditWizardField* EditWizardField::create(QString fieldName,
                                           QStringList modeList,
                                           Markov_IO::ClassDescription* cd,
                                           Markov_IO::ABC_Var* av)
  {

    std::size_t i=cd->NameIndex(fieldName.toStdString());
    if (cd->IsComplexObject(i))
      return new EditWizard_Complex_Var(fieldName,modeList,cd,av);
    else
      {
        const Markov_IO::ABC_Object* o=cd->operator [](fieldName.toStdString());
        if (o->myClass()==Markov_IO::Object<Markov_LA::M_Matrix<double> >::ClassName())
          return new EditWizardMatrixDoubles(fieldName,modeList,cd,av);
        else if (o->myClass()==Markov_IO::Object<Markov_LA::M_Matrix<std::size_t> >::ClassName())
          return new EditWizardMatrixSizes(fieldName,modeList,cd,av);
        else if (o->myClass()==Markov_IO::Object<double >::ClassName())
          return new EditWizardDouble(fieldName,modeList,cd,av);
        else if (o->myClass()==Markov_IO::Object<std::size_t >::ClassName())
          return new EditWizardSize(fieldName,modeList,cd,av);
        else if (o->myClass()==Markov_IO::Object<bool>::ClassName())
          return new EditWizardBool(fieldName,modeList,cd,av);
        else if (o->myClass()==Markov_IO::Object<std::string>::ClassName())
          return new EditWizardString(fieldName,modeList,cd,av);
        else return 0;
      }
  }


  EditWizardMatrixDoubles::EditWizardMatrixDoubles(QString fieldName,
                                                   QStringList modeList,
                                                   Markov_IO::ClassDescription* cd,
                                                   Markov_IO::ABC_Var* av):
    EditWizardField(fieldName,modeList,cd,av)
  {

//    const Markov_IO::Object<Markov_LA::M_Matrix<double> > * od;
//    const Markov_IO::ABC_Object *o=(*desc)[field.toStdString()];

//    od=dynamic_cast<const Markov_IO::Object<Markov_LA::M_Matrix<double> > * > (o);

//    md_=od->Value();
    var_->getValue(field.toStdString(),md_);

    table=new QTableView;

    if (mode.contains("Q_Matrix",Qt::CaseInsensitive))
      {
        columnExpandable=false;
        rowsExpandable=false;
        ModelQMatrix *Qmodel=new ModelQMatrix(&md_);
        table->setModel(Qmodel);
        connect(Qmodel,SIGNAL(moveToCell(int,int)),this,SLOT(moveToCell(int,int)));
      }
    else
      {
        table->setModel(new ModelMatrix(&md_));
        columnExpandable=false;
        rowsExpandable=false;
      }
    table->setItemDelegate(new LineEditDelegate);
    QStringList colTitles=
        mode.filter("ColTitle",Qt::CaseInsensitive);
    foreach (QString title,colTitles )
      {
        QStringList ti=title.split("_");
        bool ok;
        int i=ti.at(1).toInt(&ok);
        if (ok)
          table->model()->setHeaderData(i,Qt::Horizontal,ti.at(2));
      }



    QLabel* label=new QLabel(field);
//    int i=desc->NameIndex(field.toStdString());
   // label->setToolTip(QString(desc->Tip(i).c_str()));
   // label->setWhatsThis(desc->WhatThis(i).c_str());

    label->setToolTip(QString(var_->getChildVar(field.toStdString())->Tip().c_str()));
    label->setWhatsThis(var_->getChildVar(field.toStdString())->WhatThis().c_str());



    QVBoxLayout* myLayout=new QVBoxLayout;

    myLayout->addWidget(label);
    /*
    if (!desc->Unit(i).empty())
      {
        QLabel* units=new QLabel(desc->Unit(i).c_str());
        myLayout->addWidget(units);
      }
*/
    if (!mode.filter("_INDEX",Qt::CaseInsensitive).isEmpty())
      {
        QHBoxLayout* lay=new QHBoxLayout;


        if (mode.contains("ROW_INDEX",Qt::CaseInsensitive))
          {
            if (mode.contains("COL_INDEX",Qt::CaseInsensitive))
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

          }else if (mode.contains("COL_INDEX",Qt::CaseInsensitive))
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

  void EditWizardMatrixDoubles::resetRowCount(int newRowCount)
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

  void EditWizardMatrixDoubles::resetColumnCount(int newColumnCount)
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


  bool EditWizardMatrixDoubles::isValid()const
  {
    if (mode.contains("NOT_ALL_ZERO",Qt::CaseInsensitive))
      {
        if (md_==0.0)
          return false;
      }
    if (mode.contains("Q_MATRIX",Qt::CaseInsensitive))
      {
        if (md_==0.0)
          return false;
        for (std::size_t i=0; i < Markov_LA::nrows(md_); i++)
          {
            for (std::size_t j=i+1; j< Markov_LA::nrows(md_); ++j)
              {
                if ((md_(i,j)<0)||(md_(j,i)<0))
                  return false;
                if ((md_(i,j)>0)&&(md_(j,i)==0))
                  return false;
                if ((md_(j,i)>0)&&(md_(i,j)==0))
                  return false;
              }
          }
      }
    return true;
  }



  void EditWizardMatrixDoubles::copy()
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

  void EditWizardMatrixDoubles::paste()
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

  void EditWizardMatrixDoubles::updateValue()
  {

//    Markov_IO::Object<Markov_LA::M_Matrix<double> > od(md_);
//    desc->ReplaceElement(field.toStdString(),od);
    var_->push_backVar(field.toStdString(),md_);

    emit valueChanged();
  }


  void EditWizardMatrixDoubles::resetModel()
  {
//    const Markov_IO::Object<Markov_LA::M_Matrix<double> > * od;
//    const Markov_IO::ABC_Object *o=(*desc)[field.toStdString()];
//    od=dynamic_cast<const Markov_IO::Object<Markov_LA::M_Matrix<double> > * > (o);
//    md_=od->Value();

    var_->getValue(field.toStdString(),md_);

    QItemSelectionModel *m = table->selectionModel();
    table->setModel(new ModelMatrix(&md_));
    delete m;
  }


  void EditWizardMatrixDoubles::moveToCell(int i, int j)
  {
    table->setCurrentIndex(table->currentIndex().sibling(i,j));
  }



  void EditWizardMatrixDoubles::setConstraint(Constrain someConstrain)
  {
    if (someConstrain==EditWizardField::Q_Matrix)
      {
        // change the matrix model accordingly
        QItemSelectionModel *m = table->selectionModel();
        ModelQMatrix *Qmodel=new ModelQMatrix(&md_);
        table->setModel(Qmodel);
        delete m;
        connect(Qmodel,SIGNAL(moveToCell(int,int)),this,SLOT(moveToCell(int,int)));
      }


  }



  EditWizard_Complex_Var::EditWizard_Complex_Var(QString fieldName,
                                         QStringList modeList,
                                         Markov_IO::ClassDescription* cd ,
                                         Markov_IO::ABC_Var* av):
    EditWizardField(fieldName,modeList,cd,av),
    isvalid(false)
  {
    desField=cd->ElementClass(field.toStdString())->GetDescription();
    QLabel* label=new QLabel(field);
    lineEdit=new QLineEdit(QString(desField.ElementValue(0).c_str()));
    lineEdit->setReadOnly(true);

    QPushButton* button=new QPushButton("&edit");
    label->setToolTip(desField.Tip(0).c_str());
    lineEdit->setToolTip(desField.Tip(0).c_str());
    label->setWhatsThis(desField.WhatThis(0).c_str());
    lineEdit->setWhatsThis(desField.WhatThis(0).c_str());

    QHBoxLayout* myLayout=new QHBoxLayout;
    myLayout->addWidget(label);
    myLayout->addWidget(lineEdit);
    myLayout->addWidget(button);
    setLayout(myLayout);
    connect(button,SIGNAL(clicked()),this,SLOT(editMe()));

  }


  void EditWizard_Complex_Var::editMe()
  {
    QString className(desField.ClassName().c_str());
    Markov_IO::ABC_Saveable *s;
    Markov_IO::ABC_Saveable **sptr=&s;

    CreateWizard* c=new CreateWizard(&className,&desField,sptr);
    if (c->exec()==1)
      {
        desc->ReplaceElement(field.toStdString(),**sptr);

        isvalid=true;
        lineEdit->setText(QString(desField.ElementValue(0).c_str()));
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


  EditWizardMatrixSizes::EditWizardMatrixSizes(QString fieldName, QStringList modeList, Markov_IO::ClassDescription* cd, Markov_IO::ABC_Var * av):
    EditWizardField(fieldName,modeList,cd,av)
  {

//    const Markov_IO::Object<Markov_LA::M_Matrix<std::size_t> > * od;
//    const Markov_IO::ABC_Object *o=(*desc)[field.toStdString()];
//    od=dynamic_cast<const Markov_IO::Object<Markov_LA::M_Matrix<std::size_t> > * > (o);
//    ms_=od->Value();

    var_->getValue(field.toStdString(),ms_);


    QTableView *table=new QTableView;

    table->setModel(new ModelMatrix(&ms_));


    QLabel* label=new QLabel(field);
    QVBoxLayout* myLayout=new QVBoxLayout;

//    int i=desc->NameIndex(field.toStdString());
//    label->setToolTip(QString(desc->Tip(i).c_str()));
//    label->setWhatsThis(desc->WhatThis(i).c_str());

    label->setToolTip(QString(var_->getChildVar(field.toStdString())->Tip().c_str()));
    label->setWhatsThis(var_->getChildVar(field.toStdString())->WhatThis().c_str());


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
    var_->push_backVar(field.toStdString(),ms_);

    emit valueChanged();
  }


  EditWizardDouble::EditWizardDouble(QString fieldName,
                                     QStringList modeList,
                                     Markov_IO::ClassDescription* cd,
                                     Markov_IO::ABC_Var*av):
    EditWizardField(fieldName,modeList,cd,av)
  {

//    const Markov_IO::Object<double > * od;
//    const Markov_IO::ABC_Object *o=(*desc)[field.toStdString()];
//    od=dynamic_cast<const Markov_IO::Object<double > * > (o);
//    d_=od->Value();

    var_->getValue(field.toStdString(),d_);

    lineEdit=new QLineEdit;


    QDoubleValidator* val=new QDoubleValidator;
    val->setDecimals(14);
    lineEdit->setValidator(val);
    lineEdit->setText(QString("%1").arg(d_,0,'g',14));
    lineEdit->setAlignment(Qt::AlignRight);

    QLabel* label=new QLabel(field);

//    int i=desc->NameIndex(field.toStdString());
//    QString toolt=QString(desc->Tip(i).c_str());
//    label->setToolTip(toolt);
//    label->setWhatsThis(desc->WhatThis(i).c_str());

    label->setToolTip(QString(var_->getChildVar(field.toStdString())->Tip().c_str()));
    label->setWhatsThis(var_->getChildVar(field.toStdString())->WhatThis().c_str());



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
    if (mode.contains("NOT_ZERO",Qt::CaseInsensitive))
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
        var_->push_backVar(field.toStdString(),d_);
        emit valueChanged();
      }
    lineEdit->updateGeometry();
  }

  EditWizardSize::EditWizardSize(QString fieldName, QStringList modeList, Markov_IO::ClassDescription* cd,
                                 Markov_IO::ABC_Var* av):
    EditWizardField(fieldName,modeList,cd,av)
  {

//    const Markov_IO::Object<std::size_t > * od;
//    const Markov_IO::ABC_Object *o=(*desc)[field.toStdString()];
//    od=dynamic_cast<const Markov_IO::Object<std::size_t > * > (o);
//    s_=od->Value();

    var_->getValue(field.toStdString(),s_);

    spinBox=new QSpinBox;

    spinBox->setMaximum(1000000);

    spinBox->setValue(s_);

    spinBox->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);


    QLabel* label=new QLabel(field);
//    int i=desc->NameIndex(field.toStdString());
//    label->setToolTip(QString(desc->Tip(i).c_str()));
//    label->setWhatsThis(desc->WhatThis(i).c_str());

    label->setToolTip(QString(var_->getChildVar(field.toStdString())->Tip().c_str()));
    label->setWhatsThis(var_->getChildVar(field.toStdString())->WhatThis().c_str());


    QHBoxLayout* myLayout=new QHBoxLayout;

    myLayout->addWidget(label);
    myLayout->addStretch();
    myLayout->addWidget(spinBox);
/*    if (!desc->Unit(i).empty())
      {
        QLabel* units=new QLabel(desc->Unit(i).c_str());
        myLayout->addWidget(units);
      }
    else
      {
        myLayout->addStretch();
      }
  */  myLayout->addStretch();

    setLayout(myLayout);
    connect(spinBox,SIGNAL(editingFinished()),this,SLOT(updateValue()));

  }

  void EditWizardSize::updateValue()
  {

    s_=spinBox->value();
//    Markov_IO::Object<std::size_t> od(s_);
//    desc->ReplaceElement(field.toStdString(),od);
    var_->push_backVar(field.toStdString(),s_);

    emit valueChanged();
  }


  EditWizardBool::EditWizardBool(QString fieldName, QStringList modeList, Markov_IO::ClassDescription* cd,
                                 Markov_IO::ABC_Var* av):
    EditWizardField(fieldName,modeList,cd,av)
  {

//    const Markov_IO::Object<bool > * od;
//    const Markov_IO::ABC_Object *o=(*desc)[field.toStdString()];
//    od=dynamic_cast<const Markov_IO::Object<bool > * > (o);
//    b_=od->Value();
    var_->getValue(field.toStdString(),b_);

    comboBox=new QComboBox;

    comboBox->insertItem(0,tr("false"));
    comboBox->insertItem(1,tr("true"));

    if (b_)
      comboBox->setCurrentIndex(1);
    else
      comboBox->setCurrentIndex(0);

    QLabel* label=new QLabel(field);

//    int i=desc->NameIndex(field.toStdString());
//    label->setToolTip(QString(desc->Tip(i).c_str()));
//    label->setWhatsThis(desc->WhatThis(i).c_str());

    label->setToolTip(QString(var_->getChildVar(field.toStdString())->Tip().c_str()));
    label->setWhatsThis(var_->getChildVar(field.toStdString())->WhatThis().c_str());


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
    var_->push_backVar(field.toStdString(),b_);

    emit valueChanged();
  }




  EditWizardString::EditWizardString(QString fieldName,
                                     QStringList modeList,
                                     Markov_IO::ClassDescription* cd ,
                                     Markov_IO::ABC_Var* av):
    EditWizardField(fieldName,modeList,cd,av)
  {

//    const Markov_IO::Object<std::string > * od;
//    const Markov_IO::ABC_Object *o=(*desc)[field.toStdString()];
//    od=dynamic_cast<const Markov_IO::Object<std::string > * > (o);
//    str_=od->Value();

    var_->getValue(field.toStdString(),str_);

    lineEdit=new QLineEdit;


    lineEdit->setText(QString(str_.c_str()));

    lineEdit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

    QLabel* label=new QLabel(field);
    QHBoxLayout* myLayout=new QHBoxLayout;

//    int i=desc->NameIndex(field.toStdString());
//    label->setToolTip(QString(desc->Tip(i).c_str()));
//    label->setWhatsThis(desc->WhatThis(i).c_str());

    label->setToolTip(QString(var_->getChildVar(field.toStdString())->Tip().c_str()));
    label->setWhatsThis(var_->getChildVar(field.toStdString())->WhatThis().c_str());


    myLayout->addWidget(label);
    myLayout->addStretch();

    myLayout->addWidget(lineEdit);
    myLayout->addStretch();
    QStringList fnameext=mode.filter("FILENAME",Qt::CaseInsensitive);
    if (!fnameext.empty())
      {

        QPushButton* button=new QPushButton("&Browse");
        myLayout->addWidget(button);
        connect(button,SIGNAL(clicked()),this,SLOT(browse()));



      }

    setLayout(myLayout);
    connect(lineEdit,SIGNAL(editingFinished()),this,SLOT(updateValue()));

  }

  void EditWizardString::browse()
  {
    QStringList fileExt=mode.filter("filename",Qt::CaseInsensitive);

    QString extensions;
    foreach (QString ext,fileExt)
      {
        QStringList ext2=ext.split("_");
        for (int i=1; i<ext2.length(); i++)
          extensions+=tr("*.")+ext2.at(i);
      }


    str_=QFileDialog::getOpenFileName(this,
                                      tr("file name"),
                                      tr(""),
                                      extensions).toStdString();

    lineEdit->setText(str_.c_str());
    //desc->ReplaceElement(field.toStdString(),str_);
    var_->push_backVar(field.toStdString(),str_);
    emit valueChanged();

  }


  bool EditWizardString::isValid()const
  {
    return !str_.empty();
  }

  void EditWizardString::updateValue()
  {
    str_=lineEdit->text().toStdString();
    //desc->ReplaceElement(field.toStdString(),str_);
    var_->push_backVar(field.toStdString(),str_);
    emit valueChanged();

  }




}
