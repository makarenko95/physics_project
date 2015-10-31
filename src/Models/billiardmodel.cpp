#include "billiardmodel.h"
#include "Math/Random.h"

BilliardModel::BilliardModel()
    : radius(5.0), collisionBox(NULL)
{
    MyCollisionBox::Point min, max;

    for (int i = 0; i < MyCollisionBox::dimension; ++i)
    {
        min[i] = MyCollisionBox::Scalar(0);
        max[i] = MyCollisionBox::Scalar(250);
    }

    collisionBox = new MyCollisionBox(MyCollisionBox::Box(min, max),
                                      MyCollisionBox::Scalar(radius));

    const MyCollisionBox::Box &boundaries = collisionBox->getBoundaries();

    int numParticles = 100;

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
                v[j] = MyCollisionBox::Scalar(Math::randUniformCC(-100.0, 100.0));
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

