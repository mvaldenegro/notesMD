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

#ifndef RICHTEXTEDITOR_H_
#define RICHTEXTEDITOR_H_

#include <QWidget>
#include <QToolBar>
#include <QComboBox>

#include <KTextEdit>

class MarkdownEditor : public QWidget
{
    Q_OBJECT

    public:
        MarkdownEditor(QWidget *parent = nullptr);
        virtual ~MarkdownEditor();
        
        bool isModified() const
        {
            return mEditor->document()->isModified();
        }
        
        QString markdown() const
        {
            return mEditor->toPlainText();
        }

    signals:
        void saveContents(const QString& markdown);
        void textChanged();
    
    public slots:
        inline void setMarkdown(const QString& markdown)
        {
            mEditor->setPlainText(markdown);
        }
        
    public slots:
        void insertBulletList();
        void insertNumberedList();
        
        void save();
        
        void boldFont();
        void italicFont();
        void underlineFont();
        
    protected slots:
        void insertHeading(const QString& headingName);

    protected:
        void insertText(const QString& text);
        void appendToSelection(const QString& str);

    private:
        QToolBar *mToolbar;
        KTextEdit *mEditor;

        void setupToolbar();
};

#endif /* RICHTEXTEDITOR_H_ */
