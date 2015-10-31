#ifndef QTBILLIARDVIEW_H
#define QTBILLIARDVIEW_H

#include <QWidget>
#include <QPaintEvent>
#include "billiardview.h"

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
};

#endif // QTBILLIARDVIEW_H
