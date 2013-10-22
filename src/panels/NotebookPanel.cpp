/*
 * Copyright (C) 2011-2012 Matias Valdenegro <matias.valdenegro@gmail.com>
 * This file is part of KResearch.
 *
 * kesearch is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * kresearch is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with KResearch.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "NotebookPanel.h"
#include "filesystem/NotebookModel.h"
#include "filesystem/NotebookManager.h"

#include "utils/LambdaSlot.h"

#include <QListView>
#include <QDebug>
#include <QVBoxLayout>
#include <QLabel>
#include <QToolBar>
#include <QMenu>

#include <KIcon>

NotebookPanel::NotebookPanel(QWidget *parent)
 : QDockWidget("Notebooks", parent)
{
    setFeatures(NoDockWidgetFeatures);
    
    mNotebookModel = new NotebookModel(this);
    mNotebooksView = new QListView(this);
        
    mNotebooksView->setModel(mNotebookModel);
    mNotebooksView->setIconSize(QSize(32, 32));

    mNotebooksView->setFrameStyle(QFrame::NoFrame);
    mNotebooksView->viewport()->setAutoFillBackground(false);
    mNotebooksView->setContextMenuPolicy(Qt::CustomContextMenu);
    
    setWidget(mNotebooksView);
    
    connect(mNotebooksView, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint&)));
    connect(mNotebooksView, SIGNAL(clicked(const QModelIndex&)),
            this, SLOT(activated(const QModelIndex&)));
}

NotebookPanel::~NotebookPanel()
{
}

void NotebookPanel::activated(const QModelIndex& index)
{
    if(!index.isValid()) {
        return;
    }
    
    Notebook::List notebooks = NotebookManager::instance()->filesystem()->notebooks();
    
    if((index.row() < 0) || (index.row() >= notebooks.count())) {
        return;
    }
    
    Notebook::Ptr sel = notebooks.at(index.row());
    
    qDebug() << "Selected notebook" << sel->name();
    
    emit selected(sel);
}

void NotebookPanel::showContextMenu(const QPoint& pos)
{
    QMenu contextMenu("Context menu", this);
    Notebook::Ptr ntbk = notebookAt(pos);

    contextMenu.addAction(new QAction("Hello", this));

    LambdaSlot deleteNotebook([ntbk]() {
        NotebookManager::instance()->filesystem()->remove(ntbk);
    });

    if(ntbk != nullptr) {
        contextMenu.addAction(KIcon("edit-delete"), QString("Remove '%1'").arg(ntbk->name()),
                              &deleteNotebook, SLOT(call()));
    }
    contextMenu.exec(mapToGlobal(pos));
}

Notebook::Ptr NotebookPanel::notebookAt(const QPoint& pos)
{
    QModelIndex idx = mNotebooksView->indexAt(pos);

    if(idx.isValid()) {
        return static_cast<Notebook::Ptr>(idx.internalPointer());
    }

    return nullptr;
}
