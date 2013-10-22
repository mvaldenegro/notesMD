/* 
 * File:   NotebookModel.cpp
 * Author: mvaldenegro
 * 
 * Created on July 26, 2013, 1:17 AM
 */

#include "NotebookModel.h"
#include "NotebookManager.h"

#include <models/Notebook.h>

#include <KIcon>

NotebookModel::NotebookModel(QObject *parent)
 : QAbstractListModel(parent)
{
    connect(NotebookManager::instance()->filesystem(), SIGNAL(added(Notebook::Ptr)), this, SLOT(invalidateData()));
    connect(NotebookManager::instance()->filesystem(), SIGNAL(removed(Notebook::Ptr)), this, SLOT(invalidateData()));
}

NotebookModel::~NotebookModel()
{
}

int NotebookModel::rowCount(const QModelIndex& parent) const
{
    Notebook::List notebooks = NotebookManager::instance()->filesystem()->notebooks();
    
    return notebooks.count();
}

QVariant NotebookModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }
    
    Notebook::List notebooks = NotebookManager::instance()->filesystem()->notebooks();
    
    if((index.row() < 0) || (index.row() >= notebooks.count())) {
        return QVariant();
    }
    
    if(role == Qt::DisplayRole) {
        return notebooks.at(index.row())->name();
    }
    
    if(role == Qt::DecorationRole) {
        return KIcon("folder");
    }
    
    return QVariant();
}

QModelIndex NotebookModel::index(int row, int column, const QModelIndex& parent) const
{
    Notebook::List notebooks = NotebookManager::instance()->filesystem()->notebooks();

    if((row < 0) || (row >= notebooks.count())) {
        return QModelIndex();
    }

    Notebook::Ptr ntbk = notebooks.at(row);

    return createIndex(row, 0, ntbk);
}

void NotebookModel::invalidateData()
{
    reset();
}
