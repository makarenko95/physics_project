#include "qtbilliardview.h"
#include <Models/billiardmodel.h>

#include <QPainter>

QtBilliardView::QtBilliardView(QWidget *parent)
    : QWidget(parent), model(NULL), trace()
{
    setFixedSize(800, 640);
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
        ViewerSettings settings = model->GetViewerSettings();
        const BilliardModel::MyCollisionBox * collisionBox = model->getCollisionBox();
        const BilliardModel::MyCollisionBox::Box &boundaries = collisionBox->getBoundaries();

        auto min = boundaries.min;
        auto max = boundaries.max;


        QPainter painter(this);

        painter.drawLine(min[0], min[1], max[0], min[1]);
        painter.drawLine(max[0], min[1], max[0], max[1]);
        painter.drawLine(max[0], max[1], min[0], max[1]);
        painter.drawLine(min[0], max[1], min[0], min[1]);

        const BilliardModel::MyCollisionBox::ParticleList & particles = collisionBox->getParticles();


        auto it = particles.begin();

        {
            auto pos = it->getPosition();
            trace.push_back(pos);
            while(trace.size()>2000000)
                trace.pop_front();
            double r = model->getRadius();

            painter.setPen(Qt::red);
            painter.drawEllipse(QPointF(pos[0], pos[1]), r, r);
        }

        if(settings.drawParticles){
            painter.setPen(Qt::black);
            it++;

            for (; it != particles.end(); it++)
            {
                auto pos = it->getPosition();
                double r = model->getRadius();

                painter.drawEllipse(QPointF(pos[0], pos[1]), r, r);
            }
        }
        painter.setPen(Qt::blue);
        if(settings.drawTrace)
        {
            auto last_pos=*(trace.begin());
            for(auto it = trace.begin();it!=trace.end();it++){
                auto current_pos = *it;
                painter.drawLine(current_pos[0],current_pos[1],last_pos[0],last_pos[1]);
                last_pos = current_pos;
            }
        }
        else
            if(trace.size()>0)
                trace.clear();
        painter.setPen(Qt::red);

        int pistonPos = collisionBox->getPistonPos();

        painter.drawLine(pistonPos, 0, pistonPos, max[1]);

    }
}
