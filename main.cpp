#include "application.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Application w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();

    return a.exec();
}
