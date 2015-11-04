#ifndef BILLIARDCONTROL_H
#define BILLIARDCONTROL_H

typedef struct BilliardModel_params{
public:
    double radius;
    int size;
    int particle_max_count;
    double max_particle_velocity;
    double piston_start_position;
    double piston_end_position;
    double piston_velocity;
} BilliardModelParams;
class BilliardControl
{
public:
    BilliardControl();
    void SetParams(BilliardModelParams params);
    void SetParticleRadius(double radius);
    void SetBoxSize(int size);
    void SetMaxParticleNumber(int maxnum);
    void SetMaxParticleVelocity(double maxvel);
    void SetPistonEndPosition(double maxpistonpos);
    void SetPistonVelocity(double speed);
    BilliardModelParams GetParams(void);
private:
    BilliardModelParams params;
};

#endif // BILLIARDCONTROL_H
