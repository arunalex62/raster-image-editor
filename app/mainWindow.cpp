#include "mainWindow.hpp"
#include "menuBar.hpp"
#include "statusBar.hpp"
#include "fileIO.hpp"
#include <qwidget.h>
#include <qstring.h>

MainWindow::MainWindow( QWidget *parent, const char *name )
        : QMainWindow( parent, name ), imageWidth{0}, imageHeight{0},
          fileName{""}, imageDisplay{new QLabel(this)}
{
    MenuBar::setupMenuBar(this);
    imageDisplay->setAlignment(Qt::AlignCenter);
    imageStorage = QPixmap(1280, 720).convertToImage();
    imageStorage.fill(16777215);
    QPixmap pm(imageStorage);
    imageDisplay->setPixmap(pm);
    imageDisplay->show();
    setCentralWidget(imageDisplay);
    imageWidth = imageStorage.width();
    imageHeight = imageStorage.height();
    // Update status bar with width/height of new image.
    StatusBar::setStatusBar(this);
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