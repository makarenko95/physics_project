#include "theory.h"
#include <QPixmap>
#include <QVBoxLayout>

Theory::Theory(QWidget *parent) : QWidget(NULL)
{
    int w = 600;

    page[0].setPixmap(QPixmap("data/theory/0.png"));
    page[1].setPixmap(QPixmap("data/theory/1.png"));
    page[2].setPixmap(QPixmap("data/theory/2.png"));

    QVBoxLayout * layout = new QVBoxLayout;
    QVBoxLayout * pages = new QVBoxLayout;

    for (int i = 0; i < 3; i++)
    {
        page[i].setFixedSize(w, 3.0 / 2 * w);
        page[i].setScaledContents(true);
        pages->addWidget(&page[i]);
    }

    QPalette p(palette());
    p.setColor(backgroundRole(), Qt::white);

    area.setPalette(p);

    QWidget * pages_wrapper = new QWidget;
    pages_wrapper->setLayout(pages);

    area.setWidget(pages_wrapper);

    backButton.setText("Главное меню");
    connect(&backButton, SIGNAL(clicked()), parent, SLOT(SelectMainMenu()));

    layout->addWidget(&area);
    layout->addWidget(&backButton);

    area.setAlignment(Qt::AlignCenter);
    layout->setAlignment(&backButton, Qt::AlignCenter);

    setLayout(layout);
}

