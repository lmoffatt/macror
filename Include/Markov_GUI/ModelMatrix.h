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
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

//    void updateEditorGeometry(QWidget *editor,
//        const QStyleOptionViewItem &option, const QModelIndex &index) const;
};


class ModelMatrix: public QAbstractTableModel
{
   Q_OBJECT

 public:
     ModelMatrix(Markov_LA::M_Matrix<double> *matrix,QObject *parent = 0);
     ModelMatrix(Markov_LA::M_Matrix<std::size_t> *matrix,QObject *parent = 0);


     int rowCount(const QModelIndex &parent = QModelIndex()) const override;
     int columnCount(const QModelIndex &parent = QModelIndex()) const override;

     bool insertRows(int row, int count, const QModelIndex &parent= QModelIndex()) override;
     bool insertColumns(int column, int count, const QModelIndex &parent= QModelIndex()) override;

     bool removeColumns(int column, int count, const QModelIndex &parent= QModelIndex()) override;
     bool removeRows(int row, int count, const QModelIndex &parent= QModelIndex()) override;

     QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

     QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

     bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int) override;
      bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

      Qt::ItemFlags flags(const QModelIndex &index) const override;

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
     ModelQMatrix(Markov_LA::M_Matrix<std::size_t> *matrix,QObject *parent = 0);


      bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

      Qt::ItemFlags flags(const QModelIndex &index) const override;
signals:
     void moveToCell(int i, int j);
private:
     Markov_LA::M_Matrix<double> Z; //partition matrix for compelling reversibility
};





#endif // MODELMATRIX_H
