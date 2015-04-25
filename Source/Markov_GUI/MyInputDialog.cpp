#include "Markov_GUI/MyInputDialog.h"
#include <QListWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>
namespace Markov_GUI {

  QString MyInputDialog::getItem(QWidget *parent, QString title,   QStringList items, bool* ok, int current)
  {

    QLabel selected;
    MyInputDialog * d= new MyInputDialog(parent,title,items,current);
    connect(d,SIGNAL(selectedItem(QString)),&selected,SLOT(setText(QString)));

    if (d->exec()==QDialog::Accepted)
      {

      *ok=true;
      return selected.text();
      }
    else
      {
        *ok=false;
      return {};
      }
  }

  std::string MyInputDialog::getItem(QWidget *parent, const std::string &title, const std::vector<std::string> &items, bool *ok, int current)
  {
    QStringList list;
    for (auto it:items)
      list<<QString(it.c_str());

    QString res=getItem(parent, QString(title.c_str()),list,ok,current);
    return res.toStdString();
  }

  void MyInputDialog::accept()
  {
    emit selectedItem(itemsList->currentItem()->text());
    QDialog::accept();
  }

  int MyInputDialog::exec()
  {
    show();
    activateWindow();
  //  raise();
    setEnabled(true);
     return QDialog::exec();
  }





  void MyInputDialog::keyPressEvent(QKeyEvent *e)
  {
    switch(e->key())
      {
      case Qt::Key_Enter:
        {
          accept();
        }
       break;
      case Qt::Key_Escape:
        {
          reject();
        }
       break;
      default:
        {
          itemsList->setFocus();
          QDialog::keyPressEvent(e);
        }

      }


  }

  void MyInputDialog::mousePressEvent(QMouseEvent *)
  {
    accept();

  }


  MyInputDialog::MyInputDialog(QWidget *parent, const QString &title,  const QStringList &items,int current):
    QDialog(parent,Qt::Dialog)
  {
    QLabel* myTitle=new QLabel;
    myTitle->setText(title);
    itemsList=new QListWidget;
    itemsList->addItems(items);

    itemsList->setCurrentRow(current);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(myTitle);
    mainLayout->addWidget(itemsList);

    QPushButton * okBt=new QPushButton("OK");
    QPushButton * clBt=new QPushButton("Cancel");
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(clBt);
    buttonLayout->addWidget(okBt);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    connect(okBt,SIGNAL(pressed()),this,SLOT(accept()));
    connect(clBt,SIGNAL(pressed()),this,SLOT(reject()));
    connect(itemsList,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(accept()));
    okBt->setDefault(true);

    setWindowModality(Qt::ApplicationModal);
  }




}
