#include "billiardcontrol.h"
#include <Models/billiardmodel.h>

BilliardControl::BilliardControl():
    params(BilliardModel::defaultParams)
{
}

void BilliardControl::SetBoxSize(int size)
{
    params.size = size;
}

void BilliardControl::SetMaxParticleNumber(int maxnum)
{
    params.particle_max_count = maxnum;
}

void BilliardControl::SetMaxParticleVelocity(double maxvel)
{
    params.max_particle_velocity = maxvel;
}

void BilliardControl::SetParams(const BilliardModel::Params & l_params)
{
   params = l_params;
}

void BilliardControl::SetParticleRadius(double radius)
{
    params.radius = radius;
}

void BilliardControl::SetPistonEndPosition(double maxpistonpos)
{
    params.piston_end_position = maxpistonpos;
}

void BilliardControl::SetPistonVelocity(double vel)
{
    params.piston_velocity = vel;
}

BilliardModel::Params BilliardControl::GetParams()
{
    return params;
}
