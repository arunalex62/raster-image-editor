#include "sizeDialogWidget.hpp"
#include "mainWindow.hpp"
#include <qslider.h>
#include <qlayout.h>

sizeDialogWidget::sizeDialogWidget( MainWindow *parent, const char *name )
        : QDialog( parent, name )
{
    const int brush_size = parent->imageView->penWidth();
    QVBoxLayout *layout = new QVBoxLayout(this);
    displayString = new QLabel(" Set Brush Size: " + std::to_string(brush_size), this);

    layout->addWidget(displayString);

    QSlider * slider = new QSlider( Horizontal, this, "slider" );
    slider->setRange(1, 30);
    slider->setValue (brush_size);
    layout->addWidget(slider);

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(updateSize(int)));
    connect(slider, SIGNAL(valueChanged(int)), parent->imageView, SLOT(setPenWidth(int)));
}

void sizeDialogWidget::updateSize(const int new_size) {
    displayString->setText(" Set Brush Size: " + std::to_string(new_size));
}