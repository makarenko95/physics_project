#ifndef BILLIARDMODEL_H
#define BILLIARDMODEL_H

#include <Views/billiardview.h>
#include <CollisionBox.h>

#include <list>

class BilliardModel
{
public:
    typedef CollisionBox<double, 2> MyCollisionBox;

    BilliardModel();
    ~BilliardModel();

    void AddView(BilliardView &);
    void RemoveView(BilliardView &);
    void UpdateViews() const;
    void update(double);
    double getRadius() const;

    const MyCollisionBox *getCollisionBox() const;

private:

    std::list<BilliardView *> views;
    double radius;
    MyCollisionBox * collisionBox;
};

#endif // BILLIARDMODEL_H
