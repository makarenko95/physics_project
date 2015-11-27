#ifndef BILLIARDMODEL_H
#define BILLIARDMODEL_H

#include <Views/billiardview.h>
#include <CollisionBox.h>

#include <list>

class BilliardModel
{
public:

    struct Params
    {
        double radius;
        int size;
        int particle_max_count;
        double max_particle_velocity;
        double piston_start_position;
        double piston_end_position;
        double piston_velocity;
    };

    static const Params defaultParams;

    typedef CollisionBox<double, 2> MyCollisionBox;

    BilliardModel(const Params & params = defaultParams);
    ~BilliardModel();

    void AddView(BilliardView &);
    void RemoveView(BilliardView &);
    void UpdateViews() const;
    void update(double);
    double getRadius() const;
    void Reload(const Params & input = defaultParams);
    void StopPiston();
    void StartPiston(double);
    void ResetPiston(double);
    const MyCollisionBox *getCollisionBox() const;
private:

    std::list<BilliardView *> views;
    double radius;
    MyCollisionBox * collisionBox;

    void GenerateParticles(const Params &);
    void Load(const Params &);
    bool piston_run;
};

#endif // BILLIARDMODEL_H
