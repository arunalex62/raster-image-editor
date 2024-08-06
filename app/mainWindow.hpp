#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <qmainwindow.h>
#include <qpopmenu.h>
#include <qmessagebox.h>
#include <qmenubar.h>
#include <qstring.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow( QWidget *parent=0, const char *name=0 );

public slots:
    void open();
};


#endif