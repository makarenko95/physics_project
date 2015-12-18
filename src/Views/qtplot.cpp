#include "qtplot.h"
#include <QHBoxLayout>

QtPlot::QtPlot(QWidget *parent)
    : QWidget(parent), xRange(0), yRange(0)
{
    plot.addGraph();
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

void QtPlot::Reload(const BilliardModel &)
{
    plot.clearGraphs();
    plot.addGraph();
    Initialize();

    x = 0;
}

void QtPlot::AddData(double y, double timeStep)
{
    double offset = ToOffset(timeStep);

    while (x + offset > xRange)
    {
        ExpandX();
    }

    while (y > yRange)
    {
        ExpandY();
    }

    plot.graph(0)->addData(x + offset, y);

    x += offset;
}

void QtPlot::ExpandX()
{
    xRange *= 1.25;
    plot.xAxis->setRange(0, xRange);
}

void QtPlot::ExpandY()
{
    yRange *= 1.25;
    plot.yAxis->setRange(0, yRange);
}
