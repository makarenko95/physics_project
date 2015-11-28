#include "billiardmodel.h"
#include "Math/Random.h"

const BilliardModel::Params BilliardModel::defaultParams =
{
    2.0,
    400,
    300,
    20.0,
    0.0,
    150.0,
    50.0
};

BilliardModel::BilliardModel(const Params & params)
    : piston_run(true)
{
    Load(params);
}

BilliardModel::~BilliardModel()
{
    delete collisionBox;
}

void BilliardModel::AddView(BilliardView &v)
{
    views.push_back(&v);
}

void BilliardModel::RemoveView(BilliardView &v)
{
    views.remove(&v);
}

void BilliardModel::UpdateViews(double timeStep) const
{
    for (auto view : views)
    {
        view->Update(*this, timeStep);
    }
}

void BilliardModel::ReloadViews() const
{
    for (auto view : views)
    {
        view->Reload(*this);
    }
}

void BilliardModel::update(double timeStep)
{
    collisionBox->simulate(timeStep);
    UpdateViews(timeStep);
}

double BilliardModel::getRadius() const
{
    return radius;
}

const BilliardModel::MyCollisionBox *BilliardModel::getCollisionBox() const
{
    return collisionBox;
}

void BilliardModel::GenerateParticles(const BilliardModel::Params & params)
{
    const MyCollisionBox::Box &boundaries = collisionBox->getBoundaries();

    int numParticles = params.particle_max_count;

    int particleIndex;

    for (particleIndex = 0; particleIndex < numParticles; ++particleIndex)
    {
        const int maxNumTries = 200;
        int tries;

        for (tries = 0; tries < maxNumTries; ++tries)
        {
            MyCollisionBox::Point p;
            MyCollisionBox::Vector v;

            //double len = 0;
            for (int j = 0; j < MyCollisionBox::dimension; ++j)
            {
                p[j] = boundaries.min[j] + MyCollisionBox::Scalar(radius) + (boundaries.max[j] - boundaries.min[j] - MyCollisionBox::Scalar(radius * 2)) * MyCollisionBox::Scalar(Math::randUniformCC());
            }

            double r = MyCollisionBox::Scalar(Math::randUniformCC(0.0, params.max_particle_velocity));
            double phi = MyCollisionBox::Scalar(Math::randUniformCC(0.0, 2 * acos(-1)));
            v[0] = r * cos(phi);
            v[1] = r * sin(phi);


            // Try adding the new particle:
            if (collisionBox->addParticle(p, v))
            {
                break;
            }
        }

        if (tries == maxNumTries) // Could not add particles after N tries; assume box is full
        {
            break;
        }
    }
}

void BilliardModel::Load(const BilliardModel::Params & params)
{
    maxVelocity = params.max_particle_velocity;
    radius = params.radius;

    MyCollisionBox::Point min, max;

    for (int i = 0; i < MyCollisionBox::dimension; ++i)
    {
        min[i] = MyCollisionBox::Scalar(0);
        max[i] = MyCollisionBox::Scalar(params.size);
    }

    collisionBox = new MyCollisionBox(MyCollisionBox::Box(min, max),
                                      MyCollisionBox::Scalar(radius));

    GenerateParticles(params);

    collisionBox->setPiston(params.piston_start_position, params.piston_end_position, params.piston_velocity);
    ReloadViews();
    //collisionBox->StartPiston();
}

void BilliardModel::Reload(const Params & input)
{
    delete collisionBox;
    Load(input);
}

void BilliardModel::StopPiston()
{
    collisionBox->StopPiston();
}

void BilliardModel::StartPiston(double vel)
{
    collisionBox->StartPiston(vel);
}

void BilliardModel::ResetPiston(double vel)
{
    if (collisionBox)
    {
        if (piston_run)
        {
            piston_run = false;
            StopPiston();
        }
        else
        {
            piston_run = true;
            StartPiston(vel);
        }
    }
}

double BilliardModel::GetAverageVelocity() const
{
    return collisionBox->GetAverageVelocity();
}

double BilliardModel::GetMaxVelocity() const
{
    return maxVelocity;
}
