#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KMessageBox>
#include <KLocale>

#include <QDebug>

#include <filesystem/NotebookManager.h>

#include "MainWindow.h"

int main (int argc, char *argv[])
{
    KAboutData aboutData("NotesMD", 0, ki18n("Notes MD"), "0.0.1",
                         ki18n("Note taking application with Markdown formatting"),
                         KAboutData::License_GPL,
                         ki18n("Copyright (c) 2013 Matias Valdenegro T."),
                         ki18n(""),
                         "http://github.com/mvaldenegro/notesMD",
                         "matias.valdenegro@gmail.com");
    
    aboutData.setProgramIconName("documentation");
 
    KCmdLineArgs::init(argc, argv, &aboutData);
    KApplication app;
    NotebookManager *manager = new NotebookManager();
    
    MainWindow *window = new MainWindow();
    window->show();

    int ret = app.exec();

    delete manager;
    delete window;
    return ret;
}
