#include "menuBar.hpp"
#include <qpopupmenu.h>
#include <qmenubar.h>

// Creating/displaying menu bar items with their click functions linked.
void MenuBar::setupMenuBar(QMainWindow *mainWindow)
{
    QMenuBar *menuBar = mainWindow->menuBar();
    QPopupMenu *fileMenu = new QPopupMenu( mainWindow );
    menuBar->insertItem("File", fileMenu);
    fileMenu->insertItem( "New", mainWindow, SLOT(fileNew()));
    fileMenu->insertItem( "Open", mainWindow, SLOT(fileOpen()));
    fileMenu->insertItem( "Export", mainWindow, SLOT(fileExport()));

    QPopupMenu *editMenu = new QPopupMenu( mainWindow );
    menuBar->insertItem("Edit", editMenu);
    editMenu->insertItem( "Resize Canvas", mainWindow, SLOT(editResizeCanvas()));

    QPopupMenu *viewMenu = new QPopupMenu( mainWindow );
    menuBar->insertItem("View", viewMenu);
    viewMenu->insertItem( "Grid-Lines Toggle", mainWindow, SLOT(viewGridlinesToggle()));

    QPopupMenu *brushMenu = new QPopupMenu( mainWindow );
    menuBar->insertItem("Brush", brushMenu);
    brushMenu->insertItem ( "Select Color", mainWindow, SLOT(colorDialog()));
    brushMenu->insertItem ( "Set Brush Size", mainWindow, SLOT(brushSizeDialog()));

    QPopupMenu *toolsMenu = new QPopupMenu( mainWindow );
    menuBar->insertItem("Tools", toolsMenu);
    toolsMenu->insertItem ( "Eraser", mainWindow, SLOT(toolsEraser()));
    toolsMenu->insertItem ( "Fill", mainWindow, SLOT(toolsFill()));
    toolsMenu->insertItem ( "Colour Picker", mainWindow, SLOT(toolsColourPicker()));

    QPopupMenu *helpMenu = new QPopupMenu( mainWindow );
    menuBar->insertSeparator();
    menuBar->insertItem("Help", helpMenu);
    helpMenu->insertItem( "About", mainWindow, SLOT(open()));
}