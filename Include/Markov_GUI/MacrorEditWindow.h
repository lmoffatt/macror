#ifndef MACROREDITWINDOW_H
#define MACROREDITWINDOW_H

#include <QDialog>
#include <QList>
#include <QDialogButtonBox>
#include <QString>
#include <QMap>
#include <QTableWidget>

#include "Markov_LA/Matrix.h"
#include "Markov_Console/Markov_CommandManager.h"
#include "Markov_Console/ABC_Command.h"

#include "Markov_Console/EditCommand.h"
#include "Markov_GUI/EditWidgetField.h"



class QLabel;
class QLineEdit;
class QComboBox;
class MacrorEditWindow;


class MacrorEditCommand:public Markov_Console::EditCommand
{
public:
    MacrorEditCommand(Markov_Console::Markov_CommandManager* cm);

    /// virtual destructor
    virtual ~MacrorEditCommand();


    /// runs the command for a list of parameters
    virtual bool run(const std::string &varname);


};




class MacrorEditWindow: public QDialog
{
    Q_OBJECT
public:
    MacrorEditWindow(QString Qvarname,Markov_Console::Markov_CommandManager* cm,
                       QWidget* parent=0);

    MacrorEditWindow(QString fieldName,MacrorEditWindow* parent);


    const Markov_IO::ABC_Saveable* getFieldClass(QString fieldName) const;

    QString getFieldValue(QString fieldName)const;

    const Markov_IO::ABC_Object *getFieldObject(QString fieldName)const;

    QString getFieldTip(QString fieldName)const;

    QString getFieldWhatThis(QString fieldName)const;


    bool replaceField(QString fieldName,QString newValue);

    bool replaceField(QString fieldName,const Markov_IO::ABC_Object* newObject);


    void setFieldObject(Markov_IO::ABC_Saveable* obj);

    QString getAlias()const;

public slots:
    void accept();
    void changeClass(QString newClass);

signals:
    void editButtonPressed(QString fieldName);

private:
     void init();
     Markov_Console::Markov_CommandManager* cm_;
     MacrorEditWindow* pw_;
     QString alias;
     QString myFieldName;
     const Markov_IO::ABC_Saveable* v;
     const Markov_IO::ABC_Saveable* v_old;

     Markov_IO::ClassDescription desc;

     QDialogButtonBox* buttonBox;


     QLabel* nameLabel;
     QLineEdit* nameEdit;

     QLabel* classLabel;
     QComboBox* classEdit;

     QLabel* superClassLabel;
     QLineEdit* superClassEdit;

     QVector<QString> fieldNames;
     QMap<QString,EditWidgetField*> fieldsMap;

 };



#endif // MACROREDITWINDOW_H
