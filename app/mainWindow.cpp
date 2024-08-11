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
    imageView = new ImageView (this);
    StatusBar::setupStatusBar(this);
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