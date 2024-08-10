#include <qapplication.h>

#include "mainWindow.hpp"

// Main file that runs the application

int main( int argc, char **argv )
{
    QApplication a( argc, argv );
    // MainWindow contents used as main UI for application.
    MainWindow window;

    window.setGeometry( 100, 100, 1280, 720 );
    a.setMainWidget( &window );
    window.show();
    return a.exec();
}