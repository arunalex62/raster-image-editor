#ifndef FILEIO_HPP
#define FILEIO_HPP

#include "mainWindow.hpp"
#include <qstring.h>

// Simple helper class with two methods, one for
// opening files and the other for exporting files into
// a supported format.
class FileIO {
public:
    static QString open(MainWindow *mainWindow);
    static QString saveAs(MainWindow *mainWindow);
};


#endif