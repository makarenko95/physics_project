#ifndef THEORY_H
#define THEORY_H

#include <QWidget>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>

class Theory : public QWidget
{
    Q_OBJECT
public:
    explicit Theory(QWidget *parent = 0);

signals:

public slots:

private:
    QScrollArea area;
    QLabel page[3];
    QPushButton backButton;
};

#endif // THEORY_H
