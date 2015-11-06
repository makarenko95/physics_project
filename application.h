#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include <Models/billiardmodel.h>
#include <Views/qtbilliardview.h>
#include <Control/qtbilliardcontrol.h>
#include <QTimer>

class Application : public QWidget
{
    Q_OBJECT

public:
    Application(QWidget *parent = 0);

private:
    BilliardModel model;
    QtBilliardView view;
    QtBilliardControl controller;

public slots:
};

#endif // APPLICATION_H
