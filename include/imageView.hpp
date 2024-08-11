#ifndef IMAGEVIEW_HPP
#define IMAGEVIEW_HPP
// Used the QT3 Docs Scribble example to aid in 
// the implementation of drawing functionality:
// https://doc.qt.io/archives/3.3/scribble-example.html

#include <qmainwindow.h>
#include <qpen.h>
#include <qpoint.h>
#include <qpixmap.h>
#include <qwidget.h>
#include <qpointarray.h>

class QMouseEvent;
class QResizeEvent;
class QPaintEvent;

class ImageView : public QWidget
{
    Q_OBJECT

public:
    ImageView( QWidget *parent = 0, const char *name = 0 );

    void setPenColor( const QColor &c )
    { pen.setColor( c ); }

    QColor penColor()
    { return pen.color(); }

    int penWidth()
    { return pen.width(); }

    QPixmap buffer;
    int mouseX;
    int mouseY;

public slots:
    void setPenWidth( int w )
    { pen.setWidth( w ); }

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent( QMouseEvent *e );
    void mouseMoveEvent( QMouseEvent *e );
    void resizeEvent( QResizeEvent *e );
    void paintEvent( QPaintEvent *e );
    bool withinBounds (const QMouseEvent *e);

    QPen pen;
    QPointArray polyline;

    bool mousePressed;

};

#endif