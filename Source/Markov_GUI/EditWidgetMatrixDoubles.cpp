#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableView>
#include <QDoubleValidator>
#include <QMenu>
#include "Markov_IO/Object.h"

#include "Markov_GUI/EditWidgetMatrixDoubles.h"
#include "Markov_GUI/EditWidgetField.h"

#include "Markov_GUI/MacrorEditWindow.h"
#include "Markov_GUI/ModelMatrix.h"

#include "Markov_LA/Matrix.h"

EditWidgetMatrixDoubles::EditWidgetMatrixDoubles(QString fieldName,MacrorEditWindow* parentW ):
    EditWidgetField(fieldName,parentW){

    const Markov_IO::Object<Markov_LA::M_Matrix<double> > * od;
    od=dynamic_cast<const Markov_IO::Object<Markov_LA::M_Matrix<double> > * > (o);
    md_=od->Value();

}







void EditWidgetMatrixDoubles::updateValue()
{

        Markov_IO::Object<Markov_LA::M_Matrix<double> > od(md_);
        pw->replaceField(name,&od);
   }

void EditWidgetMatrixDoubles::editMe()
{
    MacrorEditWindow* ew=new MacrorEditWindow(name,pw);
    ew->show();
}


void EditWidgetMatrixDoubles::insertColumn()
{
//insertColumn(table->currentColumn());

}

void EditWidgetMatrixDoubles::insertColumn(int )
{
    }


void EditWidgetMatrixDoubles::insertRow(int ){

}



void EditWidgetMatrixDoubles::init()

{

     QHBoxLayout* mainLayout=new QHBoxLayout;
     // matrix of doubles
     ncol=Markov_LA::ncols(md_);
     nrow=Markov_LA::nrows(md_);
    // delete table;



     table=new QTableView(this);
     table->setModel(new ModelMatrix(&md_));
     table->setItemDelegate(new LineEditDelegate);
     lineEditArray.clear();
     //delete layout();
     QLabel* label=new QLabel(name);
     label->setToolTip(pw->getFieldTip(name));
     label->setWhatsThis(pw->getFieldWhatThis(name));
     mainLayout->addWidget(label);
     mainLayout->addWidget(table);

     connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
         this, SLOT(ShowContextMenu(const QPoint&)));
     setLayout(mainLayout);

}

void EditWidgetMatrixDoubles::fillTable()
{

}

void EditWidgetMatrixDoubles::ShowContextMenu(const QPoint& ) // this is a slot
{
}
