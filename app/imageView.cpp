#include "imageView.hpp"
// Used the QT3 Docs Scribble example to aid in 
// the implementation of drawing functionality:
// https://doc.qt.io/archives/3.3/scribble-example.html

#include <qevent.h>
#include <qpainter.h>
#include <qrect.h>
#include <qpoint.h>
#include <iostream>
#include <statusBar.hpp>
#include "mainWindow.hpp"

ImageView::ImageView( QWidget *parent, const char *name )
    : QWidget( parent, name, WStaticContents ), buffer( 960, 540 ), 
    mouseX(-1), mouseY(-1), pen( Qt::black, 3 ), polyline(3),
     mousePressed( FALSE ) {

    // Set default image to white.
    buffer.fill(16777215);

    setMouseTracking(true);
}

void ImageView::mousePressEvent(QMouseEvent *e) {
    mousePressed = TRUE;
    int x = e->pos().x() - (width() - buffer.width()) / 2;
    int y = e->pos().y() - (height() - buffer.height()) / 2;

    // Ensure the coordinates are clamped within the buffer bounds
    x = std::max(0, std::min(x, buffer.width() - 1));
    y = std::max(0, std::min(y, buffer.height() - 1));
    polyline[2] = polyline[1] = polyline[0] = QPoint(x, y);
}

void ImageView::mouseReleaseEvent(QMouseEvent *) {
    mousePressed = FALSE;
}

void ImageView::mouseMoveEvent( QMouseEvent *e ) {
    mouseX = e->pos().x() - (width() - buffer.width()) / 2;
    mouseY = e->pos().y() - (height() - buffer.height()) / 2;
    StatusBar::setStatusBar(static_cast<MainWindow*>(parent()));
    if (mousePressed && withinBounds(e)) {

        QPainter painter;
        painter.begin(&buffer);
        painter.setPen( pen );
        polyline[2] = polyline[1];
        polyline[1] = polyline[0];
        polyline[0] = QPoint(std::max(0, std::min(mouseX, buffer.width() - 1)),
         std::max(0, std::min(mouseY, buffer.height() - 1)));
        painter.drawPolyline( polyline );
        painter.end();

        QRect r = polyline.boundingRect();
        int translatedX = r.x() + (width() - buffer.width())/2;
        int translatedY = r.y() + (height() - buffer.height())/2;
        QRect translatedRect(translatedX, translatedY, r.width(), r.height());

        update(translatedRect);
    }
}

void ImageView::resizeEvent( QResizeEvent *e )
{
    QWidget::resizeEvent(e);
    update();
}

void ImageView::paintEvent( QPaintEvent *)
{
    QPainter painter(this);
    int x = (width() - buffer.width())/2;
    int y = (height() - buffer.height())/2;

    painter.drawPixmap(x, y, buffer);
}

// Function that returns true if the click position
// was on the image itself. Returns false otherwise (the click
// was outside the image, like the application sidebars, etc).

// This calculation is needed because the image does not start at (0,0)
// because it is centered on the widget frame, so the mouse click coordinates should
// to be checked against the centered image's coordinates, not (0,0).

bool ImageView::withinBounds(const QMouseEvent *e) {
    if(e->pos().x() > (width() - buffer.width())/2 
    && e->pos().x() < width() - (width() - buffer.width())/2
    && e->pos().y() > (height() - buffer.height())/2
    && e->pos().y() < height() - (height() - buffer.height())/2) {
        return true;
    }
    return false;
}