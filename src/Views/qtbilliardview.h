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
    QtBilliardView(QWidget *parent = 0);
    void Update(const BilliardModel & );
    void SetModel(const BilliardModel &);

protected:
    void paintEvent(QPaintEvent *);
signals:

public slots:

private:
    const BilliardModel * model;
    std::list<Point> trace;
};

#endif // QTBILLIARDVIEW_H
