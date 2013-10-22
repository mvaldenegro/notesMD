/*
 * File:   CreateNotebookDialog.cpp
 * Author: mvaldenegro
 *
 * Created on July 30, 2013, 3:52 AM
 */

#include <QDir>
#include <QDialogButtonBox>
#include <QPushButton>
#include <KFileDialog>

#include "CreateNotebookDialog.h"

CreateNotebookDialog::CreateNotebookDialog()
{
    widget.setupUi(this);
    
    connect(widget.notebookParentFolderButton, SIGNAL(clicked()), this, SLOT(openFolderDialog()));
    connect(widget.notebookParentFolderEdit, SIGNAL(textChanged(const QString&)), this, SLOT(updateNotebookFolder()));
    connect(widget.notebookNameEdit, SIGNAL(textChanged(const QString&)), this, SLOT(updateNotebookFolder()));
    
    validate();
}

CreateNotebookDialog::~CreateNotebookDialog()
{
}

void CreateNotebookDialog::openFolderDialog()
{
    QString folder = KFileDialog::getExistingDirectory();
    
    widget.notebookParentFolderEdit->setText(folder);
    
    validate();
}

void CreateNotebookDialog::updateNotebookFolder()
{
    QString folder = widget.notebookParentFolderEdit->text();
    QString name = widget.notebookNameEdit->text();
    
    if(validate()) {    
        widget.notebookFolderLabel->setText(folder + QDir::separator() + name);
    } else {
        widget.notebookFolderLabel->setText(QString());
    }    
}

QString CreateNotebookDialog::getNotebookFolder()
{
    CreateNotebookDialog dialog;
    QString ret;
    
    int e = dialog.exec();
    
    if(e == QDialog::Accepted) {
        ret = dialog.widget.notebookFolderLabel->text();
    }
    
    return ret;
}

bool CreateNotebookDialog::validate()
{
    bool valid = !(widget.notebookNameEdit->text().isEmpty() || widget.notebookNameEdit->text().isNull());
    valid &= !(widget.notebookParentFolderEdit->text().isEmpty() || widget.notebookParentFolderEdit->text().isNull());
    
    widget.buttonBox->button(QDialogButtonBox::Ok)->setEnabled(valid);
    
    return valid;
}