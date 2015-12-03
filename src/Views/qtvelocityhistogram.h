#ifndef QTVELOCITYHISTOGRAM_H
#define QTVELOCITYHISTOGRAM_H

#include "qthistogram.h"

class QtVelocityHistogram : public QtHistogram
{
public:
    QtVelocityHistogram();
    void Initialize();
    void OnUpdate(const BilliardModel &, double);
    void Reload(const BilliardModel &);
    double ToStep(int count);

signals:

public slots:

private:
    double v_max;
};

#endif // QTVELOCITYHISTOGRAM_H
