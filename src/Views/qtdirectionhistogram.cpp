#include "qtdirectionhistogram.h"

QtDirectionHistogram::QtDirectionHistogram()
    : QtHistogram(1)
{
    Initialize();
}

void QtDirectionHistogram::Initialize()
{
    plot.yAxis->setLabel("Количество\nчастиц");
    plot.xAxis->setLabel("Угол в градусах");

    bars->setName("Локальное");
    if(!local)
        plot.graph(0)->setName("Общее");
    plot.legend->setVisible(true);
}

void QtDirectionHistogram::OnUpdate(const BilliardModel & model, double)
{
    Initialize();

    QVector<double> values;
    const BilliardModel::MyCollisionBox * cb = model.getCollisionBox();
    const BilliardModel::MyCollisionBox::ParticleList & pl = cb->getParticles();

    for(auto & particle : pl)
    {
        auto & vel = particle.getVelocity();
        values.push_back(atan2(vel[1], vel[0]) + M_PI);
    }

    int num_columns = std::max(1, values.size() / 10);
    SetData(values, num_columns);

    plot.replot();
}

double QtDirectionHistogram::ToStep(int count)
{
    return 360.0 / count;
}



