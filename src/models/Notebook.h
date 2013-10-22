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

#ifndef NOTEBOOK_H_
#define NOTEBOOK_H_

#include <QString>
#include <QList>
#include <QIcon>
#include <QDir>

#include <models/Note.h>

class Notebook
{
    public:
        typedef Notebook *Ptr;
        typedef QList<Ptr> List;

        Notebook();
        virtual ~Notebook();

        QString name() const
        {
            return mName;
        }
        
        void setName(const QString& name)
        {
            mName = name;
        }
        
        QString storageFolder() const
        {
            return mStorageFolder;
        }
        
        void setStorageFolder(const QString &storageFolder)
        {
            mStorageFolder = storageFolder;
            
            setName(QDir(storageFolder).dirName());
        }
        
        Note::List notes() const
        {
            return mNotes;
        }
        
        void setNotes(const Note::List& notes)
        {
            mNotes = notes;
        }
        
    private:
        QString mName;
        QString mStorageFolder;
        Note::List mNotes;
};

#endif /* NOTEBOOK_H_ */
