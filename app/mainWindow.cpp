#include "mainWindow.hpp"
#include "menuBar.hpp"
#include "statusBar.hpp"
#include "qwidget.h"
#include "qlabel.h"
#include <qimage.h>
#include <qpixmap.h>
#include <iostream>
#include <qfiledialog.h>

MainWindow::MainWindow( QWidget *parent, const char *name )
        : QMainWindow( parent, name ), imageWidth{0}, imageHeight{0},
          fileName{""}, imageDisplay{new QLabel(this)}
{
    MenuBar::setupMenuBar(this);
    imageDisplay->setAlignment(Qt::AlignCenter);
    // if(imagePixmap.load(fileName)) {
    //     std::cout << "Works!\n";
    //     imageDisplay->setPixmap(imagePixmap);
    //     imageDisplay->show();
    //     setCentralWidget(imageDisplay);
    // }
    StatusBar::setStatusBar(this);
}

void MainWindow::open() {
    QMessageBox::about(this, "Test", "This is a test app with a menu bar.");
}

void MainWindow::fileOpen() {
    // Taken from QFileDialog Qt Class Reference Page:
    // https://doc.qt.io/archives/3.3/qfiledialog.html
    fileName = QFileDialog::getOpenFileName(
                    "/home",
                    "Images (*.png *.jpg)",
                    this,
                    "open file dialog",
                    "Choose a file" );
    // If filename is found, load the image and display it.
    if (fileName != "") {
        if(imagePixmap.load(fileName)) {
            imageDisplay->setPixmap(imagePixmap);
            imageDisplay->show();
            setCentralWidget(imageDisplay);
            imageWidth = imagePixmap.width();
            imageHeight = imagePixmap.height();
            // Update status bar with width/height of new image.
            StatusBar::setStatusBar(this);
        }
    }
       
}