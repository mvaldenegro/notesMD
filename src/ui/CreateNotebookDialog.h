/* 
 * File:   CreateNotebookDialog.h
 * Author: mvaldenegro
 *
 * Created on July 30, 2013, 3:52 AM
 */

#ifndef _CREATENOTEBOOKDIALOG_H
#define	_CREATENOTEBOOKDIALOG_H

#include "ui_CreateNotebookDialog.h"

class CreateNotebookDialog : public QDialog
{
    Q_OBJECT
    public:
        CreateNotebookDialog();
        virtual ~CreateNotebookDialog();
        
        static QString getNotebookFolder();
        
    private slots:
        void openFolderDialog();
        void updateNotebookFolder();
        
        bool validate();
        
    private:
        Ui::CreateNotebookDialog widget;
};

#endif	/* _CREATENOTEBOOKDIALOG_H */
