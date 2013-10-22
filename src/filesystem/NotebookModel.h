/* 
 * File:   NotebookModel.h
 * Author: mvaldenegro
 *
 * Created on July 26, 2013, 1:17 AM
 */

#ifndef NOTEBOOKMODEL_H
#define	NOTEBOOKMODEL_H

#include <QAbstractListModel>

class NotebookModel : public QAbstractListModel
{
    Q_OBJECT
    
    public:
        NotebookModel(QObject *parent = nullptr);
        virtual ~NotebookModel();
        
        virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
        virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
        
        virtual QModelIndex index(int row, int column = 0, const QModelIndex& parent = QModelIndex()) const;

    public slots:
        void invalidateData();
};

#endif	/* NOTEBOOKMODEL_H */

