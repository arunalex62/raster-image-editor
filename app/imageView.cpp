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
    mouseX(-1), mouseY(-1), enableColourPicker(false), enableFill(false),
     pen( Qt::black, 3 ), polyline(3), mousePressed(false),
      enableGridLines(false), enablePanning(false), offsetX(0), offsetY(0) {

    // Set default image to white.
    buffer.fill(16777215);

    pen.setCapStyle(Qt::RoundCap);
    // This setting needs to be enabled for mouse position
    // display functionality in the status bar.
    setMouseTracking(true);
}

void ImageView::mousePressEvent(QMouseEvent *e) {

    if(e->button() == Qt::MidButton) {
        // If the middle mouse button is pressed, enable
        // panning functionality.
        lastPos = e->pos();
        enablePanning = true;
        return;
    }

    mousePressed = true;
    // Calculates the current pixel position of the mouse click,
    // taking into account the image is centered, and potentially offset
    // due to panning.
    int x = e->pos().x() - (width() - buffer.width())/2 - offsetX;
    int y = e->pos().y() - (height() - buffer.height())/2 - offsetY;
    // If the colour picker or fill tool are enabled, those methods are called. Only if the
    // current mouse position is within the image itself.
    if((enableColourPicker || enableFill) && withinBounds(e->pos().x()-offsetX, e->pos().y()-offsetY)) {
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
    // Sets the line segment array all to 1 Point if a single click was performed.
    polyline[2] = polyline[1] = polyline[0] = QPoint(x, y);
}

void ImageView::mouseReleaseEvent(QMouseEvent *) {
    enablePanning = false;
    mousePressed = false;
    // When the mouse is released, the canvas will be 
    // repainted and with grid lines (if enabled).
    repaint();
    gridDrawHelper();
}

void ImageView::mouseMoveEvent( QMouseEvent *e ) {
    // Calculations to move the image if panning is enabled
    // The user has to actively hold middle mouse button for this
    // to happen.
    if (enablePanning) {
        int dx = e->x() - lastPos.x();
        int dy = e->y() - lastPos.y();
        offsetX += dx;
        offsetY += dy;
        lastPos = e->pos();
        // Repaint to display to the user the new canvas position.
        repaint();
        return;
    }
    // Current mouse position on the image is stored, taking into
    // account the image being centered, and a potential panning offset.
    mouseX = e->pos().x() - (width() - buffer.width())/2 - offsetX;
    mouseY = e->pos().y() - (height() - buffer.height())/2 - offsetY;
    // Updates the status bar with the mouse information just stored.
    StatusBar::setStatusBarMouse(static_cast<MainWindow*>(parent()));
    if(enableColourPicker || enableFill) {
        return;
    }
    if (mousePressed && withinBounds(e->pos().x()-offsetX, e->pos().y()-offsetY)) {
        // Painting functionality.
        QPainter painter;
        painter.begin(&buffer);
        painter.setPen( pen );
        // polyline is an array of points, so each time 
        // the user paints, the connected line segments from the
        // points stored in polyline are drawn on the screen.
        polyline[2] = polyline[1];
        polyline[1] = polyline[0];
        polyline[0] = QPoint(std::max(0, std::min(mouseX, buffer.width() - 1)),
        std::max(0, std::min(mouseY, buffer.height() - 1)));
        painter.drawPolyline( polyline );
        painter.end();

        // This is an optimized way to update only the area of image 
        // that was painted on. This avoids having to repaint the whole image
        // constantly to display changes to the user.
        QRect r = polyline.boundingRect();
        int translatedX = r.x() + (width() - buffer.width())/2 + offsetX;
        int translatedY = r.y() + (height() - buffer.height())/2 + offsetY;
        QRect translatedRect(translatedX, translatedY, r.width(), r.height());

        // The rectangle that bounds the drawing, along with its position
        // are calculated and that area of the image is repainted dynamically
        // while drawing.
        update(translatedRect);
    }
}
// This method gets called each time the window is resized, like when resizing manually
// using the corner of the window and dragging.
void ImageView::resizeEvent( QResizeEvent *e ) {
    QWidget::resizeEvent(e);
    update();
    // After resize, if grid lines are enabled, re draw the grid lines.
    if(enableGridLines) {
        // Need to put 500ms timer because repaint() gets called automatically
        // after resizeEvent(), and that would get rid of the grid lines.
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(gridDrawHelper()));
        timer->start(500, TRUE);
    }
}

// Repaints the image, taking into account any current offsets.
void ImageView::paintEvent( QPaintEvent *) {
    QPainter painter(this);
    int x = (width() - buffer.width())/2 + offsetX;
    int y = (height() - buffer.height())/2 + offsetY;

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

// Function that draws the grid lines onto the image (if enabled).
void ImageView::drawGridlines(QPainter &painter) { 
    painter.setPen(QPen(Qt::lightGray, 1, Qt::DotLine));

    int xStart = (width() - buffer.width()) / 2 + offsetX;
    int yStart = (height() - buffer.height()) / 2 + offsetY;

    // Drawing the vertical grid lines in increments of 20 pixels.
    for (int x = 0; x < buffer.width(); x += 20) {
        painter.drawLine(x + xStart, yStart, x + xStart, buffer.height() + yStart);
    }

    // Drawing the horizontal grid lines in increments of 20 pixels.
    for (int y = 0; y < buffer.height(); y += 20) {
        painter.drawLine(xStart, y + yStart, buffer.width() + xStart, y + yStart);
    }
}

// Easy to call helper function that checks if grid lines are
// enabled before calling the method.
void ImageView::gridDrawHelper() {
    if(enableGridLines) {
        QPainter painter(this);
        drawGridlines(painter);
    }
}

// This method gets called when the colour picker is activated and clicked
// on a part of the image.
void ImageView::useColourPicker(const int x, const int y) {
    // Converts QPixmap buffer to QImage (to access pixel-level data).
    QImage image = buffer.convertToImage();
    // Gets colour at coordinates passed in.
    QColor color(image.pixel(x, y));
    // Sets the current pen colour to that colour.
    setPenColor(color);
    // Changes the cursor back to normal.
    QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
    enableColourPicker = false;
    // Updates the status bar with the newly selected current colour.
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