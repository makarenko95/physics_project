#include "mainmenu.h"

#include <QPixmap>
#include <QVBoxLayout>

MainMenu::MainMenu(QWidget *parent) : QWidget(NULL)
{
    int size = 250;

    QVBoxLayout * layout = new QVBoxLayout;

    project_name.setFont(QFont("Times", 22, QFont::Bold));

    project_name.setText("Математический биллиард с движущимся поршнем");
    project_name.setAlignment(Qt::AlignCenter);

    box.setPixmap(QPixmap("data/box.png"));
    box.setFixedSize(size, size);
    box.setScaledContents(true);

    demonstration_button.setText("Демонстрация");
    theory_button.setText("Теория");
    authors_button.setText("Об авторах");

    demonstration_button.setFixedWidth(200);
    theory_button.setFixedWidth(200);
    authors_button.setFixedWidth(200);

    connect(&authors_button, SIGNAL(clicked()), parent, SLOT(SelectAuthors()));
    connect(&demonstration_button, SIGNAL(clicked()), parent, SLOT(SelectDemonstration()));

    layout->addWidget(&project_name);
    layout->addWidget(&box);
    layout->addWidget(&demonstration_button);
    layout->addWidget(&theory_button);
    layout->addWidget(&authors_button);

    layout->setAlignment(&box, Qt::AlignCenter);
    layout->setAlignment(&demonstration_button, Qt::AlignCenter);
    layout->setAlignment(&theory_button, Qt::AlignCenter);
    layout->setAlignment(&authors_button, Qt::AlignCenter);

    setLayout(layout);
}

