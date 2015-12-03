#ifndef QTDIRECTIONHISTOGRAM_H
#define QTDIRECTIONHISTOGRAM_H

#include "qthistogram.h"
#include "Models/billiardmodel.h"

class BilliardModel;

class QtDirectionHistogram : public QtHistogram
{
public:
    QtDirectionHistogram();
    void Initialize();
    void OnUpdate(const BilliardModel &, double);
    double ToStep(int);

signals:

public slots:
};

#endif // QTDIRECTIONHISTOGRAM_H
