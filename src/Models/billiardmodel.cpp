#include "billiardmodel.h"
#include "Math/Random.h"

BilliardModel::BilliardModel(const struct BilliardModel_params params)
    : radius(params.radius), collisionBox(NULL),settings({false,true})
{
    MyCollisionBox::Point min, max;

    for (int i = 0; i < MyCollisionBox::dimension; ++i)
    {
        min[i] = MyCollisionBox::Scalar(0);
        max[i] = MyCollisionBox::Scalar(params.size);
    }

    collisionBox = new MyCollisionBox(MyCollisionBox::Box(min, max),
                                      MyCollisionBox::Scalar(radius));

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

            for (int j = 0; j < MyCollisionBox::dimension; ++j)
            {
                p[j] = boundaries.min[j] + MyCollisionBox::Scalar(radius) + (boundaries.max[j] - boundaries.min[j] - MyCollisionBox::Scalar(radius * 2)) * MyCollisionBox::Scalar(Math::randUniformCC());
                v[j] = MyCollisionBox::Scalar(Math::randUniformCC(-params.max_particle_velocity, params.max_particle_velocity));
            }

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

    collisionBox->setPiston(params.piston_start_position, params.piston_end_position, params.piston_velocity);
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

void BilliardModel::UpdateViews() const
{
    for (auto iter : views)
    {
        iter->Update(*this);
    }
}

void BilliardModel::update(double timeStep)
{
    collisionBox->simulate(timeStep);
    UpdateViews();
}

double BilliardModel::getRadius() const
{
    return radius;
}

const BilliardModel::MyCollisionBox *BilliardModel::getCollisionBox() const
{
    return collisionBox;
}

void BilliardModel::Reload(BilliardModelParams *inputparams){
    if(collisionBox!=NULL) delete collisionBox;
    settings = {false,true};
    BilliardModelParams params = {2.0,500,300,20.0,0.0,150.0,50.0};
    if(inputparams!=NULL)
        params =*inputparams;
    radius = params.radius;
    MyCollisionBox::Point min, max;

    for (int i = 0; i < MyCollisionBox::dimension; ++i)
    {
        min[i] = MyCollisionBox::Scalar(0);
        max[i] = MyCollisionBox::Scalar(params.size);
    }

    collisionBox = new MyCollisionBox(MyCollisionBox::Box(min, max),
                                      MyCollisionBox::Scalar(radius));

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

            for (int j = 0; j < MyCollisionBox::dimension; ++j)
            {
                p[j] = boundaries.min[j] + MyCollisionBox::Scalar(radius) + (boundaries.max[j] - boundaries.min[j] - MyCollisionBox::Scalar(radius * 2)) * MyCollisionBox::Scalar(Math::randUniformCC());
                v[j] = MyCollisionBox::Scalar(Math::randUniformCC(-params.max_particle_velocity, params.max_particle_velocity));
            }

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

    collisionBox->setPiston(params.piston_start_position, params.piston_end_position, params.piston_velocity);
}
void BilliardModel::changeViewerSettings_DrawParticles()
{
    settings.drawParticles = !settings.drawParticles;
}
void BilliardModel::changeViewerSettings_DrawTrace()
{
    settings.drawTrace = !settings.drawTrace;
}
ViewerSettings BilliardModel::GetViewerSettings()const
{
    return settings;
}
