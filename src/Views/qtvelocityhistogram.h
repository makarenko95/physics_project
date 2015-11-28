#ifndef QTVELOCITYHISTOGRAM_H
#define QTVELOCITYHISTOGRAM_H

#include "qthistogram.h"

class QtVelocityHistogram : public QtHistogram
{
public:
    QtVelocityHistogram();
    void Initialize();
    void Update(const BilliardModel &, double);

signals:

public slots:
};

#endif // QTVELOCITYHISTOGRAM_H
