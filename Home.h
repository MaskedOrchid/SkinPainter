#ifndef HOME_H
#define HOME_H

#include <QList>
#include <QMainWindow>
#include "pixelcanvas.h"

class PixelCanvas;

//Home:
    // show skins saved
    // create a skin
    // open a skin
    // export skin
        //where to export, and what model
    // open skin with the viewport
        //go to viewport
    //settings
    //color mode
    //and about
//drawing
    //select body part
        //render areas for each of the faces
        //uses paint event and a qpainter object to draw and save that change-
        //maybe use a temp pixel file, that way they can discard changes
        //outside controls
        //pen size
        //color
        //select a color
        //color picker
        //turn on symatery, if limbs turn on symatery for body parts
        //exit to body select
        //save if any changes were made
        //export
        //go to viewport

class Home : public QMainWindow
{
    Q_OBJECT

public:
    Home(QWidget *parent = nullptr);

protected:
//remake this to have it contain, and instantae everything.
private slots:
    void open();
    void penColor();
    //void penWidth();
private:
    void createActions();
    void createMenus();

    QMenu *fileMenu;
    QMenu *optionMenu;

    QAction *openAct;
    QAction *penColorAct;
    //QAction *penWidthAct;

    PixelCanvas *Canvas;

};
#endif // HOME_H



