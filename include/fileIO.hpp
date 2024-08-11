#ifndef FILEIO_HPP
#define FILEIO_HPP

#include "mainWindow.hpp"
#include <qstring.h>

class FileIO {
public:
    static QString open(MainWindow *mainWindow);
    static QString saveAs(MainWindow *mainWindow);
};


#endif