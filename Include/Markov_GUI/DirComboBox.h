#ifndef DIRCOMBOBOX_H
#define DIRCOMBOBOX_H

#include <QWidget>
#include <QDir>

QT_BEGIN_NAMESPACE
class QComboBox;
class QLabel;
class QPushButton;
class QTableWidget;
class QTableWidgetItem;
QT_END_NAMESPACE



class DirComboBox:public QWidget
{
    Q_OBJECT

public:
    DirComboBox(QDir initDir, QString label, QWidget *parent = 0);

private slots:
    void browse();

signals:
    void changeDirectory(QString newDir);

private:
    QComboBox *directoryComboBox;
    QLabel *directoryLabel;
    QPushButton *browseButton;

    QDir currentDir;
};


#endif // DIRCOMBOBOX_H
