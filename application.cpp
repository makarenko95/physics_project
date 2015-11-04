#include "application.h"
#include <Views/qtbilliardview.h>
#include <QHBoxLayout>
#include <Control/qtbilliardcontrol.h>

Application::Application(QWidget *parent)
    : QWidget(parent), model({2.0,500,300,20.0,0.0,150.0,50.0}), interval(15)
{
    QtBilliardView * view = new QtBilliardView;
    model.AddView(*view);
    QHBoxLayout * layout = new QHBoxLayout;
    layout->addWidget(view);
    QtBilliardControl * control = new QtBilliardControl(this);
    layout->addWidget(control);
    setLayout(layout);
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    timer->start(interval);
}

Application::~Application()
{
    delete timer;
}

void Application::onTimeOut()
{
    model.update(interval * 1.0 / 1000);
}
void Application::buttonReloadPressed()
{
    model.Reload(0);
}
