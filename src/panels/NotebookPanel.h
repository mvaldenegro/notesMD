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

#ifndef NOTEBOOKPANEL_H_
#define NOTEBOOKPANEL_H_

#include "models/Notebook.h"

#include <QDockWidget>
#include <QModelIndex>

class QListView;
class QToolBar;
class NotebookModel;

class NotebookPanel : public QDockWidget
{
    Q_OBJECT

    public:
        NotebookPanel(QWidget *parent = nullptr);
        virtual ~NotebookPanel();
        
    signals:
        void selected(Notebook::Ptr notebook);
    
    private slots:
        void activated(const QModelIndex& index);
        void showContextMenu(const QPoint& pos);

    private:
        Notebook::Ptr notebookAt(const QPoint& pos);

        QListView *mNotebooksView;
        NotebookModel *mNotebookModel;
};

#endif /* NOTEBOOKPANEL_H_ */
