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

#include "MarkdownEditor.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFontDatabase>

#include <KIcon>
#include <QTextObject>

MarkdownEditor::MarkdownEditor(QWidget *parent)
 : QWidget(parent)
{
    mToolbar = new QToolBar(this);
    mEditor = new KTextEdit(this);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(mToolbar);
    mainLayout->addWidget(mEditor);

    //QMargins margins = mainLayout->contentsMargins();
    //margins.setLeft(0);
    //mainLayout->setContentsMargins(margins);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    
    setupToolbar();

    connect(mEditor, SIGNAL(textChanged()), this, SIGNAL(textChanged()));
}

MarkdownEditor::~MarkdownEditor()
{
}

void MarkdownEditor::setupToolbar()
{
    mToolbar->addAction(KIcon("document-save"), "Save", this, SLOT(save()));
    
    mToolbar->addAction(KIcon("format-text-bold"), "Bold", this, SLOT(boldFont()));
    mToolbar->addAction(KIcon("format-text-italic"), "Italic", this, SLOT(italicFont()));
    mToolbar->addAction(KIcon("format-text-underline"), "Underline", this, SLOT(underlineFont()));

    mToolbar->addSeparator();

    mToolbar->addAction(KIcon("format-list-unordered"), "Insert bulleted list",
                        this, SLOT(insertBulletList()));
    mToolbar->addAction(KIcon("format-list-ordered"), "Insert numbered list",
                       this, SLOT(insertNumberedList()));
    
    mToolbar->addSeparator();

    mToolbar->addAction(KIcon("insert-link"), "Insert link", this, SLOT(insertLink()));

    mToolbar->addSeparator();

    mToolbar->addAction("H1", this, SLOT(insertH1()));
    mToolbar->addAction("H2", this, SLOT(insertH2()));
    mToolbar->addAction("H3", this, SLOT(insertH3()));
    mToolbar->addAction("H4", this, SLOT(insertH4()));
    mToolbar->addAction("H5", this, SLOT(insertH5()));
    mToolbar->addAction("H6", this, SLOT(insertH6()));
}

void MarkdownEditor::insertBulletList()
{
    insertText("* ");
}

void MarkdownEditor::insertNumberedList()
{
    insertText("1.-");
}

void MarkdownEditor::save()
{
    emit saveContents(mEditor->toPlainText());
    
    mEditor->document()->setModified(false);
}

void MarkdownEditor::boldFont()
{
    appendToSelection("**");
}

void MarkdownEditor::italicFont()
{
    appendToSelection("*");
}

void MarkdownEditor::underlineFont()
{
    
}

void MarkdownEditor::insertHeading(const QString& headingName)
{
    if(headingName == "H1") {
        appendToSelection("#");
    }

    if(headingName == "H2") {
        appendToSelection("##");
    }

    if(headingName == "H3") {
        appendToSelection("###");
    }

    if(headingName == "H4") {
        appendToSelection("####");
    }

    if(headingName == "H5") {
        appendToSelection("#####");
    }

    if(headingName == "H6") {
        appendToSelection("######");
    }
}

void MarkdownEditor::insertText(const QString& text)
{
    mEditor->insertPlainText(text);
    mEditor->setFocus();
}

void MarkdownEditor::appendToSelection(const QString& str)
{
    if(mEditor->textCursor().hasSelection()) {

        QString text = mEditor->textCursor().block().text();
        mEditor->textCursor().insertText(str + " " + text + " " + str);

    } else {

        QTextCursor cursor = mEditor->textCursor();

        cursor.insertText(str + "  " + str);
        cursor.movePosition(QTextCursor::PreviousCharacter,
                QTextCursor::MoveAnchor, str.length() + 1);

        mEditor->setTextCursor(cursor);
        mEditor->setFocus();
    }
}
