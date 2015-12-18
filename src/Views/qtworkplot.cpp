#include "qtworkplot.h"

QtWorkPlot::QtWorkPlot()
{
    Initialize();
    fullWork = 0.0;
    lastEnergy = -1;
}

void QtWorkPlot::Initialize()
{
    xRange = 50;
    yRange = 10;
    plot.xAxis->setRange(0, xRange);
    plot.yAxis->setRange(0, yRange);
    plot.xAxis->setLabel("Время");
    plot.yAxis->setLabel("Суммарная\nРабота поршня");
}

void QtWorkPlot::Update(const BilliardModel & model, double timeStep)
{
    const BilliardModel::MyCollisionBox * cb = model.getCollisionBox();
    double Energy = cb->GetEnergy();
    if(lastEnergy < 0)
        lastEnergy = Energy;
    if(lastEnergy < Energy)
    {
        fullWork += Energy - lastEnergy;
    }
    lastEnergy = Energy;

    AddData(fullWork, timeStep);

    plot.replot();
}

void QtWorkPlot::Reload(const BilliardModel &)
{
    plot.clearGraphs();
    plot.addGraph();
    Initialize();

    x = 0;
    lastEnergy = -1;
    fullWork = 0;
}


