#include "resizeCanvasDialogWidget.hpp"
#include "mainWindow.hpp"
#include <qinputdialog.h>
#include <qmessagebox.h>
#include "statusBar.hpp"

resizeCanvasDialogWidget::resizeCanvasDialogWidget( MainWindow *parent, const char *name )
        : QDialog( parent, name )
{
    bool valid;
    // Show a QInputDialog to the user, allowing scale factors between 0.1 and 10.0,
    // with 1 decimal place allowed. The default value (no scaling) is 1.0.
    double scaleFactor = QInputDialog::getDouble(
            "Raster Editor", "Enter a decimal scale factor between 0.1 and 10.0 to scale the image by", 
            1.0, 0.1, 10.0, 1, &valid, this );
    if ( valid ) {
        if(scaleFactor == 1) {
            return;
        }
        int newWidth = parent->imageView->buffer.width()*scaleFactor;
        int newHeight = parent->imageView->buffer.height()*scaleFactor;
        // Ensure the new width/height are not greater than
        // 2000 pixels for performance reasons.
        if (newWidth > 2000 || newWidth < 1) {
            QMessageBox::warning(parent, "Raster Editor",
             "Please ensure the new width is between 1 and 2000 pixels.");
             return;
        }
        if (newHeight > 2000 || newHeight < 1) {
            QMessageBox::warning(parent, "Raster Editor",
             "Please ensure the new height is between 1 and 2000 pixels.");
             return;
        }
        parent->imageView->resizeCanvas(scaleFactor);
        StatusBar::setStatusBarDimensions(parent);
    }
}