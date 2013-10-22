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

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>

#include "editor/MarkdownEditor.h"
#include "models/Notebook.h"

class NotebookPanel;
class EditorPanel;
class NotesPanel;

class QSplitter;
class QToolButton;

class KSystemTrayIcon;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow();
        virtual ~MainWindow();

        Notebook::Ptr currentNotebook() const
        {
            return mCurrentNotebook;
        }
        
        Note::Ptr currentNote() const
        {
            return mCurrentNote;
        }
        
    public slots:
        void openNotebook();
        void createNotebook();
        void removeNotebook();
        
        void createNote();
        void removeNote();

        void resetViews();

    private slots:
        void setCurrentNotebook(Notebook::Ptr notebook);
        
        void setCurrentNote(Note::Ptr note);
        
    private:        
        void setupToolbars();
        QToolButton *createMenu();
        
        void saveConfig();
        void readConfig();

        QSplitter *mSplitter;
        
        NotebookPanel *mNotebookPanel;
        EditorPanel *mEditorPanel;
        NotesPanel *mNotesPanel;

        KSystemTrayIcon *mTrayIcon;
        
        Notebook::Ptr mCurrentNotebook;
        Note::Ptr mCurrentNote;
};

#endif /* MAINWINDOW_H_ */
