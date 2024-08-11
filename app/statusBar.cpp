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
    mainWindow->brushColor = new QLabel("Selected Brush Colour", mainWindow);
    mainWindow->brushSize = new QLabel("Selected Brush Size", mainWindow);
    mainWindow->statusBar()->addWidget(mainWindow->mouseInfo);
    mainWindow->statusBar()->addWidget(mainWindow->dimensions);
    mainWindow->statusBar()->addWidget(mainWindow->brushColor);
    mainWindow->statusBar()->addWidget(mainWindow->brushSize);

    // Set statusBar and sub-labels to dark grey colour.
    mainWindow->mouseInfo->setBackgroundColor(9737364);
    mainWindow->dimensions->setBackgroundColor(9737364);
    mainWindow->brushColor->setBackgroundColor(9737364);
    mainWindow->brushSize->setBackgroundColor(9737364);
    mainWindow->statusBar()->setBackgroundColor(9737364);

    // Set the data within the status bar.
    setStatusBarDimensions(mainWindow);
    setStatusBarMouse(mainWindow);
    setStatusBarBrushColour(mainWindow);
    setStatusBarBrushSize(mainWindow);
}


void StatusBar::setStatusBarDimensions(MainWindow *mainWindow)
{
    // If the image width/height are valid, display their contents
    // in the status bar in the format: width x height.
    if(mainWindow->imageView->buffer.width() > 0 && mainWindow->imageView->buffer.height() > 0) {
        QString dim = "   " + std::to_string(mainWindow->imageView->buffer.width()) +
         " x " + std::to_string(mainWindow->imageView->buffer.height()) + "  ";
         mainWindow->dimensions->setText(dim);
    } else {
        // Case where the image does not have a valid width/height.
        mainWindow->dimensions->setText("Image width and height not found");
    }
}

void StatusBar::setStatusBarMouse(MainWindow *mainWindow)
{
    // If the mouse position is over top of the image, display the 
    // current mouse position coordinates in the format:
    // "X: {x_position} | Y: {y_position}", in the status bar. 
    //
    // Otherwise, the status bar displays "X: | Y: ".
    if(mainWindow->imageView->mouseX >= 0 && mainWindow->imageView->mouseX <= mainWindow->imageView->buffer.width()-1
        && mainWindow->imageView->mouseY >= 0 && mainWindow->imageView->mouseY <= mainWindow->imageView->buffer.height()-1) {
        QString coords = "X: " + std::to_string(mainWindow->imageView->mouseX) +
         " | Y:" + std::to_string(mainWindow->imageView->mouseY) + "  ";
         mainWindow->mouseInfo->setText(coords);
    } else {
        mainWindow->mouseInfo->setText("X: | Y: ");
    }
}

void StatusBar::setStatusBarBrushColour(MainWindow *mainWindow)
{
    // Displays the status bar's brush colour information as the hex value 
    // of the currently selected pen colour.
    QString colourString = "  Brush Colour: " + mainWindow->imageView->penColor().name() + "  ";
    mainWindow->brushColor->setText(colourString);
}

void StatusBar::setStatusBarBrushSize(MainWindow *mainWindow)
{
    // Sets the status bar's brush size to the size
    // of the currently selected pen.
    QString widthString = "  Brush Size: " + 
    std::to_string(mainWindow->imageView->penWidth()) + "  ";
    mainWindow->brushSize->setText(widthString);
}