#include "qthistogram.h"
#include <QHBoxLayout>

QtHistogram::QtHistogram(int step, QWidget *parent, bool l_local)
    : QWidget(parent),  max_max_num(0), local(l_local),
      bars(NULL), refresh_step(step), elapsed_steps(0), num_of_iterations(0)
{
    bars = new QCPBars(plot.xAxis, plot.yAxis);
    plot.addPlottable(bars);
    QHBoxLayout * layout = new QHBoxLayout;
    layout->addWidget(&plot);
    setLayout(layout);
    plot.setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    QFont legend_font = QFont("Times", 12, QFont::Normal);
    QFont axis_font = QFont("Times", 11, QFont::Normal);
    QFont axis_number_font = QFont("Times", 10, QFont::Normal);
    QString number_format = "gb";

    plot.legend->setFont(legend_font);
    plot.xAxis->setLabelFont(axis_font);
    plot.yAxis->setLabelFont(axis_font);
    plot.xAxis->setTickLabelFont(axis_number_font);
    plot.xAxis->setNumberFormat(number_format);
    plot.yAxis->setNumberFormat(number_format);
}

void QtHistogram::Reload(const BilliardModel &)
{
    max_max_num = 0;
    elapsed_steps = 0;
    num_of_iterations = 0;
    Initialize();
}

void QtHistogram::SetLocal(bool l_local)
{
    local = l_local;

    if(!local)
    {
        plot.addGraph();
        plot.graph(0)->setPen(QPen(QColor(255,0,0)));
    }
}

void QtHistogram::Update(const BilliardModel & model, double timeStep)
{
    elapsed_steps++;

    if (elapsed_steps == refresh_step)
    {
        elapsed_steps = 0;

        OnUpdate(model, timeStep);
    }
}

void QtHistogram::SetData(QVector<double> & v, int num_of_columns)
{
    bars->clearData();
    QVector<double> hist(num_of_columns, 0);
    QVector<double> key(num_of_columns, 0);

    double step = ToStep(num_of_columns);

    for(int i = 0; i < num_of_columns; ++i)
    {
        key[i] = (i + 0.5) * step;
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

    if(max_num > max_max_num)
    {
        max_max_num = max_num;
        plot.yAxis->setRange(0, max_max_num * 1.25);
    }

    bars->setWidth(step);

    plot.xAxis->setRange(0, step * num_of_columns);
    plot.yAxis->setRangeLower(0);

    bars->setData(key, hist);

    if(!local)
    {
        auto data = plot.graph(0)->data();
        for(int i = 0; i < hist.size(); i++)
        {
            hist[i] = (hist[i] + num_of_iterations * data->take(key[i]).value) / (num_of_iterations + 1);
        }
        plot.graph(0)->setData(key,hist);
    }
    num_of_iterations++;
}

