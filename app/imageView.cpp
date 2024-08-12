#include "imageView.hpp"
// Used the QT3 Docs Scribble example to aid in 
// the implementation of drawing functionality:
// https://doc.qt.io/archives/3.3/scribble-example.html

#include <qevent.h>
#include <qrect.h>
#include <qpoint.h>
#include <statusBar.hpp>
#include "mainWindow.hpp"
#include <qtimer.h>
#include <queue>

ImageView::ImageView( QWidget *parent, const char *name )
    : QWidget( parent, name, WStaticContents ), buffer( 960, 540 ), 
    mouseX(-1), mouseY(-1), pen( Qt::black, 3 ), polyline(3),
     mousePressed(false), enableGridLines(false), enableColourPicker(false),
     enableFill(false) {

    // Set default image to white.
    buffer.fill(16777215);

    setMouseTracking(true);
}

void ImageView::mousePressEvent(QMouseEvent *e) {
    mousePressed = true;
    int x = e->pos().x() - (width() - buffer.width())/2;
    int y = e->pos().y() - (height() - buffer.height())/2;

    if((enableColourPicker || enableFill) && withinBounds(e->pos().x(), e->pos().y())) {
        if(enableColourPicker) {
            useColourPicker(x, y);
        } else {
            useFill(x, y);
        }
        return;
    }

    // Map the coordinates within the image boundaries.
    x = std::max(0, std::min(x, buffer.width() - 1));
    y = std::max(0, std::min(y, buffer.height() - 1));
    polyline[2] = polyline[1] = polyline[0] = QPoint(x, y);
}

void ImageView::mouseReleaseEvent(QMouseEvent *) {
    mousePressed = false;
    gridDrawHelper();
}

void ImageView::mouseMoveEvent( QMouseEvent *e ) {
    mouseX = e->pos().x() - (width() - buffer.width())/2;
    mouseY = e->pos().y() - (height() - buffer.height())/2;
    StatusBar::setStatusBarMouse(static_cast<MainWindow*>(parent()));
    if(enableColourPicker || enableFill) {
        return;
    }
    if (mousePressed && withinBounds(e->pos().x(), e->pos().y())) {
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

void ImageView::resizeEvent( QResizeEvent *e ) {
    QWidget::resizeEvent(e);
    update();
    if(enableGridLines) {
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(gridDrawHelper()));
        timer->start(500, TRUE);
    }
}

void ImageView::paintEvent( QPaintEvent *) {
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

bool ImageView::withinBounds(const int x, const int y) {
    if(x >= (width() - buffer.width())/2 
    && x < width() - (width() - buffer.width())/2
    && y >= (height() - buffer.height())/2
    && y < height() - (height() - buffer.height())/2) {
        return true;
    }
    return false;
}

void ImageView::drawGridlines(QPainter &painter) { 
    painter.setPen(QPen(Qt::lightGray, 1, Qt::DotLine));

    int xStart = (width() - buffer.width()) / 2;
    int yStart = (height() - buffer.height()) / 2;

    // Drawing the vertical grid lines in increments of 20 pixels.
    for (int x = 0; x < buffer.width(); x += 20) {
        painter.drawLine(x + xStart, yStart, x + xStart, buffer.height() + yStart);
    }

    // Drawing the horizontal grid lines in increments of 20 pixels.
    for (int y = 0; y < buffer.height(); y += 20) {
        painter.drawLine(xStart, y + yStart, buffer.width() + xStart, y + yStart);
    }
}

void ImageView::gridDrawHelper() {
    if(enableGridLines) {
        QPainter painter(this);
        drawGridlines(painter);
    }
}

void ImageView::useColourPicker(const int x, const int y) {
    QImage image = buffer.convertToImage();
    QColor color(image.pixel(x, y));
    setPenColor(color);
    QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
    enableColourPicker = false;
    StatusBar::setStatusBarBrushColour(static_cast<MainWindow*>(parent()));
    return;
}

// Used the flood fill fill algorithm from this website:
// https://www.geeksforgeeks.org/flood-fill-algorithm/
void ImageView::useFill(const int x, const int y) {
    // First need to convert QPixmap buffer to 
    // QImage for pixel-level access to image.
    QImage image = buffer.convertToImage();
    QColor newColor(penColor());

    // Queue that holds pixels for flood-fill
    // algorithm.
    std::queue<std::pair<int, int> > queue;
    auto point = std::make_pair(x, y);
    queue.push(point);
    QColor oldColour = image.pixel(x, y);
    image.setPixel(x, y, newColor.rgb());

    // Checks each pixel in the queue if the adjacent pixels 
    // can be filled.
    while(queue.size() > 0) {
        auto currentPoint = queue.front();
        queue.pop();
        int x = currentPoint.first;
        int y = currentPoint.second;
        // Check adjacent pixels if they are the same colour, then fill them
        // and add that pixel to the queue.
        if(x+1< buffer.width() && image.pixel(x+1, y) == oldColour.rgb()) {
            image.setPixel(x+1, y, newColor.rgb());
            point.first = x + 1;
            point.second = y;
            queue.push(point);
        }
        if(x-1 >= 0 && image.pixel(x-1, y) == oldColour.rgb()) {
            image.setPixel(x-1, y, newColor.rgb());
            point.first = x - 1;
            point.second = y;
            queue.push(point);
        }
        if(y+1 < buffer.height() && image.pixel(x, y+1) == oldColour.rgb()) {
            image.setPixel(x, y+1, newColor.rgb());
            point.first = x;
            point.second = y + 1;
            queue.push(point);
        }
        if(y-1 >= 0 && image.pixel(x, y-1) == oldColour.rgb()) {
            image.setPixel(x, y-1, newColor.rgb());
            point.first = x;
            point.second = y - 1;
            queue.push(point);
        }
    }
    // Setting buffer (QPixmap) to filled QImage
    // using copy assignment operator).
    buffer = image;
    repaint();
    gridDrawHelper();

    QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
    enableFill = false;
    return;
}