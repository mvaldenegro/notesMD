#ifndef NOTEBOOKMANAGER_H_
#define NOTEBOOKMANAGER_H_

#include <models/Notebook.h>
#include <filesystem/FilesystemInterface.h>

class NotebookManager
{
    public:
        NotebookManager();
        virtual ~NotebookManager();
        
        void readConfig();
        void writeConfig();
        
        inline FilesystemInterface *filesystem() const
        {
            return mFSInterface;
        }
        
        inline static NotebookManager *instance()
        {
            return mInstance;
        }
        
    private:
        
        FilesystemInterface *mFSInterface;
        static NotebookManager *mInstance;
};

#endif /* NOTEBOOKMANAGER_H_ */
