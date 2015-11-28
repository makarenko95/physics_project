#include "qtvelocityhistogram.h"
#include <Models/billiardmodel.h>

QtVelocityHistogram::QtVelocityHistogram()
{
    //SetWindowTitle("Гистограмма модуля скорости");
    Initialize();
}

void QtVelocityHistogram::Initialize()
{
    plot.yAxis->setLabel("Количество\nчастиц");
}

void QtVelocityHistogram::Update(const BilliardModel & model, double)
{
    Initialize();

    const BilliardModel::MyCollisionBox * cb = model.getCollisionBox();
    const BilliardModel::MyCollisionBox::ParticleList & pl = cb->getParticles();

    QVector<double> values;

    for (auto & particle : pl)
    {
        values.push_back(particle.getVelocity().mag());
    }

    int num_columns = std::max(1, int(values.size() / 10));
    SetData(values, num_columns);

    plot.replot();
}

