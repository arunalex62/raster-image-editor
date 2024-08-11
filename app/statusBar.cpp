#include "statusBar.hpp"
#include <qstatusbar.h>
#include <qstring.h>
#include <qlabel.h>
#include <iostream>

void StatusBar::setupStatusBar(MainWindow *mainWindow)
{
    // Initializing status bar sections for mouse information and 
    // the image dimensions, and adding them to the status bar.
    mainWindow->mouseInfo = new QLabel("Mouse Information", mainWindow);
    mainWindow->dimensions = new QLabel("Image Dimensions", mainWindow);
    mainWindow->statusBar()->addWidget(mainWindow->mouseInfo);
    mainWindow->statusBar()->addWidget(mainWindow->dimensions);

    // Set statusBar and sub-labels to dark grey colour.
    mainWindow->mouseInfo->setBackgroundColor(9737364);
    mainWindow->dimensions->setBackgroundColor(9737364);
    mainWindow->statusBar()->setBackgroundColor(9737364);

    // Set the data within the status bar.
    setStatusBar(mainWindow);
}


void StatusBar::setStatusBar(MainWindow *mainWindow)
{
    // If the image width/height are valid, display their contents
    // in the status bar in the format: width x height.
    if(mainWindow->imageView->buffer.width() > 0 && mainWindow->imageView->buffer.height() > 0) {
        QString dim = "                   " + std::to_string(mainWindow->imageView->buffer.width()) +
         " x " + std::to_string(mainWindow->imageView->buffer.height());
         mainWindow->dimensions->setText(dim);
    } else {
        // Case where the image does not have a valid width/height.
        mainWindow->dimensions->setText("Image width and height not found");
    }
    // If the mouse position is over top of the image, display the 
    // current mouse position coordinates in the format:
    // "X: {x_position} | Y: {y_position}", in the status bar. 
    //
    // Otherwise, the status bar displays "X: | Y: ".
    if(mainWindow->imageView->mouseX >= 0 && mainWindow->imageView->mouseX <= mainWindow->imageView->buffer.width()-1
        && mainWindow->imageView->mouseY >= 0 && mainWindow->imageView->mouseY <= mainWindow->imageView->buffer.height()-1) {
        QString coords = "X: " + std::to_string(mainWindow->imageView->mouseX) +
         " | Y:" + std::to_string(mainWindow->imageView->mouseY);
         mainWindow->mouseInfo->setText(coords);
    } else {
        mainWindow->mouseInfo->setText("X: | Y: ");
    }
}