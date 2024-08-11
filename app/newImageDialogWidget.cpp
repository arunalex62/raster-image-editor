#include "newImageDialogWidget.hpp"
#include "mainWindow.hpp"
#include <qinputdialog.h>

newImageDialogWidget::newImageDialogWidget( MainWindow *parent, const char *name )
        : QDialog( parent, name )
{
    // Show two QInputDialogs to the user, one for selecting width, and
    // the other for height, allowing integer numbers between 1 and 2000.
    // The default value is 500 pixels.
    bool widthValid;
    int width = QInputDialog::getDouble(
            "Raster Editor", "Enter a width between 1 and 2000 pixels.", 
            500, 1, 2000, 0, &widthValid, this );
    if (widthValid) {
        bool heightValid;
        int height = QInputDialog::getDouble(
                "Raster Editor", "Enter a height between 1 and 2000 pixels.", 
                500, 1, 2000, 0, &heightValid, this );
        if(heightValid) {
            parent->imageView->createNewImage(width, height);
            parent->fileName = "";
        } else {
            return;
        }
    }
}