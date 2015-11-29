#ifndef QTWORKPLOT_H
#define QTWORKPLOT_H

#include <Views/qtplot.h>
#include <Models/billiardmodel.h>

class QtWorkPlot : public QtPlot
{
public:
    QtWorkPlot();
    void Initialize();
    void Update(const BilliardModel &, double);
    void Reload(const BilliardModel &);
private:
    double fullWork;
    double lastEnergy;
signals:

public slots:
};

#endif // QTWORKPLOT_H
