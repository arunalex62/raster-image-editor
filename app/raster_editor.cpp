#include <qapplication.h>

#include "mainWindow.hpp"

int main( int argc, char **argv )
{
    QApplication a( argc, argv );
    MainWindow window;

   // MyWindow w;
    window.setGeometry( 100, 100, 500, 355 );
    a.setMainWidget( &window );
    window.show();
    return a.exec();
}