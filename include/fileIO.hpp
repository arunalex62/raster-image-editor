#ifndef FILEIO_HPP
#define FILEIO_HPP

#include "mainWindow.hpp"
#include "statusBar.hpp"
#include <qfiledialog.h>
#include <qdir.h>
#include <qfileinfo.h>
#include <qmessagebox.h>

class FileIO {
public:
    static QString open(MainWindow *mainWindow);
    static void saveAs(MainWindow *mainWindow);
};


#endif