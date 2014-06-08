#ifndef EDITWIDGETMATRIXDOUBLES_H
#define EDITWIDGETMATRIXDOUBLES_H

#include "Markov_GUI/EditWidgetField.h"


class EditWidgetMatrixDoubles: public EditWidgetField
{
    Q_OBJECT
public:
    EditWidgetMatrixDoubles(QString fieldName,MacrorEditWindow* parentW );
virtual ~EditWidgetMatrixDoubles(){}
    virtual void init();
public slots:
    void editMe();
    void updateValue();
    void  ShowContextMenu(const QPoint&);
    void insertColumn();
    void insertColumn(int);
    void insertRow(int);
 protected:
    Markov_LA::M_Matrix<double> md_;
private:
    void fillTable();

 };



#endif // EDITWIDGETMATRIXDOUBLES_H
