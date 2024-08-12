#include "mainWindow.hpp"
#include "menuBar.hpp"
#include "statusBar.hpp"
#include "fileIO.hpp"
#include "brushSizeDialogWidget.hpp"
#include "resizeCanvasDialogWidget.hpp"
#include "newImageDialogWidget.hpp"
#include <qwidget.h>
#include <imageView.hpp>
#include <qmessagebox.h>
#include <qcolordialog.h>
#include <qcursor.h>
#include <qapplication.h>

MainWindow::MainWindow( QWidget *parent, const char *name )
        : QMainWindow( parent, name ), fileName{""}
{
    // Initializes the menu bar, status bar, and central image
    // widget of the application with their information.
    imageView = new ImageView (this);
    StatusBar::setupStatusBar(this);
    MenuBar::setupMenuBar(this);
    setCentralWidget(imageView);
}

void MainWindow::open() {
    QMessageBox::about(this, "Test", "This is a test app with a menu bar.");
}

void MainWindow::fileNew() {
    // Displays a dialog to the user to prompt
    // them for the new width/height.
    // Then updates the status bar dimensions
    // display and the current file name.
    newImageDialogWidget newDialog(this);
    StatusBar::setStatusBarDimensions(this);
    StatusBar::setStatusBarFileName(this);
}

void MainWindow::fileOpen() {
    // Opens a file selector in the current directory.
    QString result = FileIO::open(this);
    // If a file was selected, then set the current 
    // file name to the opened file name.
    if(result != "") {
        fileName = result;
        StatusBar::setStatusBarFileName(this);
    }   
}

void MainWindow::fileExport() {
    // Exports the current file by opening
    // a file dialog for the user to enter a file name.
    QString result = FileIO::saveAs(this);
    // If a file was exported, set the current
    // file name of the program to the file name
    // of the exported file.
    if(result != "") {
        fileName = result;
        StatusBar::setStatusBarFileName(this); 
    }    
}

void MainWindow::editResizeCanvas() {
    // Displays a dialog to the user to enter in a scale factor
    // to resize the image by.
    resizeCanvasDialogWidget *w = new resizeCanvasDialogWidget(this);
    w->move(0, 0);
}

void MainWindow::viewGridlinesToggle() {
    // Toggles the enableGridlines setting on the 
    // imageView object.
    imageView->gridlinesToggle();
}

void MainWindow::viewResetCamera() {
    // Resets the camera position back to
    // the center.
    imageView->resetCamera();
}

void MainWindow::colorDialog() {
    // Uses Qt's built in QColorDialog and gets the colour, and then
    // sets the current pen colour to that colour.
    // Then updates the status bar with the selected colour.
    const QColor color = QColorDialog::getColor(imageView->penColor(), this, "Color Dialog");
    imageView->setPenColor(color);
    StatusBar::setStatusBarBrushColour(this);
}

void MainWindow::brushSizeDialog() {
    // Uses custom dialog with slider to select brush size.
    brushSizeDialogWidget brushDialog(this);
    brushDialog.resize(140, 75);
    brushDialog.exec();
    // Sets the status bar to display the newly set brush size.
    StatusBar::setStatusBarBrushSize(this);
}

void MainWindow::toolsBrush() {
    // Sets the pen colour to the stored
    // pen colour previously.
    
    // Disable other tools before using brush.
    imageView->enableFill = false;
    imageView->enableColourPicker = false;
    QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
    imageView->setPenColor(imageView->brushColour);
    // Then updates the status bar with the selected colour. 
    StatusBar::setStatusBarBrushColour(this);
}

void MainWindow::toolsEraser() {
    // Sets the pen colour to the background
    // colour of the application because transparency
    // is not functional in Qt3.

    // Disable other tools before using eraser.
    imageView->enableFill = false;
    imageView->enableColourPicker = false;
    QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
    imageView->setPenColor(paletteBackgroundColor());
    // Then updates the status bar with the selected colour. 
    StatusBar::setStatusBarBrushColour(this);
}

void MainWindow::toolsFill() {
    // Sets the imageView object in fill mode.
    // Disable other tools before using fill.
    imageView->enableColourPicker = false;
    imageView->setFillMode();
}

void MainWindow::toolsColourPicker() {
     // Sets the imageView object in colour pick mode.
     // Disable other tools before using colour picker.
     imageView->enableFill = false;
    imageView->setColourPicker();
}