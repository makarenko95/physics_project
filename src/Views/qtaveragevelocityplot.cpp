#include "qtaveragevelocityplot.h"
QtAverageVelocityPlot::QtAverageVelocityPlot()
{
    Initialize();
}

void QtAverageVelocityPlot::Update(const BilliardModel & model, double timeStep)
{
    double vel = model.GetAverageVelocity();
    AddData(vel, timeStep);
    plot.replot();
}

void QtAverageVelocityPlot::Initialize()
{
    xRange = 50;
    yRange = 100;
    plot.xAxis->setRange(0, xRange);
    plot.yAxis->setRange(0, yRange);
    plot.xAxis->setLabel("Время");
    plot.yAxis->setLabel("Средний модуль\nскорости");
}

double QtAverageVelocityPlot::ToOffset(double timeStep)
{
    return timeStep;
}

