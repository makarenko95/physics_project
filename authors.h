#ifndef AUTHORS_H
#define AUTHORS_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class Authors : public QWidget
{
    Q_OBJECT
public:
    explicit Authors(QWidget *parent = 0);

signals:

public slots:

private:
    QLabel vova_photo;
    QLabel ruslan_photo;
    QLabel vova_text;
    QLabel ruslan_text;
    QLabel boss_text;
    QPushButton backButton;
};

#endif // AUTHORS_H
