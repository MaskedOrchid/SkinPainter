#include "Home.h"
#include "pixelcanvas.h"

#include <QApplication>
#include <QColorDialog>
#include <QFileDialog>
#include <QImageWriter>
#include <QInputDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QCloseEvent>

Home::Home(QWidget *parent)
    : QMainWindow(parent),Canvas(new PixelCanvas(this))
{
    setCentralWidget(Canvas);

    createActions();
    createMenus();

    setWindowTitle(tr("Skin Painter"));
    resize(500, 500);
}

void Home::open(){
    //to open up an image for testing
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty())
        Canvas->openImage(fileName);
}

void Home::penColor(){
    QColor newColor = QColorDialog::getColor(Canvas->penColor());
    if (newColor.isValid())
        Canvas->setPenColor(newColor);
}

void Home::createActions(){
    //setting up the open actions
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &Home::open);
    //setting up the color selection action
    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, &QAction::triggered, this, &Home::penColor);


}
void Home::createMenus(){
    //creating the file and open menu action
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);

    //creating the pen color actions
    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
}
