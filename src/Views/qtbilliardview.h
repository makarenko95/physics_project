#ifndef QTBILLIARDVIEW_H
#define QTBILLIARDVIEW_H

#include <QWidget>
#include <QPaintEvent>
#include "billiardview.h"
#include <Geometry/Point.h>
#include <list>
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
        bool clearTrace;
    };

    static const Params defaultParams;

    QtBilliardView(QWidget *parent = 0, const Params & l_params = defaultParams);
    void Update(const BilliardModel & );
    void SetModel(const BilliardModel &);
    void SetParams(const Params &);

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:

private:
    const BilliardModel * model;
    Params params;
    std::list<Point> trace;
};

#endif // QTBILLIARDVIEW_H
