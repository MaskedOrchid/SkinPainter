#include "Home.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Home h;
    h.show();
    return app.exec();
}
