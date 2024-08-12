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
    Q_OBJECT

public:
    ImageView( QWidget *parent = 0, const char *name = 0 );

    void setPenColor( const QColor &c ) { 
        pen.setColor( c );
        if(c != paletteBackgroundColor()) {
            brushColour = c;
        }
    }

    QColor penColor() { 
        return pen.color();
    }

    int penWidth() { 
        return pen.width();
    }

    void gridlinesToggle() {
        enableGridLines = !enableGridLines;
        if(enableGridLines){ 
            QPainter painter(this);
            drawGridlines(painter);
        } else {
            repaint();
        }
    }

    void resizeCanvas(double scaleFactor) {
        QImage imageConversion = buffer.convertToImage();
        QImage scaled = imageConversion.scale(buffer.width()*scaleFactor,
         buffer.height()*scaleFactor);
        buffer = scaled;
        repaint();
        gridDrawHelper();
    }

    void setColourPicker() {
        if(enableFill) {
            QMessageBox::warning(this, "Raster Editor",
             "Please disable fill before enabling colour picker."); 
        } else {
            enableColourPicker = !enableColourPicker;
            if(enableColourPicker) {
                QApplication::setOverrideCursor(QCursor(Qt::CrossCursor));
            } else {
                QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
            }
        }
    }

    void createNewImage(int width, int height) {
        buffer = QPixmap(width, height);
        buffer.fill(16777215);
        repaint();
        gridDrawHelper();
    }

    void setFillMode() {
        if(enableColourPicker) {
            QMessageBox::warning(this, "Raster Editor",
             "Please disable colour picker before enabling fill.");
        } else {
            enableFill = !enableFill;
            if(enableFill) {
                QApplication::setOverrideCursor(QCursor(Qt::PointingHandCursor));
            } else {
                QApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
            }
        }
    }

    QPixmap buffer;
    int mouseX;
    int mouseY;
    bool enableColourPicker;
    bool enableFill;
    QColor brushColour;

public slots:
    void setPenWidth( int w ) { 
        pen.setWidth( w );
    }
    void gridDrawHelper();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent( QMouseEvent *e );
    void mouseMoveEvent( QMouseEvent *e );
    void resizeEvent( QResizeEvent *e );
    void paintEvent( QPaintEvent *e );
    bool withinBounds (const int x, const int y);
    void drawGridlines(QPainter &painter);
    void useColourPicker(const int x, const int y);
    void useFill(const int x, const int y);

    QPen pen;
    QPointArray polyline;

    bool mousePressed;
    bool enableGridLines; 

};

#endif