#include "menuBar.hpp"
#include <qpopupmenu.h>
#include <qmenubar.h>

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
    editMenu->insertItem( "Resize Canvas", mainWindow, SLOT(editResizeCanvas()));

    QPopupMenu *viewMenu = new QPopupMenu( mainWindow );
    menuBar->insertItem("View", viewMenu);
    viewMenu->insertItem( "Grid-Lines Toggle", mainWindow, SLOT(viewGridlinesToggle()));

    QPopupMenu *colorDialog = new QPopupMenu( mainWindow );
    menuBar->insertItem("Brush", colorDialog);
    colorDialog->insertItem ( "Select Color", mainWindow, SLOT(colorDialog()));
    colorDialog->insertItem ( "Set Brush Size", mainWindow, SLOT(brushSizeDialog()));

    QPopupMenu *helpMenu = new QPopupMenu( mainWindow );
    menuBar->insertSeparator();
    menuBar->insertItem("Help", helpMenu);
    helpMenu->insertItem( "About", mainWindow, SLOT(open()));
}