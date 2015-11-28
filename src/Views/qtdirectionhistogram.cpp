#include "qtdirectionhistogram.h"

QtDirectionHistogram::QtDirectionHistogram()
{
    Initialize();
}

void QtDirectionHistogram::Initialize()
{
    plot.yAxis->setLabel("Количество частиц");
}

void QtDirectionHistogram::Update(const BilliardModel & model, double)
{
    Initialize();

    double PI = acos(-1.0);

    QVector<double> values;
    const BilliardModel::MyCollisionBox * cb = model.getCollisionBox();
    const BilliardModel::MyCollisionBox::ParticleList & pl = cb->getParticles();

    for(auto & particle : pl)
    {
        auto & vel = particle.getVelocity();
        values.push_back(atan2(vel[1], vel[0]) + PI);
    }

    SetData(values, values.size() / 10);

    plot.replot();
}



