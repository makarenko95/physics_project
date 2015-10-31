#ifndef BILLIARDVIEW_H
#define BILLIARDVIEW_H


class BilliardModel;

class BilliardView
{
public:
    BilliardView();
    virtual void Update(const BilliardModel &) = 0;
};

#endif // BILLIARDVIEW_H
