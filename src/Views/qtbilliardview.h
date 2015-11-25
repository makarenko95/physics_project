#ifndef QTBILLIARDVIEW_H
#define QTBILLIARDVIEW_H

#include <QWidget>
#include <QPaintEvent>
#include "billiardview.h"
#include <Geometry/Point.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <list>
#include <QRadialGradient>
#include <Geometry/Point.h>

typedef Geometry::Point<double, 2> Point;

class QtBilliardView : public QWidget,
                       public BilliardView
{
    Q_OBJECT
public:

    struct Params
    {
        bool drawParticles;
        bool drawTrace;
        bool enableVisualFx;
    };

    static const Params defaultParams;

    QtBilliardView(QWidget *parent = 0);
    ~QtBilliardView();

    void Update(const BilliardModel & );
    void Reload(const BilliardModel &);
    void EnableVisualFx();
    void DisableVisualFx();
    void ShowParticles();
    void HideParticles();
    void EnableTrace();
    void DisableTrace();

protected:

signals:

public slots:

private:
    int width;
    int height;
    int radius;

    QGraphicsScene scene;
    QGraphicsView view;

    QGraphicsRectItem * walls;
    QGraphicsRectItem * piston;
    std::list<QGraphicsEllipseItem *> particles;
    QGraphicsEllipseItem *observable_particle;
    QGraphicsPixmapItem * trace;

    QPixmap trace_layer;
    QPointF last_position;

    void Destroy();
    void SetWidth(int);
    void SetHeight(int);
    void SetRadius(int);
    void CreateWalls();
    void CreatePiston(int);
    void CreateParticle(int, int);
    void CreateObservableParticle(QGraphicsEllipseItem *);
    void CreateTrace();
    void MakeScene();

    void UpdatePiston(const BilliardModel &);
    void UpdateParticles(const BilliardModel &);
    void UpdateTrace(const BilliardModel &);
    void ClearTrace();

    QRadialGradient getParticleGradient(const QColor &);
};

#endif // QTBILLIARDVIEW_H
