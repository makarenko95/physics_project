#include "qtbilliardcontrol.h"
#include <QApplication>

void QtBilliardControl::createRadiusDialog(QGridLayout * layout)
{
    QLabel *labelRadius = new QLabel("Радиус частицы:", this);
    labelRadius->setFont(QFont("Times", 14, QFont::Normal));

    layout->addWidget(labelRadius, 0, 0);

    QDoubleSpinBox *radiusSpinBox = new QDoubleSpinBox(this);
    radiusSpinBox->setMaximum(50.0);
    radiusSpinBox->setMinimum(1.0);
    radiusSpinBox->setValue(GetParams().radius);
    radiusSpinBox->setDecimals(1);
    radiusSpinBox->setSingleStep(0.5);
    radiusSpinBox->setFont(QFont("Times", 14, QFont::Normal));

    layout->addWidget(radiusSpinBox, 0, 1);

    connect(radiusSpinBox, SIGNAL(valueChanged(double)), this, SLOT(onRadiusChange(double)));
}

void QtBilliardControl::createSizeDialog(QGridLayout * layout)
{
    QLabel *labelSize = new QLabel("Размер сосуда:", this);
    labelSize->setFont(QFont("Times", 14, QFont::Normal));

    layout->addWidget(labelSize, 1, 0);

    QSpinBox *sizeSpinBox = new QSpinBox(this);
    sizeSpinBox->setMaximum(700);
    sizeSpinBox->setMinimum(100);
    sizeSpinBox->setSingleStep(10);
    sizeSpinBox->setValue(GetParams().size);
    sizeSpinBox->setFont(QFont("Times", 14, QFont::Normal));

    layout->addWidget(sizeSpinBox, 1, 1);

    connect(sizeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onSizeChange(int)));
}

void QtBilliardControl::createParticleNumDialog(QGridLayout * layout)
{
    QLabel *labelParticleNum = new QLabel("Число частиц:",this);
    labelParticleNum->setFont(QFont("Times", 14, QFont::Normal));

    layout->addWidget(labelParticleNum, 2, 0);

    QSpinBox *particleNumSpinBox = new QSpinBox(this);
    particleNumSpinBox->setMaximum(20000);
    particleNumSpinBox->setMinimum(0);
    particleNumSpinBox->setSingleStep(10);
    particleNumSpinBox->setValue(GetParams().particle_max_count);
    particleNumSpinBox->setFont(QFont("Times", 14, QFont::Normal));

    layout->addWidget(particleNumSpinBox, 2, 1);

    connect(particleNumSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onParticleNumChange(int)));
}

void QtBilliardControl::createMaxParticleVelocityDialog(QGridLayout * layout)
{
    QLabel *labelMaxParticleVelocity = new QLabel("Макс. скорость:", this);
    labelMaxParticleVelocity->setFont(QFont("Times", 14, QFont::Normal));

    layout->addWidget(labelMaxParticleVelocity, 3, 0);

    QDoubleSpinBox *maxParticleVelocitySpinBox = new QDoubleSpinBox(this);
    maxParticleVelocitySpinBox->setMaximum(15000000.0);
    maxParticleVelocitySpinBox->setMinimum(0.0);
    maxParticleVelocitySpinBox->setValue(this->GetParams().max_particle_velocity);
    maxParticleVelocitySpinBox->setDecimals(2);
    maxParticleVelocitySpinBox->setSingleStep(2.5);
    maxParticleVelocitySpinBox->setFont(QFont("Times", 14, QFont::Normal));

    layout->addWidget(maxParticleVelocitySpinBox, 3, 1);

    connect(maxParticleVelocitySpinBox, SIGNAL(valueChanged(double)), this, SLOT(onParticleVelocityChange(double)));
}

void QtBilliardControl::createPistonMaxPosDialog(QGridLayout *layout)
{
    QLabel *labelPistonMaxPath = new QLabel("Амплитуда поршня:", this);
    labelPistonMaxPath->setFont(QFont("Times", 14, QFont::Normal));

    layout->addWidget(labelPistonMaxPath, 4, 0);

    QDoubleSpinBox *pistonMaxPathSpinBox = new QDoubleSpinBox(this);
    pistonMaxPathSpinBox->setMaximum(400);
    pistonMaxPathSpinBox->setMinimum(1.0);
    pistonMaxPathSpinBox->setValue(GetParams().piston_end_position);
    pistonMaxPathSpinBox->setDecimals(2);
    pistonMaxPathSpinBox->setSingleStep(1.0);
    pistonMaxPathSpinBox->setFont(QFont("Times", 14, QFont::Normal));

    layout->addWidget(pistonMaxPathSpinBox, 4, 1);

    connect(pistonMaxPathSpinBox, SIGNAL(valueChanged(double)), this, SLOT(onPistonMaxPosChange(double)));
}

void QtBilliardControl::createPistonVelocityDialog(QGridLayout * layout)
{
    QLabel *labelPistonVelocity = new QLabel("Скорость поршня:",this);
    labelPistonVelocity->setFont(QFont("Times", 14, QFont::Normal));

    layout->addWidget(labelPistonVelocity, 5, 0);

    QDoubleSpinBox *pistonVelocitySpinBox = new QDoubleSpinBox(this);
    pistonVelocitySpinBox->setMaximum(3000.0);
    pistonVelocitySpinBox->setMinimum(0.0);
    pistonVelocitySpinBox->setValue(GetParams().piston_velocity);
    pistonVelocitySpinBox->setDecimals(2);
    pistonVelocitySpinBox->setSingleStep(2.5);
    pistonVelocitySpinBox->setFont(QFont("Times", 14, QFont::Normal));

    layout->addWidget(pistonVelocitySpinBox, 5, 1);

    connect(pistonVelocitySpinBox, SIGNAL(valueChanged(double)), this, SLOT(onPistonVelocityChange(double)));
}

void QtBilliardControl::createPistonResetDialog(QGridLayout * layout)
{    QPushButton *pistonButton = new QPushButton("Вкл./Выкл. поршень", this);
     pistonButton->setFont(QFont("Times", 14, QFont::Normal));

     layout->addWidget(pistonButton, 6, 0);

     connect(pistonButton, SIGNAL(clicked()), this, SLOT(onPistonResetButtonClick()));
}

void QtBilliardControl::createDrawTraceDialog(QGridLayout * layout)
{
    QLabel *drawTraceLabel = new QLabel("Отрисовка траектории:", this);
    drawTraceLabel->setFont(QFont("Times", 14, QFont::Normal));

    layout->addWidget(drawTraceLabel, 7, 0);

    QCheckBox * drawTraceCheckBox = new QCheckBox;
    drawTraceCheckBox->setChecked(drawTrace);

    layout->addWidget(drawTraceCheckBox, 7, 1);

    connect(drawTraceCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onDrawTraceStateChange(int)));
}

void QtBilliardControl::createDrawParticlesDialog(QGridLayout * layout)
{
    QLabel *drawParticlesLabel = new QLabel("Отрисовка частиц:", this);
    drawParticlesLabel->setFont(QFont("Times", 14, QFont::Normal));

    layout->addWidget(drawParticlesLabel, 8, 0);

    QCheckBox * drawParticlesCheckBox = new QCheckBox;
    drawParticlesCheckBox->setChecked(drawParticles);

    layout->addWidget(drawParticlesCheckBox, 8, 1);

    connect(drawParticlesCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onDrawParticlesStateChange(int)));
}

void QtBilliardControl::createVisualFxDialog(QGridLayout * layout)
{
    QLabel *visualFxLabel = new QLabel("Вкл. оформление:", this);
    visualFxLabel->setFont(QFont("Times", 14, QFont::Normal));

    layout->addWidget(visualFxLabel, 9, 0);

    QCheckBox * visualFxCheckBox = new QCheckBox;
    visualFxCheckBox->setChecked(enableVisualFx);

    layout->addWidget(visualFxCheckBox, 9, 1);

    connect(visualFxCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onVisualFxStateChange(int)));
}

void QtBilliardControl::createResetDialog(QGridLayout * layout)
{
    QPushButton *reloadButton = new QPushButton("Начать заново", this);
    reloadButton->setFont(QFont("Times", 14, QFont::Normal));
    layout->addWidget(reloadButton, 10, 0);

    connect(reloadButton, SIGNAL(clicked()), this, SLOT(onResetButtonClick()));
}

void QtBilliardControl::createTimerDialog(QGridLayout * layout)
{
    QPushButton * timerButton = new QPushButton("Пауза/Продолжить", this);
    timerButton->setFont(QFont("Times", 14, QFont::Normal));
    layout->addWidget(timerButton, 11, 0);

    connect(timerButton, SIGNAL(clicked()), this, SLOT(onTimerButtonClick()));
}

void QtBilliardControl::createBackButton(QGridLayout * layout)
{
    QPushButton * backButton = new QPushButton("Главное меню", this);
    backButton->setFont(QFont("Times", 14, QFont::Normal));
    layout->addWidget(backButton, 12, 0);

    connect(backButton, SIGNAL(clicked()), parent, SLOT(SelectMainMenu()));
}

void QtBilliardControl::start()
{
    timer.start(interval);
}

void QtBilliardControl::stop()
{
    timer.stop();
}

void QtBilliardControl::Reset()
{
    stop();

    model->Reload(GetParams());

    if (drawParticles)
    {
        view->ShowParticles();
    }
    else
    {
        view->HideParticles();
    }

    if (drawTrace)
    {
        view->EnableTrace();
    }
    else
    {
        view->DisableTrace();
    }

    if (enableVisualFx)
    {
        view->EnableVisualFx();
    }
    else
    {
        view->DisableVisualFx();
    }

    running = true;

    start();
}

QtBilliardControl::QtBilliardControl(BilliardModel * m, QtBilliardView * v, QWidget *l_parent)
    : QWidget(NULL), parent(l_parent), model(m), view(v), running(false),
      drawParticles(QtBilliardView::defaultParams.drawParticles),
      drawTrace(QtBilliardView::defaultParams.drawTrace),
      enableVisualFx(QtBilliardView::defaultParams.enableVisualFx)
{
    QGridLayout * layout = new QGridLayout;

    createRadiusDialog(layout);
    createSizeDialog(layout);
    createParticleNumDialog(layout);
    createMaxParticleVelocityDialog(layout);
    createPistonMaxPosDialog(layout);
    createPistonVelocityDialog(layout);
    createPistonResetDialog(layout);
    createDrawTraceDialog(layout);
    createDrawParticlesDialog(layout);
    createVisualFxDialog(layout);
    createResetDialog(layout);
    createTimerDialog(layout);
    createBackButton(layout);

    setLayout(layout);

    connect(&timer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    model->AddView(*view);
}

void QtBilliardControl::onRadiusChange(double r)
{
    SetParticleRadius(r);
}

void QtBilliardControl::onSizeChange(int size)
{
    SetBoxSize(size);
}

void QtBilliardControl::onParticleNumChange(int num)
{
    SetMaxParticleNumber(num);
}

void QtBilliardControl::onParticleVelocityChange(double vel)
{
    SetMaxParticleVelocity(vel);
}

void QtBilliardControl::onPistonMaxPosChange(double pos)
{
    SetPistonEndPosition(pos);
}

void QtBilliardControl::onPistonVelocityChange(double vel)
{
    SetPistonVelocity(vel);
}

void QtBilliardControl::onPistonResetButtonClick()
{
    model->ResetPiston(GetParams().piston_velocity);
}

void QtBilliardControl::onDrawTraceStateChange(int state)
{
    if (running)
    {
        if (state)
        {
            view->EnableTrace();
        }
        else
        {
            view->DisableTrace();
        }
    }
    drawTrace = state;
}

void QtBilliardControl::onDrawParticlesStateChange(int state)
{
    if (running)
    {
        if (state)
        {
            view->ShowParticles();
        }
        else
        {
            view->HideParticles();
        }
    }
    drawParticles = state;
}

void QtBilliardControl::onVisualFxStateChange(int state)
{
    if (running)
    {
        if (state)
        {
            view->EnableVisualFx();
        }
        else
        {
            view->DisableVisualFx();
        }
    }

    enableVisualFx = state;
}

void QtBilliardControl::onResetButtonClick()
{
    Reset();
}

void QtBilliardControl::onTimerButtonClick()
{
    if (running)
    {
        if (timer.isActive())
        {
            stop();
        }
        else
        {
            start();
        }
    }
    else
    {
        Reset();
    }
}

void QtBilliardControl::onTimeout()
{
    model->update(interval * 1.0 / 1000);
}
