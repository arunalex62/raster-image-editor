#ifndef STATUSBAR_HPP
#define STATUSBAR_HPP

#include "mainWindow.hpp"

// Class that implements and defines methods for
// initializing and dynamically updating the
// status bar of the main window with
// image-related information.

class StatusBar {
public:
    // Method for initializing the sub-sections of the 
    // status bar, such as the image dimensions section
    // and the mouse position section.
    static void setupStatusBar(MainWindow *mainWindow);
    // Method for updating the status bar with information
    // during the execution of the program.
    // This includes mouse position and image dimensions.
    static void setStatusBar(MainWindow *mainWindow);
};


#endif