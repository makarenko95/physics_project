#include "application.h"
#include <Views/qtbilliardview.h>
#include <QHBoxLayout>
#include <Control/qtbilliardcontrol.h>

#include <QPalette>

Application::Application(QWidget *parent)
    : QWidget(parent), controller(&model, &view)
{
    QPalette p = palette();
    p.setColor(backgroundRole(), QColor(177, 224, 242));
    setPalette(p);
    QHBoxLayout * layout = new QHBoxLayout;
    layout->addWidget(&view);
    layout->addWidget(&controller);
    setLayout(layout);
}
