#include "qtvelocityhistogram.h"
#include <Models/billiardmodel.h>

QtVelocityHistogram::QtVelocityHistogram()
{
    Initialize();
}

void QtVelocityHistogram::Initialize()
{
    plot.yAxis->setLabel("Количество\nчастиц");
    plot.xAxis->setLabel("Разбиения");

    bars->setName("По модулю");

    plot.legend->setVisible(true);
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

    int num_columns = std::max(1, int(std::max(1, values.size() / 10)));
    SetData(values, num_columns);

    plot.replot();
}

