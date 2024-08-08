#ifndef MENUBAR_HPP
#define MENUBAR_HPP

#include <qmainwindow.h>
#include <qpopupmenu.h>
#include <qmenubar.h>

class MenuBar {
public:
    static void setupMenuBar(QMainWindow *mainWindow);
};


#endif