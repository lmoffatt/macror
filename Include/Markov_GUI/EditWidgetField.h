#ifndef EDITWIDGETFIELD_H
#define EDITWIDGETFIELD_H

#include <QString>
#include <QList>
#include <QWidget>

#include "Markov_IO/ClassDescription.h"
#include "Markov_LA/Matrix.h"



class QWidget;
class QLineEdit;
class QTableView;
class MacrorEditWindow;
class MacrorVarEditWindow;



class EditWidgetField:public QWidget
{
    Q_OBJECT
public:
    EditWidgetField(QString fieldName,MacrorEditWindow* parentW );
    enum Type{BOOL,SIZE,DOUBLE,STRING,MSIZET,MDOUBLE,SAVEABLE,INVALID};


    static EditWidgetField* create(QString fieldName,MacrorEditWindow* parentW);

    Type type;

    virtual ~EditWidgetField(){}
    void virtual init();
 public slots:
    virtual void editMe();
    virtual void updateValue();
 protected:
    MacrorEditWindow* pw;
    QString name;
    const Markov_IO::ABC_Saveable* v;
    const Markov_IO::ABC_Object* o;
    Markov_IO::ClassDescription desc;

    Markov_LA::M_Matrix<std::size_t> mu_;
    int nrow, ncol;

    QLineEdit* lineEdit;
    QTableView* table;
    QList<QList<QLineEdit*> > lineEditArray;

};


#endif // EDITWIDGETFIELD_H
