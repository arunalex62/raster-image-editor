#ifndef MENUBAR_HPP
#define MENUBAR_HPP

#include <qmainwindow.h>

// Single class method to setup the menu bar with
// all of the buttons/linked methods.

// This is initialized when the program is initialized.
class MenuBar {
public:
    static void setupMenuBar(QMainWindow *mainWindow);
};


#endif