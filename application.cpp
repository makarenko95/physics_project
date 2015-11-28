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

    QPalette p = palette();
    p.setColor(backgroundRole(), QColor(177, 224, 242));
    setPalette(p);

    QVBoxLayout * left = new QVBoxLayout;
    QHBoxLayout * plots = new QHBoxLayout;

    left->addWidget(&view);
    plots->addWidget(&av_plot);
    plots->addWidget(&v_histogram);
    plots->addWidget(&d_histogram);
    left->addLayout(plots);

    av_plot.setFixedHeight(200);

    QHBoxLayout * layout = new QHBoxLayout;
    layout->addLayout(left);
    layout->addWidget(&controller);
    setLayout(layout);
}
