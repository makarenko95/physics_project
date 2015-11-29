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
    explicit QtHistogram(QWidget *parent = 0);
    void Reload(const BilliardModel &);
    virtual void Initialize() = 0;
    void SetData(QVector<double> &, int);

private:
    double max_max_num;

signals:

public slots:

protected:
    QCustomPlot plot;
    QCPBars * bars;
};

#endif // QTHISTOGRAM_H
