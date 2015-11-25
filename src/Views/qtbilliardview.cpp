#include "qtbilliardview.h"
#include <Models/billiardmodel.h>

#include <QPainter>
#include <QHBoxLayout>

const QtBilliardView::Params QtBilliardView::defaultParams = {true, false, false};

QtBilliardView::QtBilliardView(QWidget *parent)
    : QWidget(parent), width(0), height(0), radius(0), view(&scene),
      walls(NULL), piston(NULL), observable_particle(NULL),
      trace(NULL)
{
    view.setRenderHint(QPainter::Antialiasing);

    QHBoxLayout * layout = new QHBoxLayout;
    layout->addWidget(&view);
    setLayout(layout);
}

QtBilliardView::~QtBilliardView()
{
    Destroy();
}

void QtBilliardView::Update(const BilliardModel & model)
{
    UpdatePiston(model);
    UpdateParticles(model);
    UpdateTrace(model);
    scene.update();
}

void QtBilliardView::Reload(const BilliardModel & model)
{
    Destroy();

    auto collisionBox = model.getCollisionBox();
    auto boundaries = collisionBox->getBoundaries();
    auto & m_particles = collisionBox->getParticles();

    auto max = boundaries.max;

    SetWidth(max[0]);
    SetHeight(max[1]);
    SetRadius(model.getRadius());

    CreateWalls();
    CreatePiston(collisionBox->getPistonPos());

    for (auto &m_particle : m_particles)
    {
        auto pos = m_particle.getPosition();

        CreateParticle(pos[0], pos[1]);
    }

    CreateObservableParticle(*(particles.begin()));

    last_position = observable_particle->pos();

    CreateTrace();
    MakeScene();
}

void QtBilliardView::Destroy()
{
    delete piston;
    delete walls;
    delete trace;

    for (auto & particle : particles)
    {
        delete particle;
    }

    particles.clear();
    scene.clear();

    piston = NULL;
    walls = NULL;
    observable_particle = NULL;
    trace = NULL;
    width = height = radius = 0;
}

void QtBilliardView::SetWidth(int w)
{
    width = w;
}

void QtBilliardView::SetHeight(int h)
{
    height = h;
}

void QtBilliardView::SetRadius(int r)
{
    radius = r;
}

void QtBilliardView::CreateWalls()
{
    walls = new QGraphicsRectItem(0, 0, width, height);
}

void QtBilliardView::CreatePiston(int x)
{
    piston = new QGraphicsRectItem(0, 0, x, height);
}

void QtBilliardView::CreateParticle(int x, int y)
{
    QGraphicsEllipseItem *particle = new QGraphicsEllipseItem(0, 0, 2 * radius, 2 * radius);
    particle->setPos(x - radius, y - radius);
    particles.push_back(particle);
}

void QtBilliardView::CreateObservableParticle(QGraphicsEllipseItem * particle)
{
    observable_particle = particle;
}

void QtBilliardView::CreateTrace()
{
    trace_layer = QPixmap(width, height);
    trace = new QGraphicsPixmapItem;
}

void QtBilliardView::MakeScene()
{
    scene.addItem(trace);
    scene.addItem(walls);
    scene.addItem(piston);

    for (auto & particle : particles)
    {
        scene.addItem(particle);
    }
}

void QtBilliardView::UpdatePiston(const BilliardModel & model)
{
    auto collisionBox = model.getCollisionBox();
    int x = collisionBox->getPistonPos();

    piston->setRect(0, 0, x, height);
}

void QtBilliardView::UpdateParticles(const BilliardModel & model)
{
    auto collisionBox = model.getCollisionBox();
    auto & m_particles = collisionBox->getParticles();

    auto it = particles.begin();

    for (auto m_it = m_particles.begin(); m_it != m_particles.end(); m_it++)
    {
        auto pos = m_it->getPosition();

        (*it)->setPos(pos[0] - radius, pos[1] - radius);

        it++;
    }
}

void QtBilliardView::UpdateTrace(const BilliardModel & model)
{
    if (trace->isVisible())
    {
        auto collisionBox = model.getCollisionBox();
        auto & track = collisionBox->getTrack();

        QPainter painter(&trace_layer);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::blue);

        //QPointF current_pos = observable_particle->pos();

        //painter.drawLine(QPointF(last_position.x() + radius, last_position.y() + radius),
        //    QPointF(current_pos.x() + radius, current_pos.y() + radius));

        for (int i = 0; i < (int)track.size() - 1; i++)
        {
            painter.drawLine(QPointF(track[i][0], track[i][1]),
                QPointF(track[i + 1][0], track[i + 1][1]));
        }

        trace->setPixmap(trace_layer);
        //last_position = current_pos;
    }
}

void QtBilliardView::ClearTrace()
{
    QPainter painter(&trace_layer);
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(0, 0, width, height);
}

void QtBilliardView::EnableVisualFx()
{
    piston->setBrush(QBrush(QColor(163, 163, 209)));
    piston->setPen(Qt::NoPen);

    for (auto & particle : particles)
    {
        particle->setBrush(QBrush(getParticleGradient(Qt::green)));
        particle->setPen(Qt::NoPen);
    }

    observable_particle->setBrush(QBrush(getParticleGradient(Qt::red)));
    observable_particle->setPen(Qt::NoPen);
}

void QtBilliardView::DisableVisualFx()
{
    piston->setBrush(Qt::NoBrush);
    piston->setPen(QPen(Qt::black));

    for (auto & particle : particles)
    {
        particle->setBrush(Qt::NoBrush);
        particle->setPen(QPen(Qt::black));
    }

    observable_particle->setBrush(Qt::NoBrush);
    observable_particle->setPen(QPen(Qt::red));
}

void QtBilliardView::ShowParticles()
{
    for (auto & particle : particles)
    {
        particle->show();
    }
}

void QtBilliardView::HideParticles()
{
    for (auto & particle : particles)
    {
        particle->hide();
    }

    observable_particle->show();
}

void QtBilliardView::EnableTrace()
{
    ClearTrace();
    trace->setPixmap(trace_layer);
    trace->show();
    last_position = observable_particle->pos();
}

void QtBilliardView::DisableTrace()
{
    trace->hide();
}

QRadialGradient QtBilliardView::getParticleGradient(const QColor & color)
{
    QRadialGradient gradient(radius / 1.5, radius / 1.5, radius / 1.5);
    gradient.setColorAt(1, color);
    gradient.setColorAt(0, Qt::white);

    return gradient;
}
