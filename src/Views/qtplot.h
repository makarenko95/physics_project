#ifndef QTPLOT_H
#define QTPLOT_H

#include <QWidget>
#include <qcustomplot.h>
#include "billiardview.h"

class BilliardModel;

class QtPlot : public QWidget,
               public BilliardView
{
    Q_OBJECT
public:
    QtPlot(QWidget *parent = 0);
    void Reload(const BilliardModel &);
    virtual void Initialize() = 0;
    virtual double ToOffset(double) {return 1;}
    void AddData(double, double);
    void ExpandX();
    void ExpandY();
signals:

public slots:

protected:
    QCustomPlot plot;
    double x;
    double xRange;
    double yRange;
};

#endif // QTPLOT_H
