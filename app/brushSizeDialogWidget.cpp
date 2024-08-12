#include "brushSizeDialogWidget.hpp"
#include "mainWindow.hpp"
#include <qslider.h>
#include <qlayout.h>

brushSizeDialogWidget::brushSizeDialogWidget( MainWindow *parent, const char *name )
        : QDialog( parent, name )
{
    // Get the current brush size to use as the initial slider value.
    const int brush_size = parent->imageView->penWidth();
    QVBoxLayout *layout = new QVBoxLayout(this);

    // displayString is the text the user sees while using the slider.
    displayString = new QLabel(" Set Brush Size: " + std::to_string(brush_size), this);

    layout->addWidget(displayString);
    // Slider created with range [1, 30].
    // Has initial value of current brush size.
    QSlider * slider = new QSlider( Horizontal, this, "slider" );
    slider->setRange(1, 30);
    slider->setValue (brush_size);
    layout->addWidget(slider);

    // When the slider value is changed, it updates the displayString
    // in real-time to the user to show the selected size.
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(updateSize(int)));
    // The same happens when the slider value changes, setting the
    // actual brush size of the application in real-time.
    connect(slider, SIGNAL(valueChanged(int)), parent->imageView, SLOT(setPenWidth(int)));
}

void brushSizeDialogWidget::updateSize(const int new_size) {
    displayString->setText(" Set Brush Size: " + std::to_string(new_size));
}