#ifndef DEMONSTRATION_H
#define DEMONSTRATION_H

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
#include <Views/qtfreepathplot.h>
#include <QPushButton>

class Demonstration : public QWidget
{
    Q_OBJECT
public:
    explicit Demonstration(QWidget *parent = 0);

signals:

private:
    BilliardModel model;
    QtBilliardView view;
    QtBilliardControl controller;
    QtAverageVelocityPlot av_plot;
    QtVelocityHistogram v_histogram;
    QtDirectionHistogram d_histogram;
    QtWorkPlot w_plot;
    QtFreePathPlot fp_plot;

public slots:
};

#endif // DEMONSTRATION_H
