#include "mainWindow.hpp"
#include "menuBar.hpp"
#include "statusBar.hpp"
#include "fileIO.hpp"
#include "sizeDialogWidget.hpp"
#include <qwidget.h>
#include <imageView.hpp>
#include <qdockwindow.h>
#include <qtoolbar.h>
#include <qmessagebox.h>
#include <qstatusbar.h>
#include <qcolordialog.h>

MainWindow::MainWindow( QWidget *parent, const char *name )
        : QMainWindow( parent, name ), fileName{""}
{
    mouseInfo = new QLabel("Mouse Information", this);
    dimensions = new QLabel("Image Dimensions", this);
    statusBar()->addWidget(mouseInfo);
    statusBar()->addWidget(dimensions);
    mouseInfo->setBackgroundColor(9737364);
    dimensions->setBackgroundColor(9737364);
    imageView = new ImageView (this);
    StatusBar::setStatusBar(this);
    statusBar()->setBackgroundColor(9737364);
    MenuBar::setupMenuBar(this);
    setCentralWidget(imageView);
}

void MainWindow::open() {
    QMessageBox::about(this, "Test", "This is a test app with a menu bar.");
}

void MainWindow::fileOpen() {
    fileName = FileIO::open(this);    
}

void MainWindow::fileExport() {
    FileIO::saveAs(this);       
}

void MainWindow::viewGridlinesToggle() {
    imageView->gridlinesToggle();
}

void MainWindow::colorDialog() {
    const QColor color = QColorDialog::getColor(imageView->penColor(), this, "Color Dialog");
    imageView->setPenColor(color);
}

void MainWindow::sizeDialog() {
    sizeDialogWidget *w = new sizeDialogWidget(this);
    w->resize(140, 75);
    w->show();
}