/*
 * NoteRenderWidget.h
 *
 *  Created on: Sep 21, 2013
 *      Author: mvaldenegro
 */

#ifndef NOTERENDERWIDGET_H_
#define NOTERENDERWIDGET_H_

#include <QWidget>
#include <QWebView>
#include <QScrollArea>
#include <models/Note.h>

class MarkdownRenderer : public QScrollArea
{
    Q_OBJECT

    public:
        MarkdownRenderer(QWidget *parent = nullptr);
        virtual ~MarkdownRenderer();

    public Q_SLOTS:
        void displayMarkdown(const QString& markdown);

    protected slots:
        void linkClicked(const QUrl& url);

    private:
        QString mCachedHTML;

        QWebView *mWebView;
};

#endif /* NOTERENDERWIDGET_H_ */
