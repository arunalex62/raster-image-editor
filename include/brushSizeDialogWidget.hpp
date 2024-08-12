#include "mainWindow.hpp"
#include <qdialog.h>
#include <qlabel.h>

// Simple class to show a brush size slider widget
// to the user to select their brush size.
class brushSizeDialogWidget : public QDialog
{
    // Allows for a tight integration with signal/slot mechanism
    // between different parts of the application.
    Q_OBJECT
public:
    brushSizeDialogWidget( MainWindow *parent=0, const char *name=0 );
private slots:
    // Helper function to update the string that appears to the user
    // when selecting their brush size.
    void updateSize(int value);
private:
    QLabel *displayString;
};