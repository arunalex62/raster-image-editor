#include "mainWindow.hpp"

MainWindow::MainWindow( QWidget *parent, const char *name )
        : QMainWindow( parent, name )
{
    QPopupMenu *fileMenu = new QPopupMenu( this );
    menuBar()->insertItem("File", fileMenu);
    fileMenu->insertItem( "Open", this, SLOT(open()));
    fileMenu->insertItem( "Export", this, SLOT(open()));

    QPopupMenu *editMenu = new QPopupMenu( this );
    menuBar()->insertItem("Edit", editMenu);
    editMenu->insertItem( "Resize Canvas", this, SLOT(open()));

    QPopupMenu *viewMenu = new QPopupMenu( this );
    menuBar()->insertItem("View", viewMenu);
    viewMenu->insertItem( "Grid-Lines Toggle", this, SLOT(open()));

    QPopupMenu *helpMenu = new QPopupMenu( this );
    menuBar()->insertSeparator();
    menuBar()->insertItem("Help", helpMenu);
    helpMenu->insertItem( "About", this, SLOT(open()));
}

void MainWindow::open() {
    QMessageBox::about(this, "Test", "This is a test app with a menu bar.");
}