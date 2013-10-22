/* 
 * File:   EditorPanel.cpp
 * Author: mvaldenegro
 * 
 * Created on July 26, 2013, 12:30 AM
 */

#include "EditorPanel.h"

#include <models/Notebook.h>
#include <editor/MarkdownEditor.h>

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QVBoxLayout>

EditorPanel::EditorPanel(QWidget *parent)
 : QDockWidget("Editor", parent), mCurrentNote(nullptr)
{
    QWidget *widget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->setContentsMargins(0, 0, 0, 0);

    mEditor = new MarkdownEditor(widget);
    mView = new MarkdownRenderer(widget);

    mSplitter = new QSplitter(Qt::Vertical, widget);
    mSplitter->setChildrenCollapsible(false);

    mSplitter->addWidget(mEditor);
    mSplitter->addWidget(mView);

    layout->addWidget(mSplitter);

    setWidget(widget);

    connect(mEditor, SIGNAL(saveContents(const QString&)), this, SLOT(saveNote(const QString&)));
    connect(mEditor, SIGNAL(textChanged()), this, SLOT(triggerRendering()));
    
    setFeatures(QDockWidget::NoDockWidgetFeatures);
}

EditorPanel::~EditorPanel()
{
}

void EditorPanel::setCurrentNote(Note::Ptr note)
{
    if(mEditor->isModified()) {
        
        if(QMessageBox::Yes == QMessageBox::question(this, "Save changes?",
            "Note has changed and has not been saved, save changes?",
            QMessageBox::Yes | QMessageBox::No)) {
            
            mEditor->save();
        }
    }
    
    mCurrentNote = note;

    if(note != nullptr) {

        mEditor->setMarkdown(note->markdownContents());
        status("Editing " + note->owner()->name() + "/" + note->name());
    } else {

        mEditor->setMarkdown(QString());

        status("Editor");
    }
}


void EditorPanel::saveNote(const QString& markdown)
{
    qDebug() << "Writing to" << currentNote()->fileName();
    
    QFile file(currentNote()->fileName());
    
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << markdown;
 
       file.close(); 
       
       currentNote()->setMarkdownContents(markdown);
    }    
}

void EditorPanel::triggerRendering()
{
    if(mCurrentNote != nullptr) {
        mView->displayMarkdown(mEditor->markdown());
    }
}
