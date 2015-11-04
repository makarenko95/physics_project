#ifndef QTBILLIARDCONTROL_H
#define QTBILLIARDCONTROL_H

#include <QWidget>
#include <Control/billiardcontrol.h>
#include <QPushButton>

class QtBilliardControl : public BilliardControl, public QWidget
{
public:
    QtBilliardControl(QWidget *parent = 0);
    void Update(const BilliardModelParams & new_params);
signals:

public slots:
};

#endif // QTBILLIARDCONTROL_H
