#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QAbstractButton>
#include <QScrollArea>
#include <QComboBox>

#include "Markov_IO/Object.h"

#include "Markov_GUI/MacrorEditWindow.h"
#include "Markov_GUI/ABC_Var_GUI.h"




MacrorEditWindow::MacrorEditWindow(QString Qvarname,
                                   Markov_Console::Markov_CommandManager* cm,
                                   QWidget* parent):

    QDialog(parent),
    cm_(cm),
    pw_(0),
    alias(Qvarname)
{

    std::string varname=Qvarname.toStdString();

    if (cm_->has_var(varname))
    {
        v=cm_->getVar(varname);
        init();
    }
}

MacrorEditWindow::MacrorEditWindow(QString fieldName,
                                   MacrorEditWindow *parent):

    QDialog(parent),
    cm_(parent->cm_),
    pw_(parent),
    alias(parent->alias+"."+fieldName),
    myFieldName(fieldName),
    v(parent->getFieldClass(fieldName))
{
    if (v)
        init();
}


void MacrorEditWindow::changeClass(QString newClass)
{
    if (cm_->has_type(newClass.toStdString()))
    {
        if (v_old)
        {
            if (v_old->myClass()==newClass.toStdString())
            {
                std::swap(v,v_old);
            }
        }
        delete v_old;
        v_old=v;
        Markov_IO::ABC_Saveable* newv;
        Markov_IO::create(newv,newClass.toStdString());
        v=newv;
        init();
        update();
    }

}


void MacrorEditWindow::init()
{
    desc=v->GetDescription();
    setWindowTitle(QString(alias).prepend("Edit "));

    QVBoxLayout* mainLayout=new QVBoxLayout;
    nameLabel= new QLabel(tr("&Name"));
    nameEdit= new QLineEdit(QString(desc.ElementValue(0).c_str()));
    nameLabel->setBuddy(nameEdit);
    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(nameEdit);



    classLabel= new QLabel("&Class");
    classEdit= new QComboBox(this);

    QStringList classList;
    std::vector<std::string> classv=cm_->getSiblings(v->myClass());
    for (std::size_t i=0; i<classv.size();++i)
        classList.push_back(classv[i].c_str());



    classEdit->insertItems(0,classList);
    // (QString(desc.ClassName().c_str()));

    classEdit->setCurrentIndex(classEdit->findText(QString(v->myClass().c_str())));

    classLabel->setBuddy(classEdit);
    mainLayout->addWidget(classLabel);
    mainLayout->addWidget(classEdit);

    connect(classEdit,SIGNAL(currentIndexChanged(QString)),this,SLOT(changeClass(QString)));


    superClassLabel= new QLabel("&SuperClass");
    superClassEdit= new QLineEdit(QString(desc.SuperClass().c_str()));
    superClassLabel->setBuddy(superClassEdit);
    mainLayout->addWidget(superClassLabel);
    mainLayout->addWidget(superClassEdit);



    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    buttonBox->buttons().value(0)->setToolTip("accept editing");
    buttonBox->buttons().value(1)->setToolTip("cancel editing");
    buttonBox->buttons().value(1)->setWhatsThis("Press this button to finish when you think the editing"
                                                "has finished. Press the cancel button when you do not want"
                                                " to save the work done");

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    mainLayout->addWidget(buttonBox);


    QVBoxLayout* fieldsLayout=new QVBoxLayout;

    for (std::size_t i=0; i<desc.size(); i++)
    {
        QString fieldName=desc.ElementName(i).c_str();

        fieldNames.push_back(fieldName);
        EditWidgetField* fe=EditWidgetField::create(fieldName,this);
        fe->init();
        fieldsMap[fieldName]=fe;
        fieldsLayout->addWidget(fe);

    }

    QWidget* fieldsWidget=new QWidget;
    QScrollArea* area=new QScrollArea(this);
    fieldsWidget->setLayout(fieldsLayout);
    area->setWidget(fieldsWidget);
    mainLayout->addWidget(area);
    delete layout();
    setLayout(mainLayout);



}





const Markov_IO::ABC_Saveable *MacrorEditWindow::getFieldClass(QString fieldName)const
{
    return desc.ElementClass(fieldName.toStdString());
}

QString MacrorEditWindow::getFieldValue(QString fieldName)const
{
    return QString(desc.ElementValue(desc.NameIndex(fieldName.toStdString())).c_str());
}

const Markov_IO::ABC_Object* MacrorEditWindow::getFieldObject(QString fieldName) const{
    return desc[fieldName.toStdString()];
}


QString MacrorEditWindow::getFieldTip(QString fieldName)const
{
    return QString(desc.Tip(desc.NameIndex(fieldName.toStdString())).c_str());
}

QString MacrorEditWindow::getFieldWhatThis(QString fieldName)const
{
    return QString(desc.WhatThis(desc.NameIndex(fieldName.toStdString())).c_str());

}

QString MacrorEditWindow::getAlias()const
{
    return alias;
}





bool MacrorEditWindow::replaceField(QString fieldName,QString newValue)
{
    return desc.ReplaceElement(fieldName.toStdString(),newValue.toStdString());
}
bool MacrorEditWindow::replaceField(QString fieldName,const Markov_IO::ABC_Object* newObject)
{
   return desc.ReplaceElement(fieldName.toStdString(),*newObject);

}


void MacrorEditWindow::accept()
{
    for (int i=0;i<fieldNames.size();++i)
    {
        fieldsMap[fieldNames.at(i)]->updateValue();
    }

    Markov_IO::ABC_Saveable* vv=v->clone();
    vv->LoadFromDescription(desc);

    if (pw_)
    {
        pw_->replaceField(myFieldName,vv);
    }
    else
    {
        cm_->add_var(alias.toStdString(),vv);
    }

QDialog::accept();

}








///  destructor
MacrorEditCommand::~MacrorEditCommand(){}



MacrorEditCommand::MacrorEditCommand(Markov_Console::Markov_CommandManager* cm):
    EditCommand(cm)
{}



bool MacrorEditCommand::run(const std::string& varname)

{
    if (cm_->has_var(varname))
    {
        MacrorEditWindow* eW=new MacrorEditWindow(QString(varname.c_str()),cm_);
        eW->show();
        return true;
    }
    else if (cm_->has_child(varname))
      {
        Markov_GUI::EditVariableDialog*
            eD=new Markov_GUI::EditVariableDialog(nullptr,cm_->getChild(varname));
        eD->show();
        return true;

      }
    else

        return false;
}








