/*
 * NoteRenderWidget.cpp
 *
 *  Created on: Sep 21, 2013
 *      Author: mvaldenegro
 */

#include "MarkdownRenderer.h"

#include <QVBoxLayout>
#include <QProcess>
#include <QDebug>
#include <QWebFrame>

MarkdownRenderer::MarkdownRenderer(QWidget *parent)
 : QScrollArea(parent)
{
    mWebView = new QWebView(this);
    mWebView->setRenderHint(QPainter::TextAntialiasing);
    mWebView->setRenderHint(QPainter::Antialiasing);

    mWebView->settings()->setFontFamily(QWebSettings::StandardFont, "Sans Serif");
    mWebView->settings()->setFontSize(QWebSettings::DefaultFontSize, 14);

    mWebView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    connect(mWebView->page(), SIGNAL(linkClicked(QUrl)), this, SLOT(linkClicked(QUrl)));

    setWidgetResizable(true);
    setWidget(mWebView);
}

MarkdownRenderer::~MarkdownRenderer()
{
}

QString markdownToHTML(const QString& markdown)
{
    QProcess process;
    process.start("markdown");

    process.write(markdown.toUtf8());
    process.closeWriteChannel();

    process.waitForFinished(-1);

    return QString(process.readAllStandardOutput());
}

void MarkdownRenderer::displayMarkdown(const QString& markdown)
{
    if(!markdown.isNull()) {
        mWebView->setContent(markdownToHTML(markdown).toUtf8());
    }
}

void MarkdownRenderer::linkClicked(const QUrl& url)
{
    qDebug() << "Link clicked" << url.toString();
}
