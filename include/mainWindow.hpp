#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <qmainwindow.h>
#include <qstring.h>
#include "imageView.hpp"
#include <qlabel.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow( QWidget *parent=0, const char *name=0 );
    QString fileName;
    ImageView *imageView;
    QLabel *mouseInfo;
    QLabel *dimensions;
    QLabel *brushColor;
    QLabel *brushSize;
    QLabel *fileNameDisplay;

private slots:
    void open();
    void fileNew();
    void fileOpen();
    void fileExport();
    void editResizeCanvas();
    void viewGridlinesToggle();
    void colorDialog();
    void brushSizeDialog();
    void toolsEraser();
    void toolsColourPicker();
};


#endif