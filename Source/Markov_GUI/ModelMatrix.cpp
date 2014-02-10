#include "Markov_GUI/ModelMatrix.h"
#include "Markov_LA/auxiliarMath.h"
#include "Markov_LA/matrixSum.h"
#include "Markov_LA/matrixInit.h"
#include "Markov_Mol/QMarkovModel.h"


ModelMatrix::ModelMatrix(Markov_LA::M_Matrix<double> *matrix,QObject *parent):
  QAbstractTableModel(parent),
  m(matrix),s(0)
{
}


ModelMatrix::ModelMatrix(Markov_LA::M_Matrix<std::size_t> *matrix,QObject *parent):
  QAbstractTableModel(parent),
  m(0),
  s(matrix)
{
}




int ModelMatrix::rowCount(const QModelIndex &parent) const
{
  if (m)
    return Markov_LA::nrows(*m);
  if (s)
    return Markov_LA::nrows(*s);
  return -1;
}
int ModelMatrix::columnCount(const QModelIndex &parent) const
{
  if (m)
    return Markov_LA::ncols(*m);
  if (s)
    return Markov_LA::ncols(*s);
  return -1;
}


bool ModelMatrix::insertRows(int row, int count, const QModelIndex &parent)
{
  if (row>rowCount())
    return false;
  else
    {
      if (count==0)
        return true;
      if (m)
        {
          Markov_LA::M_Matrix<double> newMatrix(rowCount()+count,columnCount());
          for (std::size_t j=0; j<columnCount();++j)
            {
              for (std::size_t i=0;i<row;++i)
                newMatrix(i,j)=(*m)(i,j);
              for (std::size_t i=row; i<row+count;++i)
                newMatrix(i,j)=0;
              for (std::size_t i=row; i<rowCount(); ++i)
                newMatrix(i+count,j)=(*m)(i,j);
            }
          beginInsertRows(parent,row,row+count-1);
          *m=newMatrix;
          endInsertRows();
          return true;
        }
      else if (s)
        {

          Markov_LA::M_Matrix<std::size_t> newMatrix(rowCount()+count,columnCount());
          for (std::size_t j=0; j<columnCount();++j)
            {
              for (std::size_t i=0;i<row;++i)
                newMatrix(i,j)=(*s)(i,j);
              for (std::size_t i=row; i<row+count;++i)
                newMatrix(i,j)=0;
              for (std::size_t i=row; i<rowCount(); ++i)
                newMatrix(i+count,j)=(*s)(i,j);
            }
          beginInsertRows(parent,row,row+count-1);
          *s=newMatrix;
          endInsertRows();
          return true;
        }
      else
        return false;

    }
}

bool ModelMatrix::insertColumns(int column, int count, const QModelIndex &parent)
{
  if (column>columnCount())
    return false;
  else
    {
      if (count==0)
        return true;
      if (m)
        {
          Markov_LA::M_Matrix<double> newMatrix(rowCount(),columnCount()+count);
          for (std::size_t i=0; i<rowCount();++i)
            {
              for (std::size_t j=0;j<column;++j)
                newMatrix(i,j)=(*m)(i,j);
              for (std::size_t j=column; j<column+count;++j)
                newMatrix(i,j)=0;
              for (std::size_t j=column; j<columnCount(); ++j)
                newMatrix(i,j+count)=(*m)(i,j);
            }
          beginInsertColumns(parent,column,column+count-1);
          *m=newMatrix;
          endInsertColumns();
          return true;
        }
      else if (s)
        {
          Markov_LA::M_Matrix<std::size_t> newMatrix(rowCount(),columnCount()+count);
          for (std::size_t i=0; i<rowCount();++i)
            {
              for (std::size_t j=0;j<column;++j)
                newMatrix(i,j)=(*s)(i,j);
              for (std::size_t j=column; j<column+count;++j)
                newMatrix(i,j)=0;
              for (std::size_t j=column; j<columnCount(); ++j)
                newMatrix(i,j+count)=(*s)(i,j);
            }
          beginInsertColumns(parent,column,column+count-1);
          *s=newMatrix;
          endInsertColumns();
          return true;
        }
      else
        return false;

    }
}


bool ModelMatrix::removeColumns(int column, int count, const QModelIndex &parent)
{
  if (column+count>columnCount())
    return false;
  else
    {
      if (count==0)
        return true;
      if (m)
        {
          Markov_LA::M_Matrix<double> newMatrix(rowCount(),columnCount()-count);
          for (std::size_t i=0; i<rowCount();++i)
            {
              for (std::size_t j=0;j<column;++j)
                newMatrix(i,j)=(*m)(i,j);
              for (std::size_t j=column+count; j<columnCount(); ++j)
                newMatrix(i,j-count)=(*m)(i,j);
            }
          beginRemoveColumns(parent,column,column+count-1);
          *m=newMatrix;
          endRemoveColumns();
          return true;
        }
      else if (s)
        {
          Markov_LA::M_Matrix<std::size_t> newMatrix(rowCount(),columnCount()-count);
          for (std::size_t i=0; i<rowCount();++i)
            {
              for (std::size_t j=0;j<column;++j)
                newMatrix(i,j)=(*s)(i,j);
              for (std::size_t j=column+count; j<columnCount(); ++j)
                newMatrix(i,j-count)=(*s)(i,j);
            }
          beginRemoveColumns(parent,column,column+count-1);
          *s=newMatrix;
          endRemoveColumns();
          return true;
        }
      else
        return false;

    }
}




bool ModelMatrix::removeRows(int row, int count, const QModelIndex &parent)
{
  if (row+count>rowCount())
    return false;
  else
    {
      if (count==0)
        return true;
      if (m)
        {
          Markov_LA::M_Matrix<double> newMatrix(rowCount()-count,columnCount());
          for (std::size_t j=0; j<columnCount();++j)
            {
              for (std::size_t i=0;i<row;++i)
                newMatrix(i,j)=(*m)(i,j);
              for (std::size_t i=row+count; i<rowCount(); ++i)
                newMatrix(i-count,j)=(*m)(i,j);
            }
          beginRemoveRows(parent,row,row+count-1);
          *m=newMatrix;
          endRemoveRows();
          return true;
        }
      else if (s)
        {

          Markov_LA::M_Matrix<std::size_t> newMatrix(rowCount()-count,columnCount());
          for (std::size_t j=0; j<columnCount();++j)
            {
              for (std::size_t i=0;i<row;++i)
                newMatrix(i,j)=(*s)(i,j);
              for (std::size_t i=row+count; i<rowCount(); ++i)
                newMatrix(i-count,j)=(*s)(i,j);
            }
          beginRemoveRows(parent,row,row+count-1);
          *s=newMatrix;
          endRemoveRows();
          return true;
        }
      else
        return false;

    }
}






QVariant ModelMatrix::data(const QModelIndex &index, int role ) const
{
  if (!index.isValid())
    return QVariant();

  if (role != Qt::DisplayRole && role != Qt::EditRole)
    return QVariant();
  if (m)
    return QVariant((*m)(index.row(),index.column()));
  else if (s)
    return QVariant(qulonglong((*s)(index.row(),index.column())));
  else
    return QVariant();
}

bool  ModelMatrix::setData(const QModelIndex &index, const QVariant &value, int role)
{
  if (role != Qt::EditRole)
    return false;

  if (m &&(index.row()<Markov_LA::nrows(*m))&&(index.column()<Markov_LA::ncols(*m)))
    {
      bool ok;

      (*m)(index.row(),index.column())=value.toDouble(&ok);
      if (ok)
        emit dataChanged(index, index);

      return ok;
    }
  if (s &&(index.row()<Markov_LA::nrows(*s))&&(index.column()<Markov_LA::ncols(*s)))
    {
      bool ok;

      (*s)(index.row(),index.column())=value.toUInt(&ok);
      if (ok)
        emit dataChanged(index, index);

      return ok;
    }

  return false;
}

Qt::ItemFlags ModelMatrix::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return 0;

  return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable|Qt::ItemIsDropEnabled;
}


QVariant ModelMatrix::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role==Qt::DisplayRole)
    {
      if ((orientation==Qt::Horizontal)
          &&(! HheaderData.isEmpty())
          &&(HheaderData.contains(section)))
        return HheaderData[section];
      else if  ((orientation==Qt::Vertical)
                &&(! VheaderData.isEmpty())
                &&(VheaderData.contains(section)))
        return VheaderData[section];
      else
        {
          QVariant res(QString("%1").arg(section));
          return res;
        }
    }
  else
    return QVariant();
}




bool ModelMatrix::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{

  if (orientation==Qt::Vertical)
    {
      VheaderData[section]=value;
      return true;
    }
  if (orientation==Qt::Horizontal)
    {
      HheaderData[section]=value;
      return true;
    }
  return false;
}





ModelQMatrix::ModelQMatrix(Markov_LA::M_Matrix<double> *matrix,QObject *parent):
  ModelMatrix(matrix,parent),
  Z(Markov_LA::zeros<double>(Markov_LA::nrows(*m),1))
{
}


bool  ModelQMatrix::setData(const QModelIndex &index, const QVariant &value, int role)
{

  if (role != Qt::EditRole)
    return false;

  std::size_t i=index.row();
  std::size_t j=index.column();


  bool ok;

  double kij=value.toDouble(&ok);

  if (!ok||kij<0)
    return false;


  if (m &&(i<Markov_LA::nrows(*m))&&(j<Markov_LA::ncols(*m)))
    {
      (*m)(i,j)=kij;
      if ((*m)(i,j)==0)
        {
          bool hasloops;
          Z=Markov_Mol::getPartitionVector(*m,Markov_Mol::getConnectionMap(*m),hasloops,false);
        }
      if ((Z[j]!=0)&&(Z[i]!=0))
        {
          (*m)(j,i)=(*m)(i,j)*Z[i]/Z[j];
          (*m)(j,j)=0;
          (*m)(j,j)=-Markov_LA::totalsum((*m)(j,":"));
        }

      if (((*m)(i,j)>0.0)&&((*m)(j,i)<=0.0))
        {
          bool hasloops;
          Z=Markov_Mol::getPartitionVector(*m,Markov_Mol::getConnectionMap(*m),hasloops,false);
          if ((Z[j]!=0)&&(Z[i]!=0))
            {
              (*m)(j,i)=(*m)(i,j)*Z[i]/Z[j];
              (*m)(j,j)=0;
              (*m)(j,j)=-Markov_LA::totalsum((*m)(j,":"));
            }

        }
      (*m)(i,i)=0;
      (*m)(i,i)=-Markov_LA::totalsum((*m)(i,":"));
      emit dataChanged(index, index);
      if (((*m)(i,j)>0.0)&&((*m)(j,i)<=0.0))
        emit moveToCell(j,i);
      return true;

    }

  return false;
}

Qt::ItemFlags ModelQMatrix::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return 0;

  if (index.row()==index.column())
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

  return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable|Qt::ItemIsDropEnabled;
}




//! [0]
LineEditDelegate::LineEditDelegate(QObject *parent)
  : QItemDelegate(parent)
{
}
//! [0]

//! [1]
QWidget *LineEditDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &/* option */,
                                        const QModelIndex &/* index */) const
{
  QLineEdit *editor = new QLineEdit(parent);

  QDoubleValidator* val=new QDoubleValidator;
  editor->setValidator(val);
  //editor->setText(QString().arg(val));

  return editor;
}
//! [1]

//! [2]
void LineEditDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const
{
  double value = index.model()->data(index, Qt::EditRole).toDouble();

  QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
  lineEdit->setText(QString("%1").arg(value,0,'g',14));
}
//! [2]

//! [3]
void LineEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
  QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
  QString label=lineEdit->text();
  bool ok;
  double value =label.toDouble(&ok) ;
  if (ok)
    model->setData(index, value, Qt::EditRole);
}
//! [3]

//! [4]
void LineEditDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
  editor->setGeometry(option.rect);
}

