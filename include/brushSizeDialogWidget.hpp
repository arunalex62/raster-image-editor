#include "mainWindow.hpp"
#include <qdialog.h>
#include <qlabel.h>

class brushSizeDialogWidget : public QDialog
{
    Q_OBJECT
public:
    brushSizeDialogWidget( MainWindow *parent=0, const char *name=0 );
private slots:
    void updateSize(int value);
private:
    QLabel *displayString;
};