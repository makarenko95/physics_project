#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include "demonstration.h"
#include "authors.h"
#include "mainmenu.h"
#include <QStackedWidget>

class HeadWidget: public QWidget
{
    Q_OBJECT

public:
    HeadWidget(QWidget *parent = 0);

private:
    QLabel cmc_logo;
    QLabel cmc_text;
    QLabel phys_logo;
    QLabel phys_text;
    QLabel msu_text;
};

class BottomWidget: public QWidget
{
    Q_OBJECT

public:
    BottomWidget(QWidget *parent = 0);

private:
    QLabel text;
};

class Application : public QWidget
{
    Q_OBJECT

public:
    Application(QWidget *parent = 0);

private:
    Demonstration * demonstration;
    Authors * authors;
    MainMenu * main_menu;

    QStackedWidget widgets;

    QWidget * authors_wrapper;
    QWidget * main_menu_wrapper;

    QWidget * Wrap(QWidget *);

public slots:
    void SelectAuthors();
    void SelectDemonstration();
    void SelectMainMenu();
};

#endif // APPLICATION_H
