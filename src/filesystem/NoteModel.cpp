/* 
 * File:   NoteModel.cpp
 * Author: mvaldenegro
 * 
 * Created on July 26, 2013, 2:21 AM
 */

#include "NoteModel.h"

#include "KIcon"
#include "NotebookManager.h"

NoteModel::NoteModel(QObject *parent)
 : QAbstractListModel(parent), mNotebook(nullptr)
{
    connect(NotebookManager::instance()->filesystem(), SIGNAL(added(Note::Ptr)), this, SLOT(invalidateData()));
    connect(NotebookManager::instance()->filesystem(), SIGNAL(removed(Note::Ptr)), this, SLOT(invalidateData()));
}

NoteModel::~NoteModel()
{
}

int NoteModel::rowCount(const QModelIndex& parent) const
{
    if(notebook()) {
        return notebook()->notes().count();
    }
    
    return 0;
}

QVariant NoteModel::data(const QModelIndex& index, int role) const
{
    if(!notebook()) {
        return QVariant();
    }
    
    if(!index.isValid()) {
        return QVariant();
    }
    
    if((index.row() < 0) || (index.row() >= notebook()->notes().count())) {
        return QVariant();
    }
    
    if(role == Qt::DisplayRole) {
        return notebook()->notes().at(index.row())->name();
    }
    
    if(role == Qt::DecorationRole) {
        return KIcon("text-plain");
    }
    
    return QVariant();
}

void NoteModel::invalidateData()
{
    reset();
}
