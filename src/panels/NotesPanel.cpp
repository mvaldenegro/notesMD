/* 
 * File:   NotesPanel.cpp
 * Author: mvaldenegro
 * 
 * Created on July 26, 2013, 12:56 AM
 */

#include "NotesPanel.h"
#include "filesystem/NoteModel.h"

#include <QListView>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QToolBar>

#include <KIcon>
#include <KLineEdit>

NotesPanel::NotesPanel(QWidget *parent)
 : QDockWidget("Notes", parent)
{
    setFeatures(NoDockWidgetFeatures);
    
    mNotesModel = new NoteModel(this);
    
    mNotesView = new QListView(this);
    mNotesView->setModel(mNotesModel);
    mNotesView->setIconSize(QSize(32, 32));

    mSearchLineEdit = new KLineEdit(this);
    mSearchLineEdit->setPlaceholderText("Search your notes here...");
    mSearchLineEdit->setClearButtonShown(true);
    
    QWidget *central = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(central);
    
    layout->addWidget(mSearchLineEdit);
    layout->addWidget(mNotesView);
    layout->setContentsMargins(0, 0, 0, 0);
    
    setWidget(central);
    
    connect(mNotesView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(activated(const QModelIndex&)));
}
NotesPanel::~NotesPanel()
{
}

void NotesPanel::display(Notebook::Ptr notebook)
{
    if(notebook != nullptr) {
    
        mNotesModel->setNotebook(notebook);
        setWindowTitle("Notes in Notebook " + notebook->name());
    } else {

        mNotesModel->setNotebook(nullptr);
        setWindowTitle("Notes");
    }
}

void NotesPanel::activated(const QModelIndex& index)
{
    if(!mNotesModel->notebook()) {
        return;
    }
    
    if(!index.isValid()) {
        return;
    }
    
    Note::List notes = mNotesModel->notebook()->notes();
    
    if((index.row() < 0) || (index.row() >= notes.count())) {
        return;
    }
    
    Note::Ptr note = notes.at(index.row());
    
    qDebug() << "Selected note" << note->name();
    
    emit selected(note);
}
