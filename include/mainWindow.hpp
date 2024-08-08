#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <qmainwindow.h>
#include <qmessagebox.h>
#include <qstring.h>
#include <qimage.h>
#include <qlabel.h>
#include <qpixmap.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow( QWidget *parent=0, const char *name=0 );
    int imageWidth;
    int imageHeight;
    QString fileName;
    QLabel *imageDisplay;
    QImage imageStorage;

public slots:
    void open();
    void fileOpen();
    void fileExport();
};


#endif