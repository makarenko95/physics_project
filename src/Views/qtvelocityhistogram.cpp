#include "qtvelocityhistogram.h"
#include <Models/billiardmodel.h>

QtVelocityHistogram::QtVelocityHistogram()
    : QtHistogram(1), v_max(0.0)
{
    Initialize();
}

void QtVelocityHistogram::Initialize()
{
    plot.yAxis->setLabel("Количество\nчастиц");
    plot.xAxis->setLabel("Модуль скорости");

    bars->setName("Локальное");
    if(!local)
        plot.graph(0)->setName("Общее");
    plot.legend->setVisible(true);
}

void QtVelocityHistogram::OnUpdate(const BilliardModel & model, double)
{
    Initialize();

    const BilliardModel::MyCollisionBox * cb = model.getCollisionBox();
    const BilliardModel::MyCollisionBox::ParticleList & pl = cb->getParticles();

    QVector<double> values;

    for (auto & particle : pl)
    {
        double v = particle.getVelocity().mag();
        if (v > v_max)
        {
            v_max = v;
            if(!local)
                plot.graph(0)->clearData();
            num_of_iterations = 0;
        }

        values.push_back(v);
    }

    int num_columns = std::max(1, int(std::max(1, values.size() / 10)));
    SetData(values, num_columns);

    plot.replot();
}

void QtVelocityHistogram::Reload(const BilliardModel & model)
{
    QtHistogram::Reload(model);
    v_max = 0;
}

double QtVelocityHistogram::ToStep(int count)
{
    return v_max / count;
}

