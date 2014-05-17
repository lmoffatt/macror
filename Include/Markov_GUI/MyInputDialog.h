#ifndef MYINPUTDIALOG_H
#define MYINPUTDIALOG_H

#include <QDialog>
#include <QListWidget>


namespace Markov_GUI {

  class MyInputDialog: public QDialog
  {
    Q_OBJECT
  public:

    static QString getItem(QWidget *  parent,
                           const QString & title,
                           const QStringList & items,
                           bool *ok,
                           int current = 0);

    void accept();

  public slots:
    int exec();

  signals:
    void selectedItem(QString);

  protected:
    void keyPressEvent(QKeyEvent *e);

    void mousePressEvent(QMouseEvent *m);

  private:

    MyInputDialog(QWidget *parent, const QString &title,  const QStringList &items, int current);

    QListWidget *itemsList;


  };

}



#endif // MYINPUTDIALOG_H
