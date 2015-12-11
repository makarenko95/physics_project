#ifndef QTFREEPATHPLOT_H
#define QTFREEPATHPLOT_H

#include "qtplot.h"
#include <Models/billiardmodel.h>

class QtFreePathPlot : public QtPlot
{
public:
    QtFreePathPlot();
    void Update(const BilliardModel & model, double);
    void Initialize();
    double ToOffset(double);

signals:

public slots:
};

#endif // QTFREEPATHPLOT_H
