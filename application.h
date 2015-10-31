#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include <Models/billiardmodel.h>
#include <QTimer>

class Application : public QWidget
{
    Q_OBJECT

public:
    Application(QWidget *parent = 0);
    ~Application();

private:
    BilliardModel model;
    QTimer * timer;
    int interval;

public slots:
    void onTimeOut();
};

#endif // APPLICATION_H
