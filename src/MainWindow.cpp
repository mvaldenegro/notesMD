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

#include "MainWindow.h"
#include "panels/NotebookPanel.h"
#include "panels/EditorPanel.h"
#include "panels/NotesPanel.h"

#include "models/Note.h"
#include "models/Notebook.h"

#include "ui/CreateNotebookDialog.h"
#include "filesystem/NotebookManager.h"

#include <QLabel>
#include <QSplitter>
#include <QVBoxLayout>
#include <QMenu>
#include <QToolButton>
#include <QInputDialog>
#include <QDebug>

#include <KIcon>
#include <KLineEdit>
#include <KSystemTrayIcon>
#include <KConfig>
#include <KConfigGroup>
#include <KGlobal>
#include <KSharedConfig>


MainWindow::MainWindow()
{
    setWindowTitle("Notes MD");

    mNotebookPanel = new NotebookPanel();
    mEditorPanel = new EditorPanel();    
    mNotesPanel = new NotesPanel();
    
    //setDockNestingEnabled(false);
    
    //addDockWidget(Qt::LeftDockWidgetArea, mNotebookPanel);
    //addDockWidget(Qt::LeftDockWidgetArea, mNotesPanel);
        
    //splitDockWidget(mNotebookPanel, mNotesPanel, Qt::Horizontal);
    
    
    QWidget *central = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(central);        
    mSplitter = new QSplitter(central);
    
    layout->addWidget(mSplitter);
    layout->setContentsMargins(0, 0, 0, 0);
    
    mSplitter->addWidget(mNotebookPanel);
    mSplitter->addWidget(mNotesPanel);
    mSplitter->addWidget(mEditorPanel);
    
    mSplitter->setChildrenCollapsible(false);

    mSplitter->setStretchFactor(0, 2);
    mSplitter->setStretchFactor(1, 2);
    mSplitter->setStretchFactor(2, 3);
    
    setCentralWidget(central);
    
    connect(mNotebookPanel, SIGNAL(selected(Notebook::Ptr)), mNotesPanel, SLOT(display(Notebook::Ptr)));
    connect(mNotesPanel, SIGNAL(selected(Note::Ptr)), mEditorPanel, SLOT(setCurrentNote(Note::Ptr)));
    
    connect(mNotebookPanel, SIGNAL(selected(Notebook::Ptr)), this, SLOT(setCurrentNotebook(Notebook::Ptr)));
    connect(mNotesPanel, SIGNAL(selected(Note::Ptr)), this, SLOT(setCurrentNote(Note::Ptr)));
    
    setupToolbars();

    connect(NotebookManager::instance()->filesystem(), SIGNAL(removed(Notebook::Ptr)), this, SLOT(resetViews()));

    mTrayIcon = new KSystemTrayIcon("documentation", this);
    mTrayIcon->setVisible(true);

    readConfig();

    showMaximized();
}

MainWindow::~MainWindow()
{
    saveConfig();
}

void MainWindow::setupToolbars()
{
    QToolBar *toolbar = addToolBar("Main");
    toolbar->setMovable(false);

    toolbar->addAction(KIcon("archive-insert-directory"), "Create new notebook", this, SLOT(createNotebook()));
    toolbar->addAction(KIcon("archive-insert"), "Create new note in the current notebook", this, SLOT(createNote()));
    toolbar->addAction(KIcon("insert-link"), "Insert archive as note");

    toolbar->addSeparator();

    toolbar->addAction(KIcon("edit-delete"), "Delete current note", this, SLOT(removeNote()));

    toolbar->addSeparator();
    toolbar->addWidget(createMenu());    
}

QToolButton *MainWindow::createMenu()
{
    QToolButton *ret = new QToolButton();
    QMenu *menu = new QMenu();
    
    menu->addAction("Open notebook", this, SLOT(openNotebook()));
    
    ret->setMenu(menu);
    ret->setPopupMode(QToolButton::InstantPopup);
    ret->setIcon(KIcon("applications-system"));
    return ret;
}

void MainWindow::openNotebook()
{
    
}

void MainWindow::createNotebook()
{
    QString folder = CreateNotebookDialog::getNotebookFolder();
           
    if(!(folder.isNull() || folder.isEmpty())) {
        
        qDebug() << "Creating notebook at" << folder;
        
        Notebook::Ptr notebook = new Notebook();
        notebook->setStorageFolder(folder);
        
        qDebug() << "Notebook created?" << NotebookManager::instance()->filesystem()->save(notebook);
        
        mNotesPanel->display(notebook);
    }
}

void MainWindow::removeNotebook()
{
    if(currentNotebook() != nullptr) {
        NotebookManager::instance()->filesystem()->remove(currentNotebook());

        setCurrentNotebook(nullptr);
    }
}

void MainWindow::createNote()
{
    QString noteName = QInputDialog::getText(nullptr, "Create a new note", "Note name");
    
    if(!noteName.isNull()) {
        Note::Ptr note = new Note(currentNotebook());
        note->setName(noteName);
        
        NotebookManager::instance()->filesystem()->save(note);
        setCurrentNote(note);
    }
}

void MainWindow::removeNote()
{
    if(currentNote() != nullptr) {

        Note::Ptr note = currentNote();
        setCurrentNote(nullptr);

        Note::List notes = currentNotebook()->notes();
        notes.removeAll(note);
        currentNotebook()->setNotes(notes);

        NotebookManager::instance()->filesystem()->remove(note);
    }
}
void MainWindow::setCurrentNote(Note::Ptr note)
{
    mCurrentNote = note;
    mEditorPanel->setCurrentNote(note);
}
void MainWindow::setCurrentNotebook(Notebook::Ptr notebook)
{
    mCurrentNotebook = notebook;
    mNotesPanel->display(notebook);
}

void MainWindow::resetViews()
{
    setCurrentNote(nullptr);
    setCurrentNotebook(nullptr);
}

void MainWindow::saveConfig()
{
    KSharedConfigPtr config = KGlobal::config();

    config->group("mainWindow").writeEntry("splitterState", mSplitter->saveState());
}

void MainWindow::readConfig()
{
    KSharedConfigPtr config = KGlobal::config();
    QByteArray splitterState;

    splitterState = config->group("mainWindow").readEntry("splitterState", QByteArray());
    mSplitter->restoreState(splitterState);
}
