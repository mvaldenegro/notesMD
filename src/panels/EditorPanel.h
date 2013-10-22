/* 
1 * File:   EditorPanel.h
 * Author: mvaldenegro
 *
 * Created on July 26, 2013, 12:30 AM
 */

#ifndef EDITORPANEL_H
#define	EDITORPANEL_H

#include <editor/MarkdownEditor.h>
#include <editor/MarkdownRenderer.h>
#include <models/Note.h>

#include <QDockWidget>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QSplitter>

class EditorPanel : public QDockWidget
{
    Q_OBJECT
    
    public:
        EditorPanel(QWidget *parent = nullptr);
        virtual ~EditorPanel();
        
        Note::Ptr currentNote() const
        {
            return mCurrentNote;
        }
        
    public slots:
        void setCurrentNote(Note::Ptr note);
        
    protected slots:
        void saveNote(const QString& markdown);
        
        void triggerRendering();

        void status(const QString& message)
        {
            setWindowTitle(message);
        }
        
    private:
        MarkdownEditor *mEditor;
        MarkdownRenderer *mView;

        QSplitter *mSplitter;

        Note::Ptr mCurrentNote;

};

#endif	/* EDITORPANEL_H */

