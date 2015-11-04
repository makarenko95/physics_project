#include "application.h"
#include <Views/qtbilliardview.h>
#include <QHBoxLayout>
#include <Control/qtbilliardcontrol.h>

Application::Application(QWidget *parent)
    : QWidget(parent), model({2.0,500,300,20.0,0.0,150.0,50.0}), interval(15)
{
    controller.SetParams({2.0,500,300,20.0,0.0,150.0,50.0});
    view = new QtBilliardView;
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
    if(timer->isActive())
        timer->stop();
    BilliardModelParams params = controller.GetParams();
    model.Reload(&params);
    timer->start(interval);
}
void Application::buttonStopTimerPressed()
{
    if(timer->isActive()){
        timer->stop();
    }
    else timer->start(interval);
}
void Application::radiusChanged(double radius)
{
    controller.SetParticleRadius(radius);
}
void Application::sizeChanged(int size)
{
    controller.SetBoxSize(size);
}
void Application::particlenumChanged(int num)
{
    controller.SetMaxParticleNumber(num);
}
void Application::particleVelocityChanged(double vel)
{
    controller.SetMaxParticleVelocity(vel);
}
void Application::pistonPathChanged(double path)
{
    controller.SetPistonEndPosition(path);
}
void Application::pistonVelocityChanged(double vel)
{
    controller.SetPistonVelocity(vel);
}
void Application::changeViewerSettings_trace()
{
    model.changeViewerSettings_DrawTrace();
}
void Application::changeViewerSettings_particles()
{
    model.changeViewerSettings_DrawParticles();
}
