#ifndef PIXELCANVAS_H
#define PIXELCANVAS_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QPointF>

class PixelCanvas: public QWidget
{
    Q_OBJECT
public:
    PixelCanvas(QWidget *parent = nullptr,QSize size=QSize(64,64));
    // make this accept an image file, or a section of one, allowing for the user to draw on that section only
    bool openImage(const QString &fileName);
    //maybe a function to check if the draw area is invalid, so if it does not have am image accosated with it yet.
    void setPenColor(const QColor &newColor);

    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    //add saving functions
    //add the ablitly to draw like you would on a drawing app
private:
    void resizeImage(QImage *image, const QSize &newSize);
    void setPenWidth(int newWidth);// ensuring that the petwidth is equal to the ratio size?
    void drawPixel(QMouseEvent *event);
    bool Drawing = false;
    int myPenWidth = 1;
    QColor myPenColor = Qt::blue;
    QImage RenderImage;//this one is the rendered image, the one the software displays
    QImage ActualImage;//the exported image, this one is of the actual size
    //need to some out snap the mouse draw positions to a grid
    QPoint lastPoint;
    QSize ActualSize;
    QSize RenderSize;
    QPointF PixelRatio;// change this to a Point, for x and y ratio size
};
#endif // PIXELCANVAS_H

// has an image of actual size, and has the size, and well as the scale ratio, when a rescale even happens it will get how much larger it is
//changes the scale ratio, rescale and redraw and update
