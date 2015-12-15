#ifndef QTBILLIARDCONTROL_H
#define QTBILLIARDCONTROL_H

#include <QWidget>
#include <Control/billiardcontrol.h>
#include <Views/qtbilliardview.h>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QLabel>
#include <QCheckBox>
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
    void onPistonResetButtonClick();
    void onDrawTraceStateChange(int);
    void onDrawParticlesStateChange(int);
    void onVisualFxStateChange(int);
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
    void createPistonResetDialog(QGridLayout *);
    void createDrawTraceDialog(QGridLayout *);
    void createDrawParticlesDialog(QGridLayout *);
    void createResetDialog(QGridLayout *);
    void createVisualFxDialog(QGridLayout *);
    void createTimerDialog(QGridLayout *);
    void createBackButton(QGridLayout *);
    void start();
    void stop();
    void Reset();

    QWidget * parent;
    QTimer timer;
    BilliardModel * model;
    QtBilliardView * view;

    bool running;
    bool drawParticles;
    bool drawTrace;
    bool enableVisualFx;

    static const int interval = 20;
};

#endif // QTBILLIARDCONTROL_H
