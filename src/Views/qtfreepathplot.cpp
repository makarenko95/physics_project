#include "qtfreepathplot.h"

QtFreePathPlot::QtFreePathPlot()
{
    Initialize();
}


void QtFreePathPlot::Update(const BilliardModel & model, double timeStep)
{
    double free_path = model.getCollisionBox()->GetFreePath();
    AddData(free_path, timeStep);
    plot.replot();
}

void QtFreePathPlot::Initialize()
{
    xRange = 50;
    yRange = 100;
    plot.xAxis->setRange(0, xRange);
    plot.yAxis->setRange(0, yRange);
    plot.xAxis->setLabel("Время");
    plot.yAxis->setLabel("Средняя длина\nсвободного пробега");
}

double QtFreePathPlot::ToOffset(double timeStep)
{
    return timeStep;
}
