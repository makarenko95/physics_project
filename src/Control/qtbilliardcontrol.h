#ifndef QTBILLIARDCONTROL_H
#define QTBILLIARDCONTROL_H

#include <QWidget>
#include <Control/billiardcontrol.h>
#include <Views/qtbilliardview.h>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QLabel>
#include <QGridLayout>
#include <QTimer>

class QtBilliardControl : public QWidget, public BilliardControl
{
    Q_OBJECT

public:
    QtBilliardControl(BilliardModel *, QtBilliardView *, QWidget *parent = 0);

signals:

public slots:
    void onRadiusChange(double);
    void onSizeChange(int);
    void onParticleNumChange(int);
    void onParticleVelocityChange(double);
    void onPistonMaxPosChange(double);
    void onPistonVelocityChange(double);
    void onDrawTraceButtonClick();
    void onDrawParticlesButtonClick();
    void onResetButtonClick();
    void onTimerButtonClick();
    void onTimeout();

private:
    void createRadiusDialog(QGridLayout *);
    void createSizeDialog(QGridLayout *);
    void createParticleNumDialog(QGridLayout *);
    void createMaxParticleVelocityDialog(QGridLayout *);
    void createPistonMaxPosDialog(QGridLayout *);
    void createPistonVelocityDialog(QGridLayout *);
    void createDrawDialog(QGridLayout *);
    void createResetDialog(QGridLayout *);
    void createTimerDialog(QGridLayout *);
    void start();
    void stop();

    QtBilliardView::Params viewParams;

    QTimer timer;
    BilliardModel * model;
    QtBilliardView * view;

    static const int interval = 5;
};

#endif // QTBILLIARDCONTROL_H
