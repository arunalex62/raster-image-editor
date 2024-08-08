#include "menuBar.hpp"

// Creating/displaying menu bar items with their click functions linked.
void MenuBar::setupMenuBar(QMainWindow *mainWindow)
{
    QMenuBar *menuBar = mainWindow->menuBar();
    QPopupMenu *fileMenu = new QPopupMenu( mainWindow );
    menuBar->insertItem("File", fileMenu);
    fileMenu->insertItem( "Open", mainWindow, SLOT(fileOpen()));
    fileMenu->insertItem( "Export", mainWindow, SLOT(fileExport()));

    QPopupMenu *editMenu = new QPopupMenu( mainWindow );
    menuBar->insertItem("Edit", editMenu);
    editMenu->insertItem( "Resize Canvas", mainWindow, SLOT(open()));

    QPopupMenu *viewMenu = new QPopupMenu( mainWindow );
    menuBar->insertItem("View", viewMenu);
    viewMenu->insertItem( "Grid-Lines Toggle", mainWindow, SLOT(open()));

    QPopupMenu *helpMenu = new QPopupMenu( mainWindow );
    menuBar->insertSeparator();
    menuBar->insertItem("Help", helpMenu);
    helpMenu->insertItem( "About", mainWindow, SLOT(open()));
}