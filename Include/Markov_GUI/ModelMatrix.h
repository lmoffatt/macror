#ifndef MODELMATRIX_H
#define MODELMATRIX_H
#include <QAbstractTableModel>

#include "Markov_LA/Matrix.h"
#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QSize>
#include <QLineEdit>
#include <QTableWidget>
#include <QApplication>
#include <QClipboard>
#include <QMessageBox>
#include <QKeyEvent>
//! [0]
class LineEditDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    LineEditDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;
};


class ModelMatrix: public QAbstractTableModel
{
   Q_OBJECT

 public:
     ModelMatrix(Markov_LA::M_Matrix<double> *matrix,QObject *parent = 0);
     ModelMatrix(Markov_LA::M_Matrix<std::size_t> *matrix,QObject *parent = 0);


     int rowCount(const QModelIndex &parent = QModelIndex()) const;
     int columnCount(const QModelIndex &parent = QModelIndex()) const;

     bool insertRows(int row, int count, const QModelIndex &parent= QModelIndex());
     bool insertColumns(int column, int count, const QModelIndex &parent= QModelIndex());

     bool removeColumns(int column, int count, const QModelIndex &parent= QModelIndex());
     bool removeRows(int row, int count, const QModelIndex &parent= QModelIndex());

     QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

     QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

     bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role);
     virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

     virtual Qt::ItemFlags flags(const QModelIndex &index) const;

protected:

     Markov_LA::M_Matrix<double> *m;
     Markov_LA::M_Matrix<std::size_t> *s;
     QMap<int,QVariant> HheaderData;
     QMap<int,QVariant> VheaderData;


 };




// QTableWidget with support for copy and paste added
// Here copy and paste can copy/paste the entire grid of cells
class QTableWidgetWithCopyPaste : public QTableWidget
{
public:
  QTableWidgetWithCopyPaste(int rows, int columns, QWidget *parent) :
      QTableWidget(rows, columns, parent)
  {}

  QTableWidgetWithCopyPaste(QWidget *parent) :
  QTableWidget(parent)
  {}



private:
  void copy();
  void paste();

protected:
  virtual void keyPressEvent(QKeyEvent * event);
};





class ModelQMatrix: public ModelMatrix
{
   Q_OBJECT

 public:
     ModelQMatrix(Markov_LA::M_Matrix<double> *matrix,QObject *parent = 0);


     virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

     virtual Qt::ItemFlags flags(const QModelIndex &index) const;
signals:
     void moveToCell(int i, int j);
private:
     Markov_LA::M_Matrix<double> Z; //partition matrix for compelling reversibility
};





#endif // MODELMATRIX_H
