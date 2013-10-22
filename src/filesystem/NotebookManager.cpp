#include "NotebookManager.h"

#include <cassert>

#include <QDir>
#include <QFileInfo>
#include <QDebug>

#include <KConfig>
#include <KConfigGroup>
#include <KGlobal>
#include <KSharedConfig>

NotebookManager *NotebookManager::mInstance = nullptr;

NotebookManager::NotebookManager()
{
    assert(mInstance == nullptr);
    
    mInstance = this;
    mFSInterface = new FilesystemInterface();
}

NotebookManager::~NotebookManager()
{
    writeConfig();
    
    delete mFSInterface;
}

void NotebookManager::readConfig()
{
}

void NotebookManager::writeConfig()
{
    mFSInterface->saveConfig();
}
