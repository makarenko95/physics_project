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

    QPalette p = palette();
    p.setColor(backgroundRole(), QColor(177, 224, 242));
    setPalette(p);

    QVBoxLayout * left = new QVBoxLayout;
    QVBoxLayout * left_right = new QVBoxLayout;
    QHBoxLayout * plots_and_view = new QHBoxLayout;
    QHBoxLayout * plots = new QHBoxLayout;

    plots_and_view->addWidget(&view);
    plots->addWidget(&av_plot);
    left_right->addWidget(&v_histogram);
    left_right->addWidget(&d_histogram);
    plots->addWidget(&w_plot);
    plots_and_view->addLayout(left_right);

    left->addLayout(plots_and_view);
    left->addLayout(plots);

    v_histogram.setFixedWidth(400);
    av_plot.setFixedHeight(200);

    QHBoxLayout * layout = new QHBoxLayout;
    layout->addLayout(left);
    layout->addWidget(&controller);
    setLayout(layout);
}
