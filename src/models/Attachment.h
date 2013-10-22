/* 
 * File:   Attachment.h
 * Author: mvaldenegro
 *
 * Created on July 23, 2013, 2:13 AM
 */

#ifndef ATTACHMENT_H
#define	ATTACHMENT_H

#include <QList>
#include <QString>
#include <QByteArray>

class Attachment
{
    public:
        typedef Attachment *Ptr;
        typedef QList<Ptr> List;
        
        Attachment();
        virtual ~Attachment();
        
    private:
        
};

#endif	/* ATTACHMENT_H */

