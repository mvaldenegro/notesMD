/* 
 * File:   NoteModel.h
 * Author: mvaldenegro
 *
 * Created on July 26, 2013, 2:21 AM
 */

#ifndef NOTEMODEL_H
#define	NOTEMODEL_H

#include <QAbstractListModel>

#include <models/Notebook.h>

class NoteModel : public QAbstractListModel
{
    Q_OBJECT
    
    public:
        NoteModel(QObject *parent = nullptr);
        virtual ~NoteModel();
    
        virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
        virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;    
        
        Notebook::Ptr notebook() const
        {
            return mNotebook;
        }
        
        void setNotebook(Notebook::Ptr notebook)
        {
            mNotebook = notebook;
            
            reset();
        }
        
    public slots:
        void invalidateData();
        
    private:
        Notebook::Ptr mNotebook;
};

#endif	/* NOTEMODEL_H */

