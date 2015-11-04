#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include <Models/billiardmodel.h>
#include <Views/qtbilliardview.h>
#include <QTimer>

class Application : public QWidget
{
    Q_OBJECT

public:
    Application(QWidget *parent = 0);
    ~Application();
private:
    BilliardModel model;
    BilliardControl controller;
    QtBilliardView *view;
    QTimer * timer;
    int interval;

public slots:
    void onTimeOut();
    void buttonReloadPressed();
    void buttonStopTimerPressed();
    void radiusChanged(double);
    void sizeChanged(int);
    void particlenumChanged(int);
    void particleVelocityChanged(double);
    void pistonPathChanged(double);
    void pistonVelocityChanged(double);
    void changeViewerSettings_trace();
    void changeViewerSettings_particles();
};

#endif // APPLICATION_H
