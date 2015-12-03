#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include <Models/billiardmodel.h>
#include <Views/qtbilliardview.h>
#include <Views/qtplot.h>
#include <Control/qtbilliardcontrol.h>
#include <QTimer>
#include <Views/qtaveragevelocityplot.h>
#include <Views/qtvelocityhistogram.h>
#include <Views/qtdirectionhistogram.h>
#include <Views/qtworkplot.h>

class Application : public QWidget
{
    Q_OBJECT

public:
    Application(QWidget *parent = 0);

private:
    BilliardModel model;
    QtBilliardView view;
    QtBilliardControl controller;
    QtAverageVelocityPlot av_plot;
    QtVelocityHistogram v_histogram;
    QtDirectionHistogram d_histogram;
    QtWorkPlot w_plot;
public slots:
};

#endif // APPLICATION_H
