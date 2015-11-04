#include "qtbilliardcontrol.h"
#include <QApplication>

QtBilliardControl::QtBilliardControl(QWidget *parent):
    QWidget(parent)
{
    setFixedSize(80,80);
    QPushButton *reload = new QPushButton(tr("Reload"), this);
    reload->setGeometry(1,1,78,78);
    reload->setFont(QFont("Times", 14, QFont::Bold));

    connect(reload, SIGNAL(clicked()), parent, SLOT(buttonReloadPressed()));
}
