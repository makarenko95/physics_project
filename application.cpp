#include "application.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QPalette>

Application::Application(QWidget *parent)
    : QWidget(parent), demonstration( new Demonstration(this)),
      authors(new Authors(this)),
      main_menu(new MainMenu(this)),
      authors_wrapper(Wrap(authors)),
      main_menu_wrapper(Wrap(main_menu))

{
    setFont(QFont("Times", 16, QFont::Normal));

    setPalette(demonstration->palette());

    widgets.addWidget(main_menu_wrapper);
    widgets.addWidget(demonstration);
    widgets.addWidget(authors_wrapper);

    QVBoxLayout * layout = new QVBoxLayout;

    layout->addWidget(&widgets);

    setLayout(layout);
}

QWidget *Application::Wrap(QWidget * w)
{
    QWidget * widget = new QWidget;

    QVBoxLayout * layout = new QVBoxLayout;

    HeadWidget * head = new HeadWidget;
    BottomWidget * bottom = new BottomWidget;

    layout->addWidget(head);
    layout->addWidget(w);
    layout->addWidget(bottom);

    layout->setAlignment(head, Qt::AlignTop);
    layout->setAlignment(bottom, Qt::AlignBottom);

    widget->setLayout(layout);

    return widget;
}

void Application::SelectAuthors()
{
    widgets.setCurrentWidget(authors_wrapper);
}

void Application::SelectDemonstration()
{
    widgets.setCurrentWidget(demonstration);
}

void Application::SelectMainMenu()
{
    widgets.setCurrentWidget(main_menu_wrapper);
}

HeadWidget::HeadWidget(QWidget *parent)
    : QWidget(parent)
{
    setFont(QFont("Times", 14, QFont::Normal));
    QHBoxLayout * layout = new QHBoxLayout;
    QVBoxLayout * left = new QVBoxLayout;
    QVBoxLayout * right = new QVBoxLayout;

    cmc_logo.setPixmap(QPixmap("data/cmc.png"));
    cmc_logo.setScaledContents(true);
    cmc_logo.setFixedSize(120, 120);

    phys_logo.setPixmap(QPixmap("data/phys.png"));
    phys_logo.setScaledContents(true);
    phys_logo.setFixedSize(120, 120);

    cmc_text.setText("Факультет вычислительной\nматематики и кибернетики");
    phys_text.setText("Физический факультет");
    msu_text.setText("Московский государственный университет\nимени М.В. Ломоносова");

    msu_text.setFont(QFont("Times", 24, QFont::Bold));
    msu_text.setAlignment(Qt::AlignCenter);

    left->addWidget(&cmc_logo);
    left->addWidget(&cmc_text);

    left->setAlignment(&cmc_logo, Qt::AlignCenter);
    left->setAlignment(&cmc_text, Qt::AlignCenter);

    right->addWidget(&phys_logo);
    right->addWidget(&phys_text);

    right->setAlignment(&phys_logo, Qt::AlignCenter);
    right->setAlignment(&phys_text, Qt::AlignCenter);

    layout->addLayout(left);
    layout->addWidget(&msu_text);
    layout->addLayout(right);

    layout->setAlignment(left, Qt::AlignLeft);
    layout->setAlignment(right, Qt::AlignRight);
    layout->setAlignment(&msu_text, Qt::AlignCenter);

    setLayout(layout);

    setFixedHeight(180);
}

BottomWidget::BottomWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout * layout = new QHBoxLayout;

    text.setText("Москва, 2015");

    layout->addWidget(&text);

    layout->setAlignment(&text, Qt::AlignCenter);

    setLayout(layout);

    setFixedHeight(35);
}
