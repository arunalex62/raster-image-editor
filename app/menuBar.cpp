#include "menuBar.hpp"
#include <qpopupmenu.h>
#include <qmenubar.h>

// Creating/displaying menu bar items with their click functions linked.
void MenuBar::setupMenuBar(QMainWindow *mainWindow)
{
    // Initial variable initialization to link to existing
    // menu bar on the main window.
    QMenuBar *menuBar = mainWindow->menuBar();

    // Adding file dropdown with related sub-options.
    QPopupMenu *fileMenu = new QPopupMenu( mainWindow );
    menuBar->insertItem("File", fileMenu);
    fileMenu->insertItem( "New", mainWindow, SLOT(fileNew()));
    fileMenu->insertItem( "Open", mainWindow, SLOT(fileOpen()));
    fileMenu->insertItem( "Export", mainWindow, SLOT(fileExport()));

    // Adding edit dropdown with related sub-options.
    QPopupMenu *editMenu = new QPopupMenu( mainWindow );
    menuBar->insertItem("Edit", editMenu);
    editMenu->insertItem( "Resize Canvas", mainWindow, SLOT(editResizeCanvas()));

    // Adding view dropdown with related sub-options.
    QPopupMenu *viewMenu = new QPopupMenu( mainWindow );
    menuBar->insertItem("View", viewMenu);
    viewMenu->insertItem( "Grid-Lines Toggle", mainWindow, SLOT(viewGridlinesToggle()));
    viewMenu->insertItem( "Reset Camera", mainWindow, SLOT(viewResetCamera()));

    // Adding brush dropdown with related sub-options.
    QPopupMenu *brushMenu = new QPopupMenu( mainWindow );
    menuBar->insertItem("Brush", brushMenu);
    brushMenu->insertItem ( "Select Color", mainWindow, SLOT(colorDialog()));
    brushMenu->insertItem ( "Set Brush Size", mainWindow, SLOT(brushSizeDialog()));

    // Adding tools dropdown with related sub-options.
    QPopupMenu *toolsMenu = new QPopupMenu( mainWindow );
    menuBar->insertItem("Tools", toolsMenu);
    toolsMenu->insertItem ( "Brush", mainWindow, SLOT(toolsBrush()));
    toolsMenu->insertItem ( "Eraser", mainWindow, SLOT(toolsEraser()));
    toolsMenu->insertItem ( "Fill", mainWindow, SLOT(toolsFill()));
    toolsMenu->insertItem ( "Colour Picker", mainWindow, SLOT(toolsColourPicker()));

    // Adding help dropdown with related sub-options.
    QPopupMenu *helpMenu = new QPopupMenu( mainWindow );
    menuBar->insertSeparator();
    menuBar->insertItem("Help", helpMenu);
    helpMenu->insertItem( "About", mainWindow, SLOT(helpAbout()));
}