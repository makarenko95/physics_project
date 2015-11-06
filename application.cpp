#include "application.h"
#include <Views/qtbilliardview.h>
#include <QHBoxLayout>
#include <Control/qtbilliardcontrol.h>

Application::Application(QWidget *parent)
    : QWidget(parent), controller(&model, &view)
{
    QHBoxLayout * layout = new QHBoxLayout;
    layout->addWidget(&view);
    layout->addWidget(&controller);
    setLayout(layout);
}
