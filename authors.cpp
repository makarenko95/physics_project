#include "authors.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>

Authors::Authors(QWidget *parent)
    : QWidget(NULL)
{
    int size = 80;

    QVBoxLayout * layout = new QVBoxLayout;
    QHBoxLayout * students = new QHBoxLayout;
    QVBoxLayout * left = new QVBoxLayout;
    QVBoxLayout * right = new QVBoxLayout;

    vova_photo.setPixmap(QPixmap("data/vova.png"));
    vova_photo.setScaledContents(true);
    vova_photo.setFixedSize(3 * size, 4 * size);
    vova_text.setText("Макаренко Владимир");

    ruslan_photo.setPixmap(QPixmap("data/ruslan.png"));
    ruslan_photo.setScaledContents(true);
    ruslan_photo.setFixedSize(3 * size, 4 * size);
    ruslan_text.setText("Габдуллин Руслан");
    backButton.setText("Главное меню");

    boss_text.setText("Руководитель: Шутова Ольга Анатольевна");
    boss_text.setFont(QFont("Times", 18, QFont::Bold));

    left->addWidget(&vova_photo);
    left->addWidget(&vova_text);

    right->addWidget(&ruslan_photo);
    right->addWidget(&ruslan_text);

    students->addLayout(left);
    students->addLayout(right);

    layout->addLayout(students);
    layout->addWidget(&boss_text);
    layout->addWidget(&backButton);

    students->setAlignment(left, Qt::AlignRight);
    students->setAlignment(right, Qt::AlignLeft);
    left->setAlignment(&vova_text, Qt::AlignCenter);
    right->setAlignment(&ruslan_text, Qt::AlignCenter);
    layout->setAlignment(students, Qt::AlignCenter);
    layout->setAlignment(&boss_text,Qt::AlignCenter);
    layout->setAlignment(&backButton, Qt::AlignCenter);

    connect(&backButton, SIGNAL(clicked()), parent, SLOT(SelectMainMenu()));

    setLayout(layout);
}
