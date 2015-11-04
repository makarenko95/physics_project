#include "qtbilliardcontrol.h"
#include <QApplication>
#include <QPalette>
void QtBilliardControl::changeName()
{
    stopTimer->setText("Start");
}

QtBilliardControl::QtBilliardControl(QWidget *parent):
    QWidget(parent)
{
    QPalette p;
    QColor c;
    c.setRgb(255,255,255);
    p.setColor(backgroundRole(),c);
    setPalette(p);
    const int emptyspace=1;
    const int item_height = 30;
    const int width = 200;
    const int height = 640;
    const int label_width = 100;
    setFixedSize(width,height);
    int line_number = 0;
    //Radius
    QLabel *label_radius = new QLabel("Radius",this);
    label_radius->setGeometry(0,line_number*item_height+emptyspace,label_width,item_height-emptyspace);
    label_radius->setFont(QFont("Times", 14, QFont::Normal));
    QDoubleSpinBox *radius = new QDoubleSpinBox(this);
    radius->setMaximum(20.0);
    radius->setMinimum(1.0);
    radius->setValue(this->GetParams().radius);
    radius->setDecimals(1);
    radius->setSingleStep(0.5);
    radius->setGeometry(label_width,line_number*item_height+emptyspace,width-label_width,item_height-emptyspace);
    radius->setFont(QFont("Times", 14, QFont::Normal));
    connect(radius,SIGNAL(valueChanged(double)),parent,SLOT(radiusChanged(double)));
    line_number++;
    //size
    QLabel *label_size = new QLabel("Size",this);
    label_size->setGeometry(0,line_number*item_height+emptyspace,label_width,item_height-emptyspace);
    label_size->setFont(QFont("Times", 14, QFont::Normal));
    QSpinBox *size = new QSpinBox(this);
    size->setMaximum(600);
    size->setMinimum(300);
    size->setSingleStep(10);
    size->setValue(this->GetParams().size);
    size->setGeometry(label_width,line_number*item_height+emptyspace,width-label_width,item_height-emptyspace);
    size->setFont(QFont("Times", 14, QFont::Normal));
    connect(size,SIGNAL(valueChanged(int)),parent,SLOT(sizeChanged(int)));
    line_number++;
    //particle_num
    QLabel *label_particle_num = new QLabel("Particle Num",this);
    label_particle_num->setGeometry(0,line_number*item_height+emptyspace,label_width,item_height-emptyspace);
    label_particle_num->setFont(QFont("Times", 14, QFont::Normal));
    QSpinBox *particle_num = new QSpinBox(this);
    particle_num->setMaximum(5000);
    particle_num->setMinimum(0);
    particle_num->setSingleStep(10);
    particle_num->setValue(this->GetParams().particle_max_count);
    particle_num->setGeometry(label_width,line_number*item_height+emptyspace,width-label_width,item_height-emptyspace);
    particle_num->setFont(QFont("Times", 14, QFont::Normal));
    connect(particle_num,SIGNAL(valueChanged(int)),parent,SLOT(particlenumChanged(int)));
    line_number++;
    //max_particle_velocity
    QLabel *label_max_particle_velocity = new QLabel("Max Vel",this);
    label_max_particle_velocity->setGeometry(0,line_number*item_height+emptyspace,label_width,item_height-emptyspace);
    label_max_particle_velocity->setFont(QFont("Times", 14, QFont::Normal));
    QDoubleSpinBox *max_particle_velocity = new QDoubleSpinBox(this);
    max_particle_velocity->setMaximum(3000.0);
    max_particle_velocity->setMinimum(0.0);
    max_particle_velocity->setValue(this->GetParams().max_particle_velocity);
    max_particle_velocity->setDecimals(2);
    max_particle_velocity->setSingleStep(2.5);
    max_particle_velocity->setGeometry(label_width,line_number*item_height+emptyspace,width-label_width,item_height-emptyspace);
    max_particle_velocity->setFont(QFont("Times", 14, QFont::Normal));
    connect(max_particle_velocity,SIGNAL(valueChanged(double)),parent,SLOT(particleVelocityChanged(double)));
    line_number++;
    //piston_max_path
    QLabel *label_piston_max_path = new QLabel("Piston Path",this);
    label_piston_max_path->setGeometry(0,line_number*item_height+emptyspace,label_width,item_height-emptyspace);
    label_piston_max_path->setFont(QFont("Times", 14, QFont::Normal));
    QDoubleSpinBox *piston_max_path = new QDoubleSpinBox(this);
    {
        BilliardModelParams p = this->GetParams();
        double max_piston_path = fmax(p.size/2,p.size-30*p.radius*p.radius*p.particle_max_count/p.size);
        piston_max_path->setMaximum(max_piston_path);
    }
    piston_max_path->setMinimum(0.0);
    piston_max_path->setValue(this->GetParams().piston_end_position);
    piston_max_path->setDecimals(2);
    piston_max_path->setSingleStep(1.0);
    piston_max_path->setGeometry(label_width,line_number*item_height+emptyspace,width-label_width,item_height-emptyspace);
    piston_max_path->setFont(QFont("Times", 14, QFont::Normal));
    connect(piston_max_path,SIGNAL(valueChanged(double)),parent,SLOT(pistonPathChanged(double)));
    line_number++;
    //piston_velocity
    QLabel *label_piston_velocity = new QLabel("Piston Vel",this);
    label_piston_velocity->setGeometry(0,line_number*item_height+emptyspace,label_width,item_height-emptyspace);
    label_piston_velocity->setFont(QFont("Times", 14, QFont::Normal));
    QDoubleSpinBox *piston_velocity = new QDoubleSpinBox(this);
    piston_velocity->setMaximum(1200.0);
    piston_velocity->setMinimum(0.0);
    piston_velocity->setValue(this->GetParams().max_particle_velocity);
    piston_velocity->setDecimals(2);
    piston_velocity->setSingleStep(2.5);
    piston_velocity->setGeometry(label_width,line_number*item_height+emptyspace,width-label_width,item_height-emptyspace);
    piston_velocity->setFont(QFont("Times", 14, QFont::Normal));
    connect(piston_velocity,SIGNAL(valueChanged(double)),parent,SLOT(pistonVelocityChanged(double)));
    line_number++;
    //Button DRAWTRACE
    QPushButton *draw_trace = new QPushButton("Draw Trace", this);
    draw_trace->setGeometry(0,line_number*item_height+emptyspace,width,item_height-emptyspace);
    draw_trace->setFont(QFont("Times", 14, QFont::Normal));
    connect(draw_trace, SIGNAL(clicked()), parent, SLOT(changeViewerSettings_trace()));
    line_number++;
    //Button DRAWPRATICLES
    QPushButton *draw_particles = new QPushButton("Draw Particles", this);
    draw_particles->setGeometry(0,line_number*item_height+emptyspace,width,item_height-emptyspace);
    draw_particles->setFont(QFont("Times", 14, QFont::Normal));
    connect(draw_particles, SIGNAL(clicked()), parent, SLOT(changeViewerSettings_particles()));
    line_number++;
    //Button RELOAD
    QPushButton *reload = new QPushButton("Reload", this);
    reload->setGeometry(0,line_number*item_height+emptyspace,width/2-emptyspace,item_height-emptyspace);
    reload->setFont(QFont("Times", 14, QFont::Normal));
    connect(reload, SIGNAL(clicked()), parent, SLOT(buttonReloadPressed()));
    //Button TIMER
    stopTimer = new QPushButton("Timer", this);
    stopTimer->setGeometry(width/2+emptyspace,line_number*item_height+emptyspace,width/2-emptyspace,item_height-emptyspace);
    stopTimer->setFont(QFont("Times", 14, QFont::Normal));
    connect(stopTimer, SIGNAL(clicked()), parent, SLOT(buttonStopTimerPressed()));
}
