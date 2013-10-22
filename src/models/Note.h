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

#ifndef NOTE_H_
#define NOTE_H_

#include <QString>
#include <QList>

#include <models/Attachment.h>

class Notebook;

class Note
{
    public:
        typedef Note *Ptr;
        typedef QList<Ptr> List;

        Note(Notebook *owner);
        virtual ~Note();

        Notebook *owner() const
        {
            return mOwner;
        }
        
        QString name() const
        {
            return mName;
        }
        
        void setName(const QString& name)
        {
            mName = name;
        }
        
        QString fileName() const
        {
            return mFileName;
        }
        
        void setFileName(const QString& filename)
        {
            mFileName = filename;
        }
        
        QString markdownContents() const
        {
            return mMarkdownContents;
        }
        
        void setMarkdownContents(const QString& markdown)
        {
            mMarkdownContents = markdown;
        }
        
        Attachment::List attachments() const
        {
            return mAttachments;
        }
        
        void setAttachments(const Attachment::List& attachments)
        {
            mAttachments = attachments;
        }

    private:
        Notebook *mOwner;
        
        QString mName;
        QString mFileName;
        QString mMarkdownContents;
        
        Attachment::List mAttachments;
};

#endif /* NOTE_H_ */
