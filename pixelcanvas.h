#ifndef PIXELCANVAS_H
#define PIXELCANVAS_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>

class PixelCanvas: public QWidget
{
    Q_OBJECT
public:
    PixelCanvas(QWidget *parent = nullptr,QSize size=QSize(10,10));
    bool openImage(const QString &fileName);
    void setPenColor(const QColor &newColor);

    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
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
    float PixelRatio;
};
#endif // PIXELCANVAS_H

// has an image of actual size, and has the size, and well as the scale ratio, when a rescale even happens it will get how much larger it is
//changes the scale ratio, rescale and redraw and update
