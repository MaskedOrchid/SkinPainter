#include "pixelcanvas.h"

#include <QMouseEvent>
#include <QPainter>

PixelCanvas::PixelCanvas(QWidget *parent,QSize size): QWidget(parent)
{
    ActualSize=size;
    RenderSize=ActualSize;
    PixelRatio=1;//at the start they are one to one
    setAttribute(Qt::WA_StaticContents);
    QImage newImage(size, QImage::Format_RGB32);
    RenderImage=newImage;
    RenderImage.fill(qRgb(255, 255, 255));
    update();
}
bool PixelCanvas::openImage(const QString &fileName){
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    QSize newSize = loadedImage.size().expandedTo(RenderSize);
    ActualSize=loadedImage.size();
    printf("Newsize : (%i,%i)\n",newSize.rwidth(),newSize.rheight());
    //resize updates the ratios and sizes
    resizeImage(&loadedImage, newSize);
    RenderImage = loadedImage;
    update();
    return true;
}
void PixelCanvas::setPenColor(const QColor &newColor){
     myPenColor = newColor;
}
void PixelCanvas::setPenWidth(int newWidth){
    myPenWidth=newWidth;
}

void PixelCanvas::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->position().toPoint();
        Drawing = true;
        drawPixel(event);
    }
}
void PixelCanvas::mouseMoveEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && Drawing) {
        //draw where the mouse moves to
        drawPixel(event);
    }
}
void PixelCanvas::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && Drawing) {
        //stop drawing
        Drawing = false;
    }
}
void PixelCanvas::paintEvent(QPaintEvent *event){
    //drawing the events that occured
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, RenderImage, dirtyRect);
}
void PixelCanvas::resizeEvent(QResizeEvent *event){
    if (width() > RenderImage.width() || height() > RenderImage.height()) {
        int newWidth = qMax(width(), RenderImage.width());
        int newHeight = qMax(height(), RenderImage.height());
        resizeImage(&RenderImage, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void PixelCanvas::drawPixel(QMouseEvent *event){
    //need to draw the pixels and translate based off of the ratios
    QPainter Renpainter(&RenderImage);
    Renpainter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine,Qt::SquareCap,Qt::RoundJoin));
    //translating to the orignal coordinates
    //get to the nearest pixel place, how many ratio steps to this x, coord, then place it in the center ( since we know the pixel location
    //same for the y value, and thus draw the rectangle from that point to the next,
    //and update the other image with the actual pixels so we have the actual and the rendered image
    int x = event->pos().x();
    int y = event->pos().y();
    Renpainter.drawPoint(x, y);
    update();
}
void PixelCanvas::resizeImage(QImage *image, const QSize &newSize){
    RenderSize=newSize;
    //figuring out the pixel ratio
    PixelRatio=RenderSize.rwidth()/(ActualSize.rwidth());
    printf("PixelRatio: %f\n",PixelRatio);
    printf("RenderSize : (%i,%i)\n",RenderSize.rwidth(),RenderSize.rheight());
    printf("ActualSize : (%i,%i)\n",ActualSize.rwidth(),ActualSize.rheight());
    this->setPenWidth(PixelRatio);
    if (image->size() == newSize)
        return;
    *image=image->scaled(newSize,Qt::KeepAspectRatio);
}
