#ifndef BILLIARDCONTROL_H
#define BILLIARDCONTROL_H

#include <Models/billiardmodel.h>

class BilliardControl
{
public:
    BilliardControl();

    void SetParams(const BilliardModel::Params & params);
    void SetParticleRadius(double radius);
    void SetBoxSize(int size);
    void SetMaxParticleNumber(int maxnum);
    void SetMaxParticleVelocity(double maxvel);
    void SetPistonEndPosition(double maxpistonpos);
    void SetPistonVelocity(double speed);
    BilliardModel::Params GetParams(void);

private:
    BilliardModel::Params params;
};

#endif // BILLIARDCONTROL_H
