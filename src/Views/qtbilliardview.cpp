#include "qtbilliardview.h"
#include <Models/billiardmodel.h>

#include <QPainter>

QtBilliardView::QtBilliardView(QWidget *parent)
    : QWidget(parent), model(NULL)
{
    setFixedSize(100, 100);
}

void QtBilliardView::Update(const BilliardModel & model)
{
    SetModel(model);
    update();
}

void QtBilliardView::SetModel(const BilliardModel & m)
{
    model = &m;
}

void QtBilliardView::paintEvent(QPaintEvent *)
{
    if (model)
    {
        const BilliardModel::MyCollisionBox * collisionBox = model->getCollisionBox();
        const BilliardModel::MyCollisionBox::Box &boundaries = collisionBox->getBoundaries();

        auto min = boundaries.min;
        auto max = boundaries.max;

        setFixedSize(max[0] + 1, max[1] + 1);

        QPainter painter(this);

        painter.drawLine(min[0], min[1], max[0], min[1]);
        painter.drawLine(max[0], min[1], max[0], max[1]);
        painter.drawLine(max[0], max[1], min[0], max[1]);
        painter.drawLine(min[0], max[1], min[0], min[1]);

        const BilliardModel::MyCollisionBox::ParticleList & particles = collisionBox->getParticles();

        for (auto it = particles.begin(); it != particles.end(); it++)
        {
            auto pos = it->getPosition();
            double r = model->getRadius();

            painter.drawEllipse(QPointF(pos[0], pos[1]), r, r);
        }

    }
}
