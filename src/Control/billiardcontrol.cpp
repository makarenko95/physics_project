#include "billiardcontrol.h"

BilliardControl::BilliardControl():
    params({2.0,500,300,20.0,0.0,150.0,50.0})
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
void BilliardControl::SetParams(BilliardModelParams params)
{
    this->params = params;
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
BilliardModelParams BilliardControl::GetParams(){
    return params;
}
