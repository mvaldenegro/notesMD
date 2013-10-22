/* 
 * File:   FilesystemInterface.h
 * Author: mvaldenegro
 *
 * Created on July 30, 2013, 8:50 PM
 */

#ifndef NOTEBOOKDAO_H
#define	NOTEBOOKDAO_H

#include <models/Notebook.h>
#include <models/Note.h>

#include <QObject>

class FilesystemInterface : public QObject
{
    Q_OBJECT
    
    public:
        FilesystemInterface(QObject *parent = nullptr);
        virtual ~FilesystemInterface();
        
        Notebook::Ptr notebookByName(const QString& name) const;
        Notebook::List notebooks() const;
        
        bool save(Notebook::Ptr notebook);
        
        bool rename(Notebook::Ptr notebook);        
        bool remove(Notebook::Ptr notebook);
                
        bool save(Note::Ptr note);
        bool update(Note::Ptr note);
        bool remove(Note::Ptr note);
        
        void saveConfig();
        
    signals:
        void added(Notebook::Ptr notebook);
        void removed(Notebook::Ptr notebook);
        void modified(Notebook::Ptr notebook);
        
        void added(Note::Ptr note);
        void removed(Note::Ptr note);
        void modified(Note::Ptr note);
                
    private:
        void loadNotebooks();
        Notebook::Ptr loadNotebook(const QString& folder);
        
        Notebook::List mNotebooks;
};

#endif	/* NOTEBOOKDAO_H */

