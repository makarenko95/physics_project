#ifndef QTAVERAGEVELOCITYPLOT_H
#define QTAVERAGEVELOCITYPLOT_H
#include "qtplot.h"
#include <Models/billiardmodel.h>

class QtAverageVelocityPlot : public QtPlot
{
public:
    QtAverageVelocityPlot();
    void Update(const BilliardModel & model, double);
    void Initialize();
    double ToOffset(double);
signals:

public slots:
};

#endif // QTAVERAGEVELOCITYPLOT_H
