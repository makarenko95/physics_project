#ifndef BILLIARDVIEW_H
#define BILLIARDVIEW_H


class BilliardModel;

class BilliardView
{
public:
    BilliardView();
    virtual void Update(const BilliardModel &, double) = 0;
    virtual void Reload(const BilliardModel &) {}
};

#endif // BILLIARDVIEW_H
