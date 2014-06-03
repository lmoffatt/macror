#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QTableWidget>

#include "Markov_GUI/CreateQModelWizard.h"
#include "Markov_LA/matrixRelational.h"
#include "Markov_Mol/QMarkovModel.h"


CreateQModelWizard::CreateQModelWizard(QString name, Markov_Console::Markov_CommandManager *command):
    alias(name),
    cm_(command)
{
    CreateQModelPage0* page0=new CreateQModelPage0;
    CreateQModelPage1* page1=new CreateQModelPage1;
    CreateQModelPage2* page2=new CreateQModelPage2;


  addPage(page0);
  addPage(page1);
  addPage(page2);

 // connect(page0,SIGNAL(numberOfStates(int)),page1,SLOT(setNumberStates(int)));


}

void  CreateQModelWizard::accept()
{
   // QDialog::accept() calls validatePage()!!
    QDialog::accept();
    std::string name=field("name").toString().toStdString();
    double gamma=field("gamma").toDouble();
    Markov_Mol::Q_Markov_Model* Q=new Markov_Mol::Q_Markov_Model(cm_,name,Q_,*g_,*a_,gamma);
    cm_->add_var(alias.toStdString(),Q);
}


void  CreateQModelWizard::setAgonistVector(Markov_LA::M_Matrix<std::size_t> * a){
    a_=a;
}

void CreateQModelWizard::setConductanceVector(Markov_LA::M_Matrix<double> * g)
{
    g_=g;
}

void CreateQModelWizard::setQMatrix(const Markov_LA::M_Matrix<double>& Q)
{
    Q_=Q;
}




CreateQModelPage0::CreateQModelPage0(QWidget* parent):
    QWizardPage(parent)
{
    setTitle(tr("Channel Model Creation"));
    setSubTitle(tr("Specify basic information about the class for which you "
                   "want to generate skeleton source code files."));

    QLabel* nameLabel = new QLabel(tr("&Identifying name:"));
    nameEdit = new QLineEdit;
    nameLabel->setBuddy(nameEdit);

    QLabel* statesLabel = new QLabel(tr("&Number of states:"));
    numberStates = new QSpinBox;
    statesLabel->setBuddy(numberStates);


    registerField("name*", nameEdit);
    registerField("nstates*", numberStates);


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameEdit, 0, 1);
    layout->addWidget(statesLabel, 1, 0);
    layout->addWidget(numberStates, 1, 1);
    setLayout(layout);
}


bool  CreateQModelPage0::validatePage()
{
    if (QWizardPage::validatePage())
    {
    emit numberOfStates(this->numberStates->value());
    return true;
    }
    else return false;
}




CreateQModelPage1::CreateQModelPage1(QWidget *parent):
    QWizardPage(parent)
{
    setTitle(tr("States characteristics"));
    setSubTitle(tr("Specify number of agonist bound and conductance of each state."));

//! [10]
    QLabel* agonistLabel = new QLabel(tr("&AgonistVector"));
    agonistVector = new QTableWidget;
    agonistLabel->setBuddy(agonistVector);

    QLabel* gammaLabel = new QLabel(tr("&maximal conductance"));
    gammaSB = new QDoubleSpinBox;
    gammaLabel->setBuddy(gammaSB);

    QLabel* conductanceLabel = new QLabel(tr("&Conductance vector"));
    conductanceVector = new QTableWidget;
    conductanceLabel->setBuddy(conductanceVector);


    registerField("gamma", gammaSB,"value","valueChanged()");
    registerField("gamma*", gammaSB,"value","valueChanged()");

 //   registerField("conductance*", conductanceVector);


     QGridLayout* layout = new QGridLayout;
    layout->addWidget(agonistLabel, 0, 0);
    layout->addWidget(agonistVector, 1, 0);
    QHBoxLayout* ly=new QHBoxLayout;
    ly->addWidget(gammaLabel);
    ly->addWidget(gammaSB);

    layout->addLayout(ly, 2, 0,1,1);
    layout->addWidget(conductanceLabel, 3, 0);
    layout->addWidget(conductanceVector, 4, 0);
    setLayout(layout);
    connect(conductanceVector,SIGNAL(itemChanged(QTableWidgetItem*)),
            this,SIGNAL(completeChanged()));

//    connect(conductanceVector,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(aca()));

}


void CreateQModelPage1::aca()
{
    bool iscol;

}

void CreateQModelPage1::setNumberStates(int n)
{
    agonistVector->setColumnCount(n);
    conductanceVector->setColumnCount(n);

}


void CreateQModelPage1::initializePage()
{
    int n=field(tr("nstates")).toInt();
    agonistVector->setRowCount(1);
    conductanceVector->setRowCount(1);
    agonistVector->setColumnCount(n);
    conductanceVector->setColumnCount(n);
    a=Markov_LA::M_Matrix<std::size_t>(1,std::size_t(agonistVector->columnCount()));
    g=Markov_LA::M_Matrix<double>(std::size_t(conductanceVector->columnCount()),1);

    wizard()->setAgonistVector(&a);
    wizard()->setConductanceVector(&g);

    for (int j=0; j<n;j++)
    {
        if (!agonistVector->item(0,j))
        {
            QTableWidgetItem* item= new QTableWidgetItem;
            item->setData(Qt::EditRole,QVariant(uint(0)));
            agonistVector->setItem(0,j,item);
        }
        if (!conductanceVector->item(0,j))
        {
            QTableWidgetItem* item= new QTableWidgetItem;
            item->setData(Qt::EditRole,QVariant(double(0)));
            conductanceVector->setItem(0,j,item);
        }
    }
}

bool CreateQModelPage1::validatePage()
{

        for (std::size_t i=0;i<ncols(a);i++)
            a(0,i)=agonistVector->item(0,i)->data(Qt::EditRole).toInt();
        for (std::size_t i=0;i<nrows(g);i++)
            g(i,0)=conductanceVector->item(0,i)->data(Qt::EditRole).toDouble();
        if (!(g==0.0))
        {
            return true;

        }
    return false;
}


CreateQModelWizard* CreateQModelPage1::wizard(){
return dynamic_cast<CreateQModelWizard*>(QWizardPage::wizard());
    }



CreateQModelPage2::CreateQModelPage2(QWidget *parent):
    QWizardPage(parent)
{
    setTitle(tr("Q-Matrix"));
    setSubTitle(tr("Specify the rates."));

//! [10]
    QLabel* QMatrixLabel = new QLabel(tr("&Q-Matrix"));
    QMatrixTable = new QTableWidget;
    QMatrixLabel->setBuddy(QMatrixTable);

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(QMatrixLabel, 0, 0);
    layout->addWidget(QMatrixTable, 1, 0);
    setLayout(layout);
    connect(QMatrixTable,SIGNAL(cellChanged(int,int)),this,SLOT(setKij(int,int)));


}

void CreateQModelPage2::initializePage()
{
    int n=field(tr("nstates")).toInt();
    QMatrixTable->setRowCount(n);
    QMatrixTable->setColumnCount(n);
    if (ncols(Q)!=std::size_t(n))
    {
        Q=Markov_LA::M_Matrix<double>(std::size_t(n),std::size_t(n));
        wizard()->setQMatrix(Q);
    }
    for (int i=0; i<n;i++)
    {

        for (int j=0; j<n;j++)
        {
            if (!QMatrixTable->item(i,j))
            {
                if (i!=j)
                {
                    QTableWidgetItem* item= new QTableWidgetItem;
                    item->setData(Qt::EditRole,QVariant(double(0)));
                    QMatrixTable->setItem(i,j,item);
                }
                else
                {
                    QTableWidgetItem* item= new QTableWidgetItem;
                    item->setFlags(item->flags()&~Qt::ItemIsEnabled);
                    item->setData(Qt::DisplayRole,QVariant(double(0)));

                    QMatrixTable->setItem(i,j,item);

                }
            }
        }
    }
}

void CreateQModelPage2::updateDiag(int i)
{
    int n=field(tr("nstates")).toInt();
    double sum=0;
    for (int j=0; j<n;j++)
    {
        if (i!=j)
        {
            bool valid;
            sum-=QMatrixTable->item(i,j)->data(Qt::EditRole).toDouble(&valid);
        }
    }
    QMatrixTable->item(i,i)->setData(Qt::DisplayRole,QVariant(sum));
    return;
}


void CreateQModelPage2::setKij(int i, int j)
{
    bool valid;
     double kij=QMatrixTable->item(i,j)->data(Qt::EditRole).toDouble(&valid);
     if (valid && kij>0)
     {
         updateDiag( i);
         if (QMatrixTable->item(j,i)->data(Qt::EditRole).toDouble(&valid)<=0)
             QMatrixTable->setCurrentCell(j,i);
     }

}



bool CreateQModelPage2::validatePage()
{

    for (std::size_t i=0;i<nrows(Q);i++)
    {
        for (std::size_t j=0;j<ncols(Q);j++)
        {
           bool valid;
           Q(i,j)=QMatrixTable->item(i,j)->data(Qt::EditRole).toDouble(&valid);
           if (!valid)
               return false;
         }
    }
    wizard()->setQMatrix(Q);
    return true;

}
CreateQModelWizard* CreateQModelPage2::wizard(){
return dynamic_cast<CreateQModelWizard*>(QWizardPage::wizard());
    }


