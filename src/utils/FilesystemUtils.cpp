/*
 * FilesystemUtils.cpp
 *
 *  Created on: Oct 14, 2013
 *      Author: mvaldenegro
 */

#include "FilesystemUtils.h"

#include <QDir>
#include <QFile>

bool FilesystemUtils::removeFolder(const QString& path)
{
    bool result = true;
    QDir dir(path);

    if (dir.exists(path)) {
        for(QFileInfo info: dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {

            if (info.isDir()) {
                result = removeFolder(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(path);
    }

    return result;
}
