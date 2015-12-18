#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = 0);

signals:

public slots:

private:
    QLabel project_name;
    QLabel box;
    QPushButton demonstration_button;
    QPushButton theory_button;
    QPushButton authors_button;
};

#endif // MAINMENU_H
