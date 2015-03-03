#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>

#include "Markov_IO/Object.h"

#include "Markov_GUI/MacrorEditWindow.h"
#include "Markov_GUI/EditWidgetMatrixDoubles.h"


#include "Markov_GUI/EditWidgetField.h"
#include "Markov_LA/Matrix.h"


EditWidgetField::EditWidgetField(QString fieldName,MacrorEditWindow* parentW ):
    QWidget(parentW),
    pw(parentW),
    name(fieldName),
    v(parentW->getFieldClass(fieldName)),
    o(parentW->getFieldObject(fieldName))
{
   // init();
}



 void EditWidgetField::init()

{
    QHBoxLayout* mainLayout=new QHBoxLayout;
    if(v)
    {
        type=SAVEABLE;
        desc=v->GetDescription();
        QLabel* label=new QLabel(name);
        lineEdit=new QLineEdit(QString(desc.ElementValue(0).c_str()));
        QPushButton* button=new QPushButton("&show");
        label->setToolTip(desc.Tip(0).c_str());
        lineEdit->setToolTip(desc.Tip(0).c_str());
        label->setWhatsThis(desc.WhatThis(0).c_str());
        lineEdit->setWhatsThis(desc.WhatThis(0).c_str());
        mainLayout->addWidget(label);
        mainLayout->addWidget(lineEdit);
        mainLayout->addWidget(button);

        connect(button,SIGNAL(clicked()),this,SLOT(editMe()));
    }
    else if(o->myClass()==Markov_IO::Object<Markov_LA::M_Matrix<std::size_t> >::ClassName())
    {
        // matrix of unsigned integers
        type=MSIZET;

        const Markov_IO::Object<Markov_LA::M_Matrix<std::size_t> > * ou;
        ou=dynamic_cast<const Markov_IO::Object<Markov_LA::M_Matrix<std::size_t> > * > (o);
        mu_=ou->Value();
        ncol=Markov_LA::ncols(mu_);
        nrow=Markov_LA::nrows(mu_);
        table=new QTableWidget(nrow,ncol,this);

        for (int i=0; i<nrow; i++)
        {
            QList<QLineEdit*> row;
            for (int j=0; j<ncol;j++)
            {
                QString val=QString("%1").arg(mu_(i,j));
              /*  QTableWidgetItem* item= new QTableWidgetItem;
                item->setData(Qt::EditRole,QVariant(md_(i,j)));
                item->setData(Qt::SizeHintRole,20);

                */
                QLineEdit* line=new QLineEdit(val);
                QIntValidator* valsize=new QIntValidator(line);
                valsize->setBottom(0);

                line->setValidator(valsize);
              //  table->setCellWidget(i,j,line);

                row.push_back(line);
            }
            lineEditArray.push_back(row);
        }
        QLabel* label=new QLabel(name);
        label->setToolTip(pw->getFieldTip(name));
        label->setWhatsThis(pw->getFieldWhatThis(name));
        mainLayout->addWidget(label);
        mainLayout->addWidget(table);
        setLayout(mainLayout);

    }
    else
    {
        QLabel* label=new QLabel(name);
        lineEdit=new QLineEdit(pw->getFieldValue(name));
        if(o->myClass()==Markov_IO::Object<bool >::ClassName())
        {
            type=BOOL;
            lineEdit->setValidator(new QIntValidator(0,1,lineEdit));

        }
        else if(o->myClass()==Markov_IO::Object<std::size_t >::ClassName())
        {
            type=SIZE;
            QIntValidator* valsize=new QIntValidator(lineEdit);
            valsize->setBottom(0);
            lineEdit->setValidator(valsize);
        }
        else if(o->myClass()==Markov_IO::Object<double >::ClassName())
        {
            type=DOUBLE;
            lineEdit->setValidator(new QDoubleValidator(lineEdit));

        }
        else if(o->myClass()==Markov_IO::Object<std::string >::ClassName())
        {
            type=STRING;
        }


        label->setToolTip(pw->getFieldTip(name));
        lineEdit->setToolTip(pw->getFieldTip(name));
        label->setWhatsThis(pw->getFieldWhatThis(name));
        lineEdit->setWhatsThis(pw->getFieldWhatThis(name));
        mainLayout->addWidget(label);
        mainLayout->addWidget(lineEdit);
    }

    setLayout(mainLayout);
}


EditWidgetField* EditWidgetField::create(QString fieldName,MacrorEditWindow* parentW)
{
    const Markov_IO::ABC_Saveable* v=parentW->getFieldClass(fieldName);
    if (v)
        return new EditWidgetField(fieldName,parentW);
    else
    {
        const Markov_IO::ABC_Object* o=parentW->getFieldObject(fieldName);
        if (o->myClass()==Markov_IO::Object<Markov_LA::M_Matrix<double> >::ClassName())
            return new EditWidgetMatrixDoubles(fieldName,parentW);
        else
            return new EditWidgetField(fieldName,parentW);

    }
}





void EditWidgetField::updateValue()
{
    if (type==BOOL||type==SIZE||type==DOUBLE||type==STRING)
    {
        pw->replaceField(name,lineEdit->displayText());
    }
    else if(type==MSIZET)
    {
        for (int i=0;i<nrow;i++)
            for (int j=0;j<ncol;j++)
            {
                mu_(i,j)=lineEditArray.at(i).at(j)->displayText().toULong();
            }
        Markov_IO::Object<Markov_LA::M_Matrix<std::size_t> > oo(mu_);
        pw->replaceField(name,&oo);
    }
    if (type==SAVEABLE)
    {
        pw->replaceField(name,lineEdit->displayText());
    }

    }

void EditWidgetField::editMe()
{
    MacrorEditWindow* ew=new MacrorEditWindow(name,pw);
    ew->show();
}


