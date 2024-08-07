#include "statusBar.hpp"
#include <qstatusbar.h>
#include <string>

void StatusBar::setStatusBar(MainWindow *mainWindow)
{
    QStatusBar *statusBar = mainWindow->statusBar();
    if(mainWindow->imageWidth > 0 && mainWindow->imageHeight > 0) {
        std::string s = "Width: " + std::to_string(mainWindow->imageWidth) +
         " Height: " + std::to_string(mainWindow->imageHeight);
        statusBar->message(s); 
    } else {
        statusBar->message("Test");
    }
}