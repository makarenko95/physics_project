#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include <CollisionBox.h>

class Application : public QWidget
{
    Q_OBJECT

public:
    Application(QWidget *parent = 0);
    ~Application();
};

#endif // APPLICATION_H
