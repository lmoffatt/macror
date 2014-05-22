#include "Markov_GUI/DirComboBox.h"
#include <QHBoxLayout>
#include <QFileDialog>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>

//! [0]
DirComboBox::DirComboBox(QDir initDir,QString label, QWidget *parent)
    : QWidget(parent),
      currentDir(initDir)
{

    browseButton = new QPushButton(tr("&Browse..."));
    connect(browseButton,SIGNAL(clicked()),this,SLOT(browse()));

    directoryComboBox = new QComboBox;
    directoryComboBox->setEditable(true);
    directoryComboBox->addItem(initDir.absolutePath());
    directoryComboBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    directoryComboBox->setMinimumContentsLength(3);

    directoryLabel = new QLabel(label);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(directoryLabel);
    mainLayout->addWidget(directoryComboBox);
    mainLayout->addWidget(browseButton);
    setLayout(mainLayout);
    connect(directoryComboBox,SIGNAL(currentIndexChanged(QString)),this,SIGNAL(changeDirectory(QString)));

}


void DirComboBox::browse()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                               tr("Working directory"), currentDir.absolutePath());

    if (!directory.isEmpty()) {
        if (directoryComboBox->findText(directory) == -1)
            directoryComboBox->addItem(directory);
        directoryComboBox->setCurrentIndex(directoryComboBox->findText(directory));
        currentDir=QDir(directory);
      }
}

void DirComboBox::setDirectory(QString directory)
{
  if (!directory.isEmpty()) {
      if (directoryComboBox->findText(directory) == -1)
          directoryComboBox->addItem(directory);
      disconnect(directoryComboBox,SIGNAL(currentIndexChanged(QString)),this,SIGNAL(changeDirectory(QString)));
      directoryComboBox->setCurrentIndex(directoryComboBox->findText(directory));
      connect(directoryComboBox,SIGNAL(currentIndexChanged(QString)),this,SIGNAL(changeDirectory(QString)));
      currentDir=QDir(directory);
    }
}




