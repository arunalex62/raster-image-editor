#include "statusBar.hpp"
#include <qstatusbar.h>
#include <qstring.h>
#include <qlabel.h>
#include <iostream>
void StatusBar::setStatusBar(MainWindow *mainWindow)
{
    if(mainWindow->imageView->buffer.width() > 0 && mainWindow->imageView->buffer.height() > 0) {
        QString dim = "                   " + std::to_string(mainWindow->imageView->buffer.width()) +
         " x " + std::to_string(mainWindow->imageView->buffer.height());
         mainWindow->dimensions->setText(dim);
    } else {
        mainWindow->dimensions->setText("Image width and height not found");
    }
    if(mainWindow->imageView->mouseX >= 0 && mainWindow->imageView->mouseX <= mainWindow->imageView->buffer.width()-1
        && mainWindow->imageView->mouseY >= 0 && mainWindow->imageView->mouseY <= mainWindow->imageView->buffer.height()-1) {
        QString coords = "X: " + std::to_string(mainWindow->imageView->mouseX) +
         " | Y:" + std::to_string(mainWindow->imageView->mouseY);
         mainWindow->mouseInfo->setText(coords);
    } else {
        mainWindow->mouseInfo->setText("X: | Y: ");
    }
}