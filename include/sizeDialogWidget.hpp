#include "mainWindow.hpp"
#include <qdialog.h>
#include <qlabel.h>

class sizeDialogWidget : public QDialog
{
    Q_OBJECT
public:
    sizeDialogWidget( MainWindow *parent=0, const char *name=0 );
private slots:
    void updateSize(int value);
private:
    QLabel *displayString;
};