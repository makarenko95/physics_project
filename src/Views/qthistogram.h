#ifndef QTHISTOGRAM_H
#define QTHISTOGRAM_H

#include <QWidget>
#include "billiardview.h"
#include <qcustomplot.h>

class QtHistogram : public QWidget,
                    public BilliardView
{
    Q_OBJECT
public:
    explicit QtHistogram(int step = 1, QWidget *parent = 0);
    void Reload(const BilliardModel &);
    virtual void Initialize() = 0;
    virtual void OnUpdate(const BilliardModel &, double) = 0;
    void Update(const BilliardModel &, double);
    void SetData(QVector<double> &, int);
    virtual double ToStep(int) {return 1;}

private:
    double max_max_num;

signals:

public slots:

protected:
    QCustomPlot plot;
    QCPBars * bars;
    int refresh_step;
    int elapsed_steps;
};

#endif // QTHISTOGRAM_H
