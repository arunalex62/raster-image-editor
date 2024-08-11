#include "mainWindow.hpp"
#include <qdialog.h>

// Single constructor class that creates and displays a QInputDialog
// for the user to input a scale factor for resizing the image.
class resizeCanvasDialogWidget : public QDialog

{
public:
    resizeCanvasDialogWidget( MainWindow *parent=0, const char *name=0 );
};