/* 
 * File:   NotesPanel.h
 * Author: mvaldenegro
 *
 * Created on July 26, 2013, 12:56 AM
 */

#ifndef NOTESPANEL_H
#define	NOTESPANEL_H

#include <QDockWidget>
#include <QModelIndex>

#include <models/Notebook.h>

class QListView;
class QToolBar;
class QLabel;

class KLineEdit;

class NoteModel;

class NotesPanel : public QDockWidget
{
    Q_OBJECT
    
    public:
        NotesPanel(QWidget *parent = nullptr);
        virtual ~NotesPanel();
        
    signals:
        void selected(Note::Ptr note);
        
    public slots:
        void display(Notebook::Ptr notebook);
        
    private slots:
        void activated(const QModelIndex& index);
        
    private:
        KLineEdit *mSearchLineEdit;
        QListView *mNotesView;
        NoteModel *mNotesModel;
};

#endif	/* NOTESPANEL_H */

