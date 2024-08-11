#include "mainWindow.hpp"
#include <qdialog.h>

// Single constructor class that creates and displays two QInputDialogs
// for the user to input a width and a height for creating a new image.
class newImageDialogWidget : public QDialog

{
public:
    newImageDialogWidget( MainWindow *parent=0, const char *name=0 );
};