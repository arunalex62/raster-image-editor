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

MainWindow::MainWindow( QWidget *parent, const char *name )
        : QMainWindow( parent, name ), fileName{""}
{
    imageView = new ImageView (this);
    StatusBar::setupStatusBar(this);
    MenuBar::setupMenuBar(this);
    setCentralWidget(imageView);
}

void MainWindow::open() {
    QMessageBox::about(this, "Test", "This is a test app with a menu bar.");
}

void MainWindow::fileNew() {
    newImageDialogWidget newDialog(this);
    StatusBar::setStatusBarDimensions(this);
    StatusBar::setStatusBarFileName(this);
}

void MainWindow::fileOpen() {
    QString result = FileIO::open(this);
    if(result != "") {
        fileName = result;
        StatusBar::setStatusBarFileName(this);
    }   
}

void MainWindow::fileExport() {
    QString result = FileIO::saveAs(this);
    if(result != "") {
        fileName = result;
        StatusBar::setStatusBarFileName(this); 
    }    
}

void MainWindow::editResizeCanvas() {
    resizeCanvasDialogWidget *w = new resizeCanvasDialogWidget(this);
    w->move(0, 0);
}

void MainWindow::viewGridlinesToggle() {
    imageView->gridlinesToggle();
}

void MainWindow::colorDialog() {
    const QColor color = QColorDialog::getColor(imageView->penColor(), this, "Color Dialog");
    imageView->setPenColor(color);
    StatusBar::setStatusBarBrushColour(this);
}

void MainWindow::brushSizeDialog() {
    brushSizeDialogWidget brushDialog(this);
    brushDialog.resize(140, 75);
    brushDialog.exec();
    StatusBar::setStatusBarBrushSize(this);
}

void MainWindow::toolsEraser() {
    imageView->setPenColor(paletteBackgroundColor());
    StatusBar::setStatusBarBrushColour(this);
}

void MainWindow::toolsFill() {
    imageView->setFillMode();
}

void MainWindow::toolsColourPicker() {
    imageView->setColourPicker();
}