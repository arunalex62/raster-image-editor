#ifndef IMAGEVIEW_HPP
#define IMAGEVIEW_HPP
// Used the QT3 Docs Scribble example to aid in 
// the implementation of drawing functionality:
// https://doc.qt.io/archives/3.3/scribble-example.html

#include <qapplication.h>
#include <qmainwindow.h>
#include <qpen.h>
#include <qpoint.h>
#include <qpixmap.h>
#include <qwidget.h>
#include <qpointarray.h>
#include <qpainter.h>
#include <qimage.h>
#include <qcursor.h>
#include <qmessagebox.h>
#include <qcolor.h>

class QMouseEvent;
class QResizeEvent;
class QPaintEvent;

class ImageView : public QWidget
{
    // Allows for a tight integration with signal/slot mechanism
    // between different parts of the application.
    Q_OBJECT

public:
    ImageView( QWidget *parent = 0, const char *name = 0 );

    // Sets the current pen/brush colour to
    // the colour passed into the method.
    void setPenColor( const QColor &c ) { 
        pen.setColor( c );
        // This case handles the eraser tool usage.
        // If the eraser tool is selected, it should not be 
        // set as the previous brush colour.
        if(c != paletteBackgroundColor()) {
            brushColour = c;
        }
    }

    // Returns the current pen/brush colour
    // as a QColor.
    QColor penColor() const { 
        return pen.color();
    }

    // Returns the current pen/brush size
    // as an integer.
    int penWidth() const { 
        return pen.width();
    }

    // Method that is called when the "Grid-lines toggle"
    // button is pressed. This toggles the enableGridlines
    // setting, and draws gridlines if enabled.
    void gridlinesToggle() {
        enableGridLines = !enableGridLines;
        if(enableGridLines){ 
            QPainter painter(this);
            drawGridlines(painter);
        } else {
            // If this method turns grid lines off, 
            // then repaint is called to redraw the canvas
            // without grid lines.
            repaint();
        }
    }

    // Resets the canvas/image offset back to the center.
    // Then repaints and redraws grid lines (if needed).
    void resetCamera() {
        offsetX = 0;
        offsetY = 0;
        repaint();
        gridDrawHelper();
    }

    // Given a scale factor, this method resizes the canvas
    // by converting the QPixmap buffer to a QImage, and scaling
    // that. Then the buffer is set to the QImage and the 
    // view is repainted and redraws grid lines (if needed).
    void resizeCanvas(const double scaleFactor) {
        QImage imageConversion = buffer.convertToImage();
        QImage scaled = imageConversion.scale(buffer.width()*scaleFactor,
         buffer.height()*scaleFactor);
        buffer = scaled;
        repaint();
        gridDrawHelper();
    }

    // Method that is called when the "Colour Picker"
    // tool is pressed. This toggles the enableColourPicker
    // setting.
    void setColourPicker() {
        // If the fill tool is currently enabled, show warning
        // and exit.
        if(enableFill) {
            QMessageBox::warning(this, "Raster Editor",
             "Please disable fill before enabling colour picker."); 
        } else {
            enableColourPicker = !enableColourPicker;
            if(enableColourPicker) {
                // Change mouse cursor depending on if colour picker is
                // enabled or disabled.
                QApplication::setOverrideCursor(QCursor(Qt::CrossCursor));
            } else {
                QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
            }
        }
    }

    // Creates a new image given integer width and height.
    // Buffer is set to a blank white canvas of these dimensions,
    // and then repainted and redraws grid lines (if needed).
    void createNewImage(const int width, const int height) {
        buffer = QPixmap(width, height);
        buffer.fill(16777215);
        repaint();
        gridDrawHelper();
    }

    // Similar to the setColourPicker() method above,
    // method that is called when the "Fill"
    // tool is pressed. This toggles the enableFill
    // setting.
    void setFillMode() {
        // If colour picker is currently enabled, 
        // show the user a warning and return.
        if(enableColourPicker) {
            QMessageBox::warning(this, "Raster Editor",
             "Please disable colour picker before enabling fill.");
        } else {
            enableFill = !enableFill;
            if(enableFill) {
                // Change mouse cursor depending on if fill tool is
                // enabled or disabled.
                QApplication::setOverrideCursor(QCursor(Qt::PointingHandCursor));
            } else {
                QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
            }
        }
    }
    // The image buffer storage.
    QPixmap buffer;
    // Stores the current mouse position to display
    // in the status bar.
    int mouseX;
    int mouseY;
    // Variables that are set if colour picker/fill
    // are toggled respectively.
    bool enableColourPicker;
    bool enableFill;
    // The current brush colour, expect when
    // the eraser is set.
    QColor brushColour;

public slots:
    // Slot to set the brush width. Slot is used for
    // the brush size slider to update in real-time.
    void setPenWidth( int w ) { 
        pen.setWidth( w );
    }
    // Helper slot function to draw the gridlines if 
    // the enableGridlines boolean is true.
    void gridDrawHelper();

protected:
    // Inherited members from QWidget that were
    // altered for the specific drawing functionality
    // in this application.
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent( QMouseEvent *e );
    void mouseMoveEvent( QMouseEvent *e );
    void resizeEvent( QResizeEvent *e );
    void paintEvent( QPaintEvent *e );
    // Helper function to check if the parameters x and y are within
    // the bounds of the image.
    bool withinBounds (const int x, const int y);
    // Function that draws grid lines on the canvas.
    void drawGridlines(QPainter &painter);
    // Function that sets the current brush colour to
    // the pixel colour at position (x,y) in the image.
    void useColourPicker(const int x, const int y);
    // Function that utilizes a flood-fill algorithm to
    // selectively fill the image with the current brush
    // colour, starting at point (x,y) in the image.
    void useFill(const int x, const int y);

    // Variables used for drawing and storing line
    // segment data, respectively.
    QPen pen;
    QPointArray polyline;

    // Booleans used to determine if the mouse is pressed, or
    // if grid lines or panning is enabled, respectively.
    bool mousePressed;
    bool enableGridLines; 
    bool enablePanning;

    // Storage for the lastPosition for camera movement.
    QPoint lastPos;
    // The current camera offset of the image, relative
    // to the center.
    int offsetX;
    int offsetY;

};

#endif