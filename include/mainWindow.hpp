#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <qmainwindow.h>
#include <qstring.h>
#include "imageView.hpp"
#include <qlabel.h>

// Class that holds all the functionality of the application.
class MainWindow : public QMainWindow
{
    // Allows for a tight integration with signal/slot mechanism
    // between different parts of the application.
    Q_OBJECT
public:
    // Default constructor.
    MainWindow( QWidget *parent=0, const char *name=0 );
    // Stores the current file name to display in the status bar.
    QString fileName;
    // The class relating to the image viewing/modify operations.
    ImageView *imageView;
    // Sub-labels for each status bar item.
    QLabel *mouseInfo;
    QLabel *dimensions;
    QLabel *brushColor;
    QLabel *brushSize;
    QLabel *fileNameDisplay;

// These slots are for the menu bar button functionalities.
private slots:
    void open();
    void fileNew();
    void fileOpen();
    void fileExport();
    void editResizeCanvas();
    void viewGridlinesToggle();
    void viewResetCamera();
    void colorDialog();
    void brushSizeDialog();
    void toolsBrush();
    void toolsEraser();
    void toolsFill();
    void toolsColourPicker();
};


#endif