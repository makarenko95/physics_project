#include "application.h"
#include <Views/qtbilliardview.h>
#include <QHBoxLayout>

Application::Application(QWidget *parent)
    : QWidget(parent), interval(10)
{
    QtBilliardView * view = new QtBilliardView;
    model.AddView(*view);
    QHBoxLayout * layout = new QHBoxLayout;
    layout->addWidget(view);
    setLayout(layout);

    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    timer->start(interval);
}

Application::~Application()
{
    //delete timer;
}

void Application::onTimeOut()
{
    model.update(interval * 1.0 / 1000);
}
