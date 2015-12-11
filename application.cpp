#include "application.h"
#include <Views/qtbilliardview.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <Control/qtbilliardcontrol.h>
#include <QSizePolicy>

#include <QPalette>

Application::Application(QWidget *parent)
    : QWidget(parent), controller(&model, &view)
{
    model.AddView(av_plot);
    model.AddView(v_histogram);
    model.AddView(d_histogram);
    model.AddView(w_plot);
    model.AddView(fp_plot);

    QPalette p = palette();
    p.setColor(backgroundRole(), QColor(177, 224, 242));

    QPalette pp = palette();
    pp.setColor(backgroundRole(), QColor(177, 242, 242));

    QPalette ppp = palette();
    ppp.setColor(backgroundRole(), QColor(228, 242, 242));

    QVBoxLayout * left = new QVBoxLayout;
    QScrollArea * plots_scroll = new QScrollArea;
    QHBoxLayout * plots = new QHBoxLayout;

    v_histogram.setFixedSize(400,200);
    d_histogram.setFixedSize(400,200);
    av_plot.setFixedSize(400,200);
    w_plot.setFixedSize(400,200);
    fp_plot.setFixedSize(400,200);
    plots_scroll->setMinimumWidth(420);

    plots->addWidget(&av_plot);
    plots->addWidget(&w_plot);
    plots->addWidget(&fp_plot);
    plots->addWidget(&v_histogram);
    plots->addWidget(&d_histogram);

    QWidget * plots_wrapper = new QWidget;
    plots_wrapper->setLayout(plots);

    plots_scroll->setWidgetResizable(true);
    plots_scroll->setWidget(plots_wrapper);
    plots_scroll->setFixedHeight(240);

    setPalette(p);
    plots_scroll->setPalette(ppp);

    left->addWidget(&view);
    left->addWidget(plots_scroll);

    QHBoxLayout * layout = new QHBoxLayout;
    layout->addLayout(left);
    layout->addWidget(&controller);
    setLayout(layout);
}
