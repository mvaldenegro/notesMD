/* 
 * File:   FilesystemInterface.cpp
 * Author: mvaldenegro
 * 
 * Created on July 30, 2013, 8:50 PM
 */

#include "FilesystemInterface.h"

#include <QFile>
#include <QDir>
#include <QDebug>
#include <QTextStream>

#include <KConfig>
#include <KConfigGroup>
#include <KGlobal>
#include <KSharedConfig>

#include "utils/FilesystemUtils.h"

FilesystemInterface::FilesystemInterface(QObject *parent)
 : QObject(parent)
{
    loadNotebooks();
}

FilesystemInterface::~FilesystemInterface()
{
}

Notebook::Ptr FilesystemInterface::notebookByName(const QString& name) const
{
    for(Notebook::Ptr notebook: notebooks()) {
        if(notebook->name() == name) {
            return notebook;
        }
    }
    
    return nullptr;
}

Notebook::List FilesystemInterface::notebooks() const
{
    return mNotebooks;
}

bool FilesystemInterface::save(Notebook::Ptr notebook)
{
    qDebug() << "Saving notebook at" << notebook->storageFolder();
    
    if(!notebookByName(notebook->name())) {
        
        QDir dir(notebook->storageFolder());
        QString name = dir.dirName();

        if(!dir.exists()) {
            dir.cdUp();
            dir.mkdir(notebook->name());
        }
        
        notebook->setName(name);
        
        mNotebooks.append(notebook);
        
        qDebug() << "Now we have" << mNotebooks.count() << " notebooks";
        
        saveConfig();
        
        emit added(notebook);
        
        return true;
    }
    
    return false;
}

bool FilesystemInterface::rename(Notebook::Ptr notebook)
{
    QDir dir(notebook->storageFolder());
    QString oldFolder = notebook->storageFolder();
    
    if(dir.dirName() != notebook->name()) {

        QString oldName = dir.dirName();
        
        dir.cdUp();
        return dir.rename(oldName, notebook->name());
    }
    
    return false;
}

bool FilesystemInterface::remove(Notebook::Ptr notebook)
{
    if(!notebook) {
        return false;
    }

    qDebug() << "Deleting notebook" << notebook->name();

    bool ok =  FilesystemUtils::removeFolder(notebook->storageFolder());

    qDebug() << "OK?" << ok;

    if(ok) {
        emit removed(notebook);

        mNotebooks.removeAll(notebook);

        qDebug() << "Notebook deleted";

        saveConfig();
    }

    return ok;
}

bool FilesystemInterface::save(Note::Ptr note)
{
    note->setFileName(note->owner()->storageFolder() + QDir::separator() + note->name() + ".md");
    
    QFile file(note->fileName());
    
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << note->markdownContents();
 
       file.close();
       
       emit added(note);
       
       return true;
    }
    
    return false;
}

bool FilesystemInterface::update(Note::Ptr note)
{
    QFile file(note->fileName());
    
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << note->markdownContents();
 
       file.close();
       
       emit modified(note);
       
       return true;
    }
    
    return false;
}

bool FilesystemInterface::remove(Note::Ptr note)
{
    QFile file(note->fileName());
    
    bool ret =  file.remove();
    
    if(ret) {
        note->setFileName(QString());
        
        emit removed(note);
        
        saveConfig();

        return true;
    }
    
    return false;
}

void FilesystemInterface::saveConfig()
{
    KSharedConfigPtr config = KGlobal::config();    
    QStringList notebookFolders;
        
    for(Notebook::Ptr notebook: notebooks()) {
        notebookFolders += notebook->storageFolder();
    }
    
    qDebug() << "Notebook list" << notebookFolders;
    
    config->group("notebooks").writeEntry("folders", notebookFolders);
    config->sync();
}

void FilesystemInterface::loadNotebooks()
{
    KSharedConfigPtr config = KGlobal::config();    
    QStringList notebookList = config->group("notebooks").readEntry("folders", QStringList());
    
    mNotebooks.clear();
    
    for(QString notebookFolder: notebookList) {
        mNotebooks += loadNotebook(notebookFolder);        
    }
}

inline QString readMarkdownFile(const QFileInfo& fileInfo)
{
    QFile file(fileInfo.absoluteFilePath());
    
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        
        return in.readAll();
    }
    
    return QString();
}

Notebook::Ptr FilesystemInterface::loadNotebook(const QString& folder)
{
    QDir folderDir(folder);
    Notebook::Ptr notebook = new Notebook();
    notebook->setName(folderDir.dirName());
    notebook->setStorageFolder(folder);
    
    Note::List notes;
    QFileInfoList notesInfoList = folderDir.entryInfoList(QStringList() << "*.md", QDir::Files);
    
    for(QFileInfo noteInfo : notesInfoList) {
        
        Note::Ptr note = new Note(notebook);
        note->setName(noteInfo.baseName());
        note->setFileName(noteInfo.absoluteFilePath());
        note->setMarkdownContents(readMarkdownFile(noteInfo));
        
        notes.append(note);
    }
    
    notebook->setNotes(notes);
    
    qDebug() << "Loaded notebook" << notebook->name() << "with" << notes.count() << " notes";
    
    return notebook;
}
