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

    // Method for updating the status bar with image
    // dimension information during the execution of the program.
    static void setStatusBarDimensions(MainWindow *mainWindow);

    // Method for updating the status bar with mouse position
    // information during the execution of the program.
    static void setStatusBarMouse(MainWindow *mainWindow);

    // Method for updating the status bar with the current
    // brush colour during the execution of the program.
    static void setStatusBarBrushColour(MainWindow *mainWindow);

    // Method for updating the status bar with the current
    // brush size during the execution of the program.
    static void setStatusBarBrushSize(MainWindow *mainWindow);

    // Method for updating the status bar with the current
    // name of the file in the editor.
    static void setStatusBarFileName(MainWindow *mainWindow);
};


#endif