#include "pixelcanvas.h"

#include <QMouseEvent>
#include <QPainter>
#include <QPointF>

//rixel= the scaled up rect representing the size of a pixel in the scaled up image

PixelCanvas::PixelCanvas(QWidget *parent,QSize size): QWidget(parent)
{
    ActualSize=size;
    RenderSize=size;
    PixelRatio=QPoint(1,1);//at the start they are one to one
    setAttribute(Qt::WA_StaticContents);
    //setting the render image for all of this
    QImage newImage(size, QImage::Format_ARGB32); //QImage::Format_ARGB32 should be the standard channels for pngs
    RenderImage=newImage;
    RenderImage.fill(qRgba(255, 255, 255,0));
    ActualImage=newImage;
    update();
}
bool PixelCanvas::openImage(const QString &fileName){
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;
    //setting the actual image to the open image
    ActualImage=loadedImage;
    //scaling up the new opened image
    QSize newSize = loadedImage.size().expandedTo(RenderSize);
    ActualSize=loadedImage.size();
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
        //if the window was scaled up
        int newWidth = qMax(width(), RenderImage.width());
        int newHeight = qMax(height(), RenderImage.height());
        //finding the smaller of the two to maintain the square display of the image
        int newsize=qMin(newWidth,newHeight);
        //need to repaint it, not just change the scale
        resizeImage(&RenderImage, QSize(newsize,newsize));
        update();
    }else if (width() < RenderImage.width() || height() < RenderImage.height()) {
        //if the window was scaled down
        int newWidth = qMin(width(), RenderImage.width());
        int newHeight = qMin(height(), RenderImage.height());
        //finding the smaller of the two to maintain the square display of the image
        int newsize=qMin(newWidth,newHeight);
        //need to repaint it, not just change the scale
        resizeImage(&RenderImage, QSize(newsize,newsize));
        update();
    }
    QWidget::resizeEvent(event);
}

void PixelCanvas::drawPixel(QMouseEvent *event){
    //need to draw the pixels and translate based off of the ratios
    QPainter Actpainter(&ActualImage);
    //Actpainter.setBrush(QBrush(myPenColor));
    Actpainter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine,Qt::SquareCap,Qt::RoundJoin));

    //get to the nearest pixel place, ( how many rixels we need tp step before getting to the equivlent pixel location)
    float x=event->pos().x()/PixelRatio.x();
    float y=event->pos().y()/PixelRatio.y();
    //drawing that pixel
    qDebug()<< "pixel : ("<< x<<","<<y<<")";
    Actpainter.drawPoint(x,y);
    update();
    //need to update the render canvas
    RenderImage=ActualImage;
    resizeImage(&RenderImage,RenderSize);
}
void PixelCanvas::resizeImage(QImage *image, const QSize &newSize){
    RenderSize=newSize;
    //figuring out the rixel ratio
    qreal xrixel=(RenderSize.width()*1.0)/(ActualSize.width());
    qreal yrixel=(RenderSize.height()*1.0)/(ActualSize.height());
    PixelRatio=QPointF(xrixel,yrixel);
    //setting the pen width to align with the new rixel size
    //this->setPenWidth(PixelRatio.x());
    qDebug()<< "PixelRatio : ("<< PixelRatio.x()<<","<<PixelRatio.y()<<")";
    qDebug()<< "RenderSize : ("<< RenderSize.width()<<","<<RenderSize.height()<<")";
    qDebug()<< "ActualSize : ("<< ActualSize.width()<<","<<ActualSize.height()<<")";

    if (image->size() == newSize)
        return;
    *image=image->scaled(newSize,Qt::KeepAspectRatio);
    QImage newImage(newSize, QImage::Format_ARGB32);
    newImage.fill(qRgba(255, 255, 255,0));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}
