/*
 * FilesystemUtils.h
 *
 *  Created on: Oct 14, 2013
 *      Author: mvaldenegro
 */

#ifndef FILESYSTEMUTILS_H_
#define FILESYSTEMUTILS_H_

#include <QString>

class FilesystemUtils
{
    public:
        static bool removeFolder(const QString& path);
};

#endif /* FILESYSTEMUTILS_H_ */
