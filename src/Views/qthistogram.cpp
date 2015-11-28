#include "qthistogram.h"
#include <QHBoxLayout>

QtHistogram::QtHistogram(QWidget *parent)
    : QWidget(parent), bars(NULL)
{
    bars = new QCPBars(plot.xAxis, plot.yAxis);
    plot.addPlottable(bars);
    QHBoxLayout * layout = new QHBoxLayout;
    layout->addWidget(&plot);
    setLayout(layout);
}

void QtHistogram::Reload(const BilliardModel &)
{
    Initialize();
}

void QtHistogram::SetData(QVector<double> & v, int num_of_columns)
{
    bars->clearData();
    QVector<double> hist(num_of_columns, 0);
    QVector<double> key(num_of_columns, 0);

    for(int i = 0; i < num_of_columns; ++i)
    {
        key[i] = i + 1;
    }

    double maxValue = 0.0;

    for (auto value : v)
    {
        if (maxValue < value)
        {
            maxValue = value;
        }
    }

    double max_num = 0.0;

    for(auto value : v)
    {
        int idx = std::min(int(value / maxValue * num_of_columns), num_of_columns - 1);
        hist[idx]++;
        if(hist[idx] > max_num)
            max_num = hist[idx];
    }

    plot.xAxis->setRange(0, num_of_columns);
    plot.yAxis->setRange(0, max_num * 1.25);

    bars->setData(key, hist);
}

